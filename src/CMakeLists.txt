set(SOURCE_FILES hzg_wpn_nexus_libpniio_jni_LibpniioJni.cpp)
add_library(pniio_jni SHARED ${SOURCE_FILES} jni_helpers.hpp)
target_link_libraries(pniio_jni ${LIBPNIIO_PKG_LIBRARIES})

install(TARGETS pniio_jni DESTINATION java/src/main/resources/lib/native/x86_64-linux-gnu)