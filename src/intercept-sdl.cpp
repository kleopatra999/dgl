
//SDL functors
static int (*_SDL_Init)(unsigned int flags) = NULL;
static SDL_Surface* (*_SDL_SetVideoMode)(int, int, int, unsigned int) = NULL;
static void * (*_SDL_GL_GetProcAddress)(const char* proc) = NULL;
static int (*_SDL_GL_LoadLibrary)(const char *) = NULL;
static SDL_Rect ** (*_SDL_ListModes)(SDL_PixelFormat *format, Uint32 flags) = NULL;

#ifndef __APPLE__

//X functors
#include <X11/Xlib.h>

static Display *(*_XOpenDisplay)(const char *) = NULL;
static void (*_glXSwapBuffers) ( Display*, GLXDrawable) = NULL;
static int (*_glXMakeCurrent)( Display*, GLXDrawable, GLXContext) = NULL;

#endif

//handle to point to our own library
void *handle = NULL;

bool bHasMinimized = false;


extern "C" int SDL_Init(unsigned int flags) {

	LOG("SDL_Init (dgl_is_init = %d)\n", dgl_is_init());
	if (_SDL_Init == NULL) {
		_SDL_Init = (int (*)(unsigned int)) dlsym(RTLD_NEXT, "SDL_Init");
	}

	if(!_SDL_Init){
		printf("Couldn't find SDL_Init: %s\n", dlerror());
		exit(0);
	}

	int r = (*_SDL_Init)(flags);

	//Set up our internals
	if (!dgl_is_init()) {
		dgl_init("sdl");
	} else {
		LOG("Ignored a second/non-video SDL_Init()\n");
	}

	//LOG("SDL_Init finished\n");
	return r;
}

extern "C" void SDL_GL_SwapBuffers( ) {

	//if(!bHasMinimized){
	// if (SDL_WM_IconifyWindow()==0)
	//	LOG("Could not minimize Window\n");
	//  bHasMinimized = true;
	//}


	pushOp(1499); //Swap buffers

	clearLocalCache();

	dgl_sync(buffer((void*)nullptr, 0));
}


/*
extern "C" SDL_Surface* SDL_SetVideoMode(int width, int height, int bpp, unsigned int videoFlags) {
	if (_SDL_SetVideoMode == NULL) {
		_SDL_SetVideoMode = (SDL_Surface* (*)(int,int,int,unsigned int)) dlsym(RTLD_NEXT, "SDL_SetVideoMode");
	}
	if(!_SDL_SetVideoMode){
		printf("Couldn't find SDL_SetVideoMode: %s\n", dlerror());
		exit(0);
	}
	//make a fake window
	return (*_SDL_SetVideoMode)(gConfig->fakeWindowX, gConfig->fakeWindowY, bpp, videoFlags );
}

extern "C" SDL_Rect **  SDL_ListModes(SDL_PixelFormat *format, Uint32 flags) {
	// -1 means any mode is supported (easier than adding symphony values to list)
	return (SDL_Rect **) -1;
}
*/

/*
extern "C" int SDL_GL_LoadLibrary(const char *path) {
	LOG("*SDL_GL_LoadLibrary called, searching for: %s!\n", path);
	return -1;
}*/


/*
extern "C" void *SDL_GL_GetProcAddress(const char* proc) {
	LOG("*SDL_GL_GetProcAddress finding: %s!\n", proc);
      if(!handle) {
	      char *path = NULL;
	      size_t size = 0;
	      path = getcwd(path,size);
	      char *fullPath = (char *)calloc(strlen(path) + strlen("/libGL.so.1") + 1, sizeof(char));
	      strcat(fullPath, path);
	      strcat(fullPath, "/libGL.so.1");
	      handle = dlopen(fullPath, RTLD_LOCAL | RTLD_LAZY);
	}

	if(!dlsym(handle, proc)) {
		LOG("*SDL_GL_GetProcAddress failed finding: %s!\n", proc);
		return NULL;
	}

	return dlsym(handle, proc);
}

extern "C" void SDL_GL_SwapBuffers( ) {

	//if(!bHasMinimized){
	// if (SDL_WM_IconifyWindow()==0)
	//	LOG("Could not minimize Window\n");
	//  bHasMinimized = true;
	//}


	pushOp(1499); //Swap buffers

	if(!theApp->tick()){
		exit(1);
	}
}
*/

