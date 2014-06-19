#pragma once

#include <GL/gl.h>

int getTypeSize(GLenum type);
int getLightParamSize(GLenum type);
int getFormatSize(GLenum format);
int getGetSize(GLenum type);
int getTextureParamSize(GLenum type);
const char *getGLParamName(unsigned int param);
