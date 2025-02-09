#!/usr/bin/env bash

# Change directory to the location of the script
cd "$(dirname "$0")"

# Update/build libraries:
./libs/MGL/build.sh

# Build application
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -S . -B ./build
cd build
make