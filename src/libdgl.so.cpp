#include "libdgl.hpp"
#include "instruction.hpp"

#include <iostream>

using namespace std;

static bool                 _dgl_is_init = false;
static vector<Instruction>  _dgl_instructions;

void                    dgl_init(std::string mode) {
    _dgl_is_init = true;
    cout << "dgl_init: " << mode << endl;
}

bool                    dgl_is_init() {
    return _dgl_is_init;
}

void                    dgl_sync() {
}

vector<Instruction>&    dgl_instructions() {
    return _dgl_instructions;
}
