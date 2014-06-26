#pragma once
#include "instruction.hpp"
#include "consts.hpp"
#include "libdgl.hpp"

#define LOG(x...)


void dgl_cache_clear();


struct storedPointer {
    bool sent;
    GLint size;
    GLenum type;
    GLsizei stride;
    const GLvoid *pointer;
};

#define GL_MAX_TEXTURES 8 //TODO: look this up somewhere...

extern int iCurrentActiveTextureUnit;

extern storedPointer rpTex[GL_MAX_TEXTURES]; //[8], usually
extern storedPointer rpVert;
extern storedPointer rpCol;
extern storedPointer rpInter;
extern storedPointer rpNormals;

void send_pointers(uint32_t length);
void send_pointers_glLockArraysEXT(GLint first, GLsizei count);
void send_pointers_glUnlockArraysEXT();
bool send_pointers_glLockArraysEXT_locked();
GLint send_pointers_glLockArraysEXT_length();
GLint send_pointers_glLockArraysEXT_max(GLint length);



static void pushOp(uint16_t opID){
    Instruction inst(opID);
    dgl_instructions().push_back(move(inst));
}

extern void     *return_buffer_ptr;
extern size_t    return_buffer_size;

static void pushBuf(const void *buffer, size_t len) {
    dgl_instructions().back().write(buffer, len);
}

static void pushBuf(void *buffer, size_t len, bool is_return_buffer) {
    assert(is_return_buffer);
    return_buffer_ptr   = buffer;
    return_buffer_size  = len;
}

static void waitForReturn() {
    dgl_sync(buffer(return_buffer_ptr, return_buffer_size));
}

template<typename T>
T *waitForReturnUnknown() {
    return buffer_cast<T*>(dgl_sync());
}

template<typename type> void pushParam(type data) {
    dgl_instructions().back().write(data);
}
