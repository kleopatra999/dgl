#include <string>
#include <assert.h>
#include <GLES2/gl2.h>

using namespace std;

#include "libdgl.hpp"
#include <vector>
#include <boost/asio.hpp>

using boost::asio::buffer;

static Instruction& buf() {
    return dgl_instructions().back();
}

static
void new_call(uint16_t id) {
    dgl_instructions().push_back(Instruction(id));
}

static
void send() {
}

static buffers                  return_buffers;
static vector<unique_ptr<char>> ignore_buffers;

static
void receive() {
    dgl_sync(return_buffers);
    return_buffers.clear();
    ignore_buffers.clear();
}

template<typename type>
void write(type arg) {
    buf().write(arg);
}

template<typename type, typename size_type>
void write(const type *arr, size_type size) {
    assert(arr);
    buf().write(true);
    buf().write(arr, sizeof(type) * size);
}

template<typename type = void, typename size_type>
void write(const void *arr, size_type size) {
    assert(arr);
    buf().write(true);
    buf().write((const char *)arr, size);
}

template<typename type = GLchar, typename size_type>
void write(const GLchar *str, size_type size) {
    assert(str);
    // TODO choose other magic number
    if (size == 1) {
        size = strlen(str) + 1;
    }
    buf().write(true);
    buf().write(str, size);
}

template<typename type>
void read(type &arg) {
    return_buffers.push_back(
        buffer((char*)&arg, sizeof(arg)));
}

template<typename type>
void read(type *arg) {
    if (!arg) {
        auto ignore = make_unique<char>(sizeof(type));
        arg         = (type*)ignore.get();
        ignore_buffers.push_back(move(ignore));
    }
    return_buffers.push_back(
        buffer((char*)arg, sizeof(type)));
}

template<typename type>
void read(type *arr, size_t size) {
    assert(arr);
    return_buffers.push_back(
        buffer((char*)arr, sizeof(type) * size));
}

template<typename type>
void read_rest(type *arg) {
    assert(arg);
    auto max_size   = numeric_limits<uint32_t>::max();
    auto size       = max_size - buffer_size(return_buffers);
    return_buffers.push_back(
        buffer((char*)arg, size));
}

static size_t size_by_pname(GLenum pname) {
    return 1;
}

static size_t tex_size(GLsizei width, GLsizei height, GLenum format) {
    return 1;
}

#define _DECL(id, ret, name, args) \
static uint16_t ID_##name = id | gles2_partition;
#include "gles2-decls.inc"
#undef _DECL

static void intercept_glDrawElements(
        GLenum      mode,
        GLsizei     count,
        GLenum      type,
        const void *indices) {
    assert(false);
}

struct gl_something_pointer {
    GLuint      index;
    GLint       size;
    GLenum      type;
    GLboolean   normalized;
    GLsizei     stride;
    const void *pointer;
    bool        scheduled;
};

static
gl_something_pointer vertex_attrib_pointer;

#include "get_type_size.hpp"

static void intercept_glDrawArrays(
        GLenum      mode,
        GLint       first,
        GLsizei     count) {
    /*
    auto &p = vertex_attrib_pointer;
    if (p.scheduled) {
        p.scheduled     = false;
        new_call(ID_glVertexAttribPointer);
        write(p.index);
        write(p.size);
        write(p.type);
        write(p.normalized);
        write(p.stride);
        auto el_size    = get_type_size(p.type);
        auto stride     = p.stride ? p.stride : el_size;
        auto size       = stride * (first+count-1) + el_size;
        write(p.pointer, size);
    }*/
    new_call(ID_glDrawArrays);
    write(mode);
    write(first);
    write(count);
}

static void intercept_glVertexAttribPointer(
        GLuint      index,
        GLint       size,
        GLenum      type,
        GLboolean   normalized,
        GLsizei     stride,
        const void *pointer) {
    new_call(ID_glVertexAttribPointer);
    write(index);
    write(size);
    write(type);
    write(normalized);
    write(stride);
    auto ptr_num = reinterpret_cast<uintptr_t>(pointer);
    write(ptr_num);
}

static void intercept_glShaderSource(
        GLuint      shader,
        GLsizei     count,
        const GLchar *const *string,
        const GLint *length) {
        stringstream    stream;
    new_call(ID_glShaderSource);
    write   (shader);
    if (!length) {
        for (GLsizei i = 0; i < count; i++) {
            stream << string[i];
        }
    } else {
	    for (GLsizei i = 0; i < count; i++) {
            if (length[i] < 0) {
                stream << string[i];
            } else {
                stream.write(string[i], length[i]);
            }
        }
    }
    auto str = stream.str();
    write   (str.c_str(), 1);
}

#include "gles2.inc"
