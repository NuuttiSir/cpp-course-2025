#!/usr/bin/env bash

cd -- "$(dirname "$0")"
cd ..
cmake -S . -B build -DPIXELMANCY_ENABLE_FORMATTERS=ON
cmake --build build --target format
cmake --build build --target fix-format
