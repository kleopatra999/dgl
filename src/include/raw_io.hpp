#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <type_traits>

using namespace std;

template<typename val_t, typename stream_t>
void raw_write(stream_t& stream, const val_t val) {
    stream.write(reinterpret_cast<const char *>(&val), sizeof(val));
}

template<typename ptr_t, typename stream_t, typename size_t>
void raw_write(stream_t& stream, const ptr_t *ptr, const size_t size) {
    stream.write(reinterpret_cast<const char *>(ptr), size);
}

template<typename val_t, typename stream_t>
val_t raw_read(stream_t& stream) {
    typename remove_const<val_t>::type val;
    stream.read(reinterpret_cast<const char *>(&val), sizeof(val));
    return val;
}

template<typename val_t, typename stream_t = boost::asio::streambuf&>
val_t raw_read(boost::asio::streambuf& buf) {
    istream stream(&buf);
    return raw_read<val_t>(stream);
}
