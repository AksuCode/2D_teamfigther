#!/usr/bin/env bash

# Change directory to the location of the script
cd "$(dirname "$0")"

DIRECTORY="build_wasm"
if [ -d "$DIRECTORY" ]; then
  rm -rf "$DIRECTORY"
fi
mkdir "$DIRECTORY"
cd "$DIRECTORY"
### The static library needs to be created using emar to make it compatible with emcc
emcc -I ../libs/MGL/include -c ../libs/MGL/src/*.cpp
emar rcs libMGL.a ./*.o
###
emcc $(find src -name "*.cpp" ! -name "main.cpp") -I ../src -L . -lMGL -I ../libs -s USE_SDL=2 -o index.html