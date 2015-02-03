#pragma once
#include <memory>
#include <boost/asio.hpp>

using namespace std;
using namespace boost;
using boost::asio::ip::tcp;

struct AppServerPriv {
    void connect(tcp::socket& socket);
    void sync_write();
    void sync_read(buffers return_buffers);

    asio::io_service io_service;
    unique_ptr<tcp::socket> socket;
};
