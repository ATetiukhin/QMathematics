set(APP_NAME cdbinrnk)

set(PLUGIN_FILES cdbinrnk.cpp cdbinrnk.hpp)
set(DIEHARD_RANK
    libdieharder.hpp
    diehard_rank_6x8.cpp
    static_get_bits.cpp
    vtest.hpp
    vtest.cpp
    rank.cpp
    )

include_directories(../)

add_library(${APP_NAME} SHARED ${PLUGIN_FILES} ${DIEHARD_RANK} ../plugin_probability.hpp)
target_link_libraries(${APP_NAME} Qt4::QtCore ${GSL_LIBRARY})

if (MSVC)
    set(CMAKE_CXX_FLAGS "/EHsc /W3 /nologo /Zc:wchar_t " CACHE STRING "" FORCE)
    set(CMAKE_CXX_FLAGS_DEBUG "/D_DEBUG /MTd /Ob0 /Od /Zi /RTC1 -DQT_PLUGIN -DQT_SHARED" CACHE STRING "" FORCE)
    set(CMAKE_CXX_FLAGS_RELEASE "/MT /O2 /Ob2 /D NDEBUG -DQT_PLUGIN -DQT_SHARED -DQT_NO_DEBUG" CACHE STRING "" FORCE)

    source_group("Source Files" FILES ../plugin_probability.hpp)
    source_group("Source Files\\PLUGIN" FILES ${PLUGIN_FILES})
    source_group("Source Files\\DIEHARD_RANK" FILES ${DIEHARD_RANK})

    set_target_properties(${APP_NAME} PROPERTIES LINK_FLAGS " /DYNAMICBASE /FIXED:NO")
endif ()
