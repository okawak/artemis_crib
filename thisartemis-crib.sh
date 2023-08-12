source /home/okawa/repos/SRIMlib/install/../thisSRIMlib.sh

if [ -e $ARTEMIS_WORKDIR/.venv/bin/activate ] ; then
  source $ARTEMIS_WORKDIR/.venv/bin/activate
fi

export PATH=/home/okawa/art_analysis/si26a/okawa/build/install/bin:$PATH
export LD_LIBRARY_PATH=/home/okawa/art_analysis/si26a/okawa/build/install/lib:$LD_LIBRARY_PATH
