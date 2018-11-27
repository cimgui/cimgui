::set PATH=%PATH%;C:\luaGL;C:\mingw32\bin;
::gcc -E -DIMGUI_DISABLE_OBSOLETE_FUNCTIONS -DIMGUI_API="" -DIMGUI_IMPL_API="" ../imgui/imgui.h > 11.txt

::set PATH=%PATH%;C:\luaGL;
::set PATH=%PATH%;C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.15.26726\bin\Hostx64\x64;

::ejecutar en cmd esto 
::"C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars64.bat"

::cl /P /DIMGUI_DISABLE_OBSOLETE_FUNCTIONS /DIMGUI_API="" /DIMGUI_IMPL_API="" ../imgui/imgui.h 
:: > clout.txt
cl  /P /DCIMGUI_DEFINE_ENUMS_AND_STRUCTS cimguitest.c
cmd /k