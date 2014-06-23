#include <GL/glxew.h>
#include "exec.hpp"

#define LOG(x)

//1601
 void EXEC_glXChooseVisual(char *commandbuf)
{
	LOG("Called unimplemted stub glXChooseVisual!\n");
	//( Display *dpy, int screen, int *attribList )
	//returns XVisualInfo*
}


//1602
 void EXEC_glXCreateContext(char *commandbuf)
{
	LOG("Called unimplemted stub glXCreateContext!\n");
	//( Display *dpy, XVisualInfo *vis, GLXContext shareList, Bool direct )
	//returns GLXContext
}


//1603
 void EXEC_glXDestroyContext(char *commandbuf)
{
	LOG("Called unimplemted stub glXDestroyContext!\n");
	//( Display *dpy, GLXContext ctx )
}


//1604
 void EXEC_glXMakeCurrent(char *commandbuf)
{
	LOG("Called unimplemted stub glXMakeCurrent!\n");
	//( Display *dpy, GLXDrawable drawable, GLXContext ctx)
	//returns Bool
}


//1605
 void EXEC_glXCopyContext(char *commandbuf)
{
	LOG("Called unimplemted stub glXCopyContext!\n");
	//( Display *dpy, GLXContext src, GLXContext dst, unsigned long mask )
}


//1606
 void EXEC_glXSwapBuffers(char *commandbuf)
{
	LOG("Called unimplemted stub glXSwapBuffers!\n");
	//( Display *dpy, GLXDrawable drawable )
}


//1607
 void EXEC_glXCreateGLXPixmap(char *commandbuf)
{
	LOG("Called unimplemted stub glXCreateGLXPixmap!\n");
	//( Display *dpy, XVisualInfo *visual, Pixmap pixmap )
	//returns GLXPixmap
}


//1608
 void EXEC_glXDestroyGLXPixmap(char *commandbuf)
{
	LOG("Called unimplemted stub glXDestroyGLXPixmap!\n");
	//( Display *dpy, GLXPixmap pixmap )
}


//1609
 void EXEC_glXQueryExtension(char *commandbuf)
{
	LOG("Called unimplemted stub glXQueryExtension!\n");
	//( Display *dpy, int *errorb, int *event )
	//returns bool
}


//1610
 void EXEC_glXQueryVersion(char *commandbuf)
{
	LOG("Called unimplemted stub glXQueryVersion!\n");
	//( Display *dpy, int *maj, int *min )
	//returns bool
}


//1611
 void EXEC_glXIsDirect(char *commandbuf)
{
	LOG("Called unimplemted stub glXIsDirect!\n");
	//( Display *dpy, GLXContext ctx )
	//returns bool
}


//1612
 void EXEC_glXGetConfig(char *commandbuf)
{
	LOG("Called unimplemted stub glXGetConfig!\n");
	//( Display *dpy, XVisualInfo *visual, int attrib, int *value )
	//returns int
}


//1613
 void EXEC_glXGetCurrentContext(char *commandbuf)
{
	LOG("Called unimplemted stub glXGetCurrentContext!\n");
	//returns GLXContext
}


//1614
 void EXEC_glXGetCurrentDrawable(char *commandbuf)
{
	LOG("Called unimplemted stub glXGetCurrentDrawable!\n");
	//returns GLXDrawable
}


//1615
 void EXEC_glXWaitGL(char *commandbuf)
{
	LOG("Called unimplemted stub glXWaitGL!\n");
}


//1616
 void EXEC_glXWaitX(char *commandbuf)
{
	LOG("Called unimplemted stub glXWaitX!\n");
}


//1617
 void EXEC_glXUseXFont(char *commandbuf)
{
	LOG("Called unimplemted stub glXUseXFont!\n");
	//( Font font, int first, int count, int list )
}


//GLX 1.1 and later
//1618
 void EXEC_glXQueryExtensionsString(char *commandbuf)
{
	LOG("Called unimplemted stub glXQueryExtensionsString!\n");
	//( Display *dpy, int screen )
	//returns const char *
}


//1619
 void EXEC_glXQueryServerString(char *commandbuf)
{
	LOG("Called unimplemted stub glXQueryServerString!\n");
	//( Display *dpy, int screen, int name )
	//returns const char *
}


//1620
 void EXEC_glXGetClientString(char *commandbuf)
{
	LOG("Called unimplemted stub glXGetClientString!\n");
	//( Display *dpy, int name )
	//returns const char *
}


