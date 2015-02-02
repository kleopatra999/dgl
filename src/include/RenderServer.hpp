#pragma once
#include <memory>

struct RenderServerPriv;

struct RenderServer {
    void make_main_window();
    void run(unsigned short port);
    RenderServer();
    ~RenderServer();
private:
    std::unique_ptr<RenderServerPriv> priv;
};
