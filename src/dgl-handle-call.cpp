#include "my_read_write.hpp"
#include "dgl-server.hpp"
#include "make_unique.hpp"
#include <boost/asio.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/timer/timer.hpp>

using namespace std;
using namespace boost;
using namespace boost::asio;

typedef tcp::socket     socket_t;
typedef tcp::endpoint   endpoint_t;
typedef tcp::acceptor   acceptor_t;


const char *_dgl_pushRet_ptr    = nullptr;
uint32_t    _dgl_pushRet_size   = 0;
bool        _dgl_pushRet_delete = true;



typedef pair<unique_ptr<char>, uint32_t> unique_buffer_t;

unique_buffer_t read_socket_buffer(socket_t& socket) {
    while (!socket.available());
#ifdef DEBUG_TIMER
    timer::auto_cpu_timer t("read_socket_buffer     %w\n");
#endif
    uint32_t    size;
    read(socket, buffer(&size, sizeof(size)));
    // XXX make_unique not good? double frees?
    //auto        buf     = make_unique<char>(size);
    unique_ptr<char> buf(new char[size]);
    read(socket, buffer(buf.get(), size));
    return unique_buffer_t(move(buf), size);
}

void read_socket_packet(socket_t& socket, string& buf) {
    namespace io = boost::iostreams;
#ifdef DEBUG_TIMER
    timer::auto_cpu_timer t("read_socket_packet     %w\n");
#endif
    auto    buffer              = read_socket_buffer(socket);
    auto    buffer_data         = get<0>(buffer).get();
    auto    buffer_size         = get<1>(buffer);
    io::filtering_ostream       stream;
    if (getenv("DGL_GZIP")) {
        stream.push(io::gzip_decompressor());
    }
    stream.push(io::back_inserter(buf));
    stream.write(buffer_data, buffer_size);
}

void dgl_handle_call(socket_t& socket) {
    using boost::asio::streambuf;
    string str;
    read_socket_packet(socket, str);
    auto            buf         = str.data();
    auto            buf_size    = str.size();
    auto            end         = buf + buf_size;
    while (buf != end) {
        auto        call_size   = *(uint32_t*)buf;
        buf                    += sizeof(call_size);
        auto        call_end    = buf + call_size;
        auto        id          = *(uint16_t*)buf;
        buf                    += sizeof(id);

        streambuf       reply_buf;
        ostream         reply_stream(&reply_buf);

        {
#ifdef DEBUG_TIMER
            timer::auto_cpu_timer t("call                   %w\n");
#endif
            dgl_exec_func   (id)(buf, reply_stream);
        }

        if (reply_buf.size()) {
#ifdef DEBUG_TIMER
            timer::auto_cpu_timer t("reply                  %w\n");
#endif
            // TODO check size
            uint32_t    reply_size[1] = { (uint32_t)reply_buf.size() };
            my_write    (socket, buffer(reply_size));
            my_write    (socket, reply_buf);
        }
        buf                     = call_end;
    }
}
