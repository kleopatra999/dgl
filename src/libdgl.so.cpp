#include "libdgl.hpp"
#include "instruction.hpp"
#include "make_unique.hpp"
#include "consts.hpp"
#include "count_calls.hpp"
#include "my_read_write.hpp"

#include <iostream>
#include <sys/resource.h>

using namespace std;
using boost::asio::ip::tcp;
using boost::asio::buffer;
using namespace boost;

static bool                     _dgl_is_init = false;
static vector<Instruction>      _dgl_instructions;
static unique_ptr<tcp::socket>  _dgl_socket;
static boost::asio::io_service  _dgl_io_service;

static void                     _dgl_connect(tcp::socket& socket);


void     *return_buffer_ptr   = nullptr;
size_t    return_buffer_size  = 0;



bool                    dgl_init(std::string mode) {
    _dgl_is_init        = true;
    cerr << "dgl_init: " << mode << endl;
    rlim_t              giga    = 1024*1024*1024;
    const struct rlimit one_giga{ giga, giga };
    setrlimit(RLIMIT_AS, &one_giga);
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
    return true;
}



string dgl_inst_last_name() {
    return dgl_func_name(dgl_instructions().back().id);
}



template<typename T>
void debug(T s)   {
    if (getenv("NO_DEBUG")) return;
    cerr << s << "\t";
}

static  void debug_endl()      {
    if (getenv("NO_DEBUG")) return;
    cerr << endl;
}

static  void debug_inst(Instruction& inst) {
    if (getenv("NO_DEBUG")) return;
    cerr << dgl_func_name(inst.id) << "\t";
}

static  void debug_inst()      {
    if (getenv("NO_DEBUG")) return;
    debug_inst(dgl_instructions().back());
}

static  int         debug_write_count;
static  ostream&    debug_write(Instruction& inst) {
    if (getenv("NO_DEBUG")) return cerr;
    ++debug_write_count;
    return cerr << debug_write_count << " "
        << dgl_func_name(inst.id) << "("
        << inst.buf().size() << ")";
}



void dgl_sync_read_check_size(size_t rest, size_t ret) {
    if (rest > ret) {
        cerr << "dgl_sync: return_buffer too small: "
             << rest << " != " << ret << "\t"
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
        for (auto& inst : insts) {          debug_endl();
            *size = inst.buf().size();      debug_write(inst);
            my_write(socket, buffer(size));
            my_write(socket, inst.buf());
        }
    } catch (std::exception& e) {
        cerr << "Exception: " << e.what() << endl;
        exit(1);
    }
}

void dgl_sync_read(buffers return_buffers) {
    using namespace boost::asio;
    auto&                       socket  = *_dgl_socket;
    uint32_t                    size[1];
    debug                       (" =");
    while (!socket.available());
    my_read                     (socket, buffer(size));
    debug                       (*size);
    read(socket, return_buffers, transfer_exactly(*size));
}

void dgl_sync_end() {
    auto& insts = dgl_instructions();    
    if (insts.back().id == 1499) {
        count_calls<0, 1000>("swaps/s");
    }
    insts.clear();
}

void dgl_sync(buffers return_buffer) {
    if (!dgl_is_init()) {
        dgl_init();
    }
    dgl_sync_write();
    dgl_sync_read(return_buffer);
    dgl_sync_end();
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
