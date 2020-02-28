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
    TRY
        NativeString nativeString(env, jString);
        NativeString nativeString1(env, nxTemplate);

        auto xml = xml_n::create_from_file(nativeString1.value);
        auto file = nxfile_t::create_file(nativeString.value);
        auto root_group = file.root();

        xml_n::xml_to_nexus(xml.get_child("definition"), root_group);

        file.flush();

        auto *rv = new NxFile(file);
        return reinterpret_cast<jlong>(rv);
    CATCH
}

jlong Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_openFile(JNIEnv *env, jclass jClass, jstring jString) {
    TRY
        NativeString nativeString(env, jString);
        auto file = nxfile_t::open_file(nativeString.value, false);
        auto *rv = new NxFile(file);
        return reinterpret_cast<jlong>(rv);
    CATCH
}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_closeFile(JNIEnv *env, jclass jClass, jlong jLong) {
    TRY
        NxFile *nxFile = reinterpret_cast<NxFile *>(jLong);
        nxFile->file.close();
        delete nxFile;
    CATCH
}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_flush(JNIEnv *env, jclass jClass, jlong jLong) {
    TRY
        NxFile *nxFile = reinterpret_cast<NxFile *>(jLong);
        nxFile->file.flush();
    CATCH
}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write__JLjava_lang_String_2IZ(JNIEnv *env, jclass jClass, jlong jLong,
                                                                               jstring jString, jint jInt, jboolean append) {
    write(env, jClass, jLong, jString, jInt, append);
}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write__JLjava_lang_String_2JZ(JNIEnv *env, jclass jClass, jlong jLong,
                                                                              jstring jString, jlong jLong1, jboolean append) {
    write(env, jClass, jLong, jString, jLong1, append);
}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write__JLjava_lang_String_2FZ(JNIEnv *env, jclass jClass, jlong jLong,
                                                                              jstring jString, jfloat jFloat, jboolean append) {
    write(env, jClass, jLong, jString, jFloat, append);
}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write__JLjava_lang_String_2DZ(JNIEnv *env, jclass jClass, jlong jLong,
                                                                              jstring jString, jdouble jDouble, jboolean append) {
    write(env, jClass, jLong, jString, jDouble, append);
}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write__JLjava_lang_String_2Ljava_lang_String_2Z(JNIEnv *env,
                                                                                                 jclass jClass,
                                                                                                 jlong jLong,
                                                                                                 jstring jString,
                                                                                                 jstring jstring2,
                                                                                                 jboolean append
) {
    NativeString nativeString2(env, jstring2);
    write(env, jClass, jLong, jString, nativeString2.value, append);
}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write__JLjava_lang_String_2Lsun_nio_ch_DirectBuffer_2I_3SZ(JNIEnv *env, jclass jclass1,
                                                                                   jlong jlong1, jstring jstring1,
                                                                                   jobject jlong2, jint size,
                                                                                   jshortArray array,
                                                                                   jboolean append) {
    uint16_t* data = reinterpret_cast<uint16_t*>(env->GetDirectBufferAddress(jlong2));
    write_image(env, jclass1, jlong1, jstring1, data, size, append);
}


void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write__JLjava_lang_String_2Lsun_nio_ch_DirectBuffer_2I_3IZ(JNIEnv *env, jclass jclass1,
                                                                                 jlong jlong1, jstring jstring1,
                                                                                   jobject jlong2, jint size, jintArray array, jboolean append) {
    uint32_t* data = reinterpret_cast<uint32_t*>(env->GetDirectBufferAddress(jlong2));
    write_image(env, jclass1, jlong1, jstring1, data, size, append);
}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write__JLjava_lang_String_2Lsun_nio_ch_DirectBuffer_2I_3FZ(JNIEnv *env, jclass jclass1,
                                                                                 jlong jlong1, jstring jstring1,
                                                                                   jobject jlong2, jint size, jfloatArray array, jboolean append) {
    float_t* data = reinterpret_cast<float_t*>(env->GetDirectBufferAddress(jlong2));
    write_image(env, jclass1, jlong1, jstring1, data, size, append);
}

