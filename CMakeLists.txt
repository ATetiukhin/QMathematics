####################################################################################################
#
# QMathematics
#
####################################################################################################

cmake_minimum_required(VERSION 3.0.0)

# Project settings
set(PROJECT_NAME QMathematics)
project(${PROJECT_NAME})

set(VERSION_MAJOR 0)
set(VERSION_MINOR 4)
set(VERSION_PATCH 3)
set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})
message(STATUS "VERSION: " ${VERSION})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

####################################################################################################

# OS settings
if(WIN32 OR APPLE)
    set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/build/install CACHE STRING "" FORCE)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
endif(WIN32 OR APPLE)

####################################################################################################

# Qt
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt4 4.8.6 REQUIRED QtCore QtGui QtSql QtSvg QtScript)

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

find_package(Qwt REQUIRED)                              

####################################################################################################

add_subdirectory(src)
add_subdirectory(plugins)

####################################################################################################
