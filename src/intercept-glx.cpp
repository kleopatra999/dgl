#include "libdgl.hpp"
#include <iostream>
#include <GL/glx.h>
#include <dlfcn.h>

using namespace std;

typedef int         (*glXMakeCurrent_t)
    (Display*, GLXDrawable, GLXContext);
typedef Display *   (*XOpenDisplay_t)
    (const char *);
typedef void        (*glXSwapBuffers_t)
    (Display *, GLXDrawable);

static glXMakeCurrent_t orig_glXMakeCurrent;
static XOpenDisplay_t   orig_XOpenDisplay;
static glXSwapBuffers_t orig_glXSwapBuffers;

static void my_dlsym_die() {
    auto err = dlerror();
    if (err) {
        cerr << "my_dlsym: " << err << endl;
        exit(1);
    }
}

//1604
extern "C" int glXMakeCurrent(
        Display *dpy,
        GLXDrawable drawable,
        GLXContext ctx) {
    if (!orig_glXMakeCurrent) {
        orig_glXMakeCurrent =
            (glXMakeCurrent_t)my_dlsym(RTLD_NEXT, "glXMakeCurrent");
        my_dlsym_die();
	}
	auto ret = (*orig_glXMakeCurrent) (dpy, drawable, ctx);
	if (!dgl_is_init()) {
		dgl_init();
	}
	return ret;
}


extern "C" Display *XOpenDisplay(const char *display_name) {
    if (!orig_XOpenDisplay) {
        orig_XOpenDisplay = 
            (XOpenDisplay_t)my_dlsym(RTLD_NEXT, "XOpenDisplay");
        my_dlsym_die();
    }
	auto ret = (*orig_XOpenDisplay)(display_name);
	if (!dgl_is_init()) {
		dgl_init();
	}
	return ret;
}


extern "C" void glXSwapBuffers(
        Display *dpy,
        GLXDrawable drawable) {
	if (!orig_glXSwapBuffers) {
		orig_glXSwapBuffers =
            (glXSwapBuffers_t)my_dlsym(RTLD_NEXT, "glXSwapBuffers");
        my_dlsym_die();
	}
	(*orig_glXSwapBuffers)(dpy, drawable);
    dgl_swap();
}



#ifdef NONE

//Pointer to glXChooseVisual
static XVisualInfo* (*_glXChooseVisual)(Display*, int, int*) = NULL;
//Pointer to glXCreateContext
static GLXContext (*_glXCreateContext)( Display*, XVisualInfo*, GLXContext, Bool) = NULL;
//Pointer to glXMakeCurrent
static Bool (*_glXMakeCurrent)( Display*, GLXDrawable, GLXContext) = NULL;
//Pointer to glXQueryExtensionsString
static const char * (*_glXQueryExtensionsString)( Display*, int) = NULL;

static const char * (*_glXQueryServerString)( Display*, int, int) = NULL;
//Pointer to glXGetProcAddressARB
static __GLXextFuncPtr (*_glXGetProcAddressARB)(const GLubyte *) = NULL;

static int (*_glXGetConfig) (Display*, XVisualInfo*, int, int*) = NULL;

static void (*_glXSwapBuffers) ( Display*, GLXDrawable) = NULL;




void * dlhandle;
//1601
extern "C" XVisualInfo* glXChooseVisual( Display *dpy, int screen, int *attribList )
{
//Set up our internals
if (!dgl_is_init()) {
    dgl_init();
}

if (_glXChooseVisual == NULL) {
dlhandle = dlopen("//usr/lib/libGL.so", RTLD_LAZY);
if (dlhandle==NULL) {
printf("//usr/lib/xorg/modules/extensions/libglx.so: %s\n", dlerror());
exit(0);
}
_glXChooseVisual = (XVisualInfo* (*)(Display*, int, int*)) my_dlsym(dlhandle, "glXChooseVisual");
}
if(!_glXChooseVisual) {
printf("Couldn't find glXChooseVisual: %s\n", dlerror());
exit(0);
}
return (*_glXChooseVisual) (dpy ,screen, attribList);
}


//1602
extern "C" GLXContext glXCreateContext( Display *dpy, XVisualInfo *vis, GLXContext shareList, Bool direct )
{
	if (_glXCreateContext == NULL) {
	_glXCreateContext = (GLXContext (*)(Display*, XVisualInfo*, GLXContext, Bool)) my_dlsym(dlhandle, "glXCreateContext");
	}
	if(!_glXCreateContext) {
	printf("Couldn't find glXCreateContext: %s\n", dlerror());
	exit(0);
	}
	return (*_glXCreateContext) (dpy, vis, shareList, direct);
}


