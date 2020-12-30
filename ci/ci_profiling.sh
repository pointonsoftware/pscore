#!/bin/sh

# Run automation
./build/bin/console_app < ci/automation_input.txt

# Run profiling
gprof ./build/bin/console_app > gprof.log
cat gprof.log