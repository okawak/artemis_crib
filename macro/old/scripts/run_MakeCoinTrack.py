import sys
import subprocess

ARTEMIS_WORK = "/home/okawa/art_analysis/user/okawa/"

if __name__ == '__main__':

    cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/TrackBeamCoin.yaml phys 0000"

    print(cmd)
    subprocess.call([cmd], shell=True, executable="/usr/bin/zsh")

    cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/TrackBeamCoin.yaml bg 0000"

    print(cmd)
    subprocess.call([cmd], shell=True, executable="/usr/bin/zsh")
