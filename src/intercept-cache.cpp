#include <map>
#include <GL/gl.h>
#include <cstring>

using namespace std;

/*********************************************************
	Local cache. Used for things like glGetFloatv()
*********************************************************/
static map<GLenum, char *> mLocalCache;

char *checkLocalCache(GLenum p){
	if(mLocalCache.find(p) != mLocalCache.end()){
		return mLocalCache[p];
	}
	return NULL;
}

void addLocalCache(GLenum p, char *buf, int len){
	auto b = new char[len];
	memcpy(b, buf, len);
	mLocalCache[p] = b;
}

//Called at every swapBuffer(), as things are probably no longer valid then
void dgl_cache_clear(){
	for (map<GLenum, char *>::iterator i = mLocalCache.begin();
			i != mLocalCache.end(); i++){
		delete i->second;
	}
	mLocalCache.clear();
}

