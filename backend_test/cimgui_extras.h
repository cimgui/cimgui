

// GL3W/GLFW
#include <GL/gl3w.h>    // This example is using gl3w to access OpenGL functions (because it is small). You may use glew/glad/glLoadGen/etc. whatever already works for you.

//making it accesible for luajit
#ifdef _WIN32
__declspec( dllexport ) int Do_gl3wInit(void);
#else
int Do_gl3wInit(void);
#endif
