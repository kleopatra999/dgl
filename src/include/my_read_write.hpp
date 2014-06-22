#pragma once

#include <iostream>
#include <boost/asio.hpp>

using namespace std;

static size_t my_read_stat;
static size_t my_write_stat;

template<typename socket_t, typename buffer_t>
void my_read(socket_t& s, buffer_t b) {
    my_read_stat += boost::asio::read(s, b);
    //cerr << "read\t" << my_read_stat << endl;
}

template<typename socket_t, typename buffer_t>
void my_write(socket_t& s, buffer_t&& b) {
    my_write_stat += boost::asio::write(s, b);
    //cerr << "write\t" << my_write_stat << endl;
}
