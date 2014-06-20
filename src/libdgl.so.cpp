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



void                    dgl_sync() {
    auto&       insts   = dgl_instructions();
    auto&       socket  = *_dgl_socket;
    try {
        for (auto& inst : insts) {
            uint32_t    size        = inst.buf().size();
            auto        size_buf    =
                asio::buffer((char*)&size, sizeof(size));
            asio::write(socket, size_buf);
            /*cout << inst.id << "\t"
                 << _dgl_function_names[inst.id] << "\t"
                 << size
                 << endl;*/
            asio::write(socket, inst.buf());
            if (inst.id == id_CGLSwapBuffers) {
                usleep(16000);
                count_calls<0, 1000>("swaps/s");
            }
        }
    } catch (std::exception& e) {
        cerr << "Exception: " << e.what() << endl;
        exit(1);
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
