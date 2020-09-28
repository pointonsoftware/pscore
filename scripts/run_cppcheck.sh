#!/bin/sh
export SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd $SCRIPT_DIR/../

# Note: When updating the line below, update .travis.yml as well
cppcheck --std=c++11 --enable=warning,style,performance,portability,information \
 --suppress=missingIncludeSystem --error-exitcode=1 --inline-suppr \
 core orchestra mock utility -icore/domain/unittest
