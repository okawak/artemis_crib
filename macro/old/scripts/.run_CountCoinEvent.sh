#!/usr/bin/zsh

DATADIR="/home/okawa/art_analysis/user/okawa/ridf/"
MAX_CONCURRENT_JOBS=10

running_jobs_count() {
  ps | grep artemis | wc -l
}


for FILE in `ls $DATADIR/high*.ridf`
do
  while (( $(running_jobs_count) >= MAX_CONCURRENT_JOBS )); do
    sleep 1
  done

  DATAFILE=${FILE##*/}
  FILENAME=${DATAFILE%.*}

  if [ ${FILENAME} = "high0208" ]; then
    continue
  fi
  if [ ${FILENAME} = "high0214" ]; then
    continue
  fi
  if [ ${FILENAME} = "high0215" ]; then
    continue
  fi
  if [ ${FILENAME} = "high0216" ]; then
    continue
  fi
  if [ ${FILENAME} = "high0217" ]; then
    continue
  fi
  if [ ${FILENAME} = "high0218" ]; then
    continue
  fi

  echo "in process ${FILENAME}"
  python3 /home/okawa/art_analysis/user/okawa/macro/scripts/run_CountCoinEvent.py ${FILENAME} &
done
wait


for FILE in `ls $DATADIR/secondary024*.ridf`
do
  while (( $(running_jobs_count) >= MAX_CONCURRENT_JOBS )); do
    sleep 1
  done

  DATAFILE=${FILE##*/}
  FILENAME=${DATAFILE%.*}
  echo "in process ${FILENAME}"
  python3 /home/okawa/art_analysis/user/okawa/macro/scripts/run_CountCoinEvent.py ${FILENAME} &
done
wait


for FILE in `ls $DATADIR/bg*.ridf`
do
  while (( $(running_jobs_count) >= MAX_CONCURRENT_JOBS )); do
    sleep 1
  done

  DATAFILE=${FILE##*/}
  FILENAME=${DATAFILE%.*}
  echo "in process ${FILENAME}"
  python3 /home/okawa/art_analysis/user/okawa/macro/scripts/run_CountCoinEvent.py ${FILENAME} &
done
wait
