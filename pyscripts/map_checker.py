import argparse
import os
import sys

# global variable
try:
    ARTHOME = os.environ["ARTEMIS_WORKDIR"]
except:
    sys.exit("command [artlogin user] needed")

CRIBDEV = 12
ENERGYDET = 6
TIMEDET = 7


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
        help="input the output csv file. (ex. mwdc/mwdc.yaml)",
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


if __name__ == "__main__":
    perser = get_argperser_setting()
    args = perser.parse_args()

    mapfile_list = get_mapfiles(args.input_mapper_conf)
    for mapfile in mapfile_list:
        mapinfo_list = get_mapfile_data(mapfile)
        for mapinfo in mapinfo_list:
            print(mapinfo)
