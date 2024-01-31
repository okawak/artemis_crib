#!/bin/bash

#===== USER SETTING ======================================
# need this format!
mwdcs=(
   "mwdca"
   "mwdcb"
)
#=========================================================

arthome=$(
   cd "$(dirname "$0")" || exit 1
   pwd
)
time=$(date)

usage() {
   echo "before use this shellscript, please check the MWDC conf in this file!"
   echo "USAGE:     $ ./setbldprm.sh \$1"
   echo "USAGE: ex) $ ./setbldprm.sh physics0100"
   echo "USAGE: if you want to clean the exist files"
   echo "USAGE:     $ ./setbldprm.sh -c"
}

prm_clean() {
   while true; do
      read -rp "WARNING: all the BLD parameter files will be cleaned, is it okay? (y/n): " _answer
      case ${_answer} in
      y)
         say "clean the parameter files..."

         for mwdc in "${mwdcs[@]}"; do
            mwdc_prm_dir="$arthome/prm/mwdc/$mwdc/dt2dl"
            link_file=$(readlink -f "$mwdc_prm_dir/current")
            for file in "$mwdc_prm_dir"/*; do
               if [ "$file" = "$link_file" ] || [ "$file" = "$mwdc_prm_dir/current" ]; then
                  continue
               fi
               say "rm $file"
               rm -rf "$file"
            done
         done

         break
         ;;
      n)
         say "cancelled"
         break
         ;;
      esac
   done
}

say() {
   printf "\33[1msetmuxprm.sh\33[0m: %s\n" "$1"
}

err() {
   say "$1" >&2
   usage
   exit 1
}

while getopts ":c" OPT; do
   case $OPT in
   c)
      prm_clean
      exit 0
      ;;
   \?)
      err "invalid option!"
      ;;
   esac
done

if [ "$1"_ = _ ]; then
   err "need correct argument"
fi

if [ $# -ne 1 ]; then
   err "need correct argument"
fi

for mwdc in "${mwdcs[@]}"; do
   mwdc_prm_dir="$arthome/prm/mwdc/$mwdc/dt2dl"
   cd "$mwdc_prm_dir" || exit 1
   if [ -d "$1" ]; then
      say "$mwdc pamameter: $mwdc_prm_dir/$1 is current"
      rm -f current
      ln -sf "$1" current
   else
      err "$mwdc_prm_dir/$1 not found."
   fi
done

cd "$arthome" || exit 1
echo "${time} using $1 prm" >>"$arthome/.log_mwdc"
