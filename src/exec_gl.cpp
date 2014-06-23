#include <GL/glew.h>
#include "exec.hpp"
#include "consts.hpp"
#include <cstring>

using namespace std;

//0
 void EXEC_glNewList(char *commandbuf)
{
	GLuint *list = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glNewList(*list, *mode);
}


//1
 void EXEC_glEndList(char *commandbuf)
{

	glEndList();
}


//2
 void EXEC_glCallList(char *commandbuf)
{
	GLuint *list = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

	glCallList(*list);
}


//3
 void EXEC_glCallLists(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	//LOG("glCallLists(%d, %d)\n", *n, *type);

	glCallLists(*n, *type, (const GLvoid *)popBuf());
}


//4
 void EXEC_glDeleteLists(char *commandbuf)
{
	GLuint *list = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);
	GLsizei *range = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glDeleteLists(*list, *range);
}


//5
 void EXEC_glGenLists(char *commandbuf)
{
	GLsizei *range = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	pushRet(glGenLists(*range));
}


//6
 void EXEC_glListBase(char *commandbuf)
{
	GLuint *base = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

	glListBase(*base);
}


//7
 void EXEC_glBegin(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	glBegin(*mode);
}


//8
 void EXEC_glBitmap(char *commandbuf)
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
 void EXEC_glColor3b(char *commandbuf)
{
	GLbyte *red = (GLbyte*)commandbuf;   commandbuf += sizeof(GLbyte);
	GLbyte *green = (GLbyte*)commandbuf;     commandbuf += sizeof(GLbyte);
	GLbyte *blue = (GLbyte*)commandbuf;  commandbuf += sizeof(GLbyte);

	glColor3b(*red, *green, *blue);
}


//10
 void EXEC_glColor3bv(char *commandbuf)
{

	glColor3bv((const GLbyte *)popBuf());
}


//11
 void EXEC_glColor3d(char *commandbuf)
{
	GLdouble *red = (GLdouble*)commandbuf;   commandbuf += sizeof(GLdouble);
	GLdouble *green = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *blue = (GLdouble*)commandbuf;  commandbuf += sizeof(GLdouble);

	glColor3d(*red, *green, *blue);
}


//12
 void EXEC_glColor3dv(char *commandbuf)
{

	glColor3dv((const GLdouble *)popBuf());
}


//13
 void EXEC_glColor3f(char *commandbuf)
{
	GLfloat *red = (GLfloat*)commandbuf;     commandbuf += sizeof(GLfloat);
	GLfloat *green = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *blue = (GLfloat*)commandbuf;    commandbuf += sizeof(GLfloat);

	glColor3f(*red, *green, *blue);
}


//14
 void EXEC_glColor3fv(char *commandbuf)
{

	glColor3fv((const GLfloat *)popBuf());
}


//15
 void EXEC_glColor3i(char *commandbuf)
{
	GLint *red = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *green = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *blue = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glColor3i(*red, *green, *blue);
}


//16
 void EXEC_glColor3iv(char *commandbuf)
{

	glColor3iv((const GLint *)popBuf());
}


//17
 void EXEC_glColor3s(char *commandbuf)
{
	GLshort *red = (GLshort*)commandbuf;     commandbuf += sizeof(GLshort);
	GLshort *green = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *blue = (GLshort*)commandbuf;    commandbuf += sizeof(GLshort);

	glColor3s(*red, *green, *blue);
}


//18
 void EXEC_glColor3sv(char *commandbuf)
{

	glColor3sv((const GLshort *)popBuf());
}


//19
 void EXEC_glColor3ub(char *commandbuf)
{
	GLubyte *red = (GLubyte*)commandbuf;     commandbuf += sizeof(GLubyte);
	GLubyte *green = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *blue = (GLubyte*)commandbuf;    commandbuf += sizeof(GLubyte);

	glColor3ub(*red, *green, *blue);
}


//20
 void EXEC_glColor3ubv(char *commandbuf)
{

	glColor3ubv((const GLubyte *)popBuf());
}


//21
 void EXEC_glColor3ui(char *commandbuf)
{
	GLuint *red = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *green = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLuint *blue = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

	glColor3ui(*red, *green, *blue);
}


//22
 void EXEC_glColor3uiv(char *commandbuf)
{

	glColor3uiv((const GLuint *)popBuf());
}


//23
 void EXEC_glColor3us(char *commandbuf)
{
	GLushort *red = (GLushort*)commandbuf;   commandbuf += sizeof(GLushort);
	GLushort *green = (GLushort*)commandbuf;     commandbuf += sizeof(GLushort);
	GLushort *blue = (GLushort*)commandbuf;  commandbuf += sizeof(GLushort);

	glColor3us(*red, *green, *blue);
}


//24
 void EXEC_glColor3usv(char *commandbuf)
{

	glColor3usv((const GLushort *)popBuf());
}


//25
 void EXEC_glColor4b(char *commandbuf)
{
	GLbyte *red = (GLbyte*)commandbuf;   commandbuf += sizeof(GLbyte);
	GLbyte *green = (GLbyte*)commandbuf;     commandbuf += sizeof(GLbyte);
	GLbyte *blue = (GLbyte*)commandbuf;  commandbuf += sizeof(GLbyte);
	GLbyte *alpha = (GLbyte*)commandbuf;     commandbuf += sizeof(GLbyte);

	glColor4b(*red, *green, *blue, *alpha);
}


//26
 void EXEC_glColor4bv(char *commandbuf)
{

	glColor4bv((const GLbyte *)popBuf());
}


//27
 void EXEC_glColor4d(char *commandbuf)
{
	GLdouble *red = (GLdouble*)commandbuf;   commandbuf += sizeof(GLdouble);
	GLdouble *green = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *blue = (GLdouble*)commandbuf;  commandbuf += sizeof(GLdouble);
	GLdouble *alpha = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glColor4d(*red, *green, *blue, *alpha);
}


//28
 void EXEC_glColor4dv(char *commandbuf)
{

	glColor4dv((const GLdouble *)popBuf());
}


//29
 void EXEC_glColor4f(char *commandbuf)
{
	GLfloat *red = (GLfloat*)commandbuf;     commandbuf += sizeof(GLfloat);
	GLfloat *green = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *blue = (GLfloat*)commandbuf;    commandbuf += sizeof(GLfloat);
	GLfloat *alpha = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glColor4f(*red, *green, *blue, *alpha);
}


//30
 void EXEC_glColor4fv(char *commandbuf)
{

	glColor4fv((const GLfloat *)popBuf());
}


//31
 void EXEC_glColor4i(char *commandbuf)
{
	GLint *red = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *green = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *blue = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLint *alpha = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glColor4i(*red, *green, *blue, *alpha);
}


//32
 void EXEC_glColor4iv(char *commandbuf)
{

	glColor4iv((const GLint *)popBuf());
}


//33
 void EXEC_glColor4s(char *commandbuf)
{
	GLshort *red = (GLshort*)commandbuf;     commandbuf += sizeof(GLshort);
	GLshort *green = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *blue = (GLshort*)commandbuf;    commandbuf += sizeof(GLshort);
	GLshort *alpha = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glColor4s(*red, *green, *blue, *alpha);
}


//34
 void EXEC_glColor4sv(char *commandbuf)
{

	glColor4sv((const GLshort *)popBuf());
}


//35
 void EXEC_glColor4ub(char *commandbuf)
{
	GLubyte *red = (GLubyte*)commandbuf;     commandbuf += sizeof(GLubyte);
	GLubyte *green = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *blue = (GLubyte*)commandbuf;    commandbuf += sizeof(GLubyte);
	GLubyte *alpha = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);

	glColor4ub(*red, *green, *blue, *alpha);
}


//36
 void EXEC_glColor4ubv(char *commandbuf)
{

	glColor4ubv((const GLubyte *)popBuf());
}


//37
 void EXEC_glColor4ui(char *commandbuf)
{
	GLuint *red = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *green = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLuint *blue = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);
	GLuint *alpha = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glColor4ui(*red, *green, *blue, *alpha);
}


//38
 void EXEC_glColor4uiv(char *commandbuf)
{

	glColor4uiv((const GLuint *)popBuf());
}


//39
 void EXEC_glColor4us(char *commandbuf)
{
	GLushort *red = (GLushort*)commandbuf;   commandbuf += sizeof(GLushort);
	GLushort *green = (GLushort*)commandbuf;     commandbuf += sizeof(GLushort);
	GLushort *blue = (GLushort*)commandbuf;  commandbuf += sizeof(GLushort);
	GLushort *alpha = (GLushort*)commandbuf;     commandbuf += sizeof(GLushort);

	glColor4us(*red, *green, *blue, *alpha);
}


//40
 void EXEC_glColor4usv(char *commandbuf)
{

	glColor4usv((const GLushort *)popBuf());
}


//41
 void EXEC_glEdgeFlag(char *commandbuf)
{
	GLboolean *flag = (GLboolean*)commandbuf;    commandbuf += sizeof(GLboolean);

	glEdgeFlag(*flag);
}


//42
 void EXEC_glEdgeFlagv(char *commandbuf)
{

	glEdgeFlagv((const GLboolean *)popBuf());
}


//43
 void EXEC_glEnd(char *commandbuf)
{

	glEnd();
}


//44
 void EXEC_glIndexd(char *commandbuf)
{
	GLdouble *c = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glIndexd(*c);
}


//45
 void EXEC_glIndexdv(char *commandbuf)
{

	glIndexdv((const GLdouble *)popBuf());
}


//46
 void EXEC_glIndexf(char *commandbuf)
{
	GLfloat *c = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glIndexf(*c);
}


//47
 void EXEC_glIndexfv(char *commandbuf)
{

	glIndexfv((const GLfloat *)popBuf());
}


//48
 void EXEC_glIndexi(char *commandbuf)
{
	GLint *c = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glIndexi(*c);
}


//49
 void EXEC_glIndexiv(char *commandbuf)
{

	glIndexiv((const GLint *)popBuf());
}


//50
 void EXEC_glIndexs(char *commandbuf)
{
	GLshort *c = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glIndexs(*c);
}


//51
 void EXEC_glIndexsv(char *commandbuf)
{

	glIndexsv((const GLshort *)popBuf());
}


//52
 void EXEC_glNormal3b(char *commandbuf)
{
	GLbyte *nx = (GLbyte*)commandbuf;    commandbuf += sizeof(GLbyte);
	GLbyte *ny = (GLbyte*)commandbuf;    commandbuf += sizeof(GLbyte);
	GLbyte *nz = (GLbyte*)commandbuf;    commandbuf += sizeof(GLbyte);

	glNormal3b(*nx, *ny, *nz);
}


//53
 void EXEC_glNormal3bv(char *commandbuf)
{

	glNormal3bv((const GLbyte *)popBuf());
}


//54
 void EXEC_glNormal3d(char *commandbuf)
{
	GLdouble *nx = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *ny = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *nz = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);

	glNormal3d(*nx, *ny, *nz);
}


//55
 void EXEC_glNormal3dv(char *commandbuf)
{

	glNormal3dv((const GLdouble *)popBuf());
}


//56
 void EXEC_glNormal3f(char *commandbuf)
{
	GLfloat *nx = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *ny = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *nz = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	glNormal3f(*nx, *ny, *nz);
}


//57
 void EXEC_glNormal3fv(char *commandbuf)
{

	glNormal3fv((const GLfloat *)popBuf());
}


//58
 void EXEC_glNormal3i(char *commandbuf)
{
	GLint *nx = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *ny = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *nz = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glNormal3i(*nx, *ny, *nz);
}


//59
 void EXEC_glNormal3iv(char *commandbuf)
{

	glNormal3iv((const GLint *)popBuf());
}


//60
 void EXEC_glNormal3s(char *commandbuf)
{
	GLshort *nx = (GLshort*)commandbuf;  commandbuf += sizeof(GLshort);
	GLshort *ny = (GLshort*)commandbuf;  commandbuf += sizeof(GLshort);
	GLshort *nz = (GLshort*)commandbuf;  commandbuf += sizeof(GLshort);

	glNormal3s(*nx, *ny, *nz);
}


//61
 void EXEC_glNormal3sv(char *commandbuf)
{

	glNormal3sv((const GLshort *)popBuf());
}


//62
 void EXEC_glRasterPos2d(char *commandbuf)
{
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glRasterPos2d(*x, *y);
}


//63
 void EXEC_glRasterPos2dv(char *commandbuf)
{

	glRasterPos2dv((const GLdouble *)popBuf());
}


//64
 void EXEC_glRasterPos2f(char *commandbuf)
{
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glRasterPos2f(*x, *y);
}


//65
 void EXEC_glRasterPos2fv(char *commandbuf)
{

	glRasterPos2fv((const GLfloat *)popBuf());
}


//66
 void EXEC_glRasterPos2i(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glRasterPos2i(*x, *y);
}


//67
 void EXEC_glRasterPos2iv(char *commandbuf)
{

	glRasterPos2iv((const GLint *)popBuf());
}


//68
 void EXEC_glRasterPos2s(char *commandbuf)
{
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glRasterPos2s(*x, *y);
}


//69
 void EXEC_glRasterPos2sv(char *commandbuf)
{

	glRasterPos2sv((const GLshort *)popBuf());
}


//70
 void EXEC_glRasterPos3d(char *commandbuf)
{
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glRasterPos3d(*x, *y, *z);
}


//71
 void EXEC_glRasterPos3dv(char *commandbuf)
{

	glRasterPos3dv((const GLdouble *)popBuf());
}


//72
 void EXEC_glRasterPos3f(char *commandbuf)
{
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glRasterPos3f(*x, *y, *z);
}


//73
 void EXEC_glRasterPos3fv(char *commandbuf)
{

	glRasterPos3fv((const GLfloat *)popBuf());
}


//74
 void EXEC_glRasterPos3i(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *z = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glRasterPos3i(*x, *y, *z);
}


//75
 void EXEC_glRasterPos3iv(char *commandbuf)
{

	glRasterPos3iv((const GLint *)popBuf());
}


//76
 void EXEC_glRasterPos3s(char *commandbuf)
{
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *z = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glRasterPos3s(*x, *y, *z);
}


//77
 void EXEC_glRasterPos3sv(char *commandbuf)
{

	glRasterPos3sv((const GLshort *)popBuf());
}


//78
 void EXEC_glRasterPos4d(char *commandbuf)
{
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *w = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glRasterPos4d(*x, *y, *z, *w);
}


//79
 void EXEC_glRasterPos4dv(char *commandbuf)
{

	glRasterPos4dv((const GLdouble *)popBuf());
}


//80
 void EXEC_glRasterPos4f(char *commandbuf)
{
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *w = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glRasterPos4f(*x, *y, *z, *w);
}


//81
 void EXEC_glRasterPos4fv(char *commandbuf)
{

	glRasterPos4fv((const GLfloat *)popBuf());
}


//82
 void EXEC_glRasterPos4i(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *z = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *w = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glRasterPos4i(*x, *y, *z, *w);
}


//83
 void EXEC_glRasterPos4iv(char *commandbuf)
{

	glRasterPos4iv((const GLint *)popBuf());
}


//84
 void EXEC_glRasterPos4s(char *commandbuf)
{
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *z = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *w = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glRasterPos4s(*x, *y, *z, *w);
}


//85
 void EXEC_glRasterPos4sv(char *commandbuf)
{

	glRasterPos4sv((const GLshort *)popBuf());
}


//86
 void EXEC_glRectd(char *commandbuf)
{
	GLdouble *x1 = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *y1 = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *x2 = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *y2 = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);

	glRectd(*x1, *y1, *x2, *y2);
}


//87
 void EXEC_glRectdv(char *commandbuf)
{

	glRectdv((const GLdouble *)popBuf(), (const GLdouble *)popBuf());
}


//88
 void EXEC_glRectf(char *commandbuf)
{
	GLfloat *x1 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *y1 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *x2 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *y2 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	glRectf(*x1, *y1, *x2, *y2);
}


//89
 void EXEC_glRectfv(char *commandbuf)
{

	glRectfv((const GLfloat *)popBuf(), (const GLfloat *)popBuf());
}


//90
 void EXEC_glRecti(char *commandbuf)
{
	GLint *x1 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *y1 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *x2 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *y2 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glRecti(*x1, *y1, *x2, *y2);
}


//91
 void EXEC_glRectiv(char *commandbuf)
{

	glRectiv((const GLint *)popBuf(), (const GLint *)popBuf());
}


//92
 void EXEC_glRects(char *commandbuf)
{
	GLshort *x1 = (GLshort*)commandbuf;  commandbuf += sizeof(GLshort);
	GLshort *y1 = (GLshort*)commandbuf;  commandbuf += sizeof(GLshort);
	GLshort *x2 = (GLshort*)commandbuf;  commandbuf += sizeof(GLshort);
	GLshort *y2 = (GLshort*)commandbuf;  commandbuf += sizeof(GLshort);

	glRects(*x1, *y1, *x2, *y2);
}


//93
 void EXEC_glRectsv(char *commandbuf)
{

	glRectsv((const GLshort *)popBuf(), (const GLshort *)popBuf());
}


//94
 void EXEC_glTexCoord1d(char *commandbuf)
{
	GLdouble *s = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glTexCoord1d(*s);
}


//95
 void EXEC_glTexCoord1dv(char *commandbuf)
{

	glTexCoord1dv((const GLdouble *)popBuf());
}


//96
 void EXEC_glTexCoord1f(char *commandbuf)
{
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glTexCoord1f(*s);
}


//97
 void EXEC_glTexCoord1fv(char *commandbuf)
{

	glTexCoord1fv((const GLfloat *)popBuf());
}


//98
 void EXEC_glTexCoord1i(char *commandbuf)
{
	GLint *s = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glTexCoord1i(*s);
}


//99
 void EXEC_glTexCoord1iv(char *commandbuf)
{

	glTexCoord1iv((const GLint *)popBuf());
}


//100
 void EXEC_glTexCoord1s(char *commandbuf)
{
	GLshort *s = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glTexCoord1s(*s);
}


//101
 void EXEC_glTexCoord1sv(char *commandbuf)
{

	glTexCoord1sv((const GLshort *)popBuf());
}


//102
 void EXEC_glTexCoord2d(char *commandbuf)
{
	GLdouble *s = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *t = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glTexCoord2d(*s, *t);
}


//103
 void EXEC_glTexCoord2dv(char *commandbuf)
{

	glTexCoord2dv((const GLdouble *)popBuf());
}


//104
 void EXEC_glTexCoord2f(char *commandbuf)
{
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *t = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glTexCoord2f(*s, *t);
}


//105
 void EXEC_glTexCoord2fv(char *commandbuf)
{

	glTexCoord2fv((const GLfloat *)popBuf());
}


//106
 void EXEC_glTexCoord2i(char *commandbuf)
{
	GLint *s = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *t = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glTexCoord2i(*s, *t);
}


//107
 void EXEC_glTexCoord2iv(char *commandbuf)
{

	glTexCoord2iv((const GLint *)popBuf());
}


//108
 void EXEC_glTexCoord2s(char *commandbuf)
{
	GLshort *s = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *t = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glTexCoord2s(*s, *t);
}


//109
 void EXEC_glTexCoord2sv(char *commandbuf)
{

	glTexCoord2sv((const GLshort *)popBuf());
}


//110
 void EXEC_glTexCoord3d(char *commandbuf)
{
	GLdouble *s = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *t = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *r = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glTexCoord3d(*s, *t, *r);
}


//111
 void EXEC_glTexCoord3dv(char *commandbuf)
{

	glTexCoord3dv((const GLdouble *)popBuf());
}


//112
 void EXEC_glTexCoord3f(char *commandbuf)
{
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *t = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *r = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glTexCoord3f(*s, *t, *r);
}


//113
 void EXEC_glTexCoord3fv(char *commandbuf)
{

	glTexCoord3fv((const GLfloat *)popBuf());
}


//114
 void EXEC_glTexCoord3i(char *commandbuf)
{
	GLint *s = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *t = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *r = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glTexCoord3i(*s, *t, *r);
}


//115
 void EXEC_glTexCoord3iv(char *commandbuf)
{

	glTexCoord3iv((const GLint *)popBuf());
}


//116
 void EXEC_glTexCoord3s(char *commandbuf)
{
	GLshort *s = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *t = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *r = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glTexCoord3s(*s, *t, *r);
}


//117
 void EXEC_glTexCoord3sv(char *commandbuf)
{

	glTexCoord3sv((const GLshort *)popBuf());
}


//118
 void EXEC_glTexCoord4d(char *commandbuf)
{
	GLdouble *s = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *t = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *r = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *q = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glTexCoord4d(*s, *t, *r, *q);
}


//119
 void EXEC_glTexCoord4dv(char *commandbuf)
{

	glTexCoord4dv((const GLdouble *)popBuf());
}


//120
 void EXEC_glTexCoord4f(char *commandbuf)
{
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *t = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *r = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *q = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glTexCoord4f(*s, *t, *r, *q);
}


//121
 void EXEC_glTexCoord4fv(char *commandbuf)
{

	glTexCoord4fv((const GLfloat *)popBuf());
}


//122
 void EXEC_glTexCoord4i(char *commandbuf)
{
	GLint *s = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *t = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *r = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *q = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glTexCoord4i(*s, *t, *r, *q);
}


//123
 void EXEC_glTexCoord4iv(char *commandbuf)
{

	glTexCoord4iv((const GLint *)popBuf());
}


//124
 void EXEC_glTexCoord4s(char *commandbuf)
{
	GLshort *s = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *t = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *r = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *q = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glTexCoord4s(*s, *t, *r, *q);
}


//125
 void EXEC_glTexCoord4sv(char *commandbuf)
{

	glTexCoord4sv((const GLshort *)popBuf());
}


//126
 void EXEC_glVertex2d(char *commandbuf)
{
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glVertex2d(*x, *y);
}


//127
 void EXEC_glVertex2dv(char *commandbuf)
{

	glVertex2dv((const GLdouble *)popBuf());
}


//128
 void EXEC_glVertex2f(char *commandbuf)
{
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	glVertex2f(*x, *y);
}


//129
 void EXEC_glVertex2fv(char *commandbuf)
{

	glVertex2fv((const GLfloat *)popBuf());
}


//130
 void EXEC_glVertex2i(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glVertex2i(*x, *y);
}


//131
 void EXEC_glVertex2iv(char *commandbuf)
{

	glVertex2iv((const GLint *)popBuf());
}


//132
 void EXEC_glVertex2s(char *commandbuf)
{
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glVertex2s(*x, *y);
}


//133
 void EXEC_glVertex2sv(char *commandbuf)
{

	glVertex2sv((const GLshort *)popBuf());
}


//134
 void EXEC_glVertex3d(char *commandbuf)
{
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glVertex3d(*x, *y, *z);
}


//135
 void EXEC_glVertex3dv(char *commandbuf)
{

	glVertex3dv((const GLdouble *)popBuf());
}


//136
 void EXEC_glVertex3f(char *commandbuf)
{
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glVertex3f(*x, *y, *z);
}


//137
 void EXEC_glVertex3fv(char *commandbuf)
{

	glVertex3fv((const GLfloat *)popBuf());
}


//138
 void EXEC_glVertex3i(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *z = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glVertex3i(*x, *y, *z);
}


//139
 void EXEC_glVertex3iv(char *commandbuf)
{

	glVertex3iv((const GLint *)popBuf());
}


//140
 void EXEC_glVertex3s(char *commandbuf)
{
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *z = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glVertex3s(*x, *y, *z);
}


//141
 void EXEC_glVertex3sv(char *commandbuf)
{

	glVertex3sv((const GLshort *)popBuf());
}


//142
 void EXEC_glVertex4d(char *commandbuf)
{
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *w = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glVertex4d(*x, *y, *z, *w);
}


//143
 void EXEC_glVertex4dv(char *commandbuf)
{

	glVertex4dv((const GLdouble *)popBuf());
}


//144
 void EXEC_glVertex4f(char *commandbuf)
{
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *w = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glVertex4f(*x, *y, *z, *w);
}


//145
 void EXEC_glVertex4fv(char *commandbuf)
{

	glVertex4fv((const GLfloat *)popBuf());
}


