//
// Created by ingvord on 3/31/15.
//
#include "hzg_wpn_nexus_libpniio_jni_LibpniioJni.h"
#include "jni_helpers.hpp"

using namespace libpniio::jni;

auto libpniio::jni::get_object(JNIEnv *env, jlong jLong, jstring jString) -> nxobject_t {
    NativeString nativeString(env, jString);

    NxFile *nxFile = reinterpret_cast<NxFile *>(jLong);

    auto nx_path = nxpath_t::from_string(nativeString.value);

    return pni::io::nx::get_object(nxFile->file.root(), nx_path);
}

jlong Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_createFile(JNIEnv *env, jclass jClass, jstring jString,
                                                             jstring nxTemplate) {
    try {
        NativeString nativeString(env, jString);
        NativeString nativeString1(env, nxTemplate);

        auto xml = xml_n::create_from_file(nativeString1.value);
        auto file = nxfile_t::create_file(nativeString.value);
        auto root_group = file.root();

        xml_n::xml_to_nexus(xml.get_child("definition"), root_group);

        file.flush();

        auto *rv = new NxFile(file);
        return reinterpret_cast<jlong>(rv);
    } catch (const exception_t &pniex) {
        jclass libpniioExceptionClass = env->FindClass("hzg/wpn/nexus/libpniio/jni/LibpniioException");
        env->ThrowNew(libpniioExceptionClass, pniex.description().c_str());
    }
}

jlong Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_openFile(JNIEnv *env, jclass jClass, jstring jString) {
    try {
        NativeString nativeString(env, jString);
        auto file = nxfile_t::open_file(nativeString.value, false);
        auto *rv = new NxFile(file);
        return reinterpret_cast<jlong>(rv);
    } catch (const pni::core::exception &pniex) {
        jclass libpniioExceptionClass = env->FindClass("hzg/wpn/nexus/libpniio/jni/LibpniioException");
        env->ThrowNew(libpniioExceptionClass, pniex.description().c_str());
    }
}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_closeFile(JNIEnv *env, jclass jClass, jlong jLong) {
    try {
        NxFile *nxFile = reinterpret_cast<NxFile *>(jLong);
        nxFile->file.close();
        delete nxFile;
    } catch (const pni::core::exception &pniex) {
        jclass libpniioExceptionClass = env->FindClass("hzg/wpn/nexus/libpniio/jni/LibpniioException");
        env->ThrowNew(libpniioExceptionClass, pniex.description().c_str());
    }
}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write__JLjava_lang_String_2I(JNIEnv *env, jclass jClass, jlong jLong,
                                                                               jstring jString, jint jInt) {
    write(env, jClass, jLong, jString, jInt);
}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write__JLjava_lang_String_2J(JNIEnv *env, jclass jClass, jlong jLong,
                                                                              jstring jString, jlong jLong1) {
    write(env, jClass, jLong, jString, jLong1);
}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write__JLjava_lang_String_2F(JNIEnv *env, jclass jClass, jlong jLong,
                                                                              jstring jString, jfloat jFloat) {
    write(env, jClass, jLong, jString, jFloat);
}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write__JLjava_lang_String_2D(JNIEnv *env, jclass jClass, jlong jLong,
                                                                              jstring jString, jdouble jDouble) {
    write(env, jClass, jLong, jString, jDouble);
}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write__JLjava_lang_String_2Ljava_lang_String_2(JNIEnv *env,
                                                                                                 jclass jClass,
                                                                                                 jlong jLong,
                                                                                                 jstring jString,
                                                                                                 jstring jstring2) {
    NativeString nativeString2(env, jstring2);
    write(env, jClass, jLong, jString, nativeString2.value);
}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write__JLjava_lang_String_2JI_3I(JNIEnv *env, jclass jclass1,
                                                                                 jlong jlong1, jstring jstring1,
                                                                                 jlong jlong2, jint size, jintArray array) {
    uint32_t* data = reinterpret_cast<uint32_t*>(jlong2);
    write(env, jclass1, jlong1, jstring1, data, size);
}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write__JLjava_lang_String_2JI_3F(JNIEnv *env, jclass jclass1,
                                                                                 jlong jlong1, jstring jstring1,
                                                                                 jlong jlong2, jint size, jfloatArray array) {
    float_t* data = reinterpret_cast<float_t*>(jlong2);
    write(env, jclass1, jlong1, jstring1, data, size);
}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write_1and_1grow__JLjava_lang_String_2I(JNIEnv *env, jclass jclass1,
                                                                                         jlong jlong1, jstring jstring1,
                                                                                         jint jint1) {
    write_and_grow(env, jclass1, jlong1, jstring1,jint1);

}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write_1and_1grow__JLjava_lang_String_2J(JNIEnv *env, jclass jclass1,
                                                                                         jlong jlong1, jstring jstring1,
                                                                                         jlong jlong2) {
    write_and_grow(env, jclass1, jlong1, jstring1, jlong1);
}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write_1and_1grow__JLjava_lang_String_2F(JNIEnv *env, jclass jclass1,
                                                                                         jlong jlong1, jstring jstring1,
                                                                                         jfloat jfloat1) {
    write_and_grow(env, jclass1, jlong1, jstring1, jfloat1);
}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write_1and_1grow__JLjava_lang_String_2D(JNIEnv *env, jclass jclass1,
                                                                                         jlong jlong1, jstring jstring1,
                                                                                         jdouble jdouble1) {
    write_and_grow(env, jclass1, jlong1, jstring1, jdouble1);
}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write_1and_1grow__JLjava_lang_String_2Ljava_lang_String_2(JNIEnv *env,
                                                                                                           jclass jclass1,
                                                                                                           jlong jlong1,
                                                                                                           jstring jstring1,
                                                                                                           jstring jstring2) {
    NativeString nativeString2(env, jstring2);
    write_and_grow(env, jclass1, jlong1, jstring1, nativeString2.value);
}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write_1and_1grow__JLjava_lang_String_2JI_3I(JNIEnv *env, jclass jclass1,
                                                                                            jlong jlong1,
                                                                                            jstring jstring1,
                                                                                            jlong jlong2,
                                                                                            jint size,
                                                                                            jintArray array) {
    uint32_t* data = reinterpret_cast<uint32_t*>(jlong2);
    write_and_grow(env, jclass1, jlong1, jstring1, data, size);
}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write_1and_1grow__JLjava_lang_String_2JI_3F(JNIEnv *env, jclass jclass1,
                                                                                            jlong jlong1,
                                                                                            jstring jstring1,
                                                                                            jlong jlong2,
                                                                                            jint size,
                                                                                            jfloatArray array) {
    float_t* data = reinterpret_cast<float_t*>(jlong2);
    write_and_grow(env, jclass1, jlong1, jstring1, data, size);
}