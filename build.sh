#!/bin/bash

docker run --rm -v "$(pwd):/workdir" -e CROSS_TRIPLE=x86_64-w64-mingw32  multiarch/crossbuild bash -c "mkdir -p build/windows-x64 && cd build/windows-x64 && cmake ../.. && make && mv mdrun mdrun.exe"
docker run --rm -v "$(pwd):/workdir" -e CROSS_TRIPLE=x86_64-linux-gnu    multiarch/crossbuild bash -c "mkdir -p build/linux-x64   && cd build/linux-x64   && cmake ../.. && make"
docker run --rm -v "$(pwd):/workdir" -e CROSS_TRIPLE=x86_64-apple-darwin multiarch/crossbuild bash -c "mkdir -p build/osx-x64     && cd build/osx-x64     && cmake ../.. && make"
