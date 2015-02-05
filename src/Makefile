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

# $(SOURCES:.cpp=.d) 
all: build-libdgl.so build-dgl

# dependencies
%.d: %.cpp | build-inc
	$(CXX) -MM -MF $@ -MT "$(@:.d=.o) $@" -std=c++11 -Iinclude $<
-include $(SOURCES:.cpp=.d)

# compile targets
libdgl.so: CC = $(CXX)
libdgl.so: LDFLAGS += --shared
libdgl.so: InterceptDynamicLinker.o
libdgl.so: $(AppServer)
libdgl.so: InterceptGles2.o NamesGles2.o utils.o
libdgl.so: InterceptEgl.o NamesEgl.o writer-file.o

dgl: CC = $(CXX)
dgl: LDLIBS += -lEGL -lGLESv2 -lX11 -lboost_program_options
dgl: run-dgl-stream.o
dgl: $(RenderServer)
dgl: run-dgl-server.o
dgl: run-dgl-preloaded.o
dgl: ExecGles2.o NamesGles2.o 
dgl: ExecEgl.o NamesEgl.o utils.o

ExecGles2.o InterceptGles2.o: CXXFLAGS += -Wno-unused-parameter

build-inc: DeclsGles2.inc InterceptGles2.inc ExecGles2.inc

DeclsGles2.inc: ../scripts/gen-gles2-decls.py
	$< > $@
ExecGles2.inc: ../scripts/gen-gles2-exec.py
	$< > $@
InterceptGles2.inc: ../scripts/gen-gles2.py
	$< > $@

build-libdgl.so:    $(build)/libdgl.so
build-dgl-server:   $(build)/dgl-server
build-dgl:          $(build)/dgl

$(build)/%: %
	cp $< $@
