#!/bin/bash

#cmake -B build
cmake --build build || exit $?

for file in tests/*; do
    echo "RUNNER: $file"
    ./build/LW2-arrays "$file"
    echo "RUNNER DONE: $?"
    echo
    echo
done
