#include "libdgl.hpp"
#include "instruction.hpp"
#include "make_unique.hpp"
#include "consts.hpp"
#include "count_calls.hpp"
#include "my_read_write.hpp"
#include "raw_io.hpp"

#include <iostream>
#include <sys/resource.h>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/timer/timer.hpp>

#define DEBUG_TIMER 1

using namespace std;
using boost::asio::ip::tcp;
using boost::asio::buffer;
using namespace boost;

typedef tcp::socket     socket_t;

static bool                     _dgl_is_init = false;
static vector<Instruction>      _dgl_instructions;
static unique_ptr<socket_t>     _dgl_socket;
static boost::asio::io_service  _dgl_io_service;

static void                     _dgl_connect(socket_t& socket);


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
            _dgl_socket     = make_unique<socket_t>(_dgl_io_service);
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

void dgl_sync_read_check_size(size_t rest, size_t ret) {
    if (rest > ret) {
        cerr << "dgl_sync: return_buffer too small: "
             << rest << " != " << ret << "\t"
             << dgl_inst_last_name()
             << endl;
        exit(1);
    }
}

void debug_print_inst(const Instruction& inst) {
    cerr << "  " << dgl_func_name(inst.id) << endl;
}

void debug_print_insts(const vector<Instruction>& insts) {
    for (auto& inst : insts) {
        debug_print_inst(inst);
    }
}

void debug_dgl_sync_write(const vector<Instruction>& insts) {
    if (!getenv("DEBUG")) return;
    cerr << "dgl_sync_write:" << endl;
    debug_print_insts(insts);
}

template<typename insts_t>
void write_buf_insts(string& buf, insts_t& insts) {
    using boost::asio::buffer_cast;
    namespace io = boost::iostreams;
#ifdef DEBUG_TIMER
    timer::auto_cpu_timer t("write_buf_insts        %w\n");
#endif
    io::filtering_ostream   stream;
    if (getenv("DGL_GZIP")) {
        stream.push(io::gzip_compressor());
    }
    stream.push(io::back_inserter(buf));
    for (auto& inst : insts) {
        auto    inst_data   = buffer_cast<const char*>  (inst.buf().data());
        auto    inst_size   = static_cast<uint32_t>     (inst.buf().size());
        raw_write(stream, inst_size);
        raw_write(stream, inst_data, inst_size);
    }
}

template<typename socket_t>
void write_socket_buf(socket_t& socket, string& buf) {
#ifdef DEBUG_TIMER
    timer::auto_cpu_timer t("write_socket_buf       %w\n");
#endif
    auto        buf_size    = static_cast<uint32_t>     (buf.size());
    //cerr << "  send bytes: " << buf_size << endl;
    my_write(socket, buffer(&buf_size, sizeof(buf_size)));
    my_write(socket, buffer(buf.data(), buf_size));
}

template<typename socket_t, typename insts_t>
void write_socket_insts(socket_t& socket, insts_t& insts) {
    string      buf;
    write_buf_insts(buf, insts);
    write_socket_buf(socket, buf);
}

void dgl_sync_write() {
    using namespace boost::asio;
    auto&       insts   = dgl_instructions();
    auto&       socket  = *_dgl_socket;
    try {
        debug_dgl_sync_write(insts);
        write_socket_insts(socket, insts);
    } catch (std::exception& e) {
        cerr << "Exception: " << e.what() << endl;
        exit(1);
    }
}

void dgl_sync_read(buffers return_buffers) {
    using namespace boost::asio;
#ifdef DEBUG_TIMER
    timer::auto_cpu_timer t("dgl_sync_read          %w\n");
#endif
    auto&                       socket  = *_dgl_socket;
    uint32_t                    size[1];
    my_read                     (socket, buffer(size));
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



void                    _dgl_connect(socket_t& socket) {
    tcp::resolver           resolver(_dgl_io_service);
    const char *            address     = getenv("DGL_ADDRESS");
                            address     = address ? address : "127.0.0.1";
    auto                    endpoints   =
        resolver.resolve({address, "12345"});
    boost::asio::connect(socket, endpoints);
    //socket.connect(endpoint_t("/tmp/bla"));
    socket.set_option(tcp::no_delay(true));
}


bool                    dgl_is_init() {
    return _dgl_is_init;
}

vector<Instruction>&    dgl_instructions() {
    return _dgl_instructions;
}
