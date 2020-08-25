#!/bin/sh

for i in "$@"
do
  CORE_CMAKE_FLAGS="$i $CORE_CMAKE_FLAGS"
done

cd "$(dirname $0)" || exit 1
CORE_CMAKE_FLAGS="-DBUILD_UNITTEST=OFF -DBUILD_ALL=ON $CORE_CMAKE_FLAGS"

echo $CORE_CMAKE_FLAGS

rm -rf build
mkdir build || exit 1
cd build || exit 1

echo Starting clean build...

cmake $CORE_CMAKE_FLAGS .. || exit 1
make || exit 1

echo "Build completed successfully"