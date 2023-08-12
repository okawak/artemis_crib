import sys
import subprocess
import argparse
import re
import numpy as np

#ATIMA_WORK = "/home/crib/art_analysis/user/okawa2/"
ATIMA_WORK = "/home/okawa/software/atima_1.41/"
#PRM_DIR = "/home/crib/art_analysis/user/okawa2/"
PRM_DIR = "/home/okawa/art_analysis/user/okawa/prm/eloss/si26_he4.dat"

# usage : ./atimawww (projectile)Zp Ap[amu] E[MeV/u] (target)Zt At[g/mol] t[mg/cm^2]

# 62 energy remain
if __name__ == '__main__':

    data_file = open(PRM_DIR,"wt")
    data_file.write("# inputEnergy(MeV/u) EnergyLoss(MeV/u)\n")
    # for beam (si26)
    Zp = 14
    Ap = 25.992333846
    #E = 1000.
    Zt = 2
    At = 4.0
    t = 0.00054743 #0.1mm

    for iE in np.arange(0.0, 5.0, 0.001):
        cmd = "cd " + ATIMA_WORK + "; " + ATIMA_WORK + "atimawww " + str(Zp) + " " + str(Ap) + " " + str(iE) + " " + str(Zt) + " " + str(At) + " " + str(t)
        #print(cmd)
        proc = subprocess.Popen(cmd, shell=True, executable="/usr/bin/zsh", stdout=subprocess.PIPE)
        info = proc.communicate()[0].decode("utf-8")
        info = re.split(': ', info)
        info_remain = re.split(' ', info[5])
        print("input Energy : " + str(round(iE,10)) + " MeV/u")
        print("remain Energy: " + info_remain[0] + " MeV/u")
        print("Energy loss  : " + str(round(iE,10) - round(float(info_remain[0]),10)) + " MeV/u")
        print()
        data_file.write("{:.6f}".format(iE) + " " + "{:.6f}".format(iE - float(info_remain[0])) + "\n")


    data_file.close()
