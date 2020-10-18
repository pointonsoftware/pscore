#!/bin/sh

# Reference: http://stackoverflow.com/questions/4822471/count-number-of-lines-in-a-git-repository
git ls-files | grep -P ".*(hpp|cpp|sh|txt)" | grep -v ".pdf" | xargs wc -l
exit 0
