#!/bin/sh

set -u

if [ -z "$1" ]; then
    username=${EXP_NAME}
else
    username=$1
fi
    
userdir=${ART_ANALYSIS_DIR}/${EXP_NAME}/${username}
    
if [ ! -d ${ART_ANALYSIS_DIR}/${EXP_NAME} ] ; then
    printf "please make new ${EXP_NAME} work directory by the \"artnew\" command\n"
    return 1
fi


if [ -d ${userdir} ] ; then
    cd ${userdir}
    export ART_USER_FULLNAME="`git config user.name`"
    export ART_USER_EMAIL="`git config user.email`"
    export ARTEMIS_WORKDIR=${userdir}
    export ARTEMIS_USER=${username}
    alias acd='cd ${ARTEMIS_WORKDIR}'

    if [ -e ${ARTEMIS_WORKDIR}/thisartemis-crib.sh ] ; then
      source ${ARTEMIS_WORKDIR}/thisartemis-crib.sh
    fi

    return 0
elif [ -e ${userdir} ] ; then
    printf "\33[1martlogin\33[0m: strange file ${userdir} exist.\n"
    return 1
fi

printf "\33[1martlogin\33[0m: user '$username' not found.\n"
while true; do
    read -p "create new user? (y/n): " _answer
    case ${_answer} in
        y)
            break
            ;;
        n)
            echo "cancelled."
            return 0
            ;;
    esac
done

export ARTEMIS_WORKDIR=${userdir}
export ARTEMIS_USER=${username}
git clone ${ART_USER_REPOS} ${userdir}

cd ${userdir}
alias acd='cd ${ARTEMIS_WORKDIR}'

printf "\33[1martlogin\33[0m: making local git config\n"
while true; do
    read -p "Input fullname: " _fullname
    read -p "Is it Okay? (y/n): " _answer
    case ${_answer} in
        y)
            break
            ;;
    esac
done

git config user.name "${_fullname}"

while true; do
    read -p "Input email address: " _email
    read -p "Is it Okay? (y/n): " _answer
    case ${_answer} in
        y)
            break
            ;;
    esac
done

git config user.email "${_email}"


if [ -d ${ART_DATA_DIR} ]; then
    ln -fs ${ART_DATA_DIR} ${ARTEMIS_WORKDIR}/ridf
else
    printf "\33[1martlogin\33[0m: ${ART_DATA_DIR} is not existed.\n"
fi

if [ ! -d ${OUTPUT_PATH}/${username}/output ] ; then
    mkdir -p ${OUTPUT_PATH}/${username}/output
fi

if [ ! -d ${OUTPUT_PATH}/${username}/rootfile ] ; then
    mkdir -p ${OUTPUT_PATH}/${username}/rootfile
fi

ln -fs ${OUTPUT_PATH}/${username}/output ${ARTEMIS_WORKDIR}/output
ln -fs ${OUTPUT_PATH}/${username}/rootfile ${ARTEMIS_WORKDIR}/rootfile
