#!/bin/sh
export SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd $SCRIPT_DIR/../

# Note: When updating the line below, update .travis.yml as well
cppcheck --error-exitcode=1 --enable=all --suppress=missingIncludeSystem --inline-suppr \
 application databoundary invoker utility -iinvoker/unittest
