#include <iostream>

using namespace std;

int main(int argc,char **argv) {
    h5::nxfile f = h5::nxfile::open_file("/home/khokhria/Projects/pni-libraries/test.nx");

    h5::nxfield o = get_object(f.root(), nxpath::from_string("/entry/data/data"));

    std::cout << "field.name = " << o.name() << std::endl;
    std::cout << "field.size = " << o.size() << std::endl;

    f.close();

    return 0;
}