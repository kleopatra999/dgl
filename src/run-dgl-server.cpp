#include <iostream>
#include "RenderServer.hpp"

void run_dgl_server() {
    RenderServer render_server;
    try {
        render_server.run(12345); // PORT
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return;
    }
}
