import sys
import os
import glob
import subprocess

if __name__ == '__main__':
    ARTEMIS_WORK = os.environ['ARTEMIS_WORKDIR']

    # high all
    output = ARTEMIS_WORK + "/output/single/all/high_all.root"

    inputs = ""
    input_array = glob.glob(ARTEMIS_WORK + "/output/single/all/high/*.root");
    for i in range(len(input_array)):
        inputs += input_array[i] + " "

    cmd = "cd " + ARTEMIS_WORK + "; artemis -l '" + ARTEMIS_WORK + "/scripts/processline.C(\"mergefile " + output + " " + inputs + "\")'"

    print(cmd)
    subprocess.call([cmd], shell=True, executable="/usr/bin/zsh")

    # high si26
    output = ARTEMIS_WORK + "/output/single/si26/high_si26.root"

    inputs = ""
    input_array = glob.glob(ARTEMIS_WORK + "/output/single/si26/high/*.root");
    for i in range(len(input_array)):
        inputs += input_array[i] + " "

    cmd = "cd " + ARTEMIS_WORK + "; artemis -l '" + ARTEMIS_WORK + "/scripts/processline.C(\"mergefile " + output + " " + inputs + "\")'"

    print(cmd)
    subprocess.call([cmd], shell=True, executable="/usr/bin/zsh")

    # high al25
    output = ARTEMIS_WORK + "/output/single/al25/high_al25.root"

    inputs = ""
    input_array = glob.glob(ARTEMIS_WORK + "/output/single/al25/high/*.root");
    for i in range(len(input_array)):
        inputs += input_array[i] + " "

    cmd = "cd " + ARTEMIS_WORK + "; artemis -l '" + ARTEMIS_WORK + "/scripts/processline.C(\"mergefile " + output + " " + inputs + "\")'"

    print(cmd)
    subprocess.call([cmd], shell=True, executable="/usr/bin/zsh")

    # high mg24
    output = ARTEMIS_WORK + "/output/single/mg24/high_mg24.root"

    inputs = ""
    input_array = glob.glob(ARTEMIS_WORK + "/output/single/mg24/high/*.root");
    for i in range(len(input_array)):
        inputs += input_array[i] + " "

    cmd = "cd " + ARTEMIS_WORK + "; artemis -l '" + ARTEMIS_WORK + "/scripts/processline.C(\"mergefile " + output + " " + inputs + "\")'"

    print(cmd)
    subprocess.call([cmd], shell=True, executable="/usr/bin/zsh")

    # bg all
    output = ARTEMIS_WORK + "/output/single/all/bg_all.root"

    inputs = ""
    input_array = glob.glob(ARTEMIS_WORK + "/output/single/all/bg/*.root");
    for i in range(len(input_array)):
        inputs += input_array[i] + " "

    cmd = "cd " + ARTEMIS_WORK + "; artemis -l '" + ARTEMIS_WORK + "/scripts/processline.C(\"mergefile " + output + " " + inputs + "\")'"

    print(cmd)
    subprocess.call([cmd], shell=True, executable="/usr/bin/zsh")

    # bg si26
    output = ARTEMIS_WORK + "/output/single/si26/bg_si26.root"

    inputs = ""
    input_array = glob.glob(ARTEMIS_WORK + "/output/single/si26/bg/*.root");
    for i in range(len(input_array)):
        inputs += input_array[i] + " "

    cmd = "cd " + ARTEMIS_WORK + "; artemis -l '" + ARTEMIS_WORK + "/scripts/processline.C(\"mergefile " + output + " " + inputs + "\")'"

    print(cmd)
    subprocess.call([cmd], shell=True, executable="/usr/bin/zsh")

    # bg al25
    output = ARTEMIS_WORK + "/output/single/al25/bg_al25.root"

    inputs = ""
    input_array = glob.glob(ARTEMIS_WORK + "/output/single/al25/bg/*.root");
    for i in range(len(input_array)):
        inputs += input_array[i] + " "

    cmd = "cd " + ARTEMIS_WORK + "; artemis -l '" + ARTEMIS_WORK + "/scripts/processline.C(\"mergefile " + output + " " + inputs + "\")'"

    print(cmd)
    subprocess.call([cmd], shell=True, executable="/usr/bin/zsh")

    # bg mg24
    output = ARTEMIS_WORK + "/output/single/mg24/bg_mg24.root"

    inputs = ""
    input_array = glob.glob(ARTEMIS_WORK + "/output/single/mg24/bg/*.root");
    for i in range(len(input_array)):
        inputs += input_array[i] + " "

    cmd = "cd " + ARTEMIS_WORK + "; artemis -l '" + ARTEMIS_WORK + "/scripts/processline.C(\"mergefile " + output + " " + inputs + "\")'"

    print(cmd)
    subprocess.call([cmd], shell=True, executable="/usr/bin/zsh")
