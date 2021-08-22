#include "../imgui/imgui.h"

#include "../imgui/backends/imgui_impl_opengl3_loader.h"

//making it accesible for luajit
#ifdef _WIN32
extern "C" __declspec( dllexport ) int Do_gl3wInit(void){ return imgl3wInit();};
#else
extern "C"	int Do_gl3wInit(void){ return imgl3wInit();};
#endif
