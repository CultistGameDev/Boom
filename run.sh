#!/usr/bin/env bash

if cmake --build build; then
  ./build/BoomHeadshot/BoomHeadshot
fi
