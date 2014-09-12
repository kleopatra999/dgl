#include <iostream>
//#include <SDL2/SDL.h>
//#include <SDL2/SDL_opengles2.h>
#include <EGL/egl.h>
#include <GL/gl.h>
#include <assert.h>

using namespace std;

EGLDisplay egl_display;
EGLSurface egl_surface;

//static SDL_Window       *main_window;

//SDL_Window *dgl_main_window() { return main_window; }

/*
static void sdldie(const char *msg) {
    auto err = SDL_GetError();
    cerr << "ERROR " << msg << ": " << err << "\n";
    SDL_Quit();
    exit(1);
}
*/

void dgl_make_main_window() {
    auto display_id     = EGL_DEFAULT_DISPLAY;
    auto display        = eglGetDisplay(display_id);
    auto major          = 1;
    auto minor          = 4;
    assert(               eglInitialize(display, &major, &minor));
    GLint config_attribs[] = {
        EGL_RED_SIZE,           1,
        EGL_GREEN_SIZE,         1,
        EGL_BLUE_SIZE,          1,
        EGL_DEPTH_SIZE,         1,
        EGL_SURFACE_TYPE,       EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE,    EGL_OPENGL_ES2_BIT,
        EGL_NONE
    };
    EGLConfig             config;
    GLint wtf = 1;
    assert(               eglChooseConfig(
        display, config_attribs, &config, 1, &wtf));
    assert(               eglBindAPI(EGL_OPENGL_ES_API));
    GLint context_attribs[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };
    auto context        = eglCreateContext(
        display, config, nullptr, context_attribs);
    auto window         = 0;
    GLint surface_attribs[] = { EGL_NONE };
    auto surface        = eglCreateWindowSurface(
        display, config, window, surface_attribs);
    assert(surface);
    assert(               eglMakeCurrent(
        display, surface, surface, context));
    
    typedef void (*gl_iiss)(GLint, GLint, GLsizei, GLsizei);
    auto _glViewport        = (gl_iiss)eglGetProcAddress(
        "glViewport");
    auto _glScissor        = (gl_iiss)eglGetProcAddress(
        "glScissor");
    _glViewport  (0, 0, 300, 300);
    _glScissor   (0, 0, 300, 300);

    egl_display = display;
    egl_surface = surface;
}

/*
SDL_Window *dgl_make_window() {
    SDL_Window     *window;
    SDL_GLContext   context;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        sdldie("SDL_Init");
    }
    // OpenGL Profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_ES);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    window  = SDL_CreateWindow("DGL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640, 480,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window) {
        sdldie("SDL_CreateWindow");
    }
	
    context = SDL_GL_CreateContext(window);
    if (!context) {
        sdldie("SDL_GL_CreateContext");
    }

    SDL_GL_MakeCurrent(window, context);
    SDL_GL_SetSwapInterval(1);

    if (getenv("DGL_RED_WINDOW")) {
        glClearColor(1.0, 0.0, 0.0, 1.0);
    }
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(window);
    return window;
}
*/

/*void dgl_make_main_window() {
    main_window = dgl_make_window();
}*/
