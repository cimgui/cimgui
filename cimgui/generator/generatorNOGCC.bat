rem this is used to rebuild imgui_structs.h
rem set your PATH if necessary for gcc and lua with:
set PATH=%PATH%;C:\luaGL;

type ..\..\imgui\imgui.h  | luajit.exe ./generator.lua false > out.txt

cmd /k

