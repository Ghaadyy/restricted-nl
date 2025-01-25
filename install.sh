#!/usr/bin/env bash

if [ ! -d "build" ]; then
  mkdir build
fi

cd build
cmake .. -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release

cp restricted_nl /usr/local/bin/rnlc