#include "libdgl.hpp"
#include "instruction.hpp"
#include "make_unique.hpp"

#include <iostream>

using namespace std;
using boost::asio::ip::tcp;
using namespace boost;

static bool                     _dgl_is_init = false;
static vector<Instruction>      _dgl_instructions;
static unique_ptr<tcp::socket>  _dgl_socket;
static boost::asio::io_service  _dgl_io_service;

static void                     _dgl_connect(tcp::socket& socket);



void                    dgl_init(std::string mode) {
    _dgl_is_init        = true;
    cout << "dgl_init: " << mode << endl;
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
    auto&   insts   = dgl_instructions();
    auto&   socket  = *_dgl_socket;
    try {
        for (auto& inst : insts) {
            boost::asio::write(*_dgl_socket, inst.buf());
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
