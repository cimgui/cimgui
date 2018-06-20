:: this is used to rebuild cimgui.h and cimgui.cpp and must be executed in this directory

:: set your PATH if necessary for gcc and lua 5.1 or luajit with:
set PATH=%PATH%;C:\mingw32\bin;C:\luaGL;

:: gcc -E  preprocesor striped comments
:: gcc -E -C //comments but not /* and multiple spaces to one
:: gcc -E -CC // and /* comments
:: gcc -E -C -traditional-cpp // coments and respects multiple spaces
:: gcc -E -P no #pragma location information

::generate preprocessed file
gcc -E -C -DIMGUI_DISABLE_OBSOLETE_FUNCTIONS -DIMGUI_APIX="" ../../imgui/imgui.h ../../imgui/examples/imgui_impl_glfw.h ../../imgui/examples/imgui_impl_opengl3.h > 1.txt

::process preprocessed file
type 1.txt | luajit.exe ./generator.lua true imgui imgui_impl_glfw imgui_impl_opengl3 > out.txt

::copy cimgui.h and cimgui.cpp
copy .\cimgui.h ..\cimgui.h
copy .\cimgui.cpp ..\cimgui.cpp

::leave console open
cmd /k

