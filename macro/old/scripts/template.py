import sys
import subprocess
import argparse
import yaml

INSTALL_DIR = "/home/sh13/isomer/install/bin/"
ARTEMIS_WORK = "/home/sh13/art_analysis/user/okawa/"
APV009_DATA_PATH = "/mnt/data/sh13/apv/"
APV128_DATA_PATH = "/mnt/data/sh13/vega/"
APV129_DATA_PATH = "/mnt/data/sh13/vega/"
OUTPUT_DATA_PATH = "/home/sh13/art_analysis/user/isomer/rootfiles/tmpsort2/"
THIS_ISOMER_PATH = "/home/sh13/isomer/install/share/thisisomer.sh"

if __name__ == '__main__':
    runnum = sys.argv[1]
    runnumge = sys.argv[2]
    runnumsh = sys.argv[3]
    RUNNAME = sys.argv[4]

    apv128_name = APV128_DATA_PATH + "port5042_run" + runnum + ".bin"
    apv129_name = APV129_DATA_PATH + "port5041_run" + runnum + ".bin"

    sharaq_rootname = ARTEMIS_WORK + "output/merge/pid_" + RUNNAME + runnumsh +".root"
    sharaq_mvroot = OUTPUT_DATA_PATH + "pid_" + RUNNAME + runnumsh + ".root"
    apv009_rootname = ARTEMIS_WORK + "output/apv/" + runnumge + "/apvapv" + runnumge +".root"
    apv009_mvroot = OUTPUT_DATA_PATH + "apvapv" + runnumge + ".root"
    apv128_rootname = OUTPUT_DATA_PATH + "port5041_run" + runnum + ".root"
    apv128_sortname = OUTPUT_DATA_PATH + "sort5041_run" + runnum + ".root"
    apv129_rootname = OUTPUT_DATA_PATH + "port5042_run" + runnum + ".root"
    apv129_sortname = OUTPUT_DATA_PATH + "sort5042_run" + runnum + ".root"
    all_outname = OUTPUT_DATA_PATH + "pmt" + runnum + "_ge" + runnumge + "_sh" + runnumsh + ".root"


    # Decode rawdata
    procs = []
    cmd = "source " + THIS_ISOMER_PATH + "; cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK+"steering/chkdaq.yaml apv " + runnumge
    print(cmd)
    procs.append(subprocess.Popen([cmd],shell=True))

    cmd = "source " + THIS_ISOMER_PATH + "; cd " + ARTEMIS_WORK + "; " + ARTEMIS_WORK + "build/run_artemis " + ARTEMIS_WORK+"steering/merge.yaml " + RUNNAME + " " + runnumsh
    print(cmd)
    procs.append(subprocess.Popen([cmd],shell=True))

    cmd = "source " + THIS_ISOMER_PATH +"; " + INSTALL_DIR + "apv_decoder -t APV8508 -i " + apv128_name + " -o " + apv128_rootname
    print(cmd)
    procs.append(subprocess.Popen([cmd],shell=True))

    cmd = "source " + THIS_ISOMER_PATH + "; " + INSTALL_DIR + "apv_decoder -t APV8104 -i " + apv129_name + " -o " + apv129_rootname
    print(cmd)
    procs.append(subprocess.Popen([cmd],shell=True))

    for proc in procs:
        proc.communicate()


    # move the root file
    cmd = "mv " + apv009_rootname + " " + OUTPUT_DATA_PATH
    print(cmd)
    subprocess.call([cmd],shell=True)

    cmd = "mv -f " + sharaq_rootname + " " + OUTPUT_DATA_PATH
    print(cmd)
    subprocess.call([cmd],shell=True)


    # sort the PMT data
    procs = []
    cmd = "source " + THIS_ISOMER_PATH + "; cd /home/sh13/isomer/build/data; root -b '/home/sh13/isomer/scripts/pmtsort.C(\""+ apv128_rootname +"\",\"" + apv128_sortname + "\")'"
    print(cmd)
    procs.append(subprocess.Popen([cmd],shell=True))

    cmd = "source " + THIS_ISOMER_PATH + "; cd /home/sh13/isomer/build/data; root -b '/home/sh13/isomer/scripts/pmtsort.C(\""+ apv129_rootname +"\",\"" + apv129_sortname + "\")'"
    print(cmd)
    procs.append(subprocess.Popen([cmd],shell=True))

    for proc in procs:
        proc.communicate()


    # merge using saito-san's macro
    cmd = "source " + THIS_ISOMER_PATH + "; cd /home/sh13/art_analysis/user/okawa; artemis -l '/home/sh13/isomer/scripts/tmpsort2.C(\"" + apv128_sortname + "\",\"" + apv129_sortname + "\",\"" + apv009_mvroot + "\",\"" + sharaq_mvroot + "\",\"" + all_outname + "\")'"
    print(cmd)
    subprocess.call([cmd],shell=True)
