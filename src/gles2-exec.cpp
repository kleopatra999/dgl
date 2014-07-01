#include <assert.h>
#include <cstring>
#include <GLES2/gl2.h>

using namespace std;

bool            exec_dont_delete_args;

#include "instruction.hpp"
#include <type_traits>

template<typename type>
type read_val(char *&buf) {
    auto ret = *(type*)buf;
    buf     += sizeof(type);
    return ret;
}

template<typename type>
type read_ptr(char *&buf) {
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

static
size_t pname_size(GLenum pname) {
    return 1;
}

static
size_t read_pixels_size(
        GLsizei     width,
        GLsizei     height,
        GLenum      format) {
    return 1;
}



void exec_glShaderSource(char *buf, ostream& reply)
{
    auto    shader      = read_val<GLuint>(buf);
    GLsizei count       = 1;
    auto    length      = nullptr;
    auto    source      = read_ptr<const GLchar *>(buf);
    const GLchar *string[1]{ source };
	glShaderSource(shader, count, string, length);
}

void exec_glBufferData(char *buf, ostream& reply) {
    auto         target           = read_val<GLenum>(buf);
    auto         size             = read_val<GLsizeiptr>(buf);
    auto         usage            = read_val<GLenum>(buf);
    auto         data             = read_ptr<const char *>(buf);
    // TODO memory leak
    auto         data_copy        = new char[size];
    copy(data, data + size, data_copy);
    glBufferData(target, size, data_copy, usage);
}

void exec_glVertexAttribPointer(char *buf, ostream& reply) {
    auto         index            = read_val<GLuint>(buf);
    auto         size             = read_val<GLint>(buf);
    auto         type             = read_val<GLenum>(buf);
    auto         normalized       = read_val<GLboolean>(buf);
    auto         stride           = read_val<GLsizei>(buf);
    auto         pointer          = read_val<const void *>(buf);
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}



#include <limits>
#include <algorithm>
#include "gles2-exec.inc"


#include "dgl-server.hpp"

static exec_func_t funcs[] = {
#define _DECL(id, ret, name, args) \
    exec_##name,
    #include "gles2-decls.inc"
    nullptr
#undef _DECL
};

exec_func_t gles2_exec(uint16_t id) {
    return funcs[id];
};

