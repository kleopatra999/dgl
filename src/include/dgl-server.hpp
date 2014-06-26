#pragma once
#include "dgl.hpp"
#include <SDL2/SDL.h>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

typedef void (*ExecFunc)(char *buf);

extern const char *_dgl_pushRet_ptr;
extern uint32_t    _dgl_pushRet_size;
extern bool        _dgl_pushRet_delete;
extern bool        exec_dont_delete_args;

SDL_Window *        dgl_main_window();
SDL_Window *        dgl_make_window();
void                dgl_make_main_window();
ExecFunc            dgl_exec_func(uint16_t id);
void                dgl_init_exec_funcs();
void                dgl_handle_call(tcp::socket& socket);
