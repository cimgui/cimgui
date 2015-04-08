
#include "../imgui/imgui.h"
#include "cimgui.h"

EXTERN API void ImFontAtlas_GetTexDataAsRGBA32(ImFontAtlas* atlas, unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel)
{
	atlas->GetTexDataAsRGBA32(out_pixels, out_width, out_height, out_bytes_per_pixel);
}

EXTERN API void ImFontAtlas_GetTexDataAsAlpha8(ImFontAtlas* atlas, unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel)
{
	atlas->GetTexDataAsAlpha8(out_pixels, out_width, out_height, out_bytes_per_pixel);
}

EXTERN API void ImFontAtlas_SetTexID(ImFontAtlas* atlas, void* tex)
{
	atlas->TexID = tex;
}