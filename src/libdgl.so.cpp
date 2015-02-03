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

static vector<Instruction>      _dgl_instructions;


void     *return_buffer_ptr   = nullptr;
size_t    return_buffer_size  = 0;



bool                    dgl_init(std::string ) {
    app.init();
    return true;
}



string dgl_inst_last_name() {
    return dgl_func_name(dgl_instructions().back().id);
}

void dgl_sync_read_check_size(size_t rest, size_t ret) {
    if (rest > ret) {
        cerr << "dgl_sync: return_buffer too small: "
             << rest << " != " << ret << "\t"
             << dgl_inst_last_name()
             << endl;
        exit(1);
    }
}

void debug_print_inst(const Instruction& inst) {
    cerr << "  " << dgl_func_name(inst.id) << endl;
}

void debug_print_insts(const vector<Instruction>& insts) {
    for (auto& inst : insts) {
        debug_print_inst(inst);
    }
}

void debug_dgl_sync_write(const vector<Instruction>& insts) {
    if (!getenv("DEBUG")) return;
    cerr << "dgl_sync_write:" << endl;
    debug_print_insts(insts);
}



vector<Instruction>&    dgl_instructions() {
    return _dgl_instructions;
}
