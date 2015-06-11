cmake_minimum_required(VERSION 2.8)
project(libpniio_jni)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include(configure/CMakeLists.txt)

add_subdirectory("src")
add_subdirectory("test")