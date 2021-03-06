#include "run.hpp"

#include <stdlib.h>
#include <sys/stat.h>
#include <map>
#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <boost/program_options.hpp>

using namespace std;
namespace po = boost::program_options;

bool command_runnable(const vector<string>& command) {
    assert(!command.empty());
    if (command.size() > 1) {
        return true;
    }
    auto path       = command[0];
    struct stat stat_buf;
    if (stat(path.c_str(), &stat_buf) == -1) {
        return true;
    }
    auto other_x    = stat_buf.st_mode & S_IXOTH;
    if (other_x) {
        return true;
    }
    auto group_x    = stat_buf.st_mode & S_IXGRP;
    if (group_x && getegid() == stat_buf.st_gid) {
        return true;
    }
    auto owner_x    = stat_buf.st_mode & S_IXUSR;
    if (owner_x && geteuid() == stat_buf.st_uid) {
        return true;
    }
    return false;
}

int main(int argc, char**argv) {
    vector<string> servers, command, debug, dumps;

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h"   ,
            "display this help and exit")
        ("server,s" , po::value(&servers),
            "-s local, to start a local server, TODO add a server (ip, ip:port, hostname)")
            //"add a server (ip, ip:port, hostname)")
        ("dump,d"   , po::value(&dumps),
            "add a file to dump the stream")
        ("debug,D"  , po::value(&debug),
            "specifier debug options")
        ("command,c", po::value(&command));
    po::positional_options_description pos_desc;
    pos_desc.add("command", -1);
    po::variables_map varmap;
    auto parser = po::command_line_parser(argc, argv)
        .options(desc)
        .positional(pos_desc);
    po::store(parser.run(), varmap);
    po::notify(varmap);
    if (varmap.count("help")) {
        cerr << desc << endl;
        return 1;
    }
    
    bool did_something = false;
    thread server_thread;
    if (servers.size() == 1 && servers[0].find("local") == 0) {
        did_something = true;
        cout << "run_dgl_server" << endl;
        if (command.empty()) {
            run_dgl_server();
        } else {
            server_thread = thread(run_dgl_server);
        }
    }
    if (!command.empty()) {
        did_something = true;
        if (command_runnable(command)) {
            cout << "run_dgl_preloaded" << endl;
            run_dgl_preloaded(argc, argv, command);
        } else {
            cout << "run_dgl_stream" << endl;
            run_dgl_stream(command[0]);
        }
    }
    if (server_thread.joinable()) {
        server_thread.join();
    }
    if (!did_something) {
        cerr << desc << endl;
        return 1;
    }
    return 0;
}
