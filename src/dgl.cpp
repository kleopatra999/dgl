#include <iostream>
#include <boost/program_options.hpp>

using namespace std;
namespace po = boost::program_options;

int main(int argc, char**argv) {
    vector<string> servers, command, debug, dumps;

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h"   ,
            "display this help and exit")
        ("server,s" , po::value(&servers)
            ->default_value(vector<string>(1, "127.0.0.1"), "127.0.0.1"),
            "add a server (ip, ip:port, hostname)")
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
    if (varmap.count("help") || command.empty()) {
        cerr << desc << endl;
        return 1;
    }
    
    return 0;
}
