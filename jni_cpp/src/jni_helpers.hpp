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
#include <pni/core/arrays.hpp>
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
    void write(JNIEnv * env, jclass, jlong jLong, jstring jString, T value, bool append) {
        using namespace pni::core;
        using namespace pni::io::nx;

        TRY
            nxfield_t fld = get_object(env, jLong, jString);

            if(append) grow(fld,0);

            size_t ndx = fld.size();
            std::cout << "ndx = " << ndx << std::endl;

            fld(ndx - 1).write(value);
        CATCH
    }

    template <typename T>
    inline void write(JNIEnv * env, jclass clazz, jlong jLong, jstring jString, T* value, size_t size,bool append){
        using namespace pni::core;
        using namespace pni::io::nx;
        TRY
            nxfield_t fld = get_object(env, jLong, jString);

            shape_t shape = get_shape<shape_t>(fld);

            size_t ndx = append ? shape[0] : 0;
            size_t dim_x = shape[1];
            size_t dim_y = shape[2];

            fld.grow(0);
            fld(ndx, slice(0, dim_x), slice(0, dim_y)).write(size,value);
        CATCH
    }
}//namespace
}//namespace
#endif //LIBPNIIO_JNI_JNI_HELPERS_HPP
