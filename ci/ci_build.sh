#!/bin/sh

# Clone gtest
cd $TRAVIS_BUILD_DIR
mkdir external || exit 1
cd external || exit 1
echo Cloning gtest...
git clone git@github.com:google/googletest.git

# Start make build
cd $TRAVIS_BUILD_DIR
echo Starting clean build...
./clean_build.sh -DCMAKE_EXE_LINKER_FLAGS=-fuse-ld=gold