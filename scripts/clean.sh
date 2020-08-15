#!/bin/sh

# Clean bins
cd ../packages/bin
ls -Q | grep -v .gitignore | xargs rm -rf

# Clean libs
cd ../lib
ls -Q | grep -v .gitignore | xargs rm -rf

echo "Cleaned!"