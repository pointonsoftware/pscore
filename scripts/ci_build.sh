#!/bin/sh

DOMAIN_DIR=$TRAVIS_BUILD_DIR/domain
APP_DIR=$TRAVIS_BUILD_DIR/application

BUILD_DIR=$TRAVIS_BUILD_DIR/build
LIB_DIR=$BUILD_DIR/lib
BIN_DIR=$BUILD_DIR/bin

# Build core lib
cd $LIB_DIR
cmake -DCI_BUILD=ON $DOMAIN_DIR
make

# Build app bin
#cd $BIN_DIR
#cmake -DCI_BUILD=ON -DCORE_LIB_DIR=$LIB_DIR $APP_DIR
#make