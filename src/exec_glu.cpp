#include "exec.hpp"
#include <GL/glu.h>

#define LOG(x)

//1501
 void EXEC_gluBeginCurve(char *commandbuf)
{
	LOG("Called unimplemted stub gluBeginCurve!\n");
	// (GLUnurbs* nurb)
}


//1502
 void EXEC_gluBeginPolygon(char *commandbuf)
{
	LOG("Called unimplemted stub gluBeginPolygon!\n");
	//(GLUtesselator* tess)
}


//1503
 void EXEC_gluBeginSurface(char *commandbuf)
{
	LOG("Called unimplemted stub gluBeginSurface!\n");
	// (GLUnurbs* nurb)
}


//1504
 void EXEC_gluBeginTrim(char *commandbuf)
{
	LOG("Called unimplemted stub gluBeginTrim!\n");
	// (GLUnurbs* nurb)
}


//1505
 void EXEC_gluBuild1DMipmapLevels(char *commandbuf)
{
	LOG("Called unimplemted stub gluBuild1DMipmapLevels !\n");
	// (GLenum target, GLint internalFormat, GLsizei width, GLenum format, GLenum type, GLint level, GLint base, GLint max, const void *data)
	//returns GLint
}


//1506
 void EXEC_gluBuild1DMipmaps(char *commandbuf)
{
	LOG("Called unimplemted stub gluBuild1DMipmaps!\n");
	//(GLenum target, GLint internalFormat, GLsizei width, GLenum format, GLenum type, const void *data)
	//returns GLint
}


//1507
 void EXEC_gluBuild2DMipmapLevels(char *commandbuf)
{
	LOG("Called unimplemted stub gluBuild2DMipmapLevels!\n");
	//(GLenum target, GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, GLint level, GLint base, GLint max, const void *data)
	//returns GLint
}


//1508
 void EXEC_gluBuild2DMipmaps(char *commandbuf)
{
	LOG("Called unimplemted stub gluBuild2DMipmaps!\n");
	//(GLenum target, GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *data)
	//returns GLint
}


//1509
 void EXEC_gluBuild3DMipmapLevels(char *commandbuf)
{
	LOG("Called unimplemted stub gluBuild3DMipmapLevels!\n");
	//(GLenum target, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLint level, GLint base, GLint max, const void *data)
	//returns GLint
}


//1510
 void EXEC_gluBuild3DMipmaps(char *commandbuf)
{
	//(GLenum target, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *data)
	LOG("Called unimplemted stub gluBuild3DMipmaps!\n");
	//returns GLint
}


//1511
 void EXEC_gluCheckExtension(char *commandbuf)
{
	LOG("Called unimplemted stub gluCheckExtension!\n");
	//(const GLubyte *extName, const GLubyte *extString)
	//returns GLboolean
}


//1512
 void EXEC_gluCylinder(char *commandbuf)
{
	LOG("Called unimplemted stub gluCylinder!\n");
	//(GLUquadric* quad, GLdouble base, GLdouble top, GLdouble height, GLint slices, GLint stacks)
}


//1513
 void EXEC_gluDeleteNurbsRenderer(char *commandbuf)
{
	LOG("Called unimplemted stub gluDeleteNurbsRenderer!\n");
	//(GLUnurbs* nurb)
}


//1514
 void EXEC_gluDeleteQuadric(char *commandbuf)
{
	LOG("Called unimplemted stub gluDeleteQuadric!\n");
	//(GLUquadric* quad)
}


//1515
 void EXEC_gluDeleteTess(char *commandbuf)
{
	LOG("Called unimplemted stub gluDeleteTess!\n");
	//(GLUtesselator* tess)
}


//1516
 void EXEC_gluDisk(char *commandbuf)
{
	LOG("Called unimplemted stub gluDisk!\n");
	//(GLUquadric* quad, GLdouble inner, GLdouble outer, GLint slices, GLint loops)
}


//1517
 void EXEC_gluEndCurve(char *commandbuf)
{
	LOG("Called unimplemted stub gluEndCurve!\n");
	//(GLUnurbs* nurb)
}


//1518
 void EXEC_gluEndPolygon(char *commandbuf)
{
	LOG("Called unimplemted stub gluEndPolygon!\n");
	//(GLUtesselator* tess)
}


//1519
 void EXEC_gluEndSurface(char *commandbuf)
{
	LOG("Called unimplemted stub gluEndSurface!\n");
	//(GLUnurbs* nurb)
}


//1520
 void EXEC_gluEndTrim(char *commandbuf)
{
	LOG("Called unimplemted stub gluEndTrim!\n");
	//(GLUnurbs* nurb)
}


//1521
 void EXEC_gluErrorString(char *commandbuf)
{
	LOG("Called unimplemted stub gluErrorString!\n");
	//(GLenum error)
	//returns const GLubyte *
}


