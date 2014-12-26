cmake_minimum_required(VERSION 3.0.0)

# Project settings
set(PROJECT_NAME QMathematics)
project(${PROJECT_NAME})

set(VERSION_MAJOR 0)
set(VERSION_MINOR 3)
set(VERSION_PATCH 3)
set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})
message(STATUS "VERSION: " ${VERSION})

# OS settings
if(WIN32 OR APPLE)
    set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/build/install CACHE STRING "" FORCE)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
endif(WIN32 OR APPLE)

#-------------------------------------------------------------------------------------------

# Qt
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(QT_USE_QTSQL TRUE)
set(QT_USE_QTSCRIPT TRUE)
set(QT_USE_QTPLUGIN TRUE)

find_package(Qt4 4.8.6 REQUIRED)

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

#-------------------------------------------------------------------------------------------
# Qwt

set(QWT_INCLUDE_DIR CACHE PATH "Qwt include directory")

if(NOT QWT_INCLUDE_DIR)
  message(FATAL_ERROR "QWT_INCLUDE_DIR should be set to a path like '/home/jchris/Projects/qwt-6.0.1-svn/include'")
endif()

include_directories(${QWT_INCLUDE_DIR})

# Qwt libraries
set(QWT_LIBRARY CACHE FILEPATH "Qwt library")

if(NOT QWT_LIBRARY)
  message(FATAL_ERROR "QWT_LIBRARY should be set to a filepath like '/home/jchris/Projects/qwt-6.0.1-svn/lib/libqwt.so'")
endif()

#-------------------------------------------------------------------------------------------

add_subdirectory(src)
add_subdirectory(plugins)

#-------------------------------------------------------------------------------------------

# Project settings
if (MSVC)
    add_definitions(/D_CONSOLE /D_MBCS _VARIADIC_MAX=10)
    set(CMAKE_CXX_FLAGS "/EHsc /W3 /nologo /Od /Ob0" CACHE STRING "" FORCE)
elseif (CMAKE_COMPILER_IS_GNUCXX)
    # Setting directory
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIRECTORY} CACHE STRING "" FORCE)

    # Compiler flags
    set(CMAKE_CXX_FLAGS " -std=c++11 -Wall " CACHE STRING "" FORCE)
    set(CMAKE_CXX_FLAGS_DEBUG " -g -Os " CACHE STRING "" FORCE)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}" CACHE STRING "" FORCE)

    # Linker flags
    set(CMAKE_EXE_LINKER_FLAGS " -static-libgcc -static-libstdc++ -static " CACHE STRING "" FORCE)
    set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "" CACHE STRING "" FORCE) # remove dynamic for CXX
    set(BUILD_SHARED_LIBS OFF)
endif (MSVC)

#-------------------------------------------------------------------------------------------