//146
 void EXEC_glVertex4i(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *z = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *w = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glVertex4i(*x, *y, *z, *w);
}


//147
 void EXEC_glVertex4iv(char *commandbuf)
{

	glVertex4iv((const GLint *)popBuf());
}


//148
 void EXEC_glVertex4s(char *commandbuf)
{
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *z = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *w = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glVertex4s(*x, *y, *z, *w);
}


//149
 void EXEC_glVertex4sv(char *commandbuf)
{

	glVertex4sv((const GLshort *)popBuf());
}


//150
 void EXEC_glClipPlane(char *commandbuf)
{
	GLenum *plane = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glClipPlane(*plane, (const GLdouble *)popBuf());
}


//151
 void EXEC_glColorMaterial(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glColorMaterial(*face, *mode);
}


//152
 void EXEC_glCullFace(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glCullFace(*mode);
}


//153
 void EXEC_glFogf(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glFogf(*pname, *param);
}


//154
 void EXEC_glFogfv(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glFogfv(*pname, (const GLfloat *)popBuf());
}


//155
 void EXEC_glFogi(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glFogi(*pname, *param);
}


//156
 void EXEC_glFogiv(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	glFogiv(*pname, (const GLint *)popBuf());
}


//157
 void EXEC_glFrontFace(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glFrontFace(*mode);
}


//158
 void EXEC_glHint(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glHint(*target, *mode);
}


//159
 void EXEC_glLightf(char *commandbuf)
{
	GLenum *light = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glLightf(*light, *pname, *param);
}


//160
 void EXEC_glLightfv(char *commandbuf)
{
	GLenum *light = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glLightfv(*light, *pname, (const GLfloat *)popBuf());
}


//161
 void EXEC_glLighti(char *commandbuf)
{
	GLenum *light = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glLighti(*light, *pname, *param);
}


//162
 void EXEC_glLightiv(char *commandbuf)
{
	GLenum *light = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glLightiv(*light, *pname, (const GLint *)popBuf());
}


//163
 void EXEC_glLightModelf(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glLightModelf(*pname, *param);
}


//164
 void EXEC_glLightModelfv(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glLightModelfv(*pname, (const GLfloat *)popBuf());
}


//165
 void EXEC_glLightModeli(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glLightModeli(*pname, *param);
}


//166
 void EXEC_glLightModeliv(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glLightModeliv(*pname, (const GLint *)popBuf());
}


//167
 void EXEC_glLineStipple(char *commandbuf)
{
	GLint *factor = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLushort *pattern = (GLushort*)commandbuf;   commandbuf += sizeof(GLushort);

	glLineStipple(*factor, *pattern);
}


//168
 void EXEC_glLineWidth(char *commandbuf)
{
	GLfloat *width = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glLineWidth(*width);
}


//169
 void EXEC_glMaterialf(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glMaterialf(*face, *pname, *param);
}


//170
 void EXEC_glMaterialfv(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glMaterialfv(*face, *pname, (const GLfloat *)popBuf());

	//LOG("glMaterialfv: %d\n", i);
}


//171
 void EXEC_glMateriali(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glMateriali(*face, *pname, *param);
}


//172
 void EXEC_glMaterialiv(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glMaterialiv(*face, *pname, (const GLint *)popBuf());
}


//173
 void EXEC_glPointSize(char *commandbuf)
{
	GLfloat *size = (GLfloat*)commandbuf;    commandbuf += sizeof(GLfloat);

	glPointSize(*size);
}


//174
 void EXEC_glPolygonMode(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glPolygonMode(*face, *mode);
}


//175
 void EXEC_glPolygonStipple(char *commandbuf)
{

	glPolygonStipple((const GLubyte *)popBuf());
}


//176
 void EXEC_glScissor(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glScissor(*x, *y, *width, *height);
}


//177
 void EXEC_glShadeModel(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glShadeModel(*mode);
}


//178
 void EXEC_glTexParameterf(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glTexParameterf(*target, *pname, *param);
}


//179
 void EXEC_glTexParameterfv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glTexParameterfv(*target, *pname, (const GLfloat *)popBuf());
}


//180
 void EXEC_glTexParameteri(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	glTexParameteri(*target, *pname, *param);
}


//181
 void EXEC_glTexParameteriv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glTexParameteriv(*target, *pname, (const GLint *)popBuf());
}


//182
 void EXEC_glTexImage1D(char *commandbuf)
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
 void EXEC_glTexImage2D(char *commandbuf)
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
 void EXEC_glTexEnvf(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glTexEnvf(*target, *pname, *param);
}


//185
 void EXEC_glTexEnvfv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glTexEnvfv(*target, *pname, (const GLfloat *)popBuf());
}


//186
 void EXEC_glTexEnvi(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glTexEnvi(*target, *pname, *param);
}


//187
 void EXEC_glTexEnviv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glTexEnviv(*target, *pname, (const GLint *)popBuf());
}


//188
 void EXEC_glTexGend(char *commandbuf)
{
	GLenum *coord = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLdouble *param = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glTexGend(*coord, *pname, *param);
}


//189
 void EXEC_glTexGendv(char *commandbuf)
{
	GLenum *coord = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glTexGendv(*coord, *pname, (const GLdouble *)popBuf());
}


//190
 void EXEC_glTexGenf(char *commandbuf)
{
	GLenum *coord = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glTexGenf(*coord, *pname, *param);
}


//191
 void EXEC_glTexGenfv(char *commandbuf)
{
	GLenum *coord = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glTexGenfv(*coord, *pname, (const GLfloat *)popBuf());
}


//192
 void EXEC_glTexGeni(char *commandbuf)
{
	GLenum *coord = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glTexGeni(*coord, *pname, *param);
}


//193
 void EXEC_glTexGeniv(char *commandbuf)
{
	GLenum *coord = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glTexGeniv(*coord, *pname, (const GLint *)popBuf());
}


//194
 void EXEC_glFeedbackBuffer(char *commandbuf)
{
	GLsizei *size = (GLsizei*)commandbuf;    commandbuf += sizeof(GLsizei);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glFeedbackBuffer(*size, *type, (GLfloat *)popBuf());
}


//195
 void EXEC_glSelectBuffer(char *commandbuf)
{
	GLsizei *size = (GLsizei*)commandbuf;    commandbuf += sizeof(GLsizei);

	glSelectBuffer(*size, (GLuint *)popBuf());
}


//196
 void EXEC_glRenderMode(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	pushRet(glRenderMode(*mode));
}


//197
 void EXEC_glInitNames(char *commandbuf)
{

	glInitNames();
}


//198
 void EXEC_glLoadName(char *commandbuf)
{
	GLuint *name = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

	glLoadName(*name);
}


//199
 void EXEC_glPassThrough(char *commandbuf)
{
	GLfloat *token = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glPassThrough(*token);
}


//200
 void EXEC_glPopName(char *commandbuf)
{

	glPopName();
}


//201
 void EXEC_glPushName(char *commandbuf)
{
	GLuint *name = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

	glPushName(*name);
}


//202
 void EXEC_glDrawBuffer(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glDrawBuffer(*mode);
}


//203
 void EXEC_glClear(char *commandbuf)
{
	GLbitfield *mask = (GLbitfield*)commandbuf;  commandbuf += sizeof(GLbitfield);

	glClear(*mask);
}


//204
 void EXEC_glClearAccum(char *commandbuf)
{
	GLfloat *red = (GLfloat*)commandbuf;     commandbuf += sizeof(GLfloat);
	GLfloat *green = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *blue = (GLfloat*)commandbuf;    commandbuf += sizeof(GLfloat);
	GLfloat *alpha = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glClearAccum(*red, *green, *blue, *alpha);
}


//205
 void EXEC_glClearIndex(char *commandbuf)
{
	GLfloat *c = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glClearIndex(*c);
}


//206
 void EXEC_glClearColor(char *commandbuf)
{
	GLclampf *red = (GLclampf*)commandbuf;   commandbuf += sizeof(GLclampf);
	GLclampf *green = (GLclampf*)commandbuf;     commandbuf += sizeof(GLclampf);
	GLclampf *blue = (GLclampf*)commandbuf;  commandbuf += sizeof(GLclampf);
	GLclampf *alpha = (GLclampf*)commandbuf;     commandbuf += sizeof(GLclampf);

	glClearColor(*red, *green, *blue, *alpha);
}


//207
 void EXEC_glClearStencil(char *commandbuf)
{
	GLint *s = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glClearStencil(*s);
}


//208
 void EXEC_glClearDepth(char *commandbuf)
{
	GLclampd *depth = (GLclampd*)commandbuf;     commandbuf += sizeof(GLclampd);

	glClearDepth(*depth);
}


//209
 void EXEC_glStencilMask(char *commandbuf)
{
	GLuint *mask = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

	glStencilMask(*mask);
}


//210
 void EXEC_glColorMask(char *commandbuf)
{
	GLboolean *red = (GLboolean*)commandbuf;     commandbuf += sizeof(GLboolean);
	GLboolean *green = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);
	GLboolean *blue = (GLboolean*)commandbuf;    commandbuf += sizeof(GLboolean);
	GLboolean *alpha = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);

	glColorMask(*red, *green, *blue, *alpha);
}


//211
 void EXEC_glDepthMask(char *commandbuf)
{
	GLboolean *flag = (GLboolean*)commandbuf;    commandbuf += sizeof(GLboolean);

	glDepthMask(*flag);
}


//212
 void EXEC_glIndexMask(char *commandbuf)
{
	GLuint *mask = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

	glIndexMask(*mask);
}


//213
 void EXEC_glAccum(char *commandbuf)
{
	GLenum *op = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLfloat *value = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glAccum(*op, *value);
}


//214
 void EXEC_glDisable(char *commandbuf)
{
	GLenum *cap = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);

	glDisable(*cap);
}


//215
 void EXEC_glEnable(char *commandbuf)
{
	GLenum *cap = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);

	glEnable(*cap);
}


//216
 void EXEC_glFinish(char *commandbuf)
{

	glFinish();
}


//217
 void EXEC_glFlush(char *commandbuf)
{

	glFlush();
}


//218
 void EXEC_glPopAttrib(char *commandbuf)
{

	glPopAttrib();
}


//219
 void EXEC_glPushAttrib(char *commandbuf)
{
	GLbitfield *mask = (GLbitfield*)commandbuf;  commandbuf += sizeof(GLbitfield);

	glPushAttrib(*mask);
}


//220
 void EXEC_glMap1d(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLdouble *u1 = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *u2 = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLint *stride = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *order = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glMap1d(*target, *u1, *u2, *stride, *order, (const GLdouble *)popBuf());
}


//221
 void EXEC_glMap1f(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLfloat *u1 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *u2 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLint *stride = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *order = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glMap1f(*target, *u1, *u2, *stride, *order, (const GLfloat *)popBuf());
}


//222
 void EXEC_glMap2d(char *commandbuf)
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
 void EXEC_glMap2f(char *commandbuf)
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
 void EXEC_glMapGrid1d(char *commandbuf)
{
	GLint *un = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLdouble *u1 = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *u2 = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);

	glMapGrid1d(*un, *u1, *u2);
}


//225
 void EXEC_glMapGrid1f(char *commandbuf)
{
	GLint *un = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLfloat *u1 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *u2 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	glMapGrid1f(*un, *u1, *u2);
}


//226
 void EXEC_glMapGrid2d(char *commandbuf)
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
 void EXEC_glMapGrid2f(char *commandbuf)
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
 void EXEC_glEvalCoord1d(char *commandbuf)
{
	GLdouble *u = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glEvalCoord1d(*u);
}


//229
 void EXEC_glEvalCoord1dv(char *commandbuf)
{

	glEvalCoord1dv((const GLdouble *)popBuf());
}


//230
 void EXEC_glEvalCoord1f(char *commandbuf)
{
	GLfloat *u = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glEvalCoord1f(*u);
}


//231
 void EXEC_glEvalCoord1fv(char *commandbuf)
{

	glEvalCoord1fv((const GLfloat *)popBuf());
}


//232
 void EXEC_glEvalCoord2d(char *commandbuf)
{
	GLdouble *u = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *v = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glEvalCoord2d(*u, *v);
}


//233
 void EXEC_glEvalCoord2dv(char *commandbuf)
{

	glEvalCoord2dv((const GLdouble *)popBuf());
}


//234
 void EXEC_glEvalCoord2f(char *commandbuf)
{
	GLfloat *u = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *v = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glEvalCoord2f(*u, *v);
}


//235
 void EXEC_glEvalCoord2fv(char *commandbuf)
{

	glEvalCoord2fv((const GLfloat *)popBuf());
}


//236
 void EXEC_glEvalMesh1(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLint *i1 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *i2 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glEvalMesh1(*mode, *i1, *i2);
}


//237
 void EXEC_glEvalPoint1(char *commandbuf)
{
	GLint *i = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glEvalPoint1(*i);
}


//238
 void EXEC_glEvalMesh2(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLint *i1 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *i2 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *j1 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *j2 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glEvalMesh2(*mode, *i1, *i2, *j1, *j2);
}


//239
 void EXEC_glEvalPoint2(char *commandbuf)
{
	GLint *i = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *j = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glEvalPoint2(*i, *j);
}


//240
 void EXEC_glAlphaFunc(char *commandbuf)
{
	GLenum *func = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLclampf *ref = (GLclampf*)commandbuf;   commandbuf += sizeof(GLclampf);

	glAlphaFunc(*func, *ref);
}


//241
 void EXEC_glBlendFunc(char *commandbuf)
{
	GLenum *sfactor = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);
	GLenum *dfactor = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);

	glBlendFunc(*sfactor, *dfactor);
}


//242
 void EXEC_glLogicOp(char *commandbuf)
{
	GLenum *opcode = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glLogicOp(*opcode);
}


//243
 void EXEC_glStencilFunc(char *commandbuf)
{
	GLenum *func = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLint *ref = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLuint *mask = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

	glStencilFunc(*func, *ref, *mask);
}


//244
 void EXEC_glStencilOp(char *commandbuf)
{
	GLenum *fail = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *zfail = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *zpass = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glStencilOp(*fail, *zfail, *zpass);
}


//245
 void EXEC_glDepthFunc(char *commandbuf)
{
	GLenum *func = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glDepthFunc(*func);
}


//246
 void EXEC_glPixelZoom(char *commandbuf)
{
	GLfloat *xfactor = (GLfloat*)commandbuf;     commandbuf += sizeof(GLfloat);
	GLfloat *yfactor = (GLfloat*)commandbuf;     commandbuf += sizeof(GLfloat);

	glPixelZoom(*xfactor, *yfactor);
}


//247
 void EXEC_glPixelTransferf(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glPixelTransferf(*pname, *param);
}


//248
 void EXEC_glPixelTransferi(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glPixelTransferi(*pname, *param);
}


//249
 void EXEC_glPixelStoref(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glPixelStoref(*pname, *param);
}


//250
 void EXEC_glPixelStorei(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glPixelStorei(*pname, *param);
}


//251
 void EXEC_glPixelMapfv(char *commandbuf)
{
	GLenum *map = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);
	GLsizei *mapsize = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);

	glPixelMapfv(*map, *mapsize, (const GLfloat *)popBuf());
}


//252
 void EXEC_glPixelMapuiv(char *commandbuf)
{
	GLenum *map = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);
	GLsizei *mapsize = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);

	glPixelMapuiv(*map, *mapsize, (const GLuint *)popBuf());
}


//253
 void EXEC_glPixelMapusv(char *commandbuf)
{
	GLenum *map = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);
	GLsizei *mapsize = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);

	glPixelMapusv(*map, *mapsize, (const GLushort *)popBuf());
}


//254
 void EXEC_glReadBuffer(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glReadBuffer(*mode);
}


//255
 void EXEC_glCopyPixels(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glCopyPixels(*x, *y, *width, *height, *type);
}


//256
 void EXEC_glReadPixels(char *commandbuf)
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
 void EXEC_glDrawPixels(char *commandbuf)
{
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glDrawPixels(*width, *height, *format, *type, (const GLvoid *)popBuf());
}


//258
 void EXEC_glGetBooleanv(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetBooleanv(*pname, (GLboolean *)popBuf());
}


//259
 void EXEC_glGetClipPlane(char *commandbuf)
{
	GLenum *plane = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetClipPlane(*plane, (GLdouble *)popBuf());
}


//260
 void EXEC_glGetDoublev(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetDoublev(*pname, (GLdouble *)popBuf());
}


//261
 void EXEC_glGetError(char *commandbuf)
{

	pushRet(glGetError());
}


//262
 void EXEC_glGetFloatv(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetFloatv(*pname, (GLfloat *)popBuf());
}


//263
 void EXEC_glGetIntegerv(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

    auto size   = getGetSize(*pname);
    auto params = new GLint[size];
    glGetIntegerv(*pname, params);
    pushRet(params, sizeof(GLint) * size);
}


//264
 void EXEC_glGetLightfv(char *commandbuf)
{
	GLenum *light = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetLightfv(*light, *pname, (GLfloat *)popBuf());
}


//265
 void EXEC_glGetLightiv(char *commandbuf)
{
	GLenum *light = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetLightiv(*light, *pname, (GLint *)popBuf());
}


//266
 void EXEC_glGetMapdv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *query = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetMapdv(*target, *query, (GLdouble *)popBuf());
}


//267
 void EXEC_glGetMapfv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *query = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetMapfv(*target, *query, (GLfloat *)popBuf());
}


//268
 void EXEC_glGetMapiv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *query = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetMapiv(*target, *query, (GLint *)popBuf());
}


//269
 void EXEC_glGetMaterialfv(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetMaterialfv(*face, *pname, (GLfloat *)popBuf());
}


//270
 void EXEC_glGetMaterialiv(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetMaterialiv(*face, *pname, (GLint *)popBuf());
}


//271
 void EXEC_glGetPixelMapfv(char *commandbuf)
{
	GLenum *map = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);

	glGetPixelMapfv(*map, (GLfloat *)popBuf());
}


//272
 void EXEC_glGetPixelMapuiv(char *commandbuf)
{
	GLenum *map = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);

	glGetPixelMapuiv(*map, (GLuint *)popBuf());
}


//273
 void EXEC_glGetPixelMapusv(char *commandbuf)
{
	GLenum *map = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);

	glGetPixelMapusv(*map, (GLushort *)popBuf());
}


//274
 void EXEC_glGetPolygonStipple(char *commandbuf)
{

	glGetPolygonStipple((GLubyte *)popBuf());
}


//275
 void EXEC_glGetString(char *commandbuf)
{
	GLenum *name = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

    auto str = (char*)glGetString(*name);
    pushRet(str, strlen(str)+1, false);
}


//276
 void EXEC_glGetTexEnvfv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetTexEnvfv(*target, *pname, (GLfloat *)popBuf());
}


//277
 void EXEC_glGetTexEnviv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetTexEnviv(*target, *pname, (GLint *)popBuf());
}


//278
 void EXEC_glGetTexGendv(char *commandbuf)
{
	GLenum *coord = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetTexGendv(*coord, *pname, (GLdouble *)popBuf());
}


//279
 void EXEC_glGetTexGenfv(char *commandbuf)
{
	GLenum *coord = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetTexGenfv(*coord, *pname, (GLfloat *)popBuf());
}


//280
 void EXEC_glGetTexGeniv(char *commandbuf)
{
	GLenum *coord = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetTexGeniv(*coord, *pname, (GLint *)popBuf());
}


//281
 void EXEC_glGetTexImage(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glGetTexImage(*target, *level, *format, *type, (GLvoid *)popBuf());
}


//282
 void EXEC_glGetTexParameterfv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetTexParameterfv(*target, *pname, (GLfloat *)popBuf());
}


//283
 void EXEC_glGetTexParameteriv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetTexParameteriv(*target, *pname, (GLint *)popBuf());
}


//284
 void EXEC_glGetTexLevelParameterfv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetTexLevelParameterfv(*target, *level, *pname, (GLfloat *)popBuf());
}


//285
 void EXEC_glGetTexLevelParameteriv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetTexLevelParameteriv(*target, *level, *pname, (GLint *)popBuf());
}


//286
 void EXEC_glIsEnabled(char *commandbuf)
{
	GLenum *cap = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);

	pushRet(glIsEnabled(*cap));
}


//287
 void EXEC_glIsList(char *commandbuf)
{
	GLuint *list = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

	pushRet(glIsList(*list));
}


//288
 void EXEC_glDepthRange(char *commandbuf)
{
	GLclampd *zNear = (GLclampd*)commandbuf;     commandbuf += sizeof(GLclampd);
	GLclampd *zFar = (GLclampd*)commandbuf;  commandbuf += sizeof(GLclampd);

	glDepthRange(*zNear, *zFar);
}


//289
 void EXEC_glFrustum(char *commandbuf)
{
	GLdouble *left = (GLdouble*)commandbuf;  commandbuf += sizeof(GLdouble);
	GLdouble *right = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *bottom = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *top = (GLdouble*)commandbuf;   commandbuf += sizeof(GLdouble);
	GLdouble *zNear = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *zFar = (GLdouble*)commandbuf;  commandbuf += sizeof(GLdouble);
	glFrustum(*left, *right, *bottom, *top, *zNear, *zFar);
}


//290
 void EXEC_glLoadIdentity(char *commandbuf)
{

	glLoadIdentity();
}


//291
 void EXEC_glLoadMatrixf(char *commandbuf)
{

	glLoadMatrixf((const GLfloat *)popBuf());
}


//292
 void EXEC_glLoadMatrixd(char *commandbuf)
{

	glLoadMatrixd((const GLdouble *)popBuf());
}


//293
 void EXEC_glMatrixMode(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glMatrixMode(*mode);
}


//294
 void EXEC_glMultMatrixf(char *commandbuf)
{

	glMultMatrixf((const GLfloat *)popBuf());
}


//295
 void EXEC_glMultMatrixd(char *commandbuf)
{

	glMultMatrixd((const GLdouble *)popBuf());
}


//296
 void EXEC_glOrtho(char *commandbuf)
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
 void EXEC_glPopMatrix(char *commandbuf)
{

	glPopMatrix();
}


//298
 void EXEC_glPushMatrix(char *commandbuf)
{

	glPushMatrix();
}


//299
 void EXEC_glRotated(char *commandbuf)
{
	GLdouble *angle = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glRotated(*angle, *x, *y, *z);
}


//300
 void EXEC_glRotatef(char *commandbuf)
{
	GLfloat *angle = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glRotatef(*angle, *x, *y, *z);
}


//301
 void EXEC_glScaled(char *commandbuf)
{
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glScaled(*x, *y, *z);
}


//302
 void EXEC_glScalef(char *commandbuf)
{
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glScalef(*x, *y, *z);
}


//303
 void EXEC_glTranslated(char *commandbuf)
{
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glTranslated(*x, *y, *z);
}


//304
 void EXEC_glTranslatef(char *commandbuf)
{
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glTranslatef(*x, *y, *z);
}


//305
 void EXEC_glViewport(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *height = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glViewport(*x, *y, *width, *height);
}


//306
 void EXEC_glArrayElement(char *commandbuf)
{
	GLint *i = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glArrayElement(*i);
}


//307
 void EXEC_glBindTexture(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *texture = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	glBindTexture(*target, *texture);
}


//moved glcolorpointer to be with glVertexPointer etc

//309
 void EXEC_glDisableClientState(char *commandbuf)
{
	GLenum *array = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glDisableClientState(*array);
}


//310
 void EXEC_glDrawArrays(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLint *first = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	//LOG("Starting glDrawArrays(%d, %d, %d)\n", *mode, *first, *count);

	glDrawArrays(*mode, *first, *count);

	//LOG("ok\n");
}


//311
 void EXEC_glDrawElements(char *commandbuf)
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
 void EXEC_glEdgeFlagPointer(char *commandbuf)
{
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glEdgeFlagPointer(*stride, (const GLvoid *)popBuf());
}


//313
 void EXEC_glEnableClientState(char *commandbuf)
{
	GLenum *array = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glEnableClientState(*array);
}


//314
 void EXEC_glIndexPointer(char *commandbuf)
{
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glIndexPointer(*type, *stride, (const GLvoid *)popBuf());
}


