import sys
import subprocess

ARTEMIS_WORK = "/home/okawa/art_analysis/user/okawa/"

if __name__ == '__main__':
    RUNINFO = sys.argv[1]

    RUNNAME = RUNINFO[:-4]
    RUNNUM  = RUNINFO[-4:]

    # all data
    #cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/makerawroot.yaml " + RUNNAME + " " + RUNNUM
    #print(cmd)
    #subprocess.call([cmd], shell=True, executable="/usr/bin/zsh")

    # each telescope
    procs = []
    # tel1
    if int(RUNNUM) < 249:
        cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/Coin_tel1.yaml " + RUNNAME + " " + RUNNUM
    else:
        cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/Coin2_tel1.yaml " + RUNNAME + " " + RUNNUM

    print(cmd)
    #procs.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))
    subprocess.call([cmd], shell=True, executable="/usr/bin/zsh")


    # tel2
    if int(RUNNUM) < 249:
        cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/Coin_tel2.yaml " + RUNNAME + " " + RUNNUM
    else:
        cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/Coin2_tel2.yaml " + RUNNAME + " " + RUNNUM

    print(cmd)
    #procs.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))
    subprocess.call([cmd], shell=True, executable="/usr/bin/zsh")


    # tel3
    if int(RUNNUM) < 249:
        cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/Coin_tel3.yaml " + RUNNAME + " " + RUNNUM
    else:
        cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/Coin2_tel3.yaml " + RUNNAME + " " + RUNNUM

    print(cmd)
    #procs.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))
    subprocess.call([cmd], shell=True, executable="/usr/bin/zsh")


    # tel4
    if int(RUNNUM) < 249:
        cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/Coin_tel4.yaml " + RUNNAME + " " + RUNNUM
    else:
        cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/Coin2_tel4.yaml " + RUNNAME + " " + RUNNUM

    print(cmd)
    #procs.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))
    subprocess.call([cmd], shell=True, executable="/usr/bin/zsh")


    # tel5
    if int(RUNNUM) < 249:
        cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/Coin_tel5.yaml " + RUNNAME + " " + RUNNUM
    else:
        cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/Coin2_tel5.yaml " + RUNNAME + " " + RUNNUM

    print(cmd)
    #procs.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))
    subprocess.call([cmd], shell=True, executable="/usr/bin/zsh")



    #for proc in procs:
    #    proc.communicate()
