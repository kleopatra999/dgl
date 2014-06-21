#include "count_calls.hpp"
#include "consts.hpp"
#include <cstdlib>
#include <iostream>
#include <thread>
#include <utility>
#include <boost/asio.hpp>

using namespace std;
using namespace boost;
using boost::asio::ip::tcp;

extern void         init_function_names();
extern void         init_mod_exec();
typedef void      (*ExecFunc)(char *buf);
extern ExecFunc     _dgl_functions[1700];
extern void        *_dgl_pushRet_ptr;
extern uint32_t     _dgl_pushRet_size;


void session(tcp::socket socket) {
    using namespace boost::asio;
    try {
        uint16_t        id[1];
        uint32_t        size[1];
        for (;;) {
            read(socket, buffer(size));
            read(socket, buffer(id));
            uint32_t    args_size   = *size - sizeof(id);
            auto        args        = new char[args_size];
            read(socket, buffer(args, args_size));
            _dgl_functions[*id](args);
            // TODO payload: let EXEC handle it, some need to stay
            delete args;
            if (_dgl_pushRet_ptr) {
                uint32_t ret_size[1]{ _dgl_pushRet_size };
                write(socket, buffer(ret_size));
                write(socket, buffer(_dgl_pushRet_ptr, *ret_size));
                _dgl_pushRet_ptr    = nullptr;
                _dgl_pushRet_size   = 0;
            }
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
