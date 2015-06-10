//
// Created by khokhria on 6/9/15.
//

#ifndef LIBPNIIO_JNI_JNI_HELPERS_HPP
#define LIBPNIIO_JNI_JNI_HELPERS_HPP

#include <iostream>

#include <jni.h>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/xml.hpp>
#include <pni/core/error/exceptions.hpp>
#include <pni/io/nx/algorithms/write.hpp>
#include <pni/io/nx/algorithms/get_object.hpp>
#include <pni/io/nx/algorithms/grow.hpp>

#define TRY try {
#define CATCH } catch(const exception_t& pniex){ \
                    jclass libpniioExceptionClass = env->FindClass("hzg/wpn/nexus/libpniio/jni/LibpniioException"); \
                        env->ThrowNew(libpniioExceptionClass,pniex.description().c_str()); \
              }
namespace libpniio{
namespace jni {

    namespace xml_n=pni::io::nx::xml;
    typedef pni::io::nx::nxpath nxpath_t;
    typedef pni::io::nx::shape_t shape_t;
    typedef pni::io::nx::h5::nxfile nxfile_t;
    typedef pni::io::nx::h5::nxfield nxfield_t;
    typedef pni::io::nx::h5::nxobject nxobject_t;
    typedef pni::core::exception exception_t;
    typedef pni::core::exception_record exception_record_t;

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
        TRY
            auto o = get_object(env, jLong, jString);

            pni::io::nx::write(o,value);
        CATCH
    }

    template<typename T>
    void write_and_grow(JNIEnv * env, jclass clazz, jlong jLong, jstring jString, T value) {
        TRY
            auto&& o = get_object(env, jLong, jString);

            pni::io::nx::write(o,value);
            pni::io::nx::grow(o);
        CATCH
    }

    template <typename T>
    inline void write(JNIEnv * env, jclass clazz, jlong jLong, jstring jString, T* value, size_t size){
        TRY
            nxfield_t fld = get_object(env, jLong, jString);

            shape_t shape = pni::io::nx::get_shape<shape_t>(fld);
            std::cout << "fld.size = " << fld.size() << std::endl;
            std::cout << "size = " << size << std::endl;
            std::cout << "shape[0] = " << shape[0]<< std::endl;
            std::cout << "shape[1] = " << shape[1]<< std::endl;
            std::cout << "shape[2] = " << shape[2]<< std::endl;

            fld.write(size,value);
        CATCH
    }

    template <typename T>
    inline void write_and_grow(JNIEnv * env, jclass clazz, jlong jLong, jstring jString, T* value, size_t size){
        TRY
            nxfield_t fld = get_object(env, jLong, jString);
            shape_t shape = pni::io::nx::get_shape<shape_t>(fld);
            std::cout << "shape[0] = " << shape[0]<< std::endl;
            std::cout << "shape[1] = " << shape[1]<< std::endl;
            std::cout << "shape[2] = " << shape[2]<< std::endl;

            fld.write(size,value);
            fld.grow(0);
        CATCH
    }

}//namespace
}//namespace
#endif //LIBPNIIO_JNI_JNI_HELPERS_HPP
