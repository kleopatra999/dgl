#pragma once
#include <GL/gl.h>
#include <sstream>
#include <fstream>

using namespace std;

static
char bytes_per_pixel(GLenum format) {
    // TODO no default, fail if unknown (ie. BGR, BGRA)
    switch (format) {
        case GL_RGB:
            return 3;
        case GL_RGBA:
            return 4;
        default:
            return 1;
    }
}

template<size_t id>
void write_pixels_file(
        string name,
        size_t width,
        size_t height,
        GLenum format,
        char   *pixels) {
    static size_t counter = 0;
    ++counter;
    auto        bbp     = bytes_per_pixel(format);
    auto        ext     = bbp == 1 ? ".pgm" : ".pbm";
    auto        magic   = bbp == 1 ? "P5"   : "P6";
    auto        bytes   = width * height * bbp;
    stringstream s("");
    s << name << "-" << counter << ext;
    ofstream    file(s.str());
    file << magic << " " << width << " " << height << " 255\n";
    if (bbp == 1 || bbp == 3) {
        file.write(pixels, bytes);
    } else if (bbp == 4) {
        for (size_t i = 0; i < bytes; i += 4) {
            file.write(pixels+i, 3);
        }
    }
}

template<size_t id>
void write_glReadPixels(
    string name) {
    auto pixels = new char[800*600*3];
    glReadPixels(0, 0, 800, 600, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    write_pixels_file<id>
        (name, 800, 600, GL_RGB, pixels);
}
