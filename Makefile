#
# Cross Platform Makefile
# Compatible with Ubuntu 14.04.1 and macOS

OBJS = cimgui.o
OBJS += ./imgui/imgui.o
OBJS += ./imgui/imgui_draw.o
OBJS += ./imgui/imgui_demo.o
OBJS += ./imgui/imgui_tables.o
OBJS += ./imgui/imgui_widgets.o

CXXFLAGS=-o2 -fno-exceptions -fno-rtti

UNAME_S ?= $(shell uname -s)

ifeq ($(WASM),1)
	UNAME_S := WASM
endif

AR := ar -rc

LINKFLAGS =
CFLAGS = $(CXXFLAGS)

ifeq ($(UNAME_S), Linux) #LINUX
	ECHO_MESSAGE = "Linux"

	OUTPUTNAME = cimgui.so
	CXXFLAGS += -I./imgui/
	CXXFLAGS += -Wall
	CXXFLAGS += -shared -fPIC
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(UNAME_S), Darwin) #APPLE
	ECHO_MESSAGE = "macOS"

	OUTPUTNAME = cimgui.dylib
	CXXFLAGS += -I/usr/local/include
	CXXFLAGS += -Wall
	LINKFLAGS = -dynamiclib
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(OS), Windows_NT)
	ECHO_MESSAGE = "Windows"

	OUTPUTNAME = cimgui.dll
	CXXFLAGS += -I./imgui/
	CXXFLAGS += -Wall
	CXXFLAGS += -shared
	LINKFLAGS = -limm32
endif

ifeq ($(UNAME_S), WASM)
	ECHO_MESSAGE = "WASM (via musl-clang or wasi-clang)"

	OUTPUTNAME = libcimgui.wasm
	CXX ?= $(CC)
	CXXFLAGS += --target=wasm32 -nostdlib -I./imgui/ -Wall -Wno-unused-command-line-argument
	CXXFLAGS += -Wno-missing-prototypes -Wno-unused-variable
	CXXFLAGS += -fvisibility=hidden
	CXXFLAGS += -fno-threadsafe-statics
	CXXFLAGS += -D__wasi__ -DIMGUI_DISABLE_FILE_FUNCTIONS
	CFLAGS = $(CXXFLAGS)
	LINKFLAGS += -Wl,--no-entry -Wl,--export-all
endif

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all:$(OUTPUTNAME)
	@echo Build complete for $(ECHO_MESSAGE)

static:$(OBJS)
	$(AR) libcimgui.a $(OBJS)

$(OUTPUTNAME):$(OBJS)
	$(CXX) -o $(OUTPUTNAME) $(OBJS) $(CXXFLAGS) $(LINKFLAGS)

clean:
ifeq ($(OS),Windows_NT)
	del /q $(subst /,\,$(OBJS))
else
	rm -f $(OBJS)
endif

fclean: clean
ifeq ($(OS),Windows_NT)
	del /q $(subst /,\,$(OUTPUTNAME))
else
	rm -f $(OUTPUTNAME)
endif

re: fclean all

.PHONY: all clean fclean re static
