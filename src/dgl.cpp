#include "dgl-server.hpp"

#include <iostream>

#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>

using namespace std;
namespace   io = boost::iostreams;
using       boost::asio::buffer_cast;

struct chunk {

    uint32_t    size;
    char*       data;

    chunk(istream& in) {
        in >> size >> ws;
        if (size > 0) {
            data = new char[size];
            in.read(data, size);
            in >> ws;
        } else {
            data = nullptr;
        }
    }
    
    ~chunk() {
        if (data) {
            delete data;
        }
    }
};

int main() {
    dgl_make_main_window();
    io::stream<io::file>    stream;
    stream.open("stream.dgl");
    while (!stream.eof()) {
        uint16_t        id;
        stream >> id >> ws;
        chunk           call            (stream);
        char*           buf             = call.data;
        io::stream<io::null_sink>       reply_stream( (io::null_sink()) );
        dgl_exec_func(id)(buf, reply_stream);
    }
    return 0;
}