//315
 void EXEC_glIndexub(char *commandbuf)
{
	GLubyte *c = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);

	glIndexub(*c);
}


//316
 void EXEC_glIndexubv(char *commandbuf)
{

	glIndexubv((const GLubyte *)popBuf());
}


//317
 void EXEC_glInterleavedArrays(char *commandbuf)
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
 void EXEC_glNormalPointer(char *commandbuf)
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
 void EXEC_glPolygonOffset(char *commandbuf)
{
	GLfloat *factor = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *units = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glPolygonOffset(*factor, *units);
}









//308
 void EXEC_glColorPointer(char *commandbuf)
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
 void EXEC_glTexCoordPointer(char *commandbuf)
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
 void EXEC_glVertexPointer(char *commandbuf)
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
 void EXEC_glAreTexturesResident(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	pushRet(glAreTexturesResident(*n, (const GLuint *)popBuf(), (GLboolean *)popBuf()));
}


//323
 void EXEC_glCopyTexImage1D(char *commandbuf)
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
 void EXEC_glCopyTexImage2D(char *commandbuf)
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
 void EXEC_glCopyTexSubImage1D(char *commandbuf)
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
 void EXEC_glCopyTexSubImage2D(char *commandbuf)
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
 void EXEC_glDeleteTextures(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glDeleteTextures(*n, (const GLuint *)popBuf());
}


//328
 void EXEC_glGenTextures(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	glGenTextures(*n, (GLuint *)popBuf());
}


//329
 void EXEC_glGetPointerv(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetPointerv(*pname, (GLvoid **)popBuf());
}


//330
 void EXEC_glIsTexture(char *commandbuf)
{
	GLuint *texture = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	pushRet(glIsTexture(*texture));
}


//331
 void EXEC_glPrioritizeTextures(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glPrioritizeTextures(*n, (const GLuint *)popBuf(), (const GLclampf *)popBuf());
}


//332
 void EXEC_glTexSubImage1D(char *commandbuf)
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
 void EXEC_glTexSubImage2D(char *commandbuf)
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
 void EXEC_glPopClientAttrib(char *commandbuf)
{

	glPopClientAttrib();
}


//335
 void EXEC_glPushClientAttrib(char *commandbuf)
{
	GLbitfield *mask = (GLbitfield*)commandbuf;  commandbuf += sizeof(GLbitfield);

	glPushClientAttrib(*mask);
}


//336
 void EXEC_glBlendColor(char *commandbuf)
{
	GLclampf *red = (GLclampf*)commandbuf;   commandbuf += sizeof(GLclampf);
	GLclampf *green = (GLclampf*)commandbuf;     commandbuf += sizeof(GLclampf);
	GLclampf *blue = (GLclampf*)commandbuf;  commandbuf += sizeof(GLclampf);
	GLclampf *alpha = (GLclampf*)commandbuf;     commandbuf += sizeof(GLclampf);

	glBlendColor(*red, *green, *blue, *alpha);
}


//337
 void EXEC_glBlendEquation(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glBlendEquation(*mode);
}


//338
 void EXEC_glDrawRangeElements(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLuint *start = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLuint *end = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glDrawRangeElements(*mode, *start, *end, *count, *type, (const GLvoid *)popBuf());
}


//339
 void EXEC_glColorTable(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glColorTable(*target, *internalformat, *width, *format, *type, (const GLvoid *)popBuf());
}


//340
 void EXEC_glColorTableParameterfv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glColorTableParameterfv(*target, *pname, (const GLfloat *)popBuf());
}


//341
 void EXEC_glColorTableParameteriv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glColorTableParameteriv(*target, *pname, (const GLint *)popBuf());
}


//342
 void EXEC_glCopyColorTable(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glCopyColorTable(*target, *internalformat, *x, *y, *width);
}


//343
 void EXEC_glGetColorTable(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glGetColorTable(*target, *format, *type, (GLvoid *)popBuf());
}


//344
 void EXEC_glGetColorTableParameterfv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetColorTableParameterfv(*target, *pname, (GLfloat *)popBuf());
}


//345
 void EXEC_glGetColorTableParameteriv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetColorTableParameteriv(*target, *pname, (GLint *)popBuf());
}


//346
 void EXEC_glColorSubTable(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *start = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glColorSubTable(*target, *start, *count, *format, *type, (const GLvoid *)popBuf());
}


//347
 void EXEC_glCopyColorSubTable(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *start = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glCopyColorSubTable(*target, *start, *x, *y, *width);
}


//348
 void EXEC_glConvolutionFilter1D(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glConvolutionFilter1D(*target, *internalformat, *width, *format, *type, (const GLvoid *)popBuf());
}


//349
 void EXEC_glConvolutionFilter2D(char *commandbuf)
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
 void EXEC_glConvolutionParameterf(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *params = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	glConvolutionParameterf(*target, *pname, *params);
}


//351
 void EXEC_glConvolutionParameterfv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glConvolutionParameterfv(*target, *pname, (const GLfloat *)popBuf());
}


//352
 void EXEC_glConvolutionParameteri(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *params = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glConvolutionParameteri(*target, *pname, *params);
}


//353
 void EXEC_glConvolutionParameteriv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glConvolutionParameteriv(*target, *pname, (const GLint *)popBuf());
}


//354
 void EXEC_glCopyConvolutionFilter1D(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glCopyConvolutionFilter1D(*target, *internalformat, *x, *y, *width);
}


//355
 void EXEC_glCopyConvolutionFilter2D(char *commandbuf)
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
 void EXEC_glGetConvolutionFilter(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glGetConvolutionFilter(*target, *format, *type, (GLvoid *)popBuf());
}


//357
 void EXEC_glGetConvolutionParameterfv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetConvolutionParameterfv(*target, *pname, (GLfloat *)popBuf());
}


//358
 void EXEC_glGetConvolutionParameteriv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetConvolutionParameteriv(*target, *pname, (GLint *)popBuf());
}


//359
 void EXEC_glGetSeparableFilter(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glGetSeparableFilter(*target, *format, *type, (GLvoid *)popBuf(), (GLvoid *)popBuf(), (GLvoid *)popBuf());
}


//360
 void EXEC_glSeparableFilter2D(char *commandbuf)
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
 void EXEC_glGetHistogram(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLboolean *reset = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glGetHistogram(*target, *reset, *format, *type, (GLvoid *)popBuf());
}


//362
 void EXEC_glGetHistogramParameterfv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetHistogramParameterfv(*target, *pname, (GLfloat *)popBuf());
}


//363
 void EXEC_glGetHistogramParameteriv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetHistogramParameteriv(*target, *pname, (GLint *)popBuf());
}


//364
 void EXEC_glGetMinmax(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLboolean *reset = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glGetMinmax(*target, *reset, *format, *type, (GLvoid *)popBuf());
}


//365
 void EXEC_glGetMinmaxParameterfv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetMinmaxParameterfv(*target, *pname, (GLfloat *)popBuf());
}


//366
 void EXEC_glGetMinmaxParameteriv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetMinmaxParameteriv(*target, *pname, (GLint *)popBuf());
}


//367
 void EXEC_glHistogram(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLboolean *sink = (GLboolean*)commandbuf;    commandbuf += sizeof(GLboolean);

	glHistogram(*target, *width, *internalformat, *sink);
}


//368
 void EXEC_glMinmax(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLboolean *sink = (GLboolean*)commandbuf;    commandbuf += sizeof(GLboolean);

	glMinmax(*target, *internalformat, *sink);
}


//369
 void EXEC_glResetHistogram(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glResetHistogram(*target);
}


//370
 void EXEC_glResetMinmax(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glResetMinmax(*target);
}


//371
 void EXEC_glTexImage3D(char *commandbuf)
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
 void EXEC_glTexSubImage3D(char *commandbuf)
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
 void EXEC_glCopyTexSubImage3D(char *commandbuf)
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
 void EXEC_glActiveTexture(char *commandbuf)
{
	GLenum *texture = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);

	glActiveTexture(*texture);
}


//375
 void EXEC_glClientActiveTexture(char *commandbuf)
{
	GLenum *texture = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);

	glClientActiveTexture(*texture);
}


//376
 void EXEC_glMultiTexCoord1d(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLdouble *s = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glMultiTexCoord1d(*target, *s);
}


//377
 void EXEC_glMultiTexCoord1dv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord1dv(*target, (const GLdouble *)popBuf());
}


//378
 void EXEC_glMultiTexCoord1f(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glMultiTexCoord1f(*target, *s);
}


//379
 void EXEC_glMultiTexCoord1fv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord1fv(*target, (const GLfloat *)popBuf());
}


//380
 void EXEC_glMultiTexCoord1i(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *s = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glMultiTexCoord1i(*target, *s);
}


//381
 void EXEC_glMultiTexCoord1iv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord1iv(*target, (const GLint *)popBuf());
}


//382
 void EXEC_glMultiTexCoord1s(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLshort *s = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glMultiTexCoord1s(*target, *s);
}


//383
 void EXEC_glMultiTexCoord1sv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord1sv(*target, (const GLshort *)popBuf());
}


//384
 void EXEC_glMultiTexCoord2d(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLdouble *s = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *t = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glMultiTexCoord2d(*target, *s, *t);
}


//385
 void EXEC_glMultiTexCoord2dv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord2dv(*target, (const GLdouble *)popBuf());
}


//386
 void EXEC_glMultiTexCoord2f(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *t = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glMultiTexCoord2f(*target, *s, *t);
}


//387
 void EXEC_glMultiTexCoord2fv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord2fv(*target, (const GLfloat *)popBuf());
}


//388
 void EXEC_glMultiTexCoord2i(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *s = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *t = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glMultiTexCoord2i(*target, *s, *t);
}


//389
 void EXEC_glMultiTexCoord2iv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord2iv(*target, (const GLint *)popBuf());
}


//390
 void EXEC_glMultiTexCoord2s(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLshort *s = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *t = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glMultiTexCoord2s(*target, *s, *t);
}


//391
 void EXEC_glMultiTexCoord2sv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord2sv(*target, (const GLshort *)popBuf());
}


//392
 void EXEC_glMultiTexCoord3d(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLdouble *s = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *t = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *r = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glMultiTexCoord3d(*target, *s, *t, *r);
}


//393
 void EXEC_glMultiTexCoord3dv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord3dv(*target, (const GLdouble *)popBuf());
}


//394
 void EXEC_glMultiTexCoord3f(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *t = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *r = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glMultiTexCoord3f(*target, *s, *t, *r);
}


//395
 void EXEC_glMultiTexCoord3fv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord3fv(*target, (const GLfloat *)popBuf());
}


//396
 void EXEC_glMultiTexCoord3i(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *s = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *t = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *r = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glMultiTexCoord3i(*target, *s, *t, *r);
}


//397
 void EXEC_glMultiTexCoord3iv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord3iv(*target, (const GLint *)popBuf());
}


//398
 void EXEC_glMultiTexCoord3s(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLshort *s = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *t = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *r = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glMultiTexCoord3s(*target, *s, *t, *r);
}


//399
 void EXEC_glMultiTexCoord3sv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord3sv(*target, (const GLshort *)popBuf());
}


//400
 void EXEC_glMultiTexCoord4d(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLdouble *s = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *t = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *r = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *q = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glMultiTexCoord4d(*target, *s, *t, *r, *q);
}


//401
 void EXEC_glMultiTexCoord4dv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord4dv(*target, (const GLdouble *)popBuf());
}


//402
 void EXEC_glMultiTexCoord4f(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *t = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *r = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *q = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glMultiTexCoord4f(*target, *s, *t, *r, *q);
}


//403
 void EXEC_glMultiTexCoord4fv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord4fv(*target, (const GLfloat *)popBuf());
}


//404
 void EXEC_glMultiTexCoord4i(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *s = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *t = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *r = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *q = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glMultiTexCoord4i(*target, *s, *t, *r, *q);
}


//405
 void EXEC_glMultiTexCoord4iv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord4iv(*target, (const GLint *)popBuf());
}


//406
 void EXEC_glMultiTexCoord4s(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLshort *s = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *t = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *r = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *q = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glMultiTexCoord4s(*target, *s, *t, *r, *q);
}


//407
 void EXEC_glMultiTexCoord4sv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord4sv(*target, (const GLshort *)popBuf());
}


//408
 void EXEC_glLoadTransposeMatrixf(char *commandbuf)
{

	glLoadTransposeMatrixf((const GLfloat *)popBuf());
}


//409
 void EXEC_glLoadTransposeMatrixd(char *commandbuf)
{

	glLoadTransposeMatrixd((const GLdouble *)popBuf());
}


//410
 void EXEC_glMultTransposeMatrixf(char *commandbuf)
{

	glMultTransposeMatrixf((const GLfloat *)popBuf());
}


//411
 void EXEC_glMultTransposeMatrixd(char *commandbuf)
{

	glMultTransposeMatrixd((const GLdouble *)popBuf());
}


//412
 void EXEC_glSampleCoverage(char *commandbuf)
{
	GLclampf *value = (GLclampf*)commandbuf;     commandbuf += sizeof(GLclampf);
	GLboolean *invert = (GLboolean*)commandbuf;  commandbuf += sizeof(GLboolean);

	glSampleCoverage(*value, *invert);
}


//413
 void EXEC_glCompressedTexImage3D(char *commandbuf)
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
 void EXEC_glCompressedTexImage2D(char *commandbuf)
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
 void EXEC_glCompressedTexImage1D(char *commandbuf)
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
 void EXEC_glCompressedTexSubImage3D(char *commandbuf)
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
 void EXEC_glCompressedTexSubImage2D(char *commandbuf)
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
 void EXEC_glCompressedTexSubImage1D(char *commandbuf)
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
 void EXEC_glGetCompressedTexImage(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glGetCompressedTexImage(*target, *level, (GLvoid *)popBuf());
}


//420
 void EXEC_glBlendFuncSeparate(char *commandbuf)
{
	GLenum *sfactorRGB = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *dfactorRGB = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *sfactorAlpha = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *dfactorAlpha = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glBlendFuncSeparate(*sfactorRGB, *dfactorRGB, *sfactorAlpha, *dfactorAlpha);
}


//421
 void EXEC_glFogCoordf(char *commandbuf)
{
	GLfloat *coord = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glFogCoordf(*coord);
}


//422
 void EXEC_glFogCoordfv(char *commandbuf)
{
	glFogCoordfv((const GLfloat *)popBuf());
}


//423
 void EXEC_glFogCoordd(char *commandbuf)
{
	GLdouble *coord = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glFogCoordd(*coord);
}


//424
 void EXEC_glFogCoorddv(char *commandbuf)
{

	glFogCoorddv((const GLdouble *)popBuf());
}


//425
 void EXEC_glFogCoordPointer(char *commandbuf)
{
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glFogCoordPointer(*type, *stride, (const GLvoid *)popBuf());
}


//426
 void EXEC_glMultiDrawArrays(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *primcount = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glMultiDrawArrays(*mode, (GLint *)popBuf(), (GLsizei *)popBuf(), *primcount);
}


//427
 void EXEC_glMultiDrawElements(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *primcount = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glMultiDrawElements(*mode, (GLsizei *)popBuf(), *type, (const GLvoid **)popBuf(), *primcount);
}


//428
 void EXEC_glPointParameterf(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glPointParameterf(*pname, *param);
}


//429
 void EXEC_glPointParameterfv(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glPointParameterfv(*pname, (GLfloat *)popBuf());
}


//430
 void EXEC_glPointParameteri(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	//TODO: why does this exist?
	#ifndef SYMPHONY
	glPointParameteri(*pname, *param);
	#endif
}


//431
 void EXEC_glPointParameteriv(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	//TODO: why does this exist?
	#ifndef SYMPHONY
	glPointParameteriv(*pname, (GLint *)popBuf());
	#endif
}


//432
 void EXEC_glSecondaryColor3b(char *commandbuf)
{
	GLbyte *red = (GLbyte*)commandbuf;   commandbuf += sizeof(GLbyte);
	GLbyte *green = (GLbyte*)commandbuf;     commandbuf += sizeof(GLbyte);
	GLbyte *blue = (GLbyte*)commandbuf;  commandbuf += sizeof(GLbyte);

	glSecondaryColor3b(*red, *green, *blue);
}


//433
 void EXEC_glSecondaryColor3bv(char *commandbuf)
{

	glSecondaryColor3bv((const GLbyte *)popBuf());
}


//434
 void EXEC_glSecondaryColor3d(char *commandbuf)
{
	GLdouble *red = (GLdouble*)commandbuf;   commandbuf += sizeof(GLdouble);
	GLdouble *green = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *blue = (GLdouble*)commandbuf;  commandbuf += sizeof(GLdouble);

	glSecondaryColor3d(*red, *green, *blue);
}


//435
 void EXEC_glSecondaryColor3dv(char *commandbuf)
{

	glSecondaryColor3dv((const GLdouble *)popBuf());
}


//436
 void EXEC_glSecondaryColor3f(char *commandbuf)
{
	GLfloat *red = (GLfloat*)commandbuf;     commandbuf += sizeof(GLfloat);
	GLfloat *green = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *blue = (GLfloat*)commandbuf;    commandbuf += sizeof(GLfloat);

	glSecondaryColor3f(*red, *green, *blue);
}


//437
 void EXEC_glSecondaryColor3fv(char *commandbuf)
{

	glSecondaryColor3fv((const GLfloat *)popBuf());
}


//438
 void EXEC_glSecondaryColor3i(char *commandbuf)
{
	GLint *red = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *green = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *blue = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glSecondaryColor3i(*red, *green, *blue);
}


//439
 void EXEC_glSecondaryColor3iv(char *commandbuf)
{

	glSecondaryColor3iv((const GLint *)popBuf());
}


//440
 void EXEC_glSecondaryColor3s(char *commandbuf)
{
	GLshort *red = (GLshort*)commandbuf;     commandbuf += sizeof(GLshort);
	GLshort *green = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *blue = (GLshort*)commandbuf;    commandbuf += sizeof(GLshort);

	glSecondaryColor3s(*red, *green, *blue);
}


//441
 void EXEC_glSecondaryColor3sv(char *commandbuf)
{

	glSecondaryColor3sv((const GLshort *)popBuf());
}


//442
 void EXEC_glSecondaryColor3ub(char *commandbuf)
{
	GLubyte *red = (GLubyte*)commandbuf;     commandbuf += sizeof(GLubyte);
	GLubyte *green = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *blue = (GLubyte*)commandbuf;    commandbuf += sizeof(GLubyte);

	glSecondaryColor3ub(*red, *green, *blue);
}


//443
 void EXEC_glSecondaryColor3ubv(char *commandbuf)
{

	glSecondaryColor3ubv((const GLubyte *)popBuf());
}


//444
 void EXEC_glSecondaryColor3ui(char *commandbuf)
{
	GLuint *red = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *green = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLuint *blue = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

	glSecondaryColor3ui(*red, *green, *blue);
}


//445
 void EXEC_glSecondaryColor3uiv(char *commandbuf)
{

	glSecondaryColor3uiv((const GLuint *)popBuf());
}


//446
 void EXEC_glSecondaryColor3us(char *commandbuf)
{
	GLushort *red = (GLushort*)commandbuf;   commandbuf += sizeof(GLushort);
	GLushort *green = (GLushort*)commandbuf;     commandbuf += sizeof(GLushort);
	GLushort *blue = (GLushort*)commandbuf;  commandbuf += sizeof(GLushort);

	glSecondaryColor3us(*red, *green, *blue);
}


//447
 void EXEC_glSecondaryColor3usv(char *commandbuf)
{

	glSecondaryColor3usv((const GLushort *)popBuf());
}


//448
 void EXEC_glSecondaryColorPointer(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glSecondaryColorPointer(*size, *type, *stride, (GLvoid *)popBuf());
}


//449
 void EXEC_glWindowPos2d(char *commandbuf)
{
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glWindowPos2d(*x, *y);
}


//450
 void EXEC_glWindowPos2dv(char *commandbuf)
{

	glWindowPos2dv((const GLdouble *)popBuf());
}


//451
 void EXEC_glWindowPos2f(char *commandbuf)
{
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glWindowPos2f(*x, *y);
}


//452
 void EXEC_glWindowPos2fv(char *commandbuf)
{

	glWindowPos2fv((const GLfloat *)popBuf());
}


//453
 void EXEC_glWindowPos2i(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glWindowPos2i(*x, *y);
}


//454
 void EXEC_glWindowPos2iv(char *commandbuf)
{

	glWindowPos2iv((const GLint *)popBuf());
}


//455
 void EXEC_glWindowPos2s(char *commandbuf)
{
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glWindowPos2s(*x, *y);
}


//456
 void EXEC_glWindowPos2sv(char *commandbuf)
{

	glWindowPos2sv((const GLshort *)popBuf());
}


//457
 void EXEC_glWindowPos3d(char *commandbuf)
{
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glWindowPos3d(*x, *y, *z);
}


//458
 void EXEC_glWindowPos3dv(char *commandbuf)
{

	glWindowPos3dv((const GLdouble *)popBuf());
}


//459
 void EXEC_glWindowPos3f(char *commandbuf)
{
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glWindowPos3f(*x, *y, *z);
}


//460
 void EXEC_glWindowPos3fv(char *commandbuf)
{

	glWindowPos3fv((const GLfloat *)popBuf());
}


//461
 void EXEC_glWindowPos3i(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *z = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glWindowPos3i(*x, *y, *z);
}


//462
 void EXEC_glWindowPos3iv(char *commandbuf)
{

	glWindowPos3iv((const GLint *)popBuf());
}


//463
 void EXEC_glWindowPos3s(char *commandbuf)
{
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *z = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glWindowPos3s(*x, *y, *z);
}


//464
 void EXEC_glWindowPos3sv(char *commandbuf)
{

	glWindowPos3sv((const GLshort *)popBuf());
}


//465
 void EXEC_glBindBuffer(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *buffer = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	glBindBuffer(*target, *buffer);
}


//466
 void EXEC_glBufferData(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizeiptr *size = (GLsizeiptr*)commandbuf;  commandbuf += sizeof(GLsizeiptr);
	GLenum *usage = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glBufferData(*target, *size, (const GLvoid *)popBuf(), *usage);
}


//467
 void EXEC_glBufferSubData(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLintptr *offset = (GLintptr*)commandbuf;    commandbuf += sizeof(GLintptr);
	GLsizeiptr *size = (GLsizeiptr*)commandbuf;  commandbuf += sizeof(GLsizeiptr);

	glBufferSubData(*target, *offset, *size, (const GLvoid *)popBuf());
}


//468
 void EXEC_glDeleteBuffers(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glDeleteBuffers(*n, (const GLuint *)popBuf());
}


//469
 void EXEC_glGenBuffers(char *commandbuf)
{
    auto    n   = *(GLsizei*)commandbuf;
    auto    buf = new GLuint[n];
    glGenBuffers(n, buf);
    pushRet(buf, n * sizeof(GLuint));
}


//470
 void EXEC_glGetBufferParameteriv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetBufferParameteriv(*target, *pname, (GLint *)popBuf());
}


//471
 void EXEC_glGetBufferPointerv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetBufferPointerv(*target, *pname, (GLvoid **)popBuf());
}


//472
 void EXEC_glGetBufferSubData(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLintptr *offset = (GLintptr*)commandbuf;    commandbuf += sizeof(GLintptr);
	GLsizeiptr *size = (GLsizeiptr*)commandbuf;  commandbuf += sizeof(GLsizeiptr);

	glGetBufferSubData(*target, *offset, *size, (GLvoid *)popBuf());
}


//473
 void EXEC_glIsBuffer(char *commandbuf)
{
	GLuint *buffer = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	pushRet(glIsBuffer(*buffer));
}


//474
 void EXEC_glMapBuffer(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *access = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	pushRet((const GLubyte*)glMapBuffer(*target, *access));

}


//475
 void EXEC_glUnmapBuffer(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	pushRet(glUnmapBuffer(*target));
}


//476
 void EXEC_glGenQueries(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glGenQueries(*n, (GLuint *)popBuf());
}


