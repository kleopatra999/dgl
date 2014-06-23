/*******************************************************************************
	mod_exec - this unpacks and executes the GL instructions. It also creates
	a SDL window to render to
*******************************************************************************/

#include "instruction.hpp"
#include "exec_gl.hpp"
#include "exec_glu.hpp"
#include "exec_glx.hpp"
#include "exec_dgl.hpp"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/glxew.h>

#include "consts.hpp"

#define LOG(x...)

/*******************************************************************************
	Globals
*******************************************************************************/

ExecFunc _dgl_functions[1700];

struct {
    string  id          = "summer";
    int     sizeX       = 300;
    int     sizeY       = 300;
    float   scaleX      = 1;
    float   scaleY      = 1;
    int     positionX   = 300;
    int     positionY   = 30;
    
} config;

auto *gConfig = &config;

/*******************************************************************************
	Module
*******************************************************************************/
void dgl_make_window();
void init_functions();

void init_mod_exec() {
    init_functions();
    dgl_make_window();
}

/*********************************************************
	Method Pointers
*********************************************************/


