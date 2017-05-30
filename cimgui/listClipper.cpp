#include "../imgui/imgui.h"
#include "cimgui.h"

CIMGUI_API void ImGuiListClipper_Begin(ImGuiListClipper* clipper, int count, float items_height)
{
  clipper->Begin(count, items_height);
}

CIMGUI_API void ImGuiListClipper_End(ImGuiListClipper* clipper)
{
  clipper->End();
}

CIMGUI_API bool ImGuiListClipper_Step(ImGuiListClipper* clipper)
{
  return clipper->Step();
}

CIMGUI_API int ImGuiListClipper_GetDisplayStart(ImGuiListClipper* clipper)
{
  return clipper->DisplayStart;
}

CIMGUI_API int ImGuiListClipper_GetDisplayEnd(ImGuiListClipper* clipper)
{
  return clipper->DisplayEnd;
}
