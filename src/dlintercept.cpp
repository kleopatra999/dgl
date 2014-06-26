/*******************************************************************************
	ClusterGL - dynamic library interception
*******************************************************************************/

#include <dlfcn.h>
#include <GL/glu.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

#define LOG printf

typedef unsigned char GLubyte;

/*
(notes on what this is and why, as it feels like something I'll forget)

Many apps use glxGetProcAddress() to load function pointers manually
This means they don't call our functions and so they don't get intercepted.

Apps obtain the address of glXGetProcAddress() through calling
dlopen("/usr/lib/libGL.so"), then dlsym("glxGetProcAddress") with that handle

We intercept dlsym(), and return our own copy of glXGetProcAddress() instead.
Our function uses RTLD_DEFAULT to return pointers to functions inside CGL. This
specifies local scope, instead of "go look in another library" scope, so our
functions are found instead of those in libGL

Note we have to use dlvsym() to look up the address to dlsym() in order to
handle the normal cases. TODO: is using "GLIBC_2.0" safe? Probably not.

*/

static void* (*o_dlsym) ( void *handle, const char *name )=0;

//Try lots of different glibc versions. In my testing, only one is ever valid,
//so it's okay to return the first one we find.
void find_dlsym(){

	char buf[32];

	int maxver = 40;

	//Works on Ubuntu
	for(int a=0;a<maxver;a++){
		sprintf(buf, "GLIBC_2.%d", a);

		o_dlsym = (void*(*)(void *handle, const char *name)) dlvsym(RTLD_NEXT,"dlsym", buf);

		if(o_dlsym){
			LOG("Using %s\n", buf);
			return;
		}
	}

	//Works on Debian
	for(int a=0;a<maxver;a++){
		for(int b=0;b<maxver;b++){
			sprintf(buf, "GLIBC_2.%d.%d", a, b);

			o_dlsym = (void*(*)(void *handle, const char *name)) dlvsym(RTLD_NEXT,"dlsym", buf);

			if(o_dlsym){
				LOG("Using %s\n", buf);
				return;
			}
		}
	}

}

static void *libGL() {
    static void *ptr;
    if (!ptr) {
        auto libgl_filename = "libGL.so.1";
        ptr = dlopen(libgl_filename, RTLD_GLOBAL | RTLD_LAZY);
    }
    return ptr;
}

static void *_glXGetProcAddressARB(const GLubyte *procName);
void *my_dlsym(void *handle, const char *name);

extern "C" void *glXGetProcAddress(const GLubyte *str) {
    return my_dlsym(RTLD_DEFAULT, (const char*)str);
}

extern "C" void *glXGetProcAddressARB(const GLubyte *str) {
    return my_dlsym(RTLD_DEFAULT, (const char*)str);
}



static void *_glXGetProcAddressARB(const GLubyte *procName) {
    typedef void *(*func_t)(const GLubyte *procName);
    static func_t   glXGetProcAddressARB;
    auto            name        = "glXGetProcAddressARB";
    if (!glXGetProcAddressARB) {
        glXGetProcAddressARB    = (func_t)my_dlsym(RTLD_NEXT, name);
    }
    return glXGetProcAddressARB(procName);
}


void *my_dlsym(void *handle, const char *name) {
    if(!o_dlsym){
		find_dlsym();
	}
    auto dlsym          = (*o_dlsym);
    auto sym            = dlsym(handle, name);
    auto err            = dlerror();
    if (err) {
        sym             = dlsym(libGL(), name);
        err             = dlerror();
    }
    if (err) {
        auto gl_name    = (const GLubyte *)name;
        sym             = _glXGetProcAddressARB(gl_name);
        err             = dlerror();
    }
    if (err) {
        printf("dlsym: %s\n", err);
    }
    return sym;
}

extern "C" void *dlsym(void *handle, const char *name){
    if (handle != RTLD_DEFAULT &&
        handle != RTLD_NEXT &&
        handle != libGL()) {
        return my_dlsym(handle, name);
    }
    if(strcmp(name, "glXGetProcAddressARB") == 0){
		return (void *)glXGetProcAddressARB;
	}
	if(strcmp(name, "glXGetProcAddress") == 0){
		return (void *)glXGetProcAddress;
	}
    return my_dlsym(RTLD_DEFAULT, name);
}
