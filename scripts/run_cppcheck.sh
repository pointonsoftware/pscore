#!/bin/sh
export SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd $SCRIPT_DIR/../

# Note: When updating the line below, update .travis.yml as well
cppcheck --quiet --error-exitcode=1 --enable=warning,performance,information,style --suppress=missingIncludeSystem \
--check-config application databoundary invoker utility -iinvoker/unittest
