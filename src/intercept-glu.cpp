//1501
extern "C" void gluBeginCurve (GLUnurbs* nurb) {
LOG("Called unimplemted stub gluBeginCurve!\n");
}

//1502
extern "C" void gluBeginPolygon (GLUtesselator* tess) {
LOG("Called unimplemted stub gluBeginPolygon!\n");
}

//1503
extern "C" void gluBeginSurface (GLUnurbs* nurb) {
LOG("Called unimplemted stub gluBeginSurface!\n");
}

//1504
extern "C" void gluBeginTrim (GLUnurbs* nurb) {
LOG("Called unimplemted stub gluBeginTrim!\n");
}

//1505
extern "C" GLint gluBuild1DMipmapLevels (GLenum target, GLint internalFormat, GLsizei width, GLenum format, GLenum type, GLint level, GLint base, GLint max, const void *data) {
LOG("Called unimplemted stub gluBuild1DMipmapLevels !\n");
}

//1506
extern "C" GLint gluBuild1DMipmaps (GLenum target, GLint internalFormat, GLsizei width, GLenum format, GLenum type, const void *data) {
LOG("Called unimplemted stub gluBuild1DMipmaps!\n");
}

//1507
extern "C" GLint gluBuild2DMipmapLevels (GLenum target, GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, GLint level, GLint base, GLint max, const void *data) {
LOG("Called unimplemted stub gluBuild2DMipmapLevels!\n");
}

//1508
extern "C" GLint gluBuild2DMipmaps (GLenum target, GLint internalFormat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *data) {
LOG("Called unimplemted stub gluBuild2DMipmaps!\n");
}

//1509
extern "C" GLint gluBuild3DMipmapLevels (GLenum target, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLint level, GLint base, GLint max, const void *data) {
LOG("Called unimplemted stub gluBuild3DMipmapLevels!\n");
}

//1510
extern "C" GLint gluBuild3DMipmaps (GLenum target, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *data) {
LOG("Called unimplemted stub gluBuild3DMipmaps!\n");
}

//1511
extern "C" GLboolean gluCheckExtension (const GLubyte *extName, const GLubyte *extString) {
LOG("Called unimplemted stub gluCheckExtension!\n");
}

//1512
extern "C" void gluCylinder (GLUquadric* quad, GLdouble base, GLdouble top, GLdouble height, GLint slices, GLint stacks) {
LOG("Called unimplemted stub gluCylinder!\n");
}

//1513
extern "C" void gluDeleteNurbsRenderer (GLUnurbs* nurb) {
LOG("Called unimplemted stub gluDeleteNurbsRenderer!\n");
}

//1514
extern "C" void gluDeleteQuadric (GLUquadric* quad) {
LOG("Called unimplemted stub gluDeleteQuadric!\n");
}

//1515
extern "C" void gluDeleteTess (GLUtesselator* tess) {
LOG("Called unimplemted stub gluDeleteTess!\n");
}

//1516
extern "C" void  gluDisk (GLUquadric* quad, GLdouble inner, GLdouble outer, GLint slices, GLint loops) {
LOG("Called unimplemted stub gluDisk!\n");
}

//1517
extern "C" void gluEndCurve (GLUnurbs* nurb) {
LOG("Called unimplemted stub gluEndCurve!\n");
}

//1518
extern "C" void gluEndPolygon (GLUtesselator* tess) {
LOG("Called unimplemted stub gluEndPolygon!\n");
}

//1519
extern "C" void gluEndSurface (GLUnurbs* nurb) {
LOG("Called unimplemted stub gluEndSurface!\n");
}

//1520
extern "C" void gluEndTrim (GLUnurbs* nurb) {
LOG("Called unimplemted stub gluEndTrim!\n");
}

//1521
extern "C" const GLubyte * gluErrorString (GLenum error) {
LOG("Called unimplemted stub gluErrorString!\n");
}

//1522
extern "C" void gluGetNurbsProperty (GLUnurbs* nurb, GLenum property, GLfloat* data) {
LOG("Called unimplemted stub gluGetNurbsProperty!\n");
}

