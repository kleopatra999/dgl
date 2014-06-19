#pragma once

#include "instruction.hpp"

#include <vector>
#include <string>

using namespace std;

void                    dgl_init(string mode = "");
bool                    dgl_is_init();
void                    dgl_sync();
vector<Instruction>&    dgl_instructions();
