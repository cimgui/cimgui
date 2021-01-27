#ifndef CIMGUI_INCLUDED
#define CIMGUI_INCLUDED
#include <stdio.h>
#include <stdint.h>
#if defined _WIN32 || defined __CYGWIN__
    #ifdef CIMGUI_NO_EXPORT
        #define API
    #else
        #define API __declspec(dllexport)
    #endif
    #ifndef __GNUC__
    #define snprintf sprintf_s
    #endif
#else
    #ifdef __GNUC__
        #define API  __attribute__((__visibility__("default")))
    #else
        #define API
    #endif
#endif

#if defined __cplusplus
    #define EXTERN extern "C"
#else
    #include <stdarg.h>
    #include <stdbool.h>
    #define EXTERN extern
#endif

#define CIMGUI_API EXTERN API
#define CONST const


#ifdef _MSC_VER
typedef unsigned __int64 ImU64;
#else
//typedef unsigned long long ImU64;
#endif


#ifdef CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "imgui_structs.h"
#else
struct GLFWwindow;
struct SDL_Window;
typedef union SDL_Event SDL_Event;
#endif // CIMGUI_DEFINE_ENUMS_AND_STRUCTS

#include "auto_funcs.h"

/////////////////////////hand written functions
//no LogTextV
CIMGUI_API void igLogText(CONST char *fmt, ...);
//no appendfV
CIMGUI_API void ImGuiTextBuffer_appendf(struct ImGuiTextBuffer *buffer, const char *fmt, ...);
//for getting FLT_MAX in bindings
CIMGUI_API float igGET_FLT_MAX();
//for getting FLT_MIN in bindings
CIMGUI_API float igGET_FLT_MIN();


CIMGUI_API ImVector_ImWchar* ImVector_ImWchar_create();
CIMGUI_API void ImVector_ImWchar_destroy(ImVector_ImWchar* self);
CIMGUI_API void ImVector_ImWchar_Init(ImVector_ImWchar* p);
CIMGUI_API void ImVector_ImWchar_UnInit(ImVector_ImWchar* p);


#endif //CIMGUI_INCLUDED




