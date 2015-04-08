
#include "../imgui/imgui.h"
#include "cimgui.h"

EXTERN API int ImDrawList_GetVertexBufferSize(ImDrawList* list)
{
	return list->vtx_buffer.size();
}

EXTERN API ImDrawVert* ImDrawList_GetVertexPtr(ImDrawList* list, int n)
{
	return &list->vtx_buffer[n];
}

EXTERN API int ImDrawList_GetCmdSize(ImDrawList* list)
{
	return list->commands.size();
}

EXTERN API ImDrawCmd* ImDrawList_GetCmdPtr(ImDrawList* list, int n)
{
	return &list->commands[n];
}