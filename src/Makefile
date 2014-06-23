#################################
# ClusterGL main makefile
#################################

build   := ../build/

SOURCES     := $(wildcard *.cpp)
OBJS        := $(patsubst %.cpp, %.o, $(SOURCES))
SRC_EXEC    := $(wildcard exec_*.cpp)

CC            = clang++
CXX           = $(CC)
CXXFLAGS      = -std=c++11 -march=native -Iinclude -O0 -Wextra -g -fPIC -fvisibility-inlines-hidden
LDFLAGS       = $(CXXFLAGS)
LDLIBS        = -lboost_system

all: $(SOURCES:.cpp=.d) build-libdgl.so build-dgl-server

# dependencies
%.d: %.cpp
	$(CC) -MM -MF $@ -MT "$(@:.d=.o) $@" $(CXXFLAGS) $<
-include $(SOURCES:.cpp=.d)

# compile targets
dgl-server: LDLIBS += -lSDL2 -lGL -lGLU -lGLEW
dgl-server: dgl-handle-call.o dgl-func-names.o dgl-exec-funcs.o
dgl-server: dgl-make-window.o consts.o
dgl-server: exec_gl.o exec_glx.o exec_glu.o exec_dgl.o

libdgl.so: LDFLAGS += --shared
libdgl.so: dgl-func-names.o consts.o
libdgl.so: intercept-cache.o dlintercept.o
libdgl.so: intercept.o intercept-send-pointers.o
libdgl.so: intercept-gl.o intercept-glx.o

exec_gl.o exec_glu.o exec_glx.o mod_app.p \
intercept-gl.o: \
    CXXFLAGS += -Wno-unused-parameter

build-libdgl.so:    $(build)/libdgl.so
build-dgl-server:   $(build)/dgl-server

$(build)/%: %
	cp $< $@
