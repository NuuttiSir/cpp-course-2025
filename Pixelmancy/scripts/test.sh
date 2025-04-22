#!/usr/bin/env bash

cd -- "$(dirname "$0")"
cd ..
cmake -S . -B build -DCMAKE_BUILD_TYPE=Asan -DPIXELMANCY_BUILD_TESTS=ON
cmake --build build -j 4
./build/tests/PixelmancyTests
