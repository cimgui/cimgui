
#include "../imgui/imgui.h"
#include "cimgui.h"

CIMGUI_API int ImDrawList_GetVertexBufferSize(ImDrawList* list)
{
	return list->VtxBuffer.size();
}

CIMGUI_API ImDrawVert* ImDrawList_GetVertexPtr(ImDrawList* list, int n)
{
	return &list->VtxBuffer[n];
}

CIMGUI_API int ImDrawList_GetIndexBufferSize(ImDrawList* list)
{
	return list->IdxBuffer.size();
}

CIMGUI_API ImDrawIdx* ImDrawList_GetIndexPtr(ImDrawList* list, int n)
{
	return &list->IdxBuffer[n];
}

CIMGUI_API int ImDrawList_GetCmdSize(ImDrawList* list)
{
	return list->CmdBuffer.size();
}

CIMGUI_API ImDrawCmd* ImDrawList_GetCmdPtr(ImDrawList* list, int n)
{
	return &list->CmdBuffer[n];
}

CIMGUI_API void ImDrawData_DeIndexAllBuffers(ImDrawData* drawData)
{
	return drawData->DeIndexAllBuffers();
}

CIMGUI_API void ImDrawData_ScaleClipRects(ImDrawData* drawData, struct ImVec2 sc)
{
	return drawData->ScaleClipRects(sc);
}

CIMGUI_API void ImDrawList_Clear(ImDrawList* list)
{
	return list->Clear();
}

CIMGUI_API void ImDrawList_ClearFreeMemory(ImDrawList* list)
{
	return list->ClearFreeMemory();
}

CIMGUI_API void ImDrawList_PushClipRect(ImDrawList* list, struct ImVec2 clip_rect_min, struct ImVec2 clip_rect_max, bool intersect_with_current_clip_rect)
{
	return list->PushClipRect(clip_rect_min,clip_rect_max,intersect_with_current_clip_rect);
}

CIMGUI_API void ImDrawList_PushClipRectFullScreen(ImDrawList* list)
{
	return list->PushClipRectFullScreen();
}

CIMGUI_API void ImDrawList_PopClipRect(ImDrawList* list)
{
	return list->PopClipRect();
}

CIMGUI_API void ImDrawList_PushTextureID(ImDrawList* list, CONST ImTextureID texture_id)
{
	return list->PushTextureID(texture_id);
}

CIMGUI_API void ImDrawList_PopTextureID(ImDrawList* list)
{
	return list->PopTextureID();
}

CIMGUI_API void ImDrawList_AddLine(ImDrawList* list, CONST struct ImVec2 a, CONST struct ImVec2 b, ImU32 col, float thickness)
{
	return list->AddLine(a, b, col, thickness);
}

CIMGUI_API void ImDrawList_AddRect(ImDrawList* list, CONST struct ImVec2 a, CONST struct ImVec2 b, ImU32 col, float rounding, int rounding_corners, float thickness)
{
	return list->AddRect(a, b, col, rounding, rounding_corners, thickness);
}

CIMGUI_API void ImDrawList_AddRectFilled(ImDrawList* list, CONST struct ImVec2 a, CONST struct ImVec2 b, ImU32 col, float rounding, int rounding_corners)
{
	return list->AddRectFilled(a, b, col, rounding, rounding_corners);
}

CIMGUI_API void ImDrawList_AddRectFilledMultiColor(ImDrawList* list, CONST struct ImVec2 a, CONST struct ImVec2 b, ImU32 col_upr_left, ImU32 col_upr_right, ImU32 col_bot_right, ImU32 col_bot_left)
{
	return list->AddRectFilledMultiColor(a, b, col_upr_left, col_upr_right, col_bot_right, col_bot_left);
}

CIMGUI_API void ImDrawList_AddQuad(ImDrawList* list, CONST struct ImVec2 a, CONST struct ImVec2 b, CONST struct ImVec2 c, CONST struct ImVec2 d, ImU32 col, float thickness)
{
	return list->AddQuad(a, b, c, d, col, thickness);
}

