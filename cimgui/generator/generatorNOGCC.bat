rem this is used to rebuild imgui_structs.h
rem set your PATH if necessary for gcc and lua with:
set PATH=%PATH%;C:\luaGL;

rem type ..\..\imgui\imgui.h  | luajit.exe ./generator.lua false > out.txt
type ..\..\imgui\imgui.h ..\..\imgui\examples\imgui_impl_glfw.h ..\..\imgui\examples\imgui_impl_opengl3.h  | luajit.exe ./generator.lua false > out.txt

::copy cimgui.h and cimgui.cpp
copy .\cimgui.h ..\cimgui.h
copy .\cimgui.cpp ..\cimgui.cpp

cmd /k