//1603
extern "C" void glXDestroyContext( Display *dpy, GLXContext ctx )
{
LOG("Called unimplemted stub glXDestroyContext!\n");
}


//1604
extern "C" Bool glXMakeCurrent( Display *dpy, GLXDrawable drawable, GLXContext ctx)
{
	if (_glXMakeCurrent == NULL) {
	_glXMakeCurrent = (Bool (*)( Display*, GLXDrawable, GLXContext)) my_dlsym(dlhandle, "glXMakeCurrent");
	}
	if(!_glXMakeCurrent) {
	printf("Couldn't find glXMakeCurrent: %s\n", dlerror());
	exit(0);
	}
	Bool temp = (*_glXMakeCurrent) (dpy, drawable, ctx);
	//make camoflaged window appear
	if (_glXSwapBuffers == NULL) {
	_glXSwapBuffers = (void (*)(Display*, GLXDrawable)) my_dlsym(dlhandle, "glXSwapBuffers");
	if(!_glXSwapBuffers) {
	printf("Couldn't find glXSwapBuffers: %s\n", dlerror());
	exit(0);
	}
	}
	for(int i = 0; i < 3; i++)
	{
	(*_glXSwapBuffers) (dpy, drawable);
	}
	return temp;
}


//1605
extern "C" void glXCopyContext( Display *dpy, GLXContext src, GLXContext dst, unsigned long mask )
{
LOG("Called unimplemted stub glXCopyContext!\n");
}

//1606
extern "C" void glXSwapBuffers( Display *dpy, GLXDrawable drawable )
{
	pushOp(1499); //Swap buffers
	clearLocalCache();
	dgl_sync(buffer((void*)nullptr, 0));
}


//1607
extern "C" GLXPixmap glXCreateGLXPixmap( Display *dpy, XVisualInfo *visual, Pixmap pixmap )
{
LOG("Called unimplemted stub glXCreateGLXPixmap!\n");
}


//1608
extern "C" void glXDestroyGLXPixmap( Display *dpy, GLXPixmap pixmap )
{
LOG("Called unimplemted stub glXDestroyGLXPixmap!\n");
}


//1609
extern "C" Bool glXQueryExtension( Display *dpy, int *errorb, int *event )
{
LOG("Called unimplemted stub glXQueryExtension!\n");
}


//1610
extern "C" Bool glXQueryVersion( Display *dpy, int *maj, int *min )
{
LOG("Called unimplemted stub glXQueryVersion!\n");
}


//1611
extern "C" Bool glXIsDirect( Display *dpy, GLXContext ctx )
{
LOG("Called untested stub glXIsDirect!\n");
return false;
}


//1612
extern "C" int glXGetConfig( Display *dpy, XVisualInfo *visual, int attrib, int *value )
{
	if (_glXGetConfig == NULL) {
	_glXGetConfig = (int (*)(Display*, XVisualInfo*, int, int*)) my_dlsym(dlhandle, "glXGetConfig");
	}
	if(!_glXGetConfig) {
	printf("Couldn't find glXCreateContext: %s\n", dlerror());
	exit(0);
	}
	return (*_glXGetConfig) (dpy, visual, attrib, value);
}



/* HACK!
//1613
extern "C" GLXContext glXGetCurrentContext( void )
{
LOG("Called unimplemted stub glXGetCurrentContext!\n");
}
*/

//1614
extern "C" GLXDrawable glXGetCurrentDrawable( void )
{
LOG("Called unimplemted stub glXGetCurrentDrawable!\n");
}


//1615
extern "C" void glXWaitGL( void )
{
LOG("Called unimplemted stub glXWaitGL!\n");
}



//1616
extern "C" void glXWaitX( void )
{
LOG("Called unimplemted stub glXWaitX!\n");
}


//1617
extern "C" void glXUseXFont( Font font, int first, int count, int list )
{
LOG("Called unimplemted stub glXUseXFont!\n");
}


