#!/bin/sh
export SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd "$SCRIPT_DIR"/../

# Note: When updating the line below, update .travis.yml as well
cpplint --filter=-readability/multiline_comment,-whitespace/ending_newline,-build/c++11,-build/include_subdir \
 --linelength=100 --recursive core orchestra mock utility
