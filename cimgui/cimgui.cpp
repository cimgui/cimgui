
#include "../imgui/imgui.h"
#include "cimgui.h"

// to use placement new
#define IMGUI_DEFINE_PLACEMENT_NEW
#include "../imgui/imgui_internal.h"

CIMGUI_API ImGuiIO *igGetIO()
{
    return &ImGui::GetIO();
}

CIMGUI_API ImGuiStyle *igGetStyle()
{
    return &ImGui::GetStyle();
}

CIMGUI_API ImDrawData *igGetDrawData()
{
    return ImGui::GetDrawData();
}

CIMGUI_API void igNewFrame()
{
    ImGui::NewFrame();
}

CIMGUI_API void igRender()
{
    ImGui::Render();
}

CIMGUI_API void igEndFrame()
{
    ImGui::EndFrame();
}

CIMGUI_API void igShutdown()
{
    ImGui::Shutdown();
}

CIMGUI_API void igShowUserGuide()
{
    ImGui::ShowUserGuide();
}

CIMGUI_API void igShowStyleEditor(ImGuiStyle *ref)
{
    ImGui::ShowStyleEditor(ref);
}

CIMGUI_API void igShowDemoWindow(bool *opened)
{
    ImGui::ShowDemoWindow(opened);
}

IMGUI_API void igShowMetricsWindow(bool *opened)
{
    ImGui::ShowMetricsWindow(opened);
}

CIMGUI_API void igShowStyleSelector(CONST char *label)
{
    ImGui::ShowStyleSelector(label);
}

CIMGUI_API void igShowFontSelector(CONST char *label)
{
    ImGui::ShowFontSelector(label);
}

// Window

CIMGUI_API bool igBegin(CONST char *name, bool *p_opened, ImGuiWindowFlags flags)
{
    return ImGui::Begin(name, p_opened, flags);
}

CIMGUI_API bool igBegin2(CONST char *name, bool *p_opened, CONST ImVec2 size_on_first_use, float bg_alpha, ImGuiWindowFlags flags)
{
    return ImGui::Begin(name, p_opened, size_on_first_use, bg_alpha, flags);
}

CIMGUI_API void igEnd()
{
    ImGui::End();
}

CIMGUI_API bool igBeginChild(CONST char *str_id, CONST ImVec2 size, bool border, ImGuiWindowFlags extra_flags)
{
    return ImGui::BeginChild(str_id, size, border, extra_flags);
}

CIMGUI_API bool igBeginChildEx(ImGuiID id, CONST ImVec2 size, bool border, ImGuiWindowFlags extra_flags)
{
    return ImGui::BeginChild(id, size, border, extra_flags);
}

CIMGUI_API void igEndChild()
{
    ImGui::EndChild();
}

CIMGUI_API void igGetContentRegionMax(ImVec2 *out)
{
    *out = ImGui::GetContentRegionMax();
}

CIMGUI_API void igGetContentRegionAvail(struct ImVec2 *out)
{
    *out = ImGui::GetContentRegionAvail();
}

CIMGUI_API float igGetContentRegionAvailWidth()
{
    return ImGui::GetContentRegionAvailWidth();
}

CIMGUI_API void igGetWindowContentRegionMin(ImVec2 *out)
{
    *out = ImGui::GetWindowContentRegionMin();
}

CIMGUI_API void igGetWindowContentRegionMax(ImVec2 *out)
{
    *out = ImGui::GetWindowContentRegionMax();
}

CIMGUI_API float igGetWindowContentRegionWidth()
{
    return ImGui::GetWindowContentRegionWidth();
}

CIMGUI_API ImDrawList *igGetWindowDrawList()
{
    return ImGui::GetWindowDrawList();
}

CIMGUI_API void igGetWindowPos(ImVec2 *out)
{
    *out = ImGui::GetWindowPos();
}

CIMGUI_API void igGetWindowSize(ImVec2 *out)
{
    *out = ImGui::GetWindowSize();
}

CIMGUI_API float igGetWindowWidth()
{
    return ImGui::GetWindowWidth();
}

CIMGUI_API float igGetWindowHeight()
{
    return ImGui::GetWindowHeight();
}

CIMGUI_API bool igIsWindowCollapsed()
{
    return ImGui::IsWindowCollapsed();
}

CIMGUI_API bool igIsWindowAppearing()
{
    return ImGui::IsWindowAppearing();
}

CIMGUI_API void igSetWindowFontScale(float scale)
{
    ImGui::SetWindowFontScale(scale);
}

CIMGUI_API void igSetNextWindowPos(CONST struct ImVec2 pos, ImGuiCond cond, CONST struct ImVec2 pivot)
{
    ImGui::SetNextWindowPos(pos, cond, pivot);
}

CIMGUI_API void igSetNextWindowSize(CONST ImVec2 size, ImGuiCond cond)
{
    ImGui::SetNextWindowSize(size, cond);
}

CIMGUI_API void igSetNextWindowSizeConstraints(CONST struct ImVec2 size_min, CONST struct ImVec2 size_max, ImGuiSizeConstraintCallback custom_callback, void *custom_callback_data)
{
    ImGui::SetNextWindowSizeConstraints(size_min, size_max, custom_callback, custom_callback_data);
}

CIMGUI_API void igSetNextWindowContentSize(CONST ImVec2 size)
{
    ImGui::SetNextWindowContentSize(size);
}

CIMGUI_API void igSetNextWindowCollapsed(bool collapsed, ImGuiCond cond)
{
    ImGui::SetNextWindowCollapsed(collapsed, cond);
}

CIMGUI_API void igSetNextWindowFocus()
{
    ImGui::SetNextWindowFocus();
}

CIMGUI_API void igSetWindowPos(CONST ImVec2 pos, ImGuiCond cond)
{
    ImGui::SetWindowPos(pos, cond);
}

CIMGUI_API void igSetWindowSize(CONST ImVec2 size, ImGuiCond cond)
{
    ImGui::SetWindowSize(size, cond);
}

CIMGUI_API void igSetWindowCollapsed(bool collapsed, ImGuiCond cond)
{
    ImGui::SetWindowCollapsed(collapsed, cond);
}

CIMGUI_API void igSetWindowFocus()
{
    ImGui::SetWindowFocus();
}

CIMGUI_API void igSetWindowPosByName(CONST char *name, CONST ImVec2 pos, ImGuiCond cond)
{
    ImGui::SetWindowPos(name, pos, cond);
}

CIMGUI_API void igSetWindowSize2(CONST char *name, CONST ImVec2 size, ImGuiCond cond)
{
    ImGui::SetWindowSize(name, size, cond);
}

CIMGUI_API void igSetWindowCollapsed2(CONST char *name, bool collapsed, ImGuiCond cond)
{
    ImGui::SetWindowCollapsed(name, collapsed, cond);
}

CIMGUI_API void igSetWindowFocus2(CONST char *name)
{
    ImGui::SetWindowFocus(name);
}

CIMGUI_API float igGetScrollX()
{
    return ImGui::GetScrollX();
}

CIMGUI_API float igGetScrollY()
{
    return ImGui::GetScrollY();
}

CIMGUI_API float igGetScrollMaxX()
{
    return ImGui::GetScrollMaxX();
}

CIMGUI_API float igGetScrollMaxY()
{
    return ImGui::GetScrollMaxY();
}

CIMGUI_API void igSetScrollX(float scroll_x)
{
    return ImGui::SetScrollX(scroll_x);
}

