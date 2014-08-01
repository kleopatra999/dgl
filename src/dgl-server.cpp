#include "dgl-server.hpp"
#include <boost/asio.hpp>

using namespace std;
using namespace boost;
using boost::asio::ip::tcp;
using boost::asio::local::stream_protocol;

/*
typedef stream_protocol::socket     socket_t;
typedef stream_protocol::endpoint   endpoint_t;
typedef stream_protocol::acceptor   acceptor_t;
*/
typedef tcp::socket     socket_t;
typedef tcp::endpoint   endpoint_t;
typedef tcp::acceptor   acceptor_t;



static void session(socket_t socket) {
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
    acceptor_t acceptor(
        io_service,
        endpoint_t(tcp::v4(), port));
        //endpoint_t("/tmp/bla"));
    for (;;) {
        socket_t socket(io_service);
        acceptor.accept(socket);
        socket.set_option(tcp::no_delay(true));
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
