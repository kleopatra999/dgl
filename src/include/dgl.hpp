#pragma once
#include <string>

static const uint16_t gles2_partition   = 0x0100;
static const uint16_t egl_partition     = 0x0200;

std::string         gles2_name      (uint16_t id);
std::string         egl_name        (uint16_t id);

static
std::string         dgl_func_name   (uint16_t id) {
    if (id & gles2_partition)
        return gles2_name   (id ^ id & gles2_partition);
    if (id & egl_partition  )
        return egl_name     (id ^ id & egl_partition);
    return "unknown";
}