//477
 void EXEC_glDeleteQueries(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glDeleteQueries(*n, (const GLuint *)popBuf());
}


//478
 void EXEC_glIsQuery(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	pushRet(glIsQuery(*id));
}


//479
 void EXEC_glBeginQuery(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	glBeginQuery(*target, *id);
}


//480
 void EXEC_glEndQuery(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glEndQuery(*target);
}


//481
 void EXEC_glGetQueryiv(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetQueryiv(*target, *pname, (GLint *)popBuf());
}


//482
 void EXEC_glGetQueryObjectiv(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetQueryObjectiv(*id, *pname, (GLint *)popBuf());
}


//483
 void EXEC_glGetQueryObjectuiv(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetQueryObjectuiv(*id, *pname, (GLuint *)popBuf());
}


//484
 void EXEC_glBlendEquationSeparate(char *commandbuf)
{
	GLenum *modeRGB = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);
	GLenum *modeA = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glBlendEquationSeparate(*modeRGB, *modeA);
}


//485
 void EXEC_glDrawBuffers(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glDrawBuffers(*n, (const GLenum *)popBuf());
}


//486
 void EXEC_glStencilFuncSeparate(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *func = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLint *ref = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLuint *mask = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

	glStencilFuncSeparate(*face, *func, *ref, *mask);
}


//487
 void EXEC_glStencilOpSeparate(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *sfail = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *zfail = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *zpass = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glStencilOpSeparate(*face, *sfail, *zfail, *zpass);
}


//488
 void EXEC_glStencilMaskSeparate(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLuint *mask = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

	glStencilMaskSeparate(*face, *mask);
}


//489
 void EXEC_glAttachShader(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *shader = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	glAttachShader(*program, *shader);
}


//490
 void EXEC_glBindAttribLocation(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glBindAttribLocation(*program, *index, (const GLchar *)popBuf());
}


//491
 void EXEC_glCompileShader(char *commandbuf)
{
	GLuint *shader = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	glCompileShader(*shader);
}


//492
 void EXEC_glCreateProgram(char *commandbuf)
{

	pushRet(glCreateProgram());
}


//493
 void EXEC_glCreateShader(char *commandbuf)
{
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	pushRet(glCreateShader(*type));
}


//494
 void EXEC_glDeleteProgram(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	glDeleteProgram(*program);
}


//495
 void EXEC_glDeleteShader(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	glDeleteShader(*program);
}


//496
 void EXEC_glDetachShader(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *shader = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	glDetachShader(*program, *shader);
}


//497
 void EXEC_glDisableVertexAttribArray(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glDisableVertexAttribArray(*index);
}


//498
 void EXEC_glEnableVertexAttribArray(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glEnableVertexAttribArray(*index);
}


//499
 void EXEC_glGetActiveAttrib(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei  *bufSize = (GLsizei *)commandbuf;   commandbuf += sizeof(GLsizei );

	glGetActiveAttrib(*program, *index, *bufSize, (GLsizei *)popBuf(), (GLint *)popBuf(), (GLenum *)popBuf(), (GLchar *)popBuf());
}


//500
 void EXEC_glGetActiveUniform(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *bufSize = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);

	glGetActiveUniform(*program, *index, *bufSize, (GLsizei *)popBuf(), (GLint *)popBuf(), (GLenum *)popBuf(), (GLchar *)popBuf());
}


//501
 void EXEC_glGetAttachedShaders(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLsizei *maxCount = (GLsizei*)commandbuf;    commandbuf += sizeof(GLsizei);

	glGetAttachedShaders(*program, *maxCount, (GLsizei *)popBuf(), (GLuint *)popBuf());
}


//502
 void EXEC_glGetAttribLocation(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	pushRet(glGetAttribLocation(*program, (const GLchar *)popBuf()));
}


//503
 void EXEC_glGetProgramiv(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetProgramiv(*program, *pname, (GLint *)popBuf());
}


//504
 void EXEC_glGetProgramInfoLog(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLsizei *bufSize = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);

	glGetProgramInfoLog(*program, *bufSize, (GLsizei *)popBuf(), (GLchar *)popBuf());
}


//505
 void EXEC_glGetShaderiv(char *commandbuf)
{
	GLuint *shader = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint   *params = (GLint *)popBuf();
	glGetShaderiv(*shader, *pname, params);
	pushRet(*params);
}


//506
 void EXEC_glGetShaderInfoLog(char *commandbuf)
{
    auto    shader      = (GLuint*  )commandbuf;
    commandbuf         += sizeof(GLuint);
    auto    maxLength   = (GLsizei* )commandbuf;
    commandbuf         += sizeof(GLsizei);
    auto    ret_size    = sizeof(GLsizei) + *maxLength;
    auto    ret         = new GLchar[ret_size];
    auto    length      = (GLsizei*)ret;
    auto    infoLog     = ret + sizeof(GLsizei);
    glGetShaderInfoLog(*shader, *maxLength, length, infoLog);
    pushRet(ret, ret_size);
}


//507
 void EXEC_glGetShaderSource(char *commandbuf)
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
 void EXEC_glGetUniformLocation(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	pushRet(glGetUniformLocation(*program, (const GLchar *)popBuf()));
}


//509
 void EXEC_glGetUniformfv(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glGetUniformfv(*program, *location, (GLfloat *)popBuf());
}


//510
 void EXEC_glGetUniformiv(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glGetUniformiv(*program, *location, (GLint *)popBuf());
}


//511
 void EXEC_glGetVertexAttribdv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetVertexAttribdv(*index, *pname, (GLdouble *)popBuf());
}


//512
 void EXEC_glGetVertexAttribfv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetVertexAttribfv(*index, *pname, (GLfloat *)popBuf());
}


//513
 void EXEC_glGetVertexAttribiv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetVertexAttribiv(*index, *pname, (GLint *)popBuf());
}


//514
 void EXEC_glGetVertexAttribPointerv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetVertexAttribPointerv(*index, *pname, (GLvoid **)popBuf());
}


//515
 void EXEC_glIsProgram(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	pushRet(glIsProgram(*program));
}


//516
 void EXEC_glIsShader(char *commandbuf)
{
	GLuint *shader = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	pushRet(glIsShader(*shader));
}


//517
 void EXEC_glLinkProgram(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	glLinkProgram(*program);
}


//518
 void EXEC_glShaderSource(char *commandbuf)
{
    auto    shader      = (GLuint*  )commandbuf;
    commandbuf         += sizeof(GLuint);
    GLsizei count       = 1;
    auto    source      = (GLchar*  )commandbuf;
    const GLchar *string[1]{ source };
    auto    length      = nullptr;
	glShaderSource(*shader, count, string, length);
}


//519
 void EXEC_glUseProgram(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	glUseProgram(*program);
}


//520
 void EXEC_glUniform1f(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLfloat *v0 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	glUniform1f(*location, *v0);
}


//521
 void EXEC_glUniform2f(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLfloat *v0 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *v1 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	glUniform2f(*location, *v0, *v1);
}


//522
 void EXEC_glUniform3f(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLfloat *v0 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *v1 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *v2 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	glUniform3f(*location, *v0, *v1, *v2);
}


//523
 void EXEC_glUniform4f(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLfloat *v0 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *v1 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *v2 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *v3 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	glUniform4f(*location, *v0, *v1, *v2, *v3);
}


//524
 void EXEC_glUniform1i(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLint *v0 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glUniform1i(*location, *v0);
}


//525
 void EXEC_glUniform2i(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLint *v0 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *v1 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glUniform2i(*location, *v0, *v1);
}


//526
 void EXEC_glUniform3i(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLint *v0 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *v1 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *v2 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glUniform3i(*location, *v0, *v1, *v2);
}


//527
 void EXEC_glUniform4i(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLint *v0 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *v1 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *v2 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *v3 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glUniform4i(*location, *v0, *v1, *v2, *v3);
}


//528
 void EXEC_glUniform1fv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glUniform1fv(*location, *count, (const GLfloat *)popBuf());
}


//529
 void EXEC_glUniform2fv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glUniform2fv(*location, *count, (const GLfloat *)popBuf());
}


//530
 void EXEC_glUniform3fv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glUniform3fv(*location, *count, (const GLfloat *)popBuf());
}


//531
 void EXEC_glUniform4fv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glUniform4fv(*location, *count, (const GLfloat *)popBuf());
}


//532
 void EXEC_glUniform1iv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glUniform1iv(*location, *count, (const GLint *)popBuf());
}


//533
 void EXEC_glUniform2iv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glUniform2iv(*location, *count, (const GLint *)popBuf());
}


//534
 void EXEC_glUniform3iv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glUniform3iv(*location, *count, (const GLint *)popBuf());
}


//535
 void EXEC_glUniform4iv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glUniform4iv(*location, *count, (const GLint *)popBuf());
}


//536
 void EXEC_glUniformMatrix2fv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLboolean *transpose = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);

	glUniformMatrix2fv(*location, *count, *transpose, (const GLfloat *)popBuf());
}


//537
 void EXEC_glUniformMatrix3fv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLboolean *transpose = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);

	glUniformMatrix3fv(*location, *count, *transpose, (const GLfloat *)popBuf());
}


//538
 void EXEC_glUniformMatrix4fv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLboolean *transpose = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);

	glUniformMatrix4fv(*location, *count, *transpose, (const GLfloat *)popBuf());
}


//539
 void EXEC_glValidateProgram(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	glValidateProgram(*program);
}


//540
 void EXEC_glVertexAttrib1d(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glVertexAttrib1d(*index, *x);
}


//541
 void EXEC_glVertexAttrib1dv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib1dv(*index, (const GLdouble *)popBuf());
}


//542
 void EXEC_glVertexAttrib1f(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glVertexAttrib1f(*index, *x);
}


//543
 void EXEC_glVertexAttrib1fv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib1fv(*index, (const GLfloat *)popBuf());
}


//544
 void EXEC_glVertexAttrib1s(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glVertexAttrib1s(*index, *x);
}


//545
 void EXEC_glVertexAttrib1sv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib1sv(*index, (const GLshort *)popBuf());
}


//546
 void EXEC_glVertexAttrib2d(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glVertexAttrib2d(*index, *x, *y);
}


//547
 void EXEC_glVertexAttrib2dv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib2dv(*index, (const GLdouble *)popBuf());
}


//548
 void EXEC_glVertexAttrib2f(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glVertexAttrib2f(*index, *x, *y);
}


//549
 void EXEC_glVertexAttrib2fv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib2fv(*index, (const GLfloat *)popBuf());
}


//550
 void EXEC_glVertexAttrib2s(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glVertexAttrib2s(*index, *x, *y);
}


//551
 void EXEC_glVertexAttrib2sv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib2sv(*index, (const GLshort *)popBuf());
}


//552
 void EXEC_glVertexAttrib3d(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glVertexAttrib3d(*index, *x, *y, *z);
}


//553
 void EXEC_glVertexAttrib3dv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib3dv(*index, (const GLdouble *)popBuf());
}


//554
 void EXEC_glVertexAttrib3f(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glVertexAttrib3f(*index, *x, *y, *z);
}


//555
 void EXEC_glVertexAttrib3fv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib3fv(*index, (const GLfloat *)popBuf());
}


//556
 void EXEC_glVertexAttrib3s(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *z = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glVertexAttrib3s(*index, *x, *y, *z);
}


//557
 void EXEC_glVertexAttrib3sv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib3sv(*index, (const GLshort *)popBuf());
}


//558
 void EXEC_glVertexAttrib4Nbv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4Nbv(*index, (const GLbyte *)popBuf());
}


//559
 void EXEC_glVertexAttrib4Niv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4Niv(*index, (const GLint *)popBuf());
}


//560
 void EXEC_glVertexAttrib4Nsv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4Nsv(*index, (const GLshort *)popBuf());
}


//561
 void EXEC_glVertexAttrib4Nub(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLubyte *x = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *y = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *z = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *w = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);

	glVertexAttrib4Nub(*index, *x, *y, *z, *w);
}


//562
 void EXEC_glVertexAttrib4Nubv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4Nubv(*index, (const GLubyte *)popBuf());
}


//563
 void EXEC_glVertexAttrib4Nuiv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4Nuiv(*index, (const GLuint *)popBuf());
}


//564
 void EXEC_glVertexAttrib4Nusv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4Nusv(*index, (const GLushort *)popBuf());
}


//565
 void EXEC_glVertexAttrib4bv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4bv(*index, (const GLbyte *)popBuf());
}


//566
 void EXEC_glVertexAttrib4d(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *w = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glVertexAttrib4d(*index, *x, *y, *z, *w);
}


//567
 void EXEC_glVertexAttrib4dv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4dv(*index, (const GLdouble *)popBuf());
}


//568
 void EXEC_glVertexAttrib4f(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *w = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glVertexAttrib4f(*index, *x, *y, *z, *w);
}


//569
 void EXEC_glVertexAttrib4fv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4fv(*index, (const GLfloat *)popBuf());
}


//570
 void EXEC_glVertexAttrib4iv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4iv(*index, (const GLint *)popBuf());
}


//571
 void EXEC_glVertexAttrib4s(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *z = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *w = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glVertexAttrib4s(*index, *x, *y, *z, *w);
}


//572
 void EXEC_glVertexAttrib4sv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4sv(*index, (const GLshort *)popBuf());
}


//573
 void EXEC_glVertexAttrib4ubv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4ubv(*index, (const GLubyte *)popBuf());
}


//574
 void EXEC_glVertexAttrib4uiv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4uiv(*index, (const GLuint *)popBuf());
}


//575
 void EXEC_glVertexAttrib4usv(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4usv(*index, (const GLushort *)popBuf());
}


//576
 void EXEC_glVertexAttribPointer(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLboolean *normalized = (GLboolean*)commandbuf;  commandbuf += sizeof(GLboolean);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glVertexAttribPointer(*index, *size, *type, *normalized, *stride, (const GLvoid *)popBuf());
}


//577
 void EXEC_glUniformMatrix2x3fv(char *commandbuf)
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
 void EXEC_glUniformMatrix3x2fv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLboolean *transpose = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);

	#ifndef SYMPHONY
	glUniformMatrix3x2fv(*location, *count, *transpose, (const GLfloat *)popBuf());
	#endif
}


//579
 void EXEC_glUniformMatrix2x4fv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLboolean *transpose = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);

	#ifndef SYMPHONY
	glUniformMatrix2x4fv(*location, *count, *transpose, (const GLfloat *)popBuf());
	#endif
}


//580
 void EXEC_glUniformMatrix4x2fv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLboolean *transpose = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);

	#ifndef SYMPHONY
	glUniformMatrix4x2fv(*location, *count, *transpose, (const GLfloat *)popBuf());
	#endif
}


//581
 void EXEC_glUniformMatrix3x4fv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLboolean *transpose = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);

	#ifndef SYMPHONY
	glUniformMatrix3x4fv(*location, *count, *transpose, (const GLfloat *)popBuf());
	#endif
}


//582
 void EXEC_glUniformMatrix4x3fv(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLboolean *transpose = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);

	#ifndef SYMPHONY
	glUniformMatrix4x3fv(*location, *count, *transpose, (const GLfloat *)popBuf());
	#endif
}


//374
 void EXEC_glActiveTextureARB(char *commandbuf)
{
	GLenum *texture = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);

	glActiveTextureARB(*texture);
}


//375
 void EXEC_glClientActiveTextureARB(char *commandbuf)
{
	GLenum *texture = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);

	glClientActiveTextureARB(*texture);
}


//376
 void EXEC_glMultiTexCoord1dARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLdouble *s = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glMultiTexCoord1dARB(*target, *s);
}


//377
 void EXEC_glMultiTexCoord1dvARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord1dvARB(*target, (const GLdouble *)popBuf());
}


//378
 void EXEC_glMultiTexCoord1fARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glMultiTexCoord1fARB(*target, *s);
}


//379
 void EXEC_glMultiTexCoord1fvARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord1fvARB(*target, (const GLfloat *)popBuf());
}


//380
 void EXEC_glMultiTexCoord1iARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *s = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glMultiTexCoord1iARB(*target, *s);
}


//381
 void EXEC_glMultiTexCoord1ivARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord1ivARB(*target, (const GLint *)popBuf());
}


//382
 void EXEC_glMultiTexCoord1sARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLshort *s = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glMultiTexCoord1sARB(*target, *s);
}


//383
 void EXEC_glMultiTexCoord1svARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord1svARB(*target, (const GLshort *)popBuf());
}


//384
 void EXEC_glMultiTexCoord2dARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLdouble *s = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *t = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glMultiTexCoord2dARB(*target, *s, *t);
}


//385
 void EXEC_glMultiTexCoord2dvARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord2dvARB(*target, (const GLdouble *)popBuf());
}


//386
 void EXEC_glMultiTexCoord2fARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *t = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glMultiTexCoord2fARB(*target, *s, *t);
}


//387
 void EXEC_glMultiTexCoord2fvARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord2fvARB(*target, (const GLfloat *)popBuf());
}


//388
 void EXEC_glMultiTexCoord2iARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *s = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *t = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glMultiTexCoord2iARB(*target, *s, *t);
}


//389
 void EXEC_glMultiTexCoord2ivARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord2ivARB(*target, (const GLint *)popBuf());
}


//390
 void EXEC_glMultiTexCoord2sARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLshort *s = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *t = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glMultiTexCoord2sARB(*target, *s, *t);
}


//391
 void EXEC_glMultiTexCoord2svARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord2svARB(*target, (const GLshort *)popBuf());
}


//392
 void EXEC_glMultiTexCoord3dARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLdouble *s = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *t = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *r = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glMultiTexCoord3dARB(*target, *s, *t, *r);
}


//393
 void EXEC_glMultiTexCoord3dvARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord3dvARB(*target, (const GLdouble *)popBuf());
}


//394
 void EXEC_glMultiTexCoord3fARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *t = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *r = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glMultiTexCoord3fARB(*target, *s, *t, *r);
}


//395
 void EXEC_glMultiTexCoord3fvARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord3fvARB(*target, (const GLfloat *)popBuf());
}


//396
 void EXEC_glMultiTexCoord3iARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *s = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *t = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *r = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glMultiTexCoord3iARB(*target, *s, *t, *r);
}


//397
 void EXEC_glMultiTexCoord3ivARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord3ivARB(*target, (const GLint *)popBuf());
}


//398
 void EXEC_glMultiTexCoord3sARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLshort *s = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *t = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *r = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glMultiTexCoord3sARB(*target, *s, *t, *r);
}


//399
 void EXEC_glMultiTexCoord3svARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord3svARB(*target, (const GLshort *)popBuf());
}


//400
 void EXEC_glMultiTexCoord4dARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLdouble *s = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *t = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *r = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *q = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glMultiTexCoord4dARB(*target, *s, *t, *r, *q);
}


//401
 void EXEC_glMultiTexCoord4dvARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord4dvARB(*target, (const GLdouble *)popBuf());
}


//402
 void EXEC_glMultiTexCoord4fARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *t = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *r = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *q = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glMultiTexCoord4fARB(*target, *s, *t, *r, *q);
}


//403
 void EXEC_glMultiTexCoord4fvARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord4fvARB(*target, (const GLfloat *)popBuf());
}


//404
 void EXEC_glMultiTexCoord4iARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *s = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *t = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *r = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *q = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glMultiTexCoord4iARB(*target, *s, *t, *r, *q);
}


//405
 void EXEC_glMultiTexCoord4ivARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord4ivARB(*target, (const GLint *)popBuf());
}


//406
 void EXEC_glMultiTexCoord4sARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLshort *s = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *t = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *r = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *q = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glMultiTexCoord4sARB(*target, *s, *t, *r, *q);
}


//407
 void EXEC_glMultiTexCoord4svARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glMultiTexCoord4svARB(*target, (const GLshort *)popBuf());
}


//617
 void EXEC_glLoadTransposeMatrixfARB(char *commandbuf)
{

	glLoadTransposeMatrixfARB((GLfloat *)popBuf());
}


//618
 void EXEC_glLoadTransposeMatrixdARB(char *commandbuf)
{

	glLoadTransposeMatrixdARB((GLdouble *)popBuf());
}


//619
 void EXEC_glMultTransposeMatrixfARB(char *commandbuf)
{

	glMultTransposeMatrixfARB((GLfloat *)popBuf());
}


//620
 void EXEC_glMultTransposeMatrixdARB(char *commandbuf)
{

	glMultTransposeMatrixdARB((GLdouble *)popBuf());
}


//621
 void EXEC_glSampleCoverageARB(char *commandbuf)
{
	GLclampf *value = (GLclampf*)commandbuf;     commandbuf += sizeof(GLclampf);
	GLboolean *invert = (GLboolean*)commandbuf;  commandbuf += sizeof(GLboolean);

	glSampleCoverageARB(*value, *invert);
}


//622
 void EXEC_glCompressedTexImage3DARB(char *commandbuf)
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
 void EXEC_glCompressedTexImage2DARB(char *commandbuf)
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
 void EXEC_glCompressedTexImage1DARB(char *commandbuf)
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
 void EXEC_glCompressedTexSubImage3DARB(char *commandbuf)
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
 void EXEC_glCompressedTexSubImage2DARB(char *commandbuf)
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
 void EXEC_glCompressedTexSubImage1DARB(char *commandbuf)
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
 void EXEC_glGetCompressedTexImageARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *level = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glGetCompressedTexImageARB(*target, *level, (GLvoid *)popBuf());
}


//629
 void EXEC_glPointParameterfARB(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glPointParameterfARB(*pname, *param);
}


//630
 void EXEC_glPointParameterfvARB(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glPointParameterfvARB(*pname, (GLfloat *)popBuf());
}


//631
 void EXEC_glWeightbvARB(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glWeightbvARB(*size, (GLbyte *)popBuf());
}


//632
 void EXEC_glWeightsvARB(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glWeightsvARB(*size, (GLshort *)popBuf());
}


//633
 void EXEC_glWeightivARB(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glWeightivARB(*size, (GLint *)popBuf());
}


//634
 void EXEC_glWeightfvARB(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glWeightfvARB(*size, (GLfloat *)popBuf());
}


//635
 void EXEC_glWeightdvARB(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glWeightdvARB(*size, (GLdouble *)popBuf());
}


//636
 void EXEC_glWeightubvARB(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glWeightubvARB(*size, (GLubyte *)popBuf());
}


//637
 void EXEC_glWeightusvARB(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glWeightusvARB(*size, (GLushort *)popBuf());
}


//638
 void EXEC_glWeightuivARB(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glWeightuivARB(*size, (GLuint *)popBuf());
}


//639
 void EXEC_glWeightPointerARB(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glWeightPointerARB(*size, *type, *stride, (GLvoid *)popBuf());
}


//640
 void EXEC_glVertexBlendARB(char *commandbuf)
{
	GLint *count = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glVertexBlendARB(*count);
}


//641
 void EXEC_glCurrentPaletteMatrixARB(char *commandbuf)
{
	GLint *index = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glCurrentPaletteMatrixARB(*index);
}


//642
 void EXEC_glMatrixIndexubvARB(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glMatrixIndexubvARB(*size, (GLubyte *)popBuf());
}


//643
 void EXEC_glMatrixIndexusvARB(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glMatrixIndexusvARB(*size, (GLushort *)popBuf());
}


//644
 void EXEC_glMatrixIndexuivARB(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glMatrixIndexuivARB(*size, (GLuint *)popBuf());
}


//645
 void EXEC_glMatrixIndexPointerARB(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glMatrixIndexPointerARB(*size, *type, *stride, (GLvoid *)popBuf());
}


//646
 void EXEC_glWindowPos2dARB(char *commandbuf)
{
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glWindowPos2dARB(*x, *y);
}


//647
 void EXEC_glWindowPos2fARB(char *commandbuf)
{
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glWindowPos2fARB(*x, *y);
}


//648
 void EXEC_glWindowPos2iARB(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glWindowPos2iARB(*x, *y);
}


