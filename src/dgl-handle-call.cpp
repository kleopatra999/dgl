#include "my_read_write.hpp"
#include "dgl-server.hpp"
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;
using boost::asio::ip::tcp;

const char *_dgl_pushRet_ptr    = nullptr;
uint32_t    _dgl_pushRet_size   = 0;
bool        _dgl_pushRet_delete = true;



void dgl_handle_call(tcp::socket& socket) {
    using boost::asio::streambuf;

    uint32_t        buf_size[1];
    my_read         (socket, buffer(buf_size));

    auto            buf         = new char[*buf_size];
    my_read         (socket, buffer(buf, *buf_size));

    auto            end         = buf + *buf_size;
    while (buf != end) {
        auto        call_size   = *(uint32_t*)buf;
        buf                    += sizeof(call_size);
        auto        call_end    = buf + call_size;
        auto        id          = *(uint16_t*)buf;
        buf                    += sizeof(id);

        streambuf       reply_buf;
        ostream         reply_stream(&reply_buf);

        dgl_exec_func   (id)(buf, reply_stream);

        if (reply_buf.size()) {
            // TODO check size
            uint32_t    reply_size[1] = { (uint32_t)reply_buf.size() };
            my_write    (socket, buffer(reply_size));
            my_write    (socket, reply_buf);
        }
        buf                     = call_end;
    }
}
