#!/usr/bin/env bash

cd -- "$(dirname "$0")"
cd ..

if [ "$1" == "ninja" ]; then
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DPIXELMANCY_BUILD_TESTS=OFF -G Ninja
else
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DPIXELMANCY_BUILD_TESTS=OFF
fi
cmake --build build --target PixelmancyExample -j 4
./build/standalone/PixelmancyExample -h