#! /usr/bin/bash

a="$(ls)"
b="$(ls ../group_generator/)"

if [[ $a != $b ]]; then
    echo "E: not in project root dir"
    exit 1
fi

if [[ ! -d ./build/ ]]; then
    mkdir build/
fi

cd build/
cmake .. && make
