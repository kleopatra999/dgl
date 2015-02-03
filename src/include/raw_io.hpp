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
    typename std::remove_const<val_t>::type val;
    stream.read(reinterpret_cast<const char *>(&val), sizeof(val));
    return val;
}

template<typename val_t, typename stream_t = boost::asio::streambuf&>
val_t raw_read(boost::asio::streambuf& buf) {
    istream stream(&buf);
    return raw_read<val_t>(stream);
}

template<typename buf_t, typename stream_t>
void raw_write_buf(stream_t& stream, const buf_t& buf) {
    using boost::asio::buffer_cast;
    auto data = buffer_cast<const char*>  (buf.data());
    assert(buf.size() < numeric_limits<uint32_t>::max());
    auto size = static_cast<uint32_t>     (buf.size());
    raw_write(stream, size);
    raw_write(stream, data, size);
}

template<typename socket_t>
void raw_write_socket_buf(socket_t& socket, string& buf) {
    using boost::asio::buffer;
    using boost::asio::write;
    assert(buf.size() < numeric_limits<uint32_t>::max());
    auto buf_size = static_cast<uint32_t>(buf.size());
    write(socket, buffer(&buf_size, sizeof(buf_size)));
    write(socket, buffer(buf.data(), buf_size));
}
