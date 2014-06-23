#pragma once

#include <cstdint>

extern const char *_dgl_pushRet_ptr;
extern uint32_t    _dgl_pushRet_size;
extern bool        _dgl_pushRet_delete;

#define popBuf() (commandbuf)

template<typename T>
void pushRet(T val) {
    _dgl_pushRet_size   = sizeof(T);
    _dgl_pushRet_ptr    = (const char*)new T(val);
}

static void pushRet(const void *ptr, uint32_t size) {
    _dgl_pushRet_ptr    = (const char*)ptr;
    _dgl_pushRet_size   = size;
    if (size == 0) {
        _dgl_pushRet_delete = false;
    }
}

static void pushRet(const void *ptr, uint32_t size, bool del) {
    _dgl_pushRet_delete = del;
    pushRet(ptr, size);
}