//GLX 1.1 and later
//1618
extern "C" const char *glXQueryExtensionsString( Display *dpy, int screen )
{
	if (_glXQueryExtensionsString == NULL) {
	_glXQueryExtensionsString = (const char * (*)( Display*, int)) my_dlsym(dlhandle, "glXQueryExtensionsString");
	}
	if(!_glXQueryExtensionsString) {
	printf("Couldn't find glXQueryExtensionsString: %s\n", dlerror());
	exit(0);
	}
	return (*_glXQueryExtensionsString) (dpy, screen);

}
//1619
extern "C" const char *glXQueryServerString( Display *dpy, int screen, int name ) {
	if (_glXQueryServerString == NULL) {
	_glXQueryServerString = (const char * (*)( Display*, int, int)) my_dlsym(dlhandle, "glXQueryServerString");
	}
	if(!_glXQueryServerString) {
	printf("Couldn't find glXQueryServerString: %s\n", dlerror());
	exit(0);
	}
	return (*_glXQueryServerString) (dpy, screen, name);

}

//1620
extern "C" const char *glXGetClientString( Display *dpy, int name ) {
LOG("Called unimplemted stub glXGetClientString!\n");
}

// GLX 1.2 and later
//1621
extern "C" Display *glXGetCurrentDisplay( void ) {
LOG("Called unimplemted stub glXGetCurrentDisplay!\n");
}

// GLX 1.3 and later
//1622
extern "C" GLXFBConfig *glXChooseFBConfig( Display *dpy, int screen, const int *attribList, int *nitems ) {
LOG("Called unimplemted stub glXChooseFBConfig!\n");
}

//1623
extern "C" int glXGetFBConfigAttrib( Display *dpy, GLXFBConfig config, int attribute, int *value ) {
LOG("Called unimplemted stub glXGetFBConfigAttrib!\n");
}

//1624
extern "C" GLXFBConfig *glXGetFBConfigs( Display *dpy, int screen, int *nelements ) {
LOG("Called unimplemted stub glXGetFBConfigs!\n");
}

//1625
extern "C" XVisualInfo *glXGetVisualFromFBConfig( Display *dpy, GLXFBConfig config ) {
LOG("Called unimplemted stub glXGetVisualFromFBConfig!\n");
}

//1626
extern "C" GLXWindow glXCreateWindow( Display *dpy, GLXFBConfig config, Window win, const int *attribList ) {
LOG("Called unimplemted stub glXCreateWindow!\n");
}

//1627
extern "C" void glXDestroyWindow( Display *dpy, GLXWindow window ) {
LOG("Called unimplemted stub glXDestroyWindow!\n");
}

//1628
extern "C" GLXPixmap glXCreatePixmap( Display *dpy, GLXFBConfig config, Pixmap pixmap, const int *attribList ) {
LOG("Called unimplemted stub glXCreatePixmap!\n");
}

//1629
extern "C" void glXDestroyPixmap( Display *dpy, GLXPixmap pixmap ) {
LOG("Called unimplemted stub glXDestroyPixmap!\n");
}

//1630
extern "C" GLXPbuffer glXCreatePbuffer( Display *dpy, GLXFBConfig config, const int *attribList ) {
LOG("Called unimplemted stub glXCreatePbuffer!\n");
}

//1631
extern "C" void glXDestroyPbuffer( Display *dpy, GLXPbuffer pbuf ) {
LOG("Called unimplemted stub glXDestroyPbuffer!\n");
}

//1632
extern "C" void glXQueryDrawable( Display *dpy, GLXDrawable draw, int attribute, unsigned int *value ) {
LOG("Called unimplemted stub glXQueryDrawable!\n");
}

//1633
extern "C" GLXContext glXCreateNewContext( Display *dpy, GLXFBConfig config, int renderType, GLXContext shareList, Bool direct ) {
LOG("Called unimplemted stub glXCreateNewContext!\n");
}

//1634
extern "C" Bool glXMakeContextCurrent( Display *dpy, GLXDrawable draw, GLXDrawable read, GLXContext ctx ) {
LOG("Called unimplemted stub glXMakeContextCurrent!\n");
}

//1635
extern "C" GLXDrawable glXGetCurrentReadDrawable( void ) {
LOG("Called unimplemted stub glXGetCurrentReadDrawable!\n");
}

//1636
extern "C" int glXQueryContext( Display *dpy, GLXContext ctx, int attribute, int *value ) {
LOG("Called unimplemted stub glXQueryContext!\n");
}

//1637
extern "C" void glXSelectEvent( Display *dpy, GLXDrawable drawable, unsigned long mask ) {
LOG("Called unimplemted stub glXSelectEvent!\n");
}

//1638
extern "C" void glXGetSelectedEvent( Display *dpy, GLXDrawable drawable, unsigned long *mask ) {
LOG("Called unimplemted stub glXGetSelectedEvent!\n");
}

