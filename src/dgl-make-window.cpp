#include <unistd.h>
#include <iostream>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include "eglut/eglut.h"

using namespace std;

EGLDisplay egl_display;
EGLSurface egl_surface;

void dgl_make_main_window() {
    eglutInitWindowSize(300, 300);
    eglutInitAPIMask(EGLUT_OPENGL_ES2_BIT);
    eglutInit(0, { });
    eglutCreateWindow("es2gears");
    if (getenv("DGL_RED_WINDOW")) {
        // TODO window is not read that fast, wait somehow
        usleep(16000);
        glClearColor(1.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        eglutFlip();
    }
}
