#!/usr/bin/env bash

PWD=$(pwd)
export VCPKG_ROOT="${PWD}/external/vcpkg"
export PATH=$VCPKG_ROOT:$PATH

vcpkg install
