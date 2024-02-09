import argparse
import os
import sys
from ruamel.yaml import YAML
import csv

# global variable
try:
    ARTHOME = os.environ["ARTEMIS_WORKDIR"]
except:
    sys.exit("command [artlogin user] needed")

CRIBDEV = 12

# key: mod id, value: (name, channel number)
MODULE_DICT = {
    6: ("ADC", 32),
    7: ("TDC", 128),
    63: ("SCALER", 32),
    60: ("TIMESTAMP", 1),
}

# MPV information
# key: fp (as MPV ID), value: name
MPV_DICT = {
    0: "E7MPV",
    1: "J1ADC",
    2: "J1TDC",
}

CHUNIT = 16  # after this number, begin on a new line


def get_argperser_setting():
    argparser = argparse.ArgumentParser()
    argparser.add_argument(
        "-i",
        "--input-mapper-conf",
        type=str,
        help="if you don't use default mapper.conf, please specify the path (ex test/mapper.conf)",
        default="mapper.conf",
    )
    argparser.add_argument(
        "-o",
        "--output",
        type=str,
        help="input the output csv file. (default. pyscripts/out/mapcheck.csv)",
        default="pyscripts/out/mapchecker.csv",
    )
    return argparser


# read from mapper.conf => infomation for each mapfile
def get_mapfiles(mapper: str):
    mapfile_list = []
    if os.path.exists("{}/{}".format(ARTHOME, mapper)):
        with open("{}/{}".format(ARTHOME, mapper), "r") as file:
            for line in file:
                comment_index = line.find("#")
                if comment_index == -1:
                    processed_line = line.strip()
                else:
                    processed_line = line[:comment_index].strip()

                if processed_line:
                    mapfile_list.append(processed_line)
    else:
        sys.exit("{}/{} does not found!".format(ARTHOME, mapper))

    return mapfile_list


# read each map file => information each line (channel)
def get_mapfile_data(mapfile: str):
    mapinfo = mapfile.split()  # [0]: path, [1]: number
    try:
        maplen = int(mapinfo[1])
    except:
        sys.exit("mapper.conf format error: [path] [num] (deliminator is space)")

    if len(mapinfo) != 2:
        print("Error in mapper.conf:\n{}".format(mapfile))
        sys.exit("mapper.conf format error: [path] [num] (deliminator is space)")

    mapinfo_list = []
    if os.path.exists("{}/{}".format(ARTHOME, mapinfo[0])):
        with open("{}/{}".format(ARTHOME, mapinfo[0]), "r") as file:
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
                            sys.exit("mapfile error:\n{}".format(mapinfo[0]))

                if parts:
                    if len(parts) != 2 + 5 * maplen:
                        sys.exit(
                            "mapfile parameter number is wrong! {}\n{} but {} in mapper.conf".format(
                                mapinfo[0], parts, maplen
                            )
                        )
                    mapinfo_list.append(parts)

    else:
        sys.exit("{}/{} is not found!".format(ARTHOME, mapinfo[0]))

    return mapinfo_list


def add_map_info(dict: dict, mapinfo: list) -> dict:
    if (len(mapinfo) - 2) % 5 != 0:
        sys.exit("mapfile parameter number is wrong!\nwrong line: {}".format(mapinfo))

    for i in range((len(mapinfo) - 2) // 5):
        if mapinfo[5 * i + 2] != CRIBDEV:
            sys.exit(
                "mapfile dev ID is not CRIB ID 12!\nwrong line: {}".format(mapinfo)
            )

        key_tuple = (mapinfo[5 * i + 3], mapinfo[5 * i + 4], mapinfo[5 * i + 5])
        child_key = mapinfo[5 * i + 6]
        child_value = "{}-{}".format(mapinfo[0], mapinfo[1])

        if key_tuple in dict:
            if child_key in dict[key_tuple]:
                sys.exit(
                    "Error: duplicate maps! duplicate the following:\n(fp, det, geo, ch) = {}".format(
                        key_tuple + tuple([child_key])
                    )
                )
            else:
                dict[key_tuple][child_key] = child_value
        else:
            dict[key_tuple] = {child_key: child_value}

    return dict


def add_tref_info(dict: dict) -> dict:
    if os.path.exists("{}/steering/tref.yaml".format(ARTHOME)):
        yaml = YAML()
        with open(
            "{}/steering/tref.yaml".format(ARTHOME), "r", encoding="utf-8"
        ) as file:
            tref_info = yaml.load(file)
    else:
        sys.exit("{}/steering/tref.yaml does not exist!".format(ARTHOME))

    tref_list = []
    try:
        for i in range(len(tref_info["Processor"])):
            refconfig = tref_info["Processor"][i]["parameter"]["RefConfig"]
            tref_list.append(refconfig)
    except:
        sys.exit("steering/tref.yaml format seems wrong!")

    for tref_info in tref_list:
        if tref_info[0] != CRIBDEV:
            sys.exit(
                "tref.yaml dev ID is not CRIB ID 12!\nwrong line: {}".format(tref_info)
            )
        if len(tref_info) != 5:
            sys.exit(
                "tref.yaml RefConfig format is wrong!\nwrong line: {}".format(tref_info)
            )

        key_tuple = (tref_info[1], tref_info[2], tref_info[3])
        child_key = tref_info[4]

        if key_tuple in dict:
            if child_key in dict[key_tuple]:
                print(
                    "Warning: duplicate maps! duplicate the following:\n(fp, det, geo, ch) = {}".format(
                        key_tuple + tuple([child_key])
                    )
                )
                print("do you use some signal and tref at the same time???")
                print()
            else:
                dict[key_tuple][child_key] = "TREF"
        else:
            sys.exit(
                "could not find the module for this tref!\nwrong line: {}".format(
                    tref_info
                )
            )

    return dict


if __name__ == "__main__":
    perser = get_argperser_setting()
    args = perser.parse_args()

    map_dict = {}

    mapfile_list = get_mapfiles(args.input_mapper_conf)
    for mapfile in mapfile_list:
        mapinfo_list = get_mapfile_data(mapfile)
        for mapinfo in mapinfo_list:
            map_dict = add_map_info(map_dict, mapinfo)

    map_dict = add_tref_info(map_dict)

    with open("{}/{}".format(ARTHOME, args.output), mode="w", newline="") as file:
        writer = csv.writer(file)
        for key_tuple, mod_dict in sorted(map_dict.items()):
            fp, dev, geo = key_tuple
            if not dev in MODULE_DICT:
                sys.exit(
                    'please add the MODULE_DICT the new module info in this "map_checker.py"'
                )

            print(key_tuple, end="")
            print(" = {}, {}, geo={}".format(MPV_DICT[fp], MODULE_DICT[dev][0], geo))
            writer.writerow(
                [
                    "{} = {}, {}, geo={}".format(
                        key_tuple, MPV_DICT[fp], MODULE_DICT[dev][0], geo
                    )
                ]
            )

            writer_list = []
            for i in range(MODULE_DICT[dev][1]):
                if i in mod_dict:
                    print(f"{mod_dict[i]:<8}", end="")
                    writer_list.append(mod_dict[i])
                else:
                    print("----    ", end="")
                    writer_list.append("--")

                if (i + 1) % CHUNIT == 0 or (i + 1) == MODULE_DICT[dev][1]:
                    print()
                    writer.writerow(writer_list)
                    writer_list = []
            print()
            writer.writerow([])

    print("saved for {}".format(args.output))
