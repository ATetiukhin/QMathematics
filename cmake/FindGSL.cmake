####################################################################################################
# GSL
#
# GSL_FOUND           = system has GSL lib
# GSL_LIBRARY   = full path to the GSL library
# GSL_INCLUDE_DIR     = where to find headers 
#
####################################################################################################

SET(GSL_MSVC_PREFIX "$ENV{GSL_LIB}")

FIND_LIBRARY(GSL_LIB gsl PATHS 
${GSL_MSVC_PREFIX}/lib
)

#MSVC version of the lib is just called 'cblas'
FIND_LIBRARY(GSLCBLAS_LIB gslcblas cblas PATHS 
${GSL_MSVC_PREFIX}/lib
)

FIND_PATH(GSL_INCLUDE_DIR gsl/gsl_blas.h 
${GSL_MSVC_PREFIX}/include
)

include_directories(${GSL_INCLUDE_DIR})

IF (GSL_LIB AND GSLCBLAS_LIB)
    SET (GSL_LIBRARIES ${GSL_LIB} ${GSLCBLAS_LIB})
ENDIF (GSL_LIB AND GSLCBLAS_LIB)

IF(GSL_LIBRARIES)
  IF(GSL_INCLUDE_DIR OR GSL_CXX_FLAGS)

    SET(GSL_FOUND 1)
    
    MESSAGE(STATUS "Using GSL from ${GSL_PREFIX}")

  ENDIF(GSL_INCLUDE_DIR OR GSL_CXX_FLAGS)
ENDIF(GSL_LIBRARIES)
