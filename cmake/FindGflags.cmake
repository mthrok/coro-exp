find_path(
  GFLAGS_INCLUDE_DIR
  NAMES "gflags/gflags.h"
  )

find_library(
  GFLAGS_LIBRARY
  NAMES gflags)

set(GFLAGS_LIBRARIES ${GFLAGS_LIBRARY})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    gflags DEFAULT_MSG GFLAGS_INCLUDE_DIR GFLAGS_LIBRARIES)

mark_as_advanced(GFLAGS_INCLUDE_DIR GFLAGS_LIBRARIES GFLAGS_FOUND)

if(GFLAGS_FOUND AND NOT GFLAGS_FIND_QUIETLY)
    message(STATUS "Found gflags: ${GFLAGS_LIBRARIES}")
endif()

add_library(gflags SHARED IMPORTED)
set_target_properties(
  gflags
  PROPERTIES
  IMPORTED_LOCATION "${GFLAGS_LIBRARY}"
  INTERFACE_INCLUDE_DIRECTORIES "${GFLAGS_INCLUDE_DIR}"
)
