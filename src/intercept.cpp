#include "intercept.hpp"

void dgl_swap() {
    pushOp(1499);
	dgl_cache_clear();
	dgl_sync(buffer((void*)nullptr, 0));
}
