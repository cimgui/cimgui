
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

CIMGUI_API void ImFontAtlas_SetTexID(ImFontAtlas* atlas, ImTextureID id)
{
    atlas->TexID = id;
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

CIMGUI_API ImFont* ImFontAtlas_AddFontFromMemoryTTF(ImFontAtlas* atlas, void* font_data, int font_size, float size_pixels, CONST ImFontConfig* font_cfg, CONST ImWchar* glyph_ranges)
{
    return atlas->AddFontFromMemoryTTF(font_data, font_size, size_pixels, font_cfg, glyph_ranges);
}

CIMGUI_API ImFont* ImFontAtlas_AddFontFromMemoryCompressedTTF(ImFontAtlas* atlas, CONST void* compressed_font_data, int compressed_font_size, float size_pixels, CONST ImFontConfig* font_cfg, CONST ImWchar* glyph_ranges)
{
    return atlas->AddFontFromMemoryCompressedTTF(compressed_font_data, compressed_font_size, size_pixels, font_cfg, glyph_ranges);
}

CIMGUI_API ImFont* ImFontAtlas_AddFontFromMemoryCompressedBase85TTF(ImFontAtlas* atlas, CONST char* compressed_font_data_base85, float size_pixels, CONST ImFontConfig* font_cfg, CONST ImWchar* glyph_ranges)
{
    return atlas->AddFontFromMemoryCompressedBase85TTF(compressed_font_data_base85, size_pixels, font_cfg, glyph_ranges);
}

CIMGUI_API void ImFontAtlas_ClearTexData(ImFontAtlas* atlas)
{
    return atlas->ClearTexData();
}

CIMGUI_API void ImFontAtlas_ClearInputData(ImFontAtlas* atlas)
{
    return atlas->ClearInputData();
}

CIMGUI_API void ImFontAtlas_ClearFonts(ImFontAtlas* atlas)
{
    return atlas->ClearFonts();
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

CIMGUI_API CONST ImWchar*   ImFontAtlas_GetGlyphRangesThai(struct ImFontAtlas* atlas)
{
    return atlas->GetGlyphRangesThai();
}

CIMGUI_API ImTextureID ImFontAtlas_GetTexID(struct ImFontAtlas* atlas)
{
    return atlas->TexID;
}

CIMGUI_API unsigned char* ImFontAtlas_GetTexPixelsAlpha8(struct ImFontAtlas* atlas)
{
    return atlas->TexPixelsAlpha8;
}

CIMGUI_API unsigned int* ImFontAtlas_GetTexPixelsRGBA32(struct ImFontAtlas* atlas)
{
    return atlas->TexPixelsRGBA32;
}

CIMGUI_API int ImFontAtlas_GetTexWidth(struct ImFontAtlas* atlas)
{
    return atlas->TexWidth;
}

CIMGUI_API int ImFontAtlas_GetTexHeight(struct ImFontAtlas* atlas)
{
    return atlas->TexHeight;
}

CIMGUI_API int ImFontAtlas_GetTexDesiredWidth(struct ImFontAtlas* atlas)
{
    return atlas->TexDesiredWidth;
}

CIMGUI_API void ImFontAtlas_SetTexDesiredWidth(struct ImFontAtlas* atlas, int TexDesiredWidth_)
{
    atlas->TexDesiredWidth = TexDesiredWidth_;
}

CIMGUI_API int ImFontAtlas_GetTexGlyphPadding(struct ImFontAtlas* atlas)
{
    return atlas->TexGlyphPadding;
}

CIMGUI_API void ImFontAtlas_SetTexGlyphPadding(struct ImFontAtlas* atlas, int TexGlyphPadding_)
{
    atlas->TexGlyphPadding = TexGlyphPadding_;
}

CIMGUI_API void ImFontAtlas_GetTexUvWhitePixel(struct ImFontAtlas* atlas, ImVec2* pOut)
{
    *pOut = atlas->TexUvWhitePixel;
}

// ImFontAtlas::Fonts;
CIMGUI_API int ImFontAtlas_Fonts_size(struct ImFontAtlas* atlas)
{
    return atlas->Fonts.size();
}

CIMGUI_API ImFont* ImFontAtlas_Fonts_index(struct ImFontAtlas* atlas, int index)
{
    return atlas->Fonts[index];
}

// ImFont
CIMGUI_API float ImFont_GetFontSize(const struct ImFont* font)
{
    return font->FontSize;
}

CIMGUI_API void ImFont_SetFontSize(struct ImFont* font, float FontSize_)
{
    font->FontSize = FontSize_;
}

CIMGUI_API float ImFont_GetScale(const struct ImFont* font)
{
    return font->Scale;
}

CIMGUI_API void ImFont_SetScale(struct ImFont* font, float Scale_)
{
    font->Scale = Scale_;
}

CIMGUI_API void ImFont_GetDisplayOffset(const struct ImFont* font, ImVec2* pOut)
{
    *pOut = font->DisplayOffset;
}

CIMGUI_API const struct ImFont::Glyph* ImFont_GetFallbackGlyph(const struct ImFont* font)
{
    return font->FallbackGlyph;
}

CIMGUI_API void ImFont_SetFallbackGlyph(struct ImFont* font, const struct ImFont::Glyph* FallbackGlyph_)
{
    font->FallbackGlyph = FallbackGlyph_;
}

CIMGUI_API float ImFont_GetFallbackXAdvance(const struct ImFont* font)
{
    return font->FallbackXAdvance;
}

CIMGUI_API ImWchar ImFont_GetFallbackChar(const struct ImFont* font)
{
    return font->FallbackChar;
}

CIMGUI_API short ImFont_GetConfigDataCount(const struct ImFont* font)
{
    return font->ConfigDataCount;
}

CIMGUI_API struct ImFontConfig* ImFont_GetConfigData(struct ImFont* font)
{
    return font->ConfigData;
}

CIMGUI_API struct ImFontAtlas* ImFont_GetContainerAtlas(struct ImFont* font)
{
    return font->ContainerAtlas;
}

CIMGUI_API float ImFont_GetAscent(const struct ImFont* font)
{
    return font->Ascent;
}

CIMGUI_API float ImFont_GetDescent(const struct ImFont* font)
{
    return font->Descent;
}

CIMGUI_API int ImFont_GetMetricsTotalSurface(const struct ImFont* font)
{
    return font->MetricsTotalSurface;
}

CIMGUI_API void ImFont_Clear(struct ImFont* font)
{
    font->Clear();
}

CIMGUI_API void ImFont_BuildLookupTable(struct ImFont* font)
{
    font->BuildLookupTable();
}

CIMGUI_API const struct ImFont::Glyph* ImFont_FindGlyph(const struct ImFont* font, ImWchar c)
{
    return font->FindGlyph(c);
}

CIMGUI_API void ImFont_SetFallbackChar(struct ImFont* font, ImWchar c)
{
    font->SetFallbackChar(c);
}

CIMGUI_API float ImFont_GetCharAdvance(const struct ImFont* font, ImWchar c)
{
    return font->GetCharAdvance(c);
}

CIMGUI_API bool ImFont_IsLoaded(const struct ImFont* font)
{
    return font->IsLoaded();
}

CIMGUI_API void ImFont_CalcTextSizeA(const struct ImFont* font, ImVec2* pOut, float size, float max_width, float wrap_width, const char* text_begin, const char* text_end, const char** remaining)
{
    *pOut = font->CalcTextSizeA(size, max_width, wrap_width, text_begin, text_end, remaining);
}

CIMGUI_API const char* ImFont_CalcWordWrapPositionA(const struct ImFont* font, float scale, const char* text, const char* text_end, float wrap_width)
{
    return font->CalcWordWrapPositionA(scale, text, text_end, wrap_width);
}

CIMGUI_API void ImFont_RenderChar(const struct ImFont* font, ImDrawList* draw_list, float size, ImVec2 pos, ImU32 col, unsigned short c)
{
    return font->RenderChar(draw_list, size, pos, col, c);
}

CIMGUI_API void ImFont_RenderText(const struct ImFont* font, ImDrawList* draw_list, float size, ImVec2 pos, ImU32 col, const ImVec4* clip_rect, const char* text_begin, const char* text_end, float wrap_width, bool cpu_fine_clip)
{
    return font->RenderText(draw_list, size, pos, col, *clip_rect, text_begin, text_end, wrap_width, cpu_fine_clip);
}

// ImFont::Glyph
CIMGUI_API int ImFont_Glyphs_size(const struct ImFont* font)
{
    return font->Glyphs.size();
}

CIMGUI_API struct ImFont::Glyph* ImFont_Glyphs_index(struct ImFont* font, int index)
{
    return &font->Glyphs[index];
}

// ImFont::IndexXAdvance
CIMGUI_API int ImFont_IndexXAdvance_size(const struct ImFont* font)
{
    return font->IndexXAdvance.size();
}

CIMGUI_API float ImFont_IndexXAdvance_index(const struct ImFont* font, int index)
{
    return font->IndexXAdvance[index];
}

// ImFont::IndexLookup
CIMGUI_API int ImFont_IndexLookup_size(const struct ImFont* font)
{
    return font->IndexLookup.size();
}

CIMGUI_API unsigned short ImFont_IndexLookup_index(const struct ImFont* font, int index)
{
    return font->IndexLookup[index];
}
