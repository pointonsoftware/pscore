#!/bin/sh

# Run profiling
cd $TRAVIS_BUILD_DIR/packages/bin
./qure
gprof ./qure > gprof.log
head gprof.log -n 100