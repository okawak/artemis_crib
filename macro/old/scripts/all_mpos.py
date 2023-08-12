
import sys
import subprocess

ARTEMIS_WORK = "/home/okawa/art_analysis/user/okawa/"

if __name__ == '__main__':
    RUNINFO = sys.argv[1]

    RUNNAME = RUNINFO[:-4]
    RUNNUM  = RUNINFO[-4:]

    cmd = "cd " + ARTEMIS_WORK + "; artemis -l 'macro/run_MUXParamMaker.C(\"" + RUNNAME + "\",\"" + RUNNUM + "\")'" 
    print(cmd)
    subprocess.call([cmd], shell=True, executable="/usr/bin/zsh")
