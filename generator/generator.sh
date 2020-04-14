#!/usr/bin/sh

# this script must be executed in this directory
# all the output goes to generator/output folder
# .cpp and .h files:
# cimgui.h and cimgui.cpp with gcc preprocess
# cimgui_nopreprocess.h and cimgui_nopreprocess.cpp generated without preprocess
# cimgui_impl.h with implementation function cdefs
# lua and json files:
# definitions.lua for function definitions
# structs_and_enums.lua with struct and enum information-definitions
# impl_definitions.lua for implementation function definitions

#process  files
# arg[1] compiler name gcc, clang, or cl
# arg[2] imgui_internal functions generation: true or false
# arg[3..n] name of implementations to generate
luajit ./generator.lua gcc true glfw opengl3 opengl2 sdl
