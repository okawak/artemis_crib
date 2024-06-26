import argparse
import os
import sys
from ruamel.yaml import YAML
import csv

# Global variable
# [artemis] home directory
try:
    ARTHOME = os.environ["ARTEMIS_WORKDIR"]
except:
    sys.exit("command [artlogin user] needed")

# [map] device id, name
DEV_DICT = {
    12: "CRIB",  # CRIB use 12
    0: "BIGRIPS",
    11: "SHARAQ",
    20: "20",  # ??
    31: "SHS1DAQ",  # used in SHARAQ FADC
    63: "GET",  # GET?
}


# [map] fp, name
FP_DICT = {
    0: "E7MPV",  # CRIB use fp as MPV ID
    1: "J1ADC",
    2: "J1TDC",
    3: "F3",
    4: "F4",
    5: "F5",
    6: "F6",
    7: "F7",
    8: "F8",
    9: "F9",
    10: "F10",
    11: "F11",
    12: "F12",
    20: "S0",
    21: "S1",
    22: "S2",
    34: "SHFADC",  # used in FADC
    62: "SHB3F",
    63: "B3F",
}

# [map] mod id, (name, channel number)
MODULE_DICT = {
    6: ("ADC", 32),  # for V785, MADC
    7: ("TDC", 128),  # for V1190A
    0: ("PPACQ", 128),  # assume 128ch module
    1: ("PPACT", 128),  # assume 128ch module
    2: ("PLAQ", 128),  # assume 128ch module
    3: ("PLAT", 128),  # assume 128ch module
    21: ("DALIA", 128),  # assume 128ch module
    22: ("DALIT", 128),  # assume 128ch module
    31: ("SHBLD", 128),  # assume 128ch module
    32: ("SHCRDC", 128),  # assume 128ch module
    33: ("SHCRDCA", 128),  # assume 128ch module
    55: ("FADC", 32),  # FADC in SHARAQ exp
    60: ("TIMESTAMP", 1),  # for MPV TS
    63: ("SCALER", 32),  # for SIS3820
}

# after this number, begin on a new line (just format)
UNIT = 16


def get_argperser_setting():
    argparser = argparse.ArgumentParser()
    argparser.add_argument(
        "-i",
        "--input-mapper",
        type=str,
        help="if you don't use default mapper.conf, please specify the path (ex test/mapper.conf)",
        default="mapper.conf",
    )
    argparser.add_argument(
        "-o",
        "--output",
        type=str,
        help="if you want to specify the outputfile name, input the output csv file. (default. pyscripts/out/mapcheckr.csv)",
        default="pyscripts/out/mapchecker.csv",
    )
    return argparser


# read from mapper.conf => infomation for each mapfile
def get_mapfiles(mapper: str) -> list:
    mapfile_list = []
    if os.path.exists(f"{ARTHOME}/{mapper}"):
        with open(f"{ARTHOME}/{mapper}", "r") as file:
            for line in file:
                comment_index = line.find("#")
                if comment_index == -1:
                    processed_line = line.strip()
                else:
                    processed_line = line[:comment_index].strip()

                if processed_line:
                    mapfile_list.append(processed_line)
    else:
        sys.exit(f"{ARTHOME}/{mapper} does not found!")

    return mapfile_list


# read each map file => information each line (channel)
def get_mapfile_data(mapfile: str) -> list:
    mapinfo = mapfile.split()  # [0]: path, [1]: number
    try:
        maplen = int(mapinfo[1])
    except:
        sys.exit("mapper.conf format error: [path] [num] (deliminator is space)")

    if len(mapinfo) != 2:
        print(f"Error in mapper.conf:\n{mapfile}")
        sys.exit("mapper.conf format error: [path] [num] (deliminator is space)")

    mapinfo_list = []
    if os.path.exists(f"{ARTHOME}/{mapinfo[0]}"):
        with open(f"{ARTHOME}/{mapinfo[0]}", "r") as file:
            for line in file:
                comment_index = line.find("#")
                if comment_index != -1:
                    line = line[:comment_index].strip()

                parts = []
                for part in line.split(","):
                    for item in part.split():
                        try:
                            parts.append(int(item))
                        except:
                            sys.exit(f"mapfile error:\n{mapinfo[0]}")

                if parts:
                    if len(parts) != 2 + 5 * maplen:
                        sys.exit(
                            f"mapfile parameter number is wrong! {mapinfo[0]}\n{parts} but {maplen} in mapper.conf"
                        )
                    mapinfo_list.append(parts)

    else:
        sys.exit(f"{ARTHOME}/{mapinfo[0]} is not found!")

    return mapinfo_list


