#include <string>
#include <assert.h>
#include <GLES2/gl2.h>

using namespace std;

#include "AppServer.hpp"
#include "dgl.hpp"
#include "gl-utils.hpp"
#include "pixels-utils.hpp"
#include <vector>
#include <boost/asio.hpp>

using boost::asio::buffer;

static Instruction& buf() {
    return app.instructions().back();
}

static
void new_call(uint16_t id) {
    app.instructions().push_back(Instruction(id));
}

static
void send() {
}

static buffers                  return_buffers;
static vector<unique_ptr<char>> ignore_buffers;

static
void receive() {
    app.sync(return_buffers);
    return_buffers.clear();
    ignore_buffers.clear();
}

template<typename type>
void write(type arg) {
    buf().write(arg);
}

template<typename type, typename size_type>
void write(const type *arr, size_type size) {
    if (arr) {
        buf().write(true);
        buf().write(arr, sizeof(type) * size);
    } else {
        buf().write(false);
    }
}

template<typename type = void, typename size_type>
void write(const void *arr, size_type size) {
    if (arr) {
        buf().write(true);
        buf().write((const char *)arr, size);
    } else {
        buf().write(false);
    }
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



#define _DECL(id, ret, name, args) \
static uint16_t ID_##name = id | gles2_partition;
#include "DeclsGles2.inc"
#undef _DECL

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
map<GLuint, gl_something_pointer> vertex_attrib_pointer;

#include "get_type_size.hpp"

extern "C" {

void glDrawElements(
        GLenum      mode,
        GLsizei     count,
        GLenum      type,
        const void *indices) {
    for (auto &e : vertex_attrib_pointer) {
        auto &p = get<1>(e);
        if (p.scheduled) {
            p.scheduled     = false;
            new_call(ID_glVertexAttribPointer);
            write(p.index);
            write(p.size);
            write(p.type);
            write(p.normalized);
            write(p.stride);
            write(true);
            auto el_size    = get_type_size(p.type);
            auto stride     = p.stride ? p.stride : el_size;
            auto first      = reinterpret_cast<const uintptr_t>(indices);
            auto size       = stride * (first+count-1) + el_size;
            write(p.pointer, size);
        }
    }
    new_call(ID_glDrawElements);
    write(mode);
    write(count);
    write(type);
    write(reinterpret_cast<const uintptr_t>(indices));
}

void glDrawArrays(
        GLenum      mode,
        GLint       first,
        GLsizei     count) {
    for (auto &e : vertex_attrib_pointer) {
        auto &p = get<1>(e);
        if (p.scheduled) {
            p.scheduled     = false;
            new_call(ID_glVertexAttribPointer);
            write(p.index);
            write(p.size);
            write(p.type);
            write(p.normalized);
            write(p.stride);
            write(true);
            auto el_size    = get_type_size(p.type);
            auto stride     = p.stride ? p.stride : el_size;
            auto size       = stride * (first+count-1) + el_size;
            write(p.pointer, size);
        }
    }
    new_call(ID_glDrawArrays);
    write(mode);
    write(first);
    write(count);
}

static GLuint array_buffer_bound;

void glBindBuffer(GLenum target, GLuint buffer) {
    new_call (ID_glBindBuffer);
    write    (target          );
    write    (buffer          );
    send     ();
    if (target == GL_ARRAY_BUFFER) {
        array_buffer_bound = buffer;
    }
}

void glDeleteBuffers(GLsizei n, const GLuint * buffers) {
    new_call (ID_glDeleteBuffers);
    write    (n               );
    write    (buffers         , n);
    send     ();
    if (array_buffer_bound) {
        auto last = buffers + n;
        if (find(buffers, last, array_buffer_bound) != last) {
            array_buffer_bound = 0;
        }
    }
}

void glVertexAttribPointer(
        GLuint      index,
        GLint       size,
        GLenum      type,
        GLboolean   normalized,
        GLsizei     stride,
        const void *pointer) {
    if (array_buffer_bound) {
        new_call(ID_glVertexAttribPointer);
        write(index);
        write(size);
        write(type);
        write(normalized);
        write(stride);
        write(false);
        auto ptr_num = reinterpret_cast<uintptr_t>(pointer);
        write(ptr_num);
    } else {
        vertex_attrib_pointer[index] = {
            index, size, type, normalized, stride, pointer, true
        };
    }
}

void glShaderSource(
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

GLenum glGetError() {
	(void)ID_glGetError;
    return 0;
}

void glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void * pixels) {
    new_call (ID_glReadPixels);
    write    (x               );
    write    (y               );
    write    (width           );
    write    (height          );
    write    (format          );
    write    (type            );
    send     ();
    if (getenv("APITRACE_REPLAY")) {
        // apitrace doesn't give a pointer to memory, so replace it
        vector<char> buf(width * height * bytes_per_pixel(format));
        read_rest(buf.data()  );
        receive  ();
    } else {
        read_rest(pixels      );
        receive  ();
    }
}

#include "InterceptGles2.inc"

}
