#!/bin/bash

docker run --rm -v "$(pwd):/workdir" -e CROSS_TRIPLE=x86_64-w64-mingw32  multiarch/crossbuild bash -c "mkdir -p build/win && cd build/win && cmake ../.. && make"
docker run --rm -v "$(pwd):/workdir" -e CROSS_TRIPLE=x86_64-linux-gnu    multiarch/crossbuild bash -c "mkdir -p build/unx && cd build/unx && cmake ../.. && make"
docker run --rm -v "$(pwd):/workdir" -e CROSS_TRIPLE=x86_64-apple-darwin multiarch/crossbuild bash -c "mkdir -p build/osx && cd build/osx && cmake ../.. && make"
