cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(libuv-coro-experiments)

################################################################################
# global configs
################################################################################

set(CMAKE_CXX_STANDARD 20 CACHE STRING "The C++ standard (minimum 20)")
set(USE_LIBUV ON CACHE BOOL "Use libuv")

cmake_policy(SET CMP0135 NEW)
include(FetchContent)

# ------------------------------------------------------------------------------
if (USE_LIBUV)
  add_subdirectory(third_party/libuv)
  add_subdirectory(examples/libuv)
endif (USE_LIBUV)
