import os
import sys
import pyTSrim as sr
import pyMass as mass
import matplotlib.pyplot as plt
from ruamel.yaml import YAML
import numpy as np

# Global constant
ARTHOME = os.getenv("ARTEMIS_WORKDIR")
if not ARTHOME:
    raise EnvironmentError("command [artlogin user] needed")

plt.rcParams["font.family"] = "Liberation Sans"
plt.rcParams["font.size"] = 16
# plt.rcParams["axes.labelweight"] = "bold"
plt.rcParams["axes.labelsize"] = 20
plt.rcParams["axes.titlesize"] = 20
plt.rcParams["legend.fontsize"] = 14
plt.rcParams["legend.title_fontsize"] = 14


class CRIBPID:
    """
    PID calculation at F2 and F3 focal plane.
    It is almost the same with S. Hayakawa-san's application
    https://www.cns.s.u-tokyo.ac.jp/crib/cgi-bin/pid/CRIB_PID_calc.html
    """

    LIGHTSPEED = 299792458.0  # m/s
    KJ2MEV = 6.2415064e12  # J -> MeV
    UNITCHARGE = 1.60217663e-19  # C (A s)
    LENGTHF0F2 = 7.8  # m, length between F0 and F2
    LENGTHF0F3 = 12.97  # m, length between F0 and F3
    SEC2MSEC = 1.0e9  # s -> ms
    MM2M = 1.0e-3  # mm -> m, also used for um -> mm

    def __init__(self, config_path=None):
        if config_path is None:
            raise ValueError(
                "configuration path argument is required and cannot be None"
            )

        if not os.path.exists(config_path):
            raise FileNotFoundError(f"{config_path} does not exist!")

        self.config_path = config_path

        tsrim_home = os.getenv("TSRIM_DATA_HOME")
        if not tsrim_home:
            raise EnvironmentError("Please set the TSrim environment variable!")
        self.tsrim_home = tsrim_home

        self.__load_yaml()
        self.__set_datapath()
        self.f2_datas = None
        self.f3_datas = None

    def __load_yaml(self) -> None:
        yaml = YAML()
        with open(self.config_path, "r", encoding="utf-8") as file:
            try:
                pid_yaml = yaml.load(file)
            except YAML.YAMLError as e:
                raise ValueError(f"Error parsing YAML file '{self.config_path}': {e}")
            except Exception as e:
                raise Exception(f"Unexpected error reading '{self.config_path}': {e}")

        # set ions information
        self.ion_list = pid_yaml["input_ions"]

        # F1 parameters
        f1_yaml = pid_yaml["f1_parameters"]
        self.brho = f1_yaml["brho"]
        self.degrader_material = f1_yaml["degrader_material"]
        self.degrader_thickness = f1_yaml["degrader_thickness"] * self.MM2M
        self.rf_period = f1_yaml["rf_period"]

        # F2 parameters
        f2_yaml = pid_yaml["f2_parameters"]
        self.ppac_thickness = f2_yaml["PPAC_thickness"] * self.MM2M
        self.ssd_thickness = f2_yaml["SSD_thickness"] * self.MM2M
        self.f2_rf_offset = f2_yaml["rf_offset"]
        self.f2_rf_range = f2_yaml["rf_range"]
        self.f2_energy_range = f2_yaml["energy_range"]

        # F3 parameters
        f3_yaml = pid_yaml["f3_parameters"]
        self.a_thickness = f3_yaml["a_thickness"] * self.MM2M
        self.b_thickness = f3_yaml["b_thickness"] * self.MM2M
        self.ab_distance = f3_yaml["distance"]
        self.trigger_flag = f3_yaml["trigger"]
        self.f3_rf_offset = f3_yaml["rf_offset"]
        self.f3_tof_offset = f3_yaml["tof_offset"]
        self.f3_rf_range = f3_yaml["rf_range"]
        self.f3_tof_range = f3_yaml["tof_range"]

    def __set_datapath(self) -> None:
        data_paths = []
        materials = ["mylar", "si"]
        if self.degrader_material != "mylar":
            materials.append(self.degrader_material)

        for mat in materials:
            filename = f"range_fit_pol16_{mat}.txt"
            data_path = os.path.join(self.tsrim_home, mat, filename)
            if not os.path.exists(data_path):
                raise FileNotFoundError(f"TSrim Error: {data_path} does not exist!")
            data_paths.append(data_path)

        self.datapaths = data_paths

    def calculation(self) -> None:
        """
        Main PID calculation!
        set data points
        """
        f2_datas = []
        f3_datas = []

        # TSrim initialization
        srim = sr.TSrim()
        for path in self.datapaths:
            srim.AddElement("srim", 16, path)

        self.__print_headers()
        for ion in self.ion_list:
            z, a, q, color = ion
            m = mass.Mass(z, a) * mass.amu

            # calculate the kinetic energy from Brho
            Brhoqc = self.brho * q * self.UNITCHARGE * self.LIGHTSPEED * self.KJ2MEV
            beam_energy = m * (np.sqrt(1.0 + (Brhoqc / m) ** 2) - 1.0)
            E_after_degrader = srim.EnergyNew(
                z, a, beam_energy, self.degrader_material, self.degrader_thickness
            )

            # calculate energy loss
            E_after_f2ppac = srim.EnergyNew(
                z, a, E_after_degrader, "mylar", self.ppac_thickness
            )
            E_in_f2ssd = E_after_f2ppac - srim.EnergyNew(
                z, a, E_after_f2ppac, "si", self.ssd_thickness
            )

            E_after_ppaca = srim.EnergyNew(
                z, a, E_after_degrader, "mylar", self.a_thickness
            )
            E_after_ppacb = srim.EnergyNew(
                z, a, E_after_ppaca, "mylar", self.b_thickness
            )

            # calculate tof (ns)
            tof_f0f2 = (
                self.SEC2MSEC * self.LENGTHF0F2 / self.__MeV_to_ms(beam_energy, m)
            )
            tof_f0f3 = (
                self.SEC2MSEC * self.LENGTHF0F3 / self.__MeV_to_ms(beam_energy, m)
            )
            tof_ppacs = (
                self.SEC2MSEC
                * self.ab_distance
                * self.MM2M
                / self.__MeV_to_ms(E_after_ppaca, m)
            )

            print(
                f"{a}{mass.GetEl(z)}{q}+ :".center(10)
                + f"{beam_energy:.2f}".center(10)
                + f"{E_after_degrader:.2f}".center(10)
                + f"{E_after_f2ppac:.2f}".center(10)
                + f"{E_in_f2ssd:.2f}".center(10)
                + f"{tof_f0f2:.2f}".center(10)
                + f"{tof_f0f3:.2f}".center(10)
                + f"{tof_ppacs:.2f}".center(10)
                + f"{E_after_ppacb:.2f}".center(10)
            )

            # CRIB use RF as start: f2/f3, stop: f0, so tof is negative value
            f2_datas.append([z, a, q, -tof_f0f2, E_in_f2ssd, color])
            f3_datas.append([z, a, q, -tof_f0f3, tof_ppacs, color])

        self.__print_conditions()

        self.f2_datas = f2_datas
        self.f3_datas = f3_datas

    def show_f2_pid(self, figure_path=f"{ARTHOME}/pyscripts/out/f2_pid.png"):
        if self.f2_datas == None:
            raise ValueError("need calculation first")

        x = []
        y = []
        labels = []
        colors = []
        color_map = {0: "red", 1: "blue", 2: "black"}

        for data in self.f2_datas:
            z, a, q, x_data, y_data, color = data
            x_data += self.f2_rf_offset
            if x_data < self.f2_rf_range[0]:
                while x_data < self.f2_rf_range[0]:
                    x_data += self.rf_period
            else:
                while x_data > self.f2_rf_range[0]:
                    x_data -= self.rf_period
                x_data += self.rf_period

            while x_data < self.f2_rf_range[1]:
                x.append(x_data)
                x_data += self.rf_period
                y.append(y_data)
                colors.append(color)
                labels.append(rf"$^{{{a}}}${mass.GetEl(z)}$^{{{q}+}}$")

        plt.figure(figsize=(8, 8))
        for i in range(len(x)):
            plt.scatter(x[i], y[i], color=color_map[colors[i]], s=100)
            plt.text(x[i] + 0.1, y[i], labels[i], fontsize=15)

        plt.xlabel(r"$T_{F2PPAC-RF}$ (ns)")
        plt.ylabel(r"$E_{SSD\ after\ F2PPAC}$ (MeV)")
        plt.title("F2 PID (E-TOF)")
        plt.grid(which="both", linestyle="--", linewidth="0.2", color="gray")
        plt.minorticks_on()
        plt.grid(which="minor", linestyle=":", linewidth="0.1", color="gray")
        plt.savefig(figure_path)
        print(f"saved {figure_path}")
        plt.clf()

    def show_f3_pid(self, figure_path=f"{ARTHOME}/pyscripts/out/f3_pid.png"):
        if self.f3_datas == None:
            raise ValueError("need calculation first")

        x = []
        y = []
        labels = []
        colors = []
        color_map = {0: "red", 1: "blue", 2: "black"}

        for data in self.f3_datas:
            z, a, q, x_data, y_data, color = data
            x_data += self.f3_rf_offset
            y_data += self.f3_tof_offset
            if x_data < self.f3_rf_range[0]:
                while x_data < self.f3_rf_range[0]:
                    x_data += self.rf_period
            else:
                while x_data > self.f3_rf_range[0]:
                    x_data -= self.rf_period
                x_data += self.rf_period

            while x_data < self.f3_rf_range[1]:
                x.append(x_data)
                x_data += self.rf_period
                y.append(y_data)
                colors.append(color)
                labels.append(rf"$^{{{a}}}${mass.GetEl(z)}$^{{{q}+}}$")

        plt.figure(figsize=(8, 8))
        for i in range(len(x)):
            plt.scatter(x[i], y[i], color=color_map[colors[i]], s=100)
            plt.text(x[i] + 0.1, y[i], labels[i], fontsize=15)

        plt.xlabel(r"$T_{F3PPAC-RF}$ (ns)")
        plt.ylabel(r"$T_{a/b}$ (ns)")
        plt.title("F3 PID (TOF-TOF)")
        plt.grid(which="both", linestyle="--", linewidth="0.2", color="gray")
        plt.minorticks_on()
        plt.grid(which="minor", linestyle=":", linewidth="0.1", color="gray")
        plt.savefig(figure_path)
        print(f"saved {figure_path}")
        plt.clf()

    def __MeV_to_ms(self, energy: float, mass: float) -> float:
        """
        energy: MeV, mass: MeV/c**2
        MeV -> m/s
        """
        return self.LIGHTSPEED * np.sqrt(1.0 - (1.0 / (energy / mass + 1.0)) ** 2)

    def __print_headers(self) -> None:
        print("[Result]")
        header_titles = [
            "",
            "aft F0tar",
            "aft F1deg",
            "bfr f2SSD",
            "f2SSD",
            "F0-F2",
            "F0-F3",
            "bet a/b",
            "bfr F3SSD",
        ]
        header_names = [
            "Ion name:",
            "E (MeV)",
            "E (MeV)",
            "E (MeV)",
            "E (MeV)",
            "TOF (ns)",
            "TOF (ns)",
            "TOF (ns)",
            "E (MeV)",
        ]
        print(
            f"{header_titles[0]}".center(10)
            + f"{header_titles[1]}".center(10)
            + f"{header_titles[2]}".center(10)
            + f"{header_titles[3]}".center(10)
            + f"{header_titles[4]}".center(10)
            + f"{header_titles[5]}".center(10)
            + f"{header_titles[6]}".center(10)
            + f"{header_titles[7]}".center(10)
            + f"{header_titles[8]}".center(10)
        )
        print(
            f"{header_names[0]}".center(10)
            + f"{header_names[1]}".center(10)
            + f"{header_names[2]}".center(10)
            + f"{header_names[3]}".center(10)
            + f"{header_names[4]}".center(10)
            + f"{header_names[5]}".center(10)
            + f"{header_names[6]}".center(10)
            + f"{header_names[7]}".center(10)
            + f"{header_names[8]}".center(10)
        )

    def __print_conditions(self) -> None:
        print(
            "[condition]\n"
            f"  Brho = {self.brho:.5f} Tm\n"
            f"  RF period = {self.rf_period:.1f} ns\n"
            f"  F1: Degrader material: {self.degrader_material}\n"
            f"      Degrader thickness = {self.degrader_thickness / self.MM2M} um\n"
            f"  F2: PPAC thickness = {self.ppac_thickness / self.MM2M:.1f} um (equiv. mylar)\n"
            f"      SSD thickness = {self.ssd_thickness / self.MM2M:.1f} um\n"
            f"  F3: PPACa/MWDCa thickness = {self.a_thickness / self.MM2M:.1f} um (equiv. mylar)\n"
            f"      Distance between a and b = {self.ab_distance:.1f} mm\n"
        )

    def check_vars(self) -> None:
        """
        For debug, show all class members
        """
        print("[debug]")
        for key, value in self.__dict__.items():
            print(f"  {key}: {value}")

    def usage(self) -> None:
        print(
            "[usage]\n"
            "  obj = CRIBPID('path to the config yaml, ex ../prm/pid/hoge.yaml')\n"
            "  obj.calculation()\n"
            "  obj.show_f2_pid() # if you want to save figure"
        )


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python CRIB_PID.py <path to config yaml>")
        sys.exit(1)

    obj = CRIBPID(sys.argv[1])
    obj.calculation()
    obj.show_f2_pid()
    obj.show_f3_pid()
