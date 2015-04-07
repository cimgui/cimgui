
#include "../imgui/imgui.h"

#define API __declspec(dllexport)

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

extern "C" API void ImGui_Text(const char* text)
{
	ImGui::Text(text);
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

