set(SOURCE_FILES main.cpp hzg_wpn_nexus_libpniio_jni_LibpniioJni.cpp)
add_library(pniio_jni SHARED ${SOURCE_FILES} )
target_link_libraries(pniio_jni ${LIBPNIIO_PKG_LIBRARIES})