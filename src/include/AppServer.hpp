#pragma once
#include <memory>
#include <vector>
#include <boost/asio.hpp>

using namespace std;
using boost::asio::ip::tcp;
using boost::asio::mutable_buffers_1;
typedef vector<mutable_buffers_1> buffers;

struct AppServerPriv;

struct AppServer {
    void init();
    void sync(buffers return_buffer);

    bool is_initialized() const { return _is_initialized; }
    tcp::socket* socket();

    AppServer();
    ~AppServer();
private:
    bool _is_initialized;
    std::unique_ptr<AppServerPriv> priv;
};

extern AppServer app;
