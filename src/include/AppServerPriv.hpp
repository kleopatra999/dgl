#pragma once
#include <memory>
#include <boost/asio.hpp>

using namespace std;
using namespace boost;
using boost::asio::ip::tcp;

struct AppServerPriv {
    void connect(tcp::socket& socket);

    asio::io_service io_service;
    unique_ptr<tcp::socket> socket;
};
