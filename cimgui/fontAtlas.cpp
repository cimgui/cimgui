
#include "../imgui/imgui.h"
#include "cimgui.h"

CIMGUI_API void ImFontConfig_DefaultConstructor(ImFontConfig* config)
{
	*config = ImFontConfig();
}

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

CIMGUI_API ImFont* ImFontAtlas_AddFont(ImFontAtlas* atlas, CONST ImFontConfig* font_cfg)
{
	return atlas->AddFont(font_cfg);
}

CIMGUI_API ImFont* ImFontAtlas_AddFontDefault(ImFontAtlas* atlas, CONST ImFontConfig* font_cfg)
{
	return atlas->AddFontDefault(font_cfg);
}

CIMGUI_API ImFont* ImFontAtlas_AddFontFromFileTTF(ImFontAtlas* atlas,CONST char* filename, float size_pixels, CONST ImFontConfig* font_cfg, CONST ImWchar* glyph_ranges)
{
	return atlas->AddFontFromFileTTF(filename, size_pixels, font_cfg, glyph_ranges);
}

CIMGUI_API ImFont* ImFontAtlas_AddFontFromMemoryTTF(ImFontAtlas* atlas, void* ttf_data, int ttf_size, float size_pixels, CONST ImFontConfig* font_cfg, CONST ImWchar* glyph_ranges)
{
	return atlas->AddFontFromMemoryTTF(ttf_data, ttf_size, size_pixels, font_cfg, glyph_ranges);
}

CIMGUI_API ImFont* ImFontAtlas_AddFontFromMemoryCompressedTTF(ImFontAtlas* atlas, CONST void* compressed_ttf_data, int compressed_ttf_size, float size_pixels, CONST ImFontConfig* font_cfg, CONST ImWchar* glyph_ranges)
{
	return atlas->AddFontFromMemoryCompressedTTF(compressed_ttf_data, compressed_ttf_size, size_pixels, font_cfg, glyph_ranges);
}

CIMGUI_API ImFont* ImFontAtlas_AddFontFromMemoryCompressedBase85TTF(ImFontAtlas* atlas, CONST char* compressed_ttf_data_base85, float size_pixels, CONST ImFontConfig* font_cfg, CONST ImWchar* glyph_ranges)
{
	return atlas->AddFontFromMemoryCompressedBase85TTF(compressed_ttf_data_base85, size_pixels, font_cfg, glyph_ranges);
}

CIMGUI_API void ImFontAtlas_ClearTexData(ImFontAtlas* atlas)
{
	return atlas->ClearTexData();
}

CIMGUI_API void ImFontAtlas_Clear(ImFontAtlas* atlas)
{
	return atlas->Clear();
}

CIMGUI_API CONST ImWchar* ImFontAtlas_GetGlyphRangesDefault(struct ImFontAtlas* atlas)
{
	return atlas->GetGlyphRangesDefault();
}

CIMGUI_API CONST ImWchar*   ImFontAtlas_GetGlyphRangesKorean(struct ImFontAtlas* atlas)
{
	return atlas->GetGlyphRangesKorean();
}

CIMGUI_API CONST ImWchar*   ImFontAtlas_GetGlyphRangesJapanese(struct ImFontAtlas* atlas)
{
	return atlas->GetGlyphRangesJapanese();
}

CIMGUI_API CONST ImWchar*   ImFontAtlas_GetGlyphRangesChinese(struct ImFontAtlas* atlas)
{
	return atlas->GetGlyphRangesChinese();
}

CIMGUI_API CONST ImWchar*   ImFontAtlas_GetGlyphRangesCyrillic(struct ImFontAtlas* atlas)
{
	return atlas->GetGlyphRangesCyrillic();
}