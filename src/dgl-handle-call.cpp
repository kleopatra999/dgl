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
void debug      (T s)   { cerr << s << "\t"; }
static void debug_endl ()      { cerr << endl; }
static void debug_inst (uint16_t id) {
    cerr << dgl_func_name(id) << "\t";
}

static void handle_call_write(tcp::socket& socket) {
    uint32_t ret_size[1]{ _dgl_pushRet_size };  debug("write");
    my_write(socket, buffer(ret_size));
    my_write(socket, buffer(_dgl_pushRet_ptr, *ret_size));
    if (_dgl_pushRet_delete) {
        delete _dgl_pushRet_ptr;
    } else {
        _dgl_pushRet_delete = true;
    }
    _dgl_pushRet_ptr    = nullptr;              debug(*ret_size);
    _dgl_pushRet_size   = 0;
}

void dgl_handle_call(tcp::socket& socket) {
    uint16_t        id[1];
    uint32_t        size[1];                    debug("call");
    my_read(socket, buffer(size));
    my_read(socket, buffer(id));                debug_inst(*id);
    uint32_t        args_size   = *size - sizeof(id);
    auto            args        = new char[args_size];
    my_read(socket, buffer(args, args_size));
    dgl_exec_func(*id)(args);
    // TODO payload: let EXEC handle it, some need to stay
    delete args;
    if (_dgl_pushRet_ptr) {
        handle_call_write(socket);
    }                                           debug_endl();
}
