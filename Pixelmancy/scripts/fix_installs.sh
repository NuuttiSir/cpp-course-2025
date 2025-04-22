#!/usr/bin/env bash

cd -- "$(dirname "$0")"
cd ..
rm -rf libs/pre-built-backup
mv libs/pre-built libs/pre-built-backup

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DPIXELMANCY_ENABLE_PRE_BUILD_LIBS=ON
cmake --build build/libs
cmake --install build/libs