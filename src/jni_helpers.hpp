//
// Created by khokhria on 6/9/15.
//

#ifndef LIBPNIIO_JNI_JNI_HELPERS_HPP
#define LIBPNIIO_JNI_JNI_HELPERS_HPP

#include <jni.h>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/xml.hpp>
#include <pni/core/error/exceptions.hpp>
#include <pni/io/nx/algorithms/write.hpp>
#include <pni/io/nx/algorithms/get_object.hpp>
#include <pni/io/nx/algorithms/grow.hpp>

namespace libpniio{
namespace jni {

    namespace xml_n=pni::io::nx::xml;
    typedef pni::io::nx::nxpath nxpath_t;
    typedef pni::io::nx::h5::nxfile nxfile_t;
    typedef pni::io::nx::h5::nxobject nxobject_t;
    typedef pni::core::exception exception_t;

    struct NxFile{
        nxfile_t file;
        NxFile(nxfile_t file):file(file){}
    };

    //TODO replace with ID
    struct NativeString{
        JNIEnv* env;
        jstring jString;
        const char* value;

        NativeString(JNIEnv* env, jstring jString):
                env(env),
                jString(jString),
                value(env->GetStringUTFChars(jString, 0))
        {}

        ~NativeString(){
            env->ReleaseStringUTFChars(jString, value);
        }
    };

    auto get_object(JNIEnv * env, jlong jLong, jstring jString) -> nxobject_t;

    template<typename T>
    void write(JNIEnv * env, jclass, jlong jLong, jstring jString, T value) {
        try {
            auto o = get_object(env, jLong, jString);

            pni::io::nx::write(o,value);
        } catch(const exception_t& pniex){
            jclass libpniioExceptionClass = env->FindClass("hzg/wpn/nexus/libpniio/jni/LibpniioException");
            env->ThrowNew(libpniioExceptionClass,pniex.description().c_str());
        }
    }

    template<typename T>
    void write_and_grow(JNIEnv * env, jclass clazz, jlong jLong, jstring jString, T value) {
        try {
            auto&& o = get_object(env, jLong, jString);

            pni::io::nx::write(o,value);
            pni::io::nx::grow(o);
        } catch(const exception_t& pniex){
            jclass libpniioExceptionClass = env->FindClass("hzg/wpn/nexus/libpniio/jni/LibpniioException");
            env->ThrowNew(libpniioExceptionClass,pniex.description().c_str());
        }
    }

}//namespace
}//namespace
#endif //LIBPNIIO_JNI_JNI_HELPERS_HPP
