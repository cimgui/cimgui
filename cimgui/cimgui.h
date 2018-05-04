
#include <stdio.h>

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
typedef unsigned long long ImU64;
#endif

#ifdef CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "imgui_structs.h"
#endif // CIMGUI_DEFINE_ENUMS_AND_STRUCTS
/*
    struct GlyphRangesBuilder
    {
        ImVector<unsigned char> UsedChars;
    };
typedef struct GlyphRangesBuilder GlyphRangesBuilder;

struct CustomRect
{
    unsigned int ID;
    unsigned short Width, Height;
    unsigned short X, Y;
    float GlyphAdvanceX;
    ImVec2 GlyphOffset;
    ImFont* Font;
};
typedef struct CustomRect CustomRect;

    struct TextRange
    {
        const char* b;
        const char* e;
    };
typedef struct TextRange TextRange;

    struct Pair
    {
        ImGuiID key;
        union { int val_i; float val_f; void* val_p; };
    };
typedef struct Pair Pair;

typedef ImFontAtlas::GlyphRangesBuilder GlyphRangesBuilder;
typedef ImFontAtlas::CustomRect CustomRect;
typedef ImGuiTextFilter::TextRange TextRange;
typedef ImGuiStorage::Pair Pair;
*/

#include "auto_funcs.h"

//no LogTextV
CIMGUI_API void igLogText(CONST char *fmt, ...);
//no appendfV
CIMGUI_API void ImGuiTextBuffer_appendf(struct ImGuiTextBuffer *buffer, const char *fmt, ...);
CIMGUI_API void ImFontConfig_DefaultConstructor(ImFontConfig *config);

