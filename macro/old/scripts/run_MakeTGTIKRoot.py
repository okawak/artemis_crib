import subprocess

ARTEMIS_WORK = "/home/okawa/art_analysis/user/okawa/"

if __name__ == '__main__':
    
    procs = []
    cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/TGTIK_alpha.yaml phys 0000"
    print(cmd)
    procs.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))

    cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/TGTIK_alpha.yaml bg 0000"
    print(cmd)
    procs.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))

    cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/TGTIK_proton.yaml phys 0000"
    print(cmd)
    procs.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))

    cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/TGTIK_proton.yaml bg 0000"
    print(cmd)
    procs.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))

    for proc in procs:
        proc.communicate()