CIMGUI_API void igSetScrollY(float scroll_y)
{
    return ImGui::SetScrollY(scroll_y);
}

CIMGUI_API void igSetScrollHere(float center_y_ratio)
{
    ImGui::SetScrollHere(center_y_ratio);
}

CIMGUI_API void igSetScrollFromPosY(float pos_y, float center_y_ratio)
{
    return ImGui::SetScrollFromPosY(pos_y, center_y_ratio);
}

CIMGUI_API void igSetStateStorage(ImGuiStorage *tree)
{
    ImGui::SetStateStorage(tree);
}

CIMGUI_API ImGuiStorage *igGetStateStorage()
{
    return ImGui::GetStateStorage();
}

// Parameters stacks (shared)
CIMGUI_API void igPushFont(ImFont *font)
{
    ImGui::PushFont(font);
}

CIMGUI_API void igPopFont()
{
    return ImGui::PopFont();
}

CIMGUI_API void igPushStyleColorU32(ImGuiCol idx, ImU32 col)
{
    return ImGui::PushStyleColor(idx, col);
}

CIMGUI_API void igPushStyleColor(ImGuiCol idx, CONST ImVec4 col)
{
    return ImGui::PushStyleColor(idx, col);
}

CIMGUI_API void igPopStyleColor(int count)
{
    return ImGui::PopStyleColor(count);
}

CIMGUI_API void igPushStyleVar(ImGuiStyleVar idx, float val)
{
    return ImGui::PushStyleVar(idx, val);
}

CIMGUI_API void igPushStyleVarVec(ImGuiStyleVar idx, CONST ImVec2 val)
{
    return ImGui::PushStyleVar(idx, val);
}

CIMGUI_API void igPopStyleVar(int count)
{
    return ImGui::PopStyleVar(count);
}

CIMGUI_API void igGetStyleColorVec4(ImVec4 *pOut, ImGuiCol idx)
{
    *pOut = ImGui::GetStyleColorVec4(idx);
}

CIMGUI_API ImFont *igGetFont()
{
    return ImGui::GetFont();
}

CIMGUI_API float igGetFontSize()
{
    return ImGui::GetFontSize();
}

CIMGUI_API void igGetFontTexUvWhitePixel(ImVec2 *pOut)
{
    *pOut = ImGui::GetFontTexUvWhitePixel();
}

CIMGUI_API ImU32 igGetColorU32(ImGuiCol idx, float alpha_mul)
{
    return ImGui::GetColorU32(idx, alpha_mul);
}

CIMGUI_API ImU32 igGetColorU32Vec(CONST ImVec4 *col)
{
    return ImGui::GetColorU32(*col);
}

CIMGUI_API ImU32 igGetColorU32U32(ImU32 col)
{
    return ImGui::GetColorU32(col);
}

// Parameters stacks (current window)
CIMGUI_API void igPushItemWidth(float item_width)
{
    return ImGui::PushItemWidth(item_width);
}

CIMGUI_API void igPopItemWidth()
{
    return ImGui::PopItemWidth();
}

CIMGUI_API float igCalcItemWidth()
{
    return ImGui::CalcItemWidth();
}

CIMGUI_API void igPushAllowKeyboardFocus(bool v)
{
    return ImGui::PushAllowKeyboardFocus(v);
}

CIMGUI_API void igPopAllowKeyboardFocus()
{
    return ImGui::PopAllowKeyboardFocus();
}

CIMGUI_API void igPushTextWrapPos(float wrap_pos_x)
{
    return ImGui::PushTextWrapPos(wrap_pos_x);
}

CIMGUI_API void igPopTextWrapPos()
{
    return ImGui::PopTextWrapPos();
}

CIMGUI_API void igPushButtonRepeat(bool repeat)
{
    return ImGui::PushButtonRepeat(repeat);
}

CIMGUI_API void igPopButtonRepeat()
{
    return ImGui::PopButtonRepeat();
}

// Tooltip
CIMGUI_API void igSetTooltip(CONST char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    ImGui::SetTooltipV(fmt, args);
    va_end(args);
}

CIMGUI_API void igSetTooltipV(CONST char *fmt, va_list args)
{
    ImGui::SetTooltipV(fmt, args);
}

CIMGUI_API void igBeginTooltip()
{
    return ImGui::BeginTooltip();
}

CIMGUI_API void igEndTooltip()
{
    return ImGui::EndTooltip();
}

// Popup
CIMGUI_API void igOpenPopup(CONST char *str_id)
{
    return ImGui::OpenPopup(str_id);
}

CIMGUI_API bool igOpenPopupOnItemClick(const char *str_id, int mouse_button)
{
    return ImGui::OpenPopupOnItemClick(str_id, mouse_button);
}

CIMGUI_API bool igBeginPopup(CONST char *str_id)
{
    return ImGui::BeginPopup(str_id);
}

CIMGUI_API bool igBeginPopupModal(CONST char *name, bool *p_open, ImGuiWindowFlags extra_flags)
{
    return ImGui::BeginPopupModal(name, p_open, extra_flags);
}

CIMGUI_API bool igBeginPopupContextItem(CONST char *str_id, int mouse_button)
{
    return ImGui::BeginPopupContextItem(str_id, mouse_button);
}

CIMGUI_API bool igBeginPopupContextWindow(CONST char *str_id, int mouse_button, bool also_over_items)
{
    return ImGui::BeginPopupContextWindow(str_id, mouse_button, also_over_items);
}

CIMGUI_API bool igBeginPopupContextVoid(CONST char *str_id, int mouse_button)
{
    return ImGui::BeginPopupContextVoid(str_id, mouse_button);
}

CIMGUI_API void igEndPopup()
{
    return ImGui::EndPopup();
}

CIMGUI_API bool igIsPopupOpen(CONST char *str_id)
{
    return ImGui::IsPopupOpen(str_id);
}

CIMGUI_API void igCloseCurrentPopup()
{
    return ImGui::CloseCurrentPopup();
}

// Layout

CIMGUI_API void igSeparator()
{
    return ImGui::Separator();
}

CIMGUI_API void igSameLine(float pos_x, float spacing_w)
{
    return ImGui::SameLine(pos_x, spacing_w);
}

CIMGUI_API void igNewLine()
{
    return ImGui::NewLine();
}

CIMGUI_API void igSpacing()
{
    return ImGui::Spacing();
}

CIMGUI_API void igDummy(CONST ImVec2 *size)
{
    return ImGui::Dummy(*size);
}

CIMGUI_API void igIndent(float indent_w)
{
    return ImGui::Indent(indent_w);
}

CIMGUI_API void igUnindent(float indent_w)
{
    return ImGui::Unindent(indent_w);
}

CIMGUI_API void igBeginGroup()
{
    return ImGui::BeginGroup();
}

CIMGUI_API void igEndGroup()
{
    return ImGui::EndGroup();
}

CIMGUI_API void igGetCursorPos(ImVec2 *pOut)
{
    *pOut = ImGui::GetCursorPos();
}

CIMGUI_API float igGetCursorPosX()
{
    return ImGui::GetCursorPosX();
}

CIMGUI_API float igGetCursorPosY()
{
    return ImGui::GetCursorPosY();
}

CIMGUI_API void igSetCursorPos(CONST ImVec2 local_pos)
{
    return ImGui::SetCursorPos(local_pos);
}

