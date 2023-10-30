#!/bin/sh
# reference: https://sh.rustup.rs


set -u

# set variables

# main function
main() {
    need_cmd git
    need_cmd wget
    usage
}

# several function
check_old_directory() {
    echo "check"
}

usage() {
    echo "in usage function"
    echo "test"
}

# general function
say() {
    printf 'art_analysis: %s\n' "$1"
}

err() {
    say "$1" >&2
    exit 1
}

need_cmd() {
    if ! check_cmd "$1"; then
        err "need '$1' (command not found)"
    fi
}

check_cmd() {
    command -v "$1" > /dev/null 2>&1
}


# main part
main "$@" || exit 1
