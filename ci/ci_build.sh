#!/bin/sh
# Start make build
echo Starting clean build...
./clean_build.sh -DCMAKE_EXE_LINKER_FLAGS=-fuse-ld=gold