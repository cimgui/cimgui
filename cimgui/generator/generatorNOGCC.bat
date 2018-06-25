rem this is used to rebuild imgui_structs.h
rem set your PATH if necessary for gcc and lua with:
set PATH=%PATH%;C:\luaGL;


luajit.exe ./generator.lua false 

::copy cimgui.h and cimgui.cpp
::copy .\cimgui.h ..\cimgui.h
::copy .\cimgui.cpp ..\cimgui.cpp

cmd /k