// GLX 1.2 and later
//1621
 void EXEC_glXGetCurrentDisplay(char *commandbuf)
{
	LOG("Called unimplemted stub glXGetCurrentDisplay!\n");
	//returns Display *
}


// GLX 1.3 and later
//1622
 void EXEC_glXChooseFBConfig(char *commandbuf)
{
	LOG("Called unimplemted stub glXChooseFBConfig!\n");
	//( Display *dpy, int screen, const int *attribList, int *nitems )
	//returns GLXFBConfig *
}


//1623
 void EXEC_glXGetFBConfigAttrib(char *commandbuf)
{
	LOG("Called unimplemted stub glXGetFBConfigAttrib!\n");
	//( Display *dpy, GLXFBConfig config, int attribute, int *value )
	//returns int
}


//1624
 void EXEC_glXGetFBConfigs(char *commandbuf)
{
	LOG("Called unimplemted stub glXGetFBConfigs!\n");
	//( Display *dpy, int screen, int *nelements )
	//returns GLXFBConfig *
}


//1625
 void EXEC_glXGetVisualFromFBConfig(char *commandbuf)
{
	LOG("Called unimplemted stub glXGetVisualFromFBConfig!\n");
	//( Display *dpy, GLXFBConfig config )
	//returns XVisualInfo *
}


//1626
 void EXEC_glXCreateWindow(char *commandbuf)
{
	LOG("Called unimplemted stub glXCreateWindow!\n");
	//( Display *dpy, GLXFBConfig config, Window win, const int *attribList )
	//returns  GLXWindow
}


//1627
 void EXEC_glXDestroyWindow(char *commandbuf)
{
	LOG("Called unimplemted stub glXDestroyWindow!\n");
	//( Display *dpy, GLXWindow window )
}


//1628
 void EXEC_glXCreatePixmap(char *commandbuf)
{
	LOG("Called unimplemted stub glXCreatePixmap!\n");
	//( Display *dpy, GLXFBConfig config, Pixmap pixmap, const int *attribList )
	//returns GLXPixmap
}


//1629
 void EXEC_glXDestroyPixmap(char *commandbuf)
{
	LOG("Called unimplemted stub glXDestroyPixmap!\n");
	//( Display *dpy, GLXPixmap pixmap )
}


//1630
 void EXEC_glXCreatePbuffer(char *commandbuf)
{
	LOG("Called unimplemted stub glXCreatePbuffer!\n");
	//( Display *dpy, GLXFBConfig config, const int *attribList )
	//returns GLXPbuffer
}


//1631
 void EXEC_glXDestroyPbuffer(char *commandbuf)
{
	LOG("Called unimplemted stub glXDestroyPbuffer!\n");
	//( Display *dpy, GLXPbuffer pbuf )
}


//1632
 void EXEC_glXQueryDrawable(char *commandbuf)
{
	LOG("Called unimplemted stub glXQueryDrawable!\n");
	//( Display *dpy, GLXDrawable draw, int attribute, unsigned int *value )
}


//1633
 void EXEC_glXCreateNewContext(char *commandbuf)
{
	LOG("Called unimplemted stub glXCreateNewContext!\n");
	//( Display *dpy, GLXFBConfig config, int renderType, GLXContext shareList, Bool direct )
	//returns GLXContext
}


//1634
 void EXEC_glXMakeContextCurrent(char *commandbuf)
{
	LOG("Called unimplemted stub glXMakeContextCurrent!\n");
	//( Display *dpy, GLXDrawable draw, GLXDrawable read, GLXContext ctx )
	//returns Bool
}


//1635
 void EXEC_glXGetCurrentReadDrawable(char *commandbuf)
{
	LOG("Called unimplemted stub glXGetCurrentReadDrawable!\n");
	//returns GLXDrawable
}


//1636
 void EXEC_glXQueryContext(char *commandbuf)
{
	LOG("Called unimplemted stub glXQueryContext!\n");
	//( Display *dpy, GLXContext ctx, int attribute, int *value )
	//returns int
}


//1637
 void EXEC_glXSelectEvent(char *commandbuf)
{
	LOG("Called unimplemted stub glXSelectEvent!\n");
	//( Display *dpy, GLXDrawable drawable, unsigned long mask )
}


//1638
 void EXEC_glXGetSelectedEvent(char *commandbuf)
{
	LOG("Called unimplemted stub glXGetSelectedEvent!\n");
	//( Display *dpy, GLXDrawable drawable, unsigned long *mask )
}


