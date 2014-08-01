#pragma once
#include "dgl.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <boost/asio.hpp>

using namespace boost::asio::ip;

typedef tcp::socket     socket_t;
typedef tcp::endpoint   endpoint_t;
typedef tcp::acceptor   acceptor_t;


typedef void (*exec_func_t)(
    const char     *buf,
    std::ostream&   reply_stream);

extern const char *_dgl_pushRet_ptr;
extern uint32_t    _dgl_pushRet_size;
extern bool        _dgl_pushRet_delete;
extern bool        exec_dont_delete_args;

SDL_Window *        dgl_main_window();
SDL_Window *        dgl_make_window();
void                dgl_make_main_window();
void                dgl_init_exec_funcs();
void                dgl_handle_call(socket_t& socket);



exec_func_t         gles2_exec      (uint16_t id);
exec_func_t         egl_exec        (uint16_t id);

static
exec_func_t         dgl_exec_func(uint16_t id) {
    if (id & gles2_partition)
        return gles2_exec   (id ^ id & gles2_partition);
    if (id & egl_partition  )
        return egl_exec     (id ^ id & egl_partition);
    return nullptr;
}