//649
 void EXEC_glWindowPos2sARB(char *commandbuf)
{
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glWindowPos2sARB(*x, *y);
}


//650
 void EXEC_glWindowPos2dvARB(char *commandbuf)
{

	glWindowPos2dvARB((const GLdouble *)popBuf());
}


//651
 void EXEC_glWindowPos2fvARB(char *commandbuf)
{

	glWindowPos2fvARB((const GLfloat *)popBuf());
}


//652
 void EXEC_glWindowPos2ivARB(char *commandbuf)
{

	glWindowPos2ivARB((const GLint *)popBuf());
}


//653
 void EXEC_glWindowPos2svARB(char *commandbuf)
{

	glWindowPos2svARB((const GLshort *)popBuf());
}


//654
 void EXEC_glWindowPos3dARB(char *commandbuf)
{
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glWindowPos3dARB(*x, *y, *z);
}


//655
 void EXEC_glWindowPos3fARB(char *commandbuf)
{
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glWindowPos3fARB(*x, *y, *z);
}


//656
 void EXEC_glWindowPos3iARB(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *z = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glWindowPos3iARB(*x, *y, *z);
}


//657
 void EXEC_glWindowPos3sARB(char *commandbuf)
{
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *z = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glWindowPos3sARB(*x, *y, *z);
}


//658
 void EXEC_glWindowPos3dvARB(char *commandbuf)
{

	glWindowPos3dvARB((const GLdouble *)popBuf());
}


//659
 void EXEC_glWindowPos3fvARB(char *commandbuf)
{

	glWindowPos3fvARB((const GLfloat *)popBuf());
}


//660
 void EXEC_glWindowPos3ivARB(char *commandbuf)
{

	glWindowPos3ivARB((const GLint *)popBuf());
}


//661
 void EXEC_glWindowPos3svARB(char *commandbuf)
{

	glWindowPos3svARB((const GLshort *)popBuf());
}


//662
 void EXEC_glGetVertexAttribdvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetVertexAttribdvARB(*index, *pname, (GLdouble *)popBuf());
}


//663
 void EXEC_glGetVertexAttribfvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetVertexAttribfvARB(*index, *pname, (GLfloat *)popBuf());
}


//664
 void EXEC_glGetVertexAttribivARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetVertexAttribivARB(*index, *pname, (GLint *)popBuf());
}


//665
 void EXEC_glVertexAttrib1dARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glVertexAttrib1dARB(*index, *x);
}


//666
 void EXEC_glVertexAttrib1dvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib1dvARB(*index, (const GLdouble *)popBuf());
}


//667
 void EXEC_glVertexAttrib1fARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glVertexAttrib1fARB(*index, *x);
}


//668
 void EXEC_glVertexAttrib1fvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib1fvARB(*index, (const GLfloat *)popBuf());
}


//669
 void EXEC_glVertexAttrib1sARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glVertexAttrib1sARB(*index, *x);
}


//670
 void EXEC_glVertexAttrib1svARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib1svARB(*index, (const GLshort *)popBuf());
}


//671
 void EXEC_glVertexAttrib2dARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glVertexAttrib2dARB(*index, *x, *y);
}


//672
 void EXEC_glVertexAttrib2dvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib2dvARB(*index, (const GLdouble *)popBuf());
}


//673
 void EXEC_glVertexAttrib2fARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glVertexAttrib2fARB(*index, *x, *y);
}


//674
 void EXEC_glVertexAttrib2fvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib2fvARB(*index, (const GLfloat *)popBuf());
}


//675
 void EXEC_glVertexAttrib2sARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glVertexAttrib2sARB(*index, *x, *y);
}


//676
 void EXEC_glVertexAttrib2svARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib2svARB(*index, (const GLshort *)popBuf());
}


//677
 void EXEC_glVertexAttrib3dARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glVertexAttrib3dARB(*index, *x, *y, *z);
}


//678
 void EXEC_glVertexAttrib3dvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib3dvARB(*index, (const GLdouble *)popBuf());
}


//679
 void EXEC_glVertexAttrib3fARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glVertexAttrib3fARB(*index, *x, *y, *z);
}


//680
 void EXEC_glVertexAttrib3fvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib3fvARB(*index, (const GLfloat *)popBuf());
}


//681
 void EXEC_glVertexAttrib3sARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *z = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glVertexAttrib3sARB(*index, *x, *y, *z);
}


//682
 void EXEC_glVertexAttrib3svARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib3svARB(*index, (const GLshort *)popBuf());
}


//683
 void EXEC_glVertexAttrib4dARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *w = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glVertexAttrib4dARB(*index, *x, *y, *z, *w);
}


//684
 void EXEC_glVertexAttrib4dvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4dvARB(*index, (const GLdouble *)popBuf());
}


//685
 void EXEC_glVertexAttrib4fARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *w = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glVertexAttrib4fARB(*index, *x, *y, *z, *w);
}


//686
 void EXEC_glVertexAttrib4fvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4fvARB(*index, (const GLfloat *)popBuf());
}


//687
 void EXEC_glVertexAttrib4sARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *z = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *w = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glVertexAttrib4sARB(*index, *x, *y, *z, *w);
}


//688
 void EXEC_glVertexAttrib4svARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4svARB(*index, (const GLshort *)popBuf());
}


//689
 void EXEC_glVertexAttrib4NubARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLubyte *x = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *y = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *z = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *w = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);

	glVertexAttrib4NubARB(*index, *x, *y, *z, *w);
}


//690
 void EXEC_glVertexAttrib4NubvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4NubvARB(*index, (const GLubyte *)popBuf());
}


//691
 void EXEC_glVertexAttrib4bvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4bvARB(*index, (const GLbyte *)popBuf());
}


//692
 void EXEC_glVertexAttrib4ivARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4ivARB(*index, (const GLint *)popBuf());
}


//693
 void EXEC_glVertexAttrib4ubvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4ubvARB(*index, (const GLubyte *)popBuf());
}


//694
 void EXEC_glVertexAttrib4usvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4usvARB(*index, (const GLushort *)popBuf());
}


//695
 void EXEC_glVertexAttrib4uivARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4uivARB(*index, (const GLuint *)popBuf());
}


//696
 void EXEC_glVertexAttrib4NbvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4NbvARB(*index, (const GLbyte *)popBuf());
}


//697
 void EXEC_glVertexAttrib4NsvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4NsvARB(*index, (const GLshort *)popBuf());
}


//698
 void EXEC_glVertexAttrib4NivARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4NivARB(*index, (const GLint *)popBuf());
}


//699
 void EXEC_glVertexAttrib4NusvARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4NusvARB(*index, (const GLushort *)popBuf());
}


//700
 void EXEC_glVertexAttrib4NuivARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4NuivARB(*index, (const GLuint *)popBuf());
}


//701
 void EXEC_glVertexAttribPointerARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLboolean *normalized = (GLboolean*)commandbuf;  commandbuf += sizeof(GLboolean);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glVertexAttribPointerARB(*index, *size, *type, *normalized, *stride, (const GLvoid *)popBuf());
}


//702
 void EXEC_glEnableVertexAttribArrayARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glEnableVertexAttribArrayARB(*index);
}


//703
 void EXEC_glDisableVertexAttribArrayARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glDisableVertexAttribArrayARB(*index);
}


//704
 void EXEC_glProgramStringARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *len = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);

	glProgramStringARB(*target, *format, *len, (const GLvoid *)popBuf());
}


//705
 void EXEC_glBindProgramARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	glBindProgramARB(*target, *program);
}


//706
 void EXEC_glDeleteProgramsARB(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glDeleteProgramsARB(*n, (const GLuint *)popBuf());
}


//707
 void EXEC_glGenProgramsARB(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glGenProgramsARB(*n, (GLuint *)popBuf());
}


//708
 void EXEC_glIsProgramARB(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	pushRet(glIsProgramARB(*program));
}


//709
 void EXEC_glProgramEnvParameter4dARB(char *commandbuf)
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
 void EXEC_glProgramEnvParameter4dvARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glProgramEnvParameter4dvARB(*target, *index, (const GLdouble *)popBuf());
}


//711
 void EXEC_glProgramEnvParameter4fARB(char *commandbuf)
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
 void EXEC_glProgramEnvParameter4fvARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glProgramEnvParameter4fvARB(*target, *index, (const GLfloat *)popBuf());
}


//713
 void EXEC_glProgramLocalParameter4dARB(char *commandbuf)
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
 void EXEC_glProgramLocalParameter4dvARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glProgramLocalParameter4dvARB(*target, *index, (const GLdouble *)popBuf());
}


//715
 void EXEC_glProgramLocalParameter4fARB(char *commandbuf)
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
 void EXEC_glProgramLocalParameter4fvARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glProgramLocalParameter4fvARB(*target, *index, (const GLfloat *)popBuf());
}


//717
 void EXEC_glGetProgramEnvParameterdvARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glGetProgramEnvParameterdvARB(*target, *index, (GLdouble *)popBuf());
}


//718
 void EXEC_glGetProgramEnvParameterfvARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glGetProgramEnvParameterfvARB(*target, *index, (GLfloat *)popBuf());
}


//719
 void EXEC_glGetProgramLocalParameterdvARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glGetProgramLocalParameterdvARB(*target, *index, (GLdouble *)popBuf());
}


//720
 void EXEC_glGetProgramLocalParameterfvARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glGetProgramLocalParameterfvARB(*target, *index, (GLfloat *)popBuf());
}


//721
 void EXEC_glGetProgramivARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetProgramivARB(*target, *pname, (GLint *)popBuf());
}


//722
 void EXEC_glGetProgramStringARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetProgramStringARB(*target, *pname, (GLvoid *)popBuf());
}


//723
 void EXEC_glGetVertexAttribPointervARB(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetVertexAttribPointervARB(*index, *pname, (GLvoid **)popBuf());
}


//724
 void EXEC_glBindBufferARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *buffer = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	glBindBufferARB(*target, *buffer);
}


//725
 void EXEC_glBufferDataARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizeiptrARB *size = (GLsizeiptrARB*)commandbuf;    commandbuf += sizeof(GLsizeiptrARB);
	GLenum *usage = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glBufferDataARB(*target, *size, (const GLvoid *)popBuf(), *usage);
}


//726
 void EXEC_glBufferSubDataARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLintptrARB *offset = (GLintptrARB*)commandbuf;  commandbuf += sizeof(GLintptrARB);
	GLsizeiptrARB *size = (GLsizeiptrARB*)commandbuf;    commandbuf += sizeof(GLsizeiptrARB);

	glBufferSubDataARB(*target, *offset, *size, (const GLvoid *)popBuf());
}


//727
 void EXEC_glDeleteBuffersARB(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glDeleteBuffersARB(*n, (const GLuint *)popBuf());
}


//728
 void EXEC_glGenBuffersARB(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glGenBuffersARB(*n, (GLuint *)popBuf());
}


//729
 void EXEC_glGetBufferParameterivARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetBufferParameterivARB(*target, *pname, (GLint *)popBuf());
}


//730
 void EXEC_glGetBufferPointervARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetBufferPointervARB(*target, *pname, (GLvoid **)popBuf());
}


//731
 void EXEC_glGetBufferSubDataARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLintptrARB *offset = (GLintptrARB*)commandbuf;  commandbuf += sizeof(GLintptrARB);
	GLsizeiptrARB *size = (GLsizeiptrARB*)commandbuf;    commandbuf += sizeof(GLsizeiptrARB);

	glGetBufferSubDataARB(*target, *offset, *size, (GLvoid *)popBuf());
}


//732
 void EXEC_glIsBufferARB(char *commandbuf)
{
	GLuint *buffer = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	pushRet(glIsBufferARB(*buffer));
}


//733
 void EXEC_glMapBufferARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *access = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	pushRet((const GLubyte*) glMapBufferARB(*target, *access));
}


//734
 void EXEC_glUnmapBufferARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	pushRet(glUnmapBufferARB(*target));
}


//735
 void EXEC_glGenQueriesARB(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glGenQueriesARB(*n, (GLuint *)popBuf());
}


//736
 void EXEC_glDeleteQueriesARB(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glDeleteQueriesARB(*n, (const GLuint *)popBuf());
}


//737
 void EXEC_glIsQueryARB(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	pushRet(glIsQueryARB(*id));
}


//738
 void EXEC_glBeginQueryARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	glBeginQueryARB(*target, *id);
}


//739
 void EXEC_glEndQueryARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glEndQueryARB(*target);
}


//740
 void EXEC_glGetQueryivARB(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetQueryivARB(*target, *pname, (GLint *)popBuf());
}


//741
 void EXEC_glGetQueryObjectivARB(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetQueryObjectivARB(*id, *pname, (GLint *)popBuf());
}


//742
 void EXEC_glGetQueryObjectuivARB(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetQueryObjectuivARB(*id, *pname, (GLuint *)popBuf());
}


//743
 void EXEC_glDeleteObjectARB(char *commandbuf)
{
	GLhandleARB *obj = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);

	glDeleteObjectARB(*obj);
}


//744
 void EXEC_glGetHandleARB(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	pushRet(glGetHandleARB(*pname));
}


//745
 void EXEC_glDetachObjectARB(char *commandbuf)
{
	GLhandleARB *containerObj = (GLhandleARB*)commandbuf;    commandbuf += sizeof(GLhandleARB);
	GLhandleARB *attachedObj = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);

	glDetachObjectARB(*containerObj, *attachedObj);
}


//746
 void EXEC_glCreateShaderObjectARB(char *commandbuf)
{
	GLenum *shaderType = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	pushRet(glCreateShaderObjectARB(*shaderType));
}


//747
 void EXEC_glShaderSourceARB(char *commandbuf)
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
 void EXEC_glCompileShaderARB(char *commandbuf)
{
	GLhandleARB *shader = (GLhandleARB*)commandbuf;  commandbuf += sizeof(GLhandleARB);

	glCompileShaderARB(*shader);
}


//749
 void EXEC_glCreateProgramObjectARB(char *commandbuf)
{

	pushRet(glCreateProgramObjectARB());
}


//750
 void EXEC_glAttachObjectARB(char *commandbuf)
{
	GLhandleARB *containerObj = (GLhandleARB*)commandbuf;    commandbuf += sizeof(GLhandleARB);
	GLhandleARB *obj = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);

	glAttachObjectARB(*containerObj, *obj);
}


//751
 void EXEC_glLinkProgramARB(char *commandbuf)
{
	GLhandleARB *program = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);

	glLinkProgramARB(*program);
}


//752
 void EXEC_glUseProgramObjectARB(char *commandbuf)
{
	GLhandleARB *program = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);

	glUseProgramObjectARB(*program);
}


//753
 void EXEC_glValidateProgramARB(char *commandbuf)
{
	GLhandleARB *program = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);

	glValidateProgramARB(*program);
}


//754
 void EXEC_glUniform1fARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLfloat *v0 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	glUniform1fARB(*location, *v0);
}


//755
 void EXEC_glUniform2fARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLfloat *v0 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *v1 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	glUniform2fARB(*location, *v0, *v1);
}


//756
 void EXEC_glUniform3fARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLfloat *v0 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *v1 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *v2 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	glUniform3fARB(*location, *v0, *v1, *v2);
}


//757
 void EXEC_glUniform4fARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLfloat *v0 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *v1 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *v2 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *v3 = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	glUniform4fARB(*location, *v0, *v1, *v2, *v3);
}


//758
 void EXEC_glUniform1iARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLint *v0 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glUniform1iARB(*location, *v0);
}


//759
 void EXEC_glUniform2iARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLint *v0 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *v1 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glUniform2iARB(*location, *v0, *v1);
}


//760
 void EXEC_glUniform3iARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLint *v0 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *v1 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *v2 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glUniform3iARB(*location, *v0, *v1, *v2);
}


//761
 void EXEC_glUniform4iARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLint *v0 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *v1 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *v2 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *v3 = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glUniform4iARB(*location, *v0, *v1, *v2, *v3);
}


//762
 void EXEC_glUniform1fvARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glUniform1fvARB(*location, *count, (const GLfloat *)popBuf());
}


//763
 void EXEC_glUniform2fvARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glUniform2fvARB(*location, *count, (const GLfloat *)popBuf());
}


//764
 void EXEC_glUniform3fvARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glUniform3fvARB(*location, *count, (const GLfloat *)popBuf());
}


//765
 void EXEC_glUniform4fvARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glUniform4fvARB(*location, *count, (const GLfloat *)popBuf());
}


//766
 void EXEC_glUniform1ivARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glUniform1ivARB(*location, *count, (const GLint *)popBuf());
}


//767
 void EXEC_glUniform2ivARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glUniform2ivARB(*location, *count, (const GLint *)popBuf());
}


//768
 void EXEC_glUniform3ivARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glUniform3ivARB(*location, *count, (const GLint *)popBuf());
}


//769
 void EXEC_glUniform4ivARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glUniform4ivARB(*location, *count, (const GLint *)popBuf());
}


//770
 void EXEC_glUniformMatrix2fvARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLboolean *transpose = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);

	glUniformMatrix2fvARB(*location, *count, *transpose, (const GLfloat *)popBuf());
}


//771
 void EXEC_glUniformMatrix3fvARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLboolean *transpose = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);

	glUniformMatrix3fvARB(*location, *count, *transpose, (const GLfloat *)popBuf());
}


//772
 void EXEC_glUniformMatrix4fvARB(char *commandbuf)
{
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLboolean *transpose = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);

	glUniformMatrix4fvARB(*location, *count, *transpose, (const GLfloat *)popBuf());
}


//773
 void EXEC_glGetObjectParameterfvARB(char *commandbuf)
{
	GLhandleARB *obj = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetObjectParameterfvARB(*obj, *pname, (GLfloat *)popBuf());
}


//774
 void EXEC_glGetObjectParameterivARB(char *commandbuf)
{
	GLhandleARB *obj = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetObjectParameterivARB(*obj, *pname, (GLint *)popBuf());
}


//775
 void EXEC_glGetInfoLogARB(char *commandbuf)
{
	GLhandleARB *obj = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);
	GLsizei *maxLength = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *length = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glGetInfoLogARB(*obj, *maxLength, length, (GLcharARB *)popBuf());
}


//776
 void EXEC_glGetAttachedObjectsARB(char *commandbuf)
{
	GLhandleARB *containerObj = (GLhandleARB*)commandbuf;    commandbuf += sizeof(GLhandleARB);
	GLsizei *maxLength = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glGetAttachedObjectsARB(*containerObj, *maxLength, (GLsizei *)popBuf(), (GLhandleARB *)popBuf());
}


//777
 void EXEC_glGetUniformLocationARB(char *commandbuf)
{
	GLhandleARB *program = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);
	int num = glGetUniformLocationARB(*program, (const GLcharARB *)popBuf());
	pushRet(num);
}


//778
 void EXEC_glGetActiveUniformARB(char *commandbuf)
{
	GLhandleARB *program = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *bufSize = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);

	glGetActiveUniformARB(*program, *index, *bufSize, (GLsizei *)popBuf(), (GLint *)popBuf(), (GLenum *)popBuf(), (GLcharARB *)popBuf());
}


//779
 void EXEC_glGetUniformfvARB(char *commandbuf)
{
	GLhandleARB *program = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glGetUniformfvARB(*program, *location, (GLfloat *)popBuf());
}


//780
 void EXEC_glGetUniformivARB(char *commandbuf)
{
	GLhandleARB *program = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);
	GLint *location = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glGetUniformivARB(*program, *location, (GLint *)popBuf());
}


//781
 void EXEC_glGetShaderSourceARB(char *commandbuf)
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
 void EXEC_glBindAttribLocationARB(char *commandbuf)
{
	GLhandleARB *program = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glBindAttribLocationARB(*program, *index, (const GLcharARB *)popBuf());
}


//783
 void EXEC_glGetActiveAttribARB(char *commandbuf)
{
	GLhandleARB *program = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *bufSize = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);

	glGetActiveAttribARB(*program, *index, *bufSize, (GLsizei *)popBuf(), (GLint *)popBuf(), (GLenum *)popBuf(), (GLcharARB *)popBuf());
}


//784
 void EXEC_glGetAttribLocationARB(char *commandbuf)
{
	GLhandleARB *program = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);

	pushRet(glGetAttribLocationARB(*program, (const GLcharARB *)popBuf()));
}


//785
 void EXEC_glDrawBuffersARB(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glDrawBuffersARB(*n, (const GLenum *)popBuf());
}


//786
 void EXEC_glBlendColorEXT(char *commandbuf)
{
	GLclampf *red = (GLclampf*)commandbuf;   commandbuf += sizeof(GLclampf);
	GLclampf *green = (GLclampf*)commandbuf;     commandbuf += sizeof(GLclampf);
	GLclampf *blue = (GLclampf*)commandbuf;  commandbuf += sizeof(GLclampf);
	GLclampf *alpha = (GLclampf*)commandbuf;     commandbuf += sizeof(GLclampf);

	glBlendColorEXT(*red, *green, *blue, *alpha);
}


//787
 void EXEC_glPolygonOffsetEXT(char *commandbuf)
{
	GLfloat *factor = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *bias = (GLfloat*)commandbuf;    commandbuf += sizeof(GLfloat);

	glPolygonOffsetEXT(*factor, *bias);
}


//788
 void EXEC_glTexImage3DEXT(char *commandbuf)
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
 void EXEC_glTexSubImage3DEXT(char *commandbuf)
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
 void EXEC_glGetTexFilterFuncSGIS(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *filter = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glGetTexFilterFuncSGIS(*target, *filter, (GLfloat *)popBuf());
}


//791
 void EXEC_glTexFilterFuncSGIS(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *filter = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glTexFilterFuncSGIS(*target, *filter, *n, (const GLfloat *)popBuf());
}


//792
 void EXEC_glTexSubImage1DEXT(char *commandbuf)
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
 void EXEC_glTexSubImage2DEXT(char *commandbuf)
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
 void EXEC_glCopyTexImage1DEXT(char *commandbuf)
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
 void EXEC_glCopyTexImage2DEXT(char *commandbuf)
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
 void EXEC_glCopyTexSubImage1DEXT(char *commandbuf)
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
 void EXEC_glCopyTexSubImage2DEXT(char *commandbuf)
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
 void EXEC_glCopyTexSubImage3DEXT(char *commandbuf)
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
 void EXEC_glGetHistogramEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLboolean *reset = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glGetHistogramEXT(*target, *reset, *format, *type, (GLvoid *)popBuf());
}


//800
 void EXEC_glGetHistogramParameterfvEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetHistogramParameterfvEXT(*target, *pname, (GLfloat *)popBuf());
}


//801
 void EXEC_glGetHistogramParameterivEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetHistogramParameterivEXT(*target, *pname, (GLint *)popBuf());
}


//802
 void EXEC_glGetMinmaxEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLboolean *reset = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glGetMinmaxEXT(*target, *reset, *format, *type, (GLvoid *)popBuf());
}


//803
 void EXEC_glGetMinmaxParameterfvEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetMinmaxParameterfvEXT(*target, *pname, (GLfloat *)popBuf());
}


//804
 void EXEC_glGetMinmaxParameterivEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetMinmaxParameterivEXT(*target, *pname, (GLint *)popBuf());
}


//805
 void EXEC_glHistogramEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLboolean *sink = (GLboolean*)commandbuf;    commandbuf += sizeof(GLboolean);

	glHistogramEXT(*target, *width, *internalformat, *sink);
}


//806
 void EXEC_glMinmaxEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLboolean *sink = (GLboolean*)commandbuf;    commandbuf += sizeof(GLboolean);

	glMinmaxEXT(*target, *internalformat, *sink);
}


//807
 void EXEC_glResetHistogramEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glResetHistogramEXT(*target);
}


//808
 void EXEC_glResetMinmaxEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glResetMinmaxEXT(*target);
}


//809
 void EXEC_glConvolutionFilter1DEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glConvolutionFilter1DEXT(*target, *internalformat, *width, *format, *type, (const GLvoid *)popBuf());
}


