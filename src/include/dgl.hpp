#pragma once
#include <string>
#include <ostream>

static const uint16_t gles2_partition   = 0x0100;
static const uint16_t egl_partition     = 0x0200;

std::string         dgl_func_name   (uint16_t id);
std::string         gles2_name      (uint16_t id);
std::string         egl_name        (uint16_t id);

typedef void (*exec_func_t)(
    const char     *buf,
    std::ostream&   reply_stream);

exec_func_t         dgl_exec_func   (uint16_t id);
exec_func_t         gles2_exec      (uint16_t id);
exec_func_t         egl_exec        (uint16_t id);

void run_dgl_stream(const std::string& path);
