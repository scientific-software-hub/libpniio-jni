include(FindPkgConfig)

if(NOT PKG_CONFIG_FOUND)
    message(FATAL_ERROR "Could not find pkg-config!")
endif()

include(configure/libpniio.cmake)

include(configure/jni_headers.cmake)

