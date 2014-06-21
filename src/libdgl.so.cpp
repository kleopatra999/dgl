#include "libdgl.hpp"
#include "instruction.hpp"
#include "make_unique.hpp"
#include "consts.hpp"
#include "count_calls.hpp"

#include <iostream>

using namespace std;
using boost::asio::ip::tcp;
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
    cout << "dgl_init: " << mode << endl;
    init_mod_app();
    cout << "1" << endl;
    init_function_names();
    cout << "2" << endl;
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


#include <type_traits>

// From integer type to integer type
template <typename to, typename from>
constexpr typename std::enable_if<std::is_integral<from>::value && std::is_integral<to>::value, to>::type
narrow_cast(const from& value)
{
    return static_cast<to>(value & (static_cast<typename std::make_unsigned<from>::type>(-1)));
}



static void check_size(size_t a, size_t b, uint16_t inst_id) {
    if (a != b) {
        cerr << "dgl_sync: return_buffer size mismatch: "
             << a << " != " << b << "\t"
             << _dgl_function_names[inst_id]
             << endl;
        exit(1);
    }
}

void dgl_sync(mutable_buffers_1 return_buffer) {
    using namespace boost::asio;
    auto&       insts   = dgl_instructions();
    auto&       socket  = *_dgl_socket;
    uint32_t    size[1];
    try {
        for (auto& inst : insts) {
            *size = inst.buf().size();
            write(socket, buffer(size));
            write(socket, inst.buf());
        }
    } catch (std::exception& e) {
        cerr << "Exception: " << e.what() << endl;
        exit(1);
    }
    read(socket, buffer(size));
    check_size(*size, buffer_size(return_buffer), insts.back().id);
    read(socket, return_buffer);
    if (insts.back().id == 1499) {
        count_calls<0, 1000>("swaps/s");
    }
    insts.clear();
}



void                    _dgl_connect(tcp::socket& socket) {
    tcp::resolver           resolver(_dgl_io_service);
    auto                    endpoints =
        resolver.resolve({"127.0.0.1", "12345"});
    boost::asio::connect(socket, endpoints);
}


bool                    dgl_is_init() {
    return _dgl_is_init;
}

vector<Instruction>&    dgl_instructions() {
    return _dgl_instructions;
}
