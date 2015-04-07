
#include <stdarg.h>
#include <stdio.h>

#include "../imgui/imgui.h"

#if defined _WIN32 || defined __CYGWIN__
#define API __declspec(dllexport)
#else
#define API
#endif

extern "C" API ImGuiIO* ImGui_GetIO()
{
	return &ImGui::GetIO();
}

extern "C" API void ImGui_Shutdown()
{
	ImGui::Shutdown();
}

extern "C" API void ImGui_NewFrame()
{
	ImGui::NewFrame();
}

extern "C" API void ImGui_Render()
{
	ImGui::Render();
}

extern "C" API void ImGui_ShowTestWindow(bool* opened)
{
	ImGui::ShowTestWindow(opened);
}

extern "C" API bool ImGui_Begin(const char* name, bool* p_opened, ImGuiWindowFlags flags)
{
	return ImGui::Begin(name, p_opened, flags);
}

extern "C" API void ImGui_End()
{
	ImGui::End();
}

extern "C" API void ImGui_Text(const char* text, ...)
{
	char buffer[256];
  	va_list args;
  	va_start (args, text);
  	vsprintf (buffer, text, args);
  	va_end (args);

	ImGui::Text(buffer);
}

extern "C" API bool ImGui_ColorEdit3(const char* label, float col[3])
{
	return ImGui::ColorEdit3(label,col);
}

extern "C" API void ImGui_SetNextWindowPos(const ImVec2 pos, ImGuiSetCond cond)
{
	ImGui::SetNextWindowPos(pos,cond);
}

extern "C" API void ImGui_SetNextWindowSize(const ImVec2 size, ImGuiSetCond cond)
{
	ImGui::SetNextWindowSize(size, cond);
}

extern "C" API void ImGui_SliderFloat(const char* label, float* v, float v_min, float v_max, const char* display_format, float power)
{
	ImGui::SliderFloat(label,v,v_min,v_max,display_format,power);
}

extern "C" API bool ImGui_Button(const char* label, const ImVec2& size, bool repeat_when_held)
{
	return ImGui::Button(label,size,repeat_when_held);
}

extern "C" API bool ImGui_SmallButton(const char* label)
{
	return ImGui::SmallButton(label);
}

extern "C" API bool ImGui_TreeNode(const char* str_label_id)
{
	return ImGui::TreeNode(str_label_id);
}

extern "C" API bool ImGui_TreeNode_IdFmt(const void* ptr_id, const char* fmt, ...)
{
	char buffer[256];
  	va_list args;
  	va_start (args, fmt);
  	vsprintf (buffer, fmt, args);
  	va_end (args);

  	//TODO: use TreeNodeV
	return ImGui::TreeNode(ptr_id,"%s",buffer);	
}

extern "C" API void ImGui_TreePop()
{
	ImGui::TreePop();
}

extern "C" API void ImGui_SameLine(int column_x, int spacing_w)
{
	ImGui::SameLine(column_x,spacing_w);
}

extern "C" API void ImFontAtlas_GetTexDataAsRGBA32(ImFontAtlas* atlas, unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel)
{
	atlas->GetTexDataAsRGBA32(out_pixels,out_width,out_height,out_bytes_per_pixel);
}

extern "C" API void ImFontAtlas_SetTexID(ImFontAtlas* atlas, void* tex)
{
	atlas->TexID = tex;
}

extern "C" API int ImDrawList_GetVertexBufferSize(ImDrawList* list)
{
	return list->vtx_buffer.size();
}

extern "C" API ImDrawVert* ImDrawList_GetVertexPtr(ImDrawList* list, int n)
{
	return &list->vtx_buffer[n];
}

extern "C" API int ImDrawList_GetCmdSize(ImDrawList* list)
{
	return list->commands.size();
}

extern "C" API ImDrawCmd* ImDrawList_GetCmdPtr(ImDrawList* list, int n)
{
	return &list->commands[n];
}

extern "C" API void ImGuiIO_AddInputCharacter(unsigned short c)
{
	ImGui::GetIO().AddInputCharacter(c);
}
