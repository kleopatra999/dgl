#include "dgl-server.hpp"
#include <boost/asio.hpp>

using namespace std;
using namespace boost;
using boost::asio::ip::tcp;

static void session(tcp::socket socket) {
    try {
        for (;;) {
            dgl_handle_call(socket);
        }
    } catch (std::exception& e) {
        cerr << "Exception in thread: " << e.what() << "\n";
    }
}

static void server(
        asio::io_service& io_service,
        unsigned short port) {
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
    dgl_make_main_window();
    try {
        asio::io_service io_service;
        server(io_service, 12345);
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
