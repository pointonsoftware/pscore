#!/bin/sh

# Clean bins
cd $BIN_DIR
ls -Q | grep -v .gitignore | xargs rm -rf

# Clean libs
cd $LIB_DIR
ls -Q | grep -v .gitignore | xargs rm -rf

echo "Cleaned!"