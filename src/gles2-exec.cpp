#include <GL/glew.h>
#include <GL/gl.h>
#include <assert.h>
#include <cstring>
#include <fstream>
#include <limits>
#include <algorithm>

using namespace std;

bool            exec_dont_delete_args;

#include "instruction.hpp"
#include "gl-utils.hpp"
#include "pixels-utils.hpp"
#include <type_traits>

template<typename type>
type read_val(const char *&buf) {
    auto ret = *(type*)buf;
    cerr << ret << endl;
    buf     += sizeof(type);
    return ret;
}

template<typename type>
type read_ptr(const char *&buf) {
    auto valid = read_val<bool>(buf);
    return valid ? (type)buf : nullptr;
}

template<typename type>
void write(ostream& reply, type arg) {
    reply.write((const char *)&arg, sizeof(arg));
}

template<typename type>
void write(ostream& reply, type *ptr, size_t size) {
    reply.write((const char *)ptr, sizeof(type) * size);
}




void exec_glShaderSource(const char *buf, ostream& reply)
{
    auto    shader      = read_val<GLuint>(buf);
    GLsizei count       = 1;
    auto    length      = nullptr;
    auto    source      = read_ptr<const GLchar *>(buf);
    const GLchar *string[1]{ source };
	glShaderSource(shader, count, string, length);
}

void exec_glBufferData(const char *buf, ostream& reply) {
    auto         target           = read_val<GLenum>(buf);
    auto         size             = read_val<GLsizeiptr>(buf);
    auto         usage            = read_val<GLenum>(buf);
    auto         data             = read_ptr<const char *>(buf);
    // TODO memory leak
    auto         data_copy        = new char[size];
    copy(data, data + size, data_copy);
    glBufferData(target, size, data_copy, usage);
}

void exec_glVertexAttribPointer(const char *buf, ostream& reply) {
    auto         index            = read_val<GLuint>(buf);
    auto         size             = read_val<GLint>(buf);
    auto         type             = read_val<GLenum>(buf);
    auto         normalized       = read_val<GLboolean>(buf);
    auto         stride           = read_val<GLsizei>(buf);
    auto         pointer_is_buf   = read_val<bool>(buf);
    const void * pointer;
    if (pointer_is_buf) {
                 pointer          = read_ptr<const void *>(buf);
    } else {
                 pointer          = read_val<const void *>(buf);
    }
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void exec_glReadPixels(const char *buf, ostream& reply) {
    auto         x                = read_val<GLint>(buf);
    auto         y                = read_val<GLint>(buf);
    auto         width            = read_val<GLsizei>(buf);
    auto         height           = read_val<GLsizei>(buf);
    auto         format           = read_val<GLenum>(buf);
    auto         type             = read_val<GLenum>(buf);
    auto         byte_size        = width * height * bytes_per_pixel(format);
    auto         pixels           = new char[byte_size];
    glReadPixels(x, y, width, height, format, type, pixels);
#ifdef SCREENSHOT_glReadPixels    
    write_pixels_file<1>
        ("exec_glReadPixels", width, height, format, pixels);
#endif
    write(reply, pixels, byte_size);
}

void exec_glDrawElements(const char *buf, ostream& reply) {
    auto         mode             = read_val<GLenum>(buf);
    auto         count            = read_val<GLsizei>(buf);
    auto         type             = read_val<GLenum>(buf);
    auto         indices          = read_val<const uintptr_t>(buf);
    glDrawElements(mode, count, type, reinterpret_cast<const void *>(indices));
}

void exec_glGetVertexAttribPointerv(const char *buf, ostream& reply) {
    auto         index            = read_val<GLuint>(buf);
    auto         pname            = read_val<GLenum>(buf);
    void*        pointer;
    glGetVertexAttribPointerv(index, pname, &pointer);
    write(reply, reinterpret_cast<uintptr_t>(pointer));
}

// for exec_glGetUniform[if]v
template<typename params_t>
void fill_params(params_t &params) {
    auto p = *params;
    typedef numeric_limits<decltype(p)> num;
    for (int i = 0; i < 3; i++) {
        params[i] = num::max();
    }
}

// for exec_glGetUniform[if]v
template<typename params_t>
int filled_params(params_t params) {
    auto p = *params;
    typedef numeric_limits<decltype(p)> num;
    for (int i = 0; i < 3; i++) { 
        if (params[i] == num::max()) {
            return i;
        }
    }
    return 3;
}

// size of params can be 1, 2 or 3
// depending on kind (scalar, vec2, vec3).
// to guess the size we use magic numbers
// which get possibly overwritten.
void exec_glGetUniformfv(const char *buf, ostream& reply) {
    auto         program          = read_val<GLuint>(buf);
    auto         location         = read_val<GLint>(buf);
    auto         params           = new GLfloat[3];
    fill_params(params);
    glGetUniformfv(program, location, params);
    write(reply, params, filled_params(params));
}

void exec_glGetUniformiv(const char *buf, ostream& reply) {
    auto         program          = read_val<GLuint>(buf);
    auto         location         = read_val<GLint>(buf);
    auto         params           = new GLint[3];
    fill_params(params);
    glGetUniformiv(program, location, params);
    write(reply, params, filled_params(params));
}



#include "execs.inc"


#include "dgl-server.hpp"

static exec_func_t funcs[] = {
#define _DECL(id, ret, name, args) \
    exec_##name,
    #include "decls.inc"
    nullptr
#undef _DECL
};

exec_func_t gles2_exec(uint16_t id) {
    return funcs[id];
};

