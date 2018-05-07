rem this is used to rebuild imgui_structs.h
rem set your PATH if necessary for gcc and lua with:
set PATH=%PATH%;C:\mingw32\bin;C:\luaGL;

gcc -E -DIMGUI_DISABLE_OBSOLETE_FUNCTIONS  ../../imgui/imgui.h | luajit.exe ./generator.lua > out.txt
rem gcc -E   ../imgui/imgui.h > imgui_structs.raw
cmd /k

