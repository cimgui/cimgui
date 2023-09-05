#ifndef CIMGUI_BONFIRE_INCLUDED
#define CIMGUI_BONFIRE_INCLUDED

# include "cimgui.h"

CIMGUI_API bool igButtonXY(const char* label,float x, float y);
CIMGUI_API bool igBeginTableXY(const char* str_id,int column,ImGuiTableFlags flags,float outer_size_x, float outer_size_y,float inner_width);
CIMGUI_API void igSetNextWindowPosXY(float posX, float posY, ImGuiCond cond, float pivotX, float pivotY);
CIMGUI_API void igSetNextWindowSizeXY(float sizeX, float sizeY,ImGuiCond cond);
CIMGUI_API void igSetNextWindowContentSizeXY(float sizeX, float sizeY);
CIMGUI_API void igTextColoredRGBA(float r, float g, float b, float a,const char* fmt,...);

#endif