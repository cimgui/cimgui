
#include "../imgui/imgui.h"
//#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"

// to use placement new
#define IMGUI_DEFINE_PLACEMENT_NEW
#include "../imgui/imgui_internal.h"

#include "auto_funcs.cpp"

CIMGUI_API void igLogText(CONST char *fmt, ...)
{
    char buffer[256];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, 256, fmt, args);
    va_end(args);

    ImGui::LogText("%s", buffer);
}
CIMGUI_API void ImGuiTextBuffer_appendf(struct ImGuiTextBuffer *buffer, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    buffer->appendfv(fmt, args);
    va_end(args);
}
