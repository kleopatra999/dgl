#include <string>

static
std::string names[] = {
    "eglSwapBuffers"
};

std::string egl_name(uint16_t id) {
    return names[id];
}
