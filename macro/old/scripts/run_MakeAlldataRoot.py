import sys
import subprocess

ARTEMIS_WORK = "/home/okawa/art_analysis/user/okawa/"

if __name__ == '__main__':
    RUNINFO = sys.argv[1]

    RUNNAME = RUNINFO[:-4]
    RUNNUM  = RUNINFO[-4:]

    # all data
    cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/makerawroot.yaml " + RUNNAME + " " + RUNNUM
    print(cmd)
    subprocess.call([cmd], shell=True, executable="/usr/bin/zsh")

