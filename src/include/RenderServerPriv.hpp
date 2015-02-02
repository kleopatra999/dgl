#pragma once
#include <boost/asio.hpp>

using namespace boost;
using namespace boost::asio::ip;

typedef tcp::socket     socket_t;
typedef tcp::endpoint   endpoint_t;
typedef tcp::acceptor   acceptor_t;

using namespace boost::asio;

struct RenderServerPriv {
    void session(socket_t socket);
    void serve(
        asio::io_service& io_service,
        unsigned short port);
    void handle_call(socket_t& socket);
};
