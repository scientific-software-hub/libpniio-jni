set(SOURCE_FILES main.cpp org_bitbucket_ingvord_pnijni_LibpniioJni.cpp)
add_library(pniio_jni SHARED ${SOURCE_FILES})
target_link_libraries(pniio_jni ${LIBPNIIO_PKG_LIBRARIES})