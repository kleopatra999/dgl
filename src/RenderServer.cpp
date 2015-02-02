#include "RenderServer.hpp"
#include "RenderServerPriv.hpp"

RenderServer::RenderServer() : priv(new RenderServerPriv()) {}
RenderServer::~RenderServer() {}
