#pragma once

#include <string>
#include <vector>

// runs a render server with a file
// blocks, as long file is run
void run_dgl_stream(const std::string& path);

// runs a render server with networking
// blocks, as long connection lasts
void run_dgl_server();

// runs a command in a new process
// blocks, returns when new process exits
void run_dgl_preloaded(const std::vector<std::string>& command);
