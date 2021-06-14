//
// Created by ingvord on 14.06.2021.
//

#ifndef LIBPNIIO_JNI_NX_FILE_HPP
#define LIBPNIIO_JNI_NX_FILE_HPP

namespace libpniio {
    namespace jni {
        struct NxFile{
            hdf5::file::File file;
            NxFile(hdf5::file::File file):file(file){}
        };
    }
}

#endif //LIBPNIIO_JNI_NX_FILE_HPP