CIMGUI_API void ImDrawList_AddQuadFilled(ImDrawList* list, CONST struct ImVec2 a, CONST struct ImVec2 b, CONST struct ImVec2 c, CONST struct ImVec2 d, ImU32 col)
{
	return list->AddQuadFilled(a, b, c, d, col);
}

CIMGUI_API void ImDrawList_AddTriangle(ImDrawList* list, CONST struct ImVec2 a, CONST struct ImVec2 b, CONST struct ImVec2 c, ImU32 col, float thickness)
{
	return list->AddTriangle(a,b,c,col,thickness);
}

CIMGUI_API void ImDrawList_AddTriangleFilled(ImDrawList* list, CONST struct ImVec2 a, CONST struct ImVec2 b, CONST struct ImVec2 c, ImU32 col)
{
	return list->AddTriangleFilled(a, b, c, col);
}

CIMGUI_API void ImDrawList_AddCircle(ImDrawList* list, CONST struct ImVec2 centre, float radius, ImU32 col, int num_segments, float thickness)
{
	return list->AddCircle(centre, radius, col, num_segments, thickness);
}

CIMGUI_API void ImDrawList_AddCircleFilled(ImDrawList* list, CONST struct ImVec2 centre, float radius, ImU32 col, int num_segments)
{
	return list->AddCircleFilled(centre, radius, col, num_segments);
}

CIMGUI_API void ImDrawList_AddText(ImDrawList* list, CONST struct ImVec2 pos, ImU32 col, CONST char* text_begin, CONST char* text_end)
{
	return list->AddText(pos, col, text_begin, text_end);
}

CIMGUI_API void ImDrawList_AddTextExt(ImDrawList* list, CONST ImFont* font, float font_size, CONST struct ImVec2 pos, ImU32 col, CONST char* text_begin, CONST char* text_end, float wrap_width, CONST ImVec4* cpu_fine_clip_rect)
{
	return list->AddText(font, font_size, pos, col, text_begin, text_end, wrap_width, cpu_fine_clip_rect);
}

CIMGUI_API void ImDrawList_AddImage(ImDrawList* list, ImTextureID user_texture_id, CONST struct ImVec2 a, CONST struct ImVec2 b, CONST struct ImVec2 uv0, CONST struct ImVec2 uv1, ImU32 col)
{
	return list->AddImage(user_texture_id, a, b, uv0, uv1, col);
}

CIMGUI_API void ImDrawList_AddPolyline(ImDrawList* list, CONST ImVec2* points, CONST int num_points, ImU32 col, bool closed, float thickness, bool anti_aliased)
{
	return list->AddPolyline(points, num_points, col, closed, thickness, anti_aliased);
}

CIMGUI_API void ImDrawList_AddConvexPolyFilled(ImDrawList* list, CONST ImVec2* points, CONST int num_points, ImU32 col, bool anti_aliased)
{
	return list->AddConvexPolyFilled(points, num_points, col, anti_aliased);
}

CIMGUI_API void ImDrawList_AddBezierCurve(ImDrawList* list, CONST struct ImVec2 pos0, CONST struct ImVec2 cp0, CONST struct ImVec2 cp1, CONST struct ImVec2 pos1, ImU32 col, float thickness, int num_segments)
{
	return list->AddBezierCurve(pos0, cp0, cp1, pos1, col, thickness, num_segments);
}

CIMGUI_API void ImDrawList_PathClear(ImDrawList* list)
{
	return list->PathClear();
}

CIMGUI_API void ImDrawList_PathLineTo(ImDrawList* list, CONST struct ImVec2 pos)
{
	return list->PathLineTo(pos);
}

CIMGUI_API void ImDrawList_PathLineToMergeDuplicate(ImDrawList* list, CONST struct ImVec2 pos)
{
	return list->PathLineToMergeDuplicate(pos);
}

CIMGUI_API void ImDrawList_PathFill(ImDrawList* list, ImU32 col)
{
	return list->PathFill(col);
}

CIMGUI_API void ImDrawList_PathStroke(ImDrawList* list, ImU32 col, bool closed, float thickness)
{
	return list->PathStroke(col, closed, thickness);
}

