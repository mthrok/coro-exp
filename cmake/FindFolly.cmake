# note:
# runtime dependencies of folly are
# boost, double-conversion, fmt, gflags and glog

find_package(Boost REQUIRED COMPONENTS context)
find_package(fmt REQUIRED)
find_package(glog REQUIRED)
find_package(gflags REQUIRED)

find_path(
  FOLLY_INCLUDE_DIR
  NAMES "folly/experimental/coro/Task.h"
  )

find_library(
  FOLLY_LIBRARY
  NAMES folly
  )

set(FOLLY_LIBRARIES ${FOLLY_LIBRARY})  #  ${DOUBLE_CONVERSION_LIBRARY})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  folly DEFAULT_MSG FOLLY_INCLUDE_DIR FOLLY_LIBRARIES)

mark_as_advanced(FOLLY_INCLUDE_DIR FOLLY_LIBRARIES FOLLY_FOUND)

if(FOLLY_FOUND AND NOT FOLLY_FIND_QUIETLY)
  message(STATUS "Found folly: ${FOLLY_LIBRARIES}")
endif()

add_library(folly SHARED IMPORTED)
target_link_libraries(folly INTERFACE double-conversion fmt glog gflags c++abi event Boost::context)
set_target_properties(
  folly
  PROPERTIES
  IMPORTED_LOCATION "${FOLLY_LIBRARY}"
  INTERFACE_INCLUDE_DIRECTORIES "${FOLLY_INCLUDE_DIR}"
)
