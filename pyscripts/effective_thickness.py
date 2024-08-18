import os
import pyTSrim as sr
import pyMass as mass
import ROOT


class EffectiveThickness:
    tsrim_home = os.getenv("TSRIM_DATA_HOME")
    if not tsrim_home:
        raise EnvironmentError("Please set the TSrim environment variable!")

    def __init__(self, z=None, a=None, target=None, pressure=None, temperature=None):
        self.beam_z = None
        self.beam_a = None
        self.target = None
        self.pressure = None
        self.temperature = None
        self.datapath = None
        self.do_init = False

        self.set_parameters(z, a, target, pressure, temperature)

    def set_parameters(self, z, a, target, pressure=None, temperature=None) -> None:
        if z is not None and not isinstance(z, int):
            raise TypeError("beam_z must be an int or None")
        if a is not None and not isinstance(a, int):
            raise TypeError("beam_a must be an int or None")
        if target is not None and not isinstance(target, str):
            raise TypeError("target must be a str or None")
        if pressure is not None and not isinstance(pressure, float):
            raise TypeError("pressure must be a float or None")
        if temperature is not None and not isinstance(temperature, float):
            raise TypeError("temperature must be a float or None")

        if self.do_init:
            self.show_status()
            raise ValueError("Beam and target information is already registered")

        self.beam_z = z
        self.beam_a = a
        self.target = target
        self.pressure = pressure or sr.P1
        self.temperature = temperature or sr.T0

        self.__set_datapath()

    def __set_datapath(self) -> None:
        if not self.target:
            return

        filename = f"range_fit_pol16_{self.target}.txt"
        data_path = os.path.join(self.tsrim_home, self.target, filename)
        if not os.path.exists(data_path):
            raise FileNotFoundError(f"{data_path} does not exist!")

        self.datapath = data_path
        self.do_init = True

    def show_status(self) -> None:
        status = {
            "do_init": self.do_init,
            "beam_z": self.beam_z,
            "beam_a": self.beam_a,
            "target": self.target,
            "pressure": self.pressure,
            "temperature": self.temperature,
            "datafile": self.datapath,
        }
        for key, value in status.items():
            print(f"{key}: {value}")

    def get_thickness_gr(self, delta: float, unit_type: str) -> ROOT.TGraph:
        if not self.do_init:
            raise ValueError("not initialized the instance")

        if unit_type == "mm":
            unit_flag = 0
        elif unit_type == "g/cm2":
            unit_flag = 1
        elif unit_type == "atom/cm2":
            unit_flag = 2
        else:
            raise ValueError(
                f"unit: {unit_type} is not supported, only mm, g/cm2 and atom/cm2"
            )

        print(f"calculate effective thickness unit: {unit_type}")
        gr = ROOT.TGraph()
        return gr


if __name__ == "__main__":
    ef = EffectiveThickness()
    ef.set_parameters(6, 12, "he", 250.0, 300.0)
    # ef.set_parameters(6, 12, "he", 250.0, "300.0")
    # ef.set_parameters(6, 12, "he")
    ef.show_status()
