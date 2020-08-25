#!/bin/sh

create_dirs() {
    # Create the build directory
    if [ ! -d "$BUILD_DIR" ]; then
        mkdir $BUILD_DIR
    fi
    # Create the libraries directory
    if [ ! -d "$LIB_DIR" ]; then
        mkdir $LIB_DIR
    fi
    # Create the binaries directory
    if [ ! -d "$BIN_DIR" ]; then
        mkdir $BIN_DIR
    fi
}

start_build() {
    echo "Building core lib..."
    cd $LIB_DIR
    cmake $DOMAIN_DIR
    make

    #echo "Building app bin..."
    #cd $BIN_DIR
    #cmake $APP_DIR -DCORE_LIB_DIR=$LIB_DIR
    #make
}

# main
create_dirs
start_build

echo "Build Done!"