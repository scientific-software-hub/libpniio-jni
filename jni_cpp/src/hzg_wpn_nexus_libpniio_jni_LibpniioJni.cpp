//
// Created by ingvord on 3/31/15.
//
#include <jni.h>
#include <stdexcept>
#include <h5cpp/hdf5.hpp>
#include <pni/io/nexus/xml/create.hpp>
#include <boost/filesystem.hpp>

#include "hzg_wpn_nexus_libpniio_jni_LibpniioJni.h"
//#include "jni_helpers.hpp"
#include "nx_file.hpp"
#include "native_string.hpp"
#include "write.hpp"

using namespace libpniio::jni;

jlong Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_createFile(JNIEnv *env, jclass jClass, jstring jString,
                                                             jstring nxTemplate) {
    try {
        using hdf5::node::get_node;
        using hdf5::node::Type;
        NativeString nativeString(env, jString);
        NativeString nativeString1(env, nxTemplate);

        boost::filesystem::path templatePath{nativeString1.value};
        if (!boost::filesystem::exists(templatePath)) {
            jclass libpniioExceptionClass = env->FindClass("hzg/wpn/nexus/libpniio/jni/LibpniioException");
            env->ThrowNew(libpniioExceptionClass, "template does not exists");
            return -1;
        }


        auto file = hdf5::file::create(nativeString.value, hdf5::file::AccessFlags::TRUNCATE);
        auto root_group = file.root();

        pni::io::nexus::xml::create_from_file(root_group, templatePath);
        if (get_node(root_group, "/entry").type() != Type::GROUP) {
            jclass libpniioExceptionClass = env->FindClass("hzg/wpn/nexus/libpniio/jni/LibpniioException");
            env->ThrowNew(libpniioExceptionClass, "structure is not created");
            return -1;
        }

        auto *rv = new NxFile(file);
        return reinterpret_cast<jlong>(rv);
    } catch (const std::runtime_error& ex){
        jclass libpniioExceptionClass = env->FindClass("hzg/wpn/nexus/libpniio/jni/LibpniioException");
        env->ThrowNew(libpniioExceptionClass,ex.what());
        return -1;
    } catch (...) {
        jclass libpniioExceptionClass = env->FindClass("hzg/wpn/nexus/libpniio/jni/LibpniioException");
        env->ThrowNew(libpniioExceptionClass,"Unexpected runtime error in libpniio...");
        return -1;
    }
}

jlong Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_openFile(JNIEnv *env, jclass jClass, jstring jString) {
    try {
        NativeString nativeString(env, jString);
        auto file = hdf5::file::open(nativeString.value, false);
        auto *rv = new NxFile(file);
        return reinterpret_cast<jlong>(rv);
    } catch (const std::runtime_error& ex){
        jclass libpniioExceptionClass = env->FindClass("hzg/wpn/nexus/libpniio/jni/LibpniioException");
        env->ThrowNew(libpniioExceptionClass,ex.what());
        return -1;
    }
}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_closeFile(JNIEnv *env, jclass jClass, jlong jLong) {
    try {
        NxFile *nxFile = reinterpret_cast<NxFile *>(jLong);
        nxFile->file.close();
        delete nxFile;
    } catch (const std::runtime_error& ex){
        jclass libpniioExceptionClass = env->FindClass("hzg/wpn/nexus/libpniio/jni/LibpniioException");
        env->ThrowNew(libpniioExceptionClass,ex.what());
    }
}


//
//

//
//void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_flush(JNIEnv *env, jclass jClass, jlong jLong) {
//    TRY
//        NxFile *nxFile = reinterpret_cast<NxFile *>(jLong);
//        nxFile->file.flush();
//    CATCH
//}
//
void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write__JLjava_lang_String_2IZ(JNIEnv *env, jclass jClass, jlong jLong,
                                                                               jstring jString, jint jInt, jboolean jboolean1) {
    if(jboolean1)
        append(env, jClass, jLong, jString, jInt);
    else
        write(env, jClass, jLong, jString, jInt);
}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write__JLjava_lang_String_2JZ(JNIEnv *env, jclass jClass, jlong jLong,
                                                                              jstring jString, jlong jLong1, jboolean jboolean1) {
    if(jboolean1)
        append(env, jClass, jLong, jString, jLong1);
    else
        write(env, jClass, jLong, jString, jLong1);
}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write__JLjava_lang_String_2FZ(JNIEnv *env, jclass jClass, jlong jLong,
                                                                              jstring jString, jfloat jFloat, jboolean jboolean1) {
    if(jboolean1)
        append(env, jClass, jLong, jString, jFloat);
    else
        write(env, jClass, jLong, jString, jFloat);
}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write__JLjava_lang_String_2DZ(JNIEnv *env, jclass jClass, jlong jLong,
                                                                              jstring jString, jdouble jDouble, jboolean jboolean1) {
    if(jboolean1)
        append(env, jClass, jLong, jString, jDouble);
    else
        write(env, jClass, jLong, jString, jDouble);
}

void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write__JLjava_lang_String_2Ljava_lang_String_2Z(JNIEnv *env,
                                                                                                 jclass jClass,
                                                                                                 jlong jLong,
                                                                                                 jstring jString,
                                                                                                 jstring jstring2,
                                                                                                 jboolean jboolean1
) {
    NativeString nativeString2(env, jstring2);
    std::string value{nativeString2.value};
    if(jboolean1)
        append(env, jClass, jLong, jString, value);
    else
        write(env, jClass, jLong, jString, value);
}
//
//void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write__JLjava_lang_String_2Lsun_nio_ch_DirectBuffer_2I_3SZ(JNIEnv *env, jclass jclass1,
//                                                                                   jlong jlong1, jstring jstring1,
//                                                                                   jobject jlong2, jint size,
//                                                                                   jshortArray array,
//                                                                                   jboolean append) {
//    uint16_t* data = reinterpret_cast<uint16_t*>(env->GetDirectBufferAddress(jlong2));
//    write_image(env, jclass1, jlong1, jstring1, data, size, append);
//}
//
//
//void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write__JLjava_lang_String_2Lsun_nio_ch_DirectBuffer_2I_3IZ(JNIEnv *env, jclass jclass1,
//                                                                                 jlong jlong1, jstring jstring1,
//                                                                                   jobject jlong2, jint size, jintArray array, jboolean append) {
//    uint32_t* data = reinterpret_cast<uint32_t*>(env->GetDirectBufferAddress(jlong2));
//    write_image(env, jclass1, jlong1, jstring1, data, size, append);
//}
//
//void Java_hzg_wpn_nexus_libpniio_jni_LibpniioJni_write__JLjava_lang_String_2Lsun_nio_ch_DirectBuffer_2I_3FZ(JNIEnv *env, jclass jclass1,
//                                                                                 jlong jlong1, jstring jstring1,
//                                                                                   jobject jlong2, jint size, jfloatArray array, jboolean append) {
//    float_t* data = reinterpret_cast<float_t*>(env->GetDirectBufferAddress(jlong2));
//    write_image(env, jclass1, jlong1, jstring1, data, size, append);
//}

