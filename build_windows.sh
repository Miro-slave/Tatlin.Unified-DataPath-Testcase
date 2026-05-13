#!/bin/bash
conan profile detect --force
conan install . --output-folder=build --build=missing
cd build
cmake .. -G "Visual Studio 15 2017" -DCMAKE_TOOLCHAIN_FILE="conan_toolchain.cmake"
cmake --build . --config Release