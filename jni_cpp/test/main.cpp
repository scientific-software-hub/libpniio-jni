#include <iostream>
#include <chrono>
#include <pni/io/nx/nx.hpp>
#include <pni/io/nx/xml.hpp>
#include <pni/io/nx/algorithms/get_object.hpp>


using namespace std;
using namespace pni::io::nx;

int main(int argc,char **argv) {
    auto file = h5::nxfile::create_file("/tmp/tmp.lZE7OB24XR/test.nx");
    auto xml = xml::create_from_file("/tmp/tmp.lZE7OB24XR/test/test.nxdl.1.1.0.xml");

    auto root_group = file.root();

    xml::xml_to_nexus(xml.get_child("definition"), root_group);

    auto start = chrono::system_clock::now();



    for(size_t i=0;i<1000;i++)
    {
        h5::nxfield value_fld = get_object(root_group, nxpath::from_string("/entry/long/value"));;
        value_fld.grow(0);
        size_t ndx = value_fld.size();

        value_fld(ndx - 1).write(rand());
    }

    auto end = chrono::system_clock::now();

    cout << "Time elapsed (ms): " << chrono::duration_cast<chrono::milliseconds>(end-start).count();

    file.close();

    return 0;
}