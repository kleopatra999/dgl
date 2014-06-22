#################################
# ClusterGL main makefile
#################################

build   := ../build/

SOURCES := $(wildcard *.cpp)
OBJS    := $(patsubst %.cpp, %.o, $(SOURCES))

CC            = clang++
CXX           = $(CC)
CXXFLAGS      = -std=c++11 -march=native -Iinclude -O2 -Wextra -g -fPIC -fvisibility-inlines-hidden
LDFLAGS       = $(CXXFLAGS)
LDLIBS        = -lboost_system
DARWIN_LDLIBS = -framework,Cocoa -framework OpenGL -lintl
LINUX_LDLIBS  =

# architectecture specific
UNAME  := $(shell uname -s)
ifeq ($(UNAME),Darwin)
LDLIBS += $(DARWIN_LDLIBS)
endif
ifeq ($(UNAME),Linux)
LDLIBS += $(LINUX_LDLIBS)
endif

all: $(SOURCES:.cpp=.d) build-libdgl.so build-dgl-server

# dependencies
%.d: %.cpp
	$(CC) -MM -MF $@ -MT "$(@:.d=.o) $@" $(CXXFLAGS) $<
-include $(SOURCES:.cpp=.d)

# compile targets
dgl-server: LDLIBS += -lSDL -lGL -lGLU -lGLEW
dgl-server: mod_exec.o function_names.o consts.o

libdgl.so: LDFLAGS += --shared
libdgl.so: LBLIBS += -ldl
libdgl.so: dlintercept.o mod_app.o consts.o function_names.o

mod_app.o mod_exec.o:   CXXFLAGS += -Wno-unused-parameter

build-libdgl.so:    $(build)/libdgl.so
build-dgl-server:   $(build)/dgl-server

$(build)/%: %
	cp $< $@
