#include "AppServer.hpp"
#include "AppServerPriv.hpp"

#include "make_unique.hpp"
#include <unistd.h>
#include <iostream>
#include <vector>

using namespace std;

AppServer app;

AppServer::AppServer() : priv(new AppServerPriv()) {}
AppServer::~AppServer() {}

void AppServer::init() {
    cerr << "INIT" << endl;
    _is_initialized = true;
    //dgl_init_stream_dgl_file();
    for (;;) {
        try {
            priv->socket = make_unique<tcp::socket>(priv->io_service);
            priv->connect(*priv->socket);
            break;
        } catch (std::exception& e) {
            cerr << "Exception: " << e.what() << endl;
            sleep(1);
        }
    }
}

tcp::socket* AppServer::socket() {
    return priv->socket.get();
}

vector<Instruction>& AppServer::instructions() {
    return priv->instructions;
}

void AppServerPriv::connect(tcp::socket& socket) {
    tcp::resolver           resolver(io_service);
    const char *            address     = getenv("DGL_ADDRESS");
                            address     = address ? address : "127.0.0.1";
    auto                    endpoints   =
        resolver.resolve({address, "12345"});
    boost::asio::connect(socket, endpoints);
    socket.set_option(tcp::no_delay(true));
}
