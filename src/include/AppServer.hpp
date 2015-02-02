#pragma once
#include <memory>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

struct AppServerPriv;

struct AppServer {
    void init();

    bool is_initialized() const { return _is_initialized; }
    tcp::socket* socket();

    AppServer();
    ~AppServer();
private:
    bool _is_initialized;
    std::unique_ptr<AppServerPriv> priv;
};

extern AppServer app;
