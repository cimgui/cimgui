
#include <stdarg.h>
#include <stdio.h>

#include "../imgui/imgui.h"
#include "cimgui.h"

CIMGUI_API ImGuiIO* ig_GetIO()
{
	return &ImGui::GetIO();
}

CIMGUI_API ImGuiStyle* ig_GetStyle()
{
	return &ImGui::GetStyle();
}

CIMGUI_API void ig_NewFrame()
{
	ImGui::NewFrame();
}

CIMGUI_API void ig_Render()
{
	ImGui::Render();
}

CIMGUI_API void ig_Shutdown()
{
	ImGui::Shutdown();
}

CIMGUI_API void ig_ShowUserGuide()
{
	ImGui::ShowUserGuide();
}

CIMGUI_API void ig_ShowStyleEditor(ImGuiStyle* ref)
{
	ImGui::ShowStyleEditor(ref);
}

CIMGUI_API void ig_ShowTestWindow(bool* opened)
{
	ImGui::ShowTestWindow(opened);
}

IMGUI_API void ig_ShowMetricsWindow(bool* opened)
{
	ImGui::ShowMetricsWindow(opened);
}

// Window

CIMGUI_API bool ig_Begin(const char* name, bool* p_opened, ImGuiWindowFlags flags)
{
	return ImGui::Begin(name, p_opened, flags);
}

CIMGUI_API bool ig_Begin2(const char* name, bool* p_opened, const ImVec2 size_on_first_use, float bg_alpha, ImGuiWindowFlags flags)
{
	return ImGui::Begin(name, p_opened, size_on_first_use, bg_alpha, flags);
}

CIMGUI_API void ig_End()
{
	ImGui::End();
}

CIMGUI_API bool ig_BeginChild(const char* str_id, const ImVec2 size, bool border, ImGuiWindowFlags extra_flags)
{
	return ImGui::BeginChild(str_id, size, border, extra_flags);
}

CIMGUI_API bool ig_BeginChild2(ImGuiID id, const ImVec2 size, bool border, ImGuiWindowFlags extra_flags)
{
	return ImGui::BeginChild(id, size, border, extra_flags);
}

CIMGUI_API void ig_EndChild()
{
	ImGui::EndChild();
}

CIMGUI_API void ig_GetContentRegionMax(ImVec2& out)
{
	out = ImGui::GetContentRegionMax();
}

CIMGUI_API void ig_GetWindowContentRegionMin(ImVec2& out)
{
	out = ImGui::GetWindowContentRegionMin();
}

CIMGUI_API void ig_GetWindowContentRegionMax(ImVec2& out)
{
	out = ImGui::GetWindowContentRegionMax();
}

CIMGUI_API ImDrawList* ig_GetWindowDrawList()
{
	return ImGui::GetWindowDrawList();
}

CIMGUI_API ImFont* ig_GetWindowFont()
{
	return ImGui::GetWindowFont();
}

CIMGUI_API float ig_GetWindowFontSize()
{
	return ImGui::GetWindowFontSize();
}

CIMGUI_API void ig_SetWindowFontScale(float scale)
{
	ImGui::SetWindowFontScale(scale);
}

CIMGUI_API void ig_GetWindowPos(ImVec2& out)
{
	out = ImGui::GetWindowPos();
}

CIMGUI_API void ig_GetWindowSize(ImVec2& out)
{
	out = ImGui::GetWindowSize();
}

CIMGUI_API float ig_GetWindowWidth()
{
	return ImGui::GetWindowWidth();
}

CIMGUI_API bool ig_GetWindowCollapsed()
{
	return ImGui::GetWindowCollapsed();
}

CIMGUI_API void ig_SetNextWindowPos(const ImVec2 pos, ImGuiSetCond cond)
{
	ImGui::SetNextWindowPos(pos, cond);
}

CIMGUI_API void ig_SetNextWindowSize(const ImVec2 size, ImGuiSetCond cond)
{
	ImGui::SetNextWindowSize(size, cond);
}

CIMGUI_API void ig_SetNextWindowCollapsed(bool collapsed, ImGuiSetCond cond)
{
	ImGui::SetNextWindowCollapsed(collapsed,cond);
}

CIMGUI_API void ig_SetNextWindowFocus()
{
	ImGui::SetNextWindowFocus();
}

CIMGUI_API void ig_SetWindowPos(const ImVec2 pos, ImGuiSetCond cond)
{
	ImGui::SetWindowPos(pos,cond);
}

CIMGUI_API void ig_SetWindowSize(const ImVec2 size, ImGuiSetCond cond)
{
	ImGui::SetWindowSize(size, cond);
}

CIMGUI_API void ig_SetWindowCollapsed(bool collapsed, ImGuiSetCond cond)
{
	ImGui::SetWindowCollapsed(collapsed,cond);
}

CIMGUI_API void ig_SetWindowFocus()
{
	ImGui::SetWindowFocus();
}

CIMGUI_API void ig_SetWindowPos2(const char* name, const ImVec2 pos, ImGuiSetCond cond)
{
	ImGui::SetWindowPos(name,pos,cond);
}

CIMGUI_API void ig_SetWindowSize2(const char* name, const ImVec2 size, ImGuiSetCond cond)
{
	ImGui::SetWindowSize(name, size, cond);
}

CIMGUI_API void ig_SetWindowCollapsed2(const char* name, bool collapsed, ImGuiSetCond cond)
{
	ImGui::SetWindowCollapsed(name, collapsed, cond);
}

CIMGUI_API void ig_SetWindowFocus2(const char* name)
{
	ImGui::SetWindowFocus(name);
}

CIMGUI_API void ig_Text(const char* text, ...)
{
	char buffer[256];
  	va_list args;
  	va_start (args, text);
  	vsprintf (buffer, text, args);
  	va_end (args);

	ImGui::Text(buffer);
}

CIMGUI_API bool ig_ColorEdit3(const char* label, float col[3])
{
	return ImGui::ColorEdit3(label,col);
}

CIMGUI_API void ig_SliderFloat(const char* label, float* v, float v_min, float v_max, const char* display_format, float power)
{
	ImGui::SliderFloat(label,v,v_min,v_max,display_format,power);
}

CIMGUI_API bool ig_Button(const char* label, const ImVec2 size, bool repeat_when_held)
{
	return ImGui::Button(label,size,repeat_when_held);
}

CIMGUI_API bool ig_SmallButton(const char* label)
{
	return ImGui::SmallButton(label);
}

CIMGUI_API bool ig_TreeNode(const char* str_label_id)
{
	return ImGui::TreeNode(str_label_id);
}

CIMGUI_API bool ig_TreeNode_IdFmt(const void* ptr_id, const char* fmt, ...)
{
	char buffer[256];
  	va_list args;
  	va_start (args, fmt);
  	vsprintf (buffer, fmt, args);
  	va_end (args);

  	//TODO: use TreeNodeV
	return ImGui::TreeNode(ptr_id,"%s",buffer);	
}

CIMGUI_API void ig_TreePop()
{
	ImGui::TreePop();
}

CIMGUI_API void ig_SameLine(int column_x, int spacing_w)
{
	ImGui::SameLine(column_x,spacing_w);
}

CIMGUI_API void ImGuiIO_AddInputCharacter(unsigned short c)
{
	ImGui::GetIO().AddInputCharacter(c);
}
