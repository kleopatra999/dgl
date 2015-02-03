#include "AppServer.hpp"
#include "AppServerPriv.hpp"
#include "instruction.hpp"
#include "raw_io.hpp"

#include <boost/asio.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>

using namespace std;
using boost::asio::ip::tcp;
using boost::asio::buffer;
using namespace boost;
using namespace boost::asio;
namespace io = boost::iostreams;

void dgl_sync_read(buffers b);
void dgl_sync_end();
vector<Instruction>&    dgl_instructions();



void AppServer::sync(buffers return_buffer) {
    if (!app.is_initialized()) {
        app.init();
    }
    //dgl_write_stream_dgl_file();
    priv->sync_write();
    dgl_sync_read(return_buffer);
    dgl_sync_end();
}

void AppServerPriv::sync_write() {
    auto&       insts   = dgl_instructions();
    //auto&       socket  = *this->socket;
    try {
        //debug_dgl_sync_write(insts);
        string                  buf;
        io::filtering_ostream   stream;
            //io::gzip_compressor() |
        stream.push(io::back_inserter(buf));
        for (auto& inst : insts) {
            raw_write_buf(stream, inst.buf());
        }
        cerr << "sync" << endl;
        cerr << "  " << buf.size() << " bytes" << endl;
        cerr << "  " << insts.size() << " instructions" << endl;
        write_socket_buf(*socket, buf);
    } catch (std::exception& e) {
        cerr << "Exception: " << e.what() << endl;
        exit(1);
    }
}

