#include "count_calls.hpp"
#include "consts.hpp"
#include "my_read_write.hpp"
#include <cstdlib>
#include <iostream>
#include <thread>
#include <utility>
#include <boost/asio.hpp>

using namespace std;
using namespace boost;
using boost::asio::ip::tcp;
using boost::asio::buffer;

extern void         init_function_names();
extern void         init_mod_exec();
typedef void      (*ExecFunc)(char *buf);
extern ExecFunc     _dgl_functions[1700];
extern const char  *_dgl_pushRet_ptr;
extern uint32_t     _dgl_pushRet_size;
extern bool         _dgl_pushRet_delete;


template<typename T>
void debug      (T s)   { cerr << s << "\t"; }
void debug_endl ()      { cerr << endl; }
void debug_inst (uint16_t id) {
    cerr << _dgl_function_names[id] << "\t";
}

void handle_call_write(tcp::socket& socket) {
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

void handle_call(tcp::socket& socket) {
    uint16_t        id[1];
    uint32_t        size[1];                    debug("call");
    my_read(socket, buffer(size));
    my_read(socket, buffer(id));                debug_inst(*id);
    uint32_t        args_size   = *size - sizeof(id);
    auto            args        = new char[args_size];
    my_read(socket, buffer(args, args_size));
    _dgl_functions[*id](args);
    // TODO payload: let EXEC handle it, some need to stay
    delete args;
    if (_dgl_pushRet_ptr) {
        handle_call_write(socket);
    }                                           debug_endl();
}

void session(tcp::socket socket) {
    try {
        for (;;) {
            handle_call(socket);
        }
    } catch (std::exception& e) {
        cerr << "Exception in thread: " << e.what() << "\n";
    }
}

void server(asio::io_service& io_service, unsigned short port) {
    tcp::acceptor acceptor(
        io_service,
        tcp::endpoint(tcp::v4(), port));
    for (;;) {
        tcp::socket socket(io_service);
        acceptor.accept(socket);
        session(std::move(socket));
        //std::thread(session, std::move(socket)).detach();
        return;
    }
}

int main(int, char**) {
    init_mod_exec();
    init_function_names();
    try {
        asio::io_service io_service;
        server(io_service, 12345);
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
