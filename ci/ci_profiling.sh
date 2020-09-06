#!/bin/sh

# Run automation
cd $TRAVIS_BUILD_DIR/build/bin
./console_app < $TRAVIS_BUILD_DIR/ci/automation_input.txt

# Run profiling
gprof ./console_app > gprof.log
head gprof.log -n 100