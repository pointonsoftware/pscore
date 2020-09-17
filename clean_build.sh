#!/bin/sh

for i in "$@"
do
  CORE_CMAKE_FLAGS="$i $CORE_CMAKE_FLAGS";
done

cd "$(dirname $0)" || exit 1
CORE_CMAKE_FLAGS="-DBUILD_UNITTEST=ON -DBUILD_ALL=ON $CORE_CMAKE_FLAGS"

rm -rf build
mkdir build || exit 1
cd build || exit 1

echo Starting clean build...
echo "cmake flags: " $CORE_CMAKE_FLAGS

cmake -G "Unix Makefiles" $CORE_CMAKE_FLAGS .. || exit 1
make || exit 1

echo "Build completed successfully"

# Copy the configs
cp ../config/* bin/ || exit 1
echo "Config files copied to bin folder."