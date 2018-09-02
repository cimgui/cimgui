
#include "./imgui/imgui.h"
#include "cimgui.h"

#include "./imgui/imgui_internal.h"

#include "auto_funcs.cpp"

/////////////////////////////manual written functions
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
CIMGUI_API void ImFontConfig_DefaultConstructor(ImFontConfig *config)
{
    *config = ImFontConfig();
}
CIMGUI_API float igGET_FLT_MAX()
{
    return FLT_MAX;
}
