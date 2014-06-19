#include "libdgl.hpp"

#include <iostream>

using namespace std;

bool _dgl_is_init = false;

void dgl_init(std::string mode) {
    _dgl_is_init = true;
    cout << "dgl_init: " << mode << endl;
}

bool dgl_is_init() {
    return _dgl_is_init;
}

void dgl_sync() {
}
