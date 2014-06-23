#include <iostream>
#include <GL/glew.h>
#include <SDL2/SDL.h>

using namespace std;

static SDL_Window *main_window;

SDL_Window *dgl_main_window() { return main_window; }

static void sdldie(const char *msg) {
    auto err = SDL_GetError();
    cerr << "ERROR " << msg << ": " << err << "\n";
    SDL_Quit();
    exit(1);
}

SDL_Window *dgl_make_window() {
    SDL_Window     *window;
    SDL_GLContext   context;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        sdldie("SDL_Init");
    }
    // OpenGL Profile
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    window  = SDL_CreateWindow("DGL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        300, 300,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window) {
        sdldie("SDL_CreateWindow");
    }
	
    context = SDL_GL_CreateContext(window);

    SDL_GL_SetSwapInterval(1);

    if (getenv("DGL_RED_WINDOW")) {
        glClearColor(1.0, 0.0, 0.0, 1.0);
    }
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(window);

	if (GLEW_OK != glewInit()) {
		cerr << "ERROR glewInit" << endl;
	}
    return window;
}

void dgl_make_main_window() {
    main_window = dgl_make_window();
}
