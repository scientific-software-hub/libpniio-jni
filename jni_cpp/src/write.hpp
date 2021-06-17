//
// Created by ingvord on 17.06.2021.
//
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

    auto nx_path = nexus::Path::from_string(nativeString.value);
    std::string nx_path_string = nexus::Path::to_string(nx_path);

    nexus::PathObjectList objects = nexus::get_objects(nxFile->file.root(), nx_path);
    if(objects.size() > 1) {
        std::string message{"ambiguous nxPath: "};
        message += nx_path_string;
        jclass libpniioExceptionClass = env->FindClass("hzg/wpn/nexus/libpniio/jni/LibpniioException");
        env->ThrowNew(libpniioExceptionClass, message.c_str());
    }
    auto result = objects.front();
    if(result.type() != nexus::PathObject::Type::DATASET) {
        std::string message{"nxPath object is not a dataset "};
        message += nx_path_string;
        jclass libpniioExceptionClass = env->FindClass("hzg/wpn/nexus/libpniio/jni/LibpniioException");
        env->ThrowNew(libpniioExceptionClass, message.c_str());
    }

    return result;
}

template<typename T>
void write(JNIEnv * env, jclass, jlong jLong, jstring jString, T value) {
    TRY
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
    CATCH
}

        template<typename T>
        void append(JNIEnv * env, jclass, jlong jLong, jstring jString, T value) {
            TRY
                auto dataset = get_object(env, jLong, jString);



                dataset.extent(0,1);
                auto size = dataset.dataspace().size();


                hdf5::dataspace::Hyperslab selection{{0},{1},{1},{1}};
                selection.offset(0,size - 1);
                dataset.write(value, selection);
            CATCH
        }

    }//namespace
}//namespace

#endif //LIBPNIIO_JNI_WRITE_H
