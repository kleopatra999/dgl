#pragma once
#include <memory>

struct RenderServerPriv;

struct RenderServer {
    void run(unsigned short port);
    RenderServer();
    ~RenderServer();
private:
    std::unique_ptr<RenderServerPriv> priv;
};
