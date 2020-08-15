#!/bin/sh

# Run profiling
cd ../packages/bin
./qure
gprof ./qure > gprof.log
head gprof.log -n 100