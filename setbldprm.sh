#!/bin/sh

arthome=$(
   cd "$(dirname "$0")" || return 1
   pwd
)
time=$(date)

usage() {
   echo "usage: ./setbldprm.sh \$1"
   echo "usage: ex) ./setbldprm.sh physics0100"
}

if [ "$1"_ = _ ]; then
   usage "$0"
   return
fi

if [ $# -ne 1 ]; then
   usage "$0"
   return
fi

#===== MWDC parameters =====
dca_prm_dir="$arthome/prm/mwdc/mwdca/dt2dl"
cd "$dca_prm_dir" || return 1
if [ -d "$1" ]; then
   echo "mwdca_prm: $dca_prm_dir/$1 is current"
   rm -f current
   ln -sf "$1" current
else
   echo "ERROR: $dca_prm_dir/$1 not found."
   return
fi

dcb_prm_dir="$arthome/prm/mwdc/mwdcb/dt2dl"
cd "$dcb_prm_dir" || return 1
if [ -d "$1" ]; then
   echo "mwdcb_prm: $dca_prm_dir/$1 is current"
   rm -f current
   ln -sf "$1" current
else
   echo "ERROR: $dcb_prm_dir/$1 not found."
   return
fi

cd "$arthome" || return 1
echo "${time} using $1 prm" >>"$arthome/.log_mwdc"
