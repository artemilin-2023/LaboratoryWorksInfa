#!/bin/bash

#cmake -B build
cmake --build build || exit $?

for file in tests/*; do
    echo "RUNNER: $file"
    ./build/LW1.exe "$file"
    echo "RUNNER DONE: $?"
    echo
    echo
done
