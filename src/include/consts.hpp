#pragma once

#include <string>
#include <GL/gl.h>

extern std::string _dgl_function_names[1700];

static uint16_t id_CGLSwapBuffers = 1499;

int getTypeSize(GLenum type);
int getLightParamSize(GLenum type);
int getFormatSize(GLenum format);
int getGetSize(GLenum type);
int getTextureParamSize(GLenum type);
const char *getGLParamName(unsigned int param);
