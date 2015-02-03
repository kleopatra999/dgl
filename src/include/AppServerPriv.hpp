#pragma once
#include <memory>
#include <boost/asio.hpp>
#include <boost/iostreams/filtering_stream.hpp>

using namespace std;
using namespace boost;
using boost::asio::ip::tcp;
namespace io = boost::iostreams;

struct AppServerPriv {
    void connect(tcp::socket& socket);
    void sync_write();
    //void sync_read(buffers return_buffer);
    //void sync_end();

    asio::io_service io_service;
    unique_ptr<tcp::socket> socket;
};
