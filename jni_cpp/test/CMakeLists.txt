add_executable(main main.cpp)

include_directories(/usr/include)

target_link_libraries(main ${LIBPNIIO_PKG_LIBRARIES})