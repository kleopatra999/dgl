#################################
# ClusterGL main makefile
#################################

build   := ../build/

SOURCES     := $(wildcard *.cpp)
OBJS        := $(patsubst %.cpp, %.o, $(SOURCES))
SRC_EXEC    := $(wildcard exec_*.cpp)

CXX           = clang++
CXXFLAGS      = -std=c++11 -march=native -Iinclude -O0 -Wextra -Wall -g -fPIC -fvisibility-inlines-hidden
LDFLAGS       = $(CXXFLAGS)
LDLIBS        = -lboost_system -lboost_iostreams -lboost_timer -lprofiler

all: build-libdgl.so build-dgl-server build-dgl

# dependencies
%.d: %.cpp gles2-decls.inc gles2-exec.inc gles2.inc
	$(CXX) -MM -MF $@ -MT "$(@:.d=.o) $@" -std=c++11 -Iinclude $<
-include $(SOURCES:.cpp=.d)

# compile targets
dgl-server: CC = $(CXX)
dgl-server: LDLIBS += -lEGL -lGLESv2 -lX11
dgl-server: dgl-handle-call.o utils.o
dgl-server: dgl-make-window.o
dgl-server: gles2-exec.o gles2-names.o
dgl-server: egl-exec.o egl-names.o

libdgl.so: CC = $(CXX)
libdgl.so: LDFLAGS += --shared
libdgl.so: dlintercept.o
libdgl.so: gles2.o gles2-names.o utils.o
libdgl.so: egl.o egl-names.o writer-file.o

dgl: CC = $(CXX)
dgl: LDLIBS += -lEGL -lGLESv2 -lX11 -lboost_program_options
dgl: run-dgl-stream.o dgl-make-window.o
dgl: run-dgl-server.o dgl-handle-call.o
dgl: gles2-exec.o gles2-names.o 
dgl: egl-exec.o egl-names.o utils.o

gles2-exec.o gles2.o: CXXFLAGS += -Wno-unused-parameter

%.inc: ../scripts/gen-%.py
	$< > $@

build-libdgl.so:    $(build)/libdgl.so
build-dgl-server:   $(build)/dgl-server
build-dgl:          $(build)/dgl

$(build)/%: %
	cp $< $@
