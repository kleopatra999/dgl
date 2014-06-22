#pragma once

#include "instruction.hpp"

#include <vector>
#include <string>
#include <memory>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

void                    dgl_init(string mode = "x11");
bool                    dgl_is_init();
void                    dgl_sync(mutable_buffers_1 return_buffer);
mutable_buffers_1       dgl_sync();
vector<Instruction>&    dgl_instructions();
