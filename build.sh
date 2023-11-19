#!/usr/bin/env bash
set -eux

folly_install_dir="${HOME}/folly_installed/"

cmake -B .build \
      -DFOLLY_INCLUDE_DIR="${folly_install_dir}/folly/include" \
      -DFOLLY_LIBRARY="${folly_install_dir}/folly/lib/libfolly.a" \
      -DFMT_INCLUDE_DIR="${folly_install_dir}/fmt/include" \
      -DFMT_LIBRARY="${folly_install_dir}/fmt/lib/libfmt.a" \
      -DGLOG_INCLUDE_DIR="${folly_install_dir}/glog/include" \
      -DGLOG_LIBRARY="${folly_install_dir}/glog/lib/libglog.dylib"
cmake --build .build --target install --verbose

DYLD_LIBRARY_PATH="${folly_install_dir}/glog/lib/" ./bin/test_folly

#---
# note
#---
#
# folly from package managers (brew, anaconda) do not have c++20 coroutines
# one need to build folly from source.
#
# Following the build instruction works mostly, but need to enable c++20 manually like the following
#
# python3 ./build/fbcode_builder/getdeps.py --allow-system-packages build --extra-cmake-defines '{"CMAKE_CXX_STANDARD": "20", "BUILD_TESTS": "OFF"}'
