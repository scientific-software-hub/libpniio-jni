//
// Created by ingvord on 3/31/15.
//
#include "hzg_wpn_nexus_libpniio_jni_LibpniioJni.h"

#include <iostream>
#include <pni/io/nx/nx.hpp>


struct NxFile {
    pni::io::nx::h5::nxfile file;
    NxFile(pni::io::nx::h5::nxfile file):file(file){}
};

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


jlong Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_createFile(JNIEnv *env, jclass jClass, jstring jString) {

    NativeString nativeString(env, jString);

    try {
        auto file = pni::io::nx::h5::nxfile::create_file(nativeString.value, false);
        auto* rv = new NxFile(file);
        return reinterpret_cast<jlong>(rv);
    } catch(const pni::io::exception& pniex){
        jclass libpniioExceptionClass = env->FindClass("hzg/wpn/nexus/libpniio/jni/LibpniioException");
        env->ThrowNew(libpniioExceptionClass,pniex.description().c_str());
    }
}

jlong Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_openFile(JNIEnv *env, jclass jClass, jstring jString) {
    NativeString nativeString(env, jString);

    try {
        auto file = pni::io::nx::h5::nxfile::open_file(nativeString.value, false);
        auto* rv = new NxFile(file);
        return reinterpret_cast<jlong>(rv);
    } catch(const pni::io::exception& pniex){
        jclass libpniioExceptionClass = env->FindClass("hzg/wpn/nexus/libpniio/jni/LibpniioException");
        env->ThrowNew(libpniioExceptionClass,pniex.description().c_str());
    }
}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_closeFile(JNIEnv *env, jclass jClass, jlong jLong) {
    try {
        NxFile* nxFile = reinterpret_cast<NxFile*>(jLong);
        nxFile->file.close();
        delete nxFile;
    } catch(const pni::io::exception& pniex){
        jclass libpniioExceptionClass = env->FindClass("hzg/wpn/nexus/libpniio/jni/LibpniioException");
        env->ThrowNew(libpniioExceptionClass,pniex.description().c_str());
    }
}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write__JLjava_lang_String_2IZ(JNIEnv *env, jclass jClass, jlong jLong,
                                                                              jstring jString, jint jInt, jboolean append) {
    typedef pni::io::nx::nxpath nxpath_t;


    NativeString nativeString(env, jString);

    try {
        NxFile* nxFile = reinterpret_cast<NxFile*>(jLong);
        auto nx_path = nxpath_t::from_string(nativeString.value);
        auto o = pni::io::nx::get_object(nxFile->file.root(), nx_path);

        pni::io::nx::write(o,jInt);

        if(append){
            pni::io::nx::grow(o,0);
        }
    } catch(const pni::io::exception& pniex){
        jclass libpniioExceptionClass = env->FindClass("hzg/wpn/nexus/libpniio/jni/LibpniioException");
        env->ThrowNew(libpniioExceptionClass,pniex.description().c_str());
    }
}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write__JLjava_lang_String_2J(JNIEnv *env, jclass jclass1, jlong jlong1,
                                                                              jstring jstring1, jlong jlong2) {

}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write__JLjava_lang_String_2F(JNIEnv *env, jclass jclass1, jlong jlong1,
                                                                              jstring jstring1, jfloat jfloat1) {

}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write__JLjava_lang_String_2D(JNIEnv *env, jclass jclass1, jlong jlong1,
                                                                              jstring jstring1, jdouble jdouble1) {

}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write__JLjava_lang_String_2Ljava_lang_String_2Z(JNIEnv *env,
                                                                                                jclass jclass1,
                                                                                                jlong jlong1,
                                                                                                jstring jstring1,
                                                                                                jstring jstring2,
                                                                                                jboolean append) {

}