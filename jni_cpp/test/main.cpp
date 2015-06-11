#include <iostream>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/algorithms/get_object.hpp>

#define cimg_display 0

#include "../CImg-1.6.4_pre060415/CImg.h"



using namespace std;
using namespace pni::io::nx;
using namespace pni::io::nx::h5;

int main(int argc,char **argv) {
    h5::nxfile f = h5::nxfile::open_file("/home/khokhria/Projects/hzg.wpn/libpniio-jni/target/test.h5");

    h5::nxfield o = get_object(f.root(), nxpath::from_string("/entry/scan/data/image/value"));

    std::cout << "field.name = " << o.name() << std::endl;
    std::cout << "field.size = " << o.size() << std::endl;

    cimg_library::CImg<int32_t> img(512,512);

//    o(pni::core::slice(0,262144)).read(262144,img.data());

//    img.save_jpeg("test.out.0.jpeg");

    o(pni::core::slice(262144,262144 + 262144)).read(262144,img.data());

    img.save_jpeg("test.out.1.jpeg");

    f.close();

    return 0;
}