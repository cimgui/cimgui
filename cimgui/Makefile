#
# Cross Platform Makefile
# Compatible with Ubuntu 14.04.1 and Mac OS X

OBJS = cimgui.o
OBJS += fontAtlas.o 
OBJS += drawList.o
#OBJS += test.o
OBJS += ../imgui/imgui.o

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux) #LINUX
	ECHO_MESSAGE = "Linux"

	CXXFLAGS = -I../../
	CXXFLAGS += -Wall
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(UNAME_S), Darwin) #APPLE
	ECHO_MESSAGE = "Mac OS X"

	CXXFLAGS = -I/usr/local/include
	CXXFLAGS += -Wall
	CFLAGS = $(CXXFLAGS)
endif

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all:imgui_example
	@echo Build complete for $(ECHO_MESSAGE)

imgui_example:$(OBJS)
	$(CXX) -dynamiclib -current_version 1.0 -o cimgui.dylib $(OBJS) $(CXXFLAGS)

clean:
	rm $(OBJS)