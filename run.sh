#/usr/bin/env bash

if [[ ! -d ./build/ ]]; then
    echo "E: build/ missing"
    exit 1
fi

cd build
./group_gen
