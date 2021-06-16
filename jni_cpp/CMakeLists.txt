cmake_minimum_required(VERSION 3.2)
project(libpniio-jni)

set(CMAKE_PREFIX_PATH "/usr/local/lib/pkgconfig;${CMAKE_PREFIX_PATH}")

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include(configure/CMakeLists.txt)

add_subdirectory("src")
#add_subdirectory("test")