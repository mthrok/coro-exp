find_path(
  GLOG_INCLUDE_DIR
  NAMES "glog/logging.h"
  )

find_library(
  GLOG_LIBRARY
  NAMES glog)

set(GLOG_LIBRARIES ${GLOG_LIBRARY})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    glog DEFAULT_MSG GLOG_INCLUDE_DIR GLOG_LIBRARIES)

mark_as_advanced(GLOG_INCLUDE_DIR GLOG_LIBRARIES GLOG_FOUND)

if(GLOG_FOUND AND NOT GLOG_FIND_QUIETLY)
    message(STATUS "Found glog: ${GLOG_LIBRARIES}")
endif()

add_library(glog SHARED IMPORTED)
set_target_properties(
  glog
  PROPERTIES
  IMPORTED_LOCATION "${GLOG_LIBRARY}"
  INTERFACE_INCLUDE_DIRECTORIES "${GLOG_INCLUDE_DIR}"
)
