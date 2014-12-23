set(APP_NAME bisection)

set(PLUGIN_DICHOTOMY_FILES bisection.cpp bisection.hpp)

include_directories(../)

#find_package(Qt5Core REQUIRED)

add_definitions(-DQT_PLUGIN)
add_definitions(-DQT_SHARED)

if (MSVC)
    source_group("Source Files" FILES ../plugin_interface.hpp)
    source_group("Source Files\\PLUGIN" FILES ${PLUGIN_DICHOTOMY_FILES})
endif (MSVC)

add_library(${APP_NAME} SHARED ${PLUGIN_DICHOTOMY_FILES} ../plugin_interface.hpp)
target_link_libraries(${APP_NAME} ${QT_LIBRARIES} ${QT_QTMAIN_LIBRARY})
#target_link_libraries(${APP_NAME} Qt5::Core)

if (MSVC)
    set_target_properties(${APP_NAME} PROPERTIES LINK_FLAGS " /DYNAMICBASE /FIXED:NO")
endif (MSVC)
