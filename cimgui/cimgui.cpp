
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
