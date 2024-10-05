#!/usr/bin/env bash

if cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=1; then
  if cmake --build build; then
    ./build/Boom/Boom
  fi
fi
