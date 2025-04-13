# Findlibpostal.cmake
# This module defines the following variables:
#   libpostal_FOUND - True if libpostal is found
#   libpostal_INCLUDE_DIRS - Include directories for libpostal
#   libpostal_LIBRARIES - Libraries to link against

find_path(libpostal_INCLUDE_DIR
  NAMES libpostal.h
  PATHS /usr/local/include
)

find_library(libpostal_LIBRARY
  NAMES postal
  PATHS /usr/local/lib
)

if(NOT libpostal_LIBRARY)
  find_library(libpostal_LIBRARY
    NAMES libpostal.a
    PATHS /usr/local/lib
  )
endif()

# Explicitly use -l:libpostal.a if the library is found
if(libpostal_LIBRARY MATCHES ".*libpostal.a$")
  set(libpostal_LIBRARIES "-l:libpostal.a")
else()
  set(libpostal_LIBRARIES ${libpostal_LIBRARY})
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(libpostal DEFAULT_MSG libpostal_INCLUDE_DIR libpostal_LIBRARY)

if(libpostal_FOUND)
  set(libpostal_INCLUDE_DIRS ${libpostal_INCLUDE_DIR})
  set(libpostal_LIBRARIES ${libpostal_LIBRARIES})
endif()

find_package(nlohmann_json REQUIRED)
