//
// Created by khokhria on 6/9/15.
//

#ifndef LIBPNIIO_JNI_JNI_HELPERS_HPP
#define LIBPNIIO_JNI_JNI_HELPERS_HPP

#include <iostream>

#include <jni.h>



namespace libpniio{
namespace jni {

    namespace xml_n=pni::io::nexus::xml;
    typedef pni::io::nx::nxpath nxpath_t;
    typedef pni::io::nx::shape_t shape_t;
    typedef pni::io::nx::h5::nxfile nxfile_t;
    typedef pni::io::nx::h5::nxfield nxfield_t;
    typedef pni::io::nx::h5::nxobject nxobject_t;
    typedef pni::core::exception exception_t;
    typedef pni::core::exception_record exception_record_t;



    //TODO replace with ID


    auto get_object(JNIEnv * env, jlong jLong, jstring jString) -> nxobject_t;

    template<typename T>
    void write(JNIEnv * env, jclass, jlong jLong, jstring jString, T value, bool append) {
        using namespace pni::core;
        using namespace pni::io::nx;

        TRY
            nxfield_t fld = get_object(env, jLong, jString);

            if(append) grow(fld,0);

            size_t ndx = fld.size();

            fld(ndx - 1).write(value);
        CATCH
    }

    template <typename T>
    inline void write_image(JNIEnv * env, jclass clazz, jlong jLong, jstring jString, T* value, size_t size,bool append){
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
