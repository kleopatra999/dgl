#################################
# ClusterGL main makefile
#################################

build   := ../build/

SOURCES     := $(wildcard *.cpp)
OBJS        := $(patsubst %.cpp, %.o, $(SOURCES))
SRC_EXEC    := $(wildcard exec_*.cpp)

CXX           = clang++
CXXFLAGS      = -std=c++11 -march=native -Iinclude -O2 -Wextra -Wall -Werror -g -fPIC -fvisibility-inlines-hidden
LDFLAGS       = $(CXXFLAGS)
LDLIBS        = -lboost_system -lboost_iostreams -lboost_timer -lprofiler

RenderServer := $(filter RenderServer%,$(OBJS))
AppServer    := $(filter AppServer%,$(OBJS))

all: build-libdgl.so build-dgl

# dependencies
%.d: %.cpp gles2-decls.inc gles2-exec.inc gles2.inc
	$(CXX) -MM -MF $@ -MT "$(@:.d=.o) $@" -std=c++11 -Iinclude $<
-include $(SOURCES:.cpp=.d)

# compile targets
libdgl.so: CC = $(CXX)
libdgl.so: LDFLAGS += --shared
libdgl.so: InterceptDynamicLinker.o
libdgl.so: $(AppServer)
libdgl.so: gles2.o gles2-names.o utils.o
libdgl.so: egl.o egl-names.o writer-file.o

dgl: CC = $(CXX)
dgl: LDLIBS += -lEGL -lGLESv2 -lX11 -lboost_program_options
dgl: run-dgl-stream.o
dgl: $(RenderServer)
dgl: run-dgl-server.o
dgl: run-dgl-preloaded.o
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
