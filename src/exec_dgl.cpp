#include "exec.hpp"
#include "dgl-server.hpp"

//1499
 void EXEC_DGLSwapBuffers(char *commandbuf)
{
	SDL_GL_SwapWindow(dgl_main_window());
    // TODO payload: pushRet is a hack.
    // this sends a message with size 0 back.
    // client waits for it.
    pushRet((void*)1, 0);
}
