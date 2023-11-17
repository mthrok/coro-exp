#!/usr/bin/env bash
set -eux

# clang++ foo.cpp -std=c++20
# ./a.out

# PREFIX="$(brew --prefix)"
PREFIX="${CONDA_PREFIX}"

# libuv_options=("-I${PREFIX}/include" "-L${PREFIX}/lib" -luv)
libuv_options=("-I${PREFIX}/include" "${PREFIX}/lib/libuv.a")  # static

mkdir -p bin

clang examples/libuv_fibonacci.c -o bin/libuv_fibonacci "${libuv_options[@]}"
./bin/libuv_fibonacci

clang++ examples/libuv_coroutine.cpp -o bin/libuv_coroutine "${libuv_options[@]}" -std=c++20
./bin/libuv_coroutine

clang++ examples/libuv_coroutine_fibonacci.cpp -o bin/libuv_coroutine_fibonacci "${libuv_options[@]}" -std=c++20
./bin/libuv_coroutine_fibonacci