CIMGUI_API void igSetCursorPosX(float x)
{
    return ImGui::SetCursorPosX(x);
}

CIMGUI_API void igSetCursorPosY(float y)
{
    return ImGui::SetCursorPosY(y);
}

CIMGUI_API void igGetCursorStartPos(ImVec2 *pOut)
{
    *pOut = ImGui::GetCursorStartPos();
}

CIMGUI_API void igGetCursorScreenPos(ImVec2 *pOut)
{
    *pOut = ImGui::GetCursorScreenPos();
}

CIMGUI_API void igSetCursorScreenPos(CONST ImVec2 pos)
{
    return ImGui::SetCursorScreenPos(pos);
}

CIMGUI_API void igAlignTextToFramePadding()
{
    return ImGui::AlignTextToFramePadding();
}

CIMGUI_API float igGetTextLineHeight()
{
    return ImGui::GetTextLineHeight();
}

CIMGUI_API float igGetTextLineHeightWithSpacing()
{
    return ImGui::GetTextLineHeightWithSpacing();
}

CIMGUI_API float igGetFrameHeight()
{
    return ImGui::GetFrameHeight();
}

CIMGUI_API float igGetFrameHeightWithSpacing()
{
    return ImGui::GetFrameHeightWithSpacing();
}

//Columns

CIMGUI_API void igColumns(int count, CONST char *id, bool border)
{
    return ImGui::Columns(count, id, border);
}

CIMGUI_API void igNextColumn()
{
    return ImGui::NextColumn();
}

CIMGUI_API int igGetColumnIndex()
{
    return ImGui::GetColumnIndex();
}

CIMGUI_API float igGetColumnWidth(int column_index)
{
    return ImGui::GetColumnWidth(column_index);
}

CIMGUI_API void igSetColumnWidth(int column_index, float width)
{
    return ImGui::SetColumnWidth(column_index, width);
}

CIMGUI_API float igGetColumnOffset(int column_index)
{
    return ImGui::GetColumnOffset(column_index);
}

CIMGUI_API void igSetColumnOffset(int column_index, float offset_x)
{
    return ImGui::SetColumnOffset(column_index, offset_x);
}

CIMGUI_API int igGetColumnsCount()
{
    return ImGui::GetColumnsCount();
}

// ID scopes
// If you are creating widgets in a loop you most likely want to push a unique identifier so ImGui can differentiate them
// You can also use "##extra" within your widget name to distinguish them from each others (see 'Programmer Guide')
CIMGUI_API void igPushIDStr(CONST char *str_id)
{
    return ImGui::PushID(str_id);
}

CIMGUI_API void igPushIDStrRange(CONST char *str_begin, CONST char *str_end)
{
    return ImGui::PushID(str_begin, str_end);
}

CIMGUI_API void igPushIDPtr(CONST void *ptr_id)
{
    return ImGui::PushID(ptr_id);
}

CIMGUI_API void igPushIDInt(int int_id)
{
    return ImGui::PushID(int_id);
}

CIMGUI_API void igPopID()
{
    return ImGui::PopID();
}

CIMGUI_API ImGuiID igGetIDStr(CONST char *str_id)
{
    return ImGui::GetID(str_id);
}

CIMGUI_API ImGuiID igGetIDStrRange(CONST char *str_begin, CONST char *str_end)
{
    return ImGui::GetID(str_begin, str_end);
}

CIMGUI_API ImGuiID igGetIDPtr(CONST void *ptr_id)
{
    return ImGui::GetID(ptr_id);
}

// Widgets
CIMGUI_API void igText(CONST char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    ImGui::TextV(fmt, args);
    va_end(args);
}

CIMGUI_API void igTextV(CONST char *fmt, va_list args)
{
    ImGui::TextV(fmt, args);
}

CIMGUI_API void igTextColored(CONST ImVec4 col, CONST char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    ImGui::TextColoredV(col, fmt, args);
    va_end(args);
}

CIMGUI_API void igTextColoredV(CONST ImVec4 col, CONST char *fmt, va_list args)
{
    ImGui::TextColoredV(col, fmt, args);
}

CIMGUI_API void igTextDisabled(CONST char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    ImGui::TextDisabledV(fmt, args);
    va_end(args);
}

CIMGUI_API void igTextDisabledV(CONST char *fmt, va_list args)
{
    return ImGui::TextDisabledV(fmt, args);
}

CIMGUI_API void igTextWrapped(CONST char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    ImGui::TextWrappedV(fmt, args);
    va_end(args);
}

CIMGUI_API void igTextWrappedV(CONST char *fmt, va_list args)
{
    ImGui::TextWrappedV(fmt, args);
}

CIMGUI_API void igTextUnformatted(CONST char *text, CONST char *text_end)
{
    return ImGui::TextUnformatted(text, text_end);
}

CIMGUI_API void igLabelText(CONST char *label, CONST char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    ImGui::LabelTextV(label, fmt, args);
    va_end(args);
}

CIMGUI_API void igLabelTextV(CONST char *label, CONST char *fmt, va_list args)
{
    ImGui::LabelTextV(label, fmt, args);
}

CIMGUI_API void igBullet()
{
    return ImGui::Bullet();
}

CIMGUI_API void igBulletText(CONST char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    ImGui::BulletTextV(fmt, args);
    va_end(args);
}

CIMGUI_API void igBulletTextV(CONST char *fmt, va_list args)
{
    ImGui::BulletTextV(fmt, args);
}

CIMGUI_API bool igButton(CONST char *label, CONST ImVec2 size)
{
    return ImGui::Button(label, size);
}

CIMGUI_API bool igSmallButton(CONST char *label)
{
    return ImGui::SmallButton(label);
}

CIMGUI_API bool igInvisibleButton(CONST char *str_id, CONST ImVec2 size)
{
    return ImGui::InvisibleButton(str_id, size);
}

CIMGUI_API void igImage(ImTextureID user_texture_id, CONST ImVec2 size, CONST ImVec2 uv0, CONST ImVec2 uv1, CONST ImVec4 tint_col, CONST ImVec4 border_col)
{
    return ImGui::Image(user_texture_id, size, uv0, uv1, tint_col, border_col);
}

CIMGUI_API bool igImageButton(ImTextureID user_texture_id, CONST ImVec2 size, CONST ImVec2 uv0, CONST ImVec2 uv1, int frame_padding, CONST ImVec4 bg_col, CONST ImVec4 tint_col)
{
    return ImGui::ImageButton(user_texture_id, size, uv0, uv1, frame_padding, bg_col, tint_col);
}

CIMGUI_API bool igCheckbox(CONST char *label, bool *v)
{
    return ImGui::Checkbox(label, v);
}

CIMGUI_API bool igCheckboxFlags(CONST char *label, unsigned int *flags, unsigned int flags_value)
{
    return ImGui::CheckboxFlags(label, flags, flags_value);
}

CIMGUI_API bool igRadioButtonBool(CONST char *label, bool active)
{
    return ImGui::RadioButton(label, active);
}

CIMGUI_API bool igRadioButton(CONST char *label, int *v, int v_button)
{
    return ImGui::RadioButton(label, v, v_button);
}

CIMGUI_API void igPlotLines(CONST char *label, CONST float *values, int values_count, int values_offset, CONST char *overlay_text, float scale_min, float scale_max, ImVec2 graph_size, int stride)
{
    return ImGui::PlotLines(label, values, values_count, values_offset, overlay_text, scale_min, scale_max, graph_size, stride);
}