//1522
 void EXEC_gluGetNurbsProperty(char *commandbuf)
{
	LOG("Called unimplemted stub gluGetNurbsProperty!\n");
	//(GLUnurbs* nurb, GLenum property, GLfloat* data)
}


//1523
 void EXEC_gluGetString(char *commandbuf)
{
	LOG("Called unimplemted stub gluGetString!\n");
	//(GLenum name)
	//returns const GLubyte *
}


//1524
 void EXEC_gluGetTessProperty(char *commandbuf)
{
	LOG("Called unimplemted stub gluGetTessProperty!\n");
	//(GLUtesselator* tess, GLenum which, GLdouble* data)
}


//1525
 void EXEC_gluLoadSamplingMatrices(char *commandbuf)
{
	LOG("Called unimplemted stub gluLoadSamplingMatrices!\n");
	//(GLUnurbs* nurb, const GLfloat *model, const GLfloat *perspective, const GLint *view)
}


//1526
 void EXEC_gluLookAt(char *commandbuf)
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
 void EXEC_gluNewNurbsRenderer(char *commandbuf)
{
	LOG("Called unimplemted stub gluNewNurbsRenderer!\n");
	//returns GLUnurbs*
}


//1528
 void EXEC_gluNewQuadric(char *commandbuf)
{
	LOG("Called unimplemted stub gluNewQuadric!\n");
	//returns GLUquadric*
}


//1529
 void EXEC_gluNewTess(char *commandbuf)
{
	LOG("Called unimplemted stub gluNewTess!\n");
	//returns GLUtesselator*
}


//1530
 void EXEC_gluNextContour(char *commandbuf)
{
	LOG("Called unimplemted stub gluNextContour!\n");
	//(GLUtesselator* tess, GLenum type)
}


//1531
 void EXEC_gluNurbsCallback(char *commandbuf)
{
	LOG("Called unimplemted stub gluNurbsCallback!\n");
	//(GLUnurbs* nurb, GLenum which, _GLUfuncptr CallBackFunc)
}


//1532
 void EXEC_gluNurbsCallbackData(char *commandbuf)
{
	LOG("Called unimplemted stub gluNurbsCallbackData!\n");
	//(GLUnurbs* nurb, GLvoid* userData)
}


//1533
 void EXEC_gluNurbsCallbackDataEXT(char *commandbuf)
{
	LOG("Called unimplemted stub gluNurbsCallbackDataEXT!\n");
	//(GLUnurbs* nurb, GLvoid* userData)
}


//1534
 void EXEC_gluNurbsCurve(char *commandbuf)
{
	LOG("Called unimplemted stub gluNurbsCurve!\n");
	//(GLUnurbs* nurb, GLint knotCount, GLfloat *knots, GLint stride, GLfloat *control, GLint order, GLenum type)
}


//1535
 void EXEC_gluNurbsProperty(char *commandbuf)
{
	LOG("Called unimplemted stub gluNurbsProperty!\n");
	//(GLUnurbs* nurb, GLenum property, GLfloat value)
}


//1536
 void EXEC_gluNurbsSurface(char *commandbuf)
{
	LOG("Called unimplemted stub gluNurbsSurface!\n");
	//(GLUnurbs* nurb, GLint sKnotCount, GLfloat* sKnots, GLint tKnotCount, GLfloat* tKnots, GLint sStride, GLint tStride, GLfloat* control, GLint sOrder, GLint tOrder, GLenum type)
}


//1537
 void EXEC_gluOrtho2D(char *commandbuf)
{
	LOG("Called unimplemted stub gluOrtho2D!\n");
	//(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top)
}


//1538
 void EXEC_gluPartialDisk(char *commandbuf)
{
	LOG("Called unimplemted stub gluPartialDisk!\n");
	//(GLUquadric* quad, GLdouble inner, GLdouble outer, GLint slices, GLint loops, GLdouble start, GLdouble sweep)
}


//1539
 void EXEC_gluPerspective(char *commandbuf)
{
	GLdouble *fovy = (GLdouble*)commandbuf;  commandbuf += sizeof(GLdouble);
	GLdouble *aspect = (GLdouble*)commandbuf;    commandbuf += sizeof(GLdouble);
	GLdouble *zNear = (GLdouble*)commandbuf;     commandbuf += sizeof(GLdouble);
	GLdouble *zFar = (GLdouble*)commandbuf;  commandbuf += sizeof(GLdouble);
	gluPerspective(*fovy, *aspect, *zNear, *zFar);
}


//1540
 void EXEC_gluPickMatrix(char *commandbuf)
{
	LOG("Called unimplemted stub gluPickMatrix!\n");
	//(GLdouble x, GLdouble y, GLdouble delX, GLdouble delY, GLint *viewport)
}


