#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>

#include <boost/filesystem.hpp>

using namespace std;
namespace fs = boost::filesystem;

std::string get_selfpath() {
    char buff[PATH_MAX];
    ssize_t len = ::readlink("/proc/self/exe", buff, sizeof(buff)-1);
    if (len != -1) {
      buff[len] = '\0';
      return std::string(buff);
    }
    return std::string();
}

void run_dgl_preloaded(int /*argc*/, char**/*argv*/, const vector<string>& command) {
	fs::path selfpath( get_selfpath() );
    stringstream    command_ss;
    command_ss << "LD_PRELOAD=" << selfpath.parent_path() << "/libdgl.so ";
    copy(command.begin(), command.end(), ostream_iterator<string>(command_ss, " "));
    string          command_str = command_ss.str();
    cout << "run: " << command_str << endl;
    auto res = system(command_str.c_str());
    (void)res;
}
