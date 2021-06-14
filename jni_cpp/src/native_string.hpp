//
// Created by ingvord on 14.06.2021.
//

#ifndef LIBPNIIO_JNI_NATIVE_STRING_HPP
#define LIBPNIIO_JNI_NATIVE_STRING_HPP

#endif //LIBPNIIO_JNI_NATIVE_STRING_HPP

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