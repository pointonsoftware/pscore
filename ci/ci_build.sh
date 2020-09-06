#!/bin/sh
# Start make build
cd $TRAVIS_BUILD_DIR
echo Starting clean build...
./clean_build.sh -DCMAKE_EXE_LINKER_FLAGS=-fuse-ld=gold

# Run unittest
cd $TRAVIS_BUILD_DIR/build/bin
./domain_unittest