#pragma once
#include "dgl.hpp"
#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio::ip;

typedef tcp::socket     socket_t;
typedef tcp::endpoint   endpoint_t;
typedef tcp::acceptor   acceptor_t;

void                dgl_make_main_window();
void                dgl_init_exec_funcs();
void                dgl_handle_call(socket_t& socket);
