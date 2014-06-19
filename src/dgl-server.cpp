#include "consts.hpp"
#include <cstdlib>
#include <iostream>
#include <thread>
#include <utility>
#include <boost/asio.hpp>

using namespace std;
using namespace boost;
using boost::asio::ip::tcp;

extern void init_function_names();
extern void init_mod_exec();
typedef void (*ExecFunc)(char *buf);
extern ExecFunc _dgl_functions[1700];



void session(tcp::socket socket) {
    try {
        asio::streambuf streambuf;
        istream         stream(&streambuf);
        uint16_t        id;
        uint32_t        size;
        for (;;) {
            asio::read(socket, streambuf, asio::transfer_exactly(sizeof(size)));
            stream.read((char*)&size, sizeof(size));
            asio::read(socket, streambuf, asio::transfer_exactly(size));
            stream.read((char*)&id, sizeof(id));
            uint32_t    args_size   = size - sizeof(id);
            char        *buf        = new char[args_size];
            stream.read(buf, args_size);
            /*cout << id << "\t"
                 << _dgl_function_names[id] << "\t"
                 << size
                 << endl;*/
            // TODO const char*, char*, const char*, ...
            _dgl_functions[id](buf);
            delete buf;
        }
    } catch (std::exception& e) {
        std::cerr << "Exception in thread: " << e.what() << "\n";
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
