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

bool                    dgl_init(string mode = "x11");
bool                    dgl_is_init();
void                    dgl_sync(buffers return_buffers);
vector<Instruction>&    dgl_instructions();
void                    dgl_swap();

void                    dgl_init_stream_dgl_file();
void                    dgl_write_stream_dgl_file();

void *my_dlsym(void *handle, const char *name);