//1639
 void EXEC_glXGetProcAddressARB(char *commandbuf)
{
	LOG("Called unimplemted stub glXGetProcAddressARB!\n");
	//(const GLubyte *)
	//returns __GLXextFuncPtr
}


//1640
 void EXEC_glXGetProcAddress(char *commandbuf)
{
	LOG("Called unimplemted stub glXGetProcAddress!\n");
	//(const GLubyte *procname)
}


//1641
 void EXEC_glXAllocateMemoryNV(char *commandbuf)
{
	LOG("Called unimplemted stub glXAllocateMemoryNV!\n");
	//(GLsizei size, GLfloat readfreq, GLfloat writefreq, GLfloat priority)
}


//1642
 void EXEC_glXFreeMemoryNV(char *commandbuf)
{
	LOG("Called unimplemted stub glXFreeMemoryNV!\n");
	//(GLvoid *pointer)
}


//1643
 void EXEC_glXAllocateMemoryMESA(char *commandbuf)
{
	LOG("Called unimplemted stub glXAllocateMemoryMESA!\n");
	//(Display *dpy, int scrn, size_t size, float readfreq, float writefreq, float priority)
}


//1644
 void EXEC_glXFreeMemoryMESA(char *commandbuf)
{
	LOG("Called unimplemted stub glXFreeMemoryMESA!\n");
	//(Display *dpy, int scrn, void *pointer)
}


//1645
 void EXEC_glXGetMemoryOffsetMESA(char *commandbuf)
{
	LOG("Called unimplemted stub glXGetMemoryOffsetMESA!\n");
	//(Display *dpy, int scrn, const void *pointer)
	//returns GLuint
}


//1646
 void EXEC_glXBindTexImageARB(char *commandbuf)
{
	LOG("Called unimplemted stub glXBindTexImageARB!\n");
	//(Display *dpy, GLXPbuffer pbuffer, int buffer)
	//returns Bool
}


//1647
 void EXEC_glXReleaseTexImageARB(char *commandbuf)
{
	LOG("Called unimplemted stub glXReleaseTexImageARB!\n");
	//(Display *dpy, GLXPbuffer pbuffer, int buffer)
	//returns Bool
}


//1648
 void EXEC_glXDrawableAttribARB(char *commandbuf)
{
	LOG("Called unimplemted stub glXDrawableAttribARB!\n");
	//(Display *dpy, GLXDrawable draw, const int *attribList)
	//returns Bool
}


//1649
 void EXEC_glXGetFrameUsageMESA(char *commandbuf)
{
	LOG("Called unimplemted stub glXGetFrameUsageMESA!\n");
	//(Display *dpy, GLXDrawable drawable, float *usage)
	//returns int
}


//1650
 void EXEC_glXBeginFrameTrackingMESA(char *commandbuf)
{
	LOG("Called unimplemted stub glXBeginFrameTrackingMESA!\n");
	//(Display *dpy, GLXDrawable drawable)
	//returns int
}


//1651
 void EXEC_glXEndFrameTrackingMESA(char *commandbuf)
{
	LOG("Called unimplemted stub glXEndFrameTrackingMESA!\n");
	//(Display *dpy, GLXDrawable drawable)
	//returns int
}


//1652
 void EXEC_glXQueryFrameTrackingMESA(char *commandbuf)
{
	LOG("Called unimplemted stub glXQueryFrameTrackingMESA!\n");
	//(Display *dpy, GLXDrawable drawable, int64_t *swapCount, int64_t *missedFrames, float *lastMissedUsage)
	//returns int
}


//1653
 void EXEC_glXSwapIntervalMESA(char *commandbuf)
{
    unsigned int interval = *(unsigned int *)commandbuf;
    int err               = glXSwapIntervalMESA(interval);
    // TODO payload: ignore error code
}


//1654
 void EXEC_glXGetSwapIntervalMESA(char *commandbuf)
{
	pushRet(glXGetSwapIntervalMESA());
}


//1655
 void EXEC_glXBindTexImageEXT(char *commandbuf)
{
	LOG("Called unimplemted stub glXBindTexImageEXT!\n");
	//(Display *dpy, GLXDrawable drawable, int buffer, const int *attrib_list)
}


//1656
 void EXEC_glXReleaseTexImageEXT(char *commandbuf)
{
	LOG("Called unimplemted stub glXReleaseTexImageEXT!\n");
	//(Display *dpy, GLXDrawable drawable, int buffer)
}

