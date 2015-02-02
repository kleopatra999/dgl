#include <boost/asio.hpp>

#include "RenderServer.hpp"
#include "RenderServerPriv.hpp"

using namespace std;
using namespace boost;
using boost::asio::ip::tcp;

typedef tcp::socket     socket_t;
typedef tcp::endpoint   endpoint_t;
typedef tcp::acceptor   acceptor_t;



void RenderServerPriv::session(socket_t socket) {
    try {
        for (;;) {
            handle_call(socket);
        }
    } catch (std::exception& e) {
        cerr << "Exception in thread: " << e.what() << "\n";
    }
}


void RenderServerPriv::serve(
        asio::io_service& io_service,
        unsigned short port) {
    acceptor_t acceptor(
        io_service,
        endpoint_t(tcp::v4(), port));
    socket_t socket(io_service);
    acceptor.accept(socket);
    socket.set_option(tcp::no_delay(true));
    session(std::move(socket));
}


void RenderServer::run(unsigned short port) {
    asio::io_service io_service;
    priv->serve(io_service, port);
}
