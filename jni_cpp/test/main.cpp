#include <iostream>
#include <chrono>
#include <pni/io/nexus/xml/create.hpp>
#include <pni/io/nexus/path.hpp>

using namespace std;
using namespace pni::io;

auto get_dataset(const string& nx_path_as_string, const hdf5::file::File& file) -> hdf5::node::Dataset{
    auto nx_path = nexus::Path::from_string(nx_path_as_string);
    std::string nx_path_string = nexus::Path::to_string(nx_path);

    nexus::PathObjectList objects = nexus::get_objects(file.root(), nx_path);
    auto result = objects.front();
    return result;
}

void append(ulong v, const hdf5::node::Dataset& dataset){
    dataset.extent(0, 1);
    auto size = dataset.dataspace().size();


    hdf5::dataspace::Hyperslab selection{{0},
                                         {1},
                                         {1},
                                         {1}};
    selection.offset(0, size - 1);
    dataset.write(v, selection);
}

int main(int argc,char **argv) {

    if (boost::filesystem::exists("/tmp/tmp.pkeofpWFJ6/cmake-build-debug-remote/test_native.h5")) {
        boost::filesystem::remove("/tmp/tmp.pkeofpWFJ6/cmake-build-debug-remote/test_native.h5");
    }

    auto file = hdf5::file::create("/tmp/tmp.pkeofpWFJ6/cmake-build-debug-remote/test_native.h5", hdf5::file::AccessFlags::TRUNCATE);
    auto root_group = file.root();

    pni::io::nexus::xml::create_from_file(root_group, "/tmp/tmp.pkeofpWFJ6/test/test.nxdl.xml");

    auto start = chrono::system_clock::now();


    auto dataset = get_dataset("/entry/long/value", file);

    hdf5::dataspace::Hyperslab selection{{0},{1},{1},{1}};

    auto dtype = hdf5::datatype::create<long int>();
    hdf5::property::DatasetTransferList dtpl;
    hdf5::dataspace::Simple simple_space({1}, {hdf5::dataspace::Simple::UNLIMITED});
    for(size_t i = 0; i < 1000000  ; i++) {
        dataset.extent(0, 1);
        auto file_space = dataset.dataspace();
        selection.offset(0, i);
        file_space.selection(hdf5::dataspace::SelectionOperation::SET,selection);
        dataset.write(std::rand(), dtype, simple_space, file_space, dtpl);
    }
    auto end = chrono::system_clock::now();

    cout << "Time elapsed (ms): " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << endl;

    file.flush(hdf5::file::Scope::GLOBAL);
    file.close();

    return 0;
}