//1523
extern "C" const GLubyte * gluGetString (GLenum name) {
LOG("Called unimplemted stub gluGetString!\n");
}

//1524
extern "C" void  gluGetTessProperty (GLUtesselator* tess, GLenum which, GLdouble* data) {
LOG("Called unimplemted stub gluGetTessProperty!\n");
}

//1525
extern "C" void  gluLoadSamplingMatrices (GLUnurbs* nurb, const GLfloat *model, const GLfloat *perspective, const GLint *view) {
LOG("Called unimplemted stub gluLoadSamplingMatrices!\n");
}

//1526
extern "C" void  gluLookAt (GLdouble eyeX, GLdouble eyeY, GLdouble eyeZ, GLdouble centerX, GLdouble centerY, GLdouble centerZ, GLdouble upX, GLdouble upY, GLdouble upZ) {
LOG("Called untested stub gluLookAt!\n");
    pushOp(1526);
    pushParam(eyeX);
    pushParam(eyeY);
    pushParam(eyeZ);
    pushParam(centerX);
	pushParam(centerY);
	pushParam(centerZ);
	pushParam(upX);
	pushParam(upY);
	pushParam(upZ);

}

//1527
extern "C" GLUnurbs* gluNewNurbsRenderer (void) {
LOG("Called unimplemted stub gluNewNurbsRenderer!\n");
}

//1528
extern "C" GLUquadric* gluNewQuadric (void) {
LOG("Called unimplemted stub gluNewQuadric!\n");
}

//1529
extern "C" GLUtesselator* gluNewTess (void) {
LOG("Called unimplemted stub gluNewTess!\n");
}

//1530
extern "C" void gluNextContour (GLUtesselator* tess, GLenum type) {
LOG("Called unimplemted stub gluNextContour!\n");
}

//1531
extern "C" void gluNurbsCallback (GLUnurbs* nurb, GLenum which, _GLUfuncptr CallBackFunc) {
LOG("Called unimplemted stub gluNurbsCallback!\n");
}

//1532
extern "C" void gluNurbsCallbackData (GLUnurbs* nurb, GLvoid* userData) {
LOG("Called unimplemted stub gluNurbsCallbackData!\n");
}

//1533
extern "C" void gluNurbsCallbackDataEXT (GLUnurbs* nurb, GLvoid* userData) {
LOG("Called unimplemted stub gluNurbsCallbackDataEXT!\n");
}

//1534
extern "C" void gluNurbsCurve (GLUnurbs* nurb, GLint knotCount, GLfloat *knots, GLint stride, GLfloat *control, GLint order, GLenum type) {
LOG("Called unimplemted stub gluNurbsCurve!\n");
}

//1535
extern "C" void gluNurbsProperty (GLUnurbs* nurb, GLenum property, GLfloat value) {
LOG("Called unimplemted stub gluNurbsProperty!\n");
}

//1536
extern "C" void gluNurbsSurface (GLUnurbs* nurb, GLint sKnotCount, GLfloat* sKnots, GLint tKnotCount, GLfloat* tKnots, GLint sStride, GLint tStride, GLfloat* control, GLint sOrder, GLint tOrder, GLenum type) {
LOG("Called unimplemted stub gluNurbsSurface!\n");
}

//1537
extern "C" void gluOrtho2D (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top) {
LOG("Called unimplemted stub gluOrtho2D!\n");
}

//1538
extern "C" void gluPartialDisk (GLUquadric* quad, GLdouble inner, GLdouble outer, GLint slices, GLint loops, GLdouble start, GLdouble sweep) {
LOG("Called unimplemted stub gluPartialDisk!\n");
}

#endif

//1539
extern "C" void gluPerspective (GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar) {
	pushOp(1539);
	pushParam(fovy);
	pushParam(aspect);
	pushParam(zNear);
	pushParam(zFar);
}

#ifdef GLUFULL

//1540
extern "C" void gluPickMatrix (GLdouble x, GLdouble y, GLdouble delX, GLdouble delY, GLint *viewport) {
LOG("Called unimplemted stub gluPickMatrix!\n");
}

