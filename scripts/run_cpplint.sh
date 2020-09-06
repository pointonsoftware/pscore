#!/bin/sh
export SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd $SCRIPT_DIR/../
cpplint --filter=-readability/multiline_comment,-whitespace/ending_newline,-build/c++11 --linelength=100 \
--recursive application databoundary domain utility