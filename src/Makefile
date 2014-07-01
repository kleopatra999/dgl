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

all: $(SOURCES:.cpp=.d)
all: build-libdgl.so build-dgl-server

# dependencies
%.d: %.cpp gles2-decls.inc gles2-exec.inc gles2.inc
	$(CC) -MM -MF $@ -MT "$(@:.d=.o) $@" $(CXXFLAGS) $<
-include $(SOURCES:.cpp=.d)

# compile targets
dgl-server: LDLIBS += -L./eglut/ -leglut_x11 -lSDL2 -lEGL -lGLESv2 -lX11
dgl-server: dgl-handle-call.o
dgl-server: dgl-make-window.o consts.o
dgl-server: gles2-exec.o gles2-names.o
dgl-server: egl-exec.o egl-names.o

libdgl.so: LDFLAGS += --shared
libdgl.so: consts.o dlintercept.o
libdgl.so: gles2.o gles2-names.o
libdgl.so: egl.o egl-names.o

exec_gl.o exec_glu.o exec_glx.o mod_app.p \
intercept-gl.o gles2-exec.o gles2.o: \
    CXXFLAGS += -Wno-unused-parameter

%.inc: ../scripts/gen-%.py
	$< > $@

build-libdgl.so:    $(build)/libdgl.so
build-dgl-server:   $(build)/dgl-server

$(build)/%: %
	cp $< $@
