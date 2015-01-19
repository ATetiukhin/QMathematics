set(APP_NAME bisection)

set(PLUGIN_FILES bisection.cpp bisection.hpp)

include_directories(../)

add_library(${APP_NAME} SHARED ${PLUGIN_FILES} ../plugin_interface.hpp)
target_link_libraries(${APP_NAME} Qt4::QtCore)

if (MSVC)
    set(CMAKE_CXX_FLAGS "/EHsc /W3 /nologo /Zc:wchar_t " CACHE STRING "" FORCE)
    set(CMAKE_CXX_FLAGS_DEBUG "/D_DEBUG /MTd /Ob0 /Od /Zi /RTC1 -DQT_PLUGIN -DQT_SHARED" CACHE STRING "" FORCE)
    set(CMAKE_CXX_FLAGS_RELEASE "/MT /O2 /Ob2 /D NDEBUG -DQT_PLUGIN -DQT_SHARED -DQT_NO_DEBUG" CACHE STRING "" FORCE)

    source_group("Source Files" FILES ../plugin_interface.hpp)
    source_group("Source Files\\PLUGIN" FILES ${PLUGIN_FILES})

    set_target_properties(${APP_NAME} PROPERTIES LINK_FLAGS " /DYNAMICBASE /FIXED:NO")
endif ()
