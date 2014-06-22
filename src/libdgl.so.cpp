#include "libdgl.hpp"
#include "instruction.hpp"
#include "make_unique.hpp"
#include "consts.hpp"
#include "count_calls.hpp"
#include "my_read_write.hpp"

#include <iostream>

using namespace std;
using boost::asio::ip::tcp;
using boost::asio::buffer;
using namespace boost;

static bool                     _dgl_is_init = false;
static vector<Instruction>      _dgl_instructions;
static unique_ptr<tcp::socket>  _dgl_socket;
static boost::asio::io_service  _dgl_io_service;

static void                     _dgl_connect(tcp::socket& socket);

extern void                     init_mod_app();
extern void                     init_function_names();



void                    dgl_init(std::string mode) {
    _dgl_is_init        = true;
    cerr << "dgl_init: " << mode << endl;
    init_mod_app();
    init_function_names();
    for (;;) {
        try {
            _dgl_socket     = make_unique<tcp::socket>(_dgl_io_service);
            _dgl_connect(*_dgl_socket);
            break;
        } catch (std::exception& e) {
            cerr << "Exception: " << e.what() << endl;
            sleep(1);
        }
    }
}



string dgl_inst_last_name() {
    return _dgl_function_names[dgl_instructions().back().id];
}

void dgl_sync_read_check_size(size_t a, size_t b) {
    if (a != b) {
        cerr << "dgl_sync: return_buffer size mismatch: "
             << a << " != " << b << "\t"
             << dgl_inst_last_name()
             << endl;
        exit(1);
    }
}

void dgl_sync_write() {
    using namespace boost::asio;
    auto&       insts   = dgl_instructions();
    auto&       socket  = *_dgl_socket;
    uint32_t    size[1];
    try {
        for (auto& inst : insts) {
            *size = inst.buf().size();
            my_write(socket, buffer(size));
            my_write(socket, inst.buf());
        }
    } catch (std::exception& e) {
        cerr << "Exception: " << e.what() << endl;
        exit(1);
    }
}

template<typename T>
void debug      (T s)   { cerr << s << "\t"; }
void debug_endl ()      { cerr << endl; }
void debug_inst ()      { cerr << dgl_inst_last_name() << "\t"; }

void dgl_sync_read(mutable_buffers_1 return_buffer) {
    using namespace boost::asio;
    auto&       socket  = *_dgl_socket;
    uint32_t    size[1];                        debug("read");
    my_read(socket, buffer(size));              debug(*size);
    dgl_sync_read_check_size(*size, buffer_size(return_buffer));
    my_read(socket, return_buffer);
}

mutable_buffers_1 dgl_sync_read() {
    auto&       socket  = *_dgl_socket;
    uint32_t    size[1];                        debug("read");
    my_read(socket, buffer(size));              debug(*size);
    auto        data    = new char[*size];
    auto        buf     = buffer(data, *size);
    my_read(socket, buf);
    return buf;
}

void dgl_sync_end() {
    auto& insts = dgl_instructions();    
    if (insts.back().id == 1499) {
        count_calls<0, 1000>("swaps/s");
    }
    insts.clear();
}

void dgl_sync(mutable_buffers_1 return_buffer) {
    dgl_sync_write();               debug("sync");  debug_inst();
    dgl_sync_read(return_buffer);   debug_endl();
    dgl_sync_end();
}

mutable_buffers_1 dgl_sync() {
    dgl_sync_write();               debug("sync");  debug_inst();
    auto buf = dgl_sync_read();     debug_endl();
    dgl_sync_end();
    return buf;
}



void                    _dgl_connect(tcp::socket& socket) {
    tcp::resolver           resolver(_dgl_io_service);
    auto                    endpoints =
        resolver.resolve({"127.0.0.1", "12345"});
    boost::asio::connect(socket, endpoints);
    socket.set_option(tcp::no_delay(true));
}


bool                    dgl_is_init() {
    return _dgl_is_init;
}

vector<Instruction>&    dgl_instructions() {
    return _dgl_instructions;
}
