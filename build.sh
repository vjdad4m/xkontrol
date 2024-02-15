#!/bin/bash

mkdir -p build

cmake -S . -B build
cmake --build build

# Return to the shell on windows
if [[ "$OSTYPE" == "msys" ]]; then
  $SHELL
fi
