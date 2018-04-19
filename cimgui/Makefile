#
# Cross Platform Makefile
# Compatible with Ubuntu 14.04.1 and Mac OS X

OBJS = cimgui.o
OBJS += fontAtlas.o
OBJS += drawList.o
OBJS += listClipper.o
#OBJS += test.o
OBJS += ../imgui/imgui.o
OBJS += ../imgui/imgui_draw.o
OBJS += ../imgui/imgui_demo.o

CXXFLAGS=-O2

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux) #LINUX
	ECHO_MESSAGE = "Linux"

	OUTPUTNAME = cimgui.so
	CXXFLAGS += -I../../
	CXXFLAGS += -Wall
	CXXFLAGS += -shared -fPIC
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(UNAME_S), Darwin) #APPLE
	ECHO_MESSAGE = "Mac OS X"

	OUTPUTNAME = cimgui.dylib
	CXXFLAGS += -I/usr/local/include
	CXXFLAGS += -Wall
	LINKFLAGS = -dynamiclib
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(OS), Windows_NT)
	ECHO_MESSAGE = "Windows"

	OUTPUTNAME = cimgui.dll
	CXXFLAGS += -I../../
	CXXFLAGS += -Wall
	CXXFLAGS += -shared
	LINKFLAGS = -limm32
	CFLAGS = $(CXXFLAGS)
endif

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all:imgui_example
	@echo Build complete for $(ECHO_MESSAGE)

imgui_example:$(OBJS)
	$(CXX) -o $(OUTPUTNAME) $(OBJS) $(CXXFLAGS) $(LINKFLAGS)

clean:
	rm $(OBJS)
