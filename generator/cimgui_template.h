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
    #define API
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

//UDT stuff
typedef struct ImVec2_Simple { float x; float y; } ImVec2_Simple;
typedef struct ImVec4_Simple { float x; float y; float z; float w;} ImVec4_Simple;
typedef struct ImColor_Simple { ImVec4_Simple Value;} ImColor_Simple;


#ifndef CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "imgui_structs.h"
#else
struct GLFWwindow;
struct SDL_Window;
typedef union SDL_Event SDL_Event;
inline ImVec2_Simple ImVec2ToSimple(ImVec2 vec)
{
	ImVec2_Simple result;
    result.x = vec.x;
    result.y = vec.y;
    return result;
}
inline ImVec4_Simple ImVec4ToSimple(ImVec4 vec)
{
	ImVec4_Simple result;
    result.x = vec.x;
    result.y = vec.y;
	result.z = vec.z;
    result.w = vec.w;
    return result;
}
inline ImColor_Simple ImColorToSimple(ImColor col)
{
	ImColor_Simple result;
    result.Value = ImVec4ToSimple(col.Value);
    return result;
}
#endif // ndef CIMGUI_DEFINE_ENUMS_AND_STRUCTS

#include "auto_funcs.h"

/////////////////////////hand written functions
//no LogTextV
CIMGUI_API void igLogText(CONST char *fmt, ...);
//no appendfV
CIMGUI_API void ImGuiTextBuffer_appendf(struct ImGuiTextBuffer *buffer, const char *fmt, ...);
//for getting FLT_MAX in bindings
CIMGUI_API float igGET_FLT_MAX();
//not const args from & to *
CIMGUI_API void igColorConvertRGBtoHSV(float r,float g,float b,float *out_h,float *out_s,float *out_v);
CIMGUI_API void igColorConvertHSVtoRGB(float h,float s,float v,float *out_r,float *out_g,float *out_b);

CIMGUI_API ImVector_ImWchar* ImVector_ImWchar_create();
CIMGUI_API void ImVector_ImWchar_destroy(ImVector_ImWchar* self);
CIMGUI_API void ImVector_ImWchar_Init(ImVector_ImWchar* p);
CIMGUI_API void ImVector_ImWchar_UnInit(ImVector_ImWchar* p);
#endif //CIMGUI_INCLUDED




