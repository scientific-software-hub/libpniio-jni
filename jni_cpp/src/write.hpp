//
// Created by ingvord on 17.06.2021.
//
#include <string>
#include <pni/io/nexus.hpp>
#include <h5cpp/hdf5.hpp>

#include "native_string.hpp"
#include "nx_file.hpp"

#ifndef LIBPNIIO_JNI_WRITE_H
#define LIBPNIIO_JNI_WRITE_H

namespace libpniio{
    namespace jni {

auto get_object(JNIEnv *env, jlong jLong, jstring jString) -> hdf5::node::Dataset {
    using namespace pni::io;
    NativeString nativeString(env, jString);

    NxFile *nxFile = reinterpret_cast<NxFile *>(jLong);

    auto result = nxFile->get_dataset({nativeString.value});
    return result;
}

template<typename T>
void write(JNIEnv * env, jclass, jlong jLong, jstring jString, T value) {
    try {
    auto dataset = get_object(env, jLong, jString);


    auto size = dataset.dataspace().size();
    if(size == 0){
        dataset.extent(0,1);
    } else if(size != 1){
        std::string message{"trying to write into non-Scalar node. Use append instead "};
        jclass libpniioExceptionClass = env->FindClass("hzg/wpn/nexus/libpniio/jni/LibpniioException");
        env->ThrowNew(libpniioExceptionClass, message.c_str());
    }

    dataset.write(value);
    } catch (const std::runtime_error& ex){
        jclass libpniioExceptionClass = env->FindClass("hzg/wpn/nexus/libpniio/jni/LibpniioException");
        env->ThrowNew(libpniioExceptionClass,ex.what());
    }
}

        template<typename T>
        void append(JNIEnv * env, jclass, jlong jLong, jstring jString, T value) {
            try {
                auto dataset = get_object(env, jLong, jString);



                dataset.extent(0,1);
                auto size = dataset.dataspace().size();


                hdf5::dataspace::Hyperslab selection{{0},{1},{1},{1}};
                selection.offset(0,size - 1);
                dataset.write(value, selection);
            } catch (const std::runtime_error& ex){
                jclass libpniioExceptionClass = env->FindClass("hzg/wpn/nexus/libpniio/jni/LibpniioException");
                env->ThrowNew(libpniioExceptionClass,ex.what());
            }
        }

    }//namespace
}//namespace

#endif //LIBPNIIO_JNI_WRITE_H