//810
 void EXEC_glConvolutionFilter2DEXT(char *commandbuf)
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
 void EXEC_glConvolutionParameterfEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *params = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	glConvolutionParameterfEXT(*target, *pname, *params);
}


//812
 void EXEC_glConvolutionParameterfvEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glConvolutionParameterfvEXT(*target, *pname, (const GLfloat *)popBuf());
}


//813
 void EXEC_glConvolutionParameteriEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *params = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glConvolutionParameteriEXT(*target, *pname, *params);
}


//814
 void EXEC_glConvolutionParameterivEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glConvolutionParameterivEXT(*target, *pname, (const GLint *)popBuf());
}


//815
 void EXEC_glCopyConvolutionFilter1DEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glCopyConvolutionFilter1DEXT(*target, *internalformat, *x, *y, *width);
}


//816
 void EXEC_glCopyConvolutionFilter2DEXT(char *commandbuf)
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
 void EXEC_glGetConvolutionFilterEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glGetConvolutionFilterEXT(*target, *format, *type, (GLvoid *)popBuf());
}


//818
 void EXEC_glGetConvolutionParameterfvEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetConvolutionParameterfvEXT(*target, *pname, (GLfloat *)popBuf());
}


//819
 void EXEC_glGetConvolutionParameterivEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetConvolutionParameterivEXT(*target, *pname, (GLint *)popBuf());
}


//820
 void EXEC_glGetSeparableFilterEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glGetSeparableFilterEXT(*target, *format, *type, (GLvoid *)popBuf(), (GLvoid *)popBuf(), (GLvoid *)popBuf());
}


//821
 void EXEC_glSeparableFilter2DEXT(char *commandbuf)
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
 void EXEC_glColorTableSGI(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glColorTableSGI(*target, *internalformat, *width, *format, *type, (const GLvoid *)popBuf());
}


//823
 void EXEC_glColorTableParameterfvSGI(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glColorTableParameterfvSGI(*target, *pname, (const GLfloat *)popBuf());
}


//824
 void EXEC_glColorTableParameterivSGI(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glColorTableParameterivSGI(*target, *pname, (const GLint *)popBuf());
}


//825
 void EXEC_glCopyColorTableSGI(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glCopyColorTableSGI(*target, *internalformat, *x, *y, *width);
}


//826
 void EXEC_glGetColorTableSGI(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glGetColorTableSGI(*target, *format, *type, (GLvoid *)popBuf());
}


//827
 void EXEC_glGetColorTableParameterfvSGI(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetColorTableParameterfvSGI(*target, *pname, (GLfloat *)popBuf());
}


//828
 void EXEC_glGetColorTableParameterivSGI(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetColorTableParameterivSGI(*target, *pname, (GLint *)popBuf());
}


//829
 void EXEC_glPixelTexGenParameteriSGIS(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	//glPixelTexGenParameteriSGIS(*pname, *param);
}


//830
 void EXEC_glPixelTexGenParameterivSGIS(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	//glPixelTexGenParameterivSGIS(*pname, (const GLint *)popBuf());
}


//831
 void EXEC_glPixelTexGenParameterfSGIS(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	//glPixelTexGenParameterfSGIS(*pname, *param);
}


//832
 void EXEC_glPixelTexGenParameterfvSGIS(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	//glPixelTexGenParameterfvSGIS(*pname, (const GLfloat *)popBuf());
}


//833
 void EXEC_glGetPixelTexGenParameterivSGIS(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	//glGetPixelTexGenParameterivSGIS(*pname, (GLint *)popBuf());
}


//834
 void EXEC_glGetPixelTexGenParameterfvSGIS(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	//glGetPixelTexGenParameterfvSGIS(*pname, (GLfloat *)popBuf());
}


//835
 void EXEC_glTexImage4DSGIS(char *commandbuf)
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
 void EXEC_glTexSubImage4DSGIS(char *commandbuf)
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
 void EXEC_glAreTexturesResidentEXT(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	pushRet(glAreTexturesResidentEXT(*n, (const GLuint *)popBuf(), (GLboolean *)popBuf()));
}


//838
 void EXEC_glBindTextureEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *texture = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	glBindTextureEXT(*target, *texture);
}


//839
 void EXEC_glDeleteTexturesEXT(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glDeleteTexturesEXT(*n, (const GLuint *)popBuf());
}


//840
 void EXEC_glGenTexturesEXT(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glGenTexturesEXT(*n, (GLuint *)popBuf());
}


//841
 void EXEC_glIsTextureEXT(char *commandbuf)
{
	GLuint *texture = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	pushRet(glIsTextureEXT(*texture));
}


//842
 void EXEC_glPrioritizeTexturesEXT(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glPrioritizeTexturesEXT(*n, (const GLuint *)popBuf(), (const GLclampf *)popBuf());
}


//843
 void EXEC_glDetailTexFuncSGIS(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glDetailTexFuncSGIS(*target, *n, (const GLfloat *)popBuf());
}


//844
 void EXEC_glGetDetailTexFuncSGIS(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glGetDetailTexFuncSGIS(*target, (GLfloat *)popBuf());
}


//845
 void EXEC_glSharpenTexFuncSGIS(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glSharpenTexFuncSGIS(*target, *n, (const GLfloat *)popBuf());
}


//846
 void EXEC_glGetSharpenTexFuncSGIS(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glGetSharpenTexFuncSGIS(*target, (GLfloat *)popBuf());
}


//847
 void EXEC_glSampleMaskSGIS(char *commandbuf)
{
	GLclampf *value = (GLclampf*)commandbuf;     commandbuf += sizeof(GLclampf);
	GLboolean *invert = (GLboolean*)commandbuf;  commandbuf += sizeof(GLboolean);

	glSampleMaskSGIS(*value, *invert);
}


//848
 void EXEC_glSamplePatternSGIS(char *commandbuf)
{
	GLenum *pattern = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);

	glSamplePatternSGIS(*pattern);
}


//849
 void EXEC_glArrayElementEXT(char *commandbuf)
{
	GLint *i = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glArrayElementEXT(*i);
}


//850
 void EXEC_glColorPointerEXT(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glColorPointerEXT(*size, *type, *stride, *count, (const GLvoid *)popBuf());
}


//851
 void EXEC_glDrawArraysEXT(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLint *first = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glDrawArraysEXT(*mode, *first, *count);
}


//852
 void EXEC_glEdgeFlagPointerEXT(char *commandbuf)
{
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glEdgeFlagPointerEXT(*stride, *count, (const GLboolean *)popBuf());
}



//853
 void EXEC_glGetPointervEXT(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	glGetPointerv(*pname, (GLvoid **)popBuf());
}




//854
 void EXEC_glIndexPointerEXT(char *commandbuf)
{
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glIndexPointerEXT(*type, *stride, *count, (const GLvoid *)popBuf());
}


//855
 void EXEC_glNormalPointerEXT(char *commandbuf)
{
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glNormalPointerEXT(*type, *stride, *count, (const GLvoid *)popBuf());
}


//856
 void EXEC_glTexCoordPointerEXT(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glTexCoordPointerEXT(*size, *type, *stride, *count, (const GLvoid *)popBuf());
}


//857
 void EXEC_glVertexPointerEXT(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glVertexPointerEXT(*size, *type, *stride, *count, (const GLvoid *)popBuf());
}


//858
 void EXEC_glBlendEquationEXT(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glBlendEquationEXT(*mode);
}


//859
 void EXEC_glSpriteParameterfSGIX(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glSpriteParameterfSGIX(*pname, *param);
}


//860
 void EXEC_glSpriteParameterfvSGIX(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glSpriteParameterfvSGIX(*pname, (GLfloat *)popBuf());
}


//861
 void EXEC_glSpriteParameteriSGIX(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glSpriteParameteriSGIX(*pname, *param);
}


//862
 void EXEC_glSpriteParameterivSGIX(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glSpriteParameterivSGIX(*pname, (GLint *)popBuf());
}


//863
 void EXEC_glPointParameterfEXT(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glPointParameterfEXT(*pname, *param);
}


//864
 void EXEC_glPointParameterfvEXT(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glPointParameterfvEXT(*pname, (GLfloat *)popBuf());
}


//865
 void EXEC_glGetInstrumentsSGIX(char *commandbuf)
{

	//pushRet(glGetInstrumentsSGIX());
}


//866
 void EXEC_glInstrumentsBufferSGIX(char *commandbuf)
{
	GLsizei *size = (GLsizei*)commandbuf;    commandbuf += sizeof(GLsizei);

	//glInstrumentsBufferSGIX(*size, (GLint *)popBuf());
}


//867
 void EXEC_glPollInstrumentsSGIX(char *commandbuf)
{

	//pushRet(glPollInstrumentsSGIX((GLint *)popBuf()));
}


//868
 void EXEC_glReadInstrumentsSGIX(char *commandbuf)
{
	GLint *marker = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	//glReadInstrumentsSGIX(*marker);
}


//869
 void EXEC_glStartInstrumentsSGIX(char *commandbuf)
{

	//glStartInstrumentsSGIX();
}


//870
 void EXEC_glStopInstrumentsSGIX(char *commandbuf)
{
	GLint *marker = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	//glStopInstrumentsSGIX(*marker);
}


//871
 void EXEC_glFrameZoomSGIX(char *commandbuf)
{
	GLint *factor = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	//glFrameZoomSGIX(*factor);
}


//872
 void EXEC_glTagSampleBufferSGIX(char *commandbuf)
{

	//glTagSampleBufferSGIX();
}


//873
 void EXEC_glReferencePlaneSGIX(char *commandbuf)
{

	//glReferencePlaneSGIX((const GLdouble *)popBuf());
}


//874
 void EXEC_glFlushRasterSGIX(char *commandbuf)
{

	//glFlushRasterSGIX();
}


//875
 void EXEC_glFogFuncSGIS(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glFogFuncSGIS(*n, (const GLfloat *)popBuf());
}


//876
 void EXEC_glGetFogFuncSGIS(char *commandbuf)
{

	glGetFogFuncSGIS((GLfloat *)popBuf());
}


//877
 void EXEC_glImageTransformParameteriHP(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glImageTransformParameteriHP(*target, *pname, *param);
}


//878
 void EXEC_glImageTransformParameterfHP(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glImageTransformParameterfHP(*target, *pname, *param);
}


//879
 void EXEC_glImageTransformParameterivHP(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glImageTransformParameterivHP(*target, *pname, (const GLint *)popBuf());
}


//880
 void EXEC_glImageTransformParameterfvHP(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glImageTransformParameterfvHP(*target, *pname, (const GLfloat *)popBuf());
}


//881
 void EXEC_glGetImageTransformParameterivHP(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetImageTransformParameterivHP(*target, *pname, (GLint *)popBuf());
}


//882
 void EXEC_glGetImageTransformParameterfvHP(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetImageTransformParameterfvHP(*target, *pname, (GLfloat *)popBuf());
}


//883
 void EXEC_glColorSubTableEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *start = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glColorSubTableEXT(*target, *start, *count, *format, *type, (const GLvoid *)popBuf());
}


//884
 void EXEC_glCopyColorSubTableEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *start = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glCopyColorSubTableEXT(*target, *start, *x, *y, *width);
}


//885
 void EXEC_glHintPGI(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLint *mode = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	//glHintPGI(*target, *mode);
}


//886
 void EXEC_glColorTableEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *internalformat = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glColorTableEXT(*target, *internalformat, *width, *format, *type, (const GLvoid *)popBuf());
}


//887
 void EXEC_glGetColorTableEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *format = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glGetColorTableEXT(*target, *format, *type, (GLvoid *)popBuf());
}


//888
 void EXEC_glGetColorTableParameterivEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetColorTableParameterivEXT(*target, *pname, (GLint *)popBuf());
}


//889
 void EXEC_glGetColorTableParameterfvEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetColorTableParameterfvEXT(*target, *pname, (GLfloat *)popBuf());
}


//890
 void EXEC_glGetListParameterfvSGIX(char *commandbuf)
{
	GLuint *list = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	//glGetListParameterfvSGIX(*list, *pname, (GLfloat *)popBuf());
}


//891
 void EXEC_glGetListParameterivSGIX(char *commandbuf)
{
	GLuint *list = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	//glGetListParameterivSGIX(*list, *pname, (GLint *)popBuf());
}


//892
 void EXEC_glListParameterfSGIX(char *commandbuf)
{
	GLuint *list = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	//glListParameterfSGIX(*list, *pname, *param);
}


//893
 void EXEC_glListParameterfvSGIX(char *commandbuf)
{
	GLuint *list = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	//glListParameterfvSGIX(*list, *pname, (const GLfloat *)popBuf());
}


//894
 void EXEC_glListParameteriSGIX(char *commandbuf)
{
	GLuint *list = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	//glListParameteriSGIX(*list, *pname, *param);
}


//895
 void EXEC_glListParameterivSGIX(char *commandbuf)
{
	GLuint *list = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	//glListParameterivSGIX(*list, *pname, (const GLint *)popBuf());
}


//896
 void EXEC_glIndexMaterialEXT(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glIndexMaterialEXT(*face, *mode);
}


//897
 void EXEC_glIndexFuncEXT(char *commandbuf)
{
	GLenum *func = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLclampf *ref = (GLclampf*)commandbuf;   commandbuf += sizeof(GLclampf);

	glIndexFuncEXT(*func, *ref);
}


//898
 void EXEC_glLockArraysEXT(char *commandbuf)
{
	GLint *first = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glLockArraysEXT(*first, *count);
}


//899
 void EXEC_glUnlockArraysEXT(char *commandbuf)
{

	glUnlockArraysEXT();
}


//900
 void EXEC_glCullParameterdvEXT(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glCullParameterdvEXT(*pname, (GLdouble *)popBuf());
}


//901
 void EXEC_glCullParameterfvEXT(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glCullParameterfvEXT(*pname, (GLfloat *)popBuf());
}


//902
 void EXEC_glFragmentColorMaterialSGIX(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glFragmentColorMaterialSGIX(*face, *mode);
}


//903
 void EXEC_glFragmentLightfSGIX(char *commandbuf)
{
	GLenum *light = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glFragmentLightfSGIX(*light, *pname, *param);
}


//904
 void EXEC_glFragmentLightfvSGIX(char *commandbuf)
{
	GLenum *light = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glFragmentLightfvSGIX(*light, *pname, (GLfloat *)popBuf());
}


//905
 void EXEC_glFragmentLightiSGIX(char *commandbuf)
{
	GLenum *light = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glFragmentLightiSGIX(*light, *pname, *param);
}


//906
 void EXEC_glFragmentLightivSGIX(char *commandbuf)
{
	GLenum *light = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glFragmentLightivSGIX(*light, *pname, (GLint *)popBuf());
}


//907
 void EXEC_glFragmentLightModelfSGIX(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glFragmentLightModelfSGIX(*pname, *param);
}


//908
 void EXEC_glFragmentLightModelfvSGIX(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glFragmentLightModelfvSGIX(*pname, (GLfloat *)popBuf());
}


//909
 void EXEC_glFragmentLightModeliSGIX(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glFragmentLightModeliSGIX(*pname, *param);
}


//910
 void EXEC_glFragmentLightModelivSGIX(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glFragmentLightModelivSGIX(*pname, (GLint *)popBuf());
}


//911
 void EXEC_glFragmentMaterialfSGIX(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glFragmentMaterialfSGIX(*face, *pname, *param);
}


//912
 void EXEC_glFragmentMaterialfvSGIX(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glFragmentMaterialfvSGIX(*face, *pname, (const GLfloat *)popBuf());
}


//913
 void EXEC_glFragmentMaterialiSGIX(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glFragmentMaterialiSGIX(*face, *pname, *param);
}


//914
 void EXEC_glFragmentMaterialivSGIX(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glFragmentMaterialivSGIX(*face, *pname, (const GLint *)popBuf());
}


//915
 void EXEC_glGetFragmentLightfvSGIX(char *commandbuf)
{
	GLenum *light = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetFragmentLightfvSGIX(*light, *pname, (GLfloat *)popBuf());
}


//916
 void EXEC_glGetFragmentLightivSGIX(char *commandbuf)
{
	GLenum *light = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetFragmentLightivSGIX(*light, *pname, (GLint *)popBuf());
}


//917
 void EXEC_glGetFragmentMaterialfvSGIX(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetFragmentMaterialfvSGIX(*face, *pname, (GLfloat *)popBuf());
}


//918
 void EXEC_glGetFragmentMaterialivSGIX(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetFragmentMaterialivSGIX(*face, *pname, (GLint *)popBuf());
}


//919
 void EXEC_glLightEnviSGIX(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	//glLightEnviSGIX(*pname, *param);
}


//920
 void EXEC_glDrawRangeElementsEXT(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLuint *start = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLuint *end = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glDrawRangeElementsEXT(*mode, *start, *end, *count, *type, (const GLvoid *)popBuf());
}


//921
 void EXEC_glApplyTextureEXT(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glApplyTextureEXT(*mode);
}


//922
 void EXEC_glTextureLightEXT(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glTextureLightEXT(*pname);
}


//923
 void EXEC_glTextureMaterialEXT(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glTextureMaterialEXT(*face, *mode);
}


//924
 void EXEC_glAsyncMarkerSGIX(char *commandbuf)
{
	GLuint *marker = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	glAsyncMarkerSGIX(*marker);
}


//925
 void EXEC_glFinishAsyncSGIX(char *commandbuf)
{

	pushRet(glFinishAsyncSGIX((GLuint *)popBuf()));
}


//926
 void EXEC_glPollAsyncSGIX(char *commandbuf)
{

	pushRet(glPollAsyncSGIX((GLuint *)popBuf()));
}


//927
 void EXEC_glGenAsyncMarkersSGIX(char *commandbuf)
{
	GLsizei *range = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	pushRet(glGenAsyncMarkersSGIX(*range));
}


//928
 void EXEC_glDeleteAsyncMarkersSGIX(char *commandbuf)
{
	GLuint *marker = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLsizei *range = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glDeleteAsyncMarkersSGIX(*marker, *range);
}


//929
 void EXEC_glIsAsyncMarkerSGIX(char *commandbuf)
{
	GLuint *marker = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	pushRet(glIsAsyncMarkerSGIX(*marker));
}


//930
 void EXEC_glVertexPointervINTEL(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glVertexPointervINTEL(*size, *type, (const GLvoid **)popBuf());
}


//931
 void EXEC_glNormalPointervINTEL(char *commandbuf)
{
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glNormalPointervINTEL(*type, (const GLvoid **)popBuf());
}


//932
 void EXEC_glColorPointervINTEL(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glColorPointervINTEL(*size, *type, (const GLvoid **)popBuf());
}


//933
 void EXEC_glTexCoordPointervINTEL(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glTexCoordPointervINTEL(*size, *type, (const GLvoid **)popBuf());
}


//934
 void EXEC_glPixelTransformParameteriEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glPixelTransformParameteriEXT(*target, *pname, *param);
}


//935
 void EXEC_glPixelTransformParameterfEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glPixelTransformParameterfEXT(*target, *pname, *param);
}


//936
 void EXEC_glPixelTransformParameterivEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glPixelTransformParameterivEXT(*target, *pname, (const GLint *)popBuf());
}


//937
 void EXEC_glPixelTransformParameterfvEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glPixelTransformParameterfvEXT(*target, *pname, (const GLfloat *)popBuf());
}


//938
 void EXEC_glSecondaryColor3bEXT(char *commandbuf)
{
	GLbyte *red = (GLbyte*)commandbuf;   commandbuf += sizeof(GLbyte);
	GLbyte *green = (GLbyte*)commandbuf;     commandbuf += sizeof(GLbyte);
	GLbyte *blue = (GLbyte*)commandbuf;  commandbuf += sizeof(GLbyte);

	glSecondaryColor3bEXT(*red, *green, *blue);
}


//939
 void EXEC_glSecondaryColor3bvEXT(char *commandbuf)
{

	glSecondaryColor3bvEXT((const GLbyte *)popBuf());
}


//940
 void EXEC_glSecondaryColor3dEXT(char *commandbuf)
{
	GLdouble *red = (GLdouble*)commandbuf;   commandbuf += sizeof(GLdouble);
	GLdouble *green = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *blue = (GLdouble*)commandbuf;  commandbuf += sizeof(GLdouble);

	glSecondaryColor3dEXT(*red, *green, *blue);
}


//941
 void EXEC_glSecondaryColor3dvEXT(char *commandbuf)
{

	glSecondaryColor3dvEXT((const GLdouble *)popBuf());
}


//942
 void EXEC_glSecondaryColor3fEXT(char *commandbuf)
{
	GLfloat *red = (GLfloat*)commandbuf;     commandbuf += sizeof(GLfloat);
	GLfloat *green = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *blue = (GLfloat*)commandbuf;    commandbuf += sizeof(GLfloat);

	glSecondaryColor3fEXT(*red, *green, *blue);
}


//943
 void EXEC_glSecondaryColor3fvEXT(char *commandbuf)
{

	glSecondaryColor3fvEXT((const GLfloat *)popBuf());
}


//944
 void EXEC_glSecondaryColor3iEXT(char *commandbuf)
{
	GLint *red = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLint *green = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *blue = (GLint*)commandbuf;    commandbuf += sizeof(GLint);

	glSecondaryColor3iEXT(*red, *green, *blue);
}


//945
 void EXEC_glSecondaryColor3ivEXT(char *commandbuf)
{

	glSecondaryColor3ivEXT((const GLint *)popBuf());
}


//946
 void EXEC_glSecondaryColor3sEXT(char *commandbuf)
{
	GLshort *red = (GLshort*)commandbuf;     commandbuf += sizeof(GLshort);
	GLshort *green = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *blue = (GLshort*)commandbuf;    commandbuf += sizeof(GLshort);

	glSecondaryColor3sEXT(*red, *green, *blue);
}


//947
 void EXEC_glSecondaryColor3svEXT(char *commandbuf)
{

	glSecondaryColor3svEXT((const GLshort *)popBuf());
}


//948
 void EXEC_glSecondaryColor3ubEXT(char *commandbuf)
{
	GLubyte *red = (GLubyte*)commandbuf;     commandbuf += sizeof(GLubyte);
	GLubyte *green = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *blue = (GLubyte*)commandbuf;    commandbuf += sizeof(GLubyte);

	glSecondaryColor3ubEXT(*red, *green, *blue);
}


//949
 void EXEC_glSecondaryColor3ubvEXT(char *commandbuf)
{

	glSecondaryColor3ubvEXT((const GLubyte *)popBuf());
}


//950
 void EXEC_glSecondaryColor3uiEXT(char *commandbuf)
{
	GLuint *red = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *green = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLuint *blue = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

	glSecondaryColor3uiEXT(*red, *green, *blue);
}


//951
 void EXEC_glSecondaryColor3uivEXT(char *commandbuf)
{

	glSecondaryColor3uivEXT((const GLuint *)popBuf());
}


//952
 void EXEC_glSecondaryColor3usEXT(char *commandbuf)
{
	GLushort *red = (GLushort*)commandbuf;   commandbuf += sizeof(GLushort);
	GLushort *green = (GLushort*)commandbuf;     commandbuf += sizeof(GLushort);
	GLushort *blue = (GLushort*)commandbuf;  commandbuf += sizeof(GLushort);

	glSecondaryColor3usEXT(*red, *green, *blue);
}


//953
 void EXEC_glSecondaryColor3usvEXT(char *commandbuf)
{

	glSecondaryColor3usvEXT((const GLushort *)popBuf());
}


//954
 void EXEC_glSecondaryColorPointerEXT(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glSecondaryColorPointerEXT(*size, *type, *stride, (GLvoid *)popBuf());
}


//955
 void EXEC_glTextureNormalEXT(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glTextureNormalEXT(*mode);
}


//956
 void EXEC_glMultiDrawArraysEXT(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *primcount = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glMultiDrawArraysEXT(*mode, (GLint *)popBuf(), (GLsizei *)popBuf(), *primcount);
}