CIMGUI_API void igPlotLines2(CONST char *label, float (*values_getter)(void *data, int idx), void *data, int values_count, int values_offset, CONST char *overlay_text, float scale_min, float scale_max, ImVec2 graph_size)
{
    return ImGui::PlotLines(label, values_getter, data, values_count, values_offset, overlay_text, scale_min, scale_max, graph_size);
}

CIMGUI_API void igPlotHistogram(CONST char *label, CONST float *values, int values_count, int values_offset, CONST char *overlay_text, float scale_min, float scale_max, ImVec2 graph_size, int stride)
{
    return ImGui::PlotHistogram(label, values, values_count, values_offset, overlay_text, scale_min, scale_max, graph_size, stride);
}

CIMGUI_API void igPlotHistogram2(CONST char *label, float (*values_getter)(void *data, int idx), void *data, int values_count, int values_offset, CONST char *overlay_text, float scale_min, float scale_max, ImVec2 graph_size)
{
    return ImGui::PlotHistogram(label, values_getter, data, values_count, values_offset, overlay_text, scale_min, scale_max, graph_size);
}

CIMGUI_API void igProgressBar(float fraction, CONST ImVec2 *size_arg, CONST char *overlay)
{
    return ImGui::ProgressBar(fraction, *size_arg, overlay);
}

// Widgets: Sliders (tip: ctrl+click on a slider to input text)
CIMGUI_API bool igSliderFloat(CONST char *label, float *v, float v_min, float v_max, CONST char *display_format, float power)
{
    return ImGui::SliderFloat(label, v, v_min, v_max, display_format, power);
}

CIMGUI_API bool igSliderFloat2(CONST char *label, float v[2], float v_min, float v_max, CONST char *display_format, float power)
{
    return ImGui::SliderFloat2(label, v, v_min, v_max, display_format, power);
}

CIMGUI_API bool igSliderFloat3(CONST char *label, float v[3], float v_min, float v_max, CONST char *display_format, float power)
{
    return ImGui::SliderFloat3(label, v, v_min, v_max, display_format, power);
}

CIMGUI_API bool igSliderFloat4(CONST char *label, float v[4], float v_min, float v_max, CONST char *display_format, float power)
{
    return ImGui::SliderFloat4(label, v, v_min, v_max, display_format, power);
}

CIMGUI_API bool igSliderAngle(CONST char *label, float *v_rad, float v_degrees_min, float v_degrees_max)
{
    return ImGui::SliderAngle(label, v_rad, v_degrees_min, v_degrees_max);
}

CIMGUI_API bool igSliderInt(CONST char *label, int *v, int v_min, int v_max, CONST char *display_format)
{
    return ImGui::SliderInt(label, v, v_min, v_max, display_format);
}

CIMGUI_API bool igSliderInt2(CONST char *label, int v[2], int v_min, int v_max, CONST char *display_format)
{
    return ImGui::SliderInt2(label, v, v_min, v_max, display_format);
}

CIMGUI_API bool igSliderInt3(CONST char *label, int v[3], int v_min, int v_max, CONST char *display_format)
{
    return ImGui::SliderInt3(label, v, v_min, v_max, display_format);
}

CIMGUI_API bool igSliderInt4(CONST char *label, int v[4], int v_min, int v_max, CONST char *display_format)
{
    return ImGui::SliderInt4(label, v, v_min, v_max, display_format);
}

CIMGUI_API bool igVSliderFloat(CONST char *label, CONST ImVec2 size, float *v, float v_min, float v_max, CONST char *display_format, float power)
{
    return ImGui::VSliderFloat(label, size, v, v_min, v_max, display_format, power);
}

CIMGUI_API bool igVSliderInt(CONST char *label, CONST ImVec2 size, int *v, int v_min, int v_max, CONST char *display_format)
{
    return ImGui::VSliderInt(label, size, v, v_min, v_max, display_format);
}

CIMGUI_API bool igBeginCombo(CONST char *label, CONST char *preview_value, ImGuiComboFlags flags)
{
    return ImGui::BeginCombo(label, preview_value, flags);
}

CIMGUI_API void igEndCombo()
{
    return ImGui::EndCombo();
}

CIMGUI_API bool igCombo(CONST char *label, int *current_item, CONST char *CONST *items, int items_count, int popup_max_height_in_items)
{
    return ImGui::Combo(label, current_item, items, items_count, popup_max_height_in_items);
}

CIMGUI_API bool igCombo2(CONST char *label, int *current_item, CONST char *items_separated_by_zeros, int popup_max_height_in_items)
{
    return ImGui::Combo(label, current_item, items_separated_by_zeros, popup_max_height_in_items);
}

CIMGUI_API bool igCombo3(CONST char *label, int *current_item, bool (*items_getter)(void *data, int idx, CONST char **out_text), void *data, int items_count, int popup_max_height_in_items)
{
    return ImGui::Combo(label, current_item, items_getter, data, items_count, popup_max_height_in_items);
}

// Widgets: Color Editor/Picker (tip: the ColorEdit* functions have a little colored preview square that can be left-clicked to open a picker, and right-clicked to open an option menu.)
CIMGUI_API bool igColorEdit3(CONST char *label, float col[3], ImGuiColorEditFlags flags)
{
    return ImGui::ColorEdit3(label, col, flags);
}

CIMGUI_API bool igColorEdit4(CONST char *label, float col[4], ImGuiColorEditFlags flags)
{
    return ImGui::ColorEdit4(label, col, flags);
}

CIMGUI_API bool igColorPicker3(CONST char *label, float col[3], ImGuiColorEditFlags flags)
{
    return ImGui::ColorPicker3(label, col, flags);
}

CIMGUI_API bool igColorPicker4(CONST char *label, float col[4], ImGuiColorEditFlags flags, CONST float *ref_col)
{
    return ImGui::ColorPicker4(label, col, flags, ref_col);
}

CIMGUI_API bool igColorButton(CONST char *desc_id, CONST ImVec4 col, ImGuiColorEditFlags flags, CONST ImVec2 size)
{
    return ImGui::ColorButton(desc_id, col, flags, size);
}

CIMGUI_API void igSetColorEditOptions(ImGuiColorEditFlags flags)
{
    return ImGui::SetColorEditOptions(flags);
}

// Widgets: Drags (tip: ctrl+click on a drag box to input text)
CIMGUI_API bool igDragFloat(CONST char *label, float *v, float v_speed, float v_min, float v_max, CONST char *display_format, float power)
{
    return ImGui::DragFloat(label, v, v_speed, v_min, v_max, display_format, power);
}

CIMGUI_API bool igDragFloat2(CONST char *label, float v[2], float v_speed, float v_min, float v_max, CONST char *display_format, float power)
{
    return ImGui::DragFloat2(label, v, v_speed, v_min, v_max, display_format, power);
}

CIMGUI_API bool igDragFloat3(CONST char *label, float v[3], float v_speed, float v_min, float v_max, CONST char *display_format, float power)
{
    return ImGui::DragFloat3(label, v, v_speed, v_min, v_max, display_format, power);
}

CIMGUI_API bool igDragFloat4(CONST char *label, float v[4], float v_speed, float v_min, float v_max, CONST char *display_format, float power)
{
    return ImGui::DragFloat4(label, v, v_speed, v_min, v_max, display_format, power);
}

