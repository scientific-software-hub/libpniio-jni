include(FindPkgConfig)

if(NOT PKG_CONFIG_FOUND)
    message(FATAL_ERROR "Could not find pkg-config!")
endif()

include(configure/libpniio.cmake)

include(configure/jni_headers.cmake)

if (NOT CMAKE_BUILD_TYPE)
	message(STATUS "No build type selected, default to RELEASE")
	set(CMAKE_BUILD_TYPE "RELEASE")
endif()