//957
 void EXEC_glMultiDrawElementsEXT(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *primcount = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glMultiDrawElementsEXT(*mode, (GLsizei *)popBuf(), *type, (const GLvoid **)popBuf(), *primcount);
}


//958
 void EXEC_glFogCoordfEXT(char *commandbuf)
{
	GLfloat *coord = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glFogCoordfEXT(*coord);
}


//959
 void EXEC_glFogCoordfvEXT(char *commandbuf)
{

	glFogCoordfvEXT((const GLfloat *)popBuf());
}


//960
 void EXEC_glFogCoorddEXT(char *commandbuf)
{
	GLdouble *coord = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glFogCoorddEXT(*coord);
}


//961
 void EXEC_glFogCoorddvEXT(char *commandbuf)
{

	glFogCoorddvEXT((const GLdouble *)popBuf());
}


//962
 void EXEC_glFogCoordPointerEXT(char *commandbuf)
{
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glFogCoordPointerEXT(*type, *stride, (const GLvoid *)popBuf());
}


//963
 void EXEC_glTangent3bEXT(char *commandbuf)
{
	GLbyte *tx = (GLbyte*)commandbuf;    commandbuf += sizeof(GLbyte);
	GLbyte *ty = (GLbyte*)commandbuf;    commandbuf += sizeof(GLbyte);
	GLbyte *tz = (GLbyte*)commandbuf;    commandbuf += sizeof(GLbyte);

	//glTangent3bEXT(*tx, *ty, *tz);
}


//964
 void EXEC_glTangent3bvEXT(char *commandbuf)
{

	//glTangent3bvEXT((const GLbyte *)popBuf());
}


//965
 void EXEC_glTangent3dEXT(char *commandbuf)
{
	GLdouble *tx = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *ty = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *tz = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);

	//glTangent3dEXT(*tx, *ty, *tz);
}


//966
 void EXEC_glTangent3dvEXT(char *commandbuf)
{

	//glTangent3dvEXT((const GLdouble *)popBuf());
}


//967
 void EXEC_glTangent3fEXT(char *commandbuf)
{
	GLfloat *tx = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *ty = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *tz = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	//glTangent3fEXT(*tx, *ty, *tz);
}


//968
 void EXEC_glTangent3fvEXT(char *commandbuf)
{

	//glTangent3fvEXT((const GLfloat *)popBuf());
}


//969
 void EXEC_glTangent3iEXT(char *commandbuf)
{
	GLint *tx = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *ty = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *tz = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	//glTangent3iEXT(*tx, *ty, *tz);
}


//970
 void EXEC_glTangent3ivEXT(char *commandbuf)
{

	//glTangent3ivEXT((const GLint *)popBuf());
}


//971
 void EXEC_glTangent3sEXT(char *commandbuf)
{
	GLshort *tx = (GLshort*)commandbuf;  commandbuf += sizeof(GLshort);
	GLshort *ty = (GLshort*)commandbuf;  commandbuf += sizeof(GLshort);
	GLshort *tz = (GLshort*)commandbuf;  commandbuf += sizeof(GLshort);

	//glTangent3sEXT(*tx, *ty, *tz);
}


//972
 void EXEC_glTangent3svEXT(char *commandbuf)
{

	//glTangent3svEXT((const GLshort *)popBuf());
}


//973
 void EXEC_glBinormal3bEXT(char *commandbuf)
{
	GLbyte *bx = (GLbyte*)commandbuf;    commandbuf += sizeof(GLbyte);
	GLbyte *by = (GLbyte*)commandbuf;    commandbuf += sizeof(GLbyte);
	GLbyte *bz = (GLbyte*)commandbuf;    commandbuf += sizeof(GLbyte);

	//glBinormal3bEXT(*bx, *by, *bz);
}


//974
 void EXEC_glBinormal3bvEXT(char *commandbuf)
{

	//glBinormal3bvEXT((const GLbyte *)popBuf());
}


//975
 void EXEC_glBinormal3dEXT(char *commandbuf)
{
	GLdouble *bx = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *by = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *bz = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);

	//glBinormal3dEXT(*bx, *by, *bz);
}


//976
 void EXEC_glBinormal3dvEXT(char *commandbuf)
{

	//glBinormal3dvEXT((const GLdouble *)popBuf());
}


//977
 void EXEC_glBinormal3fEXT(char *commandbuf)
{
	GLfloat *bx = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *by = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);
	GLfloat *bz = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	//glBinormal3fEXT(*bx, *by, *bz);
}


//978
 void EXEC_glBinormal3fvEXT(char *commandbuf)
{

	//glBinormal3fvEXT((const GLfloat *)popBuf());
}


//979
 void EXEC_glBinormal3iEXT(char *commandbuf)
{
	GLint *bx = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *by = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *bz = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	//glBinormal3iEXT(*bx, *by, *bz);
}


//980
 void EXEC_glBinormal3ivEXT(char *commandbuf)
{

	//glBinormal3ivEXT((const GLint *)popBuf());
}


//981
 void EXEC_glBinormal3sEXT(char *commandbuf)
{
	GLshort *bx = (GLshort*)commandbuf;  commandbuf += sizeof(GLshort);
	GLshort *by = (GLshort*)commandbuf;  commandbuf += sizeof(GLshort);
	GLshort *bz = (GLshort*)commandbuf;  commandbuf += sizeof(GLshort);

	//glBinormal3sEXT(*bx, *by, *bz);
}


//982
 void EXEC_glBinormal3svEXT(char *commandbuf)
{

	//glBinormal3svEXT((const GLshort *)popBuf());
}


//983
 void EXEC_glTangentPointerEXT(char *commandbuf)
{
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	//glTangentPointerEXT(*type, *stride, (const GLvoid *)popBuf());
}


//984
 void EXEC_glBinormalPointerEXT(char *commandbuf)
{
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	//glBinormalPointerEXT(*type, *stride, (const GLvoid *)popBuf());
}


//985
 void EXEC_glPixelTexGenSGIX(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glPixelTexGenSGIX(*mode);
}


//986
 void EXEC_glFinishTextureSUNX(char *commandbuf)
{

	glFinishTextureSUNX();
}


//987
 void EXEC_glGlobalAlphaFactorbSUN(char *commandbuf)
{
	GLbyte *factor = (GLbyte*)commandbuf;    commandbuf += sizeof(GLbyte);

	glGlobalAlphaFactorbSUN(*factor);
}


//988
 void EXEC_glGlobalAlphaFactorsSUN(char *commandbuf)
{
	GLshort *factor = (GLshort*)commandbuf;  commandbuf += sizeof(GLshort);

	glGlobalAlphaFactorsSUN(*factor);
}


//989
 void EXEC_glGlobalAlphaFactoriSUN(char *commandbuf)
{
	GLint *factor = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glGlobalAlphaFactoriSUN(*factor);
}


//990
 void EXEC_glGlobalAlphaFactorfSUN(char *commandbuf)
{
	GLfloat *factor = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	glGlobalAlphaFactorfSUN(*factor);
}


//991
 void EXEC_glGlobalAlphaFactordSUN(char *commandbuf)
{
	GLdouble *factor = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);

	glGlobalAlphaFactordSUN(*factor);
}


//992
 void EXEC_glGlobalAlphaFactorubSUN(char *commandbuf)
{
	GLubyte *factor = (GLubyte*)commandbuf;  commandbuf += sizeof(GLubyte);

	glGlobalAlphaFactorubSUN(*factor);
}


//993
 void EXEC_glGlobalAlphaFactorusSUN(char *commandbuf)
{
	GLushort *factor = (GLushort*)commandbuf;    commandbuf += sizeof(GLushort);

	glGlobalAlphaFactorusSUN(*factor);
}


//994
 void EXEC_glGlobalAlphaFactoruiSUN(char *commandbuf)
{
	GLuint *factor = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	glGlobalAlphaFactoruiSUN(*factor);
}


//995
 void EXEC_glReplacementCodeuiSUN(char *commandbuf)
{
	GLuint *code = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

	glReplacementCodeuiSUN(*code);
}


//996
 void EXEC_glReplacementCodeusSUN(char *commandbuf)
{
	GLushort *code = (GLushort*)commandbuf;  commandbuf += sizeof(GLushort);

	glReplacementCodeusSUN(*code);
}


//997
 void EXEC_glReplacementCodeubSUN(char *commandbuf)
{
	GLubyte *code = (GLubyte*)commandbuf;    commandbuf += sizeof(GLubyte);

	glReplacementCodeubSUN(*code);
}


//998
 void EXEC_glReplacementCodeuivSUN(char *commandbuf)
{

	glReplacementCodeuivSUN((const GLuint *)popBuf());
}


//999
 void EXEC_glReplacementCodeusvSUN(char *commandbuf)
{

	glReplacementCodeusvSUN((const GLushort *)popBuf());
}


//1000
 void EXEC_glReplacementCodeubvSUN(char *commandbuf)
{

	glReplacementCodeubvSUN((const GLubyte *)popBuf());
}


//1001
 void EXEC_glReplacementCodePointerSUN(char *commandbuf)
{
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glReplacementCodePointerSUN(*type, *stride, (const GLvoid *)popBuf());
}


//1002
 void EXEC_glColor4ubVertex2fSUN(char *commandbuf)
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
 void EXEC_glColor4ubVertex2fvSUN(char *commandbuf)
{

	glColor4ubVertex2fvSUN((const GLubyte *)popBuf(), (const GLfloat *)popBuf());
}


//1004
 void EXEC_glColor4ubVertex3fSUN(char *commandbuf)
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
 void EXEC_glColor4ubVertex3fvSUN(char *commandbuf)
{

	glColor4ubVertex3fvSUN((const GLubyte *)popBuf(), (const GLfloat *)popBuf());
}


//1006
 void EXEC_glColor3fVertex3fSUN(char *commandbuf)
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
 void EXEC_glColor3fVertex3fvSUN(char *commandbuf)
{

	glColor3fVertex3fvSUN((const GLfloat *)popBuf(), (const GLfloat *)popBuf());
}


//1008
 void EXEC_glNormal3fVertex3fSUN(char *commandbuf)
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
 void EXEC_glNormal3fVertex3fvSUN(char *commandbuf)
{

	glNormal3fVertex3fvSUN((const GLfloat *)popBuf(), (const GLfloat *)popBuf());
}


//1010
 void EXEC_glColor4fNormal3fVertex3fSUN(char *commandbuf)
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
 void EXEC_glColor4fNormal3fVertex3fvSUN(char *commandbuf)
{

	glColor4fNormal3fVertex3fvSUN((const GLfloat *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf());
}


//1012
 void EXEC_glTexCoord2fVertex3fSUN(char *commandbuf)
{
	GLfloat *s = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *t = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glTexCoord2fVertex3fSUN(*s, *t, *x, *y, *z);
}


//1013
 void EXEC_glTexCoord2fVertex3fvSUN(char *commandbuf)
{

	glTexCoord2fVertex3fvSUN((const GLfloat *)popBuf(), (const GLfloat *)popBuf());
}


//1014
 void EXEC_glTexCoord4fVertex4fSUN(char *commandbuf)
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
 void EXEC_glTexCoord4fVertex4fvSUN(char *commandbuf)
{

	glTexCoord4fVertex4fvSUN((const GLfloat *)popBuf(), (const GLfloat *)popBuf());
}


//1016
 void EXEC_glTexCoord2fColor4ubVertex3fSUN(char *commandbuf)
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
 void EXEC_glTexCoord2fColor4ubVertex3fvSUN(char *commandbuf)
{

	glTexCoord2fColor4ubVertex3fvSUN((const GLfloat *)popBuf(), (const GLubyte *)popBuf(), (const GLfloat *)popBuf());
}


//1018
 void EXEC_glTexCoord2fColor3fVertex3fSUN(char *commandbuf)
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
 void EXEC_glTexCoord2fColor3fVertex3fvSUN(char *commandbuf)
{

	glTexCoord2fColor3fVertex3fvSUN((const GLfloat *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf());
}


//1020
 void EXEC_glTexCoord2fNormal3fVertex3fSUN(char *commandbuf)
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
 void EXEC_glTexCoord2fNormal3fVertex3fvSUN(char *commandbuf)
{

	glTexCoord2fNormal3fVertex3fvSUN((const GLfloat *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf());
}


//1022
 void EXEC_glTexCoord2fColor4fNormal3fVertex3fSUN(char *commandbuf)
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
 void EXEC_glTexCoord2fColor4fNormal3fVertex3fvSUN(char *commandbuf)
{

	glTexCoord2fColor4fNormal3fVertex3fvSUN((const GLfloat *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf());
}


//1024
 void EXEC_glTexCoord4fColor4fNormal3fVertex4fSUN(char *commandbuf)
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
 void EXEC_glTexCoord4fColor4fNormal3fVertex4fvSUN(char *commandbuf)
{

	glTexCoord4fColor4fNormal3fVertex4fvSUN((const GLfloat *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf());
}


//1026
 void EXEC_glReplacementCodeuiVertex3fSUN(char *commandbuf)
{
	GLuint *rc = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glReplacementCodeuiVertex3fSUN(*rc, *x, *y, *z);
}


//1027
 void EXEC_glReplacementCodeuiVertex3fvSUN(char *commandbuf)
{

	glReplacementCodeuiVertex3fvSUN((const GLuint *)popBuf(), (const GLfloat *)popBuf());
}


//1028
 void EXEC_glReplacementCodeuiColor4ubVertex3fSUN(char *commandbuf)
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
 void EXEC_glReplacementCodeuiColor4ubVertex3fvSUN(char *commandbuf)
{

	glReplacementCodeuiColor4ubVertex3fvSUN((const GLuint *)popBuf(), (const GLubyte *)popBuf(), (const GLfloat *)popBuf());
}


//1030
 void EXEC_glReplacementCodeuiColor3fVertex3fSUN(char *commandbuf)
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
 void EXEC_glReplacementCodeuiColor3fVertex3fvSUN(char *commandbuf)
{

	glReplacementCodeuiColor3fVertex3fvSUN((const GLuint *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf());
}


//1032
 void EXEC_glReplacementCodeuiNormal3fVertex3fSUN(char *commandbuf)
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
 void EXEC_glReplacementCodeuiNormal3fVertex3fvSUN(char *commandbuf)
{

	glReplacementCodeuiNormal3fVertex3fvSUN((const GLuint *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf());
}


//1034
 void EXEC_glReplacementCodeuiColor4fNormal3fVertex3fSUN(char *commandbuf)
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
 void EXEC_glReplacementCodeuiColor4fNormal3fVertex3fvSUN(char *commandbuf)
{

	glReplacementCodeuiColor4fNormal3fVertex3fvSUN((const GLuint *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf());
}


//1036
 void EXEC_glReplacementCodeuiTexCoord2fVertex3fSUN(char *commandbuf)
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
 void EXEC_glReplacementCodeuiTexCoord2fVertex3fvSUN(char *commandbuf)
{

	glReplacementCodeuiTexCoord2fVertex3fvSUN((const GLuint *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf());
}


//1038
 void EXEC_glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN(char *commandbuf)
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
 void EXEC_glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN(char *commandbuf)
{

	glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN((const GLuint *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf());
}


//1040
 void EXEC_glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN(char *commandbuf)
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
 void EXEC_glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN(char *commandbuf)
{

	glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN((const GLuint *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf(), (const GLfloat *)popBuf());
}


//1042
 void EXEC_glBlendFuncSeparateEXT(char *commandbuf)
{
	GLenum *sfactorRGB = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *dfactorRGB = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *sfactorAlpha = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *dfactorAlpha = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glBlendFuncSeparateEXT(*sfactorRGB, *dfactorRGB, *sfactorAlpha, *dfactorAlpha);
}


//1043
 void EXEC_glVertexWeightfEXT(char *commandbuf)
{
	GLfloat *weight = (GLfloat*)commandbuf;  commandbuf += sizeof(GLfloat);

	glVertexWeightfEXT(*weight);
}


//1044
 void EXEC_glVertexWeightfvEXT(char *commandbuf)
{

	glVertexWeightfvEXT((GLfloat *)popBuf());
}


//1045
 void EXEC_glVertexWeightPointerEXT(char *commandbuf)
{
	GLsizei *size = (GLsizei*)commandbuf;    commandbuf += sizeof(GLsizei);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glVertexWeightPointerEXT(*size, *type, *stride, (GLvoid *)popBuf());
}


//1046
 void EXEC_glFlushVertexArrayRangeNV(char *commandbuf)
{

	glFlushVertexArrayRangeNV();
}


//1047
 void EXEC_glVertexArrayRangeNV(char *commandbuf)
{
	GLsizei *length = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glVertexArrayRangeNV(*length, (GLvoid *)popBuf());
}


//1048
 void EXEC_glCombinerParameterfvNV(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glCombinerParameterfvNV(*pname, (const GLfloat *)popBuf());
}


//1049
 void EXEC_glCombinerParameterfNV(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glCombinerParameterfNV(*pname, *param);
}


//1050
 void EXEC_glCombinerParameterivNV(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glCombinerParameterivNV(*pname, (const GLint *)popBuf());
}


//1051
 void EXEC_glCombinerParameteriNV(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glCombinerParameteriNV(*pname, *param);
}


//1052
 void EXEC_glCombinerInputNV(char *commandbuf)
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
 void EXEC_glCombinerOutputNV(char *commandbuf)
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
 void EXEC_glFinalCombinerInputNV(char *commandbuf)
{
	GLenum *variable = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *input = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *mapping = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);
	GLenum *componentUsage = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	glFinalCombinerInputNV(*variable, *input, *mapping, *componentUsage);
}


//1055
 void EXEC_glGetCombinerInputParameterfvNV(char *commandbuf)
{
	GLenum *stage = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *portion = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);
	GLenum *variable = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetCombinerInputParameterfvNV(*stage, *portion, *variable, *pname, (GLfloat *)popBuf());
}


//1056
 void EXEC_glGetCombinerInputParameterivNV(char *commandbuf)
{
	GLenum *stage = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *portion = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);
	GLenum *variable = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetCombinerInputParameterivNV(*stage, *portion, *variable, *pname, (GLint *)popBuf());
}


//1057
 void EXEC_glGetCombinerOutputParameterfvNV(char *commandbuf)
{
	GLenum *stage = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *portion = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetCombinerOutputParameterfvNV(*stage, *portion, *pname, (GLfloat *)popBuf());
}


//1058
 void EXEC_glGetCombinerOutputParameterivNV(char *commandbuf)
{
	GLenum *stage = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *portion = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetCombinerOutputParameterivNV(*stage, *portion, *pname, (GLint *)popBuf());
}


//1059
 void EXEC_glGetFinalCombinerInputParameterfvNV(char *commandbuf)
{
	GLenum *variable = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetFinalCombinerInputParameterfvNV(*variable, *pname, (GLfloat *)popBuf());
}


//1060
 void EXEC_glGetFinalCombinerInputParameterivNV(char *commandbuf)
{
	GLenum *variable = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetFinalCombinerInputParameterivNV(*variable, *pname, (GLint *)popBuf());
}


//1061
 void EXEC_glResizeBuffersMESA(char *commandbuf)
{

	glResizeBuffersMESA();
}


//1062
 void EXEC_glWindowPos2dMESA(char *commandbuf)
{
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glWindowPos2dMESA(*x, *y);
}


//1063
 void EXEC_glWindowPos2dvMESA(char *commandbuf)
{

	glWindowPos2dvMESA((const GLdouble *)popBuf());
}


//1064
 void EXEC_glWindowPos2fMESA(char *commandbuf)
{
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glWindowPos2fMESA(*x, *y);
}


//1065
 void EXEC_glWindowPos2fvMESA(char *commandbuf)
{

	glWindowPos2fvMESA((const GLfloat *)popBuf());
}


//1066
 void EXEC_glWindowPos2iMESA(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glWindowPos2iMESA(*x, *y);
}


//1067
 void EXEC_glWindowPos2ivMESA(char *commandbuf)
{

	glWindowPos2ivMESA((const GLint *)popBuf());
}


//1068
 void EXEC_glWindowPos2sMESA(char *commandbuf)
{
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glWindowPos2sMESA(*x, *y);
}


//1069
 void EXEC_glWindowPos2svMESA(char *commandbuf)
{

	glWindowPos2svMESA((const GLshort *)popBuf());
}


//1070
 void EXEC_glWindowPos3dMESA(char *commandbuf)
{
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glWindowPos3dMESA(*x, *y, *z);
}


//1071
 void EXEC_glWindowPos3dvMESA(char *commandbuf)
{

	glWindowPos3dvMESA((const GLdouble *)popBuf());
}


//1072
 void EXEC_glWindowPos3fMESA(char *commandbuf)
{
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glWindowPos3fMESA(*x, *y, *z);
}


//1073
 void EXEC_glWindowPos3fvMESA(char *commandbuf)
{

	glWindowPos3fvMESA((const GLfloat *)popBuf());
}


//1074
 void EXEC_glWindowPos3iMESA(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *z = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glWindowPos3iMESA(*x, *y, *z);
}


//1075
 void EXEC_glWindowPos3ivMESA(char *commandbuf)
{

	glWindowPos3ivMESA((const GLint *)popBuf());
}


//1076
 void EXEC_glWindowPos3sMESA(char *commandbuf)
{
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *z = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glWindowPos3sMESA(*x, *y, *z);
}


//1077
 void EXEC_glWindowPos3svMESA(char *commandbuf)
{

	glWindowPos3svMESA((const GLshort *)popBuf());
}


//1078
 void EXEC_glWindowPos4dMESA(char *commandbuf)
{
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *w = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glWindowPos4dMESA(*x, *y, *z, *w);
}


//1079
 void EXEC_glWindowPos4dvMESA(char *commandbuf)
{

	glWindowPos4dvMESA((const GLdouble *)popBuf());
}


//1080
 void EXEC_glWindowPos4fMESA(char *commandbuf)
{
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *w = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glWindowPos4fMESA(*x, *y, *z, *w);
}


//1081
 void EXEC_glWindowPos4fvMESA(char *commandbuf)
{

	glWindowPos4fvMESA((const GLfloat *)popBuf());
}


//1082
 void EXEC_glWindowPos4iMESA(char *commandbuf)
{
	GLint *x = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *y = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *z = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLint *w = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glWindowPos4iMESA(*x, *y, *z, *w);
}


//1083
 void EXEC_glWindowPos4ivMESA(char *commandbuf)
{

	glWindowPos4ivMESA((const GLint *)popBuf());
}


//1084
 void EXEC_glWindowPos4sMESA(char *commandbuf)
{
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *z = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *w = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glWindowPos4sMESA(*x, *y, *z, *w);
}


//1085
 void EXEC_glWindowPos4svMESA(char *commandbuf)
{

	glWindowPos4svMESA((const GLshort *)popBuf());
}


//1086
 void EXEC_glMultiModeDrawArraysIBM(char *commandbuf)
{
	GLsizei *primcount = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLint *modestride = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glMultiModeDrawArraysIBM((const GLenum *)popBuf(), (const GLint *)popBuf(), (const GLsizei *)popBuf(), *primcount, *modestride);
}


//1087
 void EXEC_glMultiModeDrawElementsIBM(char *commandbuf)
{
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *primcount = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLint *modestride = (GLint*)commandbuf;  commandbuf += sizeof(GLint);

	glMultiModeDrawElementsIBM((const GLenum *)popBuf(), (const GLsizei *)popBuf(), *type, (const GLvoid * const *)popBuf(), *primcount, *modestride);
}


//1088
 void EXEC_glColorPointerListIBM(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLint *stride = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *ptrstride = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glColorPointerListIBM(*size, *type, *stride, (const GLvoid **)popBuf(), *ptrstride);
}


//1089
 void EXEC_glSecondaryColorPointerListIBM(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLint *stride = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *ptrstride = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glSecondaryColorPointerListIBM(*size, *type, *stride, (const GLvoid **)popBuf(), *ptrstride);
}


//1090
 void EXEC_glEdgeFlagPointerListIBM(char *commandbuf)
{
	GLint *stride = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *ptrstride = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glEdgeFlagPointerListIBM(*stride, (const GLboolean **)popBuf(), *ptrstride);
}


//1091
 void EXEC_glFogCoordPointerListIBM(char *commandbuf)
{
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLint *stride = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *ptrstride = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glFogCoordPointerListIBM(*type, *stride, (const GLvoid **)popBuf(), *ptrstride);
}


//1092
 void EXEC_glIndexPointerListIBM(char *commandbuf)
{
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLint *stride = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *ptrstride = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glIndexPointerListIBM(*type, *stride, (const GLvoid **)popBuf(), *ptrstride);
}


//1093
 void EXEC_glNormalPointerListIBM(char *commandbuf)
{
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLint *stride = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *ptrstride = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glNormalPointerListIBM(*type, *stride, (const GLvoid **)popBuf(), *ptrstride);
}


//1094
 void EXEC_glTexCoordPointerListIBM(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLint *stride = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *ptrstride = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glTexCoordPointerListIBM(*size, *type, *stride, (const GLvoid **)popBuf(), *ptrstride);
}


//1095
 void EXEC_glVertexPointerListIBM(char *commandbuf)
{
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLint *stride = (GLint*)commandbuf;  commandbuf += sizeof(GLint);
	GLint *ptrstride = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glVertexPointerListIBM(*size, *type, *stride, (const GLvoid **)popBuf(), *ptrstride);
}


//1096
 void EXEC_glTbufferMask3DFX(char *commandbuf)
{
	GLuint *mask = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

	glTbufferMask3DFX(*mask);
}


//1097
 void EXEC_glSampleMaskEXT(char *commandbuf)
{
	GLclampf *value = (GLclampf*)commandbuf;     commandbuf += sizeof(GLclampf);
	GLboolean *invert = (GLboolean*)commandbuf;  commandbuf += sizeof(GLboolean);

	glSampleMaskEXT(*value, *invert);
}


//1098
 void EXEC_glSamplePatternEXT(char *commandbuf)
{
	GLenum *pattern = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);

	glSamplePatternEXT(*pattern);
}


//1099
 void EXEC_glTextureColorMaskSGIS(char *commandbuf)
{
	GLboolean *red = (GLboolean*)commandbuf;     commandbuf += sizeof(GLboolean);
	GLboolean *green = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);
	GLboolean *blue = (GLboolean*)commandbuf;    commandbuf += sizeof(GLboolean);
	GLboolean *alpha = (GLboolean*)commandbuf;   commandbuf += sizeof(GLboolean);

	//glTextureColorMaskSGIS(*red, *green, *blue, *alpha);
}


//1100
 void EXEC_glDeleteFencesNV(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glDeleteFencesNV(*n, (const GLuint *)popBuf());
}


//1101
 void EXEC_glGenFencesNV(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glGenFencesNV(*n, (GLuint *)popBuf());
}


//1102
 void EXEC_glIsFenceNV(char *commandbuf)
{
	GLuint *fence = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	pushRet(glIsFenceNV(*fence));
}


//1103
 void EXEC_glTestFenceNV(char *commandbuf)
{
	GLuint *fence = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	pushRet(glTestFenceNV(*fence));
}


//1104
 void EXEC_glGetFenceivNV(char *commandbuf)
{
	GLuint *fence = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetFenceivNV(*fence, *pname, (GLint *)popBuf());
}


//1105
 void EXEC_glFinishFenceNV(char *commandbuf)
{
	GLuint *fence = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glFinishFenceNV(*fence);
}


//1106
 void EXEC_glSetFenceNV(char *commandbuf)
{
	GLuint *fence = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *condition = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glSetFenceNV(*fence, *condition);
}


//1107
 void EXEC_glMapControlPointsNV(char *commandbuf)
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
 void EXEC_glMapParameterivNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glMapParameterivNV(*target, *pname, (const GLint *)popBuf());
}


//1109
 void EXEC_glMapParameterfvNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glMapParameterfvNV(*target, *pname, (const GLfloat *)popBuf());
}


//1110
 void EXEC_glGetMapControlPointsNV(char *commandbuf)
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
 void EXEC_glGetMapParameterivNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetMapParameterivNV(*target, *pname, (GLint *)popBuf());
}


//1112
 void EXEC_glGetMapParameterfvNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetMapParameterfvNV(*target, *pname, (GLfloat *)popBuf());
}


//1113
 void EXEC_glGetMapAttribParameterivNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetMapAttribParameterivNV(*target, *index, *pname, (GLint *)popBuf());
}


//1114
 void EXEC_glGetMapAttribParameterfvNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetMapAttribParameterfvNV(*target, *index, *pname, (GLfloat *)popBuf());
}


