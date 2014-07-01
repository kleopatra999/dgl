#include <string>

static std::string names[] = {
#define _DECL(id, ret, name, args) \
    #name,
    #include "gles2-decls.inc"
    ""
#undef _DECL
};

std::string gles2_name(uint16_t id) {
    return names[id];
}