CIMGUI_API bool igDragFloatRange2(CONST char *label, float *v_current_min, float *v_current_max, float v_speed, float v_min, float v_max, CONST char *display_format, CONST char *display_format_max, float power)
{
    return ImGui::DragFloatRange2(label, v_current_min, v_current_max, v_speed, v_min, v_max, display_format, display_format_max, power);
}

CIMGUI_API bool igDragInt(CONST char *label, int *v, float v_speed, int v_min, int v_max, CONST char *display_format)
{
    return ImGui::DragInt(label, v, v_speed, v_min, v_max, display_format);
}

CIMGUI_API bool igDragInt2(CONST char *label, int v[2], float v_speed, int v_min, int v_max, CONST char *display_format)
{
    return ImGui::DragInt2(label, v, v_speed, v_min, v_max, display_format);
}

CIMGUI_API bool igDragInt3(CONST char *label, int v[3], float v_speed, int v_min, int v_max, CONST char *display_format)
{
    return ImGui::DragInt3(label, v, v_speed, v_min, v_max, display_format);
}

CIMGUI_API bool igDragInt4(CONST char *label, int v[4], float v_speed, int v_min, int v_max, CONST char *display_format)
{
    return ImGui::DragInt4(label, v, v_speed, v_min, v_max, display_format);
}

CIMGUI_API bool igDragIntRange2(CONST char *label, int *v_current_min, int *v_current_max, float v_speed, int v_min, int v_max, CONST char *display_format, CONST char *display_format_max)
{
    return ImGui::DragIntRange2(label, v_current_min, v_current_max, v_speed, v_min, v_max, display_format, display_format_max);
}

// Widgets: Input
CIMGUI_API bool igInputText(CONST char *label, char *buf, size_t buf_size, ImGuiInputTextFlags flags, ImGuiTextEditCallback callback, void *user_data)
{
    return ImGui::InputText(label, buf, buf_size, flags, callback, user_data);
}

CIMGUI_API bool igInputTextMultiline(CONST char *label, char *buf, size_t buf_size, CONST ImVec2 size, ImGuiInputTextFlags flags, ImGuiTextEditCallback callback, void *user_data)
{
    return ImGui::InputTextMultiline(label, buf, buf_size, size, flags, callback, user_data);
}

CIMGUI_API bool igInputFloat(CONST char *label, float *v, float step, float step_fast, int decimal_precision, ImGuiInputTextFlags extra_flags)
{
    return ImGui::InputFloat(label, v, step, step_fast, decimal_precision, extra_flags);
}

CIMGUI_API bool igInputFloat2(CONST char *label, float v[2], int decimal_precision, ImGuiInputTextFlags extra_flags)
{
    return ImGui::InputFloat2(label, v, decimal_precision, extra_flags);
}

CIMGUI_API bool igInputFloat3(CONST char *label, float v[3], int decimal_precision, ImGuiInputTextFlags extra_flags)
{
    return ImGui::InputFloat3(label, v, decimal_precision, extra_flags);
}

CIMGUI_API bool igInputFloat4(CONST char *label, float v[4], int decimal_precision, ImGuiInputTextFlags extra_flags)
{
    return ImGui::InputFloat4(label, v, decimal_precision, extra_flags);
}

CIMGUI_API bool igInputInt(CONST char *label, int *v, int step, int step_fast, ImGuiInputTextFlags extra_flags)
{
    return ImGui::InputInt(label, v, step, step_fast, extra_flags);
}

CIMGUI_API bool igInputInt2(CONST char *label, int v[2], ImGuiInputTextFlags extra_flags)
{
    return ImGui::InputInt2(label, v, extra_flags);
}

CIMGUI_API bool igInputInt3(CONST char *label, int v[3], ImGuiInputTextFlags extra_flags)
{
    return ImGui::InputInt3(label, v, extra_flags);
}

CIMGUI_API bool igInputInt4(CONST char *label, int v[4], ImGuiInputTextFlags extra_flags)
{
    return ImGui::InputInt4(label, v, extra_flags);
}

// Widgets: Trees
CIMGUI_API bool igTreeNode(CONST char *label)
{
    return ImGui::TreeNode(label);
}

CIMGUI_API bool igTreeNodeStr(CONST char *str_id, CONST char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    bool res = ImGui::TreeNodeV(str_id, fmt, args);
    va_end(args);

    return res;
}

CIMGUI_API bool igTreeNodePtr(CONST void *ptr_id, CONST char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    bool res = ImGui::TreeNodeV(ptr_id, fmt, args);
    va_end(args);

    return res;
}

CIMGUI_API bool igTreeNodeStrV(CONST char *str_id, CONST char *fmt, va_list args)
{
    return ImGui::TreeNodeV(str_id, fmt, args);
}

CIMGUI_API bool igTreeNodePtrV(CONST void *ptr_id, CONST char *fmt, va_list args)
{
    return ImGui::TreeNodeV(ptr_id, fmt, args);
}

CIMGUI_API bool igTreeNodeEx(CONST char *label, ImGuiTreeNodeFlags flags)
{
    return ImGui::TreeNodeEx(label, flags);
}

CIMGUI_API bool igTreeNodeExStr(CONST char *str_id, ImGuiTreeNodeFlags flags, CONST char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    bool res = ImGui::TreeNodeExV(str_id, flags, fmt, args);
    va_end(args);

    return res;
}

CIMGUI_API bool igTreeNodeExPtr(CONST void *ptr_id, ImGuiTreeNodeFlags flags, CONST char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    bool res = ImGui::TreeNodeExV(ptr_id, flags, fmt, args);
    va_end(args);

    return res;
}

CIMGUI_API bool igTreeNodeExV(CONST char *str_id, ImGuiTreeNodeFlags flags, CONST char *fmt, va_list args)
{
    return ImGui::TreeNodeExV(str_id, flags, fmt, args);
}

CIMGUI_API bool igTreeNodeExVPtr(CONST void *ptr_id, ImGuiTreeNodeFlags flags, CONST char *fmt, va_list args)
{
    return ImGui::TreeNodeExV(ptr_id, flags, fmt, args);
}

CIMGUI_API void igTreePushStr(CONST char *str_id)
{
    return ImGui::TreePush(str_id);
}

CIMGUI_API void igTreePushPtr(CONST void *ptr_id)
{
    return ImGui::TreePush(ptr_id);
}

CIMGUI_API void igTreePop()
{
    return ImGui::TreePop();
}

CIMGUI_API void igTreeAdvanceToLabelPos()
{
    return ImGui::TreeAdvanceToLabelPos();
}

CIMGUI_API float igGetTreeNodeToLabelSpacing()
{
    return ImGui::GetTreeNodeToLabelSpacing();
}

CIMGUI_API void igSetNextTreeNodeOpen(bool opened, ImGuiCond cond)
{
    return ImGui::SetNextTreeNodeOpen(opened, cond);
}

CIMGUI_API bool igCollapsingHeader(CONST char *label, ImGuiTreeNodeFlags flags)
{
    return ImGui::CollapsingHeader(label, flags);
}

CIMGUI_API bool igCollapsingHeaderEx(CONST char *label, bool *p_open, ImGuiTreeNodeFlags flags)
{
    return ImGui::CollapsingHeader(label, p_open, flags);
}

// Widgets: Selectable / Lists
CIMGUI_API bool igSelectable(CONST char *label, bool selected, ImGuiSelectableFlags flags, CONST ImVec2 size)
{
    return ImGui::Selectable(label, selected, flags, size);
}

