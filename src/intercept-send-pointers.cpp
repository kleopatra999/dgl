#include "intercept.hpp"
#include <iostream>

using namespace std;

/*********************************************************
	Pointer Structures
*********************************************************/
//some methods simply specify a pointer to the beginning
//of an array, that will be used later. As we do not yet
//know the size of the array, we cannot send the buffer
//We store the values for the method until the size is
//known (usually when glDrawElements is called)

int iCurrentActiveTextureUnit = 0;

storedPointer rpTex[GL_MAX_TEXTURES]; //[8], usually
storedPointer rpVert;
storedPointer rpCol;
storedPointer rpInter;
storedPointer rpNormals;



size_t interleaved_size() {
    switch (rpInter.type) {
	    case GL_V2F:			return sizeof(GLfloat) * 2; break;
        case GL_V3F:			return sizeof(GLfloat) * 3; break;
        case GL_C4UB_V2F:		return sizeof(GLfloat) * 2 + sizeof(GLubyte) * 4; break;
        case GL_C4UB_V3F:		return sizeof(GLfloat) * 3 + sizeof(GLubyte) * 4; break;
        case GL_C3F_V3F:		return sizeof(GLfloat) * 6; break;
        case GL_N3F_V3F:		return sizeof(GLfloat) * 6; break;
        case GL_C4F_N3F_V3F:		return sizeof(GLfloat) * 10; break;
        case GL_T2F_V3F:		return sizeof(GLfloat) * 5; break;
        case GL_T4F_V4F:		return sizeof(GLfloat) * 8; break;
        case GL_T2F_C4UB_V3F:		return sizeof(GLfloat) * 5 + sizeof(GLubyte) * 4; break;
        case GL_T2F_C3F_V3F:		return sizeof(GLfloat) * 8; break;
        case GL_T2F_N3F_V3F:		return sizeof(GLfloat) * 8; break;
        case GL_T2F_C4F_N3F_V3F:	return sizeof(GLfloat) * 12; break;
        case GL_T4F_C4F_N3F_V4F:	return sizeof(GLfloat) * 15; break;
	    default:LOG("DEFAULTED glInterleavedArrays lookup %d should be %d!\n", rpInter.type, GL_T2F_C4UB_V3F); return sizeof(GLfloat) * 15;
    }
}



static void my_glSomethingPointer(
        uint16_t        id,
        storedPointer&  array,
        uint32_t        length) {
    if (array.sent || !array.size) {
        return;
    }
    int  type_size;
    if (&array == &rpInter) {
        type_size   = interleaved_size();
    } else {
        type_size   = getTypeSize(array.type);
    }
    auto el_size    = type_size * array.size;
    auto stride     = array.stride ? array.stride : el_size;
    auto buf_size   = stride*(length-1) + el_size;
	pushOp(id);
	pushParam(array.size);
	pushParam(array.type);
	pushParam(array.stride);
	pushBuf(array.pointer, buf_size);
	array.sent      = true;
	array.pointer   = nullptr;
}

static void my_glClientActiveTexture(int i) {
    //We have to operate on the correct texture unit
	//This makes stuff like multitexturing work properly with VBOs
	//TODO This will cause an extra glClientActiveTexture() call
	//which probably isn't an issue, but...
	pushOp(375);
    //pretty sure + i is okay, carmack does it
	pushParam(GL_TEXTURE0 + i);
}

void send_pointers(uint32_t length) {
	for(int i = 0; i < GL_MAX_TEXTURES; i++){
	    my_glSomethingPointer(320, rpTex[i], length);
	}
    my_glSomethingPointer(321, rpVert   , length);
    my_glSomethingPointer(308, rpCol    , length);
    my_glSomethingPointer(317, rpInter  , length);
    my_glSomethingPointer(318, rpNormals, length);
}



static GLint    glLockArraysEXT_length;
static bool     glLockArraysEXT_locked = false;

void send_pointers_glLockArraysEXT(GLint first, GLsizei count) {
    glLockArraysEXT_length = first + count;
    glLockArraysEXT_locked = true;
}

void send_pointers_glUnlockArraysEXT() {
    send_pointers(glLockArraysEXT_length);
    glLockArraysEXT_locked = false;
}

bool send_pointers_glLockArraysEXT_locked() {
    return glLockArraysEXT_locked;
}

GLint send_pointers_glLockArraysEXT_length() {
    return glLockArraysEXT_length;
}

GLint send_pointers_glLockArraysEXT_max(GLint length) {
    if (length != glLockArraysEXT_length &&
        !getenv("NO_DEBUG")) {
        cerr << "DEBUG:\t"
            << "size mismatch (glLockArraysEXT):\t"
            << length << " != " << glLockArraysEXT_length
            << endl;
        return max(length, glLockArraysEXT_length);
    }
    return length;
}
