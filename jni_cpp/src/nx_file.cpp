//
// Created by ingvord on 21.10.2021.
//

#include "nx_file.hpp"

#include <pni/io/nexus.hpp>

using namespace pni::io;

namespace libpniio::jni {
    hdf5::node::Dataset NxFile::get_dataset(const std::string& nx_path){
        if(this->datasets.count(nx_path)){
            return this->datasets[nx_path];
        } else {
            auto nx_path_o = nexus::Path::from_string(nx_path);

            nexus::PathObjectList objects = nexus::get_objects(this->file.root(), nx_path_o);
            if(objects.size() > 1) {
                std::string message{"ambiguous nxPath: "};
                message += nx_path;
                throw std::runtime_error{message};
            }
            auto result = objects.front();
            if(result.type() != nexus::PathObject::Type::DATASET) {
                std::string message{"nxPath object is not a dataset "};
                message += nx_path;
                throw std::runtime_error{message};
            }

            this->datasets[nx_path] = result;
            return this->get_dataset(nx_path);
        }
    }
}