//1541
extern "C" GLint gluProject (GLdouble objX, GLdouble objY, GLdouble objZ, const GLdouble *model, const GLdouble *proj, const GLint *view, GLdouble* winX, GLdouble* winY, GLdouble* winZ) {
LOG("Called unimplemted stub gluProject!\n");
}

//1542
extern "C" void gluPwlCurve (GLUnurbs* nurb, GLint count, GLfloat* data, GLint stride, GLenum type) {
LOG("Called unimplemted stub gluPwlCurve!\n");
}

//1543
extern "C" void gluQuadricCallback (GLUquadric* quad, GLenum which, _GLUfuncptr CallBackFunc) {
LOG("Called unimplemted stub gluQuadricCallback!\n");
}

//1544
extern "C" void gluQuadricDrawStyle (GLUquadric* quad, GLenum draw) {
LOG("Called unimplemted stub gluQuadricDrawStyle!\n");
}

//1545
extern "C" void gluQuadricNormals (GLUquadric* quad, GLenum normal) {
LOG("Called unimplemted stub gluQuadricNormals!\n");
}

//1546
extern "C" void gluQuadricOrientation (GLUquadric* quad, GLenum orientation) {
LOG("Called unimplemted stub gluQuadricOrientation!\n");
}

//1547
extern "C" void gluQuadricTexture (GLUquadric* quad, GLboolean texture) {
LOG("Called unimplemted stub gluQuadricTexture!\n");
}

//1548
extern "C" GLint gluScaleImage (GLenum format, GLsizei wIn, GLsizei hIn, GLenum typeIn, const void *dataIn, GLsizei wOut, GLsizei hOut, GLenum typeOut, GLvoid* dataOut) {
LOG("Called unimplemted stub gluScaleImage!\n");
}

//1549
extern "C" void gluSphere (GLUquadric* quad, GLdouble radius, GLint slices, GLint stacks) {
LOG("Called unimplemted stub gluSphere!\n");
}

//1550
extern "C" void gluTessBeginContour (GLUtesselator* tess) {
LOG("Called unimplemted stub gluTessBeginContour!\n");
}

//1551
extern "C" void gluTessBeginPolygon (GLUtesselator* tess, GLvoid* data) {
LOG("Called unimplemted stub gluTessBeginPolygon!\n");
}

//1552
extern "C" void gluTessCallback (GLUtesselator* tess, GLenum which, _GLUfuncptr CallBackFunc) {
LOG("Called unimplemted stub gluTessCallback!\n");
}

//1553
extern "C" void gluTessEndContour (GLUtesselator* tess) {
LOG("Called unimplemted stub gluTessEndContour!\n");
}

//1554
extern "C" void gluTessEndPolygon (GLUtesselator* tess) {
LOG("Called unimplemted stub gluTessEndPolygon!\n");
}

//1555
extern "C" void gluTessNormal (GLUtesselator* tess, GLdouble valueX, GLdouble valueY, GLdouble valueZ) {
LOG("Called unimplemted stub gluTessNormal!\n");
}

//1556
extern "C" void gluTessProperty (GLUtesselator* tess, GLenum which, GLdouble data) {
LOG("Called unimplemted stub gluTessProperty!\n");
}

//1557
extern "C" void gluTessVertex (GLUtesselator* tess, GLdouble *location, GLvoid* data) {
LOG("Called unimplemted stub gluTessVertex!\n");
}

//1558
extern "C" GLint gluUnProject (GLdouble winX, GLdouble winY, GLdouble winZ, const GLdouble *model, const GLdouble *proj, const GLint *view, GLdouble* objX, GLdouble* objY, GLdouble* objZ) {
LOG("Called unimplemted stub gluUnProject!\n");
}

//1559
extern "C" GLint gluUnProject4 (GLdouble winX, GLdouble winY, GLdouble winZ, GLdouble clipW, const GLdouble *model, const GLdouble *proj, const GLint *view, GLdouble nearVal, GLdouble farVal, GLdouble* objX, GLdouble* objY, GLdouble* objZ, GLdouble* objW) {
LOG("Called unimplemted stub gluUnProject4!\n");
}
