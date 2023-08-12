#!/usr/bin/zsh

DATADIR="/home/okawa/art_analysis/user/okawa/ridf/"

for FILE in `ls $DATADIR/*.ridf`
do
  DATAFILE=${FILE##*/}
  FILENAME=${DATAFILE%.*}
  echo "in process ${FILENAME}"
  python3 /home/okawa/art_analysis/user/okawa/macro/scripts/all_mpos.py ${FILENAME}
done
