#!/bin/sh

cd $TRAVIS_BUILD_DIR
./clean_build.sh -DCMAKE_EXE_LINKER_FLAGS=-fuse-ld=gold