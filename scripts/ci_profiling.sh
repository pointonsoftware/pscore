#!/bin/sh
cd $TRAVIS_BUILD_DIR/build/bin
./console_app
# Run profiling
gprof ./console_app > gprof.log
head gprof.log -n 100