//1639
extern "C" __GLXextFuncPtr glXGetProcAddressARB (const GLubyte * str) {
	//printf("finding: %s\n", str);
	      char *path = NULL;
	      size_t size = 0;
	      path = getcwd(path,size);
	      char *fullPath = (char *)calloc(strlen(path) + strlen("/libGL.so.1") + 1, sizeof(char));
	      strcat(fullPath, path);
	      strcat(fullPath, "/libGL.so.1");
	      handle = dlopen(fullPath, RTLD_LOCAL | RTLD_LAZY);

	return (__GLXextFuncPtr) my_dlsym(handle, (char *) str);
	/*
	dlhandle = dlopen("libGL.so", RTLD_LAZY);

	if (_glXGetProcAddressARB == NULL) {
		_glXGetProcAddressARB = (__GLXextFuncPtr (*)(const GLubyte *))  my_dlsym(dlhandle, "glXGetProcAddressARB");
	}
	if(!_glXGetProcAddressARB) {
		printf("Couldn't find glXGetProcAddressARB: %s\n", dlerror());
		exit(0);
	}
	return  (*_glXGetProcAddressARB) (str); */
}

//1640
extern "C" void (*glXGetProcAddress(const GLubyte *procname))( void ) {
LOG("Called unimplemted stub glXGetProcAddress!\n");
}

//1641
extern "C" void *glXAllocateMemoryNV(GLsizei size, GLfloat readfreq, GLfloat writefreq, GLfloat priority) {
LOG("Called unimplemted stub glXAllocateMemoryNV!\n");
}

//1642
extern "C" void glXFreeMemoryNV(GLvoid *pointer) {
LOG("Called unimplemted stub glXFreeMemoryNV!\n");
}

//1643
extern "C" void *glXAllocateMemoryMESA(Display *dpy, int scrn, size_t size, float readfreq, float writefreq, float priority) {
LOG("Called unimplemted stub glXAllocateMemoryMESA!\n");
}

//1644
extern "C" void glXFreeMemoryMESA(Display *dpy, int scrn, void *pointer) {
LOG("Called unimplemted stub glXFreeMemoryMESA!\n");
}

//1645
extern "C" GLuint glXGetMemoryOffsetMESA(Display *dpy, int scrn, const void *pointer) {
LOG("Called unimplemted stub glXGetMemoryOffsetMESA!\n");
}

//1646
extern "C" Bool glXBindTexImageARB(Display *dpy, GLXPbuffer pbuffer, int buffer) {
LOG("Called unimplemted stub glXBindTexImageARB!\n");
}
//1647
extern "C" Bool glXReleaseTexImageARB(Display *dpy, GLXPbuffer pbuffer, int buffer) {
LOG("Called unimplemted stub glXReleaseTexImageARB!\n");
}
//1648
extern "C" Bool glXDrawableAttribARB(Display *dpy, GLXDrawable draw, const int *attribList) {
LOG("Called unimplemted stub glXDrawableAttribARB!\n");
}

//1649
extern "C" int glXGetFrameUsageMESA(Display *dpy, GLXDrawable drawable, float *usage) {
LOG("Called unimplemted stub glXGetFrameUsageMESA!\n");
}

//1650
extern "C" int glXBeginFrameTrackingMESA(Display *dpy, GLXDrawable drawable) {
LOG("Called unimplemted stub glXBeginFrameTrackingMESA!\n");
}

//1651
extern "C" int glXEndFrameTrackingMESA(Display *dpy, GLXDrawable drawable) {
LOG("Called unimplemted stub glXEndFrameTrackingMESA!\n");
}
//1652
extern "C" int glXQueryFrameTrackingMESA(Display *dpy, GLXDrawable drawable, int64_t *swapCount, int64_t *missedFrames, float *lastMissedUsage) {
LOG("Called unimplemted stub glXQueryFrameTrackingMESA!\n");
}

//1653
extern "C" int glXSwapIntervalMESA(unsigned int interval) {
    pushOp(1653);
    pushParam(interval);
    // TODO payload: return is error code, ignoring
    return 0;
}

//1654
extern "C" int glXGetSwapIntervalMESA() {
    pushOp(1654);
    int ret;
    pushBuf(&ret, sizeof(ret), true);
    waitForReturn();
    return ret;
}

//1655
extern "C" void glXBindTexImageEXT(Display *dpy, GLXDrawable drawable, int buffer, const int *attrib_list) {
LOG("Called unimplemted stub glXBindTexImageEXT!\n");
}

//1656
extern "C" void glXReleaseTexImageEXT(Display *dpy, GLXDrawable drawable, int buffer) {
LOG("Called unimplemted stub glXReleaseTexImageEXT!\n");
}

#endif
