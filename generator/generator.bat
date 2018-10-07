:: this script must be executed in this directory
:: all the output goes to generated folder
:: .cpp and .h files:
:: cimgui_nopreprocess.h and cimgui_nopreprocess.cpp generated without preprocess
:: cimgui.h and cimgui.cpp with gcc preprocess
:: cimgui_impl.h with implementation function cdefs
:: lua and json files:
:: definitions.lua for function definitions
:: structs_and_enums.lua with struct and enum information-definitions
:: impl_definitions.lua for implementation function definitions

:: set your PATH if necessary for LuaJIT or Lua5.1 or luajit with: (for example)
 set PATH=%PATH%;C:\luaGL;C:\mingw32\bin;
:: set PATH=%PATH%;C:\luaGL;C:\i686-7.2.0-release-posix-dwarf-rt_v5-rev1\mingw32\bin;
::process  files
:: arg[1..n] name of implementations to generate
luajit.exe ./generator.lua glfw opengl3 opengl2 sdl

::copy cimgui.h and cimgui.cpp
copy .\generated\cimgui.h ..\cimgui.h
copy .\generated\cimgui.cpp ..\cimgui.cpp

::leave console open
cmd /k

