#include "dgl-server.hpp"
#include "pixels-utils.hpp"
#include <iostream>
#include <fstream>
#include <GLES2/gl2.h>
//#include <EGL/egl.h>
#include "eglut/eglut.h"

using namespace std;

//extern EGLDisplay egl_display;
//extern EGLSurface egl_surface;

void exec_eglSwapBuffers(char *buf, ostream &reply) {
    //eglSwapBuffers(egl_display, egl_surface);
    //SDL_GL_SwapWindow(dgl_main_window());
    eglutFlip();
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
