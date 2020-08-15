#!/bin/sh

# Run profiling
cd $TRAVIS_BUILD_DIR/build/bin
./console_app
gprof ./console_app > gprof.log
head gprof.log -n 100