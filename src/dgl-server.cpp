#include <iostream>
#include "RenderServer.hpp"

int main(int, char**) {
    RenderServer render_server;
    render_server.make_main_window();
    try {
        render_server.run(12345); // PORT
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
