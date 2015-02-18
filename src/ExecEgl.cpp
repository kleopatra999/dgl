#include "dgl-server.hpp"
#include "pixels-utils.hpp"
#include <iostream>
#include <fstream>
#include <GLES2/gl2.h>
#include <EGL/egl.h>

using namespace std;

void exec_eglSwapBuffers(const char *, ostream &reply) {
    auto display = eglGetCurrentDisplay();
    auto surface = eglGetCurrentSurface(EGL_DRAW);
    eglSwapBuffers(display, surface);
#ifdef SCREENSHOT_eglSwapBuffers
    write_glReadPixels<2>("exec_eglSwapBuffers");
#endif
    char null = '0';
    reply.write(&null, 1);
}

static
exec_func_t funcs[] = {
    exec_eglSwapBuffers
};

exec_func_t egl_exec(uint16_t id) {
    return funcs[id];
}
