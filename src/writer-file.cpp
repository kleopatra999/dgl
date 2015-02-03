#include "dgl.hpp"
#include "AppServer.hpp"

#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/device/back_inserter.hpp> 
#include <boost/iostreams/stream.hpp>

namespace   io = boost::iostreams;
using       boost::asio::buffer_cast;

io::stream<io::file>    file_stream;

void dgl_init_stream_dgl_file() {
    file_stream.open("stream.dgl");
}

void dgl_write_stream_dgl_file() {
    vector<char>             buf;
    io::stream< io::back_insert_device<decltype(buf)> > stream(buf);
    auto&       insts   = app.instructions();
    for (auto& inst : insts) {
        auto    inst_data   = buffer_cast<const char*>  (inst.buf().data());
        auto    inst_size   = static_cast<uint32_t>     (inst.buf().size());
        inst_data          += 2;
        inst_size          -= 2;
        stream << inst.id << " " << inst_size << " ";
        stream.write(inst_data, inst_size);
        stream << "\n\n";
    }
    stream.flush();
    file_stream.write(buf.data(), buf.size());
    file_stream.flush();
}
