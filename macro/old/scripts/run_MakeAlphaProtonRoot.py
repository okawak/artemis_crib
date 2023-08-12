import subprocess

ARTEMIS_WORK = "/home/okawa/art_analysis/user/okawa/"

if __name__ == '__main__':

    procs1 = []
    cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/tel1_alpha.yaml phys 0000"
    print(cmd)
    procs1.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))

    cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/tel2_alpha.yaml phys 0000"
    print(cmd)
    procs1.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))

    cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/tel3_alpha.yaml phys 0000"
    print(cmd)
    procs1.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))

    cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/tel4_alpha.yaml phys 0000"
    print(cmd)
    procs1.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))

    cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/tel5_alpha.yaml phys 0000"
    print(cmd)
    procs1.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))

    cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/tel1_alpha.yaml bg 0000"
    print(cmd)
    procs1.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))

    cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/tel2_alpha.yaml bg 0000"
    print(cmd)
    procs1.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))

    cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/tel3_alpha.yaml bg 0000"
    print(cmd)
    procs1.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))

    cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/tel4_alpha.yaml bg 0000"
    print(cmd)
    procs1.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))

    cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/tel5_alpha.yaml bg 0000"
    print(cmd)
    procs1.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))

    for proc in procs1:
        proc.communicate()

    procs2 = []
    cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/tel1_proton.yaml phys 0000"
    print(cmd)
    procs2.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))

    cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/tel2_proton.yaml phys 0000"
    print(cmd)
    procs2.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))

    cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/tel3_proton.yaml phys 0000"
    print(cmd)
    procs2.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))

    cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/tel4_proton.yaml phys 0000"
    print(cmd)
    procs2.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))

    cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/tel5_proton.yaml phys 0000"
    print(cmd)
    procs2.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))

    cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/tel1_proton.yaml bg 0000"
    print(cmd)
    procs2.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))

    cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/tel2_proton.yaml bg 0000"
    print(cmd)
    procs2.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))

    cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/tel3_proton.yaml bg 0000"
    print(cmd)
    procs2.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))

    cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/tel4_proton.yaml bg 0000"
    print(cmd)
    procs2.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))

    cmd = "cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK + "steering/tel5_proton.yaml bg 0000"
    print(cmd)
    procs2.append(subprocess.Popen([cmd], shell=True, executable="/usr/bin/zsh"))

    for proc in procs2:
        proc.communicate()
