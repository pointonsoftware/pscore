#!/bin/sh
export SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd $SCRIPT_DIR/../
cppcheck --quiet --error-exitcode=1 --enable=warning,performance,information,style \
--suppress=missingIncludeSystem --check-config \
application databoundary domain utility -idomain/unittest 