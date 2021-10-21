//
// Created by ingvord on 14.06.2021.
//

#ifndef LIBPNIIO_JNI_NX_FILE_HPP
#define LIBPNIIO_JNI_NX_FILE_HPP

#include <map>
#include <h5cpp/hdf5.hpp>

namespace libpniio {
    namespace jni {
        class NxFile{
        protected:
            std::map<std::string, hdf5::node::Dataset> datasets;
        public:
            hdf5::file::File file;
            hdf5::node::Dataset get_dataset(const std::string& nx_path);
            NxFile(hdf5::file::File file):file(file){}
        };
    }
}

#endif //LIBPNIIO_JNI_NX_FILE_HPP
