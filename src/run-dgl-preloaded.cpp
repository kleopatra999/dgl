#include "dgl.hpp"

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <iterator>

using namespace std;

void run_dgl_preloaded(const vector<string>& command) {
    stringstream    command_ss;
    command_ss << "LD_PRELOAD=~/Code/clustergl/dgl/build/libdgl.so ";
    copy(command.begin(), command.end(), ostream_iterator<string>(command_ss, " "));
    string          command_str = command_ss.str();
    cout << "run: " << command_str << endl;
    system(command_str.c_str());
}
