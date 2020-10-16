

//making it accesible for main
#ifdef _WIN32
__declspec( dllexport ) int Do_gl3wInit(void);
#else
int Do_gl3wInit(void);
#endif
