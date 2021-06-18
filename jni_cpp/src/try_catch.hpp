//
// Created by ingvord on 14.06.2021.
//
#ifndef LIBPNIIO_JNI_TRY_CATCH_HPP
#define LIBPNIIO_JNI_TRY_CATCH_HPP

#include <stdexcept>


#define TRY try {
#define CATCH } catch(std::runtime_error& ex){ \
                    jclass libpniioExceptionClass = env->FindClass("hzg/wpn/nexus/libpniio/jni/LibpniioException"); \
                        env->ThrowNew(libpniioExceptionClass,ex.what()); \
              }

#endif //LIBPNIIO_JNI_TRY_CATCH_HPP
