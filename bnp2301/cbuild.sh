#!/bin/bash

CPUS="`lscpu | grep -e ^'CPU(s):' | cut -c22-`"

rm -fr cmake-build-debug/
cmake -DCMAKE_BUILD_TYPE=Debug -B cmake-build-debug
cmake --build "cmake-build-debug" --target all -- -j ${CPUS}

rm -fr cmake-build-release/
cmake -DCMAKE_BUILD_TYPE=Release -B cmake-build-release
cmake --build "cmake-build-release" --target all -- -j ${CPUS}
