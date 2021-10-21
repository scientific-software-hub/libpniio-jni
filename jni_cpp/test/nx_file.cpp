//
// Created by ingvord on 21.10.2021.
//
#include "../src/nx_file.hpp"
#include <pni/io/nexus/xml/create.hpp>
#include <pni/io/nexus/path.hpp>

using namespace std;
using namespace pni::io;
using namespace libpniio::jni;

int main(int argc,char **argv) {
    auto file = hdf5::file::create("/tmp/tmp.pkeofpWFJ6/cmake-build-debug-remote/test_nx_file.h5", hdf5::file::AccessFlags::TRUNCATE);
    auto root_group = file.root();

    nexus::xml::create_from_file(root_group, "/tmp/tmp.pkeofpWFJ6/test/test.nxdl.xml");

    NxFile nxFile{file};

    auto dataset = nxFile.get_dataset("/entry/long/value");

    auto dataset1 = nxFile.get_dataset("/entry/long/value");

    assert(dataset == dataset1);

    return 0;
}