//1541
 void EXEC_gluProject(char *commandbuf)
{
	LOG("Called unimplemted stub gluProject!\n");
	//(GLdouble objX, GLdouble objY, GLdouble objZ, const GLdouble *model, const GLdouble *proj, const GLint *view, GLdouble* winX, GLdouble* winY, GLdouble* winZ)
	//returns GLint
}


//1542
 void EXEC_gluPwlCurve(char *commandbuf)
{
	LOG("Called unimplemted stub gluPwlCurve!\n");
	//(GLUnurbs* nurb, GLint count, GLfloat* data, GLint stride, GLenum type)
}


//1543
 void EXEC_gluQuadricCallback(char *commandbuf)
{
	LOG("Called unimplemted stub gluQuadricCallback!\n");
	//(GLUquadric* quad, GLenum which, _GLUfuncptr CallBackFunc)
}


//1544
 void EXEC_gluQuadricDrawStyle(char *commandbuf)
{
	LOG("Called unimplemted stub gluQuadricDrawStyle!\n");
	//(GLUquadric* quad, GLenum draw)
}


//1545
 void EXEC_gluQuadricNormals(char *commandbuf)
{
	LOG("Called unimplemted stub gluQuadricNormals!\n");
	//(GLUquadric* quad, GLenum normal)
}


//1546
 void EXEC_gluQuadricOrientation(char *commandbuf)
{
	LOG("Called unimplemted stub gluQuadricOrientation!\n");
	//(GLUquadric* quad, GLenum orientation)
}


//1547
 void EXEC_gluQuadricTexture(char *commandbuf)
{
	LOG("Called unimplemted stub gluQuadricTexture!\n");
	//(GLUquadric* quad, GLboolean texture)
}


//1548
 void EXEC_glugluScaleImage(char *commandbuf)
{
	LOG("Called unimplemted stub gluScaleImage!\n");
	//(GLenum format, GLsizei wIn, GLsizei hIn, GLenum typeIn, const void *dataIn, GLsizei wOut, GLsizei hOut, GLenum typeOut, GLvoid* dataOut)
	//returns Glint
}


//1549
 void EXEC_gluSphere(char *commandbuf)
{
	LOG("Called unimplemted stub gluSphere!\n");
	//(GLUquadric* quad, GLdouble radius, GLint slices, GLint stacks)
}


//1550
 void EXEC_gluTessBeginContour(char *commandbuf)
{
	LOG("Called unimplemted stub gluTessBeginContour!\n");
	//(GLUtesselator* tess)
}


//1551
 void EXEC_gluTessBeginPolygon(char *commandbuf)
{
	LOG("Called unimplemted stub gluTessBeginPolygon!\n");
	//(GLUtesselator* tess, GLvoid* data)
}


//1552
 void EXEC_gluTessCallback(char *commandbuf)
{
	LOG("Called unimplemted stub gluTessCallback!\n");
	//(GLUtesselator* tess, GLenum which, _GLUfuncptr CallBackFunc)
}


//1553
 void EXEC_gluTessEndContour(char *commandbuf)
{
	LOG("Called unimplemted stub gluTessEndContour!\n");
	//(GLUtesselator* tess)
}


//1554
 void EXEC_gluTessEndPolygon(char *commandbuf)
{
	LOG("Called unimplemted stub gluTessEndPolygon!\n");
	//(GLUtesselator* tess)
}


//1555
 void EXEC_gluTessNormal(char *commandbuf)
{
	LOG("Called unimplemted stub gluTessNormal!\n");
	//(GLUtesselator* tess, GLdouble valueX, GLdouble valueY, GLdouble valueZ)
}


//1556
 void EXEC_gluTessProperty(char *commandbuf)
{
	LOG("Called unimplemted stub gluTessProperty!\n");
	//(GLUtesselator* tess, GLenum which, GLdouble data)
}


//1557
 void EXEC_gluTessVertex(char *commandbuf)
{
	LOG("Called unimplemted stub gluTessVertex!\n");
	//(GLUtesselator* tess, GLdouble *location, GLvoid* data)
}


//1558
 void EXEC_gluUnProject(char *commandbuf)
{
	LOG("Called unimplemted stub gluUnProject!\n");
	//(GLdouble winX, GLdouble winY, GLdouble winZ, const GLdouble *model, const GLdouble *proj, const GLint *view, GLdouble* objX, GLdouble* objY, GLdouble* objZ)
	//returns glint
}


//1559
 void EXEC_gluUnProject4(char *commandbuf)
{
	LOG("Called unimplemted stub gluUnProject4!\n");
	//(GLdouble winX, GLdouble winY, GLdouble winZ, GLdouble clipW, const GLdouble *model, const GLdouble *proj, const GLint *view, GLdouble nearVal, GLdouble farVal, GLdouble* objX, GLdouble* objY, GLdouble* objZ, GLdouble* objW)
	//returns glint
}

