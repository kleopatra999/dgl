#pragma once
#include "dgl.hpp"
#include "instruction.hpp"

#include <vector>
#include <string>
#include <memory>
#include <boost/asio.hpp>

using namespace std;
using boost::asio::mutable_buffers_1;
typedef vector<mutable_buffers_1> buffers;

void                    dgl_swap();

void                    dgl_init_stream_dgl_file();
void                    dgl_write_stream_dgl_file();

void *my_dlsym(void *handle, const char *name);
