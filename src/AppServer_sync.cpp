#include "AppServer.hpp"
#include "AppServerPriv.hpp"
#include "instruction.hpp"
#include "raw_io.hpp"

#include <vector>
#include <iomanip>
#include <boost/asio.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filter/counter.hpp>

using namespace std;
using boost::asio::ip::tcp;
using boost::asio::buffer;
using namespace boost;
using namespace boost::asio;
namespace io = boost::iostreams;

vector<Instruction>&    dgl_instructions();


void AppServer::sync(buffers return_buffer) {
    if (!is_initialized()) {
        init();
    }
    //dgl_write_stream_dgl_file();
    priv->sync_write();
    priv->sync_read(return_buffer);
    dgl_instructions().clear();
}


void AppServerPriv::sync_write() {
    using namespace boost::asio;
    namespace io = boost::iostreams;
    auto& insts = dgl_instructions();
    string      buf;
    io::counter counter;
    {
        io::filtering_ostream   stream;
        stream.push(boost::ref(counter));
        if (getenv("DGL_GZIP")) {
            stream.push(io::gzip_compressor());
        }
        stream.push(io::back_inserter(buf));
        for (auto& inst : insts) {
            raw_write_buf(stream, inst.buf());
        }
    }
    auto compression = 100.0f * buf.size() / counter.characters();
    cerr << "  " << buf.size() << " bytes"
         << "  compressed to " << fixed << setprecision(2)
           << compression << "%"
         << "  " << insts.size() << " instructions" << endl;
        auto        buf_size    = static_cast<uint32_t>     (buf.size());
    write(*socket, buffer(&buf_size, sizeof(buf_size)));
    write(*socket, buffer(buf.data(), buf_size));
}

void AppServerPriv::sync_read(buffers return_buffers) {
    uint32_t size[1];
    read(*socket, buffer(size));
    read(*socket, return_buffers, transfer_exactly(*size));
}