CIMGUI_API bool igSelectableEx(CONST char *label, bool *p_selected, ImGuiSelectableFlags flags, CONST ImVec2 size)
{
    return ImGui::Selectable(label, p_selected, flags, size);
}

CIMGUI_API bool igListBox(CONST char *label, int *current_item, CONST char *CONST *items, int items_count, int height_in_items)
{
    return ImGui::ListBox(label, current_item, items, items_count, height_in_items);
}

CIMGUI_API bool igListBox2(CONST char *label, int *current_item, bool (*items_getter)(void *data, int idx, CONST char **out_text), void *data, int items_count, int height_in_items)
{
    return ImGui::ListBox(label, current_item, items_getter, data, items_count, height_in_items);
}

CIMGUI_API bool igListBoxHeader(CONST char *label, CONST ImVec2 size)
{
    return ImGui::ListBoxHeader(label, size);
}

CIMGUI_API bool igListBoxHeader2(CONST char *label, int items_count, int height_in_items)
{
    return ImGui::ListBoxHeader(label, items_count, height_in_items);
}

CIMGUI_API void igListBoxFooter()
{
    return ImGui::ListBoxFooter();
}

CIMGUI_API bool igBeginMainMenuBar()
{
    return ImGui::BeginMainMenuBar();
}

CIMGUI_API void igEndMainMenuBar()
{
    return ImGui::EndMainMenuBar();
}

CIMGUI_API bool igBeginMenuBar()
{
    return ImGui::BeginMenuBar();
}

CIMGUI_API void igEndMenuBar()
{
    return ImGui::EndMenuBar();
}

CIMGUI_API bool igBeginMenu(CONST char *label, bool enabled)
{
    return ImGui::BeginMenu(label, enabled);
}

CIMGUI_API void igEndMenu()
{
    return ImGui::EndMenu();
}

CIMGUI_API bool igMenuItem(CONST char *label, CONST char *shortcut, bool selected, bool enabled)
{
    return ImGui::MenuItem(label, shortcut, selected, enabled);
}

CIMGUI_API bool igMenuItemPtr(CONST char *label, CONST char *shortcut, bool *p_selected, bool enabled)
{
    return ImGui::MenuItem(label, shortcut, p_selected, enabled);
}

// Widgets: Value() Helpers. Output single value in "name: value" format (tip: freely declare your own within the ImGui namespace!)
CIMGUI_API void igValueBool(CONST char *prefix, bool b)
{
    ImGui::Value(prefix, b);
}

CIMGUI_API void igValueInt(CONST char *prefix, int v)
{
    ImGui::Value(prefix, v);
}

CIMGUI_API void igValueUInt(CONST char *prefix, unsigned int v)
{
    ImGui::Value(prefix, v);
}

CIMGUI_API void igValueFloat(CONST char *prefix, float v, CONST char *float_format)
{
    ImGui::Value(prefix, v, float_format);
}

// Logging: all text output from interface is redirected to tty/file/clipboard. Tree nodes are automatically opened.
CIMGUI_API void igLogToTTY(int max_depth)
{
    ImGui::LogToTTY(max_depth);
}

CIMGUI_API void igLogToFile(int max_depth, CONST char *filename)
{
    ImGui::LogToFile(max_depth, filename);
}

CIMGUI_API void igLogToClipboard(int max_depth)
{
    ImGui::LogToClipboard(max_depth);
}

CIMGUI_API void igLogFinish()
{
    ImGui::LogFinish();
}

CIMGUI_API void igLogButtons()
{
    ImGui::LogButtons();
}

CIMGUI_API void igLogText(CONST char *fmt, ...)
{
    char buffer[256];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, 256, fmt, args);
    va_end(args);

    ImGui::LogText("%s", buffer);
}

CIMGUI_API bool igBeginDragDropSource(ImGuiDragDropFlags flags, int mouse_button)
{
    return ImGui::BeginDragDropSource(flags, mouse_button);
}

CIMGUI_API bool igSetDragDropPayload(CONST char *type, CONST void *data, size_t size, ImGuiCond cond)
{
    return ImGui::SetDragDropPayload(type, data, size, cond);
}

CIMGUI_API void igEndDragDropSource()
{
    ImGui::EndDragDropSource();
}

CIMGUI_API bool igBeginDragDropTarget()
{
    return ImGui::BeginDragDropTarget();
}

CIMGUI_API CONST struct ImGuiPayload *igAcceptDragDropPayload(CONST char *type, ImGuiDragDropFlags flags)
{
    return ImGui::AcceptDragDropPayload(type, flags);
}

CIMGUI_API void igEndDragDropTarget()
{
    ImGui::EndDragDropTarget();
}

CIMGUI_API void igPushClipRect(CONST struct ImVec2 clip_rect_min, CONST struct ImVec2 clip_rect_max, bool intersect_with_current_clip_rect)
{
    return ImGui::PushClipRect(clip_rect_min, clip_rect_max, intersect_with_current_clip_rect);
}

CIMGUI_API void igPopClipRect()
{
    return ImGui::PopClipRect();
}

CIMGUI_API void igStyleColorsClassic(struct ImGuiStyle *dst)
{
    ImGui::StyleColorsClassic(dst);
}

CIMGUI_API void igStyleColorsDark(struct ImGuiStyle *dst)
{
    ImGui::StyleColorsDark(dst);
}

CIMGUI_API void igStyleColorsLight(struct ImGuiStyle *dst)
{
    ImGui::StyleColorsLight(dst);
}

CIMGUI_API void igSetItemDefaultFocus()
{
    ImGui::SetItemDefaultFocus();
}

CIMGUI_API void igSetKeyboardFocusHere(int offset)
{
    ImGui::SetKeyboardFocusHere(offset);
}

// Utilities
CIMGUI_API bool igIsItemHovered(ImGuiHoveredFlags flags)
{
    return ImGui::IsItemHovered(flags);
}

CIMGUI_API bool igIsItemActive()
{
    return ImGui::IsItemActive();
}

CIMGUI_API bool igIsItemClicked(int mouse_button)
{
    return ImGui::IsItemClicked(mouse_button);
}

CIMGUI_API bool igIsItemVisible()
{
    return ImGui::IsItemVisible();
}

CIMGUI_API bool igIsAnyItemHovered()
{
    return ImGui::IsAnyItemHovered();
}

CIMGUI_API bool igIsAnyItemActive()
{
    return ImGui::IsAnyItemActive();
}

CIMGUI_API void igGetItemRectMin(ImVec2 *pOut)
{
    *pOut = ImGui::GetItemRectMin();
}

CIMGUI_API void igGetItemRectMax(ImVec2 *pOut)
{
    *pOut = ImGui::GetItemRectMax();
}

CIMGUI_API void igGetItemRectSize(ImVec2 *pOut)
{
    *pOut = ImGui::GetItemRectSize();
}

CIMGUI_API void igSetItemAllowOverlap()
{
    ImGui::SetItemAllowOverlap();
}

CIMGUI_API bool igIsWindowFocused(ImGuiFocusedFlags flags)
{
    return ImGui::IsWindowFocused(flags);
}

CIMGUI_API bool igIsWindowHovered(ImGuiHoveredFlags flags)
{
    return ImGui::IsWindowHovered(flags);
}

