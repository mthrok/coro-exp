#!/usr/bin/env bash
set -eux

cmake -B .build
cmake --build .build --target install
