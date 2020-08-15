#!/bin/sh

# Build core lib
cd $TRAVIS_BUILD_DIR/packages/lib
cmake -DCI_BUILD=ON ../../domain
make

# Build app bin
cd ../bin
cmake -DCI_BUILD=ON ../../application
make