#!/bin/bash

# The main script

# Define environment variables needed by other scripts
export SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
export DOMAIN_DIR=$SCRIPT_DIR/../domain
export APP_DIR=$SCRIPT_DIR/../application
export BUILD_DIR=$SCRIPT_DIR/../build
export LIB_DIR=$BUILD_DIR/lib
export BIN_DIR=$BUILD_DIR/bin


show_help() {
    echo "Usage: $0 [-flag] "
    echo "Flags: "
    echo "   -h          Display this help message"
    echo "   -b          Build cmake, then build bins and libs"
    echo "   -c          Clean the build directory"
    echo "   -p          Being profiling"
    echo "   -a          Rebuild the console app"
    echo "   -l          Rebuild the core lib"
}

rebuild_app() {
    cd $BIN_DIR
    make
}

rebuild_lib() {
    cd $LIB_DIR
    make
}


#  Get command-line arguments
OPTS=`getopt -o bcpalh --long build,clean,profile,rbapp,rblib,help -- "$@"`
if [ $? != 0 ] ; then echo "Failed parsing options." >&2; exit 1; fi

#while getopts "ht:sl" opt; do
eval set -- "$OPTS"
while true; do
    case "$1" in
    -b | --build) cd $SCRIPT_DIR; ./build.sh; exit 0 ;;
    -c | --clean) cd $SCRIPT_DIR; ./clean.sh; exit 0 ;;
    -p | --profile) cd $SCRIPT_DIR; ./profiling.sh; exit 0 ;;
    -a | --rbapp) rebuild_app; exit 0 ;;
    -l | --rblib) rebuild_lib; exit 0 ;;
    -h | --help) show_help; exit 0 ;;
    -- ) shift; break ;;
    * ) break ;;
    esac
done