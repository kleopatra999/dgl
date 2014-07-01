#include "my_read_write.hpp"
#include "dgl-server.hpp"
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;
using boost::asio::ip::tcp;

const char *_dgl_pushRet_ptr    = nullptr;
uint32_t    _dgl_pushRet_size   = 0;
bool        _dgl_pushRet_delete = true;



template<typename T>
void debug(T s)   {
    if (getenv("NO_DEBUG")) return;
    cerr << s << "\t";
}

static void debug_endl()      {
    if (getenv("NO_DEBUG")) return;
    cerr << endl;
}

static void debug_inst(uint16_t id) {
    if (getenv("NO_DEBUG")) return;
    cerr << dgl_func_name(id) << "\t";
}

static  int         debug_call_count;
static  ostream&    debug_call(uint16_t id, uint32_t size) {
    if (getenv("NO_DEBUG")) return cerr;
    ++debug_call_count;
    return cerr << debug_call_count << " "
        << dgl_func_name(id) << "("
        << size << ")";
}



void dgl_handle_call(tcp::socket& socket) {
    using boost::asio::streambuf;
    streambuf       reply_buf;
    ostream         reply_stream(&reply_buf);
    uint32_t        size[1];
    my_read         (socket, buffer(size));
    auto            callbuf     = new char[*size];
    my_read         (socket, buffer(callbuf, *size));
    auto            id          = *(uint16_t*)callbuf;
    callbuf                    += sizeof(id);
    debug_call      (id, *size);
    dgl_exec_func   (id)(callbuf, reply_stream);
    if (reply_buf.size()) {
        debug(" ="); debug(reply_buf.size());
        // TODO check size
        uint32_t    reply_size[1] = { (uint32_t)reply_buf.size() };
        my_write    (socket, buffer(reply_size));
        my_write    (socket, reply_buf);
    }
    debug_endl();
}
