cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(
  coro-experiments
  LANGUAGES C CXX
  )

################################################################################
# global configs
################################################################################

set(CMAKE_CXX_STANDARD 20 CACHE STRING "The C++ standard (minimum 20)")
set(USE_LIBUV ON CACHE BOOL "Use libuv")
set(USE_FOLLY ON CACHE BOOL "Use folly")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

cmake_policy(SET CMP0135 NEW)
include(FetchContent)

# ------------------------------------------------------------------------------
set(examples)

if (USE_LIBUV)
  add_subdirectory(third_party/libuv)
  add_subdirectory(examples/libuv)
endif (USE_LIBUV)

if (USE_FOLLY)
  find_package(folly REQUIRED)
  add_subdirectory(examples/folly)
endif(USE_FOLLY)

# ------------------------------------------------------------------------------

install(
  TARGETS ${examples}
  LIBRARY DESTINATION "${CMAKE_SOURCE_DIR}/lib"
  RUNTIME DESTINATION "${CMAKE_SOURCE_DIR}/bin"
  )
