cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(libuv-coro-experiments)

################################################################################
# libuv
################################################################################
cmake_policy(SET CMP0135 NEW)
include(FetchContent)

FetchContent_Declare(
  libuv
  URL https://github.com/libuv/libuv/archive/refs/tags/v1.47.0.tar.gz
  URL_HASH SHA256=d50af7e6d72526db137e66fad812421c8a1cae09d146b0ec2bb9a22c5f23ba93
  )
if(NOT libuv_POPULATED)
  FetchContent_Populate(libuv)
  add_subdirectory(${libuv_SOURCE_DIR} ${libuv_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()


set(LIBUV_BUILD_SHARED OFF CACHE BOOL "Disable dynamic build")
set(LIBUV_BUILD_TESTS OFF CACHE BOOL "Disable test")
set(LIBUV_BUILD_BENCH OFF CACHE BOOL "Disable benchmark")
FetchContent_MakeAvailable(libuv)

################################################################################
# global configs
################################################################################

set(CMAKE_CXX_STANDARD 20 CACHE STRING "The C++ standard (minimum 20)" FORCE)

################################################################################
# examples
################################################################################

add_executable(
  libuv_fibonacci
  examples/libuv_fibonacci.c
  )
target_link_libraries(libuv_fibonacci uv_a)
list(APPEND examples libuv_fibonacci)

add_executable(
  libuv_coroutine
  examples/libuv_coroutine.cpp
  )
target_link_libraries(libuv_coroutine uv_a)
list(APPEND examples libuv_coroutine)

add_executable(
  libuv_coroutine_fibonacci
  examples/libuv_coroutine_fibonacci.cpp
  )
target_link_libraries(libuv_coroutine_fibonacci uv_a)
list(APPEND examples libuv_coroutine_fibonacci)

# message(FATAL_ERROR "${examples}")

install(
  TARGETS ${examples}
  LIBRARY DESTINATION "${CMAKE_SOURCE_DIR}/lib"
  RUNTIME DESTINATION "${CMAKE_SOURCE_DIR}/bin"
  )
