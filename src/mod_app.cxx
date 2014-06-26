/*******************************************************************************
	ClusterGL - Application intercept module
*******************************************************************************/

#include "libdgl.hpp"
#include "instruction.hpp"
#include "consts.hpp"

#include <map>
#include <vector>
#include <iostream>
#include <dlfcn.h>
#include <GL/gl.h>
#include <boost/asio.hpp>

#ifdef __APPLE__
	#include <SDL/SDL_opengl.h>
#else
	#include <GL/gl.h>
	#include <GL/glx.h>
	#include <GL/glu.h>
#endif

#include <SDL/SDL.h>
#include <SDL/SDL_net.h>
#include <SDL/SDL_thread.h>
#include <SDL/SDL_mutex.h>
#include <SDL/SDL_syswm.h>

using namespace std;
using namespace boost::asio;

//Some left-over bradenisms
#define NO_TEX_ENV
//#define  GLXFULL
//#define  GLUFULL

#define LOG printf


/*********************************************************
	Interception Module Stuff
*********************************************************/

void init_mod_app() {
	//initialize values and structures
	for(int i=0;i<GL_MAX_TEXTURES;i++){
		rpTex[i].size = (GLint) NULL;
	}
	rpVert.size = (GLint) NULL;
	rpCol.size = (GLint) NULL;
	rpInter.size = (GLint) NULL;
	rpNormals.size = (GLint) NULL;
}

/*********************************************************
	Interception Global Functions
*********************************************************/



/*********************************************************
	Send Pointers Given Size
*********************************************************/



/********************************************************
	SDL Intercepts
********************************************************/

/********************************************************
	X Exports
********************************************************/

#ifndef __APPLE__


#endif


/********************************************************
GLX Intercepts
********************************************************/

#endif

