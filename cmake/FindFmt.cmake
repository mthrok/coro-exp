find_path(
  FMT_INCLUDE_DIR
  NAMES "fmt/format.h"
  )

find_library(
  FMT_LIBRARY
  NAMES fmt)

set(FMT_LIBRARIES ${FMT_LIBRARY})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    fmt DEFAULT_MSG FMT_INCLUDE_DIR FMT_LIBRARIES)

mark_as_advanced(FMT_INCLUDE_DIR FMT_LIBRARIES FMT_FOUND)

if(FMT_FOUND AND NOT FMT_FIND_QUIETLY)
    message(STATUS "Found fmt: ${FMT_LIBRARIES}")
endif()

add_library(fmt SHARED IMPORTED)
set_target_properties(
  fmt
  PROPERTIES
  IMPORTED_LOCATION "${FMT_LIBRARY}"
  INTERFACE_INCLUDE_DIRECTORIES "${FMT_INCLUDE_DIR}"
)
