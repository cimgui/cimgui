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

#ifndef CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#ifdef IMGUI_ENABLE_FREETYPE
#include "./imgui/misc/freetype/imgui_freetype.h"
#endif
#endif


#ifdef CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "imgui_structs.h"
#else
struct GLFWwindow;
struct SDL_Window;
typedef union SDL_Event SDL_Event;
#endif // CIMGUI_DEFINE_ENUMS_AND_STRUCTS

PLACE_STRUCTS_C

#include "auto_funcs.h"

/////////////////////////hand written functions
//no appendfV
CIMGUI_API void ImGuiTextBuffer_appendf(ImGuiTextBuffer *self, const char *fmt, ...);
//for getting FLT_MAX in bindings
CIMGUI_API float igGET_FLT_MAX(void);
//for getting FLT_MIN in bindings
CIMGUI_API float igGET_FLT_MIN(void);


CIMGUI_API ImVector_ImWchar* ImVector_ImWchar_create(void);
CIMGUI_API void ImVector_ImWchar_destroy(ImVector_ImWchar* self);
CIMGUI_API void ImVector_ImWchar_Init(ImVector_ImWchar* p);
CIMGUI_API void ImVector_ImWchar_UnInit(ImVector_ImWchar* p);

#ifdef IMGUI_HAS_DOCK
CIMGUI_API void ImGuiPlatformIO_Set_Platform_GetWindowPos(ImGuiPlatformIO* platform_io, void(*user_callback)(ImGuiViewport* vp, ImVec2* out_pos));
CIMGUI_API void ImGuiPlatformIO_Set_Platform_GetWindowSize(ImGuiPlatformIO* platform_io, void(*user_callback)(ImGuiViewport* vp, ImVec2* out_size));
#endif

#endif //CIMGUI_INCLUDED




