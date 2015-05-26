
#include "../imgui/imgui.h"
#include "cimgui.h"

CIMGUI_API void ImFontAtlas_GetTexDataAsRGBA32(ImFontAtlas* atlas, unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel)
{
	atlas->GetTexDataAsRGBA32(out_pixels, out_width, out_height, out_bytes_per_pixel);
}

CIMGUI_API void ImFontAtlas_GetTexDataAsAlpha8(ImFontAtlas* atlas, unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel)
{
	atlas->GetTexDataAsAlpha8(out_pixels, out_width, out_height, out_bytes_per_pixel);
}

CIMGUI_API void ImFontAtlas_SetTexID(ImFontAtlas* atlas, void* tex)
{
	atlas->TexID = tex;
}

CIMGUI_API ImFont* ImFontAtlas_AddFontDefault(ImFontAtlas* atlas)
{
	return atlas->AddFontDefault();
}

CIMGUI_API ImFont* ImFontAtlas_AddFontFromFileTTF(ImFontAtlas* atlas,CONST char* filename, float size_pixels, CONST ImWchar* glyph_ranges, int font_no)
{
	return atlas->AddFontFromFileTTF(filename, size_pixels, glyph_ranges, font_no);
}

CIMGUI_API ImFont* ImFontAtlas_AddFontFromMemoryTTF(ImFontAtlas* atlas, void* ttf_data, int ttf_size, float size_pixels, CONST ImWchar* glyph_ranges, int font_no)
{
	return atlas->AddFontFromMemoryTTF(ttf_data, ttf_size, size_pixels, glyph_ranges, font_no);
}

CIMGUI_API ImFont* ImFontAtlas_AddFontFromMemoryCompressedTTF(ImFontAtlas* atlas, CONST void* compressed_ttf_data, int compressed_ttf_size, float size_pixels, CONST ImWchar* glyph_ranges, int font_no)
{
	return atlas->AddFontFromMemoryCompressedTTF(compressed_ttf_data, compressed_ttf_size, size_pixels, glyph_ranges, font_no);	
}

CIMGUI_API void ImFontAtlas_ClearTexData(ImFontAtlas* atlas)
{
	return atlas->ClearTexData();
}

CIMGUI_API void ImFontAtlas_Clear(ImFontAtlas* atlas)
{
	return atlas->Clear();
}