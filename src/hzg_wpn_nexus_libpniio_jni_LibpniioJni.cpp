//
// Created by ingvord on 3/31/15.
//
#include "hzg_wpn_nexus_libpniio_jni_LibpniioJni.h"

#include <pni/io/nx/nx.hpp>

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


void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_createFile(JNIEnv *env, jobject jo, jstring js) {
    NativeString nativeString(env, js);

    try {
        pni::io::nx::h5::nxfile::create_file(nativeString.value, false);
    } catch(const pni::io::exception& pniex){
        jclass libpniioExceptionClass = env->FindClass("hzg/wpn/nexus/libpniio/jni/LibpniioException");
        env->ThrowNew(libpniioExceptionClass,pniex.description().c_str());
    }
}
