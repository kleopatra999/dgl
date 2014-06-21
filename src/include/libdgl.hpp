#pragma once

#include "instruction.hpp"

#include <vector>
#include <string>
#include <memory>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

void                    dgl_init(string mode = "");
bool                    dgl_is_init();
void                    dgl_sync(mutable_buffers_1 return_buffer);
vector<Instruction>&    dgl_instructions();