CIMGUI_API void ImDrawList_PathArcTo(ImDrawList* list, CONST struct ImVec2 centre, float radius, float a_min, float a_max, int num_segments)
{
	return list->PathArcTo(centre, radius, a_min, a_max, num_segments);
}

CIMGUI_API void ImDrawList_PathArcToFast(ImDrawList* list, CONST struct ImVec2 centre, float radius, int a_min_of_12, int a_max_of_12)
{
	return list->PathArcToFast(centre, radius, a_min_of_12, a_max_of_12);
}

CIMGUI_API void ImDrawList_PathBezierCurveTo(ImDrawList* list, CONST struct ImVec2 p1, CONST struct ImVec2 p2, CONST struct ImVec2 p3, int num_segments)
{
	return list->PathBezierCurveTo(p1, p2, p3, num_segments);
}

CIMGUI_API void ImDrawList_PathRect(ImDrawList* list, CONST struct ImVec2 rect_min, CONST struct ImVec2 rect_max, float rounding, int rounding_corners)
{
	return list->PathRect(rect_min, rect_max, rounding, rounding_corners);
}

CIMGUI_API void ImDrawList_ChannelsSplit(ImDrawList* list, int channels_count)
{
	return list->ChannelsSplit(channels_count);
}

CIMGUI_API void ImDrawList_ChannelsMerge(ImDrawList* list)
{
	return list->ChannelsMerge();
}

CIMGUI_API void ImDrawList_ChannelsSetCurrent(ImDrawList* list, int channel_index)
{
	return list->ChannelsSetCurrent(channel_index);
}

CIMGUI_API void ImDrawList_AddCallback(ImDrawList* list, ImDrawCallback callback, void* callback_data)
{
	return list->AddCallback(callback, callback_data);
}

CIMGUI_API void ImDrawList_AddDrawCmd(ImDrawList* list)
{
	return list->AddDrawCmd();
}

CIMGUI_API void ImDrawList_PrimReserve(ImDrawList* list, int idx_count, int vtx_count)
{
	return list->PrimReserve(idx_count, vtx_count);
}

CIMGUI_API void ImDrawList_PrimRect(ImDrawList* list, CONST struct ImVec2 a, CONST struct ImVec2 b, ImU32 col)
{
	return list->PrimRect(a, b, col);
}

CIMGUI_API void ImDrawList_PrimRectUV(ImDrawList* list, CONST struct ImVec2 a, CONST struct ImVec2 b, CONST struct ImVec2 uv_a, CONST struct ImVec2 uv_b, ImU32 col)
{
	return list->PrimRectUV(a, b, uv_a, uv_b, col);
}

CIMGUI_API void ImDrawList_PrimQuadUV(ImDrawList* list,CONST struct ImVec2 a, CONST struct ImVec2 b, CONST struct ImVec2 c, CONST struct ImVec2 d, CONST struct ImVec2 uv_a, CONST struct ImVec2 uv_b, CONST struct ImVec2 uv_c, CONST struct ImVec2 uv_d, ImU32 col)
{
	return list->PrimQuadUV(a,b,c,d,uv_a,uv_b,uv_c,uv_d,col);
}

CIMGUI_API void ImDrawList_PrimVtx(ImDrawList* list, CONST struct ImVec2 pos, CONST struct ImVec2 uv, ImU32 col)
{
	return list->PrimVtx(pos, uv, col);
}

CIMGUI_API void ImDrawList_PrimWriteVtx(ImDrawList* list, CONST struct ImVec2 pos, CONST struct ImVec2 uv, ImU32 col)
{
	return list->PrimWriteVtx(pos, uv, col);
}

CIMGUI_API void ImDrawList_PrimWriteIdx(ImDrawList* list, ImDrawIdx idx)
{
	return list->PrimWriteIdx(idx);
}

CIMGUI_API void ImDrawList_UpdateClipRect(ImDrawList* list)
{
	return list->UpdateClipRect();
}

CIMGUI_API void ImDrawList_UpdateTextureID(ImDrawList* list)
{
	return list->UpdateTextureID();
}
