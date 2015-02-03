#include "libdgl.hpp"
#include "instruction.hpp"
#include "make_unique.hpp"
#include "count_calls.hpp"
#include "my_read_write.hpp"
#include "raw_io.hpp"

#include "AppServer.hpp"

#include <iostream>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/timer/timer.hpp>

using namespace std;
using boost::asio::ip::tcp;
using boost::asio::buffer;
using namespace boost;

typedef tcp::socket     socket_t;

void     *return_buffer_ptr   = nullptr;
size_t    return_buffer_size  = 0;
