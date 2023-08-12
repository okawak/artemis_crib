import sys
import subprocess

ARTEMIS_WORK = "/home/okawa/art_analysis/user/okawa/"

if __name__ == '__main__':
    RUNINFO = sys.argv[1]

    RUNNAME = RUNINFO[:-4]
    RUNNUM  = RUNINFO[-4:]

    cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/makerawroot.yaml " + RUNNAME + " " + RUNNUM
    print(cmd)
    subprocess.call([cmd], shell=True, executable="/usr/bin/zsh")

    #procs = []
    #cmd = "cd " + ARTEMIS_WORK + "; artemis -l '" + ARTEMIS_WORK + "macro/MakeSimpleRoot.C(\"" + RUNNAME + "\",\"" + RUNNUM + "\",1)'" 
    #print(cmd)
    #procs.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))

    #cmd = "cd " + ARTEMIS_WORK + "; artemis -l '" + ARTEMIS_WORK + "macro/MakeSimpleRoot.C(\"" + RUNNAME + "\",\"" + RUNNUM + "\",2)'" 
    #print(cmd)
    #procs.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))

    #cmd = "cd " + ARTEMIS_WORK + "; artemis -l '" + ARTEMIS_WORK + "macro/MakeSimpleRoot.C(\"" + RUNNAME + "\",\"" + RUNNUM + "\",3)'" 
    #print(cmd)
    #procs.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))

    #cmd = "cd " + ARTEMIS_WORK + "; artemis -l '" + ARTEMIS_WORK + "macro/MakeSimpleRoot.C(\"" + RUNNAME + "\",\"" + RUNNUM + "\",4)'" 
    #print(cmd)
    #procs.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))

    #cmd = "cd " + ARTEMIS_WORK + "; artemis -l '" + ARTEMIS_WORK + "macro/MakeSimpleRoot.C(\"" + RUNNAME + "\",\"" + RUNNUM + "\",5)'" 
    #print(cmd)
    #procs.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))

    #for proc in procs:
    #    proc.communicate()