//1115
 void EXEC_glEvalMapsNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glEvalMapsNV(*target, *mode);
}


//1116
 void EXEC_glCombinerStageParameterfvNV(char *commandbuf)
{
	GLenum *stage = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glCombinerStageParameterfvNV(*stage, *pname, (const GLfloat *)popBuf());
}


//1117
 void EXEC_glGetCombinerStageParameterfvNV(char *commandbuf)
{
	GLenum *stage = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetCombinerStageParameterfvNV(*stage, *pname, (GLfloat *)popBuf());
}


//1118
 void EXEC_glAreProgramsResidentNV(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	pushRet(glAreProgramsResidentNV(*n, (const GLuint *)popBuf(), (GLboolean *)popBuf()));
}


//1119
 void EXEC_glBindProgramNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	glBindProgramNV(*target, *program);
}


//1120
 void EXEC_glDeleteProgramsNV(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glDeleteProgramsNV(*n, (const GLuint *)popBuf());
}


//1121
 void EXEC_glExecuteProgramNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	glExecuteProgramNV(*target, *id, (const GLfloat *)popBuf());
}


//1122
 void EXEC_glGenProgramsNV(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glGenProgramsNV(*n, (GLuint *)popBuf());
}


//1123
 void EXEC_glGetProgramParameterdvNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetProgramParameterdvNV(*target, *index, *pname, (GLdouble *)popBuf());
}


//1124
 void EXEC_glGetProgramParameterfvNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetProgramParameterfvNV(*target, *index, *pname, (GLfloat *)popBuf());
}


//1125
 void EXEC_glGetProgramivNV(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetProgramivNV(*id, *pname, (GLint *)popBuf());
}


//1126
 void EXEC_glGetProgramStringNV(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetProgramStringNV(*id, *pname, (GLubyte *)popBuf());
}


//1127
 void EXEC_glGetTrackMatrixivNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *address = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetTrackMatrixivNV(*target, *address, *pname, (GLint *)popBuf());
}


//1128
 void EXEC_glGetVertexAttribdvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetVertexAttribdvNV(*index, *pname, (GLdouble *)popBuf());
}


//1129
 void EXEC_glGetVertexAttribfvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetVertexAttribfvNV(*index, *pname, (GLfloat *)popBuf());
}


//1130
 void EXEC_glGetVertexAttribivNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetVertexAttribivNV(*index, *pname, (GLint *)popBuf());
}


//1131
 void EXEC_glGetVertexAttribPointervNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glGetVertexAttribPointervNV(*index, *pname, (GLvoid **)popBuf());
}


//1132
 void EXEC_glIsProgramNV(char *commandbuf)
{
	GLuint *program = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	pushRet(glIsProgramNV(*program));
}


//1133
 void EXEC_glLoadProgramNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLsizei *len = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);

	glLoadProgramNV(*target, *id, *len, (const GLubyte *)popBuf());
}


//1134
 void EXEC_glProgramParameter4dNV(char *commandbuf)
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
 void EXEC_glProgramParameter4dvNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glProgramParameter4dvNV(*target, *index, (const GLdouble *)popBuf());
}


//1136
 void EXEC_glProgramParameter4fNV(char *commandbuf)
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
 void EXEC_glProgramParameter4fvNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glProgramParameter4fvNV(*target, *index, (const GLfloat *)popBuf());
}


//1138
 void EXEC_glProgramParameters4dvNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLuint *num = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	glProgramParameters4dvNV(*target, *index, *num, (const GLdouble *)popBuf());
}


//1139
 void EXEC_glProgramParameters4fvNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLuint *num = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	glProgramParameters4fvNV(*target, *index, *num, (const GLfloat *)popBuf());
}


//1140
 void EXEC_glRequestResidentProgramsNV(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glRequestResidentProgramsNV(*n, (GLuint *)popBuf());
}


//1141
 void EXEC_glTrackMatrixNV(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *address = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLenum *matrix = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *transform = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glTrackMatrixNV(*target, *address, *matrix, *transform);
}


//1142
 void EXEC_glVertexAttribPointerNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLint *size = (GLint*)commandbuf;    commandbuf += sizeof(GLint);
	GLenum *type = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLsizei *stride = (GLsizei*)commandbuf;  commandbuf += sizeof(GLsizei);

	glVertexAttribPointerNV(*index, *size, *type, *stride, (const GLvoid *)popBuf());
}


//1143
 void EXEC_glVertexAttrib1sNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glVertexAttrib1sNV(*index, *x);
}


//1144
 void EXEC_glVertexAttrib1svNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib1svNV(*index, (const GLshort *)popBuf());
}


//1145
 void EXEC_glVertexAttrib2sNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glVertexAttrib2sNV(*index, *x, *y);
}


//1146
 void EXEC_glVertexAttrib2svNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib2svNV(*index, (const GLshort *)popBuf());
}


//1147
 void EXEC_glVertexAttrib3sNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *z = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glVertexAttrib3sNV(*index, *x, *y, *z);
}


//1148
 void EXEC_glVertexAttrib3svNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib3svNV(*index, (const GLshort *)popBuf());
}


//1149
 void EXEC_glVertexAttrib4sNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLshort *x = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *y = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *z = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);
	GLshort *w = (GLshort*)commandbuf;   commandbuf += sizeof(GLshort);

	glVertexAttrib4sNV(*index, *x, *y, *z, *w);
}


//1150
 void EXEC_glVertexAttrib4svNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4svNV(*index, (const GLshort *)popBuf());
}


//1151
 void EXEC_glVertexAttrib1fNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glVertexAttrib1fNV(*index, *x);
}


//1152
 void EXEC_glVertexAttrib1fvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib1fvNV(*index, (const GLfloat *)popBuf());
}


//1153
 void EXEC_glVertexAttrib2fNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glVertexAttrib2fNV(*index, *x, *y);
}


//1154
 void EXEC_glVertexAttrib2fvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib2fvNV(*index, (const GLfloat *)popBuf());
}


//1155
 void EXEC_glVertexAttrib3fNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glVertexAttrib3fNV(*index, *x, *y, *z);
}


//1156
 void EXEC_glVertexAttrib3fvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib3fvNV(*index, (const GLfloat *)popBuf());
}


//1157
 void EXEC_glVertexAttrib4fNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLfloat *x = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *y = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *z = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);
	GLfloat *w = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	glVertexAttrib4fNV(*index, *x, *y, *z, *w);
}


//1158
 void EXEC_glVertexAttrib4fvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4fvNV(*index, (const GLfloat *)popBuf());
}


//1159
 void EXEC_glVertexAttrib1dNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glVertexAttrib1dNV(*index, *x);
}


//1160
 void EXEC_glVertexAttrib1dvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib1dvNV(*index, (const GLdouble *)popBuf());
}


//1161
 void EXEC_glVertexAttrib2dNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glVertexAttrib2dNV(*index, *x, *y);
}


//1162
 void EXEC_glVertexAttrib2dvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib2dvNV(*index, (const GLdouble *)popBuf());
}


//1163
 void EXEC_glVertexAttrib3dNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glVertexAttrib3dNV(*index, *x, *y, *z);
}


//1164
 void EXEC_glVertexAttrib3dvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib3dvNV(*index, (const GLdouble *)popBuf());
}


//1165
 void EXEC_glVertexAttrib4dNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLdouble *x = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *y = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *z = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *w = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);

	glVertexAttrib4dNV(*index, *x, *y, *z, *w);
}


//1166
 void EXEC_glVertexAttrib4dvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4dvNV(*index, (const GLdouble *)popBuf());
}


//1167
 void EXEC_glVertexAttrib4ubNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLubyte *x = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *y = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *z = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);
	GLubyte *w = (GLubyte*)commandbuf;   commandbuf += sizeof(GLubyte);

	glVertexAttrib4ubNV(*index, *x, *y, *z, *w);
}


//1168
 void EXEC_glVertexAttrib4ubvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	glVertexAttrib4ubvNV(*index, (const GLubyte *)popBuf());
}


//1169
 void EXEC_glVertexAttribs1svNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glVertexAttribs1svNV(*index, *n, (const GLshort *)popBuf());
}


//1170
 void EXEC_glVertexAttribs2svNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glVertexAttribs2svNV(*index, *n, (const GLshort *)popBuf());
}


//1171
 void EXEC_glVertexAttribs3svNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glVertexAttribs3svNV(*index, *n, (const GLshort *)popBuf());
}


//1172
 void EXEC_glVertexAttribs4svNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glVertexAttribs4svNV(*index, *n, (const GLshort *)popBuf());
}


//1173
 void EXEC_glVertexAttribs1fvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glVertexAttribs1fvNV(*index, *n, (const GLfloat *)popBuf());
}


//1174
 void EXEC_glVertexAttribs2fvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glVertexAttribs2fvNV(*index, *n, (const GLfloat *)popBuf());
}


//1175
 void EXEC_glVertexAttribs3fvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glVertexAttribs3fvNV(*index, *n, (const GLfloat *)popBuf());
}


//1176
 void EXEC_glVertexAttribs4fvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glVertexAttribs4fvNV(*index, *n, (const GLfloat *)popBuf());
}


//1177
 void EXEC_glVertexAttribs1dvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glVertexAttribs1dvNV(*index, *n, (const GLdouble *)popBuf());
}


//1178
 void EXEC_glVertexAttribs2dvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glVertexAttribs2dvNV(*index, *n, (const GLdouble *)popBuf());
}


//1179
 void EXEC_glVertexAttribs3dvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glVertexAttribs3dvNV(*index, *n, (const GLdouble *)popBuf());
}


//1180
 void EXEC_glVertexAttribs4dvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glVertexAttribs4dvNV(*index, *n, (const GLdouble *)popBuf());
}


//1181
 void EXEC_glVertexAttribs4ubvNV(char *commandbuf)
{
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glVertexAttribs4ubvNV(*index, *n, (const GLubyte *)popBuf());
}


//1182
 void EXEC_glGenFragmentShadersATI(char *commandbuf)
{
	GLuint *range = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);

	pushRet(glGenFragmentShadersATI(*range));
}


//1183
 void EXEC_glBindFragmentShaderATI(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	glBindFragmentShaderATI(*id);
}


//1184
 void EXEC_glDeleteFragmentShaderATI(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);

	glDeleteFragmentShaderATI(*id);
}


//1185
 void EXEC_glBeginFragmentShaderATI(char *commandbuf)
{

	glBeginFragmentShaderATI();
}


//1186
 void EXEC_glEndFragmentShaderATI(char *commandbuf)
{

	glEndFragmentShaderATI();
}


//1187
 void EXEC_glPassTexCoordATI(char *commandbuf)
{
	GLuint *dst = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *coord = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLenum *swizzle = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);

	glPassTexCoordATI(*dst, *coord, *swizzle);
}


//1188
 void EXEC_glSampleMapATI(char *commandbuf)
{
	GLuint *dst = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);
	GLuint *interp = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLenum *swizzle = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);

	glSampleMapATI(*dst, *interp, *swizzle);
}


//1189
 void EXEC_glColorFragmentOp1ATI(char *commandbuf)
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
 void EXEC_glColorFragmentOp2ATI(char *commandbuf)
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
 void EXEC_glColorFragmentOp3ATI(char *commandbuf)
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
 void EXEC_glAlphaFragmentOp1ATI(char *commandbuf)
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
 void EXEC_glAlphaFragmentOp2ATI(char *commandbuf)
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
 void EXEC_glAlphaFragmentOp3ATI(char *commandbuf)
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
 void EXEC_glSetFragmentShaderConstantATI(char *commandbuf)
{
	GLuint *dst = (GLuint*)commandbuf;   commandbuf += sizeof(GLuint);

	glSetFragmentShaderConstantATI(*dst, (const GLfloat *)popBuf());
}


//1196
 void EXEC_glDrawMeshArraysSUN(char *commandbuf)
{
	GLenum *mode = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLint *first = (GLint*)commandbuf;   commandbuf += sizeof(GLint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *width = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	//glDrawMeshArraysSUN(*mode, *first, *count, *width);
}


//1197
 void EXEC_glPointParameteriNV(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLint *param = (GLint*)commandbuf;   commandbuf += sizeof(GLint);

	glPointParameteriNV(*pname, *param);
}


//1198
 void EXEC_glPointParameterivNV(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glPointParameterivNV(*pname, (const GLint *)popBuf());
}


//1199
 void EXEC_glActiveStencilFaceEXT(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	glActiveStencilFaceEXT(*face);
}


//1200
 void EXEC_glDrawBuffersATI(char *commandbuf)
{
	GLsizei *n = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	glDrawBuffersATI(*n, (const GLenum *)popBuf());
}


//1201
 void EXEC_glProgramNamedParameter4fNV(char *commandbuf)
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
 void EXEC_glProgramNamedParameter4dNV(char *commandbuf)
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
 void EXEC_glProgramNamedParameter4fvNV(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLsizei *len = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);

	glProgramNamedParameter4fvNV(*id, *len, (const GLubyte *)popBuf(), (const GLfloat *)popBuf());
}


//1204
 void EXEC_glProgramNamedParameter4dvNV(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLsizei *len = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);

	glProgramNamedParameter4dvNV(*id, *len, (const GLubyte *)popBuf(), (const GLdouble *)popBuf());
}


//1205
 void EXEC_glGetProgramNamedParameterfvNV(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLsizei *len = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);

	glGetProgramNamedParameterfvNV(*id, *len, (const GLubyte *)popBuf(), (GLfloat *)popBuf());
}


//1206
 void EXEC_glGetProgramNamedParameterdvNV(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLsizei *len = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);

	glGetProgramNamedParameterdvNV(*id, *len, (const GLubyte *)popBuf(), (GLdouble *)popBuf());
}


//1207
 void EXEC_glDepthBoundsEXT(char *commandbuf)
{
	GLclampd *zmin = (GLclampd*)commandbuf;  commandbuf += sizeof(GLclampd);
	GLclampd *zmax = (GLclampd*)commandbuf;  commandbuf += sizeof(GLclampd);

	glDepthBoundsEXT(*zmin, *zmax);
}


//1208
 void EXEC_glBlendEquationSeparateEXT(char *commandbuf)
{
	GLenum *modeRGB = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);
	GLenum *modeA = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glBlendEquationSeparateEXT(*modeRGB, *modeA);
}


//1209
 void EXEC_glBlitFramebufferEXT(char *commandbuf)
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
 void EXEC_glBlendEquationSeparateATI(char *commandbuf)
{
	GLenum *modeRGB = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);
	GLenum *modeA = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	//glBlendEquationSeparateATI(*modeRGB, *modeA);
}


//1211
 void EXEC_glStencilOpSeparateATI(char *commandbuf)
{
	GLenum *face = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *sfail = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *zfail = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *zpass = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	glStencilOpSeparateATI(*face, *sfail, *zfail, *zpass);
}


//1212
 void EXEC_glStencilFuncSeparateATI(char *commandbuf)
{
	GLenum *frontfunc = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLenum *backfunc = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLint *ref = (GLint*)commandbuf;     commandbuf += sizeof(GLint);
	GLuint *mask = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

	glStencilFuncSeparateATI(*frontfunc, *backfunc, *ref, *mask);
}


//1213
 void EXEC_glProgramEnvParameters4fvEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	#ifndef SYMPHONY
	glProgramEnvParameters4fvEXT(*target, *index, *count, (const GLfloat *)popBuf());
	#endif
}


//1214
 void EXEC_glProgramLocalParameters4fvEXT(char *commandbuf)
{
	GLenum *target = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLuint *index = (GLuint*)commandbuf;     commandbuf += sizeof(GLuint);
	GLsizei *count = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);

	#ifndef SYMPHONY
	glProgramLocalParameters4fvEXT(*target, *index, *count, (const GLfloat *)popBuf());
	#endif
}


//1215
 void EXEC_glGetQueryObjecti64vEXT(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	#ifndef SYMPHONY
	glGetQueryObjecti64vEXT(*id, *pname, (GLint64EXT *)popBuf());
	#endif
}


//1216
 void EXEC_glGetQueryObjectui64vEXT(char *commandbuf)
{
	GLuint *id = (GLuint*)commandbuf;    commandbuf += sizeof(GLuint);
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	#ifndef SYMPHONY
	glGetQueryObjectui64vEXT(*id, *pname, (GLuint64EXT *)popBuf());
	#endif
}


//1217
 void EXEC_glBlendFuncSeparateINGR(char *commandbuf)
{
	GLenum *sfactorRGB = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *dfactorRGB = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLenum *sfactorAlpha = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
	GLenum *dfactorAlpha = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	//glBlendFuncSeparateINGR(*sfactorRGB, *dfactorRGB, *sfactorAlpha, *dfactorAlpha);
}


//1218
 void EXEC_glCreateDebugObjectMESA(char *commandbuf)
{

	//pushRet(glCreateDebugObjectMESA());
}


//1219
 void EXEC_glClearDebugLogMESA(char *commandbuf)
{
	GLhandleARB *obj = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);
	GLenum *logType = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);
	GLenum *shaderType = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	//glClearDebugLogMESA(*obj, *logType, *shaderType);
}


//1220
 void EXEC_glGetDebugLogMESA(char *commandbuf)
{
	GLhandleARB *obj = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);
	GLenum *logType = (GLenum*)commandbuf;      commandbuf += sizeof(GLenum);
	GLenum *shaderType = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);
	GLsizei *maxLength = (GLsizei*)commandbuf;   commandbuf += sizeof(GLsizei);
	GLsizei *length = (GLsizei*)commandbuf;     commandbuf += sizeof(GLsizei);

	//glGetDebugLogMESA(*obj, *logType, *shaderType, *maxLength, length, (GLcharARB *)popBuf());
}


//1221
 void EXEC_glGetDebugLogLengthMESA(char *commandbuf)
{
	GLhandleARB *obj = (GLhandleARB*)commandbuf;     commandbuf += sizeof(GLhandleARB);
	GLenum *logType = (GLenum*)commandbuf;   commandbuf += sizeof(GLenum);
	GLenum *shaderType = (GLenum*)commandbuf;    commandbuf += sizeof(GLenum);

	//pushRet(glGetDebugLogLengthMESA(*obj, *logType, *shaderType));
}


//1222
 void EXEC_glPointParameterfSGIS(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);
	GLfloat *param = (GLfloat*)commandbuf;   commandbuf += sizeof(GLfloat);

	//glPointParameterfSGIS(*pname, *param);
}


//1223
 void EXEC_glPointParameterfvSGIS(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	//glPointParameterfvSGIS(*pname, (const GLfloat *)popBuf());
}


//1224
 void EXEC_glIglooInterfaceSGIX(char *commandbuf)
{
	GLenum *pname = (GLenum*)commandbuf;     commandbuf += sizeof(GLenum);

	//glIglooInterfaceSGIX(*pname, (const GLvoid *)popBuf());
}


//1225
 void EXEC_glDeformationMap3dSGIX(char *commandbuf)
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
 void EXEC_glDeformationMap3fSGIX(char *commandbuf)
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
 void EXEC_glDeformSGIX(char *commandbuf)
{
	GLenum *mask = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	//glDeformSGIX(*mask);
}


//1228
 void EXEC_glLoadIdentityDeformationMapSGIX(char *commandbuf)
{
	GLenum *mask = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);

	//glLoadIdentityDeformationMapSGIX(*mask);
}


//1229
 void EXEC_glGetStringi(char *commandbuf)
{
    GLenum *name = (GLenum*)commandbuf;  commandbuf += sizeof(GLenum);
    GLuint *index = (GLuint*)commandbuf;  commandbuf += sizeof(GLuint);

    string str = string((const char*)glGetStringi(*name, *index));
    pushRet(str.c_str(), str.size()+1, false);
}
