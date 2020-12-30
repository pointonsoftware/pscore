#!/bin/sh

# Run profiling
cd "$BIN_DIR"
./console_app
gprof ./console_app > gprof.log
head gprof.log -n 100

echo "Profiling finished!"