:: this script must be executed in this directory
:: all the output goes to generator/output folder
:: .cpp and .h files:
:: cimgui.h and cimgui.cpp with gcc preprocess
:: cimgui_nopreprocess.h and cimgui_nopreprocess.cpp generated without preprocess
:: cimgui_impl.h with implementation function cdefs
:: lua and json files:
:: definitions.lua for function definitions
:: structs_and_enums.lua with struct and enum information-definitions
:: impl_definitions.lua for implementation function definitions

:: set your PATH if necessary for LuaJIT or Lua5.1 or luajit with: (for example)
set PATH=%PATH%;C:\anima;C:\mingws\i686-7.2.0-release-posix-dwarf-rt_v5-rev1\mingw32\bin;
:: set PATH=%PATH%;C:\luaGL;C:\i686-7.2.0-release-posix-dwarf-rt_v5-rev1\mingw32\bin;
:: set PATH=%PATH%;C:\luaGL\sources\luajit-master\luajit-master\bin\mingw32;C:\mingw32\bin;
::process  files
:: arg[1] compiler name gcc, clang or cl
:: arg[2] options as words in one string: internal for imgui_internal generation, freetype for freetype generation
:: examples: "" "internal" "internal freetype"
:: arg[3..n] name of implementations to generate and/or CFLAGS (e.g. -DIMGUI_USER_CONFIG or -DIMGUI_USE_WCHAR32)
luajit ./generator.lua gcc "internal" glfw opengl3 opengl2 sdl

::leave console open
cmd /k

