//
// Created by ingvord on 3/31/15.
//
#include "org_bitbucket_ingvord_pnijni_LibpniioJni.h"

#include <pni/io/nx/nx.hpp>

JNIEXPORT void JNICALL Java_org_bitbucket_ingvord_pnijni_LibpniioJni_createFile
(JNIEnv * env, jobject jo, jstring js){
    const char *nativeString = env->GetStringUTFChars(js, 0);

    auto file = pni::io::nx::h5::nxfile::create_file(nativeString,false);

    env->ReleaseStringUTFChars(js, nativeString);

}

