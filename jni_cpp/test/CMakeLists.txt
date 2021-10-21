add_executable(main main.cpp)
target_link_libraries(main ${LIBPNIIO_PKG_LIBRARIES})

add_executable(nx_file nx_file.cpp)
target_link_libraries(nx_file pniio_jni ${LIBPNIIO_PKG_LIBRARIES})