#!/usr/bin/env bash

cd -- "$(dirname "$0")"
cd ..

# Build PixelmancyExample
if [ "$1" == "ninja" ]; then
    # Build with Ninja
    cmake -S . -G Ninja -B build -DCMAKE_BUILD_TYPE=Release -DPIXELMANCY_ENABLE_PRE_BUILD_LIBS=ON
    pushd build
    ninja PixelmancyExample
    popd
else
    # Build without Ninja
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DPIXELMANCY_ENABLE_PRE_BUILD_LIBS=ON
    cmake --build build --target PixelmancyExample -j 8
fi

./build/standalone/PixelmancyExample
