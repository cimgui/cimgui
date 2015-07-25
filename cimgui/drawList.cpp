
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

CIMGUI_API int              ImDrawList_GetIndexBufferSize(ImDrawList* list)
{
	return list->IdxBuffer.size();
}

CIMGUI_API ImDrawIdx*       ImDrawList_GetIndexPtr(ImDrawList* list, int n)
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