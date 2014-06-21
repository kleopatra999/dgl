/*******************************************************************************
	mod_exec - this unpacks and executes the GL instructions. It also creates
	a SDL window to render to
*******************************************************************************/

#include "instruction.hpp"

#include <SDL/SDL.h>
#include <GL/glew.h>

#include "consts.hpp"

#define LOG(x...)

typedef void (*ExecFunc)(char *buf);

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

void dgl_make_window() {
	const SDL_VideoInfo *videoInfo;

	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		LOG( "Video initialization failed: %s\n", SDL_GetError());
		return;
	}


	string title = "ClusterGL Output - " + gConfig->id;

	LOG("Set caption: %s\n", title.c_str());

	SDL_WM_SetCaption(title.c_str(), title.c_str());

	videoInfo = SDL_GetVideoInfo( );

	int videoFlags;

	//the flags to pass to SDL_SetVideoMode
	videoFlags  = SDL_OPENGL;
	videoFlags |= SDL_GL_DOUBLEBUFFER;
	videoFlags |= SDL_HWPALETTE;
	//videoFlags |= SDL_NOFRAME;

	if(videoInfo->hw_available ){
		videoFlags |= SDL_HWSURFACE;
	}else{
		videoFlags |= SDL_SWSURFACE;
	}

	if(videoInfo->blit_hw ){
		videoFlags |= SDL_HWACCEL;
	}

	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	//Autodetect res
	int width = gConfig->sizeX*gConfig->scaleX;
	int height = gConfig->sizeY*gConfig->scaleY;

	//set window position
	std::stringstream stream;
	stream <<gConfig->positionX<<","<<gConfig->positionY;
	setenv("SDL_VIDEO_WINDOW_POS", stream.str().c_str(), true);

	//get a SDL surface
	SDL_Surface *surface = SDL_SetVideoMode(width, height, 32, videoFlags );

	if ( !surface ) {
		LOG( "Video mode set failed: %s\n", SDL_GetError());
		return;
	}

	//Disable mouse pointer
	//SDL_ShowCursor(SDL_DISABLE);

	//Do this twice - above works for OSX, here for Linux
	//Yeah, I know.
	SDL_WM_SetCaption(title.c_str(), title.c_str());


	if (GLEW_OK != glewInit()) {
		LOG("GLEW failed to start up for some reason\n");
		return;
	}
}


/*
char *popBuf()
{
	currentBuffer++;
	return mCurrentInstruction->buffers[currentBuffer-1].buffer;
    return nullptr;
}
*/

#define popBuf() (commandbuf)

/*
char *popBuf(int *len){
    
	*len = mCurrentInstruction->buffers[currentBuffer].len;
	currentBuffer++;
	return mCurrentInstruction->buffers[currentBuffer-1].buffer;
    return nullptr;
}
*/

void       *_dgl_pushRet_ptr  = nullptr;
uint32_t    _dgl_pushRet_size = 0;

template<typename T>
void pushRet(T val) {
    _dgl_pushRet_size   = sizeof(T);
    _dgl_pushRet_ptr    = (void*)new T(val);
}

/*******************************************************************************
	CGL special functions
*******************************************************************************/

//1499
static void EXEC_CGLSwapBuffers(char *commandbuf)
{
	SDL_GL_SwapBuffers();
    // TODO payload: pushRet is a hack.
    // this sends a message with size 0 back.
    // client waits for it.
    _dgl_pushRet_ptr    = (void*)1;
    _dgl_pushRet_size   = 0;
}


/*******************************************************************************
	Regular OpenGL functions
*******************************************************************************/

//0
static void EXEC_glNewList(char *commandbuf)
{
	GLuint *list = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glNewList(*list, *mode);
}


//1
static void EXEC_glEndList(char *commandbuf)
{

	glEndList();
}


//2
static void EXEC_glCallList(char *commandbuf)
{
	GLuint *list = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

	glCallList(*list);
}


//3
static void EXEC_glCallLists(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	//LOG("glCallLists(%d, %d)\n", *n, *type);

	glCallLists(*n, *type, (const GLvoid *)popBuf());
}


//4
static void EXEC_glDeleteLists(char *commandbuf)
{
	GLuint *list = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);
	GLsizei *range = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glDeleteLists(*list, *range);
}


//5
static void EXEC_glGenLists(char *commandbuf)
{
	GLsizei *range = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	pushRet(glGenLists(*range));
}


//6
static void EXEC_glListBase(char *commandbuf)
{
	GLuint *base = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

	glListBase(*base);
}


//7
static void EXEC_glBegin(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	glBegin(*mode);
}


//8
static void EXEC_glBitmap(char *commandbuf)
{
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLfloat *xorig = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *yorig = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *xmove = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *ymove = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glBitmap(*width, *height, *xorig, *yorig, *xmove, *ymove, (const GLubyte *)popBuf());
}


//9
static void EXEC_glColor3b(char *commandbuf)
{
	GLbyte *red = (GLbyte*)commandbuf;   commandbuf += sizeof(GLbyte);
	GLbyte *green = (GLbyte*)commandbuf;     commandbuf += sizeof(GLbyte);
	GLbyte *blue = (GLbyte*)commandbuf;  commandbuf += sizeof(GLbyte);

	glColor3b(*red, *green, *blue);
}


//10
static void EXEC_glColor3bv(char *commandbuf)
{

	glColor3bv((const GLbyte *)popBuf());
}


//11
static void EXEC_glColor3d(char *commandbuf)
{
	GLdouble *red = (GLdouble*)commandbuf;   commandbuf += sizeof(GLdouble);
	GLdouble *green = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *blue = (GLdouble*)commandbuf;  commandbuf += sizeof(GLdouble);

	glColor3d(*red, *green, *blue);
}


//12
static void EXEC_glColor3dv(char *commandbuf)
{

	glColor3dv((const GLdouble *)popBuf());
}


//13
static void EXEC_glColor3f(char *commandbuf)
{
	GLfloat *red = (GLfloat*)commandbuf;     commandbuf += sizeof(GLfloat);
	GLfloat *green = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *blue = (GLfloat*)commandbuf;    commandbuf += sizeof(GLfloat);

	glColor3f(*red, *green, *blue);
}


//14
static void EXEC_glColor3fv(char *commandbuf)
{

	glColor3fv((const GLfloat *)popBuf());
}


//15
static void EXEC_glColor3i(char *commandbuf)
{
	GLint *red = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *green = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *blue = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glColor3i(*red, *green, *blue);
}


//16
static void EXEC_glColor3iv(char *commandbuf)
{

	glColor3iv((const GLint *)popBuf());
}


//17
static void EXEC_glColor3s(char *commandbuf)
{
	GLshort *red = (GLshort*)commandbuf;     commandbuf += sizeof(GLshort);
	GLshort *green = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *blue = (GLshort*)commandbuf;    commandbuf += sizeof(GLshort);

	glColor3s(*red, *green, *blue);
}


//18
static void EXEC_glColor3sv(char *commandbuf)
{

	glColor3sv((const GLshort *)popBuf());
}


//19
static void EXEC_glColor3ub(char *commandbuf)
{
	GLubyte *red = (GLubyte*)commandbuf;     commandbuf += sizeof(GLubyte);
	GLubyte *green = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *blue = (GLubyte*)commandbuf;    commandbuf += sizeof(GLubyte);

	glColor3ub(*red, *green, *blue);
}


//20
static void EXEC_glColor3ubv(char *commandbuf)
{

	glColor3ubv((const GLubyte *)popBuf());
}


//21
static void EXEC_glColor3ui(char *commandbuf)
{
	GLuint *red = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *green = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLuint *blue = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

	glColor3ui(*red, *green, *blue);
}


//22
static void EXEC_glColor3uiv(char *commandbuf)
{

	glColor3uiv((const GLuint *)popBuf());
}


//23
static void EXEC_glColor3us(char *commandbuf)
{
	GLushort *red = (GLushort*)commandbuf;   commandbuf += sizeof(GLushort);
	GLushort *green = (GLushort*)commandbuf;     commandbuf += sizeof(GLushort);
	GLushort *blue = (GLushort*)commandbuf;  commandbuf += sizeof(GLushort);

	glColor3us(*red, *green, *blue);
}


//24
static void EXEC_glColor3usv(char *commandbuf)
{

	glColor3usv((const GLushort *)popBuf());
}


//25
static void EXEC_glColor4b(char *commandbuf)
{
	GLbyte *red = (GLbyte*)commandbuf;   commandbuf += sizeof(GLbyte);
	GLbyte *green = (GLbyte*)commandbuf;     commandbuf += sizeof(GLbyte);
	GLbyte *blue = (GLbyte*)commandbuf;  commandbuf += sizeof(GLbyte);
	GLbyte *alpha = (GLbyte*)commandbuf;     commandbuf += sizeof(GLbyte);

	glColor4b(*red, *green, *blue, *alpha);
}


//26
static void EXEC_glColor4bv(char *commandbuf)
{

	glColor4bv((const GLbyte *)popBuf());
}


//27
static void EXEC_glColor4d(char *commandbuf)
{
	GLdouble *red = (GLdouble*)commandbuf;   commandbuf += sizeof(GLdouble);
	GLdouble *green = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *blue = (GLdouble*)commandbuf;  commandbuf += sizeof(GLdouble);
	GLdouble *alpha = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glColor4d(*red, *green, *blue, *alpha);
}


//28
static void EXEC_glColor4dv(char *commandbuf)
{

	glColor4dv((const GLdouble *)popBuf());
}


//29
static void EXEC_glColor4f(char *commandbuf)
{
	GLfloat *red = (GLfloat*)commandbuf;     commandbuf += sizeof(GLfloat);
	GLfloat *green = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *blue = (GLfloat*)commandbuf;    commandbuf += sizeof(GLfloat);
	GLfloat *alpha = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glColor4f(*red, *green, *blue, *alpha);
}


//30
static void EXEC_glColor4fv(char *commandbuf)
{

	glColor4fv((const GLfloat *)popBuf());
}


//31
static void EXEC_glColor4i(char *commandbuf)
{
	GLint *red = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *green = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *blue = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLint *alpha = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glColor4i(*red, *green, *blue, *alpha);
}


//32
static void EXEC_glColor4iv(char *commandbuf)
{

	glColor4iv((const GLint *)popBuf());
}


//33
static void EXEC_glColor4s(char *commandbuf)
{
	GLshort *red = (GLshort*)commandbuf;     commandbuf += sizeof(GLshort);
	GLshort *green = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *blue = (GLshort*)commandbuf;    commandbuf += sizeof(GLshort);
	GLshort *alpha = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glColor4s(*red, *green, *blue, *alpha);
}


//34
static void EXEC_glColor4sv(char *commandbuf)
{

	glColor4sv((const GLshort *)popBuf());
}


//35
static void EXEC_glColor4ub(char *commandbuf)
{
	GLubyte *red = (GLubyte*)commandbuf;     commandbuf += sizeof(GLubyte);
	GLubyte *green = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *blue = (GLubyte*)commandbuf;    commandbuf += sizeof(GLubyte);
	GLubyte *alpha = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);

	glColor4ub(*red, *green, *blue, *alpha);
}


//36
static void EXEC_glColor4ubv(char *commandbuf)
{

	glColor4ubv((const GLubyte *)popBuf());
}


//37
static void EXEC_glColor4ui(char *commandbuf)
{
	GLuint *red = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *green = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLuint *blue = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);
	GLuint *alpha = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glColor4ui(*red, *green, *blue, *alpha);
}


//38
static void EXEC_glColor4uiv(char *commandbuf)
{

	glColor4uiv((const GLuint *)popBuf());
}


//39
static void EXEC_glColor4us(char *commandbuf)
{
	GLushort *red = (GLushort*)commandbuf;   commandbuf += sizeof(GLushort);
	GLushort *green = (GLushort*)commandbuf;     commandbuf += sizeof(GLushort);
	GLushort *blue = (GLushort*)commandbuf;  commandbuf += sizeof(GLushort);
	GLushort *alpha = (GLushort*)commandbuf;     commandbuf += sizeof(GLushort);

	glColor4us(*red, *green, *blue, *alpha);
}


//40
static void EXEC_glColor4usv(char *commandbuf)
{

	glColor4usv((const GLushort *)popBuf());
}


//41
static void EXEC_glEdgeFlag(char *commandbuf)
{
	GLboolean *flag = (GLboolean*)commandbuf;    commandbuf += sizeof(GLboolean);

	glEdgeFlag(*flag);
}


//42
static void EXEC_glEdgeFlagv(char *commandbuf)
{

	glEdgeFlagv((const GLboolean *)popBuf());
}


//43
static void EXEC_glEnd(char *commandbuf)
{

	glEnd();
}


//44
static void EXEC_glIndexd(char *commandbuf)
{
	GLdouble *c = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glIndexd(*c);
}


//45
static void EXEC_glIndexdv(char *commandbuf)
{

	glIndexdv((const GLdouble *)popBuf());
}


//46
static void EXEC_glIndexf(char *commandbuf)
{
	GLfloat *c = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glIndexf(*c);
}


//47
static void EXEC_glIndexfv(char *commandbuf)
{

	glIndexfv((const GLfloat *)popBuf());
}


//48
static void EXEC_glIndexi(char *commandbuf)
{
	GLint *c = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glIndexi(*c);
}


//49
static void EXEC_glIndexiv(char *commandbuf)
{

	glIndexiv((const GLint *)popBuf());
}


//50
static void EXEC_glIndexs(char *commandbuf)
{
	GLshort *c = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glIndexs(*c);
}


//51
static void EXEC_glIndexsv(char *commandbuf)
{

	glIndexsv((const GLshort *)popBuf());
}


//52
static void EXEC_glNormal3b(char *commandbuf)
{
	GLbyte *nx = (GLbyte*)commandbuf;    commandbuf += sizeof(GLbyte);
	GLbyte *ny = (GLbyte*)commandbuf;    commandbuf += sizeof(GLbyte);
	GLbyte *nz = (GLbyte*)commandbuf;    commandbuf += sizeof(GLbyte);

	glNormal3b(*nx, *ny, *nz);
}


//53
static void EXEC_glNormal3bv(char *commandbuf)
{

	glNormal3bv((const GLbyte *)popBuf());
}


//54
static void EXEC_glNormal3d(char *commandbuf)
{
	GLdouble *nx = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *ny = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *nz = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);

	glNormal3d(*nx, *ny, *nz);
}


//55
static void EXEC_glNormal3dv(char *commandbuf)
{

	glNormal3dv((const GLdouble *)popBuf());
}


//56
static void EXEC_glNormal3f(char *commandbuf)
{
	GLfloat *nx = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *ny = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *nz = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	glNormal3f(*nx, *ny, *nz);
}


//57
static void EXEC_glNormal3fv(char *commandbuf)
{

	glNormal3fv((const GLfloat *)popBuf());
}


//58
static void EXEC_glNormal3i(char *commandbuf)
{
	GLint *nx = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *ny = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *nz = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glNormal3i(*nx, *ny, *nz);
}


//59
static void EXEC_glNormal3iv(char *commandbuf)
{

	glNormal3iv((const GLint *)popBuf());
}


//60
static void EXEC_glNormal3s(char *commandbuf)
{
	GLshort *nx = (GLshort*)commandbuf;  commandbuf += sizeof(GLshort);
	GLshort *ny = (GLshort*)commandbuf;  commandbuf += sizeof(GLshort);
	GLshort *nz = (GLshort*)commandbuf;  commandbuf += sizeof(GLshort);

	glNormal3s(*nx, *ny, *nz);
}


//61
static void EXEC_glNormal3sv(char *commandbuf)
{

	glNormal3sv((const GLshort *)popBuf());
}


//62
static void EXEC_glRasterPos2d(char *commandbuf)
{
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glRasterPos2d(*x, *y);
}


//63
static void EXEC_glRasterPos2dv(char *commandbuf)
{

	glRasterPos2dv((const GLdouble *)popBuf());
}


//64
static void EXEC_glRasterPos2f(char *commandbuf)
{
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glRasterPos2f(*x, *y);
}


//65
static void EXEC_glRasterPos2fv(char *commandbuf)
{

	glRasterPos2fv((const GLfloat *)popBuf());
}


//66
static void EXEC_glRasterPos2i(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glRasterPos2i(*x, *y);
}


//67
static void EXEC_glRasterPos2iv(char *commandbuf)
{

	glRasterPos2iv((const GLint *)popBuf());
}


//68
static void EXEC_glRasterPos2s(char *commandbuf)
{
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glRasterPos2s(*x, *y);
}


//69
static void EXEC_glRasterPos2sv(char *commandbuf)
{

	glRasterPos2sv((const GLshort *)popBuf());
}


//70
static void EXEC_glRasterPos3d(char *commandbuf)
{
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glRasterPos3d(*x, *y, *z);
}


//71
static void EXEC_glRasterPos3dv(char *commandbuf)
{

	glRasterPos3dv((const GLdouble *)popBuf());
}


//72
static void EXEC_glRasterPos3f(char *commandbuf)
{
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glRasterPos3f(*x, *y, *z);
}


//73
static void EXEC_glRasterPos3fv(char *commandbuf)
{

	glRasterPos3fv((const GLfloat *)popBuf());
}


//74
static void EXEC_glRasterPos3i(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *z = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glRasterPos3i(*x, *y, *z);
}


//75
static void EXEC_glRasterPos3iv(char *commandbuf)
{

	glRasterPos3iv((const GLint *)popBuf());
}


//76
static void EXEC_glRasterPos3s(char *commandbuf)
{
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *z = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glRasterPos3s(*x, *y, *z);
}


//77
static void EXEC_glRasterPos3sv(char *commandbuf)
{

	glRasterPos3sv((const GLshort *)popBuf());
}


//78
static void EXEC_glRasterPos4d(char *commandbuf)
{
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *w = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glRasterPos4d(*x, *y, *z, *w);
}


//79
static void EXEC_glRasterPos4dv(char *commandbuf)
{

	glRasterPos4dv((const GLdouble *)popBuf());
}


//80
static void EXEC_glRasterPos4f(char *commandbuf)
{
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *w = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glRasterPos4f(*x, *y, *z, *w);
}


//81
static void EXEC_glRasterPos4fv(char *commandbuf)
{

	glRasterPos4fv((const GLfloat *)popBuf());
}


//82
static void EXEC_glRasterPos4i(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *z = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *w = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glRasterPos4i(*x, *y, *z, *w);
}


//83
static void EXEC_glRasterPos4iv(char *commandbuf)
{

	glRasterPos4iv((const GLint *)popBuf());
}


//84
static void EXEC_glRasterPos4s(char *commandbuf)
{
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *z = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *w = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glRasterPos4s(*x, *y, *z, *w);
}


//85
static void EXEC_glRasterPos4sv(char *commandbuf)
{

	glRasterPos4sv((const GLshort *)popBuf());
}


//86
static void EXEC_glRectd(char *commandbuf)
{
	GLdouble *x1 = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *y1 = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *x2 = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *y2 = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);

	glRectd(*x1, *y1, *x2, *y2);
}


//87
static void EXEC_glRectdv(char *commandbuf)
{

	glRectdv((const GLdouble *)popBuf(), (const GLdouble *)popBuf());
}


//88
static void EXEC_glRectf(char *commandbuf)
{
	GLfloat *x1 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *y1 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *x2 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *y2 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	glRectf(*x1, *y1, *x2, *y2);
}


//89
static void EXEC_glRectfv(char *commandbuf)
{

	glRectfv((const GLfloat *)popBuf(), (const GLfloat *)popBuf());
}


//90
static void EXEC_glRecti(char *commandbuf)
{
	GLint *x1 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *y1 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *x2 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *y2 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glRecti(*x1, *y1, *x2, *y2);
}


//91
static void EXEC_glRectiv(char *commandbuf)
{

	glRectiv((const GLint *)popBuf(), (const GLint *)popBuf());
}


//92
static void EXEC_glRects(char *commandbuf)
{
	GLshort *x1 = (GLshort*)commandbuf;  commandbuf += sizeof(GLshort);
	GLshort *y1 = (GLshort*)commandbuf;  commandbuf += sizeof(GLshort);
	GLshort *x2 = (GLshort*)commandbuf;  commandbuf += sizeof(GLshort);
	GLshort *y2 = (GLshort*)commandbuf;  commandbuf += sizeof(GLshort);

	glRects(*x1, *y1, *x2, *y2);
}


//93
static void EXEC_glRectsv(char *commandbuf)
{

	glRectsv((const GLshort *)popBuf(), (const GLshort *)popBuf());
}


//94
static void EXEC_glTexCoord1d(char *commandbuf)
{
	GLdouble *s = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glTexCoord1d(*s);
}


//95
static void EXEC_glTexCoord1dv(char *commandbuf)
{

	glTexCoord1dv((const GLdouble *)popBuf());
}


//96
static void EXEC_glTexCoord1f(char *commandbuf)
{
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glTexCoord1f(*s);
}


//97
static void EXEC_glTexCoord1fv(char *commandbuf)
{

	glTexCoord1fv((const GLfloat *)popBuf());
}


//98
static void EXEC_glTexCoord1i(char *commandbuf)
{
	GLint *s = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glTexCoord1i(*s);
}


//99
static void EXEC_glTexCoord1iv(char *commandbuf)
{

	glTexCoord1iv((const GLint *)popBuf());
}


//100
static void EXEC_glTexCoord1s(char *commandbuf)
{
	GLshort *s = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glTexCoord1s(*s);
}


//101
static void EXEC_glTexCoord1sv(char *commandbuf)
{

	glTexCoord1sv((const GLshort *)popBuf());
}


//102
static void EXEC_glTexCoord2d(char *commandbuf)
{
	GLdouble *s = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *t = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glTexCoord2d(*s, *t);
}


//103
static void EXEC_glTexCoord2dv(char *commandbuf)
{

	glTexCoord2dv((const GLdouble *)popBuf());
}


//104
static void EXEC_glTexCoord2f(char *commandbuf)
{
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *t = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glTexCoord2f(*s, *t);
}


//105
static void EXEC_glTexCoord2fv(char *commandbuf)
{

	glTexCoord2fv((const GLfloat *)popBuf());
}


//106
static void EXEC_glTexCoord2i(char *commandbuf)
{
	GLint *s = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *t = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glTexCoord2i(*s, *t);
}


//107
static void EXEC_glTexCoord2iv(char *commandbuf)
{

	glTexCoord2iv((const GLint *)popBuf());
}


//108
static void EXEC_glTexCoord2s(char *commandbuf)
{
	GLshort *s = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *t = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glTexCoord2s(*s, *t);
}


//109
static void EXEC_glTexCoord2sv(char *commandbuf)
{

	glTexCoord2sv((const GLshort *)popBuf());
}


//110
static void EXEC_glTexCoord3d(char *commandbuf)
{
	GLdouble *s = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *t = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *r = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glTexCoord3d(*s, *t, *r);
}


//111
static void EXEC_glTexCoord3dv(char *commandbuf)
{

	glTexCoord3dv((const GLdouble *)popBuf());
}


//112
static void EXEC_glTexCoord3f(char *commandbuf)
{
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *t = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *r = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glTexCoord3f(*s, *t, *r);
}


//113
static void EXEC_glTexCoord3fv(char *commandbuf)
{

	glTexCoord3fv((const GLfloat *)popBuf());
}


//114
static void EXEC_glTexCoord3i(char *commandbuf)
{
	GLint *s = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *t = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *r = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glTexCoord3i(*s, *t, *r);
}


//115
static void EXEC_glTexCoord3iv(char *commandbuf)
{

	glTexCoord3iv((const GLint *)popBuf());
}


//116
static void EXEC_glTexCoord3s(char *commandbuf)
{
	GLshort *s = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *t = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *r = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glTexCoord3s(*s, *t, *r);
}


//117
static void EXEC_glTexCoord3sv(char *commandbuf)
{

	glTexCoord3sv((const GLshort *)popBuf());
}


//118
static void EXEC_glTexCoord4d(char *commandbuf)
{
	GLdouble *s = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *t = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *r = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *q = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glTexCoord4d(*s, *t, *r, *q);
}


//119
static void EXEC_glTexCoord4dv(char *commandbuf)
{

	glTexCoord4dv((const GLdouble *)popBuf());
}


//120
static void EXEC_glTexCoord4f(char *commandbuf)
{
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *t = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *r = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *q = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glTexCoord4f(*s, *t, *r, *q);
}


//121
static void EXEC_glTexCoord4fv(char *commandbuf)
{

	glTexCoord4fv((const GLfloat *)popBuf());
}


//122
static void EXEC_glTexCoord4i(char *commandbuf)
{
	GLint *s = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *t = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *r = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *q = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glTexCoord4i(*s, *t, *r, *q);
}


//123
static void EXEC_glTexCoord4iv(char *commandbuf)
{

	glTexCoord4iv((const GLint *)popBuf());
}


//124
static void EXEC_glTexCoord4s(char *commandbuf)
{
	GLshort *s = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *t = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *r = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *q = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glTexCoord4s(*s, *t, *r, *q);
}


//125
static void EXEC_glTexCoord4sv(char *commandbuf)
{

	glTexCoord4sv((const GLshort *)popBuf());
}


//126
static void EXEC_glVertex2d(char *commandbuf)
{
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glVertex2d(*x, *y);
}


//127
static void EXEC_glVertex2dv(char *commandbuf)
{

	glVertex2dv((const GLdouble *)popBuf());
}


//128
static void EXEC_glVertex2f(char *commandbuf)
{
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	glVertex2f(*x, *y);
}


//129
static void EXEC_glVertex2fv(char *commandbuf)
{

	glVertex2fv((const GLfloat *)popBuf());
}


//130
static void EXEC_glVertex2i(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glVertex2i(*x, *y);
}


//131
static void EXEC_glVertex2iv(char *commandbuf)
{

	glVertex2iv((const GLint *)popBuf());
}


//132
static void EXEC_glVertex2s(char *commandbuf)
{
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glVertex2s(*x, *y);
}


//133
static void EXEC_glVertex2sv(char *commandbuf)
{

	glVertex2sv((const GLshort *)popBuf());
}


//134
static void EXEC_glVertex3d(char *commandbuf)
{
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glVertex3d(*x, *y, *z);
}


//135
static void EXEC_glVertex3dv(char *commandbuf)
{

	glVertex3dv((const GLdouble *)popBuf());
}


//136
static void EXEC_glVertex3f(char *commandbuf)
{
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glVertex3f(*x, *y, *z);
}


//137
static void EXEC_glVertex3fv(char *commandbuf)
{

	glVertex3fv((const GLfloat *)popBuf());
}


//138
static void EXEC_glVertex3i(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *z = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glVertex3i(*x, *y, *z);
}


//139
static void EXEC_glVertex3iv(char *commandbuf)
{

	glVertex3iv((const GLint *)popBuf());
}


//140
static void EXEC_glVertex3s(char *commandbuf)
{
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *z = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glVertex3s(*x, *y, *z);
}


//141
static void EXEC_glVertex3sv(char *commandbuf)
{

	glVertex3sv((const GLshort *)popBuf());
}


//142
static void EXEC_glVertex4d(char *commandbuf)
{
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *w = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glVertex4d(*x, *y, *z, *w);
}


//143
static void EXEC_glVertex4dv(char *commandbuf)
{

	glVertex4dv((const GLdouble *)popBuf());
}


//144
static void EXEC_glVertex4f(char *commandbuf)
{
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *w = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glVertex4f(*x, *y, *z, *w);
}


//145
static void EXEC_glVertex4fv(char *commandbuf)
{

	glVertex4fv((const GLfloat *)popBuf());
}


//146
static void EXEC_glVertex4i(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *z = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *w = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glVertex4i(*x, *y, *z, *w);
}


//147
static void EXEC_glVertex4iv(char *commandbuf)
{

	glVertex4iv((const GLint *)popBuf());
}


//148
static void EXEC_glVertex4s(char *commandbuf)
{
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *z = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *w = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glVertex4s(*x, *y, *z, *w);
}


//149
static void EXEC_glVertex4sv(char *commandbuf)
{

	glVertex4sv((const GLshort *)popBuf());
}


//150
static void EXEC_glClipPlane(char *commandbuf)
{
	GLenum *plane = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glClipPlane(*plane, (const GLdouble *)popBuf());
}


//151
static void EXEC_glColorMaterial(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glColorMaterial(*face, *mode);
}


//152
static void EXEC_glCullFace(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glCullFace(*mode);
}


//153
static void EXEC_glFogf(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glFogf(*pname, *param);
}


//154
static void EXEC_glFogfv(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glFogfv(*pname, (const GLfloat *)popBuf());
}


//155
static void EXEC_glFogi(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glFogi(*pname, *param);
}


//156
static void EXEC_glFogiv(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	glFogiv(*pname, (const GLint *)popBuf());
}


//157
static void EXEC_glFrontFace(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glFrontFace(*mode);
}


//158
static void EXEC_glHint(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glHint(*target, *mode);
}


//159
static void EXEC_glLightf(char *commandbuf)
{
	GLenum *light = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glLightf(*light, *pname, *param);
}


//160
static void EXEC_glLightfv(char *commandbuf)
{
	GLenum *light = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glLightfv(*light, *pname, (const GLfloat *)popBuf());
}


//161
static void EXEC_glLighti(char *commandbuf)
{
	GLenum *light = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glLighti(*light, *pname, *param);
}


//162
static void EXEC_glLightiv(char *commandbuf)
{
	GLenum *light = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glLightiv(*light, *pname, (const GLint *)popBuf());
}


//163
static void EXEC_glLightModelf(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glLightModelf(*pname, *param);
}


//164
static void EXEC_glLightModelfv(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glLightModelfv(*pname, (const GLfloat *)popBuf());
}


//165
static void EXEC_glLightModeli(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glLightModeli(*pname, *param);
}


//166
static void EXEC_glLightModeliv(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glLightModeliv(*pname, (const GLint *)popBuf());
}


//167
static void EXEC_glLineStipple(char *commandbuf)
{
	GLint *factor = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLushort *pattern = (GLushort*)commandbuf;   commandbuf += sizeof(GLushort);

	glLineStipple(*factor, *pattern);
}


//168
static void EXEC_glLineWidth(char *commandbuf)
{
	GLfloat *width = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glLineWidth(*width);
}


//169
static void EXEC_glMaterialf(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glMaterialf(*face, *pname, *param);
}


//170
static void EXEC_glMaterialfv(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glMaterialfv(*face, *pname, (const GLfloat *)popBuf());

	//LOG("glMaterialfv: %d\n", i);
}


//171
static void EXEC_glMateriali(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glMateriali(*face, *pname, *param);
}


//172
static void EXEC_glMaterialiv(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glMaterialiv(*face, *pname, (const GLint *)popBuf());
}


//173
static void EXEC_glPointSize(char *commandbuf)
{
	GLfloat *size = (GLfloat*)commandbuf;    commandbuf += sizeof(GLfloat);

	glPointSize(*size);
}


//174
static void EXEC_glPolygonMode(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glPolygonMode(*face, *mode);
}


//175
static void EXEC_glPolygonStipple(char *commandbuf)
{

	glPolygonStipple((const GLubyte *)popBuf());
}


//176
static void EXEC_glScissor(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glScissor(*x, *y, *width, *height);
}


//177
static void EXEC_glShadeModel(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glShadeModel(*mode);
}


//178
static void EXEC_glTexParameterf(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glTexParameterf(*target, *pname, *param);
}


//179
static void EXEC_glTexParameterfv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glTexParameterfv(*target, *pname, (const GLfloat *)popBuf());
}


//180
static void EXEC_glTexParameteri(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	glTexParameteri(*target, *pname, *param);
}


//181
static void EXEC_glTexParameteriv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glTexParameteriv(*target, *pname, (const GLint *)popBuf());
}


//182
static void EXEC_glTexImage1D(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *internalformat = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLint *border = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glTexImage1D(*target, *level, *internalformat, *width, *border, *format, *type, (const GLvoid *)popBuf());
}


//183
static void EXEC_glTexImage2D(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *internalformat = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLint *border = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLboolean *null = (GLboolean*)commandbuf;  commandbuf += sizeof(GLboolean);

	char *pixels = popBuf();

	//LOG("glTexImage2D: %d/%d, %d %d\n", *width, *height, l, hash(pixels, l));

	//if(*null) {
		glTexImage2D(*target, *level, *internalformat, *width, *height, *border, *format, *type, (const GLvoid *)pixels);
	//}
	//else {
	//	LOG("183 no pixels!\n");
	//	glTexImage2D(*target, *level, *internalformat, *width, *height, *border, *format, *type, NULL);
	//}

}


//184
static void EXEC_glTexEnvf(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glTexEnvf(*target, *pname, *param);
}


//185
static void EXEC_glTexEnvfv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glTexEnvfv(*target, *pname, (const GLfloat *)popBuf());
}


//186
static void EXEC_glTexEnvi(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glTexEnvi(*target, *pname, *param);
}


//187
static void EXEC_glTexEnviv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glTexEnviv(*target, *pname, (const GLint *)popBuf());
}


//188
static void EXEC_glTexGend(char *commandbuf)
{
	GLenum *coord = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLdouble *param = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glTexGend(*coord, *pname, *param);
}


//189
static void EXEC_glTexGendv(char *commandbuf)
{
	GLenum *coord = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glTexGendv(*coord, *pname, (const GLdouble *)popBuf());
}


//190
static void EXEC_glTexGenf(char *commandbuf)
{
	GLenum *coord = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glTexGenf(*coord, *pname, *param);
}


//191
static void EXEC_glTexGenfv(char *commandbuf)
{
	GLenum *coord = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glTexGenfv(*coord, *pname, (const GLfloat *)popBuf());
}


//192
static void EXEC_glTexGeni(char *commandbuf)
{
	GLenum *coord = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glTexGeni(*coord, *pname, *param);
}


//193
static void EXEC_glTexGeniv(char *commandbuf)
{
	GLenum *coord = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glTexGeniv(*coord, *pname, (const GLint *)popBuf());
}


//194
static void EXEC_glFeedbackBuffer(char *commandbuf)
{
	GLsizei *size = (GLsizei*)commandbuf;    commandbuf += sizeof(GLsizei);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glFeedbackBuffer(*size, *type, (GLfloat *)popBuf());
}


//195
static void EXEC_glSelectBuffer(char *commandbuf)
{
	GLsizei *size = (GLsizei*)commandbuf;    commandbuf += sizeof(GLsizei);

	glSelectBuffer(*size, (GLuint *)popBuf());
}


//196
static void EXEC_glRenderMode(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	pushRet(glRenderMode(*mode));
}


//197
static void EXEC_glInitNames(char *commandbuf)
{

	glInitNames();
}


//198
static void EXEC_glLoadName(char *commandbuf)
{
	GLuint *name = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

	glLoadName(*name);
}


//199
static void EXEC_glPassThrough(char *commandbuf)
{
	GLfloat *token = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glPassThrough(*token);
}


//200
static void EXEC_glPopName(char *commandbuf)
{

	glPopName();
}


//201
static void EXEC_glPushName(char *commandbuf)
{
	GLuint *name = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

	glPushName(*name);
}


//202
static void EXEC_glDrawBuffer(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glDrawBuffer(*mode);
}


//203
static void EXEC_glClear(char *commandbuf)
{
	GLbitfield *mask = (GLbitfield*)commandbuf;  commandbuf += sizeof(GLbitfield);

	glClear(*mask);
}


//204
static void EXEC_glClearAccum(char *commandbuf)
{
	GLfloat *red = (GLfloat*)commandbuf;     commandbuf += sizeof(GLfloat);
	GLfloat *green = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *blue = (GLfloat*)commandbuf;    commandbuf += sizeof(GLfloat);
	GLfloat *alpha = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glClearAccum(*red, *green, *blue, *alpha);
}


//205
static void EXEC_glClearIndex(char *commandbuf)
{
	GLfloat *c = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glClearIndex(*c);
}


//206
static void EXEC_glClearColor(char *commandbuf)
{
	GLclampf *red = (GLclampf*)commandbuf;   commandbuf += sizeof(GLclampf);
	GLclampf *green = (GLclampf*)commandbuf;     commandbuf += sizeof(GLclampf);
	GLclampf *blue = (GLclampf*)commandbuf;  commandbuf += sizeof(GLclampf);
	GLclampf *alpha = (GLclampf*)commandbuf;     commandbuf += sizeof(GLclampf);

	glClearColor(*red, *green, *blue, *alpha);
}


//207
static void EXEC_glClearStencil(char *commandbuf)
{
	GLint *s = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glClearStencil(*s);
}


//208
static void EXEC_glClearDepth(char *commandbuf)
{
	GLclampd *depth = (GLclampd*)commandbuf;     commandbuf += sizeof(GLclampd);

	glClearDepth(*depth);
}


//209
static void EXEC_glStencilMask(char *commandbuf)
{
	GLuint *mask = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

	glStencilMask(*mask);
}


//210
static void EXEC_glColorMask(char *commandbuf)
{
	GLboolean *red = (GLboolean*)commandbuf;     commandbuf += sizeof(GLboolean);
	GLboolean *green = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);
	GLboolean *blue = (GLboolean*)commandbuf;    commandbuf += sizeof(GLboolean);
	GLboolean *alpha = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);

	glColorMask(*red, *green, *blue, *alpha);
}


//211
static void EXEC_glDepthMask(char *commandbuf)
{
	GLboolean *flag = (GLboolean*)commandbuf;    commandbuf += sizeof(GLboolean);

	glDepthMask(*flag);
}


//212
static void EXEC_glIndexMask(char *commandbuf)
{
	GLuint *mask = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

	glIndexMask(*mask);
}


//213
static void EXEC_glAccum(char *commandbuf)
{
	GLenum *op = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLfloat *value = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glAccum(*op, *value);
}


//214
static void EXEC_glDisable(char *commandbuf)
{
	GLenum *cap = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);

	glDisable(*cap);
}


//215
static void EXEC_glEnable(char *commandbuf)
{
	GLenum *cap = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);

	glEnable(*cap);
}


//216
static void EXEC_glFinish(char *commandbuf)
{

	glFinish();
}


//217
static void EXEC_glFlush(char *commandbuf)
{

	glFlush();
}


//218
static void EXEC_glPopAttrib(char *commandbuf)
{

	glPopAttrib();
}


//219
static void EXEC_glPushAttrib(char *commandbuf)
{
	GLbitfield *mask = (GLbitfield*)commandbuf;  commandbuf += sizeof(GLbitfield);

	glPushAttrib(*mask);
}


//220
static void EXEC_glMap1d(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLdouble *u1 = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *u2 = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLint *stride = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *order = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glMap1d(*target, *u1, *u2, *stride, *order, (const GLdouble *)popBuf());
}


//221
static void EXEC_glMap1f(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLfloat *u1 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *u2 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLint *stride = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *order = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glMap1f(*target, *u1, *u2, *stride, *order, (const GLfloat *)popBuf());
}


//222
static void EXEC_glMap2d(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLdouble *u1 = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *u2 = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLint *ustride = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *uorder = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLdouble *v1 = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *v2 = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLint *vstride = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *vorder = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glMap2d(*target, *u1, *u2, *ustride, *uorder, *v1, *v2, *vstride, *vorder, (const GLdouble *)popBuf());
}


//223
static void EXEC_glMap2f(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLfloat *u1 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *u2 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLint *ustride = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *uorder = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLfloat *v1 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *v2 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLint *vstride = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *vorder = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glMap2f(*target, *u1, *u2, *ustride, *uorder, *v1, *v2, *vstride, *vorder, (const GLfloat *)popBuf());
}


//224
static void EXEC_glMapGrid1d(char *commandbuf)
{
	GLint *un = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLdouble *u1 = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *u2 = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);

	glMapGrid1d(*un, *u1, *u2);
}


//225
static void EXEC_glMapGrid1f(char *commandbuf)
{
	GLint *un = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLfloat *u1 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *u2 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	glMapGrid1f(*un, *u1, *u2);
}


//226
static void EXEC_glMapGrid2d(char *commandbuf)
{
	GLint *un = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLdouble *u1 = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *u2 = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLint *vn = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLdouble *v1 = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *v2 = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);

	glMapGrid2d(*un, *u1, *u2, *vn, *v1, *v2);
}


//227
static void EXEC_glMapGrid2f(char *commandbuf)
{
	GLint *un = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLfloat *u1 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *u2 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLint *vn = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLfloat *v1 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *v2 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	glMapGrid2f(*un, *u1, *u2, *vn, *v1, *v2);
}


//228
static void EXEC_glEvalCoord1d(char *commandbuf)
{
	GLdouble *u = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glEvalCoord1d(*u);
}


//229
static void EXEC_glEvalCoord1dv(char *commandbuf)
{

	glEvalCoord1dv((const GLdouble *)popBuf());
}


//230
static void EXEC_glEvalCoord1f(char *commandbuf)
{
	GLfloat *u = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glEvalCoord1f(*u);
}


//231
static void EXEC_glEvalCoord1fv(char *commandbuf)
{

	glEvalCoord1fv((const GLfloat *)popBuf());
}


//232
static void EXEC_glEvalCoord2d(char *commandbuf)
{
	GLdouble *u = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *v = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glEvalCoord2d(*u, *v);
}


//233
static void EXEC_glEvalCoord2dv(char *commandbuf)
{

	glEvalCoord2dv((const GLdouble *)popBuf());
}


//234
static void EXEC_glEvalCoord2f(char *commandbuf)
{
	GLfloat *u = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *v = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glEvalCoord2f(*u, *v);
}


//235
static void EXEC_glEvalCoord2fv(char *commandbuf)
{

	glEvalCoord2fv((const GLfloat *)popBuf());
}


//236
static void EXEC_glEvalMesh1(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLint *i1 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *i2 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glEvalMesh1(*mode, *i1, *i2);
}


//237
static void EXEC_glEvalPoint1(char *commandbuf)
{
	GLint *i = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glEvalPoint1(*i);
}


//238
static void EXEC_glEvalMesh2(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLint *i1 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *i2 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *j1 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *j2 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glEvalMesh2(*mode, *i1, *i2, *j1, *j2);
}


//239
static void EXEC_glEvalPoint2(char *commandbuf)
{
	GLint *i = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *j = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glEvalPoint2(*i, *j);
}


//240
static void EXEC_glAlphaFunc(char *commandbuf)
{
	GLenum *func = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLclampf *ref = (GLclampf*)commandbuf;   commandbuf += sizeof(GLclampf);

	glAlphaFunc(*func, *ref);
}


//241
static void EXEC_glBlendFunc(char *commandbuf)
{
	GLenum *sfactor = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);
	GLenum *dfactor = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);

	glBlendFunc(*sfactor, *dfactor);
}


//242
static void EXEC_glLogicOp(char *commandbuf)
{
	GLenum *opcode = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glLogicOp(*opcode);
}


//243
static void EXEC_glStencilFunc(char *commandbuf)
{
	GLenum *func = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLint *ref = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLuint *mask = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

	glStencilFunc(*func, *ref, *mask);
}


//244
static void EXEC_glStencilOp(char *commandbuf)
{
	GLenum *fail = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *zfail = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *zpass = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glStencilOp(*fail, *zfail, *zpass);
}


//245
static void EXEC_glDepthFunc(char *commandbuf)
{
	GLenum *func = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glDepthFunc(*func);
}


//246
static void EXEC_glPixelZoom(char *commandbuf)
{
	GLfloat *xfactor = (GLfloat*)commandbuf;     commandbuf += sizeof(GLfloat);
	GLfloat *yfactor = (GLfloat*)commandbuf;     commandbuf += sizeof(GLfloat);

	glPixelZoom(*xfactor, *yfactor);
}


//247
static void EXEC_glPixelTransferf(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glPixelTransferf(*pname, *param);
}


//248
static void EXEC_glPixelTransferi(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glPixelTransferi(*pname, *param);
}


//249
static void EXEC_glPixelStoref(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glPixelStoref(*pname, *param);
}


//250
static void EXEC_glPixelStorei(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glPixelStorei(*pname, *param);
}


//251
static void EXEC_glPixelMapfv(char *commandbuf)
{
	GLenum *map = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);
	GLsizei *mapsize = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);

	glPixelMapfv(*map, *mapsize, (const GLfloat *)popBuf());
}


//252
static void EXEC_glPixelMapuiv(char *commandbuf)
{
	GLenum *map = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);
	GLsizei *mapsize = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);

	glPixelMapuiv(*map, *mapsize, (const GLuint *)popBuf());
}


//253
static void EXEC_glPixelMapusv(char *commandbuf)
{
	GLenum *map = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);
	GLsizei *mapsize = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);

	glPixelMapusv(*map, *mapsize, (const GLushort *)popBuf());
}


//254
static void EXEC_glReadBuffer(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glReadBuffer(*mode);
}


//255
static void EXEC_glCopyPixels(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glCopyPixels(*x, *y, *width, *height, *type);
}


//256
static void EXEC_glReadPixels(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glReadPixels(*x, *y, *width, *height, *format, *type, (GLvoid *)popBuf());
}


//257
static void EXEC_glDrawPixels(char *commandbuf)
{
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glDrawPixels(*width, *height, *format, *type, (const GLvoid *)popBuf());
}


//258
static void EXEC_glGetBooleanv(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetBooleanv(*pname, (GLboolean *)popBuf());
}


//259
static void EXEC_glGetClipPlane(char *commandbuf)
{
	GLenum *plane = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetClipPlane(*plane, (GLdouble *)popBuf());
}


//260
static void EXEC_glGetDoublev(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetDoublev(*pname, (GLdouble *)popBuf());
}


//261
static void EXEC_glGetError(char *commandbuf)
{

	pushRet(glGetError());
}


//262
static void EXEC_glGetFloatv(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetFloatv(*pname, (GLfloat *)popBuf());
}


//263
static void EXEC_glGetIntegerv(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetIntegerv(*pname, (GLint *)popBuf());
}


//264
static void EXEC_glGetLightfv(char *commandbuf)
{
	GLenum *light = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetLightfv(*light, *pname, (GLfloat *)popBuf());
}


//265
static void EXEC_glGetLightiv(char *commandbuf)
{
	GLenum *light = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetLightiv(*light, *pname, (GLint *)popBuf());
}


//266
static void EXEC_glGetMapdv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *query = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetMapdv(*target, *query, (GLdouble *)popBuf());
}


//267
static void EXEC_glGetMapfv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *query = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetMapfv(*target, *query, (GLfloat *)popBuf());
}


//268
static void EXEC_glGetMapiv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *query = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetMapiv(*target, *query, (GLint *)popBuf());
}


//269
static void EXEC_glGetMaterialfv(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetMaterialfv(*face, *pname, (GLfloat *)popBuf());
}


//270
static void EXEC_glGetMaterialiv(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetMaterialiv(*face, *pname, (GLint *)popBuf());
}


//271
static void EXEC_glGetPixelMapfv(char *commandbuf)
{
	GLenum *map = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);

	glGetPixelMapfv(*map, (GLfloat *)popBuf());
}


//272
static void EXEC_glGetPixelMapuiv(char *commandbuf)
{
	GLenum *map = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);

	glGetPixelMapuiv(*map, (GLuint *)popBuf());
}


//273
static void EXEC_glGetPixelMapusv(char *commandbuf)
{
	GLenum *map = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);

	glGetPixelMapusv(*map, (GLushort *)popBuf());
}


//274
static void EXEC_glGetPolygonStipple(char *commandbuf)
{

	glGetPolygonStipple((GLubyte *)popBuf());
}


//275
static void EXEC_glGetString(char *commandbuf)
{
	GLenum *name = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	pushRet(glGetString(*name));
}


//276
static void EXEC_glGetTexEnvfv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetTexEnvfv(*target, *pname, (GLfloat *)popBuf());
}


//277
static void EXEC_glGetTexEnviv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetTexEnviv(*target, *pname, (GLint *)popBuf());
}


//278
static void EXEC_glGetTexGendv(char *commandbuf)
{
	GLenum *coord = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetTexGendv(*coord, *pname, (GLdouble *)popBuf());
}


//279
static void EXEC_glGetTexGenfv(char *commandbuf)
{
	GLenum *coord = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetTexGenfv(*coord, *pname, (GLfloat *)popBuf());
}


//280
static void EXEC_glGetTexGeniv(char *commandbuf)
{
	GLenum *coord = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetTexGeniv(*coord, *pname, (GLint *)popBuf());
}


//281
static void EXEC_glGetTexImage(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glGetTexImage(*target, *level, *format, *type, (GLvoid *)popBuf());
}


//282
static void EXEC_glGetTexParameterfv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetTexParameterfv(*target, *pname, (GLfloat *)popBuf());
}


//283
static void EXEC_glGetTexParameteriv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetTexParameteriv(*target, *pname, (GLint *)popBuf());
}


//284
static void EXEC_glGetTexLevelParameterfv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetTexLevelParameterfv(*target, *level, *pname, (GLfloat *)popBuf());
}


//285
static void EXEC_glGetTexLevelParameteriv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetTexLevelParameteriv(*target, *level, *pname, (GLint *)popBuf());
}


//286
static void EXEC_glIsEnabled(char *commandbuf)
{
	GLenum *cap = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);

	pushRet(glIsEnabled(*cap));
}


//287
static void EXEC_glIsList(char *commandbuf)
{
	GLuint *list = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

	pushRet(glIsList(*list));
}


//288
static void EXEC_glDepthRange(char *commandbuf)
{
	GLclampd *zNear = (GLclampd*)commandbuf;     commandbuf += sizeof(GLclampd);
	GLclampd *zFar = (GLclampd*)commandbuf;  commandbuf += sizeof(GLclampd);

	glDepthRange(*zNear, *zFar);
}


//289
static void EXEC_glFrustum(char *commandbuf)
{
	GLdouble *left = (GLdouble*)commandbuf;  commandbuf += sizeof(GLdouble);
	GLdouble *right = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *bottom = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *top = (GLdouble*)commandbuf;   commandbuf += sizeof(GLdouble);
	GLdouble *zNear = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *zFar = (GLdouble*)commandbuf;  commandbuf += sizeof(GLdouble);
	LOG("called glFrustum, panic!!!!\n");
	glFrustum(*left, *right, *bottom, *top, *zNear, *zFar);
}


//290
static void EXEC_glLoadIdentity(char *commandbuf)
{

	glLoadIdentity();
}


//291
static void EXEC_glLoadMatrixf(char *commandbuf)
{

	glLoadMatrixf((const GLfloat *)popBuf());
}


//292
static void EXEC_glLoadMatrixd(char *commandbuf)
{

	glLoadMatrixd((const GLdouble *)popBuf());
}


//293
static void EXEC_glMatrixMode(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glMatrixMode(*mode);
}


//294
static void EXEC_glMultMatrixf(char *commandbuf)
{

	glMultMatrixf((const GLfloat *)popBuf());
}


//295
static void EXEC_glMultMatrixd(char *commandbuf)
{

	glMultMatrixd((const GLdouble *)popBuf());
}


//296
static void EXEC_glOrtho(char *commandbuf)
{
	GLdouble *left = (GLdouble*)commandbuf;  commandbuf += sizeof(GLdouble);
	GLdouble *right = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *bottom = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *top = (GLdouble*)commandbuf;   commandbuf += sizeof(GLdouble);
	GLdouble *zNear = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *zFar = (GLdouble*)commandbuf;  commandbuf += sizeof(GLdouble);

	glOrtho(*left, *right, *bottom, *top, *zNear, *zFar);
}


//297
static void EXEC_glPopMatrix(char *commandbuf)
{

	glPopMatrix();
}


//298
static void EXEC_glPushMatrix(char *commandbuf)
{

	glPushMatrix();
}


//299
static void EXEC_glRotated(char *commandbuf)
{
	GLdouble *angle = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glRotated(*angle, *x, *y, *z);
}


//300
static void EXEC_glRotatef(char *commandbuf)
{
	GLfloat *angle = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glRotatef(*angle, *x, *y, *z);
}


//301
static void EXEC_glScaled(char *commandbuf)
{
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glScaled(*x, *y, *z);
}


//302
static void EXEC_glScalef(char *commandbuf)
{
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glScalef(*x, *y, *z);
}


//303
static void EXEC_glTranslated(char *commandbuf)
{
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glTranslated(*x, *y, *z);
}


//304
static void EXEC_glTranslatef(char *commandbuf)
{
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glTranslatef(*x, *y, *z);
}


//305
static void EXEC_glViewport(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glViewport(*x, *y, *width, *height);
}


//306
static void EXEC_glArrayElement(char *commandbuf)
{
	GLint *i = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glArrayElement(*i);
}


//307
static void EXEC_glBindTexture(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *texture = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	glBindTexture(*target, *texture);
}


//moved glcolorpointer to be with glVertexPointer etc

//309
static void EXEC_glDisableClientState(char *commandbuf)
{
	GLenum *array = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glDisableClientState(*array);
}


//310
static void EXEC_glDrawArrays(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLint *first = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	//LOG("Starting glDrawArrays(%d, %d, %d)\n", *mode, *first, *count);

	glDrawArrays(*mode, *first, *count);

	//LOG("ok\n");
}


//311
static void EXEC_glDrawElements(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	const GLvoid * buf = (const GLvoid *)popBuf();

	//LOG("About to glDrawElements(%d, %d, %d)\n", l, *count, hash((char *)buf, l));

	glDrawElements(*mode, *count, *type, buf);

	//LOG("Done!\n");
}


//312
static void EXEC_glEdgeFlagPointer(char *commandbuf)
{
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glEdgeFlagPointer(*stride, (const GLvoid *)popBuf());
}


//313
static void EXEC_glEnableClientState(char *commandbuf)
{
	GLenum *array = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glEnableClientState(*array);
}


//314
static void EXEC_glIndexPointer(char *commandbuf)
{
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glIndexPointer(*type, *stride, (const GLvoid *)popBuf());
}


//315
static void EXEC_glIndexub(char *commandbuf)
{
	GLubyte *c = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);

	glIndexub(*c);
}


//316
static void EXEC_glIndexubv(char *commandbuf)
{

	glIndexubv((const GLubyte *)popBuf());
}


//317
static void EXEC_glInterleavedArrays(char *commandbuf)
{
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLboolean *null = (GLboolean*)commandbuf;    commandbuf += sizeof(GLsizei);
	if(*null)
		glInterleavedArrays(*format, *stride, (char *) NULL);
	else {
		const GLvoid * buf =  (const GLvoid *)popBuf();
		glInterleavedArrays(*format, *stride, buf);
	}
}


//318
static void EXEC_glNormalPointer(char *commandbuf)
{
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLboolean *null = (GLboolean*)commandbuf;    commandbuf += sizeof(GLsizei);

	if(*null){
		glNormalPointer(*type, *stride, (const GLvoid *)NULL);
	}else{
		glNormalPointer(*type, *stride, (const GLvoid *)popBuf());
	}
}


//319
static void EXEC_glPolygonOffset(char *commandbuf)
{
	GLfloat *factor = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *units = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glPolygonOffset(*factor, *units);
}









//308
static void EXEC_glColorPointer(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLboolean *null = (GLboolean*)commandbuf;    commandbuf += sizeof(GLsizei);
	if(*null)
		glColorPointer(*size, *type, *stride, (char *) NULL);
	else {
		const GLvoid * buf =  (const GLvoid *)popBuf();
		glColorPointer(*size, *type, *stride, buf);
		//LOG("glColorPointer size: %d, %d, %d\n", *size, i, hash((char *)buf, i));
		//LOG("glColorPointer size: %d, bytes: %d\n", *size, i);

		//LOG("EXEC glColorPointer(%d, %s, %d) - %d\n", *size, getGLParamName(*type), *stride, i);
	}
}

//320
static void EXEC_glTexCoordPointer(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLboolean *null = (GLboolean*)commandbuf;    commandbuf += sizeof(GLsizei);
	if(*null)
		glTexCoordPointer(*size, *type, *stride, (char *) NULL);
	else {
		const GLvoid * buf =  (const GLvoid *)popBuf();
		glTexCoordPointer(*size, *type, *stride, buf);
		//LOG("glTexCoordPointer size: %d, bytes: %d\n", *size, i);

		//LOG("EXEC glTexCoordPointer(%d, %s, %d) - %d\n", *size, getGLParamName(*type), *stride, i);

	}
}


//321
static void EXEC_glVertexPointer(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLboolean *null = (GLboolean*)commandbuf;    commandbuf += sizeof(GLsizei);

	if(*null)
		glVertexPointer(*size, *type, *stride, (char *) NULL);
	else {
		const GLvoid * buf =  (const GLvoid *)popBuf();
		glVertexPointer(*size, *type, *stride, buf);
		//LOG("glVertexPointer size: %d, bytes: %d\n", *size, i);

		//LOG("EXEC glVertexPointer(%d, %s, %d) - %d\n", *size, getGLParamName(*type), *stride, i);
	}
}












//322
static void EXEC_glAreTexturesResident(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	pushRet(glAreTexturesResident(*n, (const GLuint *)popBuf(), (GLboolean *)popBuf()));
}


//323
static void EXEC_glCopyTexImage1D(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLint *border = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glCopyTexImage1D(*target, *level, *internalformat, *x, *y, *width, *border);
}


//324
static void EXEC_glCopyTexImage2D(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLint *border = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glCopyTexImage2D(*target, *level, *internalformat, *x, *y, *width, *height, *border);
}


//325
static void EXEC_glCopyTexSubImage1D(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *xoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glCopyTexSubImage1D(*target, *level, *xoffset, *x, *y, *width);
}


//326
static void EXEC_glCopyTexSubImage2D(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *xoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *yoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glCopyTexSubImage2D(*target, *level, *xoffset, *yoffset, *x, *y, *width, *height);
}


//327
static void EXEC_glDeleteTextures(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glDeleteTextures(*n, (const GLuint *)popBuf());
}


//328
static void EXEC_glGenTextures(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	glGenTextures(*n, (GLuint *)popBuf());
}


//329
static void EXEC_glGetPointerv(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetPointerv(*pname, (GLvoid **)popBuf());
}


//330
static void EXEC_glIsTexture(char *commandbuf)
{
	GLuint *texture = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	pushRet(glIsTexture(*texture));
}


//331
static void EXEC_glPrioritizeTextures(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glPrioritizeTextures(*n, (const GLuint *)popBuf(), (const GLclampf *)popBuf());
}


//332
static void EXEC_glTexSubImage1D(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *xoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	//GLuint *UNUSED = (GLuint*)commandbuf;	 commandbuf += sizeof(GLuint);

	glTexSubImage1D(*target, *level, *xoffset, *width, *format, *type,  (const GLvoid *)popBuf());
}


//333
static void EXEC_glTexSubImage2D(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *xoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *yoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	//GLuint *UNUSED = (GLuint*)commandbuf;	 commandbuf += sizeof(GLuint);

	glTexSubImage2D(*target, *level, *xoffset, *yoffset, *width, *height, *format, *type,  (const GLvoid *)popBuf());
}


//334
static void EXEC_glPopClientAttrib(char *commandbuf)
{

	glPopClientAttrib();
}


//335
static void EXEC_glPushClientAttrib(char *commandbuf)
{
	GLbitfield *mask = (GLbitfield*)commandbuf;  commandbuf += sizeof(GLbitfield);

	glPushClientAttrib(*mask);
}


//336
static void EXEC_glBlendColor(char *commandbuf)
{
	GLclampf *red = (GLclampf*)commandbuf;   commandbuf += sizeof(GLclampf);
	GLclampf *green = (GLclampf*)commandbuf;     commandbuf += sizeof(GLclampf);
	GLclampf *blue = (GLclampf*)commandbuf;  commandbuf += sizeof(GLclampf);
	GLclampf *alpha = (GLclampf*)commandbuf;     commandbuf += sizeof(GLclampf);

	glBlendColor(*red, *green, *blue, *alpha);
}


//337
static void EXEC_glBlendEquation(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glBlendEquation(*mode);
}


//338
static void EXEC_glDrawRangeElements(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLuint *start = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLuint *end = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glDrawRangeElements(*mode, *start, *end, *count, *type, (const GLvoid *)popBuf());
}


//339
static void EXEC_glColorTable(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glColorTable(*target, *internalformat, *width, *format, *type, (const GLvoid *)popBuf());
}


//340
static void EXEC_glColorTableParameterfv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glColorTableParameterfv(*target, *pname, (const GLfloat *)popBuf());
}


//341
static void EXEC_glColorTableParameteriv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glColorTableParameteriv(*target, *pname, (const GLint *)popBuf());
}


//342
static void EXEC_glCopyColorTable(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glCopyColorTable(*target, *internalformat, *x, *y, *width);
}


//343
static void EXEC_glGetColorTable(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glGetColorTable(*target, *format, *type, (GLvoid *)popBuf());
}


//344
static void EXEC_glGetColorTableParameterfv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetColorTableParameterfv(*target, *pname, (GLfloat *)popBuf());
}


//345
static void EXEC_glGetColorTableParameteriv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetColorTableParameteriv(*target, *pname, (GLint *)popBuf());
}


//346
static void EXEC_glColorSubTable(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *start = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glColorSubTable(*target, *start, *count, *format, *type, (const GLvoid *)popBuf());
}


//347
static void EXEC_glCopyColorSubTable(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *start = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glCopyColorSubTable(*target, *start, *x, *y, *width);
}


//348
static void EXEC_glConvolutionFilter1D(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glConvolutionFilter1D(*target, *internalformat, *width, *format, *type, (const GLvoid *)popBuf());
}


//349
static void EXEC_glConvolutionFilter2D(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glConvolutionFilter2D(*target, *internalformat, *width, *height, *format, *type, (const GLvoid *)popBuf());
}


//350
static void EXEC_glConvolutionParameterf(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *params = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	glConvolutionParameterf(*target, *pname, *params);
}


//351
static void EXEC_glConvolutionParameterfv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glConvolutionParameterfv(*target, *pname, (const GLfloat *)popBuf());
}


//352
static void EXEC_glConvolutionParameteri(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *params = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glConvolutionParameteri(*target, *pname, *params);
}


//353
static void EXEC_glConvolutionParameteriv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glConvolutionParameteriv(*target, *pname, (const GLint *)popBuf());
}


//354
static void EXEC_glCopyConvolutionFilter1D(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glCopyConvolutionFilter1D(*target, *internalformat, *x, *y, *width);
}


//355
static void EXEC_glCopyConvolutionFilter2D(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glCopyConvolutionFilter2D(*target, *internalformat, *x, *y, *width, *height);
}


//356
static void EXEC_glGetConvolutionFilter(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glGetConvolutionFilter(*target, *format, *type, (GLvoid *)popBuf());
}


//357
static void EXEC_glGetConvolutionParameterfv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetConvolutionParameterfv(*target, *pname, (GLfloat *)popBuf());
}


//358
static void EXEC_glGetConvolutionParameteriv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetConvolutionParameteriv(*target, *pname, (GLint *)popBuf());
}


//359
static void EXEC_glGetSeparableFilter(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glGetSeparableFilter(*target, *format, *type, (GLvoid *)popBuf(), (GLvoid *)popBuf(), (GLvoid *)popBuf());
}


//360
static void EXEC_glSeparableFilter2D(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glSeparableFilter2D(*target, *internalformat, *width, *height, *format, *type, (const GLvoid *)popBuf(), (const GLvoid *)popBuf());
}


//361
static void EXEC_glGetHistogram(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLboolean *reset = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glGetHistogram(*target, *reset, *format, *type, (GLvoid *)popBuf());
}


//362
static void EXEC_glGetHistogramParameterfv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetHistogramParameterfv(*target, *pname, (GLfloat *)popBuf());
}


//363
static void EXEC_glGetHistogramParameteriv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetHistogramParameteriv(*target, *pname, (GLint *)popBuf());
}


//364
static void EXEC_glGetMinmax(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLboolean *reset = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glGetMinmax(*target, *reset, *format, *type, (GLvoid *)popBuf());
}


//365
static void EXEC_glGetMinmaxParameterfv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetMinmaxParameterfv(*target, *pname, (GLfloat *)popBuf());
}


//366
static void EXEC_glGetMinmaxParameteriv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetMinmaxParameteriv(*target, *pname, (GLint *)popBuf());
}


//367
static void EXEC_glHistogram(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLboolean *sink = (GLboolean*)commandbuf;    commandbuf += sizeof(GLboolean);

	glHistogram(*target, *width, *internalformat, *sink);
}


//368
static void EXEC_glMinmax(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLboolean *sink = (GLboolean*)commandbuf;    commandbuf += sizeof(GLboolean);

	glMinmax(*target, *internalformat, *sink);
}


//369
static void EXEC_glResetHistogram(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glResetHistogram(*target);
}


//370
static void EXEC_glResetMinmax(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glResetMinmax(*target);
}


//371
static void EXEC_glTexImage3D(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *internalformat = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLsizei *depth = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLint *border = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glTexImage3D(*target, *level, *internalformat, *width, *height, *depth, *border, *format, *type, (const GLvoid *)popBuf());
}


//372
static void EXEC_glTexSubImage3D(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *xoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *yoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *zoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLsizei *depth = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	//GLuint *UNUSED = (GLuint*)commandbuf;	 commandbuf += sizeof(GLuint);

	glTexSubImage3D(*target, *level, *xoffset, *yoffset, *zoffset, *width, *height, *depth, *format, *type,  (const GLvoid *)popBuf());
}


//373
static void EXEC_glCopyTexSubImage3D(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *xoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *yoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *zoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glCopyTexSubImage3D(*target, *level, *xoffset, *yoffset, *zoffset, *x, *y, *width, *height);
}


//374
static void EXEC_glActiveTexture(char *commandbuf)
{
	GLenum *texture = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);

	glActiveTexture(*texture);
}


//375
static void EXEC_glClientActiveTexture(char *commandbuf)
{
	GLenum *texture = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);

	glClientActiveTexture(*texture);
}


//376
static void EXEC_glMultiTexCoord1d(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLdouble *s = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glMultiTexCoord1d(*target, *s);
}


//377
static void EXEC_glMultiTexCoord1dv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord1dv(*target, (const GLdouble *)popBuf());
}


//378
static void EXEC_glMultiTexCoord1f(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glMultiTexCoord1f(*target, *s);
}


//379
static void EXEC_glMultiTexCoord1fv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord1fv(*target, (const GLfloat *)popBuf());
}


//380
static void EXEC_glMultiTexCoord1i(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *s = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glMultiTexCoord1i(*target, *s);
}


//381
static void EXEC_glMultiTexCoord1iv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord1iv(*target, (const GLint *)popBuf());
}


//382
static void EXEC_glMultiTexCoord1s(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLshort *s = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glMultiTexCoord1s(*target, *s);
}


//383
static void EXEC_glMultiTexCoord1sv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord1sv(*target, (const GLshort *)popBuf());
}


//384
static void EXEC_glMultiTexCoord2d(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLdouble *s = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *t = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glMultiTexCoord2d(*target, *s, *t);
}


//385
static void EXEC_glMultiTexCoord2dv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord2dv(*target, (const GLdouble *)popBuf());
}


//386
static void EXEC_glMultiTexCoord2f(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *t = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glMultiTexCoord2f(*target, *s, *t);
}


//387
static void EXEC_glMultiTexCoord2fv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord2fv(*target, (const GLfloat *)popBuf());
}


//388
static void EXEC_glMultiTexCoord2i(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *s = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *t = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glMultiTexCoord2i(*target, *s, *t);
}


//389
static void EXEC_glMultiTexCoord2iv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord2iv(*target, (const GLint *)popBuf());
}


//390
static void EXEC_glMultiTexCoord2s(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLshort *s = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *t = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glMultiTexCoord2s(*target, *s, *t);
}


//391
static void EXEC_glMultiTexCoord2sv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord2sv(*target, (const GLshort *)popBuf());
}


//392
static void EXEC_glMultiTexCoord3d(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLdouble *s = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *t = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *r = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glMultiTexCoord3d(*target, *s, *t, *r);
}


//393
static void EXEC_glMultiTexCoord3dv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord3dv(*target, (const GLdouble *)popBuf());
}


//394
static void EXEC_glMultiTexCoord3f(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *t = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *r = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glMultiTexCoord3f(*target, *s, *t, *r);
}


//395
static void EXEC_glMultiTexCoord3fv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord3fv(*target, (const GLfloat *)popBuf());
}


//396
static void EXEC_glMultiTexCoord3i(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *s = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *t = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *r = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glMultiTexCoord3i(*target, *s, *t, *r);
}


//397
static void EXEC_glMultiTexCoord3iv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord3iv(*target, (const GLint *)popBuf());
}


//398
static void EXEC_glMultiTexCoord3s(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLshort *s = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *t = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *r = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glMultiTexCoord3s(*target, *s, *t, *r);
}


//399
static void EXEC_glMultiTexCoord3sv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord3sv(*target, (const GLshort *)popBuf());
}


//400
static void EXEC_glMultiTexCoord4d(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLdouble *s = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *t = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *r = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *q = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glMultiTexCoord4d(*target, *s, *t, *r, *q);
}


//401
static void EXEC_glMultiTexCoord4dv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord4dv(*target, (const GLdouble *)popBuf());
}


//402
static void EXEC_glMultiTexCoord4f(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *t = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *r = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *q = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glMultiTexCoord4f(*target, *s, *t, *r, *q);
}


//403
static void EXEC_glMultiTexCoord4fv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord4fv(*target, (const GLfloat *)popBuf());
}


//404
static void EXEC_glMultiTexCoord4i(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *s = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *t = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *r = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *q = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glMultiTexCoord4i(*target, *s, *t, *r, *q);
}


//405
static void EXEC_glMultiTexCoord4iv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord4iv(*target, (const GLint *)popBuf());
}


//406
static void EXEC_glMultiTexCoord4s(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLshort *s = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *t = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *r = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *q = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glMultiTexCoord4s(*target, *s, *t, *r, *q);
}


//407
static void EXEC_glMultiTexCoord4sv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord4sv(*target, (const GLshort *)popBuf());
}


//408
static void EXEC_glLoadTransposeMatrixf(char *commandbuf)
{

	glLoadTransposeMatrixf((const GLfloat *)popBuf());
}


//409
static void EXEC_glLoadTransposeMatrixd(char *commandbuf)
{

	glLoadTransposeMatrixd((const GLdouble *)popBuf());
}


//410
static void EXEC_glMultTransposeMatrixf(char *commandbuf)
{

	glMultTransposeMatrixf((const GLfloat *)popBuf());
}


//411
static void EXEC_glMultTransposeMatrixd(char *commandbuf)
{

	glMultTransposeMatrixd((const GLdouble *)popBuf());
}


//412
static void EXEC_glSampleCoverage(char *commandbuf)
{
	GLclampf *value = (GLclampf*)commandbuf;     commandbuf += sizeof(GLclampf);
	GLboolean *invert = (GLboolean*)commandbuf;  commandbuf += sizeof(GLboolean);

	glSampleCoverage(*value, *invert);
}


//413
static void EXEC_glCompressedTexImage3D(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLsizei *depth = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLint *border = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLsizei *imageSize = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glCompressedTexImage3D(*target, *level, *internalformat, *width, *height, *depth, *border, *imageSize, (const GLvoid *)popBuf());
}


//414
static void EXEC_glCompressedTexImage2D(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLint *border = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLsizei *imageSize = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glCompressedTexImage2D(*target, *level, *internalformat, *width, *height, *border, *imageSize, (const GLvoid *)popBuf());
}


//415
static void EXEC_glCompressedTexImage1D(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLint *border = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLsizei *imageSize = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glCompressedTexImage1D(*target, *level, *internalformat, *width, *border, *imageSize, (const GLvoid *)popBuf());
}


//416
static void EXEC_glCompressedTexSubImage3D(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *xoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *yoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *zoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLsizei *depth = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *imageSize = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glCompressedTexSubImage3D(*target, *level, *xoffset, *yoffset, *zoffset, *width, *height, *depth, *format, *imageSize, (const GLvoid *)popBuf());
}


//417
static void EXEC_glCompressedTexSubImage2D(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *xoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *yoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *imageSize = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glCompressedTexSubImage2D(*target, *level, *xoffset, *yoffset, *width, *height, *format, *imageSize, (const GLvoid *)popBuf());
}


//418
static void EXEC_glCompressedTexSubImage1D(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *xoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *imageSize = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glCompressedTexSubImage1D(*target, *level, *xoffset, *width, *format, *imageSize, (const GLvoid *)popBuf());
}


//419
static void EXEC_glGetCompressedTexImage(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glGetCompressedTexImage(*target, *level, (GLvoid *)popBuf());
}


//420
static void EXEC_glBlendFuncSeparate(char *commandbuf)
{
	GLenum *sfactorRGB = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *dfactorRGB = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *sfactorAlpha = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *dfactorAlpha = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glBlendFuncSeparate(*sfactorRGB, *dfactorRGB, *sfactorAlpha, *dfactorAlpha);
}


//421
static void EXEC_glFogCoordf(char *commandbuf)
{
	GLfloat *coord = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glFogCoordf(*coord);
}


//422
static void EXEC_glFogCoordfv(char *commandbuf)
{
	glFogCoordfv((const GLfloat *)popBuf());
}


//423
static void EXEC_glFogCoordd(char *commandbuf)
{
	GLdouble *coord = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glFogCoordd(*coord);
}


//424
static void EXEC_glFogCoorddv(char *commandbuf)
{

	glFogCoorddv((const GLdouble *)popBuf());
}


//425
static void EXEC_glFogCoordPointer(char *commandbuf)
{
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glFogCoordPointer(*type, *stride, (const GLvoid *)popBuf());
}


//426
static void EXEC_glMultiDrawArrays(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *primcount = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glMultiDrawArrays(*mode, (GLint *)popBuf(), (GLsizei *)popBuf(), *primcount);
}


//427
static void EXEC_glMultiDrawElements(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *primcount = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glMultiDrawElements(*mode, (GLsizei *)popBuf(), *type, (const GLvoid **)popBuf(), *primcount);
}


//428
static void EXEC_glPointParameterf(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glPointParameterf(*pname, *param);
}


//429
static void EXEC_glPointParameterfv(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glPointParameterfv(*pname, (GLfloat *)popBuf());
}


//430
static void EXEC_glPointParameteri(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	//TODO: why does this exist?
	#ifndef SYMPHONY
	glPointParameteri(*pname, *param);
	#endif
}


//431
static void EXEC_glPointParameteriv(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	//TODO: why does this exist?
	#ifndef SYMPHONY
	glPointParameteriv(*pname, (GLint *)popBuf());
	#endif
}


//432
static void EXEC_glSecondaryColor3b(char *commandbuf)
{
	GLbyte *red = (GLbyte*)commandbuf;   commandbuf += sizeof(GLbyte);
	GLbyte *green = (GLbyte*)commandbuf;     commandbuf += sizeof(GLbyte);
	GLbyte *blue = (GLbyte*)commandbuf;  commandbuf += sizeof(GLbyte);

	glSecondaryColor3b(*red, *green, *blue);
}


//433
static void EXEC_glSecondaryColor3bv(char *commandbuf)
{

	glSecondaryColor3bv((const GLbyte *)popBuf());
}


//434
static void EXEC_glSecondaryColor3d(char *commandbuf)
{
	GLdouble *red = (GLdouble*)commandbuf;   commandbuf += sizeof(GLdouble);
	GLdouble *green = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *blue = (GLdouble*)commandbuf;  commandbuf += sizeof(GLdouble);

	glSecondaryColor3d(*red, *green, *blue);
}


//435
static void EXEC_glSecondaryColor3dv(char *commandbuf)
{

	glSecondaryColor3dv((const GLdouble *)popBuf());
}


//436
static void EXEC_glSecondaryColor3f(char *commandbuf)
{
	GLfloat *red = (GLfloat*)commandbuf;     commandbuf += sizeof(GLfloat);
	GLfloat *green = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *blue = (GLfloat*)commandbuf;    commandbuf += sizeof(GLfloat);

	glSecondaryColor3f(*red, *green, *blue);
}


//437
static void EXEC_glSecondaryColor3fv(char *commandbuf)
{

	glSecondaryColor3fv((const GLfloat *)popBuf());
}


//438
static void EXEC_glSecondaryColor3i(char *commandbuf)
{
	GLint *red = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *green = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *blue = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glSecondaryColor3i(*red, *green, *blue);
}


//439
static void EXEC_glSecondaryColor3iv(char *commandbuf)
{

	glSecondaryColor3iv((const GLint *)popBuf());
}


//440
static void EXEC_glSecondaryColor3s(char *commandbuf)
{
	GLshort *red = (GLshort*)commandbuf;     commandbuf += sizeof(GLshort);
	GLshort *green = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *blue = (GLshort*)commandbuf;    commandbuf += sizeof(GLshort);

	glSecondaryColor3s(*red, *green, *blue);
}


//441
static void EXEC_glSecondaryColor3sv(char *commandbuf)
{

	glSecondaryColor3sv((const GLshort *)popBuf());
}


//442
static void EXEC_glSecondaryColor3ub(char *commandbuf)
{
	GLubyte *red = (GLubyte*)commandbuf;     commandbuf += sizeof(GLubyte);
	GLubyte *green = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *blue = (GLubyte*)commandbuf;    commandbuf += sizeof(GLubyte);

	glSecondaryColor3ub(*red, *green, *blue);
}


//443
static void EXEC_glSecondaryColor3ubv(char *commandbuf)
{

	glSecondaryColor3ubv((const GLubyte *)popBuf());
}


//444
static void EXEC_glSecondaryColor3ui(char *commandbuf)
{
	GLuint *red = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *green = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLuint *blue = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

	glSecondaryColor3ui(*red, *green, *blue);
}


//445
static void EXEC_glSecondaryColor3uiv(char *commandbuf)
{

	glSecondaryColor3uiv((const GLuint *)popBuf());
}


//446
static void EXEC_glSecondaryColor3us(char *commandbuf)
{
	GLushort *red = (GLushort*)commandbuf;   commandbuf += sizeof(GLushort);
	GLushort *green = (GLushort*)commandbuf;     commandbuf += sizeof(GLushort);
	GLushort *blue = (GLushort*)commandbuf;  commandbuf += sizeof(GLushort);

	glSecondaryColor3us(*red, *green, *blue);
}


//447
static void EXEC_glSecondaryColor3usv(char *commandbuf)
{

	glSecondaryColor3usv((const GLushort *)popBuf());
}


//448
static void EXEC_glSecondaryColorPointer(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glSecondaryColorPointer(*size, *type, *stride, (GLvoid *)popBuf());
}


//449
static void EXEC_glWindowPos2d(char *commandbuf)
{
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glWindowPos2d(*x, *y);
}


//450
static void EXEC_glWindowPos2dv(char *commandbuf)
{

	glWindowPos2dv((const GLdouble *)popBuf());
}


//451
static void EXEC_glWindowPos2f(char *commandbuf)
{
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glWindowPos2f(*x, *y);
}


//452
static void EXEC_glWindowPos2fv(char *commandbuf)
{

	glWindowPos2fv((const GLfloat *)popBuf());
}


//453
static void EXEC_glWindowPos2i(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glWindowPos2i(*x, *y);
}


//454
static void EXEC_glWindowPos2iv(char *commandbuf)
{

	glWindowPos2iv((const GLint *)popBuf());
}


//455
static void EXEC_glWindowPos2s(char *commandbuf)
{
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glWindowPos2s(*x, *y);
}


//456
static void EXEC_glWindowPos2sv(char *commandbuf)
{

	glWindowPos2sv((const GLshort *)popBuf());
}


//457
static void EXEC_glWindowPos3d(char *commandbuf)
{
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glWindowPos3d(*x, *y, *z);
}


//458
static void EXEC_glWindowPos3dv(char *commandbuf)
{

	glWindowPos3dv((const GLdouble *)popBuf());
}


//459
static void EXEC_glWindowPos3f(char *commandbuf)
{
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glWindowPos3f(*x, *y, *z);
}


//460
static void EXEC_glWindowPos3fv(char *commandbuf)
{

	glWindowPos3fv((const GLfloat *)popBuf());
}


//461
static void EXEC_glWindowPos3i(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *z = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glWindowPos3i(*x, *y, *z);
}


//462
static void EXEC_glWindowPos3iv(char *commandbuf)
{

	glWindowPos3iv((const GLint *)popBuf());
}


//463
static void EXEC_glWindowPos3s(char *commandbuf)
{
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *z = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glWindowPos3s(*x, *y, *z);
}


//464
static void EXEC_glWindowPos3sv(char *commandbuf)
{

	glWindowPos3sv((const GLshort *)popBuf());
}


//465
static void EXEC_glBindBuffer(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *buffer = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	glBindBuffer(*target, *buffer);
}


//466
static void EXEC_glBufferData(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizeiptr *size = (GLsizeiptr*)commandbuf;  commandbuf += sizeof(GLsizeiptr);
	GLenum *usage = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glBufferData(*target, *size, (const GLvoid *)popBuf(), *usage);
}


//467
static void EXEC_glBufferSubData(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLintptr *offset = (GLintptr*)commandbuf;    commandbuf += sizeof(GLintptr);
	GLsizeiptr *size = (GLsizeiptr*)commandbuf;  commandbuf += sizeof(GLsizeiptr);

	glBufferSubData(*target, *offset, *size, (const GLvoid *)popBuf());
}


//468
static void EXEC_glDeleteBuffers(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glDeleteBuffers(*n, (const GLuint *)popBuf());
}


//469
static void EXEC_glGenBuffers(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glGenBuffers(*n, (GLuint *)popBuf());
}


//470
static void EXEC_glGetBufferParameteriv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetBufferParameteriv(*target, *pname, (GLint *)popBuf());
}


//471
static void EXEC_glGetBufferPointerv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetBufferPointerv(*target, *pname, (GLvoid **)popBuf());
}


//472
static void EXEC_glGetBufferSubData(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLintptr *offset = (GLintptr*)commandbuf;    commandbuf += sizeof(GLintptr);
	GLsizeiptr *size = (GLsizeiptr*)commandbuf;  commandbuf += sizeof(GLsizeiptr);

	glGetBufferSubData(*target, *offset, *size, (GLvoid *)popBuf());
}


//473
static void EXEC_glIsBuffer(char *commandbuf)
{
	GLuint *buffer = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	pushRet(glIsBuffer(*buffer));
}


//474
static void EXEC_glMapBuffer(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *access = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	pushRet((const GLubyte*)glMapBuffer(*target, *access));

}


//475
static void EXEC_glUnmapBuffer(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	pushRet(glUnmapBuffer(*target));
}


//476
static void EXEC_glGenQueries(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glGenQueries(*n, (GLuint *)popBuf());
}


//477
static void EXEC_glDeleteQueries(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glDeleteQueries(*n, (const GLuint *)popBuf());
}


//478
static void EXEC_glIsQuery(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	pushRet(glIsQuery(*id));
}


//479
static void EXEC_glBeginQuery(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	glBeginQuery(*target, *id);
}


//480
static void EXEC_glEndQuery(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glEndQuery(*target);
}


//481
static void EXEC_glGetQueryiv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetQueryiv(*target, *pname, (GLint *)popBuf());
}


//482
static void EXEC_glGetQueryObjectiv(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetQueryObjectiv(*id, *pname, (GLint *)popBuf());
}


//483
static void EXEC_glGetQueryObjectuiv(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetQueryObjectuiv(*id, *pname, (GLuint *)popBuf());
}


//484
static void EXEC_glBlendEquationSeparate(char *commandbuf)
{
	GLenum *modeRGB = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);
	GLenum *modeA = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glBlendEquationSeparate(*modeRGB, *modeA);
}


//485
static void EXEC_glDrawBuffers(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glDrawBuffers(*n, (const GLenum *)popBuf());
}


//486
static void EXEC_glStencilFuncSeparate(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *func = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLint *ref = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLuint *mask = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

	glStencilFuncSeparate(*face, *func, *ref, *mask);
}


//487
static void EXEC_glStencilOpSeparate(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *sfail = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *zfail = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *zpass = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glStencilOpSeparate(*face, *sfail, *zfail, *zpass);
}


//488
static void EXEC_glStencilMaskSeparate(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLuint *mask = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

	glStencilMaskSeparate(*face, *mask);
}


//489
static void EXEC_glAttachShader(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *shader = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	glAttachShader(*program, *shader);
}


//490
static void EXEC_glBindAttribLocation(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glBindAttribLocation(*program, *index, (const GLchar *)popBuf());
}


//491
static void EXEC_glCompileShader(char *commandbuf)
{
	GLuint *shader = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	glCompileShader(*shader);
}


//492
static void EXEC_glCreateProgram(char *commandbuf)
{

	pushRet(glCreateProgram());
}


//493
static void EXEC_glCreateShader(char *commandbuf)
{
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	pushRet(glCreateShader(*type));
}


//494
static void EXEC_glDeleteProgram(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	glDeleteProgram(*program);
}


//495
static void EXEC_glDeleteShader(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	glDeleteShader(*program);
}


//496
static void EXEC_glDetachShader(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *shader = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	glDetachShader(*program, *shader);
}


//497
static void EXEC_glDisableVertexAttribArray(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glDisableVertexAttribArray(*index);
}


//498
static void EXEC_glEnableVertexAttribArray(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glEnableVertexAttribArray(*index);
}


//499
static void EXEC_glGetActiveAttrib(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei  *bufSize = (GLsizei *)commandbuf;   commandbuf += sizeof(GLsizei );

	glGetActiveAttrib(*program, *index, *bufSize, (GLsizei *)popBuf(), (GLint *)popBuf(), (GLenum *)popBuf(), (GLchar *)popBuf());
}


//500
static void EXEC_glGetActiveUniform(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *bufSize = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);

	glGetActiveUniform(*program, *index, *bufSize, (GLsizei *)popBuf(), (GLint *)popBuf(), (GLenum *)popBuf(), (GLchar *)popBuf());
}


//501
static void EXEC_glGetAttachedShaders(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLsizei *maxCount = (GLsizei*)commandbuf;    commandbuf += sizeof(GLsizei);

	glGetAttachedShaders(*program, *maxCount, (GLsizei *)popBuf(), (GLuint *)popBuf());
}


//502
static void EXEC_glGetAttribLocation(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	pushRet(glGetAttribLocation(*program, (const GLchar *)popBuf()));
}


//503
static void EXEC_glGetProgramiv(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetProgramiv(*program, *pname, (GLint *)popBuf());
}


//504
static void EXEC_glGetProgramInfoLog(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLsizei *bufSize = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);

	glGetProgramInfoLog(*program, *bufSize, (GLsizei *)popBuf(), (GLchar *)popBuf());
}


//505
static void EXEC_glGetShaderiv(char *commandbuf)
{
	GLuint *shader = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint   *params = (GLint *)popBuf();
	glGetShaderiv(*shader, *pname, params);
	pushRet(*params);
}


//506
static void EXEC_glGetShaderInfoLog(char *commandbuf)
{
	GLuint  *shader  = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);
	GLsizei *bufSize = (GLsizei*)commandbuf; commandbuf += sizeof(GLsizei);
	GLint   *length  = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLchar  *infolog = (GLchar *)popBuf();
	if(*length == -1) {
		length = NULL;
	}

	glGetShaderInfoLog(*shader, *bufSize, length, infolog);
	pushRet(infolog);
}


//507
static void EXEC_glGetShaderSource(char *commandbuf)
{
	GLuint *shader = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLsizei *bufSize = (GLsizei*)commandbuf; commandbuf += sizeof(GLsizei);
	GLint   *length  = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLchar  *source = (GLchar *)popBuf();
	if(*length == -1) {
		length = NULL;
	}

	glGetShaderSource(*shader, *bufSize, length, source);
}


//508
static void EXEC_glGetUniformLocation(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	pushRet(glGetUniformLocation(*program, (const GLchar *)popBuf()));
}


//509
static void EXEC_glGetUniformfv(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glGetUniformfv(*program, *location, (GLfloat *)popBuf());
}


//510
static void EXEC_glGetUniformiv(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glGetUniformiv(*program, *location, (GLint *)popBuf());
}


//511
static void EXEC_glGetVertexAttribdv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetVertexAttribdv(*index, *pname, (GLdouble *)popBuf());
}


//512
static void EXEC_glGetVertexAttribfv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetVertexAttribfv(*index, *pname, (GLfloat *)popBuf());
}


//513
static void EXEC_glGetVertexAttribiv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetVertexAttribiv(*index, *pname, (GLint *)popBuf());
}


//514
static void EXEC_glGetVertexAttribPointerv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetVertexAttribPointerv(*index, *pname, (GLvoid **)popBuf());
}


//515
static void EXEC_glIsProgram(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	pushRet(glIsProgram(*program));
}


//516
static void EXEC_glIsShader(char *commandbuf)
{
	GLuint *shader = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	pushRet(glIsShader(*shader));
}


//517
static void EXEC_glLinkProgram(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	glLinkProgram(*program);
}


//518
static void EXEC_glShaderSource(char *commandbuf)
{
	GLuint *shader = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	const GLchar * string = (const GLchar *)popBuf();
	GLint   *length = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	if(*length == -1) {
		length = NULL;
	}

	glShaderSource(*shader, *count, &string, length);
}


//519
static void EXEC_glUseProgram(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	glUseProgram(*program);
}


//520
static void EXEC_glUniform1f(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLfloat *v0 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	glUniform1f(*location, *v0);
}


//521
static void EXEC_glUniform2f(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLfloat *v0 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *v1 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	glUniform2f(*location, *v0, *v1);
}


//522
static void EXEC_glUniform3f(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLfloat *v0 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *v1 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *v2 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	glUniform3f(*location, *v0, *v1, *v2);
}


//523
static void EXEC_glUniform4f(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLfloat *v0 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *v1 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *v2 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *v3 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	glUniform4f(*location, *v0, *v1, *v2, *v3);
}


//524
static void EXEC_glUniform1i(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLint *v0 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glUniform1i(*location, *v0);
}


//525
static void EXEC_glUniform2i(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLint *v0 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *v1 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glUniform2i(*location, *v0, *v1);
}


//526
static void EXEC_glUniform3i(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLint *v0 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *v1 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *v2 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glUniform3i(*location, *v0, *v1, *v2);
}


//527
static void EXEC_glUniform4i(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLint *v0 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *v1 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *v2 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *v3 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glUniform4i(*location, *v0, *v1, *v2, *v3);
}


//528
static void EXEC_glUniform1fv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glUniform1fv(*location, *count, (const GLfloat *)popBuf());
}


//529
static void EXEC_glUniform2fv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glUniform2fv(*location, *count, (const GLfloat *)popBuf());
}


//530
static void EXEC_glUniform3fv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glUniform3fv(*location, *count, (const GLfloat *)popBuf());
}


//531
static void EXEC_glUniform4fv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glUniform4fv(*location, *count, (const GLfloat *)popBuf());
}


//532
static void EXEC_glUniform1iv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glUniform1iv(*location, *count, (const GLint *)popBuf());
}


//533
static void EXEC_glUniform2iv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glUniform2iv(*location, *count, (const GLint *)popBuf());
}


//534
static void EXEC_glUniform3iv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glUniform3iv(*location, *count, (const GLint *)popBuf());
}


//535
static void EXEC_glUniform4iv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glUniform4iv(*location, *count, (const GLint *)popBuf());
}


//536
static void EXEC_glUniformMatrix2fv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLboolean *transpose = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);

	glUniformMatrix2fv(*location, *count, *transpose, (const GLfloat *)popBuf());
}


//537
static void EXEC_glUniformMatrix3fv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLboolean *transpose = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);

	glUniformMatrix3fv(*location, *count, *transpose, (const GLfloat *)popBuf());
}


//538
static void EXEC_glUniformMatrix4fv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLboolean *transpose = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);

	glUniformMatrix4fv(*location, *count, *transpose, (const GLfloat *)popBuf());
}


//539
static void EXEC_glValidateProgram(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	glValidateProgram(*program);
}


//540
static void EXEC_glVertexAttrib1d(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glVertexAttrib1d(*index, *x);
}


//541
static void EXEC_glVertexAttrib1dv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib1dv(*index, (const GLdouble *)popBuf());
}


//542
static void EXEC_glVertexAttrib1f(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glVertexAttrib1f(*index, *x);
}


//543
static void EXEC_glVertexAttrib1fv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib1fv(*index, (const GLfloat *)popBuf());
}


//544
static void EXEC_glVertexAttrib1s(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glVertexAttrib1s(*index, *x);
}


//545
static void EXEC_glVertexAttrib1sv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib1sv(*index, (const GLshort *)popBuf());
}


//546
static void EXEC_glVertexAttrib2d(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glVertexAttrib2d(*index, *x, *y);
}


//547
static void EXEC_glVertexAttrib2dv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib2dv(*index, (const GLdouble *)popBuf());
}


//548
static void EXEC_glVertexAttrib2f(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glVertexAttrib2f(*index, *x, *y);
}


//549
static void EXEC_glVertexAttrib2fv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib2fv(*index, (const GLfloat *)popBuf());
}


//550
static void EXEC_glVertexAttrib2s(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glVertexAttrib2s(*index, *x, *y);
}


//551
static void EXEC_glVertexAttrib2sv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib2sv(*index, (const GLshort *)popBuf());
}


//552
static void EXEC_glVertexAttrib3d(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glVertexAttrib3d(*index, *x, *y, *z);
}


//553
static void EXEC_glVertexAttrib3dv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib3dv(*index, (const GLdouble *)popBuf());
}


//554
static void EXEC_glVertexAttrib3f(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glVertexAttrib3f(*index, *x, *y, *z);
}


//555
static void EXEC_glVertexAttrib3fv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib3fv(*index, (const GLfloat *)popBuf());
}


//556
static void EXEC_glVertexAttrib3s(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *z = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glVertexAttrib3s(*index, *x, *y, *z);
}


//557
static void EXEC_glVertexAttrib3sv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib3sv(*index, (const GLshort *)popBuf());
}


//558
static void EXEC_glVertexAttrib4Nbv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4Nbv(*index, (const GLbyte *)popBuf());
}


//559
static void EXEC_glVertexAttrib4Niv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4Niv(*index, (const GLint *)popBuf());
}


//560
static void EXEC_glVertexAttrib4Nsv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4Nsv(*index, (const GLshort *)popBuf());
}


//561
static void EXEC_glVertexAttrib4Nub(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLubyte *x = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *y = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *z = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *w = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);

	glVertexAttrib4Nub(*index, *x, *y, *z, *w);
}


//562
static void EXEC_glVertexAttrib4Nubv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4Nubv(*index, (const GLubyte *)popBuf());
}


//563
static void EXEC_glVertexAttrib4Nuiv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4Nuiv(*index, (const GLuint *)popBuf());
}


//564
static void EXEC_glVertexAttrib4Nusv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4Nusv(*index, (const GLushort *)popBuf());
}


//565
static void EXEC_glVertexAttrib4bv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4bv(*index, (const GLbyte *)popBuf());
}


//566
static void EXEC_glVertexAttrib4d(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *w = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glVertexAttrib4d(*index, *x, *y, *z, *w);
}


//567
static void EXEC_glVertexAttrib4dv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4dv(*index, (const GLdouble *)popBuf());
}


//568
static void EXEC_glVertexAttrib4f(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *w = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glVertexAttrib4f(*index, *x, *y, *z, *w);
}


//569
static void EXEC_glVertexAttrib4fv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4fv(*index, (const GLfloat *)popBuf());
}


//570
static void EXEC_glVertexAttrib4iv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4iv(*index, (const GLint *)popBuf());
}


//571
static void EXEC_glVertexAttrib4s(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *z = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *w = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glVertexAttrib4s(*index, *x, *y, *z, *w);
}


//572
static void EXEC_glVertexAttrib4sv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4sv(*index, (const GLshort *)popBuf());
}


//573
static void EXEC_glVertexAttrib4ubv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4ubv(*index, (const GLubyte *)popBuf());
}


//574
static void EXEC_glVertexAttrib4uiv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4uiv(*index, (const GLuint *)popBuf());
}


//575
static void EXEC_glVertexAttrib4usv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4usv(*index, (const GLushort *)popBuf());
}


//576
static void EXEC_glVertexAttribPointer(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLboolean *normalized = (GLboolean*)commandbuf;  commandbuf += sizeof(GLboolean);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glVertexAttribPointer(*index, *size, *type, *normalized, *stride, (const GLvoid *)popBuf());
}


//577
static void EXEC_glUniformMatrix2x3fv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLboolean *transpose = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);

	//TODO: why does this exist?
	#ifndef SYMPHONY
	glUniformMatrix2x3fv(*location, *count, *transpose, (const GLfloat *)popBuf());
	#endif
}


//578
static void EXEC_glUniformMatrix3x2fv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLboolean *transpose = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);

	#ifndef SYMPHONY
	glUniformMatrix3x2fv(*location, *count, *transpose, (const GLfloat *)popBuf());
	#endif
}


//579
static void EXEC_glUniformMatrix2x4fv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLboolean *transpose = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);

	#ifndef SYMPHONY
	glUniformMatrix2x4fv(*location, *count, *transpose, (const GLfloat *)popBuf());
	#endif
}


//580
static void EXEC_glUniformMatrix4x2fv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLboolean *transpose = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);

	#ifndef SYMPHONY
	glUniformMatrix4x2fv(*location, *count, *transpose, (const GLfloat *)popBuf());
	#endif
}


//581
static void EXEC_glUniformMatrix3x4fv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLboolean *transpose = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);

	#ifndef SYMPHONY
	glUniformMatrix3x4fv(*location, *count, *transpose, (const GLfloat *)popBuf());
	#endif
}


//582
static void EXEC_glUniformMatrix4x3fv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLboolean *transpose = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);

	#ifndef SYMPHONY
	glUniformMatrix4x3fv(*location, *count, *transpose, (const GLfloat *)popBuf());
	#endif
}


//374
static void EXEC_glActiveTextureARB(char *commandbuf)
{
	GLenum *texture = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);

	glActiveTextureARB(*texture);
}


//375
static void EXEC_glClientActiveTextureARB(char *commandbuf)
{
	GLenum *texture = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);

	glClientActiveTextureARB(*texture);
}


//376
static void EXEC_glMultiTexCoord1dARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLdouble *s = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glMultiTexCoord1dARB(*target, *s);
}


//377
static void EXEC_glMultiTexCoord1dvARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord1dvARB(*target, (const GLdouble *)popBuf());
}


//378
static void EXEC_glMultiTexCoord1fARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glMultiTexCoord1fARB(*target, *s);
}


//379
static void EXEC_glMultiTexCoord1fvARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord1fvARB(*target, (const GLfloat *)popBuf());
}


//380
static void EXEC_glMultiTexCoord1iARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *s = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glMultiTexCoord1iARB(*target, *s);
}


//381
static void EXEC_glMultiTexCoord1ivARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord1ivARB(*target, (const GLint *)popBuf());
}


//382
static void EXEC_glMultiTexCoord1sARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLshort *s = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glMultiTexCoord1sARB(*target, *s);
}


//383
static void EXEC_glMultiTexCoord1svARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord1svARB(*target, (const GLshort *)popBuf());
}


//384
static void EXEC_glMultiTexCoord2dARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLdouble *s = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *t = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glMultiTexCoord2dARB(*target, *s, *t);
}


//385
static void EXEC_glMultiTexCoord2dvARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord2dvARB(*target, (const GLdouble *)popBuf());
}


//386
static void EXEC_glMultiTexCoord2fARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *t = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glMultiTexCoord2fARB(*target, *s, *t);
}


//387
static void EXEC_glMultiTexCoord2fvARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord2fvARB(*target, (const GLfloat *)popBuf());
}


//388
static void EXEC_glMultiTexCoord2iARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *s = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *t = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glMultiTexCoord2iARB(*target, *s, *t);
}


//389
static void EXEC_glMultiTexCoord2ivARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord2ivARB(*target, (const GLint *)popBuf());
}


//390
static void EXEC_glMultiTexCoord2sARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLshort *s = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *t = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glMultiTexCoord2sARB(*target, *s, *t);
}


//391
static void EXEC_glMultiTexCoord2svARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord2svARB(*target, (const GLshort *)popBuf());
}


//392
static void EXEC_glMultiTexCoord3dARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLdouble *s = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *t = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *r = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glMultiTexCoord3dARB(*target, *s, *t, *r);
}


//393
static void EXEC_glMultiTexCoord3dvARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord3dvARB(*target, (const GLdouble *)popBuf());
}


//394
static void EXEC_glMultiTexCoord3fARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *t = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *r = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glMultiTexCoord3fARB(*target, *s, *t, *r);
}


//395
static void EXEC_glMultiTexCoord3fvARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord3fvARB(*target, (const GLfloat *)popBuf());
}


//396
static void EXEC_glMultiTexCoord3iARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *s = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *t = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *r = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glMultiTexCoord3iARB(*target, *s, *t, *r);
}


//397
static void EXEC_glMultiTexCoord3ivARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord3ivARB(*target, (const GLint *)popBuf());
}


//398
static void EXEC_glMultiTexCoord3sARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLshort *s = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *t = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *r = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glMultiTexCoord3sARB(*target, *s, *t, *r);
}


//399
static void EXEC_glMultiTexCoord3svARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord3svARB(*target, (const GLshort *)popBuf());
}


//400
static void EXEC_glMultiTexCoord4dARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLdouble *s = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *t = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *r = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *q = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glMultiTexCoord4dARB(*target, *s, *t, *r, *q);
}


//401
static void EXEC_glMultiTexCoord4dvARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord4dvARB(*target, (const GLdouble *)popBuf());
}


//402
static void EXEC_glMultiTexCoord4fARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *t = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *r = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *q = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glMultiTexCoord4fARB(*target, *s, *t, *r, *q);
}


//403
static void EXEC_glMultiTexCoord4fvARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord4fvARB(*target, (const GLfloat *)popBuf());
}


//404
static void EXEC_glMultiTexCoord4iARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *s = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *t = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *r = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *q = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glMultiTexCoord4iARB(*target, *s, *t, *r, *q);
}


//405
static void EXEC_glMultiTexCoord4ivARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord4ivARB(*target, (const GLint *)popBuf());
}


//406
static void EXEC_glMultiTexCoord4sARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLshort *s = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *t = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *r = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *q = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glMultiTexCoord4sARB(*target, *s, *t, *r, *q);
}


//407
static void EXEC_glMultiTexCoord4svARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord4svARB(*target, (const GLshort *)popBuf());
}


//617
static void EXEC_glLoadTransposeMatrixfARB(char *commandbuf)
{

	glLoadTransposeMatrixfARB((GLfloat *)popBuf());
}


//618
static void EXEC_glLoadTransposeMatrixdARB(char *commandbuf)
{

	glLoadTransposeMatrixdARB((GLdouble *)popBuf());
}


//619
static void EXEC_glMultTransposeMatrixfARB(char *commandbuf)
{

	glMultTransposeMatrixfARB((GLfloat *)popBuf());
}


//620
static void EXEC_glMultTransposeMatrixdARB(char *commandbuf)
{

	glMultTransposeMatrixdARB((GLdouble *)popBuf());
}


//621
static void EXEC_glSampleCoverageARB(char *commandbuf)
{
	GLclampf *value = (GLclampf*)commandbuf;     commandbuf += sizeof(GLclampf);
	GLboolean *invert = (GLboolean*)commandbuf;  commandbuf += sizeof(GLboolean);

	glSampleCoverageARB(*value, *invert);
}


//622
static void EXEC_glCompressedTexImage3DARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLsizei *depth = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLint *border = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLsizei *imageSize = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glCompressedTexImage3DARB(*target, *level, *internalformat, *width, *height, *depth, *border, *imageSize, (const GLvoid *)popBuf());
}


//623
static void EXEC_glCompressedTexImage2DARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLint *border = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLsizei *imageSize = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glCompressedTexImage2DARB(*target, *level, *internalformat, *width, *height, *border, *imageSize, (const GLvoid *)popBuf());
}


//624
static void EXEC_glCompressedTexImage1DARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLint *border = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLsizei *imageSize = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glCompressedTexImage1DARB(*target, *level, *internalformat, *width, *border, *imageSize, (const GLvoid *)popBuf());
}


//625
static void EXEC_glCompressedTexSubImage3DARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *xoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *yoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *zoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLsizei *depth = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *imageSize = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glCompressedTexSubImage3DARB(*target, *level, *xoffset, *yoffset, *zoffset, *width, *height, *depth, *format, *imageSize, (const GLvoid *)popBuf());
}


//626
static void EXEC_glCompressedTexSubImage2DARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *xoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *yoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *imageSize = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glCompressedTexSubImage2DARB(*target, *level, *xoffset, *yoffset, *width, *height, *format, *imageSize, (const GLvoid *)popBuf());
}


//627
static void EXEC_glCompressedTexSubImage1DARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *xoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *imageSize = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glCompressedTexSubImage1DARB(*target, *level, *xoffset, *width, *format, *imageSize, (const GLvoid *)popBuf());
}


//628
static void EXEC_glGetCompressedTexImageARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glGetCompressedTexImageARB(*target, *level, (GLvoid *)popBuf());
}


//629
static void EXEC_glPointParameterfARB(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glPointParameterfARB(*pname, *param);
}


//630
static void EXEC_glPointParameterfvARB(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glPointParameterfvARB(*pname, (GLfloat *)popBuf());
}


//631
static void EXEC_glWeightbvARB(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glWeightbvARB(*size, (GLbyte *)popBuf());
}


//632
static void EXEC_glWeightsvARB(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glWeightsvARB(*size, (GLshort *)popBuf());
}


//633
static void EXEC_glWeightivARB(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glWeightivARB(*size, (GLint *)popBuf());
}


//634
static void EXEC_glWeightfvARB(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glWeightfvARB(*size, (GLfloat *)popBuf());
}


//635
static void EXEC_glWeightdvARB(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glWeightdvARB(*size, (GLdouble *)popBuf());
}


//636
static void EXEC_glWeightubvARB(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glWeightubvARB(*size, (GLubyte *)popBuf());
}


//637
static void EXEC_glWeightusvARB(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glWeightusvARB(*size, (GLushort *)popBuf());
}


//638
static void EXEC_glWeightuivARB(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glWeightuivARB(*size, (GLuint *)popBuf());
}


//639
static void EXEC_glWeightPointerARB(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glWeightPointerARB(*size, *type, *stride, (GLvoid *)popBuf());
}


//640
static void EXEC_glVertexBlendARB(char *commandbuf)
{
	GLint *count = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glVertexBlendARB(*count);
}


//641
static void EXEC_glCurrentPaletteMatrixARB(char *commandbuf)
{
	GLint *index = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glCurrentPaletteMatrixARB(*index);
}


//642
static void EXEC_glMatrixIndexubvARB(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glMatrixIndexubvARB(*size, (GLubyte *)popBuf());
}


//643
static void EXEC_glMatrixIndexusvARB(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glMatrixIndexusvARB(*size, (GLushort *)popBuf());
}


//644
static void EXEC_glMatrixIndexuivARB(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glMatrixIndexuivARB(*size, (GLuint *)popBuf());
}


//645
static void EXEC_glMatrixIndexPointerARB(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glMatrixIndexPointerARB(*size, *type, *stride, (GLvoid *)popBuf());
}


//646
static void EXEC_glWindowPos2dARB(char *commandbuf)
{
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glWindowPos2dARB(*x, *y);
}


//647
static void EXEC_glWindowPos2fARB(char *commandbuf)
{
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glWindowPos2fARB(*x, *y);
}


//648
static void EXEC_glWindowPos2iARB(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glWindowPos2iARB(*x, *y);
}


//649
static void EXEC_glWindowPos2sARB(char *commandbuf)
{
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glWindowPos2sARB(*x, *y);
}


//650
static void EXEC_glWindowPos2dvARB(char *commandbuf)
{

	glWindowPos2dvARB((const GLdouble *)popBuf());
}


//651
static void EXEC_glWindowPos2fvARB(char *commandbuf)
{

	glWindowPos2fvARB((const GLfloat *)popBuf());
}


//652
static void EXEC_glWindowPos2ivARB(char *commandbuf)
{

	glWindowPos2ivARB((const GLint *)popBuf());
}


//653
static void EXEC_glWindowPos2svARB(char *commandbuf)
{

	glWindowPos2svARB((const GLshort *)popBuf());
}


//654
static void EXEC_glWindowPos3dARB(char *commandbuf)
{
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glWindowPos3dARB(*x, *y, *z);
}


//655
static void EXEC_glWindowPos3fARB(char *commandbuf)
{
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glWindowPos3fARB(*x, *y, *z);
}


//656
static void EXEC_glWindowPos3iARB(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *z = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glWindowPos3iARB(*x, *y, *z);
}


//657
static void EXEC_glWindowPos3sARB(char *commandbuf)
{
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *z = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glWindowPos3sARB(*x, *y, *z);
}


//658
static void EXEC_glWindowPos3dvARB(char *commandbuf)
{

	glWindowPos3dvARB((const GLdouble *)popBuf());
}


//659
static void EXEC_glWindowPos3fvARB(char *commandbuf)
{

	glWindowPos3fvARB((const GLfloat *)popBuf());
}


//660
static void EXEC_glWindowPos3ivARB(char *commandbuf)
{

	glWindowPos3ivARB((const GLint *)popBuf());
}


//661
static void EXEC_glWindowPos3svARB(char *commandbuf)
{

	glWindowPos3svARB((const GLshort *)popBuf());
}


//662
static void EXEC_glGetVertexAttribdvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetVertexAttribdvARB(*index, *pname, (GLdouble *)popBuf());
}


//663
static void EXEC_glGetVertexAttribfvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetVertexAttribfvARB(*index, *pname, (GLfloat *)popBuf());
}


//664
static void EXEC_glGetVertexAttribivARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetVertexAttribivARB(*index, *pname, (GLint *)popBuf());
}


//665
static void EXEC_glVertexAttrib1dARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glVertexAttrib1dARB(*index, *x);
}


//666
static void EXEC_glVertexAttrib1dvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib1dvARB(*index, (const GLdouble *)popBuf());
}


//667
static void EXEC_glVertexAttrib1fARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glVertexAttrib1fARB(*index, *x);
}


//668
static void EXEC_glVertexAttrib1fvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib1fvARB(*index, (const GLfloat *)popBuf());
}


//669
static void EXEC_glVertexAttrib1sARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glVertexAttrib1sARB(*index, *x);
}


//670
static void EXEC_glVertexAttrib1svARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib1svARB(*index, (const GLshort *)popBuf());
}


//671
static void EXEC_glVertexAttrib2dARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glVertexAttrib2dARB(*index, *x, *y);
}


//672
static void EXEC_glVertexAttrib2dvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib2dvARB(*index, (const GLdouble *)popBuf());
}


//673
static void EXEC_glVertexAttrib2fARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glVertexAttrib2fARB(*index, *x, *y);
}


//674
static void EXEC_glVertexAttrib2fvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib2fvARB(*index, (const GLfloat *)popBuf());
}


//675
static void EXEC_glVertexAttrib2sARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glVertexAttrib2sARB(*index, *x, *y);
}


//676
static void EXEC_glVertexAttrib2svARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib2svARB(*index, (const GLshort *)popBuf());
}


//677
static void EXEC_glVertexAttrib3dARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glVertexAttrib3dARB(*index, *x, *y, *z);
}


//678
static void EXEC_glVertexAttrib3dvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib3dvARB(*index, (const GLdouble *)popBuf());
}


//679
static void EXEC_glVertexAttrib3fARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glVertexAttrib3fARB(*index, *x, *y, *z);
}


//680
static void EXEC_glVertexAttrib3fvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib3fvARB(*index, (const GLfloat *)popBuf());
}


//681
static void EXEC_glVertexAttrib3sARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *z = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glVertexAttrib3sARB(*index, *x, *y, *z);
}


//682
static void EXEC_glVertexAttrib3svARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib3svARB(*index, (const GLshort *)popBuf());
}


//683
static void EXEC_glVertexAttrib4dARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *w = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glVertexAttrib4dARB(*index, *x, *y, *z, *w);
}


//684
static void EXEC_glVertexAttrib4dvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4dvARB(*index, (const GLdouble *)popBuf());
}


//685
static void EXEC_glVertexAttrib4fARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *w = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glVertexAttrib4fARB(*index, *x, *y, *z, *w);
}


//686
static void EXEC_glVertexAttrib4fvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4fvARB(*index, (const GLfloat *)popBuf());
}


//687
static void EXEC_glVertexAttrib4sARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *z = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *w = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glVertexAttrib4sARB(*index, *x, *y, *z, *w);
}


//688
static void EXEC_glVertexAttrib4svARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4svARB(*index, (const GLshort *)popBuf());
}


//689
static void EXEC_glVertexAttrib4NubARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLubyte *x = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *y = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *z = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *w = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);

	glVertexAttrib4NubARB(*index, *x, *y, *z, *w);
}


//690
static void EXEC_glVertexAttrib4NubvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4NubvARB(*index, (const GLubyte *)popBuf());
}


//691
static void EXEC_glVertexAttrib4bvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4bvARB(*index, (const GLbyte *)popBuf());
}


//692
static void EXEC_glVertexAttrib4ivARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4ivARB(*index, (const GLint *)popBuf());
}


//693
static void EXEC_glVertexAttrib4ubvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4ubvARB(*index, (const GLubyte *)popBuf());
}


//694
static void EXEC_glVertexAttrib4usvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4usvARB(*index, (const GLushort *)popBuf());
}


//695
static void EXEC_glVertexAttrib4uivARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4uivARB(*index, (const GLuint *)popBuf());
}


//696
static void EXEC_glVertexAttrib4NbvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4NbvARB(*index, (const GLbyte *)popBuf());
}


//697
static void EXEC_glVertexAttrib4NsvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4NsvARB(*index, (const GLshort *)popBuf());
}


//698
static void EXEC_glVertexAttrib4NivARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4NivARB(*index, (const GLint *)popBuf());
}


//699
static void EXEC_glVertexAttrib4NusvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4NusvARB(*index, (const GLushort *)popBuf());
}


//700
static void EXEC_glVertexAttrib4NuivARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4NuivARB(*index, (const GLuint *)popBuf());
}


//701
static void EXEC_glVertexAttribPointerARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLboolean *normalized = (GLboolean*)commandbuf;  commandbuf += sizeof(GLboolean);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glVertexAttribPointerARB(*index, *size, *type, *normalized, *stride, (const GLvoid *)popBuf());
}


//702
static void EXEC_glEnableVertexAttribArrayARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glEnableVertexAttribArrayARB(*index);
}


//703
static void EXEC_glDisableVertexAttribArrayARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glDisableVertexAttribArrayARB(*index);
}


//704
static void EXEC_glProgramStringARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *len = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);

	glProgramStringARB(*target, *format, *len, (const GLvoid *)popBuf());
}


//705
static void EXEC_glBindProgramARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	glBindProgramARB(*target, *program);
}


//706
static void EXEC_glDeleteProgramsARB(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glDeleteProgramsARB(*n, (const GLuint *)popBuf());
}


//707
static void EXEC_glGenProgramsARB(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glGenProgramsARB(*n, (GLuint *)popBuf());
}


//708
static void EXEC_glIsProgramARB(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	pushRet(glIsProgramARB(*program));
}


//709
static void EXEC_glProgramEnvParameter4dARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *w = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glProgramEnvParameter4dARB(*target, *index, *x, *y, *z, *w);
}


//710
static void EXEC_glProgramEnvParameter4dvARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glProgramEnvParameter4dvARB(*target, *index, (const GLdouble *)popBuf());
}


//711
static void EXEC_glProgramEnvParameter4fARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *w = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glProgramEnvParameter4fARB(*target, *index, *x, *y, *z, *w);
}


//712
static void EXEC_glProgramEnvParameter4fvARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glProgramEnvParameter4fvARB(*target, *index, (const GLfloat *)popBuf());
}


//713
static void EXEC_glProgramLocalParameter4dARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *w = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glProgramLocalParameter4dARB(*target, *index, *x, *y, *z, *w);
}


//714
static void EXEC_glProgramLocalParameter4dvARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glProgramLocalParameter4dvARB(*target, *index, (const GLdouble *)popBuf());
}


//715
static void EXEC_glProgramLocalParameter4fARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *w = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glProgramLocalParameter4fARB(*target, *index, *x, *y, *z, *w);
}


//716
static void EXEC_glProgramLocalParameter4fvARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glProgramLocalParameter4fvARB(*target, *index, (const GLfloat *)popBuf());
}


//717
static void EXEC_glGetProgramEnvParameterdvARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glGetProgramEnvParameterdvARB(*target, *index, (GLdouble *)popBuf());
}


//718
static void EXEC_glGetProgramEnvParameterfvARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glGetProgramEnvParameterfvARB(*target, *index, (GLfloat *)popBuf());
}


//719
static void EXEC_glGetProgramLocalParameterdvARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glGetProgramLocalParameterdvARB(*target, *index, (GLdouble *)popBuf());
}


//720
static void EXEC_glGetProgramLocalParameterfvARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glGetProgramLocalParameterfvARB(*target, *index, (GLfloat *)popBuf());
}


//721
static void EXEC_glGetProgramivARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetProgramivARB(*target, *pname, (GLint *)popBuf());
}


//722
static void EXEC_glGetProgramStringARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetProgramStringARB(*target, *pname, (GLvoid *)popBuf());
}


//723
static void EXEC_glGetVertexAttribPointervARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetVertexAttribPointervARB(*index, *pname, (GLvoid **)popBuf());
}


//724
static void EXEC_glBindBufferARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *buffer = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	glBindBufferARB(*target, *buffer);
}


//725
static void EXEC_glBufferDataARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizeiptrARB *size = (GLsizeiptrARB*)commandbuf;    commandbuf += sizeof(GLsizeiptrARB);
	GLenum *usage = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glBufferDataARB(*target, *size, (const GLvoid *)popBuf(), *usage);
}


//726
static void EXEC_glBufferSubDataARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLintptrARB *offset = (GLintptrARB*)commandbuf;  commandbuf += sizeof(GLintptrARB);
	GLsizeiptrARB *size = (GLsizeiptrARB*)commandbuf;    commandbuf += sizeof(GLsizeiptrARB);

	glBufferSubDataARB(*target, *offset, *size, (const GLvoid *)popBuf());
}


//727
static void EXEC_glDeleteBuffersARB(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glDeleteBuffersARB(*n, (const GLuint *)popBuf());
}


//728
static void EXEC_glGenBuffersARB(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glGenBuffersARB(*n, (GLuint *)popBuf());
}


//729
static void EXEC_glGetBufferParameterivARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetBufferParameterivARB(*target, *pname, (GLint *)popBuf());
}


//730
static void EXEC_glGetBufferPointervARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetBufferPointervARB(*target, *pname, (GLvoid **)popBuf());
}


//731
static void EXEC_glGetBufferSubDataARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLintptrARB *offset = (GLintptrARB*)commandbuf;  commandbuf += sizeof(GLintptrARB);
	GLsizeiptrARB *size = (GLsizeiptrARB*)commandbuf;    commandbuf += sizeof(GLsizeiptrARB);

	glGetBufferSubDataARB(*target, *offset, *size, (GLvoid *)popBuf());
}


//732
static void EXEC_glIsBufferARB(char *commandbuf)
{
	GLuint *buffer = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	pushRet(glIsBufferARB(*buffer));
}


//733
static void EXEC_glMapBufferARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *access = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	pushRet((const GLubyte*) glMapBufferARB(*target, *access));
}


//734
static void EXEC_glUnmapBufferARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	pushRet(glUnmapBufferARB(*target));
}


//735
static void EXEC_glGenQueriesARB(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glGenQueriesARB(*n, (GLuint *)popBuf());
}


//736
static void EXEC_glDeleteQueriesARB(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glDeleteQueriesARB(*n, (const GLuint *)popBuf());
}


//737
static void EXEC_glIsQueryARB(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	pushRet(glIsQueryARB(*id));
}


//738
static void EXEC_glBeginQueryARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	glBeginQueryARB(*target, *id);
}


//739
static void EXEC_glEndQueryARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glEndQueryARB(*target);
}


//740
static void EXEC_glGetQueryivARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetQueryivARB(*target, *pname, (GLint *)popBuf());
}


//741
static void EXEC_glGetQueryObjectivARB(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetQueryObjectivARB(*id, *pname, (GLint *)popBuf());
}


//742
static void EXEC_glGetQueryObjectuivARB(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetQueryObjectuivARB(*id, *pname, (GLuint *)popBuf());
}


//743
static void EXEC_glDeleteObjectARB(char *commandbuf)
{
	GLhandleARB *obj = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);

	glDeleteObjectARB(*obj);
}


//744
static void EXEC_glGetHandleARB(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	pushRet(glGetHandleARB(*pname));
}


//745
static void EXEC_glDetachObjectARB(char *commandbuf)
{
	GLhandleARB *containerObj = (GLhandleARB*)commandbuf;    commandbuf += sizeof(GLhandleARB);
	GLhandleARB *attachedObj = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);

	glDetachObjectARB(*containerObj, *attachedObj);
}


//746
static void EXEC_glCreateShaderObjectARB(char *commandbuf)
{
	GLenum *shaderType = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	pushRet(glCreateShaderObjectARB(*shaderType));
}


//747
static void EXEC_glShaderSourceARB(char *commandbuf)
{
	GLuint *shader = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	const GLchar * string = (const GLchar *)popBuf();
	GLint   *length = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	if(*length == -1) {
		length = NULL;
	}

	glShaderSourceARB(*shader, *count,  &string, length);
}


//748
static void EXEC_glCompileShaderARB(char *commandbuf)
{
	GLhandleARB *shader = (GLhandleARB*)commandbuf;  commandbuf += sizeof(GLhandleARB);

	glCompileShaderARB(*shader);
}


//749
static void EXEC_glCreateProgramObjectARB(char *commandbuf)
{

	pushRet(glCreateProgramObjectARB());
}


//750
static void EXEC_glAttachObjectARB(char *commandbuf)
{
	GLhandleARB *containerObj = (GLhandleARB*)commandbuf;    commandbuf += sizeof(GLhandleARB);
	GLhandleARB *obj = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);

	glAttachObjectARB(*containerObj, *obj);
}


//751
static void EXEC_glLinkProgramARB(char *commandbuf)
{
	GLhandleARB *program = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);

	glLinkProgramARB(*program);
}


//752
static void EXEC_glUseProgramObjectARB(char *commandbuf)
{
	GLhandleARB *program = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);

	glUseProgramObjectARB(*program);
}


//753
static void EXEC_glValidateProgramARB(char *commandbuf)
{
	GLhandleARB *program = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);

	glValidateProgramARB(*program);
}


//754
static void EXEC_glUniform1fARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLfloat *v0 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	glUniform1fARB(*location, *v0);
}


//755
static void EXEC_glUniform2fARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLfloat *v0 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *v1 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	glUniform2fARB(*location, *v0, *v1);
}


//756
static void EXEC_glUniform3fARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLfloat *v0 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *v1 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *v2 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	glUniform3fARB(*location, *v0, *v1, *v2);
}


//757
static void EXEC_glUniform4fARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLfloat *v0 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *v1 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *v2 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *v3 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	glUniform4fARB(*location, *v0, *v1, *v2, *v3);
}


//758
static void EXEC_glUniform1iARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLint *v0 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glUniform1iARB(*location, *v0);
}


//759
static void EXEC_glUniform2iARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLint *v0 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *v1 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glUniform2iARB(*location, *v0, *v1);
}


//760
static void EXEC_glUniform3iARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLint *v0 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *v1 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *v2 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glUniform3iARB(*location, *v0, *v1, *v2);
}


//761
static void EXEC_glUniform4iARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLint *v0 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *v1 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *v2 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *v3 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glUniform4iARB(*location, *v0, *v1, *v2, *v3);
}


//762
static void EXEC_glUniform1fvARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glUniform1fvARB(*location, *count, (const GLfloat *)popBuf());
}


//763
static void EXEC_glUniform2fvARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glUniform2fvARB(*location, *count, (const GLfloat *)popBuf());
}


//764
static void EXEC_glUniform3fvARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glUniform3fvARB(*location, *count, (const GLfloat *)popBuf());
}


//765
static void EXEC_glUniform4fvARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glUniform4fvARB(*location, *count, (const GLfloat *)popBuf());
}


//766
static void EXEC_glUniform1ivARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glUniform1ivARB(*location, *count, (const GLint *)popBuf());
}


//767
static void EXEC_glUniform2ivARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glUniform2ivARB(*location, *count, (const GLint *)popBuf());
}


//768
static void EXEC_glUniform3ivARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glUniform3ivARB(*location, *count, (const GLint *)popBuf());
}


//769
static void EXEC_glUniform4ivARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glUniform4ivARB(*location, *count, (const GLint *)popBuf());
}


//770
static void EXEC_glUniformMatrix2fvARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLboolean *transpose = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);

	glUniformMatrix2fvARB(*location, *count, *transpose, (const GLfloat *)popBuf());
}


//771
static void EXEC_glUniformMatrix3fvARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLboolean *transpose = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);

	glUniformMatrix3fvARB(*location, *count, *transpose, (const GLfloat *)popBuf());
}


//772
static void EXEC_glUniformMatrix4fvARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLboolean *transpose = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);

	glUniformMatrix4fvARB(*location, *count, *transpose, (const GLfloat *)popBuf());
}


//773
static void EXEC_glGetObjectParameterfvARB(char *commandbuf)
{
	GLhandleARB *obj = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetObjectParameterfvARB(*obj, *pname, (GLfloat *)popBuf());
}


//774
static void EXEC_glGetObjectParameterivARB(char *commandbuf)
{
	GLhandleARB *obj = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetObjectParameterivARB(*obj, *pname, (GLint *)popBuf());
}


//775
static void EXEC_glGetInfoLogARB(char *commandbuf)
{
	GLhandleARB *obj = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);
	GLsizei *maxLength = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *length = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glGetInfoLogARB(*obj, *maxLength, length, (GLcharARB *)popBuf());
}


//776
static void EXEC_glGetAttachedObjectsARB(char *commandbuf)
{
	GLhandleARB *containerObj = (GLhandleARB*)commandbuf;    commandbuf += sizeof(GLhandleARB);
	GLsizei *maxLength = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glGetAttachedObjectsARB(*containerObj, *maxLength, (GLsizei *)popBuf(), (GLhandleARB *)popBuf());
}


//777
static void EXEC_glGetUniformLocationARB(char *commandbuf)
{
	GLhandleARB *program = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);
	int num = glGetUniformLocationARB(*program, (const GLcharARB *)popBuf());
	pushRet(num);
}


//778
static void EXEC_glGetActiveUniformARB(char *commandbuf)
{
	GLhandleARB *program = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *bufSize = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);

	glGetActiveUniformARB(*program, *index, *bufSize, (GLsizei *)popBuf(), (GLint *)popBuf(), (GLenum *)popBuf(), (GLcharARB *)popBuf());
}


//779
static void EXEC_glGetUniformfvARB(char *commandbuf)
{
	GLhandleARB *program = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glGetUniformfvARB(*program, *location, (GLfloat *)popBuf());
}


//780
static void EXEC_glGetUniformivARB(char *commandbuf)
{
	GLhandleARB *program = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glGetUniformivARB(*program, *location, (GLint *)popBuf());
}


//781
static void EXEC_glGetShaderSourceARB(char *commandbuf)
{
	GLuint *shader = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLsizei *bufSize = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);
	GLint   *length  = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLchar  *source = (GLchar *)popBuf();
	if(*length == -1) {
		length = NULL;
	}

	glGetShaderSourceARB(*shader, *bufSize, length, source);
}


//782
static void EXEC_glBindAttribLocationARB(char *commandbuf)
{
	GLhandleARB *program = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glBindAttribLocationARB(*program, *index, (const GLcharARB *)popBuf());
}


//783
static void EXEC_glGetActiveAttribARB(char *commandbuf)
{
	GLhandleARB *program = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *bufSize = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);

	glGetActiveAttribARB(*program, *index, *bufSize, (GLsizei *)popBuf(), (GLint *)popBuf(), (GLenum *)popBuf(), (GLcharARB *)popBuf());
}


//784
static void EXEC_glGetAttribLocationARB(char *commandbuf)
{
	GLhandleARB *program = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);

	pushRet(glGetAttribLocationARB(*program, (const GLcharARB *)popBuf()));
}


//785
static void EXEC_glDrawBuffersARB(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glDrawBuffersARB(*n, (const GLenum *)popBuf());
}


//786
static void EXEC_glBlendColorEXT(char *commandbuf)
{
	GLclampf *red = (GLclampf*)commandbuf;   commandbuf += sizeof(GLclampf);
	GLclampf *green = (GLclampf*)commandbuf;     commandbuf += sizeof(GLclampf);
	GLclampf *blue = (GLclampf*)commandbuf;  commandbuf += sizeof(GLclampf);
	GLclampf *alpha = (GLclampf*)commandbuf;     commandbuf += sizeof(GLclampf);

	glBlendColorEXT(*red, *green, *blue, *alpha);
}


//787
static void EXEC_glPolygonOffsetEXT(char *commandbuf)
{
	GLfloat *factor = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *bias = (GLfloat*)commandbuf;    commandbuf += sizeof(GLfloat);

	glPolygonOffsetEXT(*factor, *bias);
}


//788
static void EXEC_glTexImage3DEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLsizei *depth = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLint *border = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glTexImage3DEXT(*target, *level, *internalformat, *width, *height, *depth, *border, *format, *type, (const GLvoid *)popBuf());
}


//789
static void EXEC_glTexSubImage3DEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *xoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *yoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *zoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLsizei *depth = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	//GLuint *UNUSED = (GLuint*)commandbuf;	 commandbuf += sizeof(GLuint);

	glTexSubImage3DEXT(*target, *level, *xoffset, *yoffset, *zoffset, *width, *height, *depth, *format, *type,  (const GLvoid *)popBuf());
}


//790
static void EXEC_glGetTexFilterFuncSGIS(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *filter = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glGetTexFilterFuncSGIS(*target, *filter, (GLfloat *)popBuf());
}


//791
static void EXEC_glTexFilterFuncSGIS(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *filter = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glTexFilterFuncSGIS(*target, *filter, *n, (const GLfloat *)popBuf());
}


//792
static void EXEC_glTexSubImage1DEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *xoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	//GLuint *UNUSED = (GLuint*)commandbuf;	 commandbuf += sizeof(GLuint);

	glTexSubImage1DEXT(*target, *level, *xoffset, *width, *format, *type,  (const GLvoid *)popBuf());
}


//793
static void EXEC_glTexSubImage2DEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *xoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *yoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	//GLuint *UNUSED = (GLuint*)commandbuf;	 commandbuf += sizeof(GLuint);

	glTexSubImage2DEXT(*target, *level, *xoffset, *yoffset, *width, *height, *format, *type,  (const GLvoid *)popBuf());
}


//794
static void EXEC_glCopyTexImage1DEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLint *border = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glCopyTexImage1DEXT(*target, *level, *internalformat, *x, *y, *width, *border);
}


//795
static void EXEC_glCopyTexImage2DEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLint *border = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glCopyTexImage2DEXT(*target, *level, *internalformat, *x, *y, *width, *height, *border);
}


//796
static void EXEC_glCopyTexSubImage1DEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *xoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glCopyTexSubImage1DEXT(*target, *level, *xoffset, *x, *y, *width);
}


//797
static void EXEC_glCopyTexSubImage2DEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *xoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *yoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glCopyTexSubImage2DEXT(*target, *level, *xoffset, *yoffset, *x, *y, *width, *height);
}


//798
static void EXEC_glCopyTexSubImage3DEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *xoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *yoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *zoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glCopyTexSubImage3DEXT(*target, *level, *xoffset, *yoffset, *zoffset, *x, *y, *width, *height);
}


//799
static void EXEC_glGetHistogramEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLboolean *reset = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glGetHistogramEXT(*target, *reset, *format, *type, (GLvoid *)popBuf());
}


//800
static void EXEC_glGetHistogramParameterfvEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetHistogramParameterfvEXT(*target, *pname, (GLfloat *)popBuf());
}


//801
static void EXEC_glGetHistogramParameterivEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetHistogramParameterivEXT(*target, *pname, (GLint *)popBuf());
}


//802
static void EXEC_glGetMinmaxEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLboolean *reset = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glGetMinmaxEXT(*target, *reset, *format, *type, (GLvoid *)popBuf());
}


//803
static void EXEC_glGetMinmaxParameterfvEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetMinmaxParameterfvEXT(*target, *pname, (GLfloat *)popBuf());
}


//804
static void EXEC_glGetMinmaxParameterivEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetMinmaxParameterivEXT(*target, *pname, (GLint *)popBuf());
}


//805
static void EXEC_glHistogramEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLboolean *sink = (GLboolean*)commandbuf;    commandbuf += sizeof(GLboolean);

	glHistogramEXT(*target, *width, *internalformat, *sink);
}


//806
static void EXEC_glMinmaxEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLboolean *sink = (GLboolean*)commandbuf;    commandbuf += sizeof(GLboolean);

	glMinmaxEXT(*target, *internalformat, *sink);
}


//807
static void EXEC_glResetHistogramEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glResetHistogramEXT(*target);
}


//808
static void EXEC_glResetMinmaxEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glResetMinmaxEXT(*target);
}


//809
static void EXEC_glConvolutionFilter1DEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glConvolutionFilter1DEXT(*target, *internalformat, *width, *format, *type, (const GLvoid *)popBuf());
}


//810
static void EXEC_glConvolutionFilter2DEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glConvolutionFilter2DEXT(*target, *internalformat, *width, *height, *format, *type, (const GLvoid *)popBuf());
}


//811
static void EXEC_glConvolutionParameterfEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *params = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	glConvolutionParameterfEXT(*target, *pname, *params);
}


//812
static void EXEC_glConvolutionParameterfvEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glConvolutionParameterfvEXT(*target, *pname, (const GLfloat *)popBuf());
}


//813
static void EXEC_glConvolutionParameteriEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *params = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glConvolutionParameteriEXT(*target, *pname, *params);
}


//814
static void EXEC_glConvolutionParameterivEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glConvolutionParameterivEXT(*target, *pname, (const GLint *)popBuf());
}


//815
static void EXEC_glCopyConvolutionFilter1DEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glCopyConvolutionFilter1DEXT(*target, *internalformat, *x, *y, *width);
}


//816
static void EXEC_glCopyConvolutionFilter2DEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glCopyConvolutionFilter2DEXT(*target, *internalformat, *x, *y, *width, *height);
}


//817
static void EXEC_glGetConvolutionFilterEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glGetConvolutionFilterEXT(*target, *format, *type, (GLvoid *)popBuf());
}


//818
static void EXEC_glGetConvolutionParameterfvEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetConvolutionParameterfvEXT(*target, *pname, (GLfloat *)popBuf());
}


//819
static void EXEC_glGetConvolutionParameterivEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetConvolutionParameterivEXT(*target, *pname, (GLint *)popBuf());
}


//820
static void EXEC_glGetSeparableFilterEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glGetSeparableFilterEXT(*target, *format, *type, (GLvoid *)popBuf(), (GLvoid *)popBuf(), (GLvoid *)popBuf());
}


//821
static void EXEC_glSeparableFilter2DEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glSeparableFilter2DEXT(*target, *internalformat, *width, *height, *format, *type, (const GLvoid *)popBuf(), (const GLvoid *)popBuf());
}


//822
static void EXEC_glColorTableSGI(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glColorTableSGI(*target, *internalformat, *width, *format, *type, (const GLvoid *)popBuf());
}


//823
static void EXEC_glColorTableParameterfvSGI(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glColorTableParameterfvSGI(*target, *pname, (const GLfloat *)popBuf());
}


//824
static void EXEC_glColorTableParameterivSGI(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glColorTableParameterivSGI(*target, *pname, (const GLint *)popBuf());
}


//825
static void EXEC_glCopyColorTableSGI(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glCopyColorTableSGI(*target, *internalformat, *x, *y, *width);
}


//826
static void EXEC_glGetColorTableSGI(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glGetColorTableSGI(*target, *format, *type, (GLvoid *)popBuf());
}


//827
static void EXEC_glGetColorTableParameterfvSGI(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetColorTableParameterfvSGI(*target, *pname, (GLfloat *)popBuf());
}


//828
static void EXEC_glGetColorTableParameterivSGI(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetColorTableParameterivSGI(*target, *pname, (GLint *)popBuf());
}


//829
static void EXEC_glPixelTexGenParameteriSGIS(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	//glPixelTexGenParameteriSGIS(*pname, *param);
}


//830
static void EXEC_glPixelTexGenParameterivSGIS(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	//glPixelTexGenParameterivSGIS(*pname, (const GLint *)popBuf());
}


//831
static void EXEC_glPixelTexGenParameterfSGIS(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	//glPixelTexGenParameterfSGIS(*pname, *param);
}


//832
static void EXEC_glPixelTexGenParameterfvSGIS(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	//glPixelTexGenParameterfvSGIS(*pname, (const GLfloat *)popBuf());
}


//833
static void EXEC_glGetPixelTexGenParameterivSGIS(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	//glGetPixelTexGenParameterivSGIS(*pname, (GLint *)popBuf());
}


//834
static void EXEC_glGetPixelTexGenParameterfvSGIS(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	//glGetPixelTexGenParameterfvSGIS(*pname, (GLfloat *)popBuf());
}


//835
static void EXEC_glTexImage4DSGIS(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLsizei *depth = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *size4d = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLint *border = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	//glTexImage4DSGIS(*target, *level, *internalformat, *width, *height, *depth, *size4d, *border, *format, *type, (const GLvoid *)popBuf());
}


//836
static void EXEC_glTexSubImage4DSGIS(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *xoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *yoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *zoffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *woffset = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLsizei *depth = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *size4d = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	//GLuint *UNUSED = (GLuint*)commandbuf;	 commandbuf += sizeof(GLuint);

	//glTexSubImage4DSGIS(*target, *level, *xoffset, *yoffset, *zoffset, *woffset, *width, *height, *depth, *size4d, *format, *type,  (const GLvoid *)popBuf());
}


//837
static void EXEC_glAreTexturesResidentEXT(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	pushRet(glAreTexturesResidentEXT(*n, (const GLuint *)popBuf(), (GLboolean *)popBuf()));
}


//838
static void EXEC_glBindTextureEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *texture = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	glBindTextureEXT(*target, *texture);
}


//839
static void EXEC_glDeleteTexturesEXT(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glDeleteTexturesEXT(*n, (const GLuint *)popBuf());
}


//840
static void EXEC_glGenTexturesEXT(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glGenTexturesEXT(*n, (GLuint *)popBuf());
}


//841
static void EXEC_glIsTextureEXT(char *commandbuf)
{
	GLuint *texture = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	pushRet(glIsTextureEXT(*texture));
}


//842
static void EXEC_glPrioritizeTexturesEXT(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glPrioritizeTexturesEXT(*n, (const GLuint *)popBuf(), (const GLclampf *)popBuf());
}


//843
static void EXEC_glDetailTexFuncSGIS(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glDetailTexFuncSGIS(*target, *n, (const GLfloat *)popBuf());
}


//844
static void EXEC_glGetDetailTexFuncSGIS(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glGetDetailTexFuncSGIS(*target, (GLfloat *)popBuf());
}


//845
static void EXEC_glSharpenTexFuncSGIS(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glSharpenTexFuncSGIS(*target, *n, (const GLfloat *)popBuf());
}


//846
static void EXEC_glGetSharpenTexFuncSGIS(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glGetSharpenTexFuncSGIS(*target, (GLfloat *)popBuf());
}


//847
static void EXEC_glSampleMaskSGIS(char *commandbuf)
{
	GLclampf *value = (GLclampf*)commandbuf;     commandbuf += sizeof(GLclampf);
	GLboolean *invert = (GLboolean*)commandbuf;  commandbuf += sizeof(GLboolean);

	glSampleMaskSGIS(*value, *invert);
}


//848
static void EXEC_glSamplePatternSGIS(char *commandbuf)
{
	GLenum *pattern = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);

	glSamplePatternSGIS(*pattern);
}


//849
static void EXEC_glArrayElementEXT(char *commandbuf)
{
	GLint *i = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glArrayElementEXT(*i);
}


//850
static void EXEC_glColorPointerEXT(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glColorPointerEXT(*size, *type, *stride, *count, (const GLvoid *)popBuf());
}


//851
static void EXEC_glDrawArraysEXT(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLint *first = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glDrawArraysEXT(*mode, *first, *count);
}


//852
static void EXEC_glEdgeFlagPointerEXT(char *commandbuf)
{
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glEdgeFlagPointerEXT(*stride, *count, (const GLboolean *)popBuf());
}



//853
static void EXEC_glGetPointervEXT(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	LOG("Warning: Called glGetPointervEXT, using glGetPointerv instead\n");

	glGetPointerv(*pname, (GLvoid **)popBuf());
}




//854
static void EXEC_glIndexPointerEXT(char *commandbuf)
{
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glIndexPointerEXT(*type, *stride, *count, (const GLvoid *)popBuf());
}


//855
static void EXEC_glNormalPointerEXT(char *commandbuf)
{
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glNormalPointerEXT(*type, *stride, *count, (const GLvoid *)popBuf());
}


//856
static void EXEC_glTexCoordPointerEXT(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glTexCoordPointerEXT(*size, *type, *stride, *count, (const GLvoid *)popBuf());
}


//857
static void EXEC_glVertexPointerEXT(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glVertexPointerEXT(*size, *type, *stride, *count, (const GLvoid *)popBuf());
}


//858
static void EXEC_glBlendEquationEXT(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glBlendEquationEXT(*mode);
}


//859
static void EXEC_glSpriteParameterfSGIX(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glSpriteParameterfSGIX(*pname, *param);
}


//860
static void EXEC_glSpriteParameterfvSGIX(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glSpriteParameterfvSGIX(*pname, (GLfloat *)popBuf());
}


//861
static void EXEC_glSpriteParameteriSGIX(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glSpriteParameteriSGIX(*pname, *param);
}


//862
static void EXEC_glSpriteParameterivSGIX(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glSpriteParameterivSGIX(*pname, (GLint *)popBuf());
}


//863
static void EXEC_glPointParameterfEXT(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glPointParameterfEXT(*pname, *param);
}


//864
static void EXEC_glPointParameterfvEXT(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glPointParameterfvEXT(*pname, (GLfloat *)popBuf());
}


//865
static void EXEC_glGetInstrumentsSGIX(char *commandbuf)
{

	//pushRet(glGetInstrumentsSGIX());
}


//866
static void EXEC_glInstrumentsBufferSGIX(char *commandbuf)
{
	GLsizei *size = (GLsizei*)commandbuf;    commandbuf += sizeof(GLsizei);

	//glInstrumentsBufferSGIX(*size, (GLint *)popBuf());
}


//867
static void EXEC_glPollInstrumentsSGIX(char *commandbuf)
{

	//pushRet(glPollInstrumentsSGIX((GLint *)popBuf()));
}


//868
static void EXEC_glReadInstrumentsSGIX(char *commandbuf)
{
	GLint *marker = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	//glReadInstrumentsSGIX(*marker);
}


//869
static void EXEC_glStartInstrumentsSGIX(char *commandbuf)
{

	//glStartInstrumentsSGIX();
}


//870
static void EXEC_glStopInstrumentsSGIX(char *commandbuf)
{
	GLint *marker = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	//glStopInstrumentsSGIX(*marker);
}


//871
static void EXEC_glFrameZoomSGIX(char *commandbuf)
{
	GLint *factor = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	//glFrameZoomSGIX(*factor);
}


//872
static void EXEC_glTagSampleBufferSGIX(char *commandbuf)
{

	//glTagSampleBufferSGIX();
}


//873
static void EXEC_glReferencePlaneSGIX(char *commandbuf)
{

	//glReferencePlaneSGIX((const GLdouble *)popBuf());
}


//874
static void EXEC_glFlushRasterSGIX(char *commandbuf)
{

	//glFlushRasterSGIX();
}


//875
static void EXEC_glFogFuncSGIS(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glFogFuncSGIS(*n, (const GLfloat *)popBuf());
}


//876
static void EXEC_glGetFogFuncSGIS(char *commandbuf)
{

	glGetFogFuncSGIS((GLfloat *)popBuf());
}


//877
static void EXEC_glImageTransformParameteriHP(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glImageTransformParameteriHP(*target, *pname, *param);
}


//878
static void EXEC_glImageTransformParameterfHP(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glImageTransformParameterfHP(*target, *pname, *param);
}


//879
static void EXEC_glImageTransformParameterivHP(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glImageTransformParameterivHP(*target, *pname, (const GLint *)popBuf());
}


//880
static void EXEC_glImageTransformParameterfvHP(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glImageTransformParameterfvHP(*target, *pname, (const GLfloat *)popBuf());
}


//881
static void EXEC_glGetImageTransformParameterivHP(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetImageTransformParameterivHP(*target, *pname, (GLint *)popBuf());
}


//882
static void EXEC_glGetImageTransformParameterfvHP(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetImageTransformParameterfvHP(*target, *pname, (GLfloat *)popBuf());
}


//883
static void EXEC_glColorSubTableEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *start = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glColorSubTableEXT(*target, *start, *count, *format, *type, (const GLvoid *)popBuf());
}


//884
static void EXEC_glCopyColorSubTableEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *start = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glCopyColorSubTableEXT(*target, *start, *x, *y, *width);
}


//885
static void EXEC_glHintPGI(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *mode = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	//glHintPGI(*target, *mode);
}


//886
static void EXEC_glColorTableEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glColorTableEXT(*target, *internalformat, *width, *format, *type, (const GLvoid *)popBuf());
}


//887
static void EXEC_glGetColorTableEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glGetColorTableEXT(*target, *format, *type, (GLvoid *)popBuf());
}


//888
static void EXEC_glGetColorTableParameterivEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetColorTableParameterivEXT(*target, *pname, (GLint *)popBuf());
}


//889
static void EXEC_glGetColorTableParameterfvEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetColorTableParameterfvEXT(*target, *pname, (GLfloat *)popBuf());
}


//890
static void EXEC_glGetListParameterfvSGIX(char *commandbuf)
{
	GLuint *list = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	//glGetListParameterfvSGIX(*list, *pname, (GLfloat *)popBuf());
}


//891
static void EXEC_glGetListParameterivSGIX(char *commandbuf)
{
	GLuint *list = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	//glGetListParameterivSGIX(*list, *pname, (GLint *)popBuf());
}


//892
static void EXEC_glListParameterfSGIX(char *commandbuf)
{
	GLuint *list = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	//glListParameterfSGIX(*list, *pname, *param);
}


//893
static void EXEC_glListParameterfvSGIX(char *commandbuf)
{
	GLuint *list = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	//glListParameterfvSGIX(*list, *pname, (const GLfloat *)popBuf());
}


//894
static void EXEC_glListParameteriSGIX(char *commandbuf)
{
	GLuint *list = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	//glListParameteriSGIX(*list, *pname, *param);
}


//895
static void EXEC_glListParameterivSGIX(char *commandbuf)
{
	GLuint *list = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	//glListParameterivSGIX(*list, *pname, (const GLint *)popBuf());
}


//896
static void EXEC_glIndexMaterialEXT(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glIndexMaterialEXT(*face, *mode);
}


//897
static void EXEC_glIndexFuncEXT(char *commandbuf)
{
	GLenum *func = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLclampf *ref = (GLclampf*)commandbuf;   commandbuf += sizeof(GLclampf);

	glIndexFuncEXT(*func, *ref);
}


//898
static void EXEC_glLockArraysEXT(char *commandbuf)
{
	GLint *first = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glLockArraysEXT(*first, *count);
}


//899
static void EXEC_glUnlockArraysEXT(char *commandbuf)
{

	glUnlockArraysEXT();
}


//900
static void EXEC_glCullParameterdvEXT(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glCullParameterdvEXT(*pname, (GLdouble *)popBuf());
}


//901
static void EXEC_glCullParameterfvEXT(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glCullParameterfvEXT(*pname, (GLfloat *)popBuf());
}


//902
static void EXEC_glFragmentColorMaterialSGIX(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glFragmentColorMaterialSGIX(*face, *mode);
}


//903
static void EXEC_glFragmentLightfSGIX(char *commandbuf)
{
	GLenum *light = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glFragmentLightfSGIX(*light, *pname, *param);
}


//904
static void EXEC_glFragmentLightfvSGIX(char *commandbuf)
{
	GLenum *light = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glFragmentLightfvSGIX(*light, *pname, (GLfloat *)popBuf());
}


//905
static void EXEC_glFragmentLightiSGIX(char *commandbuf)
{
	GLenum *light = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glFragmentLightiSGIX(*light, *pname, *param);
}


//906
static void EXEC_glFragmentLightivSGIX(char *commandbuf)
{
	GLenum *light = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glFragmentLightivSGIX(*light, *pname, (GLint *)popBuf());
}


//907
static void EXEC_glFragmentLightModelfSGIX(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glFragmentLightModelfSGIX(*pname, *param);
}


//908
static void EXEC_glFragmentLightModelfvSGIX(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glFragmentLightModelfvSGIX(*pname, (GLfloat *)popBuf());
}


//909
static void EXEC_glFragmentLightModeliSGIX(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glFragmentLightModeliSGIX(*pname, *param);
}


//910
static void EXEC_glFragmentLightModelivSGIX(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glFragmentLightModelivSGIX(*pname, (GLint *)popBuf());
}


//911
static void EXEC_glFragmentMaterialfSGIX(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glFragmentMaterialfSGIX(*face, *pname, *param);
}


//912
static void EXEC_glFragmentMaterialfvSGIX(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glFragmentMaterialfvSGIX(*face, *pname, (const GLfloat *)popBuf());
}


//913
static void EXEC_glFragmentMaterialiSGIX(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glFragmentMaterialiSGIX(*face, *pname, *param);
}


//914
static void EXEC_glFragmentMaterialivSGIX(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glFragmentMaterialivSGIX(*face, *pname, (const GLint *)popBuf());
}


//915
static void EXEC_glGetFragmentLightfvSGIX(char *commandbuf)
{
	GLenum *light = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetFragmentLightfvSGIX(*light, *pname, (GLfloat *)popBuf());
}


//916
static void EXEC_glGetFragmentLightivSGIX(char *commandbuf)
{
	GLenum *light = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetFragmentLightivSGIX(*light, *pname, (GLint *)popBuf());
}


//917
static void EXEC_glGetFragmentMaterialfvSGIX(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetFragmentMaterialfvSGIX(*face, *pname, (GLfloat *)popBuf());
}


//918
static void EXEC_glGetFragmentMaterialivSGIX(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetFragmentMaterialivSGIX(*face, *pname, (GLint *)popBuf());
}


//919
static void EXEC_glLightEnviSGIX(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	//glLightEnviSGIX(*pname, *param);
}


//920
static void EXEC_glDrawRangeElementsEXT(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLuint *start = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLuint *end = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glDrawRangeElementsEXT(*mode, *start, *end, *count, *type, (const GLvoid *)popBuf());
}


//921
static void EXEC_glApplyTextureEXT(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glApplyTextureEXT(*mode);
}


//922
static void EXEC_glTextureLightEXT(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glTextureLightEXT(*pname);
}


//923
static void EXEC_glTextureMaterialEXT(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glTextureMaterialEXT(*face, *mode);
}


//924
static void EXEC_glAsyncMarkerSGIX(char *commandbuf)
{
	GLuint *marker = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	glAsyncMarkerSGIX(*marker);
}


//925
static void EXEC_glFinishAsyncSGIX(char *commandbuf)
{

	pushRet(glFinishAsyncSGIX((GLuint *)popBuf()));
}


//926
static void EXEC_glPollAsyncSGIX(char *commandbuf)
{

	pushRet(glPollAsyncSGIX((GLuint *)popBuf()));
}


//927
static void EXEC_glGenAsyncMarkersSGIX(char *commandbuf)
{
	GLsizei *range = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	pushRet(glGenAsyncMarkersSGIX(*range));
}


//928
static void EXEC_glDeleteAsyncMarkersSGIX(char *commandbuf)
{
	GLuint *marker = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLsizei *range = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glDeleteAsyncMarkersSGIX(*marker, *range);
}


//929
static void EXEC_glIsAsyncMarkerSGIX(char *commandbuf)
{
	GLuint *marker = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	pushRet(glIsAsyncMarkerSGIX(*marker));
}


//930
static void EXEC_glVertexPointervINTEL(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glVertexPointervINTEL(*size, *type, (const GLvoid **)popBuf());
}


//931
static void EXEC_glNormalPointervINTEL(char *commandbuf)
{
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glNormalPointervINTEL(*type, (const GLvoid **)popBuf());
}


//932
static void EXEC_glColorPointervINTEL(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glColorPointervINTEL(*size, *type, (const GLvoid **)popBuf());
}


//933
static void EXEC_glTexCoordPointervINTEL(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glTexCoordPointervINTEL(*size, *type, (const GLvoid **)popBuf());
}


//934
static void EXEC_glPixelTransformParameteriEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glPixelTransformParameteriEXT(*target, *pname, *param);
}


//935
static void EXEC_glPixelTransformParameterfEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glPixelTransformParameterfEXT(*target, *pname, *param);
}


//936
static void EXEC_glPixelTransformParameterivEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glPixelTransformParameterivEXT(*target, *pname, (const GLint *)popBuf());
}


//937
static void EXEC_glPixelTransformParameterfvEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glPixelTransformParameterfvEXT(*target, *pname, (const GLfloat *)popBuf());
}


//938
static void EXEC_glSecondaryColor3bEXT(char *commandbuf)
{
	GLbyte *red = (GLbyte*)commandbuf;   commandbuf += sizeof(GLbyte);
	GLbyte *green = (GLbyte*)commandbuf;     commandbuf += sizeof(GLbyte);
	GLbyte *blue = (GLbyte*)commandbuf;  commandbuf += sizeof(GLbyte);

	glSecondaryColor3bEXT(*red, *green, *blue);
}


//939
static void EXEC_glSecondaryColor3bvEXT(char *commandbuf)
{

	glSecondaryColor3bvEXT((const GLbyte *)popBuf());
}


//940
static void EXEC_glSecondaryColor3dEXT(char *commandbuf)
{
	GLdouble *red = (GLdouble*)commandbuf;   commandbuf += sizeof(GLdouble);
	GLdouble *green = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *blue = (GLdouble*)commandbuf;  commandbuf += sizeof(GLdouble);

	glSecondaryColor3dEXT(*red, *green, *blue);
}


//941
static void EXEC_glSecondaryColor3dvEXT(char *commandbuf)
{

	glSecondaryColor3dvEXT((const GLdouble *)popBuf());
}


//942
static void EXEC_glSecondaryColor3fEXT(char *commandbuf)
{
	GLfloat *red = (GLfloat*)commandbuf;     commandbuf += sizeof(GLfloat);
	GLfloat *green = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *blue = (GLfloat*)commandbuf;    commandbuf += sizeof(GLfloat);

	glSecondaryColor3fEXT(*red, *green, *blue);
}


//943
static void EXEC_glSecondaryColor3fvEXT(char *commandbuf)
{

	glSecondaryColor3fvEXT((const GLfloat *)popBuf());
}


//944
static void EXEC_glSecondaryColor3iEXT(char *commandbuf)
{
	GLint *red = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *green = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *blue = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glSecondaryColor3iEXT(*red, *green, *blue);
}


//945
static void EXEC_glSecondaryColor3ivEXT(char *commandbuf)
{

	glSecondaryColor3ivEXT((const GLint *)popBuf());
}


//946
static void EXEC_glSecondaryColor3sEXT(char *commandbuf)
{
	GLshort *red = (GLshort*)commandbuf;     commandbuf += sizeof(GLshort);
	GLshort *green = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *blue = (GLshort*)commandbuf;    commandbuf += sizeof(GLshort);

	glSecondaryColor3sEXT(*red, *green, *blue);
}


//947
static void EXEC_glSecondaryColor3svEXT(char *commandbuf)
{

	glSecondaryColor3svEXT((const GLshort *)popBuf());
}


//948
static void EXEC_glSecondaryColor3ubEXT(char *commandbuf)
{
	GLubyte *red = (GLubyte*)commandbuf;     commandbuf += sizeof(GLubyte);
	GLubyte *green = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *blue = (GLubyte*)commandbuf;    commandbuf += sizeof(GLubyte);

	glSecondaryColor3ubEXT(*red, *green, *blue);
}


//949
static void EXEC_glSecondaryColor3ubvEXT(char *commandbuf)
{

	glSecondaryColor3ubvEXT((const GLubyte *)popBuf());
}


//950
static void EXEC_glSecondaryColor3uiEXT(char *commandbuf)
{
	GLuint *red = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *green = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLuint *blue = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

	glSecondaryColor3uiEXT(*red, *green, *blue);
}


//951
static void EXEC_glSecondaryColor3uivEXT(char *commandbuf)
{

	glSecondaryColor3uivEXT((const GLuint *)popBuf());
}


//952
static void EXEC_glSecondaryColor3usEXT(char *commandbuf)
{
	GLushort *red = (GLushort*)commandbuf;   commandbuf += sizeof(GLushort);
	GLushort *green = (GLushort*)commandbuf;     commandbuf += sizeof(GLushort);
	GLushort *blue = (GLushort*)commandbuf;  commandbuf += sizeof(GLushort);

	glSecondaryColor3usEXT(*red, *green, *blue);
}


//953
static void EXEC_glSecondaryColor3usvEXT(char *commandbuf)
{

	glSecondaryColor3usvEXT((const GLushort *)popBuf());
}


//954
static void EXEC_glSecondaryColorPointerEXT(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glSecondaryColorPointerEXT(*size, *type, *stride, (GLvoid *)popBuf());
}


//955
static void EXEC_glTextureNormalEXT(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glTextureNormalEXT(*mode);
}


//956
static void EXEC_glMultiDrawArraysEXT(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *primcount = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glMultiDrawArraysEXT(*mode, (GLint *)popBuf(), (GLsizei *)popBuf(), *primcount);
}


//957
static void EXEC_glMultiDrawElementsEXT(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *primcount = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glMultiDrawElementsEXT(*mode, (GLsizei *)popBuf(), *type, (const GLvoid **)popBuf(), *primcount);
}


//958
static void EXEC_glFogCoordfEXT(char *commandbuf)
{
	GLfloat *coord = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glFogCoordfEXT(*coord);
}


//959
static void EXEC_glFogCoordfvEXT(char *commandbuf)
{

	glFogCoordfvEXT((const GLfloat *)popBuf());
}


//960
static void EXEC_glFogCoorddEXT(char *commandbuf)
{
	GLdouble *coord = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glFogCoorddEXT(*coord);
}


//961
static void EXEC_glFogCoorddvEXT(char *commandbuf)
{

	glFogCoorddvEXT((const GLdouble *)popBuf());
}


//962
static void EXEC_glFogCoordPointerEXT(char *commandbuf)
{
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glFogCoordPointerEXT(*type, *stride, (const GLvoid *)popBuf());
}


//963
static void EXEC_glTangent3bEXT(char *commandbuf)
{
	GLbyte *tx = (GLbyte*)commandbuf;    commandbuf += sizeof(GLbyte);
	GLbyte *ty = (GLbyte*)commandbuf;    commandbuf += sizeof(GLbyte);
	GLbyte *tz = (GLbyte*)commandbuf;    commandbuf += sizeof(GLbyte);

	//glTangent3bEXT(*tx, *ty, *tz);
}


//964
static void EXEC_glTangent3bvEXT(char *commandbuf)
{

	//glTangent3bvEXT((const GLbyte *)popBuf());
}


//965
static void EXEC_glTangent3dEXT(char *commandbuf)
{
	GLdouble *tx = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *ty = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *tz = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);

	//glTangent3dEXT(*tx, *ty, *tz);
}


//966
static void EXEC_glTangent3dvEXT(char *commandbuf)
{

	//glTangent3dvEXT((const GLdouble *)popBuf());
}


//967
static void EXEC_glTangent3fEXT(char *commandbuf)
{
	GLfloat *tx = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *ty = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *tz = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	//glTangent3fEXT(*tx, *ty, *tz);
}


//968
static void EXEC_glTangent3fvEXT(char *commandbuf)
{

	//glTangent3fvEXT((const GLfloat *)popBuf());
}


//969
static void EXEC_glTangent3iEXT(char *commandbuf)
{
	GLint *tx = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *ty = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *tz = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	//glTangent3iEXT(*tx, *ty, *tz);
}


//970
static void EXEC_glTangent3ivEXT(char *commandbuf)
{

	//glTangent3ivEXT((const GLint *)popBuf());
}


//971
static void EXEC_glTangent3sEXT(char *commandbuf)
{
	GLshort *tx = (GLshort*)commandbuf;  commandbuf += sizeof(GLshort);
	GLshort *ty = (GLshort*)commandbuf;  commandbuf += sizeof(GLshort);
	GLshort *tz = (GLshort*)commandbuf;  commandbuf += sizeof(GLshort);

	//glTangent3sEXT(*tx, *ty, *tz);
}


//972
static void EXEC_glTangent3svEXT(char *commandbuf)
{

	//glTangent3svEXT((const GLshort *)popBuf());
}


//973
static void EXEC_glBinormal3bEXT(char *commandbuf)
{
	GLbyte *bx = (GLbyte*)commandbuf;    commandbuf += sizeof(GLbyte);
	GLbyte *by = (GLbyte*)commandbuf;    commandbuf += sizeof(GLbyte);
	GLbyte *bz = (GLbyte*)commandbuf;    commandbuf += sizeof(GLbyte);

	//glBinormal3bEXT(*bx, *by, *bz);
}


//974
static void EXEC_glBinormal3bvEXT(char *commandbuf)
{

	//glBinormal3bvEXT((const GLbyte *)popBuf());
}


//975
static void EXEC_glBinormal3dEXT(char *commandbuf)
{
	GLdouble *bx = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *by = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *bz = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);

	//glBinormal3dEXT(*bx, *by, *bz);
}


//976
static void EXEC_glBinormal3dvEXT(char *commandbuf)
{

	//glBinormal3dvEXT((const GLdouble *)popBuf());
}


//977
static void EXEC_glBinormal3fEXT(char *commandbuf)
{
	GLfloat *bx = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *by = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *bz = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	//glBinormal3fEXT(*bx, *by, *bz);
}


//978
static void EXEC_glBinormal3fvEXT(char *commandbuf)
{

	//glBinormal3fvEXT((const GLfloat *)popBuf());
}


//979
static void EXEC_glBinormal3iEXT(char *commandbuf)
{
	GLint *bx = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *by = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *bz = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	//glBinormal3iEXT(*bx, *by, *bz);
}


//980
static void EXEC_glBinormal3ivEXT(char *commandbuf)
{

	//glBinormal3ivEXT((const GLint *)popBuf());
}


//981
static void EXEC_glBinormal3sEXT(char *commandbuf)
{
	GLshort *bx = (GLshort*)commandbuf;  commandbuf += sizeof(GLshort);
	GLshort *by = (GLshort*)commandbuf;  commandbuf += sizeof(GLshort);
	GLshort *bz = (GLshort*)commandbuf;  commandbuf += sizeof(GLshort);

	//glBinormal3sEXT(*bx, *by, *bz);
}


//982
static void EXEC_glBinormal3svEXT(char *commandbuf)
{

	//glBinormal3svEXT((const GLshort *)popBuf());
}


//983
static void EXEC_glTangentPointerEXT(char *commandbuf)
{
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	//glTangentPointerEXT(*type, *stride, (const GLvoid *)popBuf());
}


//984
static void EXEC_glBinormalPointerEXT(char *commandbuf)
{
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	//glBinormalPointerEXT(*type, *stride, (const GLvoid *)popBuf());
}


//985
static void EXEC_glPixelTexGenSGIX(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glPixelTexGenSGIX(*mode);
}


//986
static void EXEC_glFinishTextureSUNX(char *commandbuf)
{

	glFinishTextureSUNX();
}


//987
static void EXEC_glGlobalAlphaFactorbSUN(char *commandbuf)
{
	GLbyte *factor = (GLbyte*)commandbuf;    commandbuf += sizeof(GLbyte);

	glGlobalAlphaFactorbSUN(*factor);
}


//988
static void EXEC_glGlobalAlphaFactorsSUN(char *commandbuf)
{
	GLshort *factor = (GLshort*)commandbuf;  commandbuf += sizeof(GLshort);

	glGlobalAlphaFactorsSUN(*factor);
}


//989
static void EXEC_glGlobalAlphaFactoriSUN(char *commandbuf)
{
	GLint *factor = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glGlobalAlphaFactoriSUN(*factor);
}


//990
static void EXEC_glGlobalAlphaFactorfSUN(char *commandbuf)
{
	GLfloat *factor = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	glGlobalAlphaFactorfSUN(*factor);
}


//991
static void EXEC_glGlobalAlphaFactordSUN(char *commandbuf)
{
	GLdouble *factor = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);

	glGlobalAlphaFactordSUN(*factor);
}


//992
static void EXEC_glGlobalAlphaFactorubSUN(char *commandbuf)
{
	GLubyte *factor = (GLubyte*)commandbuf;  commandbuf += sizeof(GLubyte);

	glGlobalAlphaFactorubSUN(*factor);
}


//993
static void EXEC_glGlobalAlphaFactorusSUN(char *commandbuf)
{
	GLushort *factor = (GLushort*)commandbuf;    commandbuf += sizeof(GLushort);

	glGlobalAlphaFactorusSUN(*factor);
}


//994
static void EXEC_glGlobalAlphaFactoruiSUN(char *commandbuf)
{
	GLuint *factor = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	glGlobalAlphaFactoruiSUN(*factor);
}


//995
static void EXEC_glReplacementCodeuiSUN(char *commandbuf)
{
	GLuint *code = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

	glReplacementCodeuiSUN(*code);
}


//996
static void EXEC_glReplacementCodeusSUN(char *commandbuf)
{
	GLushort *code = (GLushort*)commandbuf;  commandbuf += sizeof(GLushort);

	glReplacementCodeusSUN(*code);
}


//997
static void EXEC_glReplacementCodeubSUN(char *commandbuf)
{
	GLubyte *code = (GLubyte*)commandbuf;    commandbuf += sizeof(GLubyte);

	glReplacementCodeubSUN(*code);
}


//998
static void EXEC_glReplacementCodeuivSUN(char *commandbuf)
{

	glReplacementCodeuivSUN((const GLuint *)popBuf());
}


//999
static void EXEC_glReplacementCodeusvSUN(char *commandbuf)
{

	glReplacementCodeusvSUN((const GLushort *)popBuf());
}


//1000
static void EXEC_glReplacementCodeubvSUN(char *commandbuf)
{

	glReplacementCodeubvSUN((const GLubyte *)popBuf());
}


//1001
static void EXEC_glReplacementCodePointerSUN(char *commandbuf)
{
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glReplacementCodePointerSUN(*type, *stride, (const GLvoid *)popBuf());
}


//1002
static void EXEC_glColor4ubVertex2fSUN(char *commandbuf)
{
	GLubyte *r = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *g = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *b = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *a = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glColor4ubVertex2fSUN(*r, *g, *b, *a, *x, *y);
}


//1003
static void EXEC_glColor4ubVertex2fvSUN(char *commandbuf)
{

	glColor4ubVertex2fvSUN((const GLubyte *)popBuf(), (const GLfloat *)popBuf());
}


//1004
static void EXEC_glColor4ubVertex3fSUN(char *commandbuf)
{
	GLubyte *r = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *g = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *b = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *a = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glColor4ubVertex3fSUN(*r, *g, *b, *a, *x, *y, *z);
}


//1005
static void EXEC_glColor4ubVertex3fvSUN(char *commandbuf)
{

	glColor4ubVertex3fvSUN((const GLubyte *)popBuf(), (const GLfloat *)popBuf());
}


//1006
static void EXEC_glColor3fVertex3fSUN(char *commandbuf)
{
	GLfloat *r = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *g = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *b = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glColor3fVertex3fSUN(*r, *g, *b, *x, *y, *z);
}


//1007
static void EXEC_glColor3fVertex3fvSUN(char *commandbuf)
{

	glColor3fVertex3fvSUN((const GLfloat *)popBuf(), (const GLfloat *)popBuf());
}


//1008
static void EXEC_glNormal3fVertex3fSUN(char *commandbuf)
{
	GLfloat *nx = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *ny = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *nz = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glNormal3fVertex3fSUN(*nx, *ny, *nz, *x, *y, *z);
}


//1009
static void EXEC_glNormal3fVertex3fvSUN(char *commandbuf)
{

	glNormal3fVertex3fvSUN((const GLfloat *)popBuf(), (const GLfloat *)popBuf());
}


//1010
static void EXEC_glColor4fNormal3fVertex3fSUN(char *commandbuf)
{
	GLfloat *r = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *g = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *b = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *a = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *nx = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *ny = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *nz = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glColor4fNormal3fVertex3fSUN(*r, *g, *b, *a, *nx, *ny, *nz, *x, *y, *z);
}


//1011
static void EXEC_glColor4fNormal3fVertex3fvSUN(char *commandbuf)
{

	glColor4fNormal3fVertex3fvSUN((const GLfloat *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf());
}


//1012
static void EXEC_glTexCoord2fVertex3fSUN(char *commandbuf)
{
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *t = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glTexCoord2fVertex3fSUN(*s, *t, *x, *y, *z);
}


//1013
static void EXEC_glTexCoord2fVertex3fvSUN(char *commandbuf)
{

	glTexCoord2fVertex3fvSUN((const GLfloat *)popBuf(), (const GLfloat *)popBuf());
}


//1014
static void EXEC_glTexCoord4fVertex4fSUN(char *commandbuf)
{
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *t = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *p = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *q = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *w = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glTexCoord4fVertex4fSUN(*s, *t, *p, *q, *x, *y, *z, *w);
}


//1015
static void EXEC_glTexCoord4fVertex4fvSUN(char *commandbuf)
{

	glTexCoord4fVertex4fvSUN((const GLfloat *)popBuf(), (const GLfloat *)popBuf());
}


//1016
static void EXEC_glTexCoord2fColor4ubVertex3fSUN(char *commandbuf)
{
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *t = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLubyte *r = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *g = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *b = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *a = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glTexCoord2fColor4ubVertex3fSUN(*s, *t, *r, *g, *b, *a, *x, *y, *z);
}


//1017
static void EXEC_glTexCoord2fColor4ubVertex3fvSUN(char *commandbuf)
{

	glTexCoord2fColor4ubVertex3fvSUN((const GLfloat *)popBuf(), (const GLubyte *)popBuf(), (const GLfloat *)popBuf());
}


//1018
static void EXEC_glTexCoord2fColor3fVertex3fSUN(char *commandbuf)
{
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *t = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *r = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *g = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *b = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glTexCoord2fColor3fVertex3fSUN(*s, *t, *r, *g, *b, *x, *y, *z);
}


//1019
static void EXEC_glTexCoord2fColor3fVertex3fvSUN(char *commandbuf)
{

	glTexCoord2fColor3fVertex3fvSUN((const GLfloat *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf());
}


//1020
static void EXEC_glTexCoord2fNormal3fVertex3fSUN(char *commandbuf)
{
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *t = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *nx = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *ny = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *nz = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glTexCoord2fNormal3fVertex3fSUN(*s, *t, *nx, *ny, *nz, *x, *y, *z);
}


//1021
static void EXEC_glTexCoord2fNormal3fVertex3fvSUN(char *commandbuf)
{

	glTexCoord2fNormal3fVertex3fvSUN((const GLfloat *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf());
}


//1022
static void EXEC_glTexCoord2fColor4fNormal3fVertex3fSUN(char *commandbuf)
{
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *t = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *r = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *g = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *b = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *a = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *nx = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *ny = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *nz = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glTexCoord2fColor4fNormal3fVertex3fSUN(*s, *t, *r, *g, *b, *a, *nx, *ny, *nz, *x, *y, *z);
}


//1023
static void EXEC_glTexCoord2fColor4fNormal3fVertex3fvSUN(char *commandbuf)
{

	glTexCoord2fColor4fNormal3fVertex3fvSUN((const GLfloat *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf());
}


//1024
static void EXEC_glTexCoord4fColor4fNormal3fVertex4fSUN(char *commandbuf)
{
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *t = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *p = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *q = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *r = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *g = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *b = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *a = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *nx = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *ny = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *nz = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *w = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glTexCoord4fColor4fNormal3fVertex4fSUN(*s, *t, *p, *q, *r, *g, *b, *a, *nx, *ny, *nz, *x, *y, *z, *w);
}


//1025
static void EXEC_glTexCoord4fColor4fNormal3fVertex4fvSUN(char *commandbuf)
{

	glTexCoord4fColor4fNormal3fVertex4fvSUN((const GLfloat *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf());
}


//1026
static void EXEC_glReplacementCodeuiVertex3fSUN(char *commandbuf)
{
	GLuint *rc = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glReplacementCodeuiVertex3fSUN(*rc, *x, *y, *z);
}


//1027
static void EXEC_glReplacementCodeuiVertex3fvSUN(char *commandbuf)
{

	glReplacementCodeuiVertex3fvSUN((const GLuint *)popBuf(), (const GLfloat *)popBuf());
}


//1028
static void EXEC_glReplacementCodeuiColor4ubVertex3fSUN(char *commandbuf)
{
	GLuint *rc = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLubyte *r = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *g = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *b = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *a = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glReplacementCodeuiColor4ubVertex3fSUN(*rc, *r, *g, *b, *a, *x, *y, *z);
}


//1029
static void EXEC_glReplacementCodeuiColor4ubVertex3fvSUN(char *commandbuf)
{

	glReplacementCodeuiColor4ubVertex3fvSUN((const GLuint *)popBuf(), (const GLubyte *)popBuf(), (const GLfloat *)popBuf());
}


//1030
static void EXEC_glReplacementCodeuiColor3fVertex3fSUN(char *commandbuf)
{
	GLuint *rc = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLfloat *r = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *g = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *b = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glReplacementCodeuiColor3fVertex3fSUN(*rc, *r, *g, *b, *x, *y, *z);
}


//1031
static void EXEC_glReplacementCodeuiColor3fVertex3fvSUN(char *commandbuf)
{

	glReplacementCodeuiColor3fVertex3fvSUN((const GLuint *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf());
}


//1032
static void EXEC_glReplacementCodeuiNormal3fVertex3fSUN(char *commandbuf)
{
	GLuint *rc = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLfloat *nx = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *ny = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *nz = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glReplacementCodeuiNormal3fVertex3fSUN(*rc, *nx, *ny, *nz, *x, *y, *z);
}


//1033
static void EXEC_glReplacementCodeuiNormal3fVertex3fvSUN(char *commandbuf)
{

	glReplacementCodeuiNormal3fVertex3fvSUN((const GLuint *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf());
}


//1034
static void EXEC_glReplacementCodeuiColor4fNormal3fVertex3fSUN(char *commandbuf)
{
	GLuint *rc = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLfloat *r = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *g = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *b = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *a = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *nx = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *ny = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *nz = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glReplacementCodeuiColor4fNormal3fVertex3fSUN(*rc, *r, *g, *b, *a, *nx, *ny, *nz, *x, *y, *z);
}


//1035
static void EXEC_glReplacementCodeuiColor4fNormal3fVertex3fvSUN(char *commandbuf)
{

	glReplacementCodeuiColor4fNormal3fVertex3fvSUN((const GLuint *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf());
}


//1036
static void EXEC_glReplacementCodeuiTexCoord2fVertex3fSUN(char *commandbuf)
{
	GLuint *rc = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *t = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glReplacementCodeuiTexCoord2fVertex3fSUN(*rc, *s, *t, *x, *y, *z);
}


//1037
static void EXEC_glReplacementCodeuiTexCoord2fVertex3fvSUN(char *commandbuf)
{

	glReplacementCodeuiTexCoord2fVertex3fvSUN((const GLuint *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf());
}


//1038
static void EXEC_glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN(char *commandbuf)
{
	GLuint *rc = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *t = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *nx = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *ny = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *nz = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN(*rc, *s, *t, *nx, *ny, *nz, *x, *y, *z);
}


//1039
static void EXEC_glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN(char *commandbuf)
{

	glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN((const GLuint *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf());
}


//1040
static void EXEC_glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN(char *commandbuf)
{
	GLuint *rc = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *t = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *r = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *g = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *b = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *a = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *nx = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *ny = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *nz = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN(*rc, *s, *t, *r, *g, *b, *a, *nx, *ny, *nz, *x, *y, *z);
}


//1041
static void EXEC_glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN(char *commandbuf)
{

	glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN((const GLuint *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf());
}


//1042
static void EXEC_glBlendFuncSeparateEXT(char *commandbuf)
{
	GLenum *sfactorRGB = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *dfactorRGB = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *sfactorAlpha = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *dfactorAlpha = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glBlendFuncSeparateEXT(*sfactorRGB, *dfactorRGB, *sfactorAlpha, *dfactorAlpha);
}


//1043
static void EXEC_glVertexWeightfEXT(char *commandbuf)
{
	GLfloat *weight = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	glVertexWeightfEXT(*weight);
}


//1044
static void EXEC_glVertexWeightfvEXT(char *commandbuf)
{

	glVertexWeightfvEXT((GLfloat *)popBuf());
}


//1045
static void EXEC_glVertexWeightPointerEXT(char *commandbuf)
{
	GLsizei *size = (GLsizei*)commandbuf;    commandbuf += sizeof(GLsizei);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glVertexWeightPointerEXT(*size, *type, *stride, (GLvoid *)popBuf());
}


//1046
static void EXEC_glFlushVertexArrayRangeNV(char *commandbuf)
{

	glFlushVertexArrayRangeNV();
}


//1047
static void EXEC_glVertexArrayRangeNV(char *commandbuf)
{
	GLsizei *length = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glVertexArrayRangeNV(*length, (GLvoid *)popBuf());
}


//1048
static void EXEC_glCombinerParameterfvNV(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glCombinerParameterfvNV(*pname, (const GLfloat *)popBuf());
}


//1049
static void EXEC_glCombinerParameterfNV(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glCombinerParameterfNV(*pname, *param);
}


//1050
static void EXEC_glCombinerParameterivNV(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glCombinerParameterivNV(*pname, (const GLint *)popBuf());
}


//1051
static void EXEC_glCombinerParameteriNV(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glCombinerParameteriNV(*pname, *param);
}


//1052
static void EXEC_glCombinerInputNV(char *commandbuf)
{
	GLenum *stage = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *portion = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);
	GLenum *variable = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *input = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *mapping = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);
	GLenum *componentUsage = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glCombinerInputNV(*stage, *portion, *variable, *input, *mapping, *componentUsage);
}


//1053
static void EXEC_glCombinerOutputNV(char *commandbuf)
{
	GLenum *stage = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *portion = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);
	GLenum *abOutput = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *cdOutput = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *sumOutput = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *scale = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *bias = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLboolean *abDotProduct = (GLboolean*)commandbuf;    commandbuf += sizeof(GLboolean);
	GLboolean *cdDotProduct = (GLboolean*)commandbuf;    commandbuf += sizeof(GLboolean);
	GLboolean *muxSum = (GLboolean*)commandbuf;  commandbuf += sizeof(GLboolean);

	glCombinerOutputNV(*stage, *portion, *abOutput, *cdOutput, *sumOutput, *scale, *bias, *abDotProduct, *cdDotProduct, *muxSum);
}


//1054
static void EXEC_glFinalCombinerInputNV(char *commandbuf)
{
	GLenum *variable = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *input = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *mapping = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);
	GLenum *componentUsage = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glFinalCombinerInputNV(*variable, *input, *mapping, *componentUsage);
}


//1055
static void EXEC_glGetCombinerInputParameterfvNV(char *commandbuf)
{
	GLenum *stage = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *portion = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);
	GLenum *variable = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetCombinerInputParameterfvNV(*stage, *portion, *variable, *pname, (GLfloat *)popBuf());
}


//1056
static void EXEC_glGetCombinerInputParameterivNV(char *commandbuf)
{
	GLenum *stage = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *portion = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);
	GLenum *variable = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetCombinerInputParameterivNV(*stage, *portion, *variable, *pname, (GLint *)popBuf());
}


//1057
static void EXEC_glGetCombinerOutputParameterfvNV(char *commandbuf)
{
	GLenum *stage = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *portion = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetCombinerOutputParameterfvNV(*stage, *portion, *pname, (GLfloat *)popBuf());
}


//1058
static void EXEC_glGetCombinerOutputParameterivNV(char *commandbuf)
{
	GLenum *stage = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *portion = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetCombinerOutputParameterivNV(*stage, *portion, *pname, (GLint *)popBuf());
}


//1059
static void EXEC_glGetFinalCombinerInputParameterfvNV(char *commandbuf)
{
	GLenum *variable = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetFinalCombinerInputParameterfvNV(*variable, *pname, (GLfloat *)popBuf());
}


//1060
static void EXEC_glGetFinalCombinerInputParameterivNV(char *commandbuf)
{
	GLenum *variable = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetFinalCombinerInputParameterivNV(*variable, *pname, (GLint *)popBuf());
}


//1061
static void EXEC_glResizeBuffersMESA(char *commandbuf)
{

	glResizeBuffersMESA();
}


//1062
static void EXEC_glWindowPos2dMESA(char *commandbuf)
{
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glWindowPos2dMESA(*x, *y);
}


//1063
static void EXEC_glWindowPos2dvMESA(char *commandbuf)
{

	glWindowPos2dvMESA((const GLdouble *)popBuf());
}


//1064
static void EXEC_glWindowPos2fMESA(char *commandbuf)
{
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glWindowPos2fMESA(*x, *y);
}


//1065
static void EXEC_glWindowPos2fvMESA(char *commandbuf)
{

	glWindowPos2fvMESA((const GLfloat *)popBuf());
}


//1066
static void EXEC_glWindowPos2iMESA(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glWindowPos2iMESA(*x, *y);
}


//1067
static void EXEC_glWindowPos2ivMESA(char *commandbuf)
{

	glWindowPos2ivMESA((const GLint *)popBuf());
}


//1068
static void EXEC_glWindowPos2sMESA(char *commandbuf)
{
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glWindowPos2sMESA(*x, *y);
}


//1069
static void EXEC_glWindowPos2svMESA(char *commandbuf)
{

	glWindowPos2svMESA((const GLshort *)popBuf());
}


//1070
static void EXEC_glWindowPos3dMESA(char *commandbuf)
{
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glWindowPos3dMESA(*x, *y, *z);
}


//1071
static void EXEC_glWindowPos3dvMESA(char *commandbuf)
{

	glWindowPos3dvMESA((const GLdouble *)popBuf());
}


//1072
static void EXEC_glWindowPos3fMESA(char *commandbuf)
{
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glWindowPos3fMESA(*x, *y, *z);
}


//1073
static void EXEC_glWindowPos3fvMESA(char *commandbuf)
{

	glWindowPos3fvMESA((const GLfloat *)popBuf());
}


//1074
static void EXEC_glWindowPos3iMESA(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *z = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glWindowPos3iMESA(*x, *y, *z);
}


//1075
static void EXEC_glWindowPos3ivMESA(char *commandbuf)
{

	glWindowPos3ivMESA((const GLint *)popBuf());
}


//1076
static void EXEC_glWindowPos3sMESA(char *commandbuf)
{
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *z = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glWindowPos3sMESA(*x, *y, *z);
}


//1077
static void EXEC_glWindowPos3svMESA(char *commandbuf)
{

	glWindowPos3svMESA((const GLshort *)popBuf());
}


//1078
static void EXEC_glWindowPos4dMESA(char *commandbuf)
{
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *w = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glWindowPos4dMESA(*x, *y, *z, *w);
}


//1079
static void EXEC_glWindowPos4dvMESA(char *commandbuf)
{

	glWindowPos4dvMESA((const GLdouble *)popBuf());
}


//1080
static void EXEC_glWindowPos4fMESA(char *commandbuf)
{
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *w = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glWindowPos4fMESA(*x, *y, *z, *w);
}


//1081
static void EXEC_glWindowPos4fvMESA(char *commandbuf)
{

	glWindowPos4fvMESA((const GLfloat *)popBuf());
}


//1082
static void EXEC_glWindowPos4iMESA(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *z = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *w = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glWindowPos4iMESA(*x, *y, *z, *w);
}


//1083
static void EXEC_glWindowPos4ivMESA(char *commandbuf)
{

	glWindowPos4ivMESA((const GLint *)popBuf());
}


//1084
static void EXEC_glWindowPos4sMESA(char *commandbuf)
{
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *z = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *w = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glWindowPos4sMESA(*x, *y, *z, *w);
}


//1085
static void EXEC_glWindowPos4svMESA(char *commandbuf)
{

	glWindowPos4svMESA((const GLshort *)popBuf());
}


//1086
static void EXEC_glMultiModeDrawArraysIBM(char *commandbuf)
{
	GLsizei *primcount = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLint *modestride = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glMultiModeDrawArraysIBM((const GLenum *)popBuf(), (const GLint *)popBuf(), (const GLsizei *)popBuf(), *primcount, *modestride);
}


//1087
static void EXEC_glMultiModeDrawElementsIBM(char *commandbuf)
{
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *primcount = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLint *modestride = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glMultiModeDrawElementsIBM((const GLenum *)popBuf(), (const GLsizei *)popBuf(), *type, (const GLvoid * const *)popBuf(), *primcount, *modestride);
}


//1088
static void EXEC_glColorPointerListIBM(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLint *stride = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *ptrstride = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glColorPointerListIBM(*size, *type, *stride, (const GLvoid **)popBuf(), *ptrstride);
}


//1089
static void EXEC_glSecondaryColorPointerListIBM(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLint *stride = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *ptrstride = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glSecondaryColorPointerListIBM(*size, *type, *stride, (const GLvoid **)popBuf(), *ptrstride);
}


//1090
static void EXEC_glEdgeFlagPointerListIBM(char *commandbuf)
{
	GLint *stride = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *ptrstride = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glEdgeFlagPointerListIBM(*stride, (const GLboolean **)popBuf(), *ptrstride);
}


//1091
static void EXEC_glFogCoordPointerListIBM(char *commandbuf)
{
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLint *stride = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *ptrstride = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glFogCoordPointerListIBM(*type, *stride, (const GLvoid **)popBuf(), *ptrstride);
}


//1092
static void EXEC_glIndexPointerListIBM(char *commandbuf)
{
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLint *stride = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *ptrstride = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glIndexPointerListIBM(*type, *stride, (const GLvoid **)popBuf(), *ptrstride);
}


//1093
static void EXEC_glNormalPointerListIBM(char *commandbuf)
{
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLint *stride = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *ptrstride = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glNormalPointerListIBM(*type, *stride, (const GLvoid **)popBuf(), *ptrstride);
}


//1094
static void EXEC_glTexCoordPointerListIBM(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLint *stride = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *ptrstride = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glTexCoordPointerListIBM(*size, *type, *stride, (const GLvoid **)popBuf(), *ptrstride);
}


//1095
static void EXEC_glVertexPointerListIBM(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLint *stride = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *ptrstride = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glVertexPointerListIBM(*size, *type, *stride, (const GLvoid **)popBuf(), *ptrstride);
}


//1096
static void EXEC_glTbufferMask3DFX(char *commandbuf)
{
	GLuint *mask = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

	glTbufferMask3DFX(*mask);
}


//1097
static void EXEC_glSampleMaskEXT(char *commandbuf)
{
	GLclampf *value = (GLclampf*)commandbuf;     commandbuf += sizeof(GLclampf);
	GLboolean *invert = (GLboolean*)commandbuf;  commandbuf += sizeof(GLboolean);

	glSampleMaskEXT(*value, *invert);
}


//1098
static void EXEC_glSamplePatternEXT(char *commandbuf)
{
	GLenum *pattern = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);

	glSamplePatternEXT(*pattern);
}


//1099
static void EXEC_glTextureColorMaskSGIS(char *commandbuf)
{
	GLboolean *red = (GLboolean*)commandbuf;     commandbuf += sizeof(GLboolean);
	GLboolean *green = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);
	GLboolean *blue = (GLboolean*)commandbuf;    commandbuf += sizeof(GLboolean);
	GLboolean *alpha = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);

	//glTextureColorMaskSGIS(*red, *green, *blue, *alpha);
}


//1100
static void EXEC_glDeleteFencesNV(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glDeleteFencesNV(*n, (const GLuint *)popBuf());
}


//1101
static void EXEC_glGenFencesNV(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glGenFencesNV(*n, (GLuint *)popBuf());
}


//1102
static void EXEC_glIsFenceNV(char *commandbuf)
{
	GLuint *fence = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	pushRet(glIsFenceNV(*fence));
}


//1103
static void EXEC_glTestFenceNV(char *commandbuf)
{
	GLuint *fence = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	pushRet(glTestFenceNV(*fence));
}


//1104
static void EXEC_glGetFenceivNV(char *commandbuf)
{
	GLuint *fence = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetFenceivNV(*fence, *pname, (GLint *)popBuf());
}


//1105
static void EXEC_glFinishFenceNV(char *commandbuf)
{
	GLuint *fence = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glFinishFenceNV(*fence);
}


//1106
static void EXEC_glSetFenceNV(char *commandbuf)
{
	GLuint *fence = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *condition = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glSetFenceNV(*fence, *condition);
}


//1107
static void EXEC_glMapControlPointsNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *ustride = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);
	GLsizei *vstride = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);
	GLint *uorder = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *vorder = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLboolean *packed = (GLboolean*)commandbuf;  commandbuf += sizeof(GLboolean);

	glMapControlPointsNV(*target, *index, *type, *ustride, *vstride, *uorder, *vorder, *packed, (const GLvoid *)popBuf());
}


//1108
static void EXEC_glMapParameterivNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glMapParameterivNV(*target, *pname, (const GLint *)popBuf());
}


//1109
static void EXEC_glMapParameterfvNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glMapParameterfvNV(*target, *pname, (const GLfloat *)popBuf());
}


//1110
static void EXEC_glGetMapControlPointsNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *ustride = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);
	GLsizei *vstride = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);
	GLboolean *packed = (GLboolean*)commandbuf;  commandbuf += sizeof(GLboolean);

	glGetMapControlPointsNV(*target, *index, *type, *ustride, *vstride, *packed, (GLvoid *)popBuf());
}


//1111
static void EXEC_glGetMapParameterivNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetMapParameterivNV(*target, *pname, (GLint *)popBuf());
}


//1112
static void EXEC_glGetMapParameterfvNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetMapParameterfvNV(*target, *pname, (GLfloat *)popBuf());
}


//1113
static void EXEC_glGetMapAttribParameterivNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetMapAttribParameterivNV(*target, *index, *pname, (GLint *)popBuf());
}


//1114
static void EXEC_glGetMapAttribParameterfvNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetMapAttribParameterfvNV(*target, *index, *pname, (GLfloat *)popBuf());
}


//1115
static void EXEC_glEvalMapsNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glEvalMapsNV(*target, *mode);
}


//1116
static void EXEC_glCombinerStageParameterfvNV(char *commandbuf)
{
	GLenum *stage = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glCombinerStageParameterfvNV(*stage, *pname, (const GLfloat *)popBuf());
}


//1117
static void EXEC_glGetCombinerStageParameterfvNV(char *commandbuf)
{
	GLenum *stage = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetCombinerStageParameterfvNV(*stage, *pname, (GLfloat *)popBuf());
}


//1118
static void EXEC_glAreProgramsResidentNV(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	pushRet(glAreProgramsResidentNV(*n, (const GLuint *)popBuf(), (GLboolean *)popBuf()));
}


//1119
static void EXEC_glBindProgramNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	glBindProgramNV(*target, *program);
}


//1120
static void EXEC_glDeleteProgramsNV(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glDeleteProgramsNV(*n, (const GLuint *)popBuf());
}


//1121
static void EXEC_glExecuteProgramNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	glExecuteProgramNV(*target, *id, (const GLfloat *)popBuf());
}


//1122
static void EXEC_glGenProgramsNV(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glGenProgramsNV(*n, (GLuint *)popBuf());
}


//1123
static void EXEC_glGetProgramParameterdvNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetProgramParameterdvNV(*target, *index, *pname, (GLdouble *)popBuf());
}


//1124
static void EXEC_glGetProgramParameterfvNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetProgramParameterfvNV(*target, *index, *pname, (GLfloat *)popBuf());
}


//1125
static void EXEC_glGetProgramivNV(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetProgramivNV(*id, *pname, (GLint *)popBuf());
}


//1126
static void EXEC_glGetProgramStringNV(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetProgramStringNV(*id, *pname, (GLubyte *)popBuf());
}


//1127
static void EXEC_glGetTrackMatrixivNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *address = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetTrackMatrixivNV(*target, *address, *pname, (GLint *)popBuf());
}


//1128
static void EXEC_glGetVertexAttribdvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetVertexAttribdvNV(*index, *pname, (GLdouble *)popBuf());
}


//1129
static void EXEC_glGetVertexAttribfvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetVertexAttribfvNV(*index, *pname, (GLfloat *)popBuf());
}


//1130
static void EXEC_glGetVertexAttribivNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetVertexAttribivNV(*index, *pname, (GLint *)popBuf());
}


//1131
static void EXEC_glGetVertexAttribPointervNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetVertexAttribPointervNV(*index, *pname, (GLvoid **)popBuf());
}


//1132
static void EXEC_glIsProgramNV(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	pushRet(glIsProgramNV(*program));
}


//1133
static void EXEC_glLoadProgramNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLsizei *len = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);

	glLoadProgramNV(*target, *id, *len, (const GLubyte *)popBuf());
}


//1134
static void EXEC_glProgramParameter4dNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *w = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glProgramParameter4dNV(*target, *index, *x, *y, *z, *w);
}


//1135
static void EXEC_glProgramParameter4dvNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glProgramParameter4dvNV(*target, *index, (const GLdouble *)popBuf());
}


//1136
static void EXEC_glProgramParameter4fNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *w = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glProgramParameter4fNV(*target, *index, *x, *y, *z, *w);
}


//1137
static void EXEC_glProgramParameter4fvNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glProgramParameter4fvNV(*target, *index, (const GLfloat *)popBuf());
}


//1138
static void EXEC_glProgramParameters4dvNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLuint *num = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	glProgramParameters4dvNV(*target, *index, *num, (const GLdouble *)popBuf());
}


//1139
static void EXEC_glProgramParameters4fvNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLuint *num = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	glProgramParameters4fvNV(*target, *index, *num, (const GLfloat *)popBuf());
}


//1140
static void EXEC_glRequestResidentProgramsNV(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glRequestResidentProgramsNV(*n, (GLuint *)popBuf());
}


//1141
static void EXEC_glTrackMatrixNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *address = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLenum *matrix = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *transform = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glTrackMatrixNV(*target, *address, *matrix, *transform);
}


//1142
static void EXEC_glVertexAttribPointerNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glVertexAttribPointerNV(*index, *size, *type, *stride, (const GLvoid *)popBuf());
}


//1143
static void EXEC_glVertexAttrib1sNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glVertexAttrib1sNV(*index, *x);
}


//1144
static void EXEC_glVertexAttrib1svNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib1svNV(*index, (const GLshort *)popBuf());
}


//1145
static void EXEC_glVertexAttrib2sNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glVertexAttrib2sNV(*index, *x, *y);
}


//1146
static void EXEC_glVertexAttrib2svNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib2svNV(*index, (const GLshort *)popBuf());
}


//1147
static void EXEC_glVertexAttrib3sNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *z = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glVertexAttrib3sNV(*index, *x, *y, *z);
}


//1148
static void EXEC_glVertexAttrib3svNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib3svNV(*index, (const GLshort *)popBuf());
}


//1149
static void EXEC_glVertexAttrib4sNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *z = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *w = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glVertexAttrib4sNV(*index, *x, *y, *z, *w);
}


//1150
static void EXEC_glVertexAttrib4svNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4svNV(*index, (const GLshort *)popBuf());
}


//1151
static void EXEC_glVertexAttrib1fNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glVertexAttrib1fNV(*index, *x);
}


//1152
static void EXEC_glVertexAttrib1fvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib1fvNV(*index, (const GLfloat *)popBuf());
}


//1153
static void EXEC_glVertexAttrib2fNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glVertexAttrib2fNV(*index, *x, *y);
}


//1154
static void EXEC_glVertexAttrib2fvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib2fvNV(*index, (const GLfloat *)popBuf());
}


//1155
static void EXEC_glVertexAttrib3fNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glVertexAttrib3fNV(*index, *x, *y, *z);
}


//1156
static void EXEC_glVertexAttrib3fvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib3fvNV(*index, (const GLfloat *)popBuf());
}


//1157
static void EXEC_glVertexAttrib4fNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *w = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glVertexAttrib4fNV(*index, *x, *y, *z, *w);
}


//1158
static void EXEC_glVertexAttrib4fvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4fvNV(*index, (const GLfloat *)popBuf());
}


//1159
static void EXEC_glVertexAttrib1dNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glVertexAttrib1dNV(*index, *x);
}


//1160
static void EXEC_glVertexAttrib1dvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib1dvNV(*index, (const GLdouble *)popBuf());
}


//1161
static void EXEC_glVertexAttrib2dNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glVertexAttrib2dNV(*index, *x, *y);
}


//1162
static void EXEC_glVertexAttrib2dvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib2dvNV(*index, (const GLdouble *)popBuf());
}


//1163
static void EXEC_glVertexAttrib3dNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glVertexAttrib3dNV(*index, *x, *y, *z);
}


//1164
static void EXEC_glVertexAttrib3dvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib3dvNV(*index, (const GLdouble *)popBuf());
}


//1165
static void EXEC_glVertexAttrib4dNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *w = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glVertexAttrib4dNV(*index, *x, *y, *z, *w);
}


//1166
static void EXEC_glVertexAttrib4dvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4dvNV(*index, (const GLdouble *)popBuf());
}


//1167
static void EXEC_glVertexAttrib4ubNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLubyte *x = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *y = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *z = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *w = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);

	glVertexAttrib4ubNV(*index, *x, *y, *z, *w);
}


//1168
static void EXEC_glVertexAttrib4ubvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4ubvNV(*index, (const GLubyte *)popBuf());
}


//1169
static void EXEC_glVertexAttribs1svNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glVertexAttribs1svNV(*index, *n, (const GLshort *)popBuf());
}


//1170
static void EXEC_glVertexAttribs2svNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glVertexAttribs2svNV(*index, *n, (const GLshort *)popBuf());
}


//1171
static void EXEC_glVertexAttribs3svNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glVertexAttribs3svNV(*index, *n, (const GLshort *)popBuf());
}


//1172
static void EXEC_glVertexAttribs4svNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glVertexAttribs4svNV(*index, *n, (const GLshort *)popBuf());
}


//1173
static void EXEC_glVertexAttribs1fvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glVertexAttribs1fvNV(*index, *n, (const GLfloat *)popBuf());
}


//1174
static void EXEC_glVertexAttribs2fvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glVertexAttribs2fvNV(*index, *n, (const GLfloat *)popBuf());
}


//1175
static void EXEC_glVertexAttribs3fvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glVertexAttribs3fvNV(*index, *n, (const GLfloat *)popBuf());
}


//1176
static void EXEC_glVertexAttribs4fvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glVertexAttribs4fvNV(*index, *n, (const GLfloat *)popBuf());
}


//1177
static void EXEC_glVertexAttribs1dvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glVertexAttribs1dvNV(*index, *n, (const GLdouble *)popBuf());
}


//1178
static void EXEC_glVertexAttribs2dvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glVertexAttribs2dvNV(*index, *n, (const GLdouble *)popBuf());
}


//1179
static void EXEC_glVertexAttribs3dvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glVertexAttribs3dvNV(*index, *n, (const GLdouble *)popBuf());
}


//1180
static void EXEC_glVertexAttribs4dvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glVertexAttribs4dvNV(*index, *n, (const GLdouble *)popBuf());
}


//1181
static void EXEC_glVertexAttribs4ubvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glVertexAttribs4ubvNV(*index, *n, (const GLubyte *)popBuf());
}


//1182
static void EXEC_glGenFragmentShadersATI(char *commandbuf)
{
	GLuint *range = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	pushRet(glGenFragmentShadersATI(*range));
}


//1183
static void EXEC_glBindFragmentShaderATI(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	glBindFragmentShaderATI(*id);
}


//1184
static void EXEC_glDeleteFragmentShaderATI(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	glDeleteFragmentShaderATI(*id);
}


//1185
static void EXEC_glBeginFragmentShaderATI(char *commandbuf)
{

	glBeginFragmentShaderATI();
}


//1186
static void EXEC_glEndFragmentShaderATI(char *commandbuf)
{

	glEndFragmentShaderATI();
}


//1187
static void EXEC_glPassTexCoordATI(char *commandbuf)
{
	GLuint *dst = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *coord = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *swizzle = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);

	glPassTexCoordATI(*dst, *coord, *swizzle);
}


//1188
static void EXEC_glSampleMapATI(char *commandbuf)
{
	GLuint *dst = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *interp = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLenum *swizzle = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);

	glSampleMapATI(*dst, *interp, *swizzle);
}


//1189
static void EXEC_glColorFragmentOp1ATI(char *commandbuf)
{
	GLenum *op = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *dst = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *dstMask = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *dstMod = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLuint *arg1 = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);
	GLuint *arg1Rep = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *arg1Mod = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	glColorFragmentOp1ATI(*op, *dst, *dstMask, *dstMod, *arg1, *arg1Rep, *arg1Mod);
}


//1190
static void EXEC_glColorFragmentOp2ATI(char *commandbuf)
{
	GLenum *op = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *dst = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *dstMask = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *dstMod = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLuint *arg1 = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);
	GLuint *arg1Rep = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *arg1Mod = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *arg2 = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);
	GLuint *arg2Rep = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *arg2Mod = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	glColorFragmentOp2ATI(*op, *dst, *dstMask, *dstMod, *arg1, *arg1Rep, *arg1Mod, *arg2, *arg2Rep, *arg2Mod);
}


//1191
static void EXEC_glColorFragmentOp3ATI(char *commandbuf)
{
	GLenum *op = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *dst = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *dstMask = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *dstMod = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLuint *arg1 = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);
	GLuint *arg1Rep = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *arg1Mod = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *arg2 = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);
	GLuint *arg2Rep = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *arg2Mod = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *arg3 = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);
	GLuint *arg3Rep = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *arg3Mod = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	glColorFragmentOp3ATI(*op, *dst, *dstMask, *dstMod, *arg1, *arg1Rep, *arg1Mod, *arg2, *arg2Rep, *arg2Mod, *arg3, *arg3Rep, *arg3Mod);
}


//1192
static void EXEC_glAlphaFragmentOp1ATI(char *commandbuf)
{
	GLenum *op = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *dst = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *dstMod = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLuint *arg1 = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);
	GLuint *arg1Rep = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *arg1Mod = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	glAlphaFragmentOp1ATI(*op, *dst, *dstMod, *arg1, *arg1Rep, *arg1Mod);
}


//1193
static void EXEC_glAlphaFragmentOp2ATI(char *commandbuf)
{
	GLenum *op = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *dst = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *dstMod = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLuint *arg1 = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);
	GLuint *arg1Rep = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *arg1Mod = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *arg2 = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);
	GLuint *arg2Rep = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *arg2Mod = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	glAlphaFragmentOp2ATI(*op, *dst, *dstMod, *arg1, *arg1Rep, *arg1Mod, *arg2, *arg2Rep, *arg2Mod);
}


//1194
static void EXEC_glAlphaFragmentOp3ATI(char *commandbuf)
{
	GLenum *op = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *dst = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *dstMod = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLuint *arg1 = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);
	GLuint *arg1Rep = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *arg1Mod = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *arg2 = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);
	GLuint *arg2Rep = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *arg2Mod = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *arg3 = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);
	GLuint *arg3Rep = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *arg3Mod = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	glAlphaFragmentOp3ATI(*op, *dst, *dstMod, *arg1, *arg1Rep, *arg1Mod, *arg2, *arg2Rep, *arg2Mod, *arg3, *arg3Rep, *arg3Mod);
}


//1195
static void EXEC_glSetFragmentShaderConstantATI(char *commandbuf)
{
	GLuint *dst = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	glSetFragmentShaderConstantATI(*dst, (const GLfloat *)popBuf());
}


//1196
static void EXEC_glDrawMeshArraysSUN(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLint *first = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	//glDrawMeshArraysSUN(*mode, *first, *count, *width);
}


//1197
static void EXEC_glPointParameteriNV(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glPointParameteriNV(*pname, *param);
}


//1198
static void EXEC_glPointParameterivNV(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glPointParameterivNV(*pname, (const GLint *)popBuf());
}


//1199
static void EXEC_glActiveStencilFaceEXT(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glActiveStencilFaceEXT(*face);
}


//1200
static void EXEC_glDrawBuffersATI(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glDrawBuffersATI(*n, (const GLenum *)popBuf());
}


//1201
static void EXEC_glProgramNamedParameter4fNV(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLsizei *len = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *w = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glProgramNamedParameter4fNV(*id, *len, (const GLubyte *)popBuf(), *x, *y, *z, *w);
}


//1202
static void EXEC_glProgramNamedParameter4dNV(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLsizei *len = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *w = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glProgramNamedParameter4dNV(*id, *len, (const GLubyte *)popBuf(), *x, *y, *z, *w);
}


//1203
static void EXEC_glProgramNamedParameter4fvNV(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLsizei *len = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);

	glProgramNamedParameter4fvNV(*id, *len, (const GLubyte *)popBuf(), (const GLfloat *)popBuf());
}


//1204
static void EXEC_glProgramNamedParameter4dvNV(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLsizei *len = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);

	glProgramNamedParameter4dvNV(*id, *len, (const GLubyte *)popBuf(), (const GLdouble *)popBuf());
}


//1205
static void EXEC_glGetProgramNamedParameterfvNV(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLsizei *len = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);

	glGetProgramNamedParameterfvNV(*id, *len, (const GLubyte *)popBuf(), (GLfloat *)popBuf());
}


//1206
static void EXEC_glGetProgramNamedParameterdvNV(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLsizei *len = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);

	glGetProgramNamedParameterdvNV(*id, *len, (const GLubyte *)popBuf(), (GLdouble *)popBuf());
}


//1207
static void EXEC_glDepthBoundsEXT(char *commandbuf)
{
	GLclampd *zmin = (GLclampd*)commandbuf;  commandbuf += sizeof(GLclampd);
	GLclampd *zmax = (GLclampd*)commandbuf;  commandbuf += sizeof(GLclampd);

	glDepthBoundsEXT(*zmin, *zmax);
}


//1208
static void EXEC_glBlendEquationSeparateEXT(char *commandbuf)
{
	GLenum *modeRGB = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);
	GLenum *modeA = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glBlendEquationSeparateEXT(*modeRGB, *modeA);
}


//1209
static void EXEC_glBlitFramebufferEXT(char *commandbuf)
{
	GLint *srcX0 = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *srcY0 = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *srcX1 = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *srcY1 = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *dstX0 = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *dstY0 = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *dstX1 = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *dstY1 = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLbitfield *mask = (GLbitfield*)commandbuf;  commandbuf += sizeof(GLbitfield);
	GLenum *filter = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glBlitFramebufferEXT(*srcX0, *srcY0, *srcX1, *srcY1, *dstX0, *dstY0, *dstX1, *dstY1, *mask, *filter);
}


//1210
static void EXEC_glBlendEquationSeparateATI(char *commandbuf)
{
	GLenum *modeRGB = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);
	GLenum *modeA = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	//glBlendEquationSeparateATI(*modeRGB, *modeA);
}


//1211
static void EXEC_glStencilOpSeparateATI(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *sfail = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *zfail = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *zpass = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glStencilOpSeparateATI(*face, *sfail, *zfail, *zpass);
}


//1212
static void EXEC_glStencilFuncSeparateATI(char *commandbuf)
{
	GLenum *frontfunc = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *backfunc = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLint *ref = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLuint *mask = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

	glStencilFuncSeparateATI(*frontfunc, *backfunc, *ref, *mask);
}


//1213
static void EXEC_glProgramEnvParameters4fvEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	#ifndef SYMPHONY
	glProgramEnvParameters4fvEXT(*target, *index, *count, (const GLfloat *)popBuf());
	#endif
}


//1214
static void EXEC_glProgramLocalParameters4fvEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	#ifndef SYMPHONY
	glProgramLocalParameters4fvEXT(*target, *index, *count, (const GLfloat *)popBuf());
	#endif
}


//1215
static void EXEC_glGetQueryObjecti64vEXT(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	#ifndef SYMPHONY
	glGetQueryObjecti64vEXT(*id, *pname, (GLint64EXT *)popBuf());
	#endif
}


//1216
static void EXEC_glGetQueryObjectui64vEXT(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	#ifndef SYMPHONY
	glGetQueryObjectui64vEXT(*id, *pname, (GLuint64EXT *)popBuf());
	#endif
}


//1217
static void EXEC_glBlendFuncSeparateINGR(char *commandbuf)
{
	GLenum *sfactorRGB = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *dfactorRGB = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *sfactorAlpha = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *dfactorAlpha = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	//glBlendFuncSeparateINGR(*sfactorRGB, *dfactorRGB, *sfactorAlpha, *dfactorAlpha);
}


//1218
static void EXEC_glCreateDebugObjectMESA(char *commandbuf)
{

	//pushRet(glCreateDebugObjectMESA());
}


//1219
static void EXEC_glClearDebugLogMESA(char *commandbuf)
{
	GLhandleARB *obj = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);
	GLenum *logType = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);
	GLenum *shaderType = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	//glClearDebugLogMESA(*obj, *logType, *shaderType);
}


//1220
static void EXEC_glGetDebugLogMESA(char *commandbuf)
{
	GLhandleARB *obj = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);
	GLenum *logType = (GLenum*)commandbuf;      commandbuf += sizeof(GLenum);
	GLenum *shaderType = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *maxLength = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *length = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);

	//glGetDebugLogMESA(*obj, *logType, *shaderType, *maxLength, length, (GLcharARB *)popBuf());
}


//1221
static void EXEC_glGetDebugLogLengthMESA(char *commandbuf)
{
	GLhandleARB *obj = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);
	GLenum *logType = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);
	GLenum *shaderType = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	//pushRet(glGetDebugLogLengthMESA(*obj, *logType, *shaderType));
}


//1222
static void EXEC_glPointParameterfSGIS(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	//glPointParameterfSGIS(*pname, *param);
}


//1223
static void EXEC_glPointParameterfvSGIS(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	//glPointParameterfvSGIS(*pname, (const GLfloat *)popBuf());
}


//1224
static void EXEC_glIglooInterfaceSGIX(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	//glIglooInterfaceSGIX(*pname, (const GLvoid *)popBuf());
}


//1225
static void EXEC_glDeformationMap3dSGIX(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLdouble *u1 = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *u2 = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLint *ustride = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *uorder = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLdouble *v1 = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *v2 = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLint *vstride = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *vorder = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLdouble *w1 = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *w2 = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLint *wstride = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *worder = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	//glDeformationMap3dSGIX(*target, *u1, *u2, *ustride, *uorder, *v1, *v2, *vstride, *vorder, *w1, *w2, *wstride, *worder, (const GLdouble *)popBuf());
}


//1226
static void EXEC_glDeformationMap3fSGIX(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLfloat *u1 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *u2 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLint *ustride = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *uorder = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLfloat *v1 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *v2 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLint *vstride = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *vorder = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLfloat *w1 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *w2 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLint *wstride = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *worder = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	//glDeformationMap3fSGIX(*target, *u1, *u2, *ustride, *uorder, *v1, *v2, *vstride, *vorder, *w1, *w2, *wstride, *worder, (const GLfloat *)popBuf());
}


//1227
static void EXEC_glDeformSGIX(char *commandbuf)
{
	GLenum *mask = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	//glDeformSGIX(*mask);
}


//1228
static void EXEC_glLoadIdentityDeformationMapSGIX(char *commandbuf)
{
	GLenum *mask = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	//glLoadIdentityDeformationMapSGIX(*mask);
}


/********************************************************
	GLU Intercepts
********************************************************/

//1501
static void EXEC_gluBeginCurve(char *commandbuf)
{
	LOG("Called unimplemted stub gluBeginCurve!\n");
	// (GLUnurbs* nurb)
}


//1502
static void EXEC_gluBeginPolygon(char *commandbuf)
{
	LOG("Called unimplemted stub gluBeginPolygon!\n");
	//(GLUtesselator* tess)
}


//1503
static void EXEC_gluBeginSurface(char *commandbuf)
{
	LOG("Called unimplemted stub gluBeginSurface!\n");
	// (GLUnurbs* nurb)
}


//1504
static void EXEC_gluBeginTrim(char *commandbuf)
{
	LOG("Called unimplemted stub gluBeginTrim!\n");
	// (GLUnurbs* nurb)
}


//1505
static void EXEC_gluBuild1DMipmapLevels(char *commandbuf)
{
	LOG("Called unimplemted stub gluBuild1DMipmapLevels !\n");
	// (GLenum target, GLint internalFormat, GLsizei width, GLenum format, GLenum type, GLint level, GLint base, GLint max, const void *data)
	//returns GLint
}


//1506
static void EXEC_gluBuild1DMipmaps(char *commandbuf)
{
	LOG("Called unimplemted stub gluBuild1DMipmaps!\n");
	//(GLenum target, GLint internalFormat, GLsizei width, GLenum format, GLenum type, const void *data)
	//returns GLint
}


//1507
static void EXEC_gluBuild2DMipmapLevels(char *commandbuf)
{
	LOG("Called unimplemted stub gluBuild2DMipmapLevels!\n");
	//(GLenum target, GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, GLint level, GLint base, GLint max, const void *data)
	//returns GLint
}


//1508
static void EXEC_gluBuild2DMipmaps(char *commandbuf)
{
	LOG("Called unimplemted stub gluBuild2DMipmaps!\n");
	//(GLenum target, GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *data)
	//returns GLint
}


//1509
static void EXEC_gluBuild3DMipmapLevels(char *commandbuf)
{
	LOG("Called unimplemted stub gluBuild3DMipmapLevels!\n");
	//(GLenum target, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLint level, GLint base, GLint max, const void *data)
	//returns GLint
}


//1510
static void EXEC_gluBuild3DMipmaps(char *commandbuf)
{
	//(GLenum target, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *data)
	LOG("Called unimplemted stub gluBuild3DMipmaps!\n");
	//returns GLint
}


//1511
static void EXEC_gluCheckExtension(char *commandbuf)
{
	LOG("Called unimplemted stub gluCheckExtension!\n");
	//(const GLubyte *extName, const GLubyte *extString)
	//returns GLboolean
}


//1512
static void EXEC_gluCylinder(char *commandbuf)
{
	LOG("Called unimplemted stub gluCylinder!\n");
	//(GLUquadric* quad, GLdouble base, GLdouble top, GLdouble height, GLint slices, GLint stacks)
}


//1513
static void EXEC_gluDeleteNurbsRenderer(char *commandbuf)
{
	LOG("Called unimplemted stub gluDeleteNurbsRenderer!\n");
	//(GLUnurbs* nurb)
}


//1514
static void EXEC_gluDeleteQuadric(char *commandbuf)
{
	LOG("Called unimplemted stub gluDeleteQuadric!\n");
	//(GLUquadric* quad)
}


//1515
static void EXEC_gluDeleteTess(char *commandbuf)
{
	LOG("Called unimplemted stub gluDeleteTess!\n");
	//(GLUtesselator* tess)
}


//1516
static void EXEC_gluDisk(char *commandbuf)
{
	LOG("Called unimplemted stub gluDisk!\n");
	//(GLUquadric* quad, GLdouble inner, GLdouble outer, GLint slices, GLint loops)
}


//1517
static void EXEC_gluEndCurve(char *commandbuf)
{
	LOG("Called unimplemted stub gluEndCurve!\n");
	//(GLUnurbs* nurb)
}


//1518
static void EXEC_gluEndPolygon(char *commandbuf)
{
	LOG("Called unimplemted stub gluEndPolygon!\n");
	//(GLUtesselator* tess)
}


//1519
static void EXEC_gluEndSurface(char *commandbuf)
{
	LOG("Called unimplemted stub gluEndSurface!\n");
	//(GLUnurbs* nurb)
}


//1520
static void EXEC_gluEndTrim(char *commandbuf)
{
	LOG("Called unimplemted stub gluEndTrim!\n");
	//(GLUnurbs* nurb)
}


//1521
static void EXEC_gluErrorString(char *commandbuf)
{
	LOG("Called unimplemted stub gluErrorString!\n");
	//(GLenum error)
	//returns const GLubyte *
}


//1522
static void EXEC_gluGetNurbsProperty(char *commandbuf)
{
	LOG("Called unimplemted stub gluGetNurbsProperty!\n");
	//(GLUnurbs* nurb, GLenum property, GLfloat* data)
}


//1523
static void EXEC_gluGetString(char *commandbuf)
{
	LOG("Called unimplemted stub gluGetString!\n");
	//(GLenum name)
	//returns const GLubyte *
}


//1524
static void EXEC_gluGetTessProperty(char *commandbuf)
{
	LOG("Called unimplemted stub gluGetTessProperty!\n");
	//(GLUtesselator* tess, GLenum which, GLdouble* data)
}


//1525
static void EXEC_gluLoadSamplingMatrices(char *commandbuf)
{
	LOG("Called unimplemted stub gluLoadSamplingMatrices!\n");
	//(GLUnurbs* nurb, const GLfloat *model, const GLfloat *perspective, const GLint *view)
}


//1526
static void EXEC_gluLookAt(char *commandbuf)
{
	LOG("Called untested stub gluLookAt!\n");
   /* GLdouble *eyeX = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *eyeX = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *eyeX = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *eyeX = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *eyeX = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *eyeX = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *eyeX = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *eyeX = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
*/
    //glDeformationMap3fSGIX(*target, *u1, *u2, *ustride, *uorder, *v1, *v2, *vstride, *vorder, *w1, *w2, *wstride, *worder, (const GLfloat *)popBuf());
	//(GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ, GLdouble centerX, GLdouble centerY, GLdouble centerZ, GLdouble upX, GLdouble upY, GLdouble upZ)
}


//1527
static void EXEC_gluNewNurbsRenderer(char *commandbuf)
{
	LOG("Called unimplemted stub gluNewNurbsRenderer!\n");
	//returns GLUnurbs*
}


//1528
static void EXEC_gluNewQuadric(char *commandbuf)
{
	LOG("Called unimplemted stub gluNewQuadric!\n");
	//returns GLUquadric*
}


//1529
static void EXEC_gluNewTess(char *commandbuf)
{
	LOG("Called unimplemted stub gluNewTess!\n");
	//returns GLUtesselator*
}


//1530
static void EXEC_gluNextContour(char *commandbuf)
{
	LOG("Called unimplemted stub gluNextContour!\n");
	//(GLUtesselator* tess, GLenum type)
}


//1531
static void EXEC_gluNurbsCallback(char *commandbuf)
{
	LOG("Called unimplemted stub gluNurbsCallback!\n");
	//(GLUnurbs* nurb, GLenum which, _GLUfuncptr CallBackFunc)
}


//1532
static void EXEC_gluNurbsCallbackData(char *commandbuf)
{
	LOG("Called unimplemted stub gluNurbsCallbackData!\n");
	//(GLUnurbs* nurb, GLvoid* userData)
}


//1533
static void EXEC_gluNurbsCallbackDataEXT(char *commandbuf)
{
	LOG("Called unimplemted stub gluNurbsCallbackDataEXT!\n");
	//(GLUnurbs* nurb, GLvoid* userData)
}


//1534
static void EXEC_gluNurbsCurve(char *commandbuf)
{
	LOG("Called unimplemted stub gluNurbsCurve!\n");
	//(GLUnurbs* nurb, GLint knotCount, GLfloat *knots, GLint stride, GLfloat *control, GLint order, GLenum type)
}


//1535
static void EXEC_gluNurbsProperty(char *commandbuf)
{
	LOG("Called unimplemted stub gluNurbsProperty!\n");
	//(GLUnurbs* nurb, GLenum property, GLfloat value)
}


//1536
static void EXEC_gluNurbsSurface(char *commandbuf)
{
	LOG("Called unimplemted stub gluNurbsSurface!\n");
	//(GLUnurbs* nurb, GLint sKnotCount, GLfloat* sKnots, GLint tKnotCount, GLfloat* tKnots, GLint sStride, GLint tStride, GLfloat* control, GLint sOrder, GLint tOrder, GLenum type)
}


//1537
static void EXEC_gluOrtho2D(char *commandbuf)
{
	LOG("Called unimplemted stub gluOrtho2D!\n");
	//(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top)
}


//1538
static void EXEC_gluPartialDisk(char *commandbuf)
{
	LOG("Called unimplemted stub gluPartialDisk!\n");
	//(GLUquadric* quad, GLdouble inner, GLdouble outer, GLint slices, GLint loops, GLdouble start, GLdouble sweep)
}


//1539
static void EXEC_gluPerspective(char *commandbuf)
{
	GLdouble *fovy = (GLdouble*)commandbuf;  commandbuf += sizeof(GLdouble);
	GLdouble *aspect = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *zNear = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *zFar = (GLdouble*)commandbuf;  commandbuf += sizeof(GLdouble);
	gluPerspective(*fovy, *aspect, *zNear, *zFar);
}


//1540
static void EXEC_gluPickMatrix(char *commandbuf)
{
	LOG("Called unimplemted stub gluPickMatrix!\n");
	//(GLdouble x, GLdouble y, GLdouble delX, GLdouble delY, GLint *viewport)
}


//1541
static void EXEC_gluProject(char *commandbuf)
{
	LOG("Called unimplemted stub gluProject!\n");
	//(GLdouble objX, GLdouble objY, GLdouble objZ, const GLdouble *model, const GLdouble *proj, const GLint *view, GLdouble* winX, GLdouble* winY, GLdouble* winZ)
	//returns GLint
}


//1542
static void EXEC_gluPwlCurve(char *commandbuf)
{
	LOG("Called unimplemted stub gluPwlCurve!\n");
	//(GLUnurbs* nurb, GLint count, GLfloat* data, GLint stride, GLenum type)
}


//1543
static void EXEC_gluQuadricCallback(char *commandbuf)
{
	LOG("Called unimplemted stub gluQuadricCallback!\n");
	//(GLUquadric* quad, GLenum which, _GLUfuncptr CallBackFunc)
}


//1544
static void EXEC_gluQuadricDrawStyle(char *commandbuf)
{
	LOG("Called unimplemted stub gluQuadricDrawStyle!\n");
	//(GLUquadric* quad, GLenum draw)
}


//1545
static void EXEC_gluQuadricNormals(char *commandbuf)
{
	LOG("Called unimplemted stub gluQuadricNormals!\n");
	//(GLUquadric* quad, GLenum normal)
}


//1546
static void EXEC_gluQuadricOrientation(char *commandbuf)
{
	LOG("Called unimplemted stub gluQuadricOrientation!\n");
	//(GLUquadric* quad, GLenum orientation)
}


//1547
static void EXEC_gluQuadricTexture(char *commandbuf)
{
	LOG("Called unimplemted stub gluQuadricTexture!\n");
	//(GLUquadric* quad, GLboolean texture)
}


//1548
static void EXEC_glugluScaleImage(char *commandbuf)
{
	LOG("Called unimplemted stub gluScaleImage!\n");
	//(GLenum format, GLsizei wIn, GLsizei hIn, GLenum typeIn, const void *dataIn, GLsizei wOut, GLsizei hOut, GLenum typeOut, GLvoid* dataOut)
	//returns Glint
}


//1549
static void EXEC_gluSphere(char *commandbuf)
{
	LOG("Called unimplemted stub gluSphere!\n");
	//(GLUquadric* quad, GLdouble radius, GLint slices, GLint stacks)
}


//1550
static void EXEC_gluTessBeginContour(char *commandbuf)
{
	LOG("Called unimplemted stub gluTessBeginContour!\n");
	//(GLUtesselator* tess)
}


//1551
static void EXEC_gluTessBeginPolygon(char *commandbuf)
{
	LOG("Called unimplemted stub gluTessBeginPolygon!\n");
	//(GLUtesselator* tess, GLvoid* data)
}


//1552
static void EXEC_gluTessCallback(char *commandbuf)
{
	LOG("Called unimplemted stub gluTessCallback!\n");
	//(GLUtesselator* tess, GLenum which, _GLUfuncptr CallBackFunc)
}


//1553
static void EXEC_gluTessEndContour(char *commandbuf)
{
	LOG("Called unimplemted stub gluTessEndContour!\n");
	//(GLUtesselator* tess)
}


//1554
static void EXEC_gluTessEndPolygon(char *commandbuf)
{
	LOG("Called unimplemted stub gluTessEndPolygon!\n");
	//(GLUtesselator* tess)
}


//1555
static void EXEC_gluTessNormal(char *commandbuf)
{
	LOG("Called unimplemted stub gluTessNormal!\n");
	//(GLUtesselator* tess, GLdouble valueX, GLdouble valueY, GLdouble valueZ)
}


//1556
static void EXEC_gluTessProperty(char *commandbuf)
{
	LOG("Called unimplemted stub gluTessProperty!\n");
	//(GLUtesselator* tess, GLenum which, GLdouble data)
}


//1557
static void EXEC_gluTessVertex(char *commandbuf)
{
	LOG("Called unimplemted stub gluTessVertex!\n");
	//(GLUtesselator* tess, GLdouble *location, GLvoid* data)
}


//1558
static void EXEC_gluUnProject(char *commandbuf)
{
	LOG("Called unimplemted stub gluUnProject!\n");
	//(GLdouble winX, GLdouble winY, GLdouble winZ, const GLdouble *model, const GLdouble *proj, const GLint *view, GLdouble* objX, GLdouble* objY, GLdouble* objZ)
	//returns glint
}


//1559
static void EXEC_gluUnProject4(char *commandbuf)
{
	LOG("Called unimplemted stub gluUnProject4!\n");
	//(GLdouble winX, GLdouble winY, GLdouble winZ, GLdouble clipW, const GLdouble *model, const GLdouble *proj, const GLint *view, GLdouble nearVal, GLdouble farVal, GLdouble* objX, GLdouble* objY, GLdouble* objZ, GLdouble* objW)
	//returns glint
}


/********************************************************
	GLX Intercepts
********************************************************/

//1601
static void EXEC_glXChooseVisual(char *commandbuf)
{
	LOG("Called unimplemted stub glXChooseVisual!\n");
	//( Display *dpy, int screen, int *attribList )
	//returns XVisualInfo*
}


//1602
static void EXEC_glXCreateContext(char *commandbuf)
{
	LOG("Called unimplemted stub glXCreateContext!\n");
	//( Display *dpy, XVisualInfo *vis, GLXContext shareList, Bool direct )
	//returns GLXContext
}


//1603
static void EXEC_glXDestroyContext(char *commandbuf)
{
	LOG("Called unimplemted stub glXDestroyContext!\n");
	//( Display *dpy, GLXContext ctx )
}


//1604
static void EXEC_glXMakeCurrent(char *commandbuf)
{
	LOG("Called unimplemted stub glXMakeCurrent!\n");
	//( Display *dpy, GLXDrawable drawable, GLXContext ctx)
	//returns Bool
}


//1605
static void EXEC_glXCopyContext(char *commandbuf)
{
	LOG("Called unimplemted stub glXCopyContext!\n");
	//( Display *dpy, GLXContext src, GLXContext dst, unsigned long mask )
}


//1606
static void EXEC_glXSwapBuffers(char *commandbuf)
{
	LOG("Called unimplemted stub glXSwapBuffers!\n");
	//( Display *dpy, GLXDrawable drawable )
}


//1607
static void EXEC_glXCreateGLXPixmap(char *commandbuf)
{
	LOG("Called unimplemted stub glXCreateGLXPixmap!\n");
	//( Display *dpy, XVisualInfo *visual, Pixmap pixmap )
	//returns GLXPixmap
}


//1608
static void EXEC_glXDestroyGLXPixmap(char *commandbuf)
{
	LOG("Called unimplemted stub glXDestroyGLXPixmap!\n");
	//( Display *dpy, GLXPixmap pixmap )
}


//1609
static void EXEC_glXQueryExtension(char *commandbuf)
{
	LOG("Called unimplemted stub glXQueryExtension!\n");
	//( Display *dpy, int *errorb, int *event )
	//returns bool
}


//1610
static void EXEC_glXQueryVersion(char *commandbuf)
{
	LOG("Called unimplemted stub glXQueryVersion!\n");
	//( Display *dpy, int *maj, int *min )
	//returns bool
}


//1611
static void EXEC_glXIsDirect(char *commandbuf)
{
	LOG("Called unimplemted stub glXIsDirect!\n");
	//( Display *dpy, GLXContext ctx )
	//returns bool
}


//1612
static void EXEC_glXGetConfig(char *commandbuf)
{
	LOG("Called unimplemted stub glXGetConfig!\n");
	//( Display *dpy, XVisualInfo *visual, int attrib, int *value )
	//returns int
}


//1613
static void EXEC_glXGetCurrentContext(char *commandbuf)
{
	LOG("Called unimplemted stub glXGetCurrentContext!\n");
	//returns GLXContext
}


//1614
static void EXEC_glXGetCurrentDrawable(char *commandbuf)
{
	LOG("Called unimplemted stub glXGetCurrentDrawable!\n");
	//returns GLXDrawable
}


//1615
static void EXEC_glXWaitGL(char *commandbuf)
{
	LOG("Called unimplemted stub glXWaitGL!\n");
}


//1616
static void EXEC_glXWaitX(char *commandbuf)
{
	LOG("Called unimplemted stub glXWaitX!\n");
}


//1617
static void EXEC_glXUseXFont(char *commandbuf)
{
	LOG("Called unimplemted stub glXUseXFont!\n");
	//( Font font, int first, int count, int list )
}


//GLX 1.1 and later
//1618
static void EXEC_glXQueryExtensionsString(char *commandbuf)
{
	LOG("Called unimplemted stub glXQueryExtensionsString!\n");
	//( Display *dpy, int screen )
	//returns const char *
}


//1619
static void EXEC_glXQueryServerString(char *commandbuf)
{
	LOG("Called unimplemted stub glXQueryServerString!\n");
	//( Display *dpy, int screen, int name )
	//returns const char *
}


//1620
static void EXEC_glXGetClientString(char *commandbuf)
{
	LOG("Called unimplemted stub glXGetClientString!\n");
	//( Display *dpy, int name )
	//returns const char *
}


// GLX 1.2 and later
//1621
static void EXEC_glXGetCurrentDisplay(char *commandbuf)
{
	LOG("Called unimplemted stub glXGetCurrentDisplay!\n");
	//returns Display *
}


// GLX 1.3 and later
//1622
static void EXEC_glXChooseFBConfig(char *commandbuf)
{
	LOG("Called unimplemted stub glXChooseFBConfig!\n");
	//( Display *dpy, int screen, const int *attribList, int *nitems )
	//returns GLXFBConfig *
}


//1623
static void EXEC_glXGetFBConfigAttrib(char *commandbuf)
{
	LOG("Called unimplemted stub glXGetFBConfigAttrib!\n");
	//( Display *dpy, GLXFBConfig config, int attribute, int *value )
	//returns int
}


//1624
static void EXEC_glXGetFBConfigs(char *commandbuf)
{
	LOG("Called unimplemted stub glXGetFBConfigs!\n");
	//( Display *dpy, int screen, int *nelements )
	//returns GLXFBConfig *
}


//1625
static void EXEC_glXGetVisualFromFBConfig(char *commandbuf)
{
	LOG("Called unimplemted stub glXGetVisualFromFBConfig!\n");
	//( Display *dpy, GLXFBConfig config )
	//returns XVisualInfo *
}


//1626
static void EXEC_glXCreateWindow(char *commandbuf)
{
	LOG("Called unimplemted stub glXCreateWindow!\n");
	//( Display *dpy, GLXFBConfig config, Window win, const int *attribList )
	//returns  GLXWindow
}


//1627
static void EXEC_glXDestroyWindow(char *commandbuf)
{
	LOG("Called unimplemted stub glXDestroyWindow!\n");
	//( Display *dpy, GLXWindow window )
}


//1628
static void EXEC_glXCreatePixmap(char *commandbuf)
{
	LOG("Called unimplemted stub glXCreatePixmap!\n");
	//( Display *dpy, GLXFBConfig config, Pixmap pixmap, const int *attribList )
	//returns GLXPixmap
}


//1629
static void EXEC_glXDestroyPixmap(char *commandbuf)
{
	LOG("Called unimplemted stub glXDestroyPixmap!\n");
	//( Display *dpy, GLXPixmap pixmap )
}


//1630
static void EXEC_glXCreatePbuffer(char *commandbuf)
{
	LOG("Called unimplemted stub glXCreatePbuffer!\n");
	//( Display *dpy, GLXFBConfig config, const int *attribList )
	//returns GLXPbuffer
}


//1631
static void EXEC_glXDestroyPbuffer(char *commandbuf)
{
	LOG("Called unimplemted stub glXDestroyPbuffer!\n");
	//( Display *dpy, GLXPbuffer pbuf )
}


//1632
static void EXEC_glXQueryDrawable(char *commandbuf)
{
	LOG("Called unimplemted stub glXQueryDrawable!\n");
	//( Display *dpy, GLXDrawable draw, int attribute, unsigned int *value )
}


//1633
static void EXEC_glXCreateNewContext(char *commandbuf)
{
	LOG("Called unimplemted stub glXCreateNewContext!\n");
	//( Display *dpy, GLXFBConfig config, int renderType, GLXContext shareList, Bool direct )
	//returns GLXContext
}


//1634
static void EXEC_glXMakeContextCurrent(char *commandbuf)
{
	LOG("Called unimplemted stub glXMakeContextCurrent!\n");
	//( Display *dpy, GLXDrawable draw, GLXDrawable read, GLXContext ctx )
	//returns Bool
}


//1635
static void EXEC_glXGetCurrentReadDrawable(char *commandbuf)
{
	LOG("Called unimplemted stub glXGetCurrentReadDrawable!\n");
	//returns GLXDrawable
}


//1636
static void EXEC_glXQueryContext(char *commandbuf)
{
	LOG("Called unimplemted stub glXQueryContext!\n");
	//( Display *dpy, GLXContext ctx, int attribute, int *value )
	//returns int
}


//1637
static void EXEC_glXSelectEvent(char *commandbuf)
{
	LOG("Called unimplemted stub glXSelectEvent!\n");
	//( Display *dpy, GLXDrawable drawable, unsigned long mask )
}


//1638
static void EXEC_glXGetSelectedEvent(char *commandbuf)
{
	LOG("Called unimplemted stub glXGetSelectedEvent!\n");
	//( Display *dpy, GLXDrawable drawable, unsigned long *mask )
}


//1639
static void EXEC_glXGetProcAddressARB(char *commandbuf)
{
	LOG("Called unimplemted stub glXGetProcAddressARB!\n");
	//(const GLubyte *)
	//returns __GLXextFuncPtr
}


//1640
static void EXEC_glXGetProcAddress(char *commandbuf)
{
	LOG("Called unimplemted stub glXGetProcAddress!\n");
	//(const GLubyte *procname)
}


//1641
static void EXEC_glXAllocateMemoryNV(char *commandbuf)
{
	LOG("Called unimplemted stub glXAllocateMemoryNV!\n");
	//(GLsizei size, GLfloat readfreq, GLfloat writefreq, GLfloat priority)
}


//1642
static void EXEC_glXFreeMemoryNV(char *commandbuf)
{
	LOG("Called unimplemted stub glXFreeMemoryNV!\n");
	//(GLvoid *pointer)
}


//1643
static void EXEC_glXAllocateMemoryMESA(char *commandbuf)
{
	LOG("Called unimplemted stub glXAllocateMemoryMESA!\n");
	//(Display *dpy, int scrn, size_t size, float readfreq, float writefreq, float priority)
}


//1644
static void EXEC_glXFreeMemoryMESA(char *commandbuf)
{
	LOG("Called unimplemted stub glXFreeMemoryMESA!\n");
	//(Display *dpy, int scrn, void *pointer)
}


//1645
static void EXEC_glXGetMemoryOffsetMESA(char *commandbuf)
{
	LOG("Called unimplemted stub glXGetMemoryOffsetMESA!\n");
	//(Display *dpy, int scrn, const void *pointer)
	//returns GLuint
}


//1646
static void EXEC_glXBindTexImageARB(char *commandbuf)
{
	LOG("Called unimplemted stub glXBindTexImageARB!\n");
	//(Display *dpy, GLXPbuffer pbuffer, int buffer)
	//returns Bool
}


//1647
static void EXEC_glXReleaseTexImageARB(char *commandbuf)
{
	LOG("Called unimplemted stub glXReleaseTexImageARB!\n");
	//(Display *dpy, GLXPbuffer pbuffer, int buffer)
	//returns Bool
}


//1648
static void EXEC_glXDrawableAttribARB(char *commandbuf)
{
	LOG("Called unimplemted stub glXDrawableAttribARB!\n");
	//(Display *dpy, GLXDrawable draw, const int *attribList)
	//returns Bool
}


//1649
static void EXEC_glXGetFrameUsageMESA(char *commandbuf)
{
	LOG("Called unimplemted stub glXGetFrameUsageMESA!\n");
	//(Display *dpy, GLXDrawable drawable, float *usage)
	//returns int
}


//1650
static void EXEC_glXBeginFrameTrackingMESA(char *commandbuf)
{
	LOG("Called unimplemted stub glXBeginFrameTrackingMESA!\n");
	//(Display *dpy, GLXDrawable drawable)
	//returns int
}


//1651
static void EXEC_glXEndFrameTrackingMESA(char *commandbuf)
{
	LOG("Called unimplemted stub glXEndFrameTrackingMESA!\n");
	//(Display *dpy, GLXDrawable drawable)
	//returns int
}


//1652
static void EXEC_glXQueryFrameTrackingMESA(char *commandbuf)
{
	LOG("Called unimplemted stub glXQueryFrameTrackingMESA!\n");
	//(Display *dpy, GLXDrawable drawable, int64_t *swapCount, int64_t *missedFrames, float *lastMissedUsage)
	//returns int
}


//1653
static void EXEC_glXSwapIntervalMESA(char *commandbuf)
{
	LOG("Called unimplemted stub glXSwapIntervalMESA!\n");
	//(unsigned int interval)
	//returns int
}


//1654
static void EXEC_glXGetSwapIntervalMESA(char *commandbuf)
{
	LOG("Called unimplemted stub glXGetSwapIntervalMESA!\n");
	//returns int
}


//1655
static void EXEC_glXBindTexImageEXT(char *commandbuf)
{
	LOG("Called unimplemted stub glXBindTexImageEXT!\n");
	//(Display *dpy, GLXDrawable drawable, int buffer, const int *attrib_list)
}


//1656
static void EXEC_glXReleaseTexImageEXT(char *commandbuf)
{
	LOG("Called unimplemted stub glXReleaseTexImageEXT!\n");
	//(Display *dpy, GLXDrawable drawable, int buffer)
}


/*********************************************************
	Method Pointers
*********************************************************/

void init_functions() {
	for(int i=0;i<1700;i++) {
		_dgl_functions[i] = nullptr;
	}

	//GL functions
	_dgl_functions[0] = EXEC_glNewList;
	_dgl_functions[1] = EXEC_glEndList;
	_dgl_functions[2] = EXEC_glCallList;
	_dgl_functions[3] = EXEC_glCallLists;
	_dgl_functions[4] = EXEC_glDeleteLists;
	_dgl_functions[5] = EXEC_glGenLists;
	_dgl_functions[6] = EXEC_glListBase;
	_dgl_functions[7] = EXEC_glBegin;
	_dgl_functions[8] = EXEC_glBitmap;
	_dgl_functions[9] = EXEC_glColor3b;
	_dgl_functions[10] = EXEC_glColor3bv;
	_dgl_functions[11] = EXEC_glColor3d;
	_dgl_functions[12] = EXEC_glColor3dv;
	_dgl_functions[13] = EXEC_glColor3f;
	_dgl_functions[14] = EXEC_glColor3fv;
	_dgl_functions[15] = EXEC_glColor3i;
	_dgl_functions[16] = EXEC_glColor3iv;
	_dgl_functions[17] = EXEC_glColor3s;
	_dgl_functions[18] = EXEC_glColor3sv;
	_dgl_functions[19] = EXEC_glColor3ub;
	_dgl_functions[20] = EXEC_glColor3ubv;
	_dgl_functions[21] = EXEC_glColor3ui;
	_dgl_functions[22] = EXEC_glColor3uiv;
	_dgl_functions[23] = EXEC_glColor3us;
	_dgl_functions[24] = EXEC_glColor3usv;
	_dgl_functions[25] = EXEC_glColor4b;
	_dgl_functions[26] = EXEC_glColor4bv;
	_dgl_functions[27] = EXEC_glColor4d;
	_dgl_functions[28] = EXEC_glColor4dv;
	_dgl_functions[29] = EXEC_glColor4f;
	_dgl_functions[30] = EXEC_glColor4fv;
	_dgl_functions[31] = EXEC_glColor4i;
	_dgl_functions[32] = EXEC_glColor4iv;
	_dgl_functions[33] = EXEC_glColor4s;
	_dgl_functions[34] = EXEC_glColor4sv;
	_dgl_functions[35] = EXEC_glColor4ub;
	_dgl_functions[36] = EXEC_glColor4ubv;
	_dgl_functions[37] = EXEC_glColor4ui;
	_dgl_functions[38] = EXEC_glColor4uiv;
	_dgl_functions[39] = EXEC_glColor4us;
	_dgl_functions[40] = EXEC_glColor4usv;
	_dgl_functions[41] = EXEC_glEdgeFlag;
	_dgl_functions[42] = EXEC_glEdgeFlagv;
	_dgl_functions[43] = EXEC_glEnd;
	_dgl_functions[44] = EXEC_glIndexd;
	_dgl_functions[45] = EXEC_glIndexdv;
	_dgl_functions[46] = EXEC_glIndexf;
	_dgl_functions[47] = EXEC_glIndexfv;
	_dgl_functions[48] = EXEC_glIndexi;
	_dgl_functions[49] = EXEC_glIndexiv;
	_dgl_functions[50] = EXEC_glIndexs;
	_dgl_functions[51] = EXEC_glIndexsv;
	_dgl_functions[52] = EXEC_glNormal3b;
	_dgl_functions[53] = EXEC_glNormal3bv;
	_dgl_functions[54] = EXEC_glNormal3d;
	_dgl_functions[55] = EXEC_glNormal3dv;
	_dgl_functions[56] = EXEC_glNormal3f;
	_dgl_functions[57] = EXEC_glNormal3fv;
	_dgl_functions[58] = EXEC_glNormal3i;
	_dgl_functions[59] = EXEC_glNormal3iv;
	_dgl_functions[60] = EXEC_glNormal3s;
	_dgl_functions[61] = EXEC_glNormal3sv;
	_dgl_functions[62] = EXEC_glRasterPos2d;
	_dgl_functions[63] = EXEC_glRasterPos2dv;
	_dgl_functions[64] = EXEC_glRasterPos2f;
	_dgl_functions[65] = EXEC_glRasterPos2fv;
	_dgl_functions[66] = EXEC_glRasterPos2i;
	_dgl_functions[67] = EXEC_glRasterPos2iv;
	_dgl_functions[68] = EXEC_glRasterPos2s;
	_dgl_functions[69] = EXEC_glRasterPos2sv;
	_dgl_functions[70] = EXEC_glRasterPos3d;
	_dgl_functions[71] = EXEC_glRasterPos3dv;
	_dgl_functions[72] = EXEC_glRasterPos3f;
	_dgl_functions[73] = EXEC_glRasterPos3fv;
	_dgl_functions[74] = EXEC_glRasterPos3i;
	_dgl_functions[75] = EXEC_glRasterPos3iv;
	_dgl_functions[76] = EXEC_glRasterPos3s;
	_dgl_functions[77] = EXEC_glRasterPos3sv;
	_dgl_functions[78] = EXEC_glRasterPos4d;
	_dgl_functions[79] = EXEC_glRasterPos4dv;
	_dgl_functions[80] = EXEC_glRasterPos4f;
	_dgl_functions[81] = EXEC_glRasterPos4fv;
	_dgl_functions[82] = EXEC_glRasterPos4i;
	_dgl_functions[83] = EXEC_glRasterPos4iv;
	_dgl_functions[84] = EXEC_glRasterPos4s;
	_dgl_functions[85] = EXEC_glRasterPos4sv;
	_dgl_functions[86] = EXEC_glRectd;
	_dgl_functions[87] = EXEC_glRectdv;
	_dgl_functions[88] = EXEC_glRectf;
	_dgl_functions[89] = EXEC_glRectfv;
	_dgl_functions[90] = EXEC_glRecti;
	_dgl_functions[91] = EXEC_glRectiv;
	_dgl_functions[92] = EXEC_glRects;
	_dgl_functions[93] = EXEC_glRectsv;
	_dgl_functions[94] = EXEC_glTexCoord1d;
	_dgl_functions[95] = EXEC_glTexCoord1dv;
	_dgl_functions[96] = EXEC_glTexCoord1f;
	_dgl_functions[97] = EXEC_glTexCoord1fv;
	_dgl_functions[98] = EXEC_glTexCoord1i;
	_dgl_functions[99] = EXEC_glTexCoord1iv;
	_dgl_functions[100] = EXEC_glTexCoord1s;
	_dgl_functions[101] = EXEC_glTexCoord1sv;
	_dgl_functions[102] = EXEC_glTexCoord2d;
	_dgl_functions[103] = EXEC_glTexCoord2dv;
	_dgl_functions[104] = EXEC_glTexCoord2f;
	_dgl_functions[105] = EXEC_glTexCoord2fv;
	_dgl_functions[106] = EXEC_glTexCoord2i;
	_dgl_functions[107] = EXEC_glTexCoord2iv;
	_dgl_functions[108] = EXEC_glTexCoord2s;
	_dgl_functions[109] = EXEC_glTexCoord2sv;
	_dgl_functions[110] = EXEC_glTexCoord3d;
	_dgl_functions[111] = EXEC_glTexCoord3dv;
	_dgl_functions[112] = EXEC_glTexCoord3f;
	_dgl_functions[113] = EXEC_glTexCoord3fv;
	_dgl_functions[114] = EXEC_glTexCoord3i;
	_dgl_functions[115] = EXEC_glTexCoord3iv;
	_dgl_functions[116] = EXEC_glTexCoord3s;
	_dgl_functions[117] = EXEC_glTexCoord3sv;
	_dgl_functions[118] = EXEC_glTexCoord4d;
	_dgl_functions[119] = EXEC_glTexCoord4dv;
	_dgl_functions[120] = EXEC_glTexCoord4f;
	_dgl_functions[121] = EXEC_glTexCoord4fv;
	_dgl_functions[122] = EXEC_glTexCoord4i;
	_dgl_functions[123] = EXEC_glTexCoord4iv;
	_dgl_functions[124] = EXEC_glTexCoord4s;
	_dgl_functions[125] = EXEC_glTexCoord4sv;
	_dgl_functions[126] = EXEC_glVertex2d;
	_dgl_functions[127] = EXEC_glVertex2dv;
	_dgl_functions[128] = EXEC_glVertex2f;
	_dgl_functions[129] = EXEC_glVertex2fv;
	_dgl_functions[130] = EXEC_glVertex2i;
	_dgl_functions[131] = EXEC_glVertex2iv;
	_dgl_functions[132] = EXEC_glVertex2s;
	_dgl_functions[133] = EXEC_glVertex2sv;
	_dgl_functions[134] = EXEC_glVertex3d;
	_dgl_functions[135] = EXEC_glVertex3dv;
	_dgl_functions[136] = EXEC_glVertex3f;
	_dgl_functions[137] = EXEC_glVertex3fv;
	_dgl_functions[138] = EXEC_glVertex3i;
	_dgl_functions[139] = EXEC_glVertex3iv;
	_dgl_functions[140] = EXEC_glVertex3s;
	_dgl_functions[141] = EXEC_glVertex3sv;
	_dgl_functions[142] = EXEC_glVertex4d;
	_dgl_functions[143] = EXEC_glVertex4dv;
	_dgl_functions[144] = EXEC_glVertex4f;
	_dgl_functions[145] = EXEC_glVertex4fv;
	_dgl_functions[146] = EXEC_glVertex4i;
	_dgl_functions[147] = EXEC_glVertex4iv;
	_dgl_functions[148] = EXEC_glVertex4s;
	_dgl_functions[149] = EXEC_glVertex4sv;
	_dgl_functions[150] = EXEC_glClipPlane;
	_dgl_functions[151] = EXEC_glColorMaterial;
	_dgl_functions[152] = EXEC_glCullFace;
	_dgl_functions[153] = EXEC_glFogf;
	_dgl_functions[154] = EXEC_glFogfv;
	_dgl_functions[155] = EXEC_glFogi;
	_dgl_functions[156] = EXEC_glFogiv;
	_dgl_functions[157] = EXEC_glFrontFace;
	_dgl_functions[158] = EXEC_glHint;
	_dgl_functions[159] = EXEC_glLightf;
	_dgl_functions[160] = EXEC_glLightfv;
	_dgl_functions[161] = EXEC_glLighti;
	_dgl_functions[162] = EXEC_glLightiv;
	_dgl_functions[163] = EXEC_glLightModelf;
	_dgl_functions[164] = EXEC_glLightModelfv;
	_dgl_functions[165] = EXEC_glLightModeli;
	_dgl_functions[166] = EXEC_glLightModeliv;
	_dgl_functions[167] = EXEC_glLineStipple;
	_dgl_functions[168] = EXEC_glLineWidth;
	_dgl_functions[169] = EXEC_glMaterialf;
	_dgl_functions[170] = EXEC_glMaterialfv;
	_dgl_functions[171] = EXEC_glMateriali;
	_dgl_functions[172] = EXEC_glMaterialiv;
	_dgl_functions[173] = EXEC_glPointSize;
	_dgl_functions[174] = EXEC_glPolygonMode;
	_dgl_functions[175] = EXEC_glPolygonStipple;
	_dgl_functions[176] = EXEC_glScissor;
	_dgl_functions[177] = EXEC_glShadeModel;
	_dgl_functions[178] = EXEC_glTexParameterf;
	_dgl_functions[179] = EXEC_glTexParameterfv;
	_dgl_functions[180] = EXEC_glTexParameteri;
	_dgl_functions[181] = EXEC_glTexParameteriv;
	_dgl_functions[182] = EXEC_glTexImage1D;
	_dgl_functions[183] = EXEC_glTexImage2D;
	_dgl_functions[184] = EXEC_glTexEnvf;
	_dgl_functions[185] = EXEC_glTexEnvfv;
	_dgl_functions[186] = EXEC_glTexEnvi;
	_dgl_functions[187] = EXEC_glTexEnviv;
	_dgl_functions[188] = EXEC_glTexGend;
	_dgl_functions[189] = EXEC_glTexGendv;
	_dgl_functions[190] = EXEC_glTexGenf;
	_dgl_functions[191] = EXEC_glTexGenfv;
	_dgl_functions[192] = EXEC_glTexGeni;
	_dgl_functions[193] = EXEC_glTexGeniv;
	_dgl_functions[194] = EXEC_glFeedbackBuffer;
	_dgl_functions[195] = EXEC_glSelectBuffer;
	_dgl_functions[196] = EXEC_glRenderMode;
	_dgl_functions[197] = EXEC_glInitNames;
	_dgl_functions[198] = EXEC_glLoadName;
	_dgl_functions[199] = EXEC_glPassThrough;
	_dgl_functions[200] = EXEC_glPopName;
	_dgl_functions[201] = EXEC_glPushName;
	_dgl_functions[202] = EXEC_glDrawBuffer;
	_dgl_functions[203] = EXEC_glClear;
	_dgl_functions[204] = EXEC_glClearAccum;
	_dgl_functions[205] = EXEC_glClearIndex;
	_dgl_functions[206] = EXEC_glClearColor;
	_dgl_functions[207] = EXEC_glClearStencil;
	_dgl_functions[208] = EXEC_glClearDepth;
	_dgl_functions[209] = EXEC_glStencilMask;
	_dgl_functions[210] = EXEC_glColorMask;
	_dgl_functions[211] = EXEC_glDepthMask;
	_dgl_functions[212] = EXEC_glIndexMask;
	_dgl_functions[213] = EXEC_glAccum;
	_dgl_functions[214] = EXEC_glDisable;
	_dgl_functions[215] = EXEC_glEnable;
	_dgl_functions[216] = EXEC_glFinish;
	_dgl_functions[217] = EXEC_glFlush;
	_dgl_functions[218] = EXEC_glPopAttrib;
	_dgl_functions[219] = EXEC_glPushAttrib;
	_dgl_functions[220] = EXEC_glMap1d;
	_dgl_functions[221] = EXEC_glMap1f;
	_dgl_functions[222] = EXEC_glMap2d;
	_dgl_functions[223] = EXEC_glMap2f;
	_dgl_functions[224] = EXEC_glMapGrid1d;
	_dgl_functions[225] = EXEC_glMapGrid1f;
	_dgl_functions[226] = EXEC_glMapGrid2d;
	_dgl_functions[227] = EXEC_glMapGrid2f;
	_dgl_functions[228] = EXEC_glEvalCoord1d;
	_dgl_functions[229] = EXEC_glEvalCoord1dv;
	_dgl_functions[230] = EXEC_glEvalCoord1f;
	_dgl_functions[231] = EXEC_glEvalCoord1fv;
	_dgl_functions[232] = EXEC_glEvalCoord2d;
	_dgl_functions[233] = EXEC_glEvalCoord2dv;
	_dgl_functions[234] = EXEC_glEvalCoord2f;
	_dgl_functions[235] = EXEC_glEvalCoord2fv;
	_dgl_functions[236] = EXEC_glEvalMesh1;
	_dgl_functions[237] = EXEC_glEvalPoint1;
	_dgl_functions[238] = EXEC_glEvalMesh2;
	_dgl_functions[239] = EXEC_glEvalPoint2;
	_dgl_functions[240] = EXEC_glAlphaFunc;
	_dgl_functions[241] = EXEC_glBlendFunc;
	_dgl_functions[242] = EXEC_glLogicOp;
	_dgl_functions[243] = EXEC_glStencilFunc;
	_dgl_functions[244] = EXEC_glStencilOp;
	_dgl_functions[245] = EXEC_glDepthFunc;
	_dgl_functions[246] = EXEC_glPixelZoom;
	_dgl_functions[247] = EXEC_glPixelTransferf;
	_dgl_functions[248] = EXEC_glPixelTransferi;
	_dgl_functions[249] = EXEC_glPixelStoref;
	_dgl_functions[250] = EXEC_glPixelStorei;
	_dgl_functions[251] = EXEC_glPixelMapfv;
	_dgl_functions[252] = EXEC_glPixelMapuiv;
	_dgl_functions[253] = EXEC_glPixelMapusv;
	_dgl_functions[254] = EXEC_glReadBuffer;
	_dgl_functions[255] = EXEC_glCopyPixels;
	_dgl_functions[256] = EXEC_glReadPixels;
	_dgl_functions[257] = EXEC_glDrawPixels;
	_dgl_functions[258] = EXEC_glGetBooleanv;
	_dgl_functions[259] = EXEC_glGetClipPlane;
	_dgl_functions[260] = EXEC_glGetDoublev;
	_dgl_functions[261] = EXEC_glGetError;
	_dgl_functions[262] = EXEC_glGetFloatv;
	_dgl_functions[263] = EXEC_glGetIntegerv;
	_dgl_functions[264] = EXEC_glGetLightfv;
	_dgl_functions[265] = EXEC_glGetLightiv;
	_dgl_functions[266] = EXEC_glGetMapdv;
	_dgl_functions[267] = EXEC_glGetMapfv;
	_dgl_functions[268] = EXEC_glGetMapiv;
	_dgl_functions[269] = EXEC_glGetMaterialfv;
	_dgl_functions[270] = EXEC_glGetMaterialiv;
	_dgl_functions[271] = EXEC_glGetPixelMapfv;
	_dgl_functions[272] = EXEC_glGetPixelMapuiv;
	_dgl_functions[273] = EXEC_glGetPixelMapusv;
	_dgl_functions[274] = EXEC_glGetPolygonStipple;
	_dgl_functions[275] = EXEC_glGetString;
	_dgl_functions[276] = EXEC_glGetTexEnvfv;
	_dgl_functions[277] = EXEC_glGetTexEnviv;
	_dgl_functions[278] = EXEC_glGetTexGendv;
	_dgl_functions[279] = EXEC_glGetTexGenfv;
	_dgl_functions[280] = EXEC_glGetTexGeniv;
	_dgl_functions[281] = EXEC_glGetTexImage;
	_dgl_functions[282] = EXEC_glGetTexParameterfv;
	_dgl_functions[283] = EXEC_glGetTexParameteriv;
	_dgl_functions[284] = EXEC_glGetTexLevelParameterfv;
	_dgl_functions[285] = EXEC_glGetTexLevelParameteriv;
	_dgl_functions[286] = EXEC_glIsEnabled;
	_dgl_functions[287] = EXEC_glIsList;
	_dgl_functions[288] = EXEC_glDepthRange;
	_dgl_functions[289] = EXEC_glFrustum;
	_dgl_functions[290] = EXEC_glLoadIdentity;
	_dgl_functions[291] = EXEC_glLoadMatrixf;
	_dgl_functions[292] = EXEC_glLoadMatrixd;
	_dgl_functions[293] = EXEC_glMatrixMode;
	_dgl_functions[294] = EXEC_glMultMatrixf;
	_dgl_functions[295] = EXEC_glMultMatrixd;
	_dgl_functions[296] = EXEC_glOrtho;
	_dgl_functions[297] = EXEC_glPopMatrix;
	_dgl_functions[298] = EXEC_glPushMatrix;
	_dgl_functions[299] = EXEC_glRotated;
	_dgl_functions[300] = EXEC_glRotatef;
	_dgl_functions[301] = EXEC_glScaled;
	_dgl_functions[302] = EXEC_glScalef;
	_dgl_functions[303] = EXEC_glTranslated;
	_dgl_functions[304] = EXEC_glTranslatef;
	_dgl_functions[305] = EXEC_glViewport;
	_dgl_functions[306] = EXEC_glArrayElement;
	_dgl_functions[308] = EXEC_glColorPointer;
	_dgl_functions[309] = EXEC_glDisableClientState;
	_dgl_functions[310] = EXEC_glDrawArrays;
	_dgl_functions[311] = EXEC_glDrawElements;
	_dgl_functions[312] = EXEC_glEdgeFlagPointer;
	_dgl_functions[313] = EXEC_glEnableClientState;
	_dgl_functions[329] = EXEC_glGetPointerv;
	_dgl_functions[314] = EXEC_glIndexPointer;
	_dgl_functions[317] = EXEC_glInterleavedArrays;
	_dgl_functions[318] = EXEC_glNormalPointer;
	_dgl_functions[320] = EXEC_glTexCoordPointer;
	_dgl_functions[321] = EXEC_glVertexPointer;
	_dgl_functions[319] = EXEC_glPolygonOffset;
	_dgl_functions[323] = EXEC_glCopyTexImage1D;
	_dgl_functions[324] = EXEC_glCopyTexImage2D;
	_dgl_functions[325] = EXEC_glCopyTexSubImage1D;
	_dgl_functions[326] = EXEC_glCopyTexSubImage2D;
	_dgl_functions[332] = EXEC_glTexSubImage1D;
	_dgl_functions[333] = EXEC_glTexSubImage2D;
	_dgl_functions[322] = EXEC_glAreTexturesResident;
	_dgl_functions[307] = EXEC_glBindTexture;
	_dgl_functions[327] = EXEC_glDeleteTextures;
	_dgl_functions[328] = EXEC_glGenTextures;
	_dgl_functions[330] = EXEC_glIsTexture;
	_dgl_functions[331] = EXEC_glPrioritizeTextures;
	_dgl_functions[315] = EXEC_glIndexub;
	_dgl_functions[316] = EXEC_glIndexubv;
	_dgl_functions[334] = EXEC_glPopClientAttrib;
	_dgl_functions[335] = EXEC_glPushClientAttrib;
	_dgl_functions[336] = EXEC_glBlendColor;
	_dgl_functions[337] = EXEC_glBlendEquation;
	_dgl_functions[338] = EXEC_glDrawRangeElements;
	_dgl_functions[339] = EXEC_glColorTable;
	_dgl_functions[340] = EXEC_glColorTableParameterfv;
	_dgl_functions[341] = EXEC_glColorTableParameteriv;
	_dgl_functions[342] = EXEC_glCopyColorTable;
	_dgl_functions[343] = EXEC_glGetColorTable;
	_dgl_functions[344] = EXEC_glGetColorTableParameterfv;
	_dgl_functions[345] = EXEC_glGetColorTableParameteriv;
	_dgl_functions[346] = EXEC_glColorSubTable;
	_dgl_functions[347] = EXEC_glCopyColorSubTable;
	_dgl_functions[348] = EXEC_glConvolutionFilter1D;
	_dgl_functions[349] = EXEC_glConvolutionFilter2D;
	_dgl_functions[350] = EXEC_glConvolutionParameterf;
	_dgl_functions[351] = EXEC_glConvolutionParameterfv;
	_dgl_functions[352] = EXEC_glConvolutionParameteri;
	_dgl_functions[353] = EXEC_glConvolutionParameteriv;
	_dgl_functions[354] = EXEC_glCopyConvolutionFilter1D;
	_dgl_functions[355] = EXEC_glCopyConvolutionFilter2D;
	_dgl_functions[356] = EXEC_glGetConvolutionFilter;
	_dgl_functions[357] = EXEC_glGetConvolutionParameterfv;
	_dgl_functions[358] = EXEC_glGetConvolutionParameteriv;
	_dgl_functions[359] = EXEC_glGetSeparableFilter;
	_dgl_functions[360] = EXEC_glSeparableFilter2D;
	_dgl_functions[361] = EXEC_glGetHistogram;
	_dgl_functions[362] = EXEC_glGetHistogramParameterfv;
	_dgl_functions[363] = EXEC_glGetHistogramParameteriv;
	_dgl_functions[364] = EXEC_glGetMinmax;
	_dgl_functions[365] = EXEC_glGetMinmaxParameterfv;
	_dgl_functions[366] = EXEC_glGetMinmaxParameteriv;
	_dgl_functions[367] = EXEC_glHistogram;
	_dgl_functions[368] = EXEC_glMinmax;
	_dgl_functions[369] = EXEC_glResetHistogram;
	_dgl_functions[370] = EXEC_glResetMinmax;
	_dgl_functions[371] = EXEC_glTexImage3D;
	_dgl_functions[372] = EXEC_glTexSubImage3D;
	_dgl_functions[373] = EXEC_glCopyTexSubImage3D;
	_dgl_functions[374] = EXEC_glActiveTexture;
	_dgl_functions[375] = EXEC_glClientActiveTexture;
	_dgl_functions[376] = EXEC_glMultiTexCoord1d;
	_dgl_functions[377] = EXEC_glMultiTexCoord1dv;
	_dgl_functions[378] = EXEC_glMultiTexCoord1f;
	_dgl_functions[379] = EXEC_glMultiTexCoord1fv;
	_dgl_functions[380] = EXEC_glMultiTexCoord1i;
	_dgl_functions[381] = EXEC_glMultiTexCoord1iv;
	_dgl_functions[382] = EXEC_glMultiTexCoord1s;
	_dgl_functions[383] = EXEC_glMultiTexCoord1sv;
	_dgl_functions[384] = EXEC_glMultiTexCoord2d;
	_dgl_functions[385] = EXEC_glMultiTexCoord2dv;
	_dgl_functions[386] = EXEC_glMultiTexCoord2f;
	_dgl_functions[387] = EXEC_glMultiTexCoord2fv;
	_dgl_functions[388] = EXEC_glMultiTexCoord2i;
	_dgl_functions[389] = EXEC_glMultiTexCoord2iv;
	_dgl_functions[390] = EXEC_glMultiTexCoord2s;
	_dgl_functions[391] = EXEC_glMultiTexCoord2sv;
	_dgl_functions[392] = EXEC_glMultiTexCoord3d;
	_dgl_functions[393] = EXEC_glMultiTexCoord3dv;
	_dgl_functions[394] = EXEC_glMultiTexCoord3f;
	_dgl_functions[395] = EXEC_glMultiTexCoord3fv;
	_dgl_functions[396] = EXEC_glMultiTexCoord3i;
	_dgl_functions[397] = EXEC_glMultiTexCoord3iv;
	_dgl_functions[398] = EXEC_glMultiTexCoord3s;
	_dgl_functions[399] = EXEC_glMultiTexCoord3sv;
	_dgl_functions[400] = EXEC_glMultiTexCoord4d;
	_dgl_functions[401] = EXEC_glMultiTexCoord4dv;
	_dgl_functions[402] = EXEC_glMultiTexCoord4f;
	_dgl_functions[403] = EXEC_glMultiTexCoord4fv;
	_dgl_functions[404] = EXEC_glMultiTexCoord4i;
	_dgl_functions[405] = EXEC_glMultiTexCoord4iv;
	_dgl_functions[406] = EXEC_glMultiTexCoord4s;
	_dgl_functions[407] = EXEC_glMultiTexCoord4sv;
	_dgl_functions[408] = EXEC_glLoadTransposeMatrixf;
	_dgl_functions[409] = EXEC_glLoadTransposeMatrixd;
	_dgl_functions[410] = EXEC_glMultTransposeMatrixf;
	_dgl_functions[411] = EXEC_glMultTransposeMatrixd;
	_dgl_functions[412] = EXEC_glSampleCoverage;
	_dgl_functions[413] = EXEC_glCompressedTexImage3D;
	_dgl_functions[414] = EXEC_glCompressedTexImage2D;
	_dgl_functions[415] = EXEC_glCompressedTexImage1D;
	_dgl_functions[416] = EXEC_glCompressedTexSubImage3D;
	_dgl_functions[417] = EXEC_glCompressedTexSubImage2D;
	_dgl_functions[418] = EXEC_glCompressedTexSubImage1D;
	_dgl_functions[419] = EXEC_glGetCompressedTexImage;
	_dgl_functions[420] = EXEC_glBlendFuncSeparate;
	_dgl_functions[421] = EXEC_glFogCoordf;
	_dgl_functions[422] = EXEC_glFogCoordfv;
	_dgl_functions[423] = EXEC_glFogCoordd;
	_dgl_functions[424] = EXEC_glFogCoorddv;
	_dgl_functions[425] = EXEC_glFogCoordPointer;
	_dgl_functions[426] = EXEC_glMultiDrawArrays;
	_dgl_functions[427] = EXEC_glMultiDrawElements;
	_dgl_functions[428] = EXEC_glPointParameterf;
	_dgl_functions[429] = EXEC_glPointParameterfv;
	_dgl_functions[430] = EXEC_glPointParameteri;
	_dgl_functions[431] = EXEC_glPointParameteriv;
	_dgl_functions[432] = EXEC_glSecondaryColor3b;
	_dgl_functions[433] = EXEC_glSecondaryColor3bv;
	_dgl_functions[434] = EXEC_glSecondaryColor3d;
	_dgl_functions[435] = EXEC_glSecondaryColor3dv;
	_dgl_functions[436] = EXEC_glSecondaryColor3f;
	_dgl_functions[437] = EXEC_glSecondaryColor3fv;
	_dgl_functions[438] = EXEC_glSecondaryColor3i;
	_dgl_functions[439] = EXEC_glSecondaryColor3iv;
	_dgl_functions[440] = EXEC_glSecondaryColor3s;
	_dgl_functions[441] = EXEC_glSecondaryColor3sv;
	_dgl_functions[442] = EXEC_glSecondaryColor3ub;
	_dgl_functions[443] = EXEC_glSecondaryColor3ubv;
	_dgl_functions[444] = EXEC_glSecondaryColor3ui;
	_dgl_functions[445] = EXEC_glSecondaryColor3uiv;
	_dgl_functions[446] = EXEC_glSecondaryColor3us;
	_dgl_functions[447] = EXEC_glSecondaryColor3usv;
	_dgl_functions[448] = EXEC_glSecondaryColorPointer;
	_dgl_functions[449] = EXEC_glWindowPos2d;
	_dgl_functions[450] = EXEC_glWindowPos2dv;
	_dgl_functions[451] = EXEC_glWindowPos2f;
	_dgl_functions[452] = EXEC_glWindowPos2fv;
	_dgl_functions[453] = EXEC_glWindowPos2i;
	_dgl_functions[454] = EXEC_glWindowPos2iv;
	_dgl_functions[455] = EXEC_glWindowPos2s;
	_dgl_functions[456] = EXEC_glWindowPos2sv;
	_dgl_functions[457] = EXEC_glWindowPos3d;
	_dgl_functions[458] = EXEC_glWindowPos3dv;
	_dgl_functions[459] = EXEC_glWindowPos3f;
	_dgl_functions[460] = EXEC_glWindowPos3fv;
	_dgl_functions[461] = EXEC_glWindowPos3i;
	_dgl_functions[462] = EXEC_glWindowPos3iv;
	_dgl_functions[463] = EXEC_glWindowPos3s;
	_dgl_functions[464] = EXEC_glWindowPos3sv;
	_dgl_functions[465] = EXEC_glBindBuffer;
	_dgl_functions[466] = EXEC_glBufferData;
	_dgl_functions[467] = EXEC_glBufferSubData;
	_dgl_functions[468] = EXEC_glDeleteBuffers;
	_dgl_functions[469] = EXEC_glGenBuffers;
	_dgl_functions[470] = EXEC_glGetBufferParameteriv;
	_dgl_functions[471] = EXEC_glGetBufferPointerv;
	_dgl_functions[472] = EXEC_glGetBufferSubData;
	_dgl_functions[473] = EXEC_glIsBuffer;
	_dgl_functions[474] = EXEC_glMapBuffer;
	_dgl_functions[475] = EXEC_glUnmapBuffer;
	_dgl_functions[476] = EXEC_glGenQueries;
	_dgl_functions[477] = EXEC_glDeleteQueries;
	_dgl_functions[478] = EXEC_glIsQuery;
	_dgl_functions[479] = EXEC_glBeginQuery;
	_dgl_functions[480] = EXEC_glEndQuery;
	_dgl_functions[481] = EXEC_glGetQueryiv;
	_dgl_functions[482] = EXEC_glGetQueryObjectiv;
	_dgl_functions[483] = EXEC_glGetQueryObjectuiv;
	_dgl_functions[484] = EXEC_glBlendEquationSeparate;
	_dgl_functions[485] = EXEC_glDrawBuffers;
	_dgl_functions[486] = EXEC_glStencilFuncSeparate;
	_dgl_functions[487] = EXEC_glStencilOpSeparate;
	_dgl_functions[488] = EXEC_glStencilMaskSeparate;
	_dgl_functions[489] = EXEC_glAttachShader;
	_dgl_functions[490] = EXEC_glBindAttribLocation;
	_dgl_functions[491] = EXEC_glCompileShader;
	_dgl_functions[492] = EXEC_glCreateProgram;
	_dgl_functions[493] = EXEC_glCreateShader;
	_dgl_functions[494] = EXEC_glDeleteProgram;
	_dgl_functions[495] = EXEC_glDeleteShader;
	_dgl_functions[496] = EXEC_glDetachShader;
	_dgl_functions[497] = EXEC_glDisableVertexAttribArray;
	_dgl_functions[498] = EXEC_glEnableVertexAttribArray;
	_dgl_functions[499] = EXEC_glGetActiveAttrib;
	_dgl_functions[500] = EXEC_glGetActiveUniform;
	_dgl_functions[501] = EXEC_glGetAttachedShaders;
	_dgl_functions[502] = EXEC_glGetAttribLocation;
	_dgl_functions[503] = EXEC_glGetProgramiv;
	_dgl_functions[504] = EXEC_glGetProgramInfoLog;
	_dgl_functions[505] = EXEC_glGetShaderiv;
	_dgl_functions[506] = EXEC_glGetShaderInfoLog;
	_dgl_functions[507] = EXEC_glGetShaderSource;
	_dgl_functions[508] = EXEC_glGetUniformLocation;
	_dgl_functions[509] = EXEC_glGetUniformfv;
	_dgl_functions[510] = EXEC_glGetUniformiv;
	_dgl_functions[511] = EXEC_glGetVertexAttribdv;
	_dgl_functions[512] = EXEC_glGetVertexAttribfv;
	_dgl_functions[513] = EXEC_glGetVertexAttribiv;
	_dgl_functions[514] = EXEC_glGetVertexAttribPointerv;
	_dgl_functions[515] = EXEC_glIsProgram;
	_dgl_functions[516] = EXEC_glIsShader;
	_dgl_functions[517] = EXEC_glLinkProgram;
	_dgl_functions[518] = EXEC_glShaderSource;
	_dgl_functions[519] = EXEC_glUseProgram;
	_dgl_functions[520] = EXEC_glUniform1f;
	_dgl_functions[521] = EXEC_glUniform2f;
	_dgl_functions[522] = EXEC_glUniform3f;
	_dgl_functions[523] = EXEC_glUniform4f;
	_dgl_functions[524] = EXEC_glUniform1i;
	_dgl_functions[525] = EXEC_glUniform2i;
	_dgl_functions[526] = EXEC_glUniform3i;
	_dgl_functions[527] = EXEC_glUniform4i;
	_dgl_functions[528] = EXEC_glUniform1fv;
	_dgl_functions[529] = EXEC_glUniform2fv;
	_dgl_functions[530] = EXEC_glUniform3fv;
	_dgl_functions[531] = EXEC_glUniform4fv;
	_dgl_functions[532] = EXEC_glUniform1iv;
	_dgl_functions[533] = EXEC_glUniform2iv;
	_dgl_functions[534] = EXEC_glUniform3iv;
	_dgl_functions[535] = EXEC_glUniform4iv;
	_dgl_functions[536] = EXEC_glUniformMatrix2fv;
	_dgl_functions[537] = EXEC_glUniformMatrix3fv;
	_dgl_functions[538] = EXEC_glUniformMatrix4fv;
	_dgl_functions[539] = EXEC_glValidateProgram;
	_dgl_functions[540] = EXEC_glVertexAttrib1d;
	_dgl_functions[541] = EXEC_glVertexAttrib1dv;
	_dgl_functions[542] = EXEC_glVertexAttrib1f;
	_dgl_functions[543] = EXEC_glVertexAttrib1fv;
	_dgl_functions[544] = EXEC_glVertexAttrib1s;
	_dgl_functions[545] = EXEC_glVertexAttrib1sv;
	_dgl_functions[546] = EXEC_glVertexAttrib2d;
	_dgl_functions[547] = EXEC_glVertexAttrib2dv;
	_dgl_functions[548] = EXEC_glVertexAttrib2f;
	_dgl_functions[549] = EXEC_glVertexAttrib2fv;
	_dgl_functions[550] = EXEC_glVertexAttrib2s;
	_dgl_functions[551] = EXEC_glVertexAttrib2sv;
	_dgl_functions[552] = EXEC_glVertexAttrib3d;
	_dgl_functions[553] = EXEC_glVertexAttrib3dv;
	_dgl_functions[554] = EXEC_glVertexAttrib3f;
	_dgl_functions[555] = EXEC_glVertexAttrib3fv;
	_dgl_functions[556] = EXEC_glVertexAttrib3s;
	_dgl_functions[557] = EXEC_glVertexAttrib3sv;
	_dgl_functions[558] = EXEC_glVertexAttrib4Nbv;
	_dgl_functions[559] = EXEC_glVertexAttrib4Niv;
	_dgl_functions[560] = EXEC_glVertexAttrib4Nsv;
	_dgl_functions[561] = EXEC_glVertexAttrib4Nub;
	_dgl_functions[562] = EXEC_glVertexAttrib4Nubv;
	_dgl_functions[563] = EXEC_glVertexAttrib4Nuiv;
	_dgl_functions[564] = EXEC_glVertexAttrib4Nusv;
	_dgl_functions[565] = EXEC_glVertexAttrib4bv;
	_dgl_functions[566] = EXEC_glVertexAttrib4d;
	_dgl_functions[567] = EXEC_glVertexAttrib4dv;
	_dgl_functions[568] = EXEC_glVertexAttrib4f;
	_dgl_functions[569] = EXEC_glVertexAttrib4fv;
	_dgl_functions[570] = EXEC_glVertexAttrib4iv;
	_dgl_functions[571] = EXEC_glVertexAttrib4s;
	_dgl_functions[572] = EXEC_glVertexAttrib4sv;
	_dgl_functions[573] = EXEC_glVertexAttrib4ubv;
	_dgl_functions[574] = EXEC_glVertexAttrib4uiv;
	_dgl_functions[575] = EXEC_glVertexAttrib4usv;
	_dgl_functions[576] = EXEC_glVertexAttribPointer;
	_dgl_functions[577] = EXEC_glUniformMatrix2x3fv;
	_dgl_functions[578] = EXEC_glUniformMatrix3x2fv;
	_dgl_functions[579] = EXEC_glUniformMatrix2x4fv;
	_dgl_functions[580] = EXEC_glUniformMatrix4x2fv;
	_dgl_functions[581] = EXEC_glUniformMatrix3x4fv;
	_dgl_functions[582] = EXEC_glUniformMatrix4x3fv;
	_dgl_functions[374] = EXEC_glActiveTextureARB;
	_dgl_functions[375] = EXEC_glClientActiveTextureARB;
	_dgl_functions[376] = EXEC_glMultiTexCoord1dARB;
	_dgl_functions[377] = EXEC_glMultiTexCoord1dvARB;
	_dgl_functions[378] = EXEC_glMultiTexCoord1fARB;
	_dgl_functions[379] = EXEC_glMultiTexCoord1fvARB;
	_dgl_functions[380] = EXEC_glMultiTexCoord1iARB;
	_dgl_functions[381] = EXEC_glMultiTexCoord1ivARB;
	_dgl_functions[382] = EXEC_glMultiTexCoord1sARB;
	_dgl_functions[383] = EXEC_glMultiTexCoord1svARB;
	_dgl_functions[384] = EXEC_glMultiTexCoord2dARB;
	_dgl_functions[385] = EXEC_glMultiTexCoord2dvARB;
	_dgl_functions[386] = EXEC_glMultiTexCoord2fARB;
	_dgl_functions[387] = EXEC_glMultiTexCoord2fvARB;
	_dgl_functions[388] = EXEC_glMultiTexCoord2iARB;
	_dgl_functions[389] = EXEC_glMultiTexCoord2ivARB;
	_dgl_functions[390] = EXEC_glMultiTexCoord2sARB;
	_dgl_functions[391] = EXEC_glMultiTexCoord2svARB;
	_dgl_functions[392] = EXEC_glMultiTexCoord3dARB;
	_dgl_functions[393] = EXEC_glMultiTexCoord3dvARB;
	_dgl_functions[394] = EXEC_glMultiTexCoord3fARB;
	_dgl_functions[395] = EXEC_glMultiTexCoord3fvARB;
	_dgl_functions[396] = EXEC_glMultiTexCoord3iARB;
	_dgl_functions[397] = EXEC_glMultiTexCoord3ivARB;
	_dgl_functions[398] = EXEC_glMultiTexCoord3sARB;
	_dgl_functions[399] = EXEC_glMultiTexCoord3svARB;
	_dgl_functions[400] = EXEC_glMultiTexCoord4dARB;
	_dgl_functions[401] = EXEC_glMultiTexCoord4dvARB;
	_dgl_functions[402] = EXEC_glMultiTexCoord4fARB;
	_dgl_functions[403] = EXEC_glMultiTexCoord4fvARB;
	_dgl_functions[404] = EXEC_glMultiTexCoord4iARB;
	_dgl_functions[405] = EXEC_glMultiTexCoord4ivARB;
	_dgl_functions[406] = EXEC_glMultiTexCoord4sARB;
	_dgl_functions[407] = EXEC_glMultiTexCoord4svARB;
	_dgl_functions[617] = EXEC_glLoadTransposeMatrixfARB;
	_dgl_functions[618] = EXEC_glLoadTransposeMatrixdARB;
	_dgl_functions[619] = EXEC_glMultTransposeMatrixfARB;
	_dgl_functions[620] = EXEC_glMultTransposeMatrixdARB;
	_dgl_functions[621] = EXEC_glSampleCoverageARB;
	_dgl_functions[622] = EXEC_glCompressedTexImage3DARB;
	_dgl_functions[623] = EXEC_glCompressedTexImage2DARB;
	_dgl_functions[624] = EXEC_glCompressedTexImage1DARB;
	_dgl_functions[625] = EXEC_glCompressedTexSubImage3DARB;
	_dgl_functions[626] = EXEC_glCompressedTexSubImage2DARB;
	_dgl_functions[627] = EXEC_glCompressedTexSubImage1DARB;
	_dgl_functions[628] = EXEC_glGetCompressedTexImageARB;
	_dgl_functions[629] = EXEC_glPointParameterfARB;
	_dgl_functions[630] = EXEC_glPointParameterfvARB;
	_dgl_functions[631] = EXEC_glWeightbvARB;
	_dgl_functions[632] = EXEC_glWeightsvARB;
	_dgl_functions[633] = EXEC_glWeightivARB;
	_dgl_functions[634] = EXEC_glWeightfvARB;
	_dgl_functions[635] = EXEC_glWeightdvARB;
	_dgl_functions[636] = EXEC_glWeightubvARB;
	_dgl_functions[637] = EXEC_glWeightusvARB;
	_dgl_functions[638] = EXEC_glWeightuivARB;
	_dgl_functions[639] = EXEC_glWeightPointerARB;
	_dgl_functions[640] = EXEC_glVertexBlendARB;
	_dgl_functions[641] = EXEC_glCurrentPaletteMatrixARB;
	_dgl_functions[642] = EXEC_glMatrixIndexubvARB;
	_dgl_functions[643] = EXEC_glMatrixIndexusvARB;
	_dgl_functions[644] = EXEC_glMatrixIndexuivARB;
	_dgl_functions[645] = EXEC_glMatrixIndexPointerARB;
	_dgl_functions[646] = EXEC_glWindowPos2dARB;
	_dgl_functions[647] = EXEC_glWindowPos2fARB;
	_dgl_functions[648] = EXEC_glWindowPos2iARB;
	_dgl_functions[649] = EXEC_glWindowPos2sARB;
	_dgl_functions[650] = EXEC_glWindowPos2dvARB;
	_dgl_functions[651] = EXEC_glWindowPos2fvARB;
	_dgl_functions[652] = EXEC_glWindowPos2ivARB;
	_dgl_functions[653] = EXEC_glWindowPos2svARB;
	_dgl_functions[654] = EXEC_glWindowPos3dARB;
	_dgl_functions[655] = EXEC_glWindowPos3fARB;
	_dgl_functions[656] = EXEC_glWindowPos3iARB;
	_dgl_functions[657] = EXEC_glWindowPos3sARB;
	_dgl_functions[658] = EXEC_glWindowPos3dvARB;
	_dgl_functions[659] = EXEC_glWindowPos3fvARB;
	_dgl_functions[660] = EXEC_glWindowPos3ivARB;
	_dgl_functions[661] = EXEC_glWindowPos3svARB;
	_dgl_functions[662] = EXEC_glGetVertexAttribdvARB;
	_dgl_functions[663] = EXEC_glGetVertexAttribfvARB;
	_dgl_functions[664] = EXEC_glGetVertexAttribivARB;
	_dgl_functions[665] = EXEC_glVertexAttrib1dARB;
	_dgl_functions[666] = EXEC_glVertexAttrib1dvARB;
	_dgl_functions[667] = EXEC_glVertexAttrib1fARB;
	_dgl_functions[668] = EXEC_glVertexAttrib1fvARB;
	_dgl_functions[669] = EXEC_glVertexAttrib1sARB;
	_dgl_functions[670] = EXEC_glVertexAttrib1svARB;
	_dgl_functions[671] = EXEC_glVertexAttrib2dARB;
	_dgl_functions[672] = EXEC_glVertexAttrib2dvARB;
	_dgl_functions[673] = EXEC_glVertexAttrib2fARB;
	_dgl_functions[674] = EXEC_glVertexAttrib2fvARB;
	_dgl_functions[675] = EXEC_glVertexAttrib2sARB;
	_dgl_functions[676] = EXEC_glVertexAttrib2svARB;
	_dgl_functions[677] = EXEC_glVertexAttrib3dARB;
	_dgl_functions[678] = EXEC_glVertexAttrib3dvARB;
	_dgl_functions[679] = EXEC_glVertexAttrib3fARB;
	_dgl_functions[680] = EXEC_glVertexAttrib3fvARB;
	_dgl_functions[681] = EXEC_glVertexAttrib3sARB;
	_dgl_functions[682] = EXEC_glVertexAttrib3svARB;
	_dgl_functions[683] = EXEC_glVertexAttrib4dARB;
	_dgl_functions[684] = EXEC_glVertexAttrib4dvARB;
	_dgl_functions[685] = EXEC_glVertexAttrib4fARB;
	_dgl_functions[686] = EXEC_glVertexAttrib4fvARB;
	_dgl_functions[687] = EXEC_glVertexAttrib4sARB;
	_dgl_functions[688] = EXEC_glVertexAttrib4svARB;
	_dgl_functions[689] = EXEC_glVertexAttrib4NubARB;
	_dgl_functions[690] = EXEC_glVertexAttrib4NubvARB;
	_dgl_functions[691] = EXEC_glVertexAttrib4bvARB;
	_dgl_functions[692] = EXEC_glVertexAttrib4ivARB;
	_dgl_functions[693] = EXEC_glVertexAttrib4ubvARB;
	_dgl_functions[694] = EXEC_glVertexAttrib4usvARB;
	_dgl_functions[695] = EXEC_glVertexAttrib4uivARB;
	_dgl_functions[696] = EXEC_glVertexAttrib4NbvARB;
	_dgl_functions[697] = EXEC_glVertexAttrib4NsvARB;
	_dgl_functions[698] = EXEC_glVertexAttrib4NivARB;
	_dgl_functions[699] = EXEC_glVertexAttrib4NusvARB;
	_dgl_functions[700] = EXEC_glVertexAttrib4NuivARB;
	_dgl_functions[701] = EXEC_glVertexAttribPointerARB;
	_dgl_functions[702] = EXEC_glEnableVertexAttribArrayARB;
	_dgl_functions[703] = EXEC_glDisableVertexAttribArrayARB;
	_dgl_functions[704] = EXEC_glProgramStringARB;
	_dgl_functions[705] = EXEC_glBindProgramARB;
	_dgl_functions[706] = EXEC_glDeleteProgramsARB;
	_dgl_functions[707] = EXEC_glGenProgramsARB;
	_dgl_functions[708] = EXEC_glIsProgramARB;
	_dgl_functions[709] = EXEC_glProgramEnvParameter4dARB;
	_dgl_functions[710] = EXEC_glProgramEnvParameter4dvARB;
	_dgl_functions[711] = EXEC_glProgramEnvParameter4fARB;
	_dgl_functions[712] = EXEC_glProgramEnvParameter4fvARB;
	_dgl_functions[713] = EXEC_glProgramLocalParameter4dARB;
	_dgl_functions[714] = EXEC_glProgramLocalParameter4dvARB;
	_dgl_functions[715] = EXEC_glProgramLocalParameter4fARB;
	_dgl_functions[716] = EXEC_glProgramLocalParameter4fvARB;
	_dgl_functions[717] = EXEC_glGetProgramEnvParameterdvARB;
	_dgl_functions[718] = EXEC_glGetProgramEnvParameterfvARB;
	_dgl_functions[719] = EXEC_glGetProgramLocalParameterdvARB;
	_dgl_functions[720] = EXEC_glGetProgramLocalParameterfvARB;
	_dgl_functions[721] = EXEC_glGetProgramivARB;
	_dgl_functions[722] = EXEC_glGetProgramStringARB;
	_dgl_functions[723] = EXEC_glGetVertexAttribPointervARB;
	_dgl_functions[724] = EXEC_glBindBufferARB;
	_dgl_functions[725] = EXEC_glBufferDataARB;
	_dgl_functions[726] = EXEC_glBufferSubDataARB;
	_dgl_functions[727] = EXEC_glDeleteBuffersARB;
	_dgl_functions[728] = EXEC_glGenBuffersARB;
	_dgl_functions[729] = EXEC_glGetBufferParameterivARB;
	_dgl_functions[730] = EXEC_glGetBufferPointervARB;
	_dgl_functions[731] = EXEC_glGetBufferSubDataARB;
	_dgl_functions[732] = EXEC_glIsBufferARB;
	_dgl_functions[733] = EXEC_glMapBufferARB;
	_dgl_functions[734] = EXEC_glUnmapBufferARB;
	_dgl_functions[735] = EXEC_glGenQueriesARB;
	_dgl_functions[736] = EXEC_glDeleteQueriesARB;
	_dgl_functions[737] = EXEC_glIsQueryARB;
	_dgl_functions[738] = EXEC_glBeginQueryARB;
	_dgl_functions[739] = EXEC_glEndQueryARB;
	_dgl_functions[740] = EXEC_glGetQueryivARB;
	_dgl_functions[741] = EXEC_glGetQueryObjectivARB;
	_dgl_functions[742] = EXEC_glGetQueryObjectuivARB;
	_dgl_functions[743] = EXEC_glDeleteObjectARB;
	_dgl_functions[744] = EXEC_glGetHandleARB;
	_dgl_functions[745] = EXEC_glDetachObjectARB;
	_dgl_functions[746] = EXEC_glCreateShaderObjectARB;
	_dgl_functions[747] = EXEC_glShaderSourceARB;
	_dgl_functions[748] = EXEC_glCompileShaderARB;
	_dgl_functions[749] = EXEC_glCreateProgramObjectARB;
	_dgl_functions[750] = EXEC_glAttachObjectARB;
	_dgl_functions[751] = EXEC_glLinkProgramARB;
	_dgl_functions[752] = EXEC_glUseProgramObjectARB;
	_dgl_functions[753] = EXEC_glValidateProgramARB;
	_dgl_functions[754] = EXEC_glUniform1fARB;
	_dgl_functions[755] = EXEC_glUniform2fARB;
	_dgl_functions[756] = EXEC_glUniform3fARB;
	_dgl_functions[757] = EXEC_glUniform4fARB;
	_dgl_functions[758] = EXEC_glUniform1iARB;
	_dgl_functions[759] = EXEC_glUniform2iARB;
	_dgl_functions[760] = EXEC_glUniform3iARB;
	_dgl_functions[761] = EXEC_glUniform4iARB;
	_dgl_functions[762] = EXEC_glUniform1fvARB;
	_dgl_functions[763] = EXEC_glUniform2fvARB;
	_dgl_functions[764] = EXEC_glUniform3fvARB;
	_dgl_functions[765] = EXEC_glUniform4fvARB;
	_dgl_functions[766] = EXEC_glUniform1ivARB;
	_dgl_functions[767] = EXEC_glUniform2ivARB;
	_dgl_functions[768] = EXEC_glUniform3ivARB;
	_dgl_functions[769] = EXEC_glUniform4ivARB;
	_dgl_functions[770] = EXEC_glUniformMatrix2fvARB;
	_dgl_functions[771] = EXEC_glUniformMatrix3fvARB;
	_dgl_functions[772] = EXEC_glUniformMatrix4fvARB;
	_dgl_functions[773] = EXEC_glGetObjectParameterfvARB;
	_dgl_functions[774] = EXEC_glGetObjectParameterivARB;
	_dgl_functions[775] = EXEC_glGetInfoLogARB;
	_dgl_functions[776] = EXEC_glGetAttachedObjectsARB;
	_dgl_functions[777] = EXEC_glGetUniformLocationARB;
	_dgl_functions[778] = EXEC_glGetActiveUniformARB;
	_dgl_functions[779] = EXEC_glGetUniformfvARB;
	_dgl_functions[780] = EXEC_glGetUniformivARB;
	_dgl_functions[781] = EXEC_glGetShaderSourceARB;
	_dgl_functions[782] = EXEC_glBindAttribLocationARB;
	_dgl_functions[783] = EXEC_glGetActiveAttribARB;
	_dgl_functions[784] = EXEC_glGetAttribLocationARB;
	_dgl_functions[785] = EXEC_glDrawBuffersARB;
	_dgl_functions[786] = EXEC_glBlendColorEXT;
	_dgl_functions[787] = EXEC_glPolygonOffsetEXT;
	_dgl_functions[788] = EXEC_glTexImage3DEXT;
	_dgl_functions[789] = EXEC_glTexSubImage3DEXT;
	_dgl_functions[790] = EXEC_glGetTexFilterFuncSGIS;
	_dgl_functions[791] = EXEC_glTexFilterFuncSGIS;
	_dgl_functions[792] = EXEC_glTexSubImage1DEXT;
	_dgl_functions[793] = EXEC_glTexSubImage2DEXT;
	_dgl_functions[794] = EXEC_glCopyTexImage1DEXT;
	_dgl_functions[795] = EXEC_glCopyTexImage2DEXT;
	_dgl_functions[796] = EXEC_glCopyTexSubImage1DEXT;
	_dgl_functions[797] = EXEC_glCopyTexSubImage2DEXT;
	_dgl_functions[798] = EXEC_glCopyTexSubImage3DEXT;
	_dgl_functions[799] = EXEC_glGetHistogramEXT;
	_dgl_functions[800] = EXEC_glGetHistogramParameterfvEXT;
	_dgl_functions[801] = EXEC_glGetHistogramParameterivEXT;
	_dgl_functions[802] = EXEC_glGetMinmaxEXT;
	_dgl_functions[803] = EXEC_glGetMinmaxParameterfvEXT;
	_dgl_functions[804] = EXEC_glGetMinmaxParameterivEXT;
	_dgl_functions[805] = EXEC_glHistogramEXT;
	_dgl_functions[806] = EXEC_glMinmaxEXT;
	_dgl_functions[807] = EXEC_glResetHistogramEXT;
	_dgl_functions[808] = EXEC_glResetMinmaxEXT;
	_dgl_functions[809] = EXEC_glConvolutionFilter1DEXT;
	_dgl_functions[810] = EXEC_glConvolutionFilter2DEXT;
	_dgl_functions[811] = EXEC_glConvolutionParameterfEXT;
	_dgl_functions[812] = EXEC_glConvolutionParameterfvEXT;
	_dgl_functions[813] = EXEC_glConvolutionParameteriEXT;
	_dgl_functions[814] = EXEC_glConvolutionParameterivEXT;
	_dgl_functions[815] = EXEC_glCopyConvolutionFilter1DEXT;
	_dgl_functions[816] = EXEC_glCopyConvolutionFilter2DEXT;
	_dgl_functions[817] = EXEC_glGetConvolutionFilterEXT;
	_dgl_functions[818] = EXEC_glGetConvolutionParameterfvEXT;
	_dgl_functions[819] = EXEC_glGetConvolutionParameterivEXT;
	_dgl_functions[820] = EXEC_glGetSeparableFilterEXT;
	_dgl_functions[821] = EXEC_glSeparableFilter2DEXT;
	_dgl_functions[822] = EXEC_glColorTableSGI;
	_dgl_functions[823] = EXEC_glColorTableParameterfvSGI;
	_dgl_functions[824] = EXEC_glColorTableParameterivSGI;
	_dgl_functions[825] = EXEC_glCopyColorTableSGI;
	_dgl_functions[826] = EXEC_glGetColorTableSGI;
	_dgl_functions[827] = EXEC_glGetColorTableParameterfvSGI;
	_dgl_functions[828] = EXEC_glGetColorTableParameterivSGI;
	_dgl_functions[829] = EXEC_glPixelTexGenParameteriSGIS;
	_dgl_functions[830] = EXEC_glPixelTexGenParameterivSGIS;
	_dgl_functions[831] = EXEC_glPixelTexGenParameterfSGIS;
	_dgl_functions[832] = EXEC_glPixelTexGenParameterfvSGIS;
	_dgl_functions[833] = EXEC_glGetPixelTexGenParameterivSGIS;
	_dgl_functions[834] = EXEC_glGetPixelTexGenParameterfvSGIS;
	_dgl_functions[835] = EXEC_glTexImage4DSGIS;
	_dgl_functions[836] = EXEC_glTexSubImage4DSGIS;
	_dgl_functions[837] = EXEC_glAreTexturesResidentEXT;
	_dgl_functions[838] = EXEC_glBindTextureEXT;
	_dgl_functions[839] = EXEC_glDeleteTexturesEXT;
	_dgl_functions[840] = EXEC_glGenTexturesEXT;
	_dgl_functions[841] = EXEC_glIsTextureEXT;
	_dgl_functions[842] = EXEC_glPrioritizeTexturesEXT;
	_dgl_functions[843] = EXEC_glDetailTexFuncSGIS;
	_dgl_functions[844] = EXEC_glGetDetailTexFuncSGIS;
	_dgl_functions[845] = EXEC_glSharpenTexFuncSGIS;
	_dgl_functions[846] = EXEC_glGetSharpenTexFuncSGIS;
	_dgl_functions[847] = EXEC_glSampleMaskSGIS;
	_dgl_functions[848] = EXEC_glSamplePatternSGIS;
	_dgl_functions[849] = EXEC_glArrayElementEXT;
	_dgl_functions[850] = EXEC_glColorPointerEXT;
	_dgl_functions[851] = EXEC_glDrawArraysEXT;
	_dgl_functions[852] = EXEC_glEdgeFlagPointerEXT;
	_dgl_functions[853] = EXEC_glGetPointervEXT;
	_dgl_functions[854] = EXEC_glIndexPointerEXT;
	_dgl_functions[855] = EXEC_glNormalPointerEXT;
	_dgl_functions[856] = EXEC_glTexCoordPointerEXT;
	_dgl_functions[857] = EXEC_glVertexPointerEXT;
	_dgl_functions[858] = EXEC_glBlendEquationEXT;
	_dgl_functions[859] = EXEC_glSpriteParameterfSGIX;
	_dgl_functions[860] = EXEC_glSpriteParameterfvSGIX;
	_dgl_functions[861] = EXEC_glSpriteParameteriSGIX;
	_dgl_functions[862] = EXEC_glSpriteParameterivSGIX;
	_dgl_functions[863] = EXEC_glPointParameterfEXT;
	_dgl_functions[864] = EXEC_glPointParameterfvEXT;
	_dgl_functions[865] = EXEC_glGetInstrumentsSGIX;
	_dgl_functions[866] = EXEC_glInstrumentsBufferSGIX;
	_dgl_functions[867] = EXEC_glPollInstrumentsSGIX;
	_dgl_functions[868] = EXEC_glReadInstrumentsSGIX;
	_dgl_functions[869] = EXEC_glStartInstrumentsSGIX;
	_dgl_functions[870] = EXEC_glStopInstrumentsSGIX;
	_dgl_functions[871] = EXEC_glFrameZoomSGIX;
	_dgl_functions[872] = EXEC_glTagSampleBufferSGIX;
	_dgl_functions[873] = EXEC_glReferencePlaneSGIX;
	_dgl_functions[874] = EXEC_glFlushRasterSGIX;
	_dgl_functions[875] = EXEC_glFogFuncSGIS;
	_dgl_functions[876] = EXEC_glGetFogFuncSGIS;
	_dgl_functions[877] = EXEC_glImageTransformParameteriHP;
	_dgl_functions[878] = EXEC_glImageTransformParameterfHP;
	_dgl_functions[879] = EXEC_glImageTransformParameterivHP;
	_dgl_functions[880] = EXEC_glImageTransformParameterfvHP;
	_dgl_functions[881] = EXEC_glGetImageTransformParameterivHP;
	_dgl_functions[882] = EXEC_glGetImageTransformParameterfvHP;
	_dgl_functions[883] = EXEC_glColorSubTableEXT;
	_dgl_functions[884] = EXEC_glCopyColorSubTableEXT;
	_dgl_functions[885] = EXEC_glHintPGI;
	_dgl_functions[886] = EXEC_glColorTableEXT;
	_dgl_functions[887] = EXEC_glGetColorTableEXT;
	_dgl_functions[888] = EXEC_glGetColorTableParameterivEXT;
	_dgl_functions[889] = EXEC_glGetColorTableParameterfvEXT;
	_dgl_functions[890] = EXEC_glGetListParameterfvSGIX;
	_dgl_functions[891] = EXEC_glGetListParameterivSGIX;
	_dgl_functions[892] = EXEC_glListParameterfSGIX;
	_dgl_functions[893] = EXEC_glListParameterfvSGIX;
	_dgl_functions[894] = EXEC_glListParameteriSGIX;
	_dgl_functions[895] = EXEC_glListParameterivSGIX;
	_dgl_functions[896] = EXEC_glIndexMaterialEXT;
	_dgl_functions[897] = EXEC_glIndexFuncEXT;
	_dgl_functions[898] = EXEC_glLockArraysEXT;
	_dgl_functions[899] = EXEC_glUnlockArraysEXT;
	_dgl_functions[900] = EXEC_glCullParameterdvEXT;
	_dgl_functions[901] = EXEC_glCullParameterfvEXT;
	_dgl_functions[902] = EXEC_glFragmentColorMaterialSGIX;
	_dgl_functions[903] = EXEC_glFragmentLightfSGIX;
	_dgl_functions[904] = EXEC_glFragmentLightfvSGIX;
	_dgl_functions[905] = EXEC_glFragmentLightiSGIX;
	_dgl_functions[906] = EXEC_glFragmentLightivSGIX;
	_dgl_functions[907] = EXEC_glFragmentLightModelfSGIX;
	_dgl_functions[908] = EXEC_glFragmentLightModelfvSGIX;
	_dgl_functions[909] = EXEC_glFragmentLightModeliSGIX;
	_dgl_functions[910] = EXEC_glFragmentLightModelivSGIX;
	_dgl_functions[911] = EXEC_glFragmentMaterialfSGIX;
	_dgl_functions[912] = EXEC_glFragmentMaterialfvSGIX;
	_dgl_functions[913] = EXEC_glFragmentMaterialiSGIX;
	_dgl_functions[914] = EXEC_glFragmentMaterialivSGIX;
	_dgl_functions[915] = EXEC_glGetFragmentLightfvSGIX;
	_dgl_functions[916] = EXEC_glGetFragmentLightivSGIX;
	_dgl_functions[917] = EXEC_glGetFragmentMaterialfvSGIX;
	_dgl_functions[918] = EXEC_glGetFragmentMaterialivSGIX;
	_dgl_functions[919] = EXEC_glLightEnviSGIX;
	_dgl_functions[920] = EXEC_glDrawRangeElementsEXT;
	_dgl_functions[921] = EXEC_glApplyTextureEXT;
	_dgl_functions[922] = EXEC_glTextureLightEXT;
	_dgl_functions[923] = EXEC_glTextureMaterialEXT;
	_dgl_functions[924] = EXEC_glAsyncMarkerSGIX;
	_dgl_functions[925] = EXEC_glFinishAsyncSGIX;
	_dgl_functions[926] = EXEC_glPollAsyncSGIX;
	_dgl_functions[927] = EXEC_glGenAsyncMarkersSGIX;
	_dgl_functions[928] = EXEC_glDeleteAsyncMarkersSGIX;
	_dgl_functions[929] = EXEC_glIsAsyncMarkerSGIX;
	_dgl_functions[930] = EXEC_glVertexPointervINTEL;
	_dgl_functions[931] = EXEC_glNormalPointervINTEL;
	_dgl_functions[932] = EXEC_glColorPointervINTEL;
	_dgl_functions[933] = EXEC_glTexCoordPointervINTEL;
	_dgl_functions[934] = EXEC_glPixelTransformParameteriEXT;
	_dgl_functions[935] = EXEC_glPixelTransformParameterfEXT;
	_dgl_functions[936] = EXEC_glPixelTransformParameterivEXT;
	_dgl_functions[937] = EXEC_glPixelTransformParameterfvEXT;
	_dgl_functions[938] = EXEC_glSecondaryColor3bEXT;
	_dgl_functions[939] = EXEC_glSecondaryColor3bvEXT;
	_dgl_functions[940] = EXEC_glSecondaryColor3dEXT;
	_dgl_functions[941] = EXEC_glSecondaryColor3dvEXT;
	_dgl_functions[942] = EXEC_glSecondaryColor3fEXT;
	_dgl_functions[943] = EXEC_glSecondaryColor3fvEXT;
	_dgl_functions[944] = EXEC_glSecondaryColor3iEXT;
	_dgl_functions[945] = EXEC_glSecondaryColor3ivEXT;
	_dgl_functions[946] = EXEC_glSecondaryColor3sEXT;
	_dgl_functions[947] = EXEC_glSecondaryColor3svEXT;
	_dgl_functions[948] = EXEC_glSecondaryColor3ubEXT;
	_dgl_functions[949] = EXEC_glSecondaryColor3ubvEXT;
	_dgl_functions[950] = EXEC_glSecondaryColor3uiEXT;
	_dgl_functions[951] = EXEC_glSecondaryColor3uivEXT;
	_dgl_functions[952] = EXEC_glSecondaryColor3usEXT;
	_dgl_functions[953] = EXEC_glSecondaryColor3usvEXT;
	_dgl_functions[954] = EXEC_glSecondaryColorPointerEXT;
	_dgl_functions[955] = EXEC_glTextureNormalEXT;
	_dgl_functions[956] = EXEC_glMultiDrawArraysEXT;
	_dgl_functions[957] = EXEC_glMultiDrawElementsEXT;
	_dgl_functions[958] = EXEC_glFogCoordfEXT;
	_dgl_functions[959] = EXEC_glFogCoordfvEXT;
	_dgl_functions[960] = EXEC_glFogCoorddEXT;
	_dgl_functions[961] = EXEC_glFogCoorddvEXT;
	_dgl_functions[962] = EXEC_glFogCoordPointerEXT;
	_dgl_functions[963] = EXEC_glTangent3bEXT;
	_dgl_functions[964] = EXEC_glTangent3bvEXT;
	_dgl_functions[965] = EXEC_glTangent3dEXT;
	_dgl_functions[966] = EXEC_glTangent3dvEXT;
	_dgl_functions[967] = EXEC_glTangent3fEXT;
	_dgl_functions[968] = EXEC_glTangent3fvEXT;
	_dgl_functions[969] = EXEC_glTangent3iEXT;
	_dgl_functions[970] = EXEC_glTangent3ivEXT;
	_dgl_functions[971] = EXEC_glTangent3sEXT;
	_dgl_functions[972] = EXEC_glTangent3svEXT;
	_dgl_functions[973] = EXEC_glBinormal3bEXT;
	_dgl_functions[974] = EXEC_glBinormal3bvEXT;
	_dgl_functions[975] = EXEC_glBinormal3dEXT;
	_dgl_functions[976] = EXEC_glBinormal3dvEXT;
	_dgl_functions[977] = EXEC_glBinormal3fEXT;
	_dgl_functions[978] = EXEC_glBinormal3fvEXT;
	_dgl_functions[979] = EXEC_glBinormal3iEXT;
	_dgl_functions[980] = EXEC_glBinormal3ivEXT;
	_dgl_functions[981] = EXEC_glBinormal3sEXT;
	_dgl_functions[982] = EXEC_glBinormal3svEXT;
	_dgl_functions[983] = EXEC_glTangentPointerEXT;
	_dgl_functions[984] = EXEC_glBinormalPointerEXT;
	_dgl_functions[985] = EXEC_glPixelTexGenSGIX;
	_dgl_functions[986] = EXEC_glFinishTextureSUNX;
	_dgl_functions[987] = EXEC_glGlobalAlphaFactorbSUN;
	_dgl_functions[988] = EXEC_glGlobalAlphaFactorsSUN;
	_dgl_functions[989] = EXEC_glGlobalAlphaFactoriSUN;
	_dgl_functions[990] = EXEC_glGlobalAlphaFactorfSUN;
	_dgl_functions[991] = EXEC_glGlobalAlphaFactordSUN;
	_dgl_functions[992] = EXEC_glGlobalAlphaFactorubSUN;
	_dgl_functions[993] = EXEC_glGlobalAlphaFactorusSUN;
	_dgl_functions[994] = EXEC_glGlobalAlphaFactoruiSUN;
	_dgl_functions[995] = EXEC_glReplacementCodeuiSUN;
	_dgl_functions[996] = EXEC_glReplacementCodeusSUN;
	_dgl_functions[997] = EXEC_glReplacementCodeubSUN;
	_dgl_functions[998] = EXEC_glReplacementCodeuivSUN;
	_dgl_functions[999] = EXEC_glReplacementCodeusvSUN;
	_dgl_functions[1000] = EXEC_glReplacementCodeubvSUN;
	_dgl_functions[1001] = EXEC_glReplacementCodePointerSUN;
	_dgl_functions[1002] = EXEC_glColor4ubVertex2fSUN;
	_dgl_functions[1003] = EXEC_glColor4ubVertex2fvSUN;
	_dgl_functions[1004] = EXEC_glColor4ubVertex3fSUN;
	_dgl_functions[1005] = EXEC_glColor4ubVertex3fvSUN;
	_dgl_functions[1006] = EXEC_glColor3fVertex3fSUN;
	_dgl_functions[1007] = EXEC_glColor3fVertex3fvSUN;
	_dgl_functions[1008] = EXEC_glNormal3fVertex3fSUN;
	_dgl_functions[1009] = EXEC_glNormal3fVertex3fvSUN;
	_dgl_functions[1010] = EXEC_glColor4fNormal3fVertex3fSUN;
	_dgl_functions[1011] = EXEC_glColor4fNormal3fVertex3fvSUN;
	_dgl_functions[1012] = EXEC_glTexCoord2fVertex3fSUN;
	_dgl_functions[1013] = EXEC_glTexCoord2fVertex3fvSUN;
	_dgl_functions[1014] = EXEC_glTexCoord4fVertex4fSUN;
	_dgl_functions[1015] = EXEC_glTexCoord4fVertex4fvSUN;
	_dgl_functions[1016] = EXEC_glTexCoord2fColor4ubVertex3fSUN;
	_dgl_functions[1017] = EXEC_glTexCoord2fColor4ubVertex3fvSUN;
	_dgl_functions[1018] = EXEC_glTexCoord2fColor3fVertex3fSUN;
	_dgl_functions[1019] = EXEC_glTexCoord2fColor3fVertex3fvSUN;
	_dgl_functions[1020] = EXEC_glTexCoord2fNormal3fVertex3fSUN;
	_dgl_functions[1021] = EXEC_glTexCoord2fNormal3fVertex3fvSUN;
	_dgl_functions[1022] = EXEC_glTexCoord2fColor4fNormal3fVertex3fSUN;
	_dgl_functions[1023] = EXEC_glTexCoord2fColor4fNormal3fVertex3fvSUN;
	_dgl_functions[1024] = EXEC_glTexCoord4fColor4fNormal3fVertex4fSUN;
	_dgl_functions[1025] = EXEC_glTexCoord4fColor4fNormal3fVertex4fvSUN;
	_dgl_functions[1026] = EXEC_glReplacementCodeuiVertex3fSUN;
	_dgl_functions[1027] = EXEC_glReplacementCodeuiVertex3fvSUN;
	_dgl_functions[1028] = EXEC_glReplacementCodeuiColor4ubVertex3fSUN;
	_dgl_functions[1029] = EXEC_glReplacementCodeuiColor4ubVertex3fvSUN;
	_dgl_functions[1030] = EXEC_glReplacementCodeuiColor3fVertex3fSUN;
	_dgl_functions[1031] = EXEC_glReplacementCodeuiColor3fVertex3fvSUN;
	_dgl_functions[1032] = EXEC_glReplacementCodeuiNormal3fVertex3fSUN;
	_dgl_functions[1033] = EXEC_glReplacementCodeuiNormal3fVertex3fvSUN;
	_dgl_functions[1034] = EXEC_glReplacementCodeuiColor4fNormal3fVertex3fSUN;
	_dgl_functions[1035] = EXEC_glReplacementCodeuiColor4fNormal3fVertex3fvSUN;
	_dgl_functions[1036] = EXEC_glReplacementCodeuiTexCoord2fVertex3fSUN;
	_dgl_functions[1037] = EXEC_glReplacementCodeuiTexCoord2fVertex3fvSUN;
	_dgl_functions[1038] = EXEC_glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN;
	_dgl_functions[1039] = EXEC_glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN;
	_dgl_functions[1040] = EXEC_glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN;
	_dgl_functions[1041] = EXEC_glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN;
	_dgl_functions[1042] = EXEC_glBlendFuncSeparateEXT;
	_dgl_functions[1043] = EXEC_glVertexWeightfEXT;
	_dgl_functions[1044] = EXEC_glVertexWeightfvEXT;
	_dgl_functions[1045] = EXEC_glVertexWeightPointerEXT;
	_dgl_functions[1046] = EXEC_glFlushVertexArrayRangeNV;
	_dgl_functions[1047] = EXEC_glVertexArrayRangeNV;
	_dgl_functions[1048] = EXEC_glCombinerParameterfvNV;
	_dgl_functions[1049] = EXEC_glCombinerParameterfNV;
	_dgl_functions[1050] = EXEC_glCombinerParameterivNV;
	_dgl_functions[1051] = EXEC_glCombinerParameteriNV;
	_dgl_functions[1052] = EXEC_glCombinerInputNV;
	_dgl_functions[1053] = EXEC_glCombinerOutputNV;
	_dgl_functions[1054] = EXEC_glFinalCombinerInputNV;
	_dgl_functions[1055] = EXEC_glGetCombinerInputParameterfvNV;
	_dgl_functions[1056] = EXEC_glGetCombinerInputParameterivNV;
	_dgl_functions[1057] = EXEC_glGetCombinerOutputParameterfvNV;
	_dgl_functions[1058] = EXEC_glGetCombinerOutputParameterivNV;
	_dgl_functions[1059] = EXEC_glGetFinalCombinerInputParameterfvNV;
	_dgl_functions[1060] = EXEC_glGetFinalCombinerInputParameterivNV;
	_dgl_functions[1061] = EXEC_glResizeBuffersMESA;
	_dgl_functions[1062] = EXEC_glWindowPos2dMESA;
	_dgl_functions[1063] = EXEC_glWindowPos2dvMESA;
	_dgl_functions[1064] = EXEC_glWindowPos2fMESA;
	_dgl_functions[1065] = EXEC_glWindowPos2fvMESA;
	_dgl_functions[1066] = EXEC_glWindowPos2iMESA;
	_dgl_functions[1067] = EXEC_glWindowPos2ivMESA;
	_dgl_functions[1068] = EXEC_glWindowPos2sMESA;
	_dgl_functions[1069] = EXEC_glWindowPos2svMESA;
	_dgl_functions[1070] = EXEC_glWindowPos3dMESA;
	_dgl_functions[1071] = EXEC_glWindowPos3dvMESA;
	_dgl_functions[1072] = EXEC_glWindowPos3fMESA;
	_dgl_functions[1073] = EXEC_glWindowPos3fvMESA;
	_dgl_functions[1074] = EXEC_glWindowPos3iMESA;
	_dgl_functions[1075] = EXEC_glWindowPos3ivMESA;
	_dgl_functions[1076] = EXEC_glWindowPos3sMESA;
	_dgl_functions[1077] = EXEC_glWindowPos3svMESA;
	_dgl_functions[1078] = EXEC_glWindowPos4dMESA;
	_dgl_functions[1079] = EXEC_glWindowPos4dvMESA;
	_dgl_functions[1080] = EXEC_glWindowPos4fMESA;
	_dgl_functions[1081] = EXEC_glWindowPos4fvMESA;
	_dgl_functions[1082] = EXEC_glWindowPos4iMESA;
	_dgl_functions[1083] = EXEC_glWindowPos4ivMESA;
	_dgl_functions[1084] = EXEC_glWindowPos4sMESA;
	_dgl_functions[1085] = EXEC_glWindowPos4svMESA;
	_dgl_functions[1086] = EXEC_glMultiModeDrawArraysIBM;
	_dgl_functions[1087] = EXEC_glMultiModeDrawElementsIBM;
	_dgl_functions[1088] = EXEC_glColorPointerListIBM;
	_dgl_functions[1089] = EXEC_glSecondaryColorPointerListIBM;
	_dgl_functions[1090] = EXEC_glEdgeFlagPointerListIBM;
	_dgl_functions[1091] = EXEC_glFogCoordPointerListIBM;
	_dgl_functions[1092] = EXEC_glIndexPointerListIBM;
	_dgl_functions[1093] = EXEC_glNormalPointerListIBM;
	_dgl_functions[1094] = EXEC_glTexCoordPointerListIBM;
	_dgl_functions[1095] = EXEC_glVertexPointerListIBM;
	_dgl_functions[1096] = EXEC_glTbufferMask3DFX;
	_dgl_functions[1097] = EXEC_glSampleMaskEXT;
	_dgl_functions[1098] = EXEC_glSamplePatternEXT;
	_dgl_functions[1099] = EXEC_glTextureColorMaskSGIS;
	_dgl_functions[1100] = EXEC_glDeleteFencesNV;
	_dgl_functions[1101] = EXEC_glGenFencesNV;
	_dgl_functions[1102] = EXEC_glIsFenceNV;
	_dgl_functions[1103] = EXEC_glTestFenceNV;
	_dgl_functions[1104] = EXEC_glGetFenceivNV;
	_dgl_functions[1105] = EXEC_glFinishFenceNV;
	_dgl_functions[1106] = EXEC_glSetFenceNV;
	_dgl_functions[1107] = EXEC_glMapControlPointsNV;
	_dgl_functions[1108] = EXEC_glMapParameterivNV;
	_dgl_functions[1109] = EXEC_glMapParameterfvNV;
	_dgl_functions[1110] = EXEC_glGetMapControlPointsNV;
	_dgl_functions[1111] = EXEC_glGetMapParameterivNV;
	_dgl_functions[1112] = EXEC_glGetMapParameterfvNV;
	_dgl_functions[1113] = EXEC_glGetMapAttribParameterivNV;
	_dgl_functions[1114] = EXEC_glGetMapAttribParameterfvNV;
	_dgl_functions[1115] = EXEC_glEvalMapsNV;
	_dgl_functions[1116] = EXEC_glCombinerStageParameterfvNV;
	_dgl_functions[1117] = EXEC_glGetCombinerStageParameterfvNV;
	_dgl_functions[1118] = EXEC_glAreProgramsResidentNV;
	_dgl_functions[1119] = EXEC_glBindProgramNV;
	_dgl_functions[1120] = EXEC_glDeleteProgramsNV;
	_dgl_functions[1121] = EXEC_glExecuteProgramNV;
	_dgl_functions[1122] = EXEC_glGenProgramsNV;
	_dgl_functions[1123] = EXEC_glGetProgramParameterdvNV;
	_dgl_functions[1124] = EXEC_glGetProgramParameterfvNV;
	_dgl_functions[1125] = EXEC_glGetProgramivNV;
	_dgl_functions[1126] = EXEC_glGetProgramStringNV;
	_dgl_functions[1127] = EXEC_glGetTrackMatrixivNV;
	_dgl_functions[1128] = EXEC_glGetVertexAttribdvNV;
	_dgl_functions[1129] = EXEC_glGetVertexAttribfvNV;
	_dgl_functions[1130] = EXEC_glGetVertexAttribivNV;
	_dgl_functions[1131] = EXEC_glGetVertexAttribPointervNV;
	_dgl_functions[1132] = EXEC_glIsProgramNV;
	_dgl_functions[1133] = EXEC_glLoadProgramNV;
	_dgl_functions[1134] = EXEC_glProgramParameter4dNV;
	_dgl_functions[1135] = EXEC_glProgramParameter4dvNV;
	_dgl_functions[1136] = EXEC_glProgramParameter4fNV;
	_dgl_functions[1137] = EXEC_glProgramParameter4fvNV;
	_dgl_functions[1138] = EXEC_glProgramParameters4dvNV;
	_dgl_functions[1139] = EXEC_glProgramParameters4fvNV;
	_dgl_functions[1140] = EXEC_glRequestResidentProgramsNV;
	_dgl_functions[1141] = EXEC_glTrackMatrixNV;
	_dgl_functions[1142] = EXEC_glVertexAttribPointerNV;
	_dgl_functions[1143] = EXEC_glVertexAttrib1sNV;
	_dgl_functions[1144] = EXEC_glVertexAttrib1svNV;
	_dgl_functions[1145] = EXEC_glVertexAttrib2sNV;
	_dgl_functions[1146] = EXEC_glVertexAttrib2svNV;
	_dgl_functions[1147] = EXEC_glVertexAttrib3sNV;
	_dgl_functions[1148] = EXEC_glVertexAttrib3svNV;
	_dgl_functions[1149] = EXEC_glVertexAttrib4sNV;
	_dgl_functions[1150] = EXEC_glVertexAttrib4svNV;
	_dgl_functions[1151] = EXEC_glVertexAttrib1fNV;
	_dgl_functions[1152] = EXEC_glVertexAttrib1fvNV;
	_dgl_functions[1153] = EXEC_glVertexAttrib2fNV;
	_dgl_functions[1154] = EXEC_glVertexAttrib2fvNV;
	_dgl_functions[1155] = EXEC_glVertexAttrib3fNV;
	_dgl_functions[1156] = EXEC_glVertexAttrib3fvNV;
	_dgl_functions[1157] = EXEC_glVertexAttrib4fNV;
	_dgl_functions[1158] = EXEC_glVertexAttrib4fvNV;
	_dgl_functions[1159] = EXEC_glVertexAttrib1dNV;
	_dgl_functions[1160] = EXEC_glVertexAttrib1dvNV;
	_dgl_functions[1161] = EXEC_glVertexAttrib2dNV;
	_dgl_functions[1162] = EXEC_glVertexAttrib2dvNV;
	_dgl_functions[1163] = EXEC_glVertexAttrib3dNV;
	_dgl_functions[1164] = EXEC_glVertexAttrib3dvNV;
	_dgl_functions[1165] = EXEC_glVertexAttrib4dNV;
	_dgl_functions[1166] = EXEC_glVertexAttrib4dvNV;
	_dgl_functions[1167] = EXEC_glVertexAttrib4ubNV;
	_dgl_functions[1168] = EXEC_glVertexAttrib4ubvNV;
	_dgl_functions[1169] = EXEC_glVertexAttribs1svNV;
	_dgl_functions[1170] = EXEC_glVertexAttribs2svNV;
	_dgl_functions[1171] = EXEC_glVertexAttribs3svNV;
	_dgl_functions[1172] = EXEC_glVertexAttribs4svNV;
	_dgl_functions[1173] = EXEC_glVertexAttribs1fvNV;
	_dgl_functions[1174] = EXEC_glVertexAttribs2fvNV;
	_dgl_functions[1175] = EXEC_glVertexAttribs3fvNV;
	_dgl_functions[1176] = EXEC_glVertexAttribs4fvNV;
	_dgl_functions[1177] = EXEC_glVertexAttribs1dvNV;
	_dgl_functions[1178] = EXEC_glVertexAttribs2dvNV;
	_dgl_functions[1179] = EXEC_glVertexAttribs3dvNV;
	_dgl_functions[1180] = EXEC_glVertexAttribs4dvNV;
	_dgl_functions[1181] = EXEC_glVertexAttribs4ubvNV;
	_dgl_functions[1182] = EXEC_glGenFragmentShadersATI;
	_dgl_functions[1183] = EXEC_glBindFragmentShaderATI;
	_dgl_functions[1184] = EXEC_glDeleteFragmentShaderATI;
	_dgl_functions[1185] = EXEC_glBeginFragmentShaderATI;
	_dgl_functions[1186] = EXEC_glEndFragmentShaderATI;
	_dgl_functions[1187] = EXEC_glPassTexCoordATI;
	_dgl_functions[1188] = EXEC_glSampleMapATI;
	_dgl_functions[1189] = EXEC_glColorFragmentOp1ATI;
	_dgl_functions[1190] = EXEC_glColorFragmentOp2ATI;
	_dgl_functions[1191] = EXEC_glColorFragmentOp3ATI;
	_dgl_functions[1192] = EXEC_glAlphaFragmentOp1ATI;
	_dgl_functions[1193] = EXEC_glAlphaFragmentOp2ATI;
	_dgl_functions[1194] = EXEC_glAlphaFragmentOp3ATI;
	_dgl_functions[1195] = EXEC_glSetFragmentShaderConstantATI;
	_dgl_functions[1196] = EXEC_glDrawMeshArraysSUN;
	_dgl_functions[1197] = EXEC_glPointParameteriNV;
	_dgl_functions[1198] = EXEC_glPointParameterivNV;
	_dgl_functions[1199] = EXEC_glActiveStencilFaceEXT;
	_dgl_functions[1200] = EXEC_glDrawBuffersATI;
	_dgl_functions[1201] = EXEC_glProgramNamedParameter4fNV;
	_dgl_functions[1202] = EXEC_glProgramNamedParameter4dNV;
	_dgl_functions[1203] = EXEC_glProgramNamedParameter4fvNV;
	_dgl_functions[1204] = EXEC_glProgramNamedParameter4dvNV;
	_dgl_functions[1205] = EXEC_glGetProgramNamedParameterfvNV;
	_dgl_functions[1206] = EXEC_glGetProgramNamedParameterdvNV;
	_dgl_functions[1207] = EXEC_glDepthBoundsEXT;
	_dgl_functions[1208] = EXEC_glBlendEquationSeparateEXT;
	_dgl_functions[1209] = EXEC_glBlitFramebufferEXT;
	_dgl_functions[1210] = EXEC_glBlendEquationSeparateATI;
	_dgl_functions[1211] = EXEC_glStencilOpSeparateATI;
	_dgl_functions[1212] = EXEC_glStencilFuncSeparateATI;
	_dgl_functions[1213] = EXEC_glProgramEnvParameters4fvEXT;
	_dgl_functions[1214] = EXEC_glProgramLocalParameters4fvEXT;
	_dgl_functions[1215] = EXEC_glGetQueryObjecti64vEXT;
	_dgl_functions[1216] = EXEC_glGetQueryObjectui64vEXT;
	_dgl_functions[1217] = EXEC_glBlendFuncSeparateINGR;
	_dgl_functions[1218] = EXEC_glCreateDebugObjectMESA;
	_dgl_functions[1219] = EXEC_glClearDebugLogMESA;
	_dgl_functions[1220] = EXEC_glGetDebugLogMESA;
	_dgl_functions[1221] = EXEC_glGetDebugLogLengthMESA;
	_dgl_functions[1222] = EXEC_glPointParameterfSGIS;
	_dgl_functions[1223] = EXEC_glPointParameterfvSGIS;
	_dgl_functions[1224] = EXEC_glIglooInterfaceSGIX;
	_dgl_functions[1225] = EXEC_glDeformationMap3dSGIX;
	_dgl_functions[1226] = EXEC_glDeformationMap3fSGIX;
	_dgl_functions[1227] = EXEC_glDeformSGIX;
	_dgl_functions[1228] = EXEC_glLoadIdentityDeformationMapSGIX;

	//CGL functions
	_dgl_functions[1499] = EXEC_CGLSwapBuffers;

	//GLU functions
	_dgl_functions[1501] = EXEC_gluBeginCurve;
	_dgl_functions[1502] = EXEC_gluBeginPolygon;
	_dgl_functions[1503] = EXEC_gluBeginSurface;
	_dgl_functions[1504] = EXEC_gluBeginTrim;
	_dgl_functions[1505] = EXEC_gluBuild1DMipmapLevels;
	_dgl_functions[1506] = EXEC_gluBuild1DMipmaps;
	_dgl_functions[1507] = EXEC_gluBuild2DMipmapLevels;
	_dgl_functions[1508] = EXEC_gluBuild2DMipmaps;
	_dgl_functions[1509] = EXEC_gluBuild3DMipmapLevels;
	_dgl_functions[1510] = EXEC_gluBuild3DMipmaps;
	_dgl_functions[1511] = EXEC_gluCheckExtension;
	_dgl_functions[1512] = EXEC_gluCylinder;
	_dgl_functions[1513] = EXEC_gluDeleteNurbsRenderer;
	_dgl_functions[1514] = EXEC_gluDeleteQuadric;
	_dgl_functions[1515] = EXEC_gluDeleteTess;
	_dgl_functions[1516] = EXEC_gluDisk;
	_dgl_functions[1517] = EXEC_gluEndCurve;
	_dgl_functions[1518] = EXEC_gluEndPolygon;
	_dgl_functions[1519] = EXEC_gluEndSurface;
	_dgl_functions[1520] = EXEC_gluEndTrim;
	_dgl_functions[1521] = EXEC_gluErrorString;
	_dgl_functions[1522] = EXEC_gluGetNurbsProperty;
	_dgl_functions[1523] = EXEC_gluGetString;
	_dgl_functions[1524] = EXEC_gluGetTessProperty;
	_dgl_functions[1525] = EXEC_gluLoadSamplingMatrices;
	_dgl_functions[1526] = EXEC_gluLookAt;
	_dgl_functions[1527] = EXEC_gluNewNurbsRenderer;
	_dgl_functions[1528] = EXEC_gluNewQuadric;
	_dgl_functions[1529] = EXEC_gluNewTess;
	_dgl_functions[1530] = EXEC_gluNextContour;
	_dgl_functions[1531] = EXEC_gluNurbsCallback;
	_dgl_functions[1532] = EXEC_gluNurbsCallbackData;
	_dgl_functions[1533] = EXEC_gluNurbsCallbackDataEXT;
	_dgl_functions[1534] = EXEC_gluNurbsCurve;
	_dgl_functions[1535] = EXEC_gluNurbsProperty;
	_dgl_functions[1536] = EXEC_gluNurbsSurface;
	_dgl_functions[1537] = EXEC_gluOrtho2D;
	_dgl_functions[1538] = EXEC_gluPartialDisk;
	_dgl_functions[1539] = EXEC_gluPerspective;
	_dgl_functions[1540] = EXEC_gluPickMatrix;
	_dgl_functions[1541] = EXEC_gluProject;
	_dgl_functions[1542] = EXEC_gluPwlCurve;
	_dgl_functions[1543] = EXEC_gluQuadricCallback;
	_dgl_functions[1544] = EXEC_gluQuadricDrawStyle;
	_dgl_functions[1545] = EXEC_gluQuadricNormals;
	_dgl_functions[1546] = EXEC_gluQuadricOrientation;
	_dgl_functions[1547] = EXEC_gluQuadricTexture;
	_dgl_functions[1548] = EXEC_glugluScaleImage;
	_dgl_functions[1549] = EXEC_gluSphere;
	_dgl_functions[1550] = EXEC_gluTessBeginContour;
	_dgl_functions[1551] = EXEC_gluTessBeginPolygon;
	_dgl_functions[1552] = EXEC_gluTessCallback;
	_dgl_functions[1553] = EXEC_gluTessEndContour;
	_dgl_functions[1554] = EXEC_gluTessEndPolygon;
	_dgl_functions[1555] = EXEC_gluTessNormal;
	_dgl_functions[1556] = EXEC_gluTessProperty;
	_dgl_functions[1557] = EXEC_gluTessVertex;
	_dgl_functions[1558] = EXEC_gluUnProject;
	_dgl_functions[1559] = EXEC_gluUnProject4;

	//GLX functions
	_dgl_functions[1601] = EXEC_glXChooseVisual;
	_dgl_functions[1602] = EXEC_glXCreateContext;
	_dgl_functions[1603] = EXEC_glXDestroyContext;
	_dgl_functions[1604] = EXEC_glXMakeCurrent;
	_dgl_functions[1605] = EXEC_glXCopyContext;
	_dgl_functions[1606] = EXEC_glXSwapBuffers;
	_dgl_functions[1607] = EXEC_glXCreateGLXPixmap;
	_dgl_functions[1608] = EXEC_glXDestroyGLXPixmap;
	_dgl_functions[1609] = EXEC_glXQueryExtension;
	_dgl_functions[1610] = EXEC_glXQueryVersion;
	_dgl_functions[1611] = EXEC_glXIsDirect;
	_dgl_functions[1612] = EXEC_glXGetConfig;
	_dgl_functions[1613] = EXEC_glXGetCurrentContext;
	_dgl_functions[1614] = EXEC_glXGetCurrentDrawable;
	_dgl_functions[1615] = EXEC_glXWaitGL;
	_dgl_functions[1616] = EXEC_glXWaitX;
	_dgl_functions[1617] = EXEC_glXUseXFont;
	_dgl_functions[1618] = EXEC_glXQueryExtensionsString;
	_dgl_functions[1619] = EXEC_glXQueryServerString;
	_dgl_functions[1620] = EXEC_glXGetClientString;
	_dgl_functions[1621] = EXEC_glXGetCurrentDisplay;
	_dgl_functions[1622] = EXEC_glXChooseFBConfig;
	_dgl_functions[1623] = EXEC_glXGetFBConfigAttrib;
	_dgl_functions[1624] = EXEC_glXGetFBConfigs;
	_dgl_functions[1625] = EXEC_glXGetVisualFromFBConfig;
	_dgl_functions[1626] = EXEC_glXCreateWindow;
	_dgl_functions[1627] = EXEC_glXDestroyWindow;
	_dgl_functions[1628] = EXEC_glXCreatePixmap;
	_dgl_functions[1629] = EXEC_glXDestroyPixmap;
	_dgl_functions[1630] = EXEC_glXCreatePbuffer;
	_dgl_functions[1631] = EXEC_glXDestroyPbuffer;
	_dgl_functions[1632] = EXEC_glXQueryDrawable;
	_dgl_functions[1633] = EXEC_glXCreateNewContext;
	_dgl_functions[1634] = EXEC_glXMakeContextCurrent;
	_dgl_functions[1635] = EXEC_glXGetCurrentReadDrawable;
	_dgl_functions[1636] = EXEC_glXQueryContext;
	_dgl_functions[1637] = EXEC_glXSelectEvent;
	_dgl_functions[1638] = EXEC_glXGetSelectedEvent;
	_dgl_functions[1639] = EXEC_glXGetProcAddressARB;
	_dgl_functions[1640] = EXEC_glXGetProcAddress;
	_dgl_functions[1641] = EXEC_glXAllocateMemoryNV;
	_dgl_functions[1642] = EXEC_glXFreeMemoryNV;
	_dgl_functions[1643] = EXEC_glXAllocateMemoryMESA;
	_dgl_functions[1644] = EXEC_glXFreeMemoryMESA;
	_dgl_functions[1645] = EXEC_glXGetMemoryOffsetMESA;
	_dgl_functions[1646] = EXEC_glXBindTexImageARB;
	_dgl_functions[1647] = EXEC_glXReleaseTexImageARB;
	_dgl_functions[1648] = EXEC_glXDrawableAttribARB;
	_dgl_functions[1649] = EXEC_glXGetFrameUsageMESA;
	_dgl_functions[1650] = EXEC_glXBeginFrameTrackingMESA;
	_dgl_functions[1651] = EXEC_glXEndFrameTrackingMESA;
	_dgl_functions[1652] = EXEC_glXQueryFrameTrackingMESA;
	_dgl_functions[1653] = EXEC_glXSwapIntervalMESA;
	_dgl_functions[1654] = EXEC_glXGetSwapIntervalMESA;
	_dgl_functions[1655] = EXEC_glXBindTexImageEXT;
	_dgl_functions[1656] = EXEC_glXReleaseTexImageEXT;
}