CIMGUI_API bool igIsAnyWindowFocused()
{
    return ImGui::IsAnyWindowFocused();
}

CIMGUI_API bool igIsAnyWindowHovered()
{
    return ImGui::IsAnyWindowHovered();
}

CIMGUI_API bool igIsRectVisible(CONST ImVec2 item_size)
{
    return ImGui::IsRectVisible(item_size);
}

CIMGUI_API bool igIsRectVisible2(CONST struct ImVec2 *rect_min, CONST struct ImVec2 *rect_max)
{
    return ImGui::IsRectVisible(*rect_min, *rect_max);
}

CIMGUI_API int igGetKeyIndex(ImGuiKey imgui_key)
{
    return ImGui::GetKeyIndex(imgui_key);
}

CIMGUI_API bool igIsKeyDown(int user_key_index)
{
    return ImGui::IsKeyDown(user_key_index);
}

CIMGUI_API bool igIsKeyPressed(int user_key_index, bool repeat)
{
    return ImGui::IsKeyPressed(user_key_index, repeat);
}

CIMGUI_API bool igIsKeyReleased(int user_key_index)
{
    return ImGui::IsKeyReleased(user_key_index);
}

CIMGUI_API int igGetKeyPressedAmount(int key_index, float repeat_delay, float rate)
{
    return ImGui::GetKeyPressedAmount(key_index, repeat_delay, rate);
}

CIMGUI_API bool igIsMouseDown(int button)
{
    return ImGui::IsMouseDown(button);
}

CIMGUI_API bool igIsMouseClicked(int button, bool repeat)
{
    return ImGui::IsMouseClicked(button, repeat);
}

CIMGUI_API bool igIsMouseDoubleClicked(int button)
{
    return ImGui::IsMouseDoubleClicked(button);
}

CIMGUI_API bool igIsMouseReleased(int button)
{
    return ImGui::IsMouseReleased(button);
}

CIMGUI_API bool igIsMouseDragging(int button, float lock_threshold)
{
    return ImGui::IsMouseDragging(button, lock_threshold);
}

CIMGUI_API bool igIsMouseHoveringRect(CONST ImVec2 r_min, CONST ImVec2 r_max, bool clip)
{
    return ImGui::IsMouseHoveringRect(r_min, r_max, clip);
}

CIMGUI_API bool igIsMousePosValid(CONST struct ImVec2 *mouse_pos)
{
    return ImGui::IsMousePosValid(mouse_pos);
}

CIMGUI_API void igGetMousePos(ImVec2 *pOut)
{
    *pOut = ImGui::GetMousePos();
}

CIMGUI_API void igGetMousePosOnOpeningCurrentPopup(ImVec2 *pOut)
{
    *pOut = ImGui::GetMousePosOnOpeningCurrentPopup();
}

CIMGUI_API void igGetMouseDragDelta(ImVec2 *pOut, int button, float lock_threshold)
{
    *pOut = ImGui::GetMouseDragDelta(button, lock_threshold);
}

CIMGUI_API void igResetMouseDragDelta(int button)
{
    ImGui::ResetMouseDragDelta(button);
}

CIMGUI_API ImGuiMouseCursor igGetMouseCursor()
{
    return ImGui::GetMouseCursor();
}

CIMGUI_API void igSetMouseCursor(ImGuiMouseCursor type)
{
    ImGui::SetMouseCursor(type);
}

CIMGUI_API void igCaptureKeyboardFromApp(bool capture)
{
    return ImGui::CaptureKeyboardFromApp(capture);
}

CIMGUI_API void igCaptureMouseFromApp(bool capture)
{
    return ImGui::CaptureMouseFromApp(capture);
}

CIMGUI_API void *igMemAlloc(size_t sz)
{
    return ImGui::MemAlloc(sz);
}

CIMGUI_API void igMemFree(void *ptr)
{
    return ImGui::MemFree(ptr);
}

CIMGUI_API CONST char *igGetClipboardText()
{
    return ImGui::GetClipboardText();
}

CIMGUI_API void igSetClipboardText(CONST char *text)
{
    return ImGui::SetClipboardText(text);
}

CIMGUI_API float igGetTime()
{
    return ImGui::GetTime();
}

CIMGUI_API int igGetFrameCount()
{
    return ImGui::GetFrameCount();
}

CIMGUI_API struct ImDrawList *igGetOverlayDrawList()
{
    return ImGui::GetOverlayDrawList();
}

CIMGUI_API struct ImDrawListSharedData *igGetDrawListSharedData()
{
    return ImGui::GetDrawListSharedData();
}

CIMGUI_API CONST char *igGetStyleColorName(ImGuiCol idx)
{
    return ImGui::GetStyleColorName(idx);
}

CIMGUI_API void igCalcItemRectClosestPoint(ImVec2 *pOut, CONST ImVec2 pos, bool on_edge, float outward)
{
    *pOut = ImGui::CalcItemRectClosestPoint(pos, on_edge, outward);
}

CIMGUI_API void igCalcTextSize(ImVec2 *pOut, CONST char *text, CONST char *text_end, bool hide_text_after_double_hash, float wrap_width)
{
    *pOut = ImGui::CalcTextSize(text, text_end, hide_text_after_double_hash, wrap_width);
}

CIMGUI_API void igCalcListClipping(int items_count, float items_height, int *out_items_display_start, int *out_items_display_end)
{
    ImGui::CalcListClipping(items_count, items_height, out_items_display_start, out_items_display_end);
}

CIMGUI_API bool igBeginChildFrame(ImGuiID id, CONST ImVec2 size, ImGuiWindowFlags extra_flags)
{
    return ImGui::BeginChildFrame(id, size, extra_flags);
}

CIMGUI_API void igEndChildFrame()
{
    ImGui::EndChildFrame();
}

CIMGUI_API void igColorConvertU32ToFloat4(ImVec4 *pOut, ImU32 in)
{
    *pOut = ImGui::ColorConvertU32ToFloat4(in);
}

CIMGUI_API ImU32 igColorConvertFloat4ToU32(CONST ImVec4 in)
{
    return ImGui::ColorConvertFloat4ToU32(in);
}

CIMGUI_API void igColorConvertRGBtoHSV(float r, float g, float b, float *out_h, float *out_s, float *out_v)
{
    ImGui::ColorConvertRGBtoHSV(r, g, b, *out_h, *out_s, *out_v);
}

CIMGUI_API void igColorConvertHSVtoRGB(float h, float s, float v, float *out_r, float *out_g, float *out_b)
{
    ImGui::ColorConvertHSVtoRGB(h, s, v, *out_r, *out_g, *out_b);
}

CIMGUI_API CONST char *igGetVersion()
{
    return ImGui::GetVersion();
}

CIMGUI_API ImGuiContext *igCreateContext(void *(*malloc_fn)(size_t), void (*free_fn)(void *))
{
    return ImGui::CreateContext(malloc_fn, free_fn);
}

CIMGUI_API void igDestroyContext(ImGuiContext *ctx)
{
    return ImGui::DestroyContext(ctx);
}

CIMGUI_API ImGuiContext *igGetCurrentContext()
{
    return ImGui::GetCurrentContext();
}

CIMGUI_API void igSetCurrentContext(ImGuiContext *ctx)
{
    return ImGui::SetCurrentContext(ctx);
}

CIMGUI_API void ImGuiIO_AddInputCharacter(unsigned short c)
{
    ImGui::GetIO().AddInputCharacter(c);
}

