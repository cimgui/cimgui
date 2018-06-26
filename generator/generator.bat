:: this is used to rebuild cimgui.h and cimgui.cpp and must be executed in this directory
:: definitions.lua for function definitions
:: structs_and_enums.lua with struct and enum information-definitions
:: impl_definitions.lua for implementation function definitions
:: cimgui_impl.h with implementation function cdefs

:: set your PATH if necessary for LuaJIT or Lua5.1 or luajit with: (for example)
:: set PATH=%PATH%;C:\luaGL;

::process  files
:: arg[1] true=use gcc false=dont use gcc
:: arg[2..] name of implementation to generate
luajit.exe ./generator.lua false glfw opengl3 opengl2 sdl

::copy cimgui.h and cimgui.cpp
copy .\cimgui.h ..\cimgui.h
copy .\cimgui.cpp ..\cimgui.cpp

::leave console open
cmd /k

