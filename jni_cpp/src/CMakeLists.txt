set(SOURCE_FILES hzg_wpn_nexus_libpniio_jni_LibpniioJni.cpp)
set(HEADER_FILES
        native_string.hpp
        nx_file.hpp
        write.hpp)
add_library(pniio_jni SHARED ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(pniio_jni ${LIBPNIIO_PKG_LIBRARIES})

install(TARGETS pniio_jni DESTINATION ../src/main/resources/lib/native/x86_64-linux-gnu)