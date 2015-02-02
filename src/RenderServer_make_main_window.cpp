#include <unistd.h>
#include <iostream>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <assert.h>

#include "RenderServer.hpp"
#include "RenderServerPriv.hpp"

using namespace std;

EGLDisplay egl_display;
EGLSurface egl_surface;

EGLConfig choose_config(EGLDisplay display) {
    EGLint  attribs[]   = {
        EGL_RED_SIZE        , 1,
        EGL_GREEN_SIZE      , 1,
        EGL_BLUE_SIZE       , 1,
        EGL_DEPTH_SIZE      , 1,
        EGL_SURFACE_TYPE    , EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE , EGL_OPENGL_ES2_BIT,
        EGL_NONE };
    EGLint  num_configs;
    EGLConfig config;
    auto    success     = eglChooseConfig(
        display, attribs, &config, 1, &num_configs);
    // TODO check eglChooseConfig definition and this assert
    assert(success || num_configs == 0);
    return config;
}

Window init_window(EGLint vid, Display *native_display, int width, int height) {
    int x = 0, y = 0, w = width, h = height;
    auto title = "dgl";
    XVisualInfo *visInfo, visTemplate;
    int num_visuals;
    Window root, xwin;
    XSetWindowAttributes attr;
    unsigned long mask;

    /* The X window visual must match the EGL config */
    visTemplate.visualid = vid;
    visInfo = XGetVisualInfo(native_display,
         VisualIDMask, &visTemplate, &num_visuals);
    assert(visInfo);

    root = RootWindow(native_display, DefaultScreen(native_display));

    /* window attributes */
    attr.background_pixel = 0;
    attr.border_pixel = 0;
    attr.colormap = XCreateColormap(native_display,
         root, visInfo->visual, AllocNone);
    attr.event_mask = StructureNotifyMask | ExposureMask | KeyPressMask;
    mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;

    xwin = XCreateWindow(native_display, root, x, y, w, h,
         0, visInfo->depth, InputOutput, visInfo->visual, mask, &attr);
    assert(xwin);

    XFree(visInfo);

    /* set hints and properties */
    {
        XSizeHints sizehints;
        sizehints.x = x;
        sizehints.y = y;
        sizehints.width  = w;
        sizehints.height = h;
        sizehints.flags = USSize | USPosition;
        XSetNormalHints(native_display, xwin, &sizehints);
        XSetStandardProperties(native_display, xwin,
            title, title, None, (char **) NULL, 0, &sizehints);
    }

    XMapWindow(native_display, xwin);

    return xwin;
}

void _make_main_window() {
    int     width           = 800;
    int     height          = 600;
    auto    display_name    = ":0";
    // TODO XCloseDisplay(native_display);
    auto    native_display  = XOpenDisplay(display_name);
    assert( native_display);
    auto    display         = eglGetDisplay(native_display);
    // TODO eglTerminate
    assert( eglInitialize(display, nullptr, nullptr));
    EGLConfig   config      = choose_config(display);
    eglBindAPI(EGL_OPENGL_ES_API);
    EGLint  context_attribs[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE };
    auto    context     = eglCreateContext(
        display, config, EGL_NO_CONTEXT, context_attribs);
    assert(context);
    EGLint  vid;
    assert( eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &vid));
    auto    window      = init_window(vid, native_display, width, height);
    auto    surface     = eglCreateWindowSurface(
        display, config, window, nullptr);
    assert( eglMakeCurrent(display, surface, surface, context));
    glViewport(0, 0, width, height);
    glScissor(0, 0, width, height);
    if (getenv("DGL_RED_WINDOW")) {
        // TODO window is not read that fast, wait somehow
        usleep(4*16000);
        glClearColor(1.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        eglSwapBuffers(display, surface);
    }
}

void RenderServerPriv::make_main_window() {
    _make_main_window();
}

void RenderServer::make_main_window() {
    priv->make_main_window();
}
