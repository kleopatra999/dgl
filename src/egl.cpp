#include "libdgl.hpp"
#include "AppServer.hpp"

static
void new_call(uint16_t id) {
    dgl_instructions().push_back(Instruction(id));
}

static const uint16_t ID_eglSwapBuffers = 0 | egl_partition;

extern "C" void eglSwapBuffers() {
    using boost::asio::buffer;
    new_call(ID_eglSwapBuffers);
    char null[1];
    app.sync(buffers({ buffer(null) }));
}