CIMGUI_API void ImGuiIO_AddInputCharactersUTF8(CONST char *utf8_chars)
{
    return ImGui::GetIO().AddInputCharactersUTF8(utf8_chars);
}

CIMGUI_API void ImGuiIO_ClearInputCharacters()
{
    return ImGui::GetIO().ClearInputCharacters();
}

CIMGUI_API struct ImGuiTextFilter *ImGuiTextFilter_Create(const char *default_filter)
{
    ImGuiTextFilter *filter = (ImGuiTextFilter *)ImGui::MemAlloc(sizeof(ImGuiTextFilter));
    IM_PLACEMENT_NEW(filter)
    ImGuiTextFilter(default_filter);
    return filter;
}

CIMGUI_API void ImGuiTextFilter_Destroy(struct ImGuiTextFilter *filter)
{
    filter->~ImGuiTextFilter();
    ImGui::MemFree(filter);
}

CIMGUI_API void ImGuiTextFilter_Clear(struct ImGuiTextFilter *filter)
{
    filter->Clear();
}

CIMGUI_API bool ImGuiTextFilter_Draw(struct ImGuiTextFilter *filter, const char *label, float width)
{
    return filter->Draw(label, width);
}

CIMGUI_API bool ImGuiTextFilter_PassFilter(const struct ImGuiTextFilter *filter, const char *text, const char *text_end)
{
    return filter->PassFilter(text, text_end);
}

CIMGUI_API bool ImGuiTextFilter_IsActive(const struct ImGuiTextFilter *filter)
{
    return filter->IsActive();
}

CIMGUI_API void ImGuiTextFilter_Build(struct ImGuiTextFilter *filter)
{
    filter->Build();
}

CIMGUI_API const char *ImGuiTextFilter_GetInputBuf(struct ImGuiTextFilter *filter)
{
    return filter->InputBuf;
}

CIMGUI_API struct ImGuiTextBuffer *ImGuiTextBuffer_Create()
{
    ImGuiTextBuffer *buffer = (ImGuiTextBuffer *)ImGui::MemAlloc(sizeof(ImGuiTextBuffer));
    IM_PLACEMENT_NEW(buffer)
    ImGuiTextBuffer();
    return buffer;
}

CIMGUI_API void ImGuiTextBuffer_Destroy(struct ImGuiTextBuffer *buffer)
{
    buffer->~ImGuiTextBuffer();
    ImGui::MemFree(buffer);
}

CIMGUI_API char ImGuiTextBuffer_index(struct ImGuiTextBuffer *buffer, int i)
{
    return (*buffer)[i];
}

CIMGUI_API const char *ImGuiTextBuffer_begin(const struct ImGuiTextBuffer *buffer)
{
    return buffer->begin();
}

CIMGUI_API const char *ImGuiTextBuffer_end(const struct ImGuiTextBuffer *buffer)
{
    return buffer->end();
}

CIMGUI_API int ImGuiTextBuffer_size(const struct ImGuiTextBuffer *buffer)
{
    return buffer->size();
}

CIMGUI_API bool ImGuiTextBuffer_empty(struct ImGuiTextBuffer *buffer)
{
    return buffer->empty();
}

CIMGUI_API void ImGuiTextBuffer_clear(struct ImGuiTextBuffer *buffer)
{
    buffer->clear();
}

CIMGUI_API const char *ImGuiTextBuffer_c_str(const struct ImGuiTextBuffer *buffer)
{
    return buffer->c_str();
}

CIMGUI_API void ImGuiTextBuffer_appendf(struct ImGuiTextBuffer *buffer, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    buffer->appendfv(fmt, args);
    va_end(args);
}

CIMGUI_API void ImGuiTextBuffer_appendfv(struct ImGuiTextBuffer *buffer, const char *fmt, va_list args)
{
    buffer->appendfv(fmt, args);
}

CIMGUI_API struct ImGuiStorage *ImGuiStorage_Create()
{
    ImGuiStorage *storage = (ImGuiStorage *)ImGui::MemAlloc(sizeof(ImGuiStorage));
    IM_PLACEMENT_NEW(storage)
    ImGuiStorage();
    return storage;
}

CIMGUI_API void ImGuiStorage_Destroy(struct ImGuiStorage *storage)
{
    storage->~ImGuiStorage();
    ImGui::MemFree(storage);
}

CIMGUI_API void ImGuiStorage_Clear(struct ImGuiStorage *storage)
{
    storage->Clear();
}

CIMGUI_API int ImGuiStorage_GetInt(struct ImGuiStorage *storage, ImGuiID key, int default_val)
{
    return storage->GetInt(key, default_val);
}

CIMGUI_API void ImGuiStorage_SetInt(struct ImGuiStorage *storage, ImGuiID key, int val)
{
    storage->SetInt(key, val);
}

CIMGUI_API bool ImGuiStorage_GetBool(struct ImGuiStorage *storage, ImGuiID key, bool default_val)
{
    return storage->GetBool(key, default_val);
}

CIMGUI_API void ImGuiStorage_SetBool(struct ImGuiStorage *storage, ImGuiID key, bool val)
{
    storage->SetBool(key, val);
}

CIMGUI_API float ImGuiStorage_GetFloat(struct ImGuiStorage *storage, ImGuiID key, float default_val)
{
    return storage->GetFloat(key, default_val);
}

CIMGUI_API void ImGuiStorage_SetFloat(struct ImGuiStorage *storage, ImGuiID key, float val)
{
    storage->SetFloat(key, val);
}

CIMGUI_API void *ImGuiStorage_GetVoidPtr(struct ImGuiStorage *storage, ImGuiID key)
{
    return storage->GetVoidPtr(key);
}

CIMGUI_API void ImGuiStorage_SetVoidPtr(struct ImGuiStorage *storage, ImGuiID key, void *val)
{
    storage->SetVoidPtr(key, val);
}

CIMGUI_API int *ImGuiStorage_GetIntRef(struct ImGuiStorage *storage, ImGuiID key, int default_val)
{
    return storage->GetIntRef(key, default_val);
}

CIMGUI_API bool *ImGuiStorage_GetBoolRef(struct ImGuiStorage *storage, ImGuiID key, bool default_val)
{
    return storage->GetBoolRef(key, default_val);
}

CIMGUI_API float *ImGuiStorage_GetFloatRef(struct ImGuiStorage *storage, ImGuiID key, float default_val)
{
    return storage->GetFloatRef(key, default_val);
}

CIMGUI_API void **ImGuiStorage_GetVoidPtrRef(struct ImGuiStorage *storage, ImGuiID key, void *default_val)
{
    return storage->GetVoidPtrRef(key, default_val);
}

CIMGUI_API void ImGuiStorage_SetAllInt(struct ImGuiStorage *storage, int val)
{
    storage->SetAllInt(val);
}

CIMGUI_API void ImGuiTextEditCallbackData_DeleteChars(struct ImGuiTextEditCallbackData *data, int pos, int bytes_count)
{
    data->DeleteChars(pos, bytes_count);
}

CIMGUI_API void ImGuiTextEditCallbackData_InsertChars(struct ImGuiTextEditCallbackData *data, int pos, const char *text, const char *text_end)
{
    data->InsertChars(pos, text, text_end);
}

CIMGUI_API bool ImGuiTextEditCallbackData_HasSelection(struct ImGuiTextEditCallbackData *data)
{
    return data->HasSelection();
}
