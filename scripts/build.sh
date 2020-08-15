#!/bin/sh

# Build core lib
cd ../packages/lib
cmake ../../domain 
make

# Build app bin
cd ../bin
cmake ../../application
make