def add_map_info(map_dict: dict, mapinfo: list) -> dict:
    if (len(mapinfo) - 2) % 5 != 0:
        sys.exit(f"mapfile parameter number is wrong!\nwrong line: {mapinfo}")

    for i in range((len(mapinfo) - 2) // 5):
        if not mapinfo[5 * i + 2] in DEV_DICT:
            sys.exit(
                f"please add DEV_DICT in this file for new device ID {mapinfo[5 * i + 2]}!\nline: {mapinfo}"
            )

        key_tuple = (
            mapinfo[5 * i + 2],
            mapinfo[5 * i + 3],
            mapinfo[5 * i + 4],
            mapinfo[5 * i + 5],
        )
        child_key = mapinfo[5 * i + 6]
        child_value = f"{mapinfo[0]}-{mapinfo[1]}[{i}]"

        if key_tuple in map_dict:
            if child_key in map_dict[key_tuple]:
                sys.exit(
                    f"Error: duplicate maps! duplicate the following:\n(dev, fp, det, geo, ch) = {key_tuple + tuple([child_key])}"
                )
            else:
                map_dict[key_tuple][child_key] = child_value
        else:
            map_dict[key_tuple] = {child_key: child_value}

    return map_dict


def add_tref_info(map_dict: dict) -> dict:
    if os.path.exists(f"{ARTHOME}/steering/tref.yaml"):
        yaml = YAML()
        with open(f"{ARTHOME}/steering/tref.yaml", "r", encoding="utf-8") as file:
            tref_yaml = yaml.load(file)
    else:
        sys.exit(f"{ARTHOME}/steering/tref.yaml does not exist!")

    tref_list = []
    try:
        for i in range(len(tref_yaml["Processor"])):
            refconfig = tref_yaml["Processor"][i]["parameter"]["RefConfig"]
            tref_list.append(refconfig)
    except:
        sys.exit("steering/tref.yaml format seems wrong!")

    for tref_info in tref_list:
        if not tref_info[0] in DEV_DICT:
            sys.exit(
                f"please add the DEV_DICT in this file for new device ID {tref_info[0]}\nline in tref.yaml: {tref_info}"
            )
        if len(tref_info) != 5:
            sys.exit(f"tref.yaml RefConfig format is wrong!\nwrong line: {tref_info}")

        key_tuple = (tref_info[0], tref_info[1], tref_info[2], tref_info[3])
        child_key = tref_info[4]

        if key_tuple in map_dict:
            if child_key in map_dict[key_tuple]:
                print(
                    f"Warning: duplicate maps! duplicate the following: (dev, fp, det, geo, ch) = {key_tuple + tuple([child_key])}"
                )
                print("do you use some signals and tref at the same time???")
                print()
            else:
                map_dict[key_tuple][child_key] = "TREF"
        else:
            sys.exit(
                f"could not find the module for this tref!\nwrong line: {tref_info}"
            )

    return map_dict


def show_all_mapinfo(map_dict: dict, filename: str) -> None:
    print("\033[1m\033[4mOutput format [CatID]-[fID][ch]\033[0m\n")
    with open(f"{ARTHOME}/{filename}", mode="w", newline="") as file:
        writer = csv.writer(file, lineterminator="\n")
        for key_tuple, mod_dict in sorted(map_dict.items()):
            dev, fp, det, geo = key_tuple
            if not det in MODULE_DICT:
                sys.exit(
                    'please add the MODULE_DICT the new module info in this "map_checker.py"'
                )

            print(
                f"{key_tuple} = {DEV_DICT[dev]}, {FP_DICT[fp]}, {MODULE_DICT[det][0]}, geo={geo}"
            )

            header_list = [""] * UNIT
            header_list[0] = (
                f"{key_tuple} = {DEV_DICT[dev]}, {FP_DICT[fp]}, {MODULE_DICT[det][0]}, geo={geo}"
            )
            writer.writerow(header_list)

            writer_list = [""] * UNIT
            for i in range(MODULE_DICT[det][1]):
                if i in mod_dict:
                    print(f"{mod_dict[i]:<11}", end="")
                    writer_list[i % UNIT] = mod_dict[i]
                else:
                    print("----       ", end="")
                    writer_list[i % UNIT] = "--"

                if (i + 1) % UNIT == 0 or (i + 1) == MODULE_DICT[det][1]:
                    print()
                    writer.writerow(writer_list)
                    writer_list = [""] * UNIT
            print()
            writer.writerow([""] * UNIT)

    print(f"\033[1m\033[4mInfo:\033[0m\nsaved {filename}")


if __name__ == "__main__":
    perser = get_argperser_setting()
    args = perser.parse_args()

    # prepare map information as a dictionary
    map_dict = {}
    mapfile_list = get_mapfiles(args.input_mapper)
    for mapfile in mapfile_list:
        mapinfo_list = get_mapfile_data(mapfile)
        for mapinfo in mapinfo_list:
            map_dict = add_map_info(map_dict, mapinfo)

    map_dict = add_tref_info(map_dict)

    # show the result in stdout and save file at arts.output
    show_all_mapinfo(map_dict, args.output)
