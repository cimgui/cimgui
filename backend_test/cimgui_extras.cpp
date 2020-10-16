#include "../imgui/imgui.h"

// GL3W/GLFW
#include <GL/gl3w.h>    // This example is using gl3w to access OpenGL functions (because it is small). You may use glew/glad/glLoadGen/etc. whatever already works for you.

//making it accesible for luajit
#ifdef _WIN32
extern "C" __declspec( dllexport ) int Do_gl3wInit(void){ return gl3wInit();};
#else
extern "C"	int Do_gl3wInit(void){ return gl3wInit();};
#endif
