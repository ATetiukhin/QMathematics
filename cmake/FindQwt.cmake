####################################################################################################
# Qwt
#
# QWT_FOUND           = system has QWT lib
# QWT_LIBRARY_DEBUG   = full path to the QWT library debug
# QWT_LIBRARY_RELEASE = full path to the QWT library release
# QWT_INCLUDE_DIR     = where to find headers 
#
####################################################################################################

find_path(QWT_INCLUDE_DIR NAMES qwt.h PATHS
    "$ENV{QWT_ROOT}/include" 
    PATH_SUFFIXES qwt 
    )

include_directories(${QWT_INCLUDE_DIR})

find_library(QWT_LIBRARY_DEBUG NAMES qwtd PATHS "$ENV{QWT_ROOT}/lib")
find_library(QWT_LIBRARY_RELEASE NAMES qwt PATHS "$ENV{QWT_ROOT}/lib")

if(QWT_INCLUDE_DIR AND QWT_LIBRARY_DEBUG AND QWT_LIBRARY_RELEASE)
  set(QWT_FOUND TRUE)
endif(QWT_INCLUDE_DIR AND QWT_LIBRARY_DEBUG AND QWT_LIBRARY_RELEASE)

if(QWT_FOUND)
  if(NOT QWT_FIND_QUIETLY)
    MESSAGE(STATUS "Found Qwt: $ENV{QWT_ROOT}")
  endif(NOT QWT_FIND_QUIETLY)
else(QWT_FOUND)
  if(QWT_FIND_REQUIRED)
    message(FATAL_ERROR "Could not find Qwt")
  endif(QWT_FIND_REQUIRED)
endif(QWT_FOUND)
