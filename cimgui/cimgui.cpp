
#include "../imgui/imgui.h"
#include "cimgui.h"

CIMGUI_API ImGuiIO* ig_GetIO()
{
	return &ImGui::GetIO();
}

CIMGUI_API ImGuiStyle* ig_GetStyle()
{
	return &ImGui::GetStyle();
}

CIMGUI_API void ig_NewFrame()
{
	ImGui::NewFrame();
}

CIMGUI_API void ig_Render()
{
	ImGui::Render();
}

CIMGUI_API void ig_Shutdown()
{
	ImGui::Shutdown();
}

CIMGUI_API void ig_ShowUserGuide()
{
	ImGui::ShowUserGuide();
}

CIMGUI_API void ig_ShowStyleEditor(ImGuiStyle* ref)
{
	ImGui::ShowStyleEditor(ref);
}

CIMGUI_API void ig_ShowTestWindow(bool* opened)
{
	ImGui::ShowTestWindow(opened);
}

IMGUI_API void ig_ShowMetricsWindow(bool* opened)
{
	ImGui::ShowMetricsWindow(opened);
}

// Window

CIMGUI_API bool ig_Begin(const char* name, bool* p_opened, ImGuiWindowFlags flags)
{
	return ImGui::Begin(name, p_opened, flags);
}

CIMGUI_API bool ig_Begin2(const char* name, bool* p_opened, const ImVec2 size_on_first_use, float bg_alpha, ImGuiWindowFlags flags)
{
	return ImGui::Begin(name, p_opened, size_on_first_use, bg_alpha, flags);
}

CIMGUI_API void ig_End()
{
	ImGui::End();
}

CIMGUI_API bool ig_BeginChild(const char* str_id, const ImVec2 size, bool border, ImGuiWindowFlags extra_flags)
{
	return ImGui::BeginChild(str_id, size, border, extra_flags);
}

CIMGUI_API bool ig_BeginChildEx(ImGuiID id, const ImVec2 size, bool border, ImGuiWindowFlags extra_flags)
{
	return ImGui::BeginChild(id, size, border, extra_flags);
}

CIMGUI_API void ig_EndChild()
{
	ImGui::EndChild();
}

CIMGUI_API void ig_GetContentRegionMax(ImVec2* out)
{
	*out = ImGui::GetContentRegionMax();
}

CIMGUI_API void ig_GetWindowContentRegionMin(ImVec2* out)
{
	*out = ImGui::GetWindowContentRegionMin();
}

CIMGUI_API void ig_GetWindowContentRegionMax(ImVec2* out)
{
	*out = ImGui::GetWindowContentRegionMax();
}

CIMGUI_API ImDrawList* ig_GetWindowDrawList()
{
	return ImGui::GetWindowDrawList();
}

CIMGUI_API ImFont* ig_GetWindowFont()
{
	return ImGui::GetWindowFont();
}

CIMGUI_API float ig_GetWindowFontSize()
{
	return ImGui::GetWindowFontSize();
}

CIMGUI_API void ig_SetWindowFontScale(float scale)
{
	ImGui::SetWindowFontScale(scale);
}

CIMGUI_API void ig_GetWindowPos(ImVec2* out)
{
	*out = ImGui::GetWindowPos();
}

CIMGUI_API void ig_GetWindowSize(ImVec2* out)
{
	*out = ImGui::GetWindowSize();
}

CIMGUI_API float ig_GetWindowWidth()
{
	return ImGui::GetWindowWidth();
}

CIMGUI_API bool ig_GetWindowCollapsed()
{
	return ImGui::GetWindowCollapsed();
}

CIMGUI_API void ig_SetNextWindowPos(const ImVec2 pos, ImGuiSetCond cond)
{
	ImGui::SetNextWindowPos(pos, cond);
}

CIMGUI_API void ig_SetNextWindowSize(const ImVec2 size, ImGuiSetCond cond)
{
	ImGui::SetNextWindowSize(size, cond);
}

CIMGUI_API void ig_SetNextWindowCollapsed(bool collapsed, ImGuiSetCond cond)
{
	ImGui::SetNextWindowCollapsed(collapsed,cond);
}

CIMGUI_API void ig_SetNextWindowFocus()
{
	ImGui::SetNextWindowFocus();
}

CIMGUI_API void ig_SetWindowPos(const ImVec2 pos, ImGuiSetCond cond)
{
	ImGui::SetWindowPos(pos,cond);
}

CIMGUI_API void ig_SetWindowSize(const ImVec2 size, ImGuiSetCond cond)
{
	ImGui::SetWindowSize(size, cond);
}

CIMGUI_API void ig_SetWindowCollapsed(bool collapsed, ImGuiSetCond cond)
{
	ImGui::SetWindowCollapsed(collapsed,cond);
}

CIMGUI_API void ig_SetWindowFocus()
{
	ImGui::SetWindowFocus();
}

CIMGUI_API void ig_SetWindowPosByName(const char* name, const ImVec2 pos, ImGuiSetCond cond)
{
	ImGui::SetWindowPos(name,pos,cond);
}

CIMGUI_API void ig_SetWindowSize2(const char* name, const ImVec2 size, ImGuiSetCond cond)
{
	ImGui::SetWindowSize(name, size, cond);
}

CIMGUI_API void ig_SetWindowCollapsed2(const char* name, bool collapsed, ImGuiSetCond cond)
{
	ImGui::SetWindowCollapsed(name, collapsed, cond);
}

CIMGUI_API void ig_SetWindowFocus2(const char* name)
{
	ImGui::SetWindowFocus(name);
}

CIMGUI_API float			ig_GetScrollPosY()
{
	return ImGui::GetScrollPosY();
}

CIMGUI_API float			ig_GetScrollMaxY()
{
	return ImGui::GetScrollMaxY();
}

CIMGUI_API void				ig_SetScrollPosHere()
{
	ImGui::SetScrollPosHere();
}

CIMGUI_API void				ig_SetKeyboardFocusHere(int offset)
{
	ImGui::SetKeyboardFocusHere(offset);
}

CIMGUI_API void				ig_SetStateStorage(ImGuiStorage* tree)
{
	ImGui::SetStateStorage(tree);
}

CIMGUI_API ImGuiStorage*	ig_GetStateStorage()
{
	return ImGui::GetStateStorage();
}

// Parameters stacks (shared)
CIMGUI_API void				ig_PushFont(ImFont* font)
{
	ImGui::PushFont(font);
}

CIMGUI_API void				ig_PopFont()
{
	return ImGui::PopFont();
}

CIMGUI_API void				ig_PushStyleColor(ImGuiCol idx, const ImVec4 col)
{
	return ImGui::PushStyleColor(idx, col);
}

CIMGUI_API void				ig_PopStyleColor(int count)
{
	return ImGui::PopStyleColor(count);
}

CIMGUI_API void				ig_PushStyleVar(ImGuiStyleVar idx, float val)
{
	return ImGui::PushStyleVar(idx, val);
}

CIMGUI_API void				ig_PushStyleVarVec(ImGuiStyleVar idx, const ImVec2 val)
{
	return ImGui::PushStyleVar(idx, val);
}

CIMGUI_API void				ig_PopStyleVar(int count)
{
	return ImGui::PopStyleVar(count);
}

// Parameters stacks (current window)
CIMGUI_API void				ig_PushItemWidth(float item_width)
{
	return ImGui::PushItemWidth(item_width);
}

CIMGUI_API void				ig_PopItemWidth()
{
	return ImGui::PopItemWidth();
}

CIMGUI_API float			ig_CalcItemWidth()
{
	return ImGui::CalcItemWidth();
}

CIMGUI_API void				ig_PushAllowKeyboardFocus(bool v)
{
	return ImGui::PushAllowKeyboardFocus(v);
}

CIMGUI_API void				ig_PopAllowKeyboardFocus()
{
	return ImGui::PopAllowKeyboardFocus();
}

CIMGUI_API void				ig_PushTextWrapPos(float wrap_pos_x)
{
	return ImGui::PushTextWrapPos(wrap_pos_x);
}

CIMGUI_API void				ig_PopTextWrapPos()
{
	return ImGui::PopTextWrapPos();
}

// Tooltip
CIMGUI_API void				ig_SetTooltip(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	ImGui::SetTooltipV(fmt, args);
	va_end(args);
}

CIMGUI_API void				ig_SetTooltipV(const char* fmt, va_list args)
{
	ImGui::SetTooltipV(fmt, args);
}

CIMGUI_API void				ig_BeginTooltip()
{
	return ImGui::BeginTooltip();
}

CIMGUI_API void				ig_EndTooltip()
{
	return ImGui::EndTooltip();
}

// Popup
CIMGUI_API void				ig_BeginPopup(bool* p_opened)
{
	return ImGui::BeginPopup(p_opened);
}

CIMGUI_API void				ig_EndPopup()
{
	return ImGui::EndPopup();
}

// Layout
CIMGUI_API void				ig_BeginGroup()
{
	return ImGui::BeginGroup();
}

CIMGUI_API void				ig_EndGroup()
{
	return ImGui::EndGroup();
}

CIMGUI_API void				ig_Separator()
{
	return ImGui::Separator();
}

CIMGUI_API void				ig_SameLine(int column_x, int spacing_w)
{
	return ImGui::SameLine(column_x, spacing_w);
}

CIMGUI_API void				ig_Spacing()
{
	return ImGui::Spacing();
}

CIMGUI_API void				ig_Indent()
{
	return ImGui::Indent();
}

CIMGUI_API void				ig_Unindent()
{
	return ImGui::Unindent();
}

CIMGUI_API void				ig_Columns(int count, const char* id, bool border)
{
	return ImGui::Columns(count, id, border);
}

CIMGUI_API void				ig_NextColumn()
{
	return ImGui::NextColumn();
}

CIMGUI_API int				ig_GetColumnIndex()
{
	return ImGui::GetColumnIndex();
}

CIMGUI_API float			ig_GetColumnOffset(int column_index)
{
	return ImGui::GetColumnOffset(column_index);
}

CIMGUI_API void				ig_SetColumnOffset(int column_index, float offset_x)
{
	return ImGui::SetColumnOffset(column_index, offset_x);
}

CIMGUI_API float			ig_GetColumnWidth(int column_index)
{
	return ImGui::GetColumnWidth(column_index);
}

CIMGUI_API int				ig_GetColumnsCount()
{
	return ImGui::GetColumnsCount();
}

CIMGUI_API void	ig_GetCursorPos(ImVec2* pOut)
{
	*pOut = ImGui::GetCursorPos();
}

CIMGUI_API float			ig_GetCursorPosX()
{
	return ImGui::GetCursorPosX();
}

CIMGUI_API float			ig_GetCursorPosY()
{
	return ImGui::GetCursorPosY();
}

CIMGUI_API void				ig_SetCursorPos(const ImVec2 pos)
{
	return ImGui::SetCursorPos(pos);
}

CIMGUI_API void				ig_SetCursorPosX(float x)
{
	return ImGui::SetCursorPosX(x);
}

CIMGUI_API void				ig_SetCursorPosY(float y)
{
	return ImGui::SetCursorPosY(y);
}

CIMGUI_API void ig_GetCursorScreenPos(ImVec2* pOut)
{
	*pOut = ImGui::GetCursorScreenPos();
}

CIMGUI_API void				ig_SetCursorScreenPos(const ImVec2 pos)
{
	return ImGui::SetCursorScreenPos(pos);
}

CIMGUI_API void				ig_AlignFirstTextHeightToWidgets()
{
	return ImGui::AlignFirstTextHeightToWidgets();
}

CIMGUI_API float			ig_GetTextLineHeight()
{
	return ImGui::GetTextLineHeight();
}

CIMGUI_API float			ig_GetTextLineHeightWithSpacing()
{
	return ImGui::GetTextLineHeightWithSpacing();
}

// ID scopes
// If you are creating widgets in a loop you most likely want to push a unique identifier so ImGui can differentiate them
// You can also use "##extra" within your widget name to distinguish them from each others (see 'Programmer Guide')
CIMGUI_API void				ig_PushIdStr(const char* str_id)
{
	return ImGui::PushID(str_id);
}

CIMGUI_API void				ig_PushIdPtr(const void* ptr_id)
{
	return ImGui::PushID(ptr_id);
}

CIMGUI_API void				ig_PushIdInt(const int int_id)
{
	return ImGui::PushID(int_id);
}

CIMGUI_API void				ig_PopID()
{
	return ImGui::PopID();
}

CIMGUI_API ImGuiID			ig_GetID(const char* str_id)
{
	return ImGui::GetID(str_id);
}

CIMGUI_API ImGuiID			ig_GetID2(const void* ptr_id)
{
	return ImGui::GetID(ptr_id);
}

// Widgets
CIMGUI_API void				ig_Text(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	ImGui::TextV(fmt,args);
	va_end(args);
}

CIMGUI_API void				ig_TextV(const char* fmt, va_list args)
{
	ImGui::TextV(fmt, args);
}

CIMGUI_API void				ig_TextColored(const ImVec4 col, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	ImGui::TextColoredV(col, fmt, args);
	va_end(args);
}

CIMGUI_API void				ig_TextColoredV(const ImVec4 col, const char* fmt, va_list args)
{
	ImGui::TextColoredV(col,fmt,args);
}

CIMGUI_API void				ig_TextWrapped(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	ImGui::TextWrappedV(fmt, args);
	va_end(args);
}

CIMGUI_API void				ig_TextWrappedV(const char* fmt, va_list args)
{
	ImGui::TextWrappedV(fmt, args);
}

CIMGUI_API void				ig_TextUnformatted(const char* text, const char* text_end)
{
	return ImGui::TextUnformatted(text, text_end);
}

CIMGUI_API void				ig_LabelText(const char* label, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	ImGui::LabelTextV(label, fmt, args);
	va_end(args);
}

CIMGUI_API void				ig_LabelTextV(const char* label, const char* fmt, va_list args)
{
	ImGui::LabelTextV(label, fmt, args);
}

CIMGUI_API void				ig_Bullet()
{
	return ImGui::Bullet();
}

CIMGUI_API void				ig_BulletText(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	ImGui::BulletTextV(fmt, args);
	va_end(args);
}

CIMGUI_API void				ig_BulletTextV(const char* fmt, va_list args)
{
	ImGui::BulletTextV(fmt, args);
}

CIMGUI_API bool				ig_Button(const char* label, const ImVec2 size, bool repeat_when_held)
{
	return ImGui::Button(label, size, repeat_when_held);
}

CIMGUI_API bool				ig_SmallButton(const char* label)
{
	return ImGui::SmallButton(label);
}

CIMGUI_API bool				ig_InvisibleButton(const char* str_id, const ImVec2 size)
{
	return ImGui::InvisibleButton(str_id, size);
}

CIMGUI_API void				ig_Image(ImTextureID user_texture_id, const ImVec2 size, const ImVec2 uv0, const ImVec2 uv1, const ImVec4 tint_col, const ImVec4 border_col)
{
	return ImGui::Image(user_texture_id, size, uv0, uv1, tint_col, border_col);
}

CIMGUI_API bool				ig_ImageButton(ImTextureID user_texture_id, const ImVec2 size, const ImVec2 uv0, const ImVec2 uv1, int frame_padding, const ImVec4 bg_col, const ImVec4 tint_col)
{
	return ImGui::ImageButton(user_texture_id, size, uv0, uv1, frame_padding, bg_col, tint_col);
}

CIMGUI_API bool				ig_CollapsingHeader(const char* label, const char* str_id, bool display_frame, bool default_open)
{
	return ImGui::CollapsingHeader(label, str_id, display_frame, default_open);
}

CIMGUI_API bool				ig_Checkbox(const char* label, bool* v)
{
	return ImGui::Checkbox(label, v);
}

CIMGUI_API bool				ig_CheckboxFlags(const char* label, unsigned int* flags, unsigned int flags_value)
{
	return ImGui::CheckboxFlags(label, flags, flags_value);
}

CIMGUI_API bool				ig_RadioButtonBool(const char* label, bool active)
{
	return ImGui::RadioButton(label, active);
}

CIMGUI_API bool				ig_RadioButton(const char* label, int* v, int v_button)
{
	return ImGui::RadioButton(label, v, v_button);
}

CIMGUI_API bool				ig_Combo(const char* label, int* current_item, const char** items, int items_count, int height_in_items)
{
	return ImGui::Combo(label, current_item, items, items_count, height_in_items);
}

CIMGUI_API bool				ig_Combo2(const char* label, int* current_item, const char* items_separated_by_zeros, int height_in_items)
{
	return ImGui::Combo(label, current_item, items_separated_by_zeros, height_in_items);
}

CIMGUI_API bool				ig_Combo3(const char* label, int* current_item, bool(*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int height_in_items)
{
	return ImGui::Combo(label, current_item, items_getter, data, items_count, height_in_items);
}

CIMGUI_API bool				ig_ColorButton(const ImVec4 col, bool small_height, bool outline_border)
{
	return ImGui::ColorButton(col, small_height, outline_border);
}

CIMGUI_API bool				ig_ColorEdit3(const char* label, float col[3])
{
	return ImGui::ColorEdit3(label, col);
}

CIMGUI_API bool				ig_ColorEdit4(const char* label, float col[4], bool show_alpha)
{
	return ImGui::ColorEdit4(label, col, show_alpha);
}

CIMGUI_API void				ig_ColorEditMode(ImGuiColorEditMode mode)
{
	return ImGui::ColorEditMode(mode);
}

CIMGUI_API void				ig_PlotLines(const char* label, const float* values, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, ImVec2 graph_size, size_t stride)
{
	return ImGui::PlotLines(label, values, values_count, values_offset, overlay_text, scale_min, scale_max, graph_size, stride);
}

CIMGUI_API void				ig_PlotLines2(const char* label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, ImVec2 graph_size)
{
	return ImGui::PlotLines(label, values_getter, data, values_count, values_offset, overlay_text, scale_min, scale_max, graph_size);
}

CIMGUI_API void				ig_PlotHistogram(const char* label, const float* values, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, ImVec2 graph_size, size_t stride)
{
	return ImGui::PlotHistogram(label,values, values_count, values_offset, overlay_text, scale_min, scale_max, graph_size, stride);
}

CIMGUI_API void				ig_PlotHistogram2(const char* label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset, const char* overlay_text, float scale_min, float scale_max, ImVec2 graph_size)
{
	return ImGui::PlotHistogram(label, values_getter, data, values_count, values_offset, overlay_text, scale_min, scale_max, graph_size);
}

// Widgets: Sliders (tip: ctrl+click on a slider to input text)
CIMGUI_API bool				ig_SliderFloat(const char* label, float* v, float v_min, float v_max, const char* display_format, float power)
{
	return ImGui::SliderFloat(label, v, v_min, v_max, display_format, power);
}

CIMGUI_API bool				ig_SliderFloat2(const char* label, float v[2], float v_min, float v_max, const char* display_format, float power)
{
	return ImGui::SliderFloat(label, v, v_min, v_max, display_format, power);
}

CIMGUI_API bool				ig_SliderFloat3(const char* label, float v[3], float v_min, float v_max, const char* display_format, float power)
{
	return ImGui::SliderFloat3(label, v, v_min, v_max, display_format, power);
}

CIMGUI_API bool				ig_SliderFloat4(const char* label, float v[4], float v_min, float v_max, const char* display_format, float power)
{
	return ImGui::SliderFloat4(label, v, v_min, v_max, display_format, power);
}

CIMGUI_API bool				ig_SliderAngle(const char* label, float* v_rad, float v_degrees_min, float v_degrees_max)
{
	return ImGui::SliderAngle(label, v_rad, v_degrees_min, v_degrees_max);
}

CIMGUI_API bool				ig_SliderInt(const char* label, int* v, int v_min, int v_max, const char* display_format)
{
	return ImGui::SliderInt(label, v, v_min, v_max, display_format);
}

CIMGUI_API bool				ig_SliderInt2(const char* label, int v[2], int v_min, int v_max, const char* display_format)
{
	return ImGui::SliderInt2(label, v, v_min, v_max, display_format);
}

CIMGUI_API bool				ig_SliderInt3(const char* label, int v[3], int v_min, int v_max, const char* display_format)
{
	return ImGui::SliderInt3(label, v, v_min, v_max, display_format);
}

CIMGUI_API bool				ig_SliderInt4(const char* label, int v[4], int v_min, int v_max, const char* display_format)
{
	return ImGui::SliderInt4(label, v, v_min, v_max, display_format);
}

CIMGUI_API bool				ig_VSliderFloat(const char* label, const ImVec2 size, float* v, float v_min, float v_max, const char* display_format, float power)
{
	return ImGui::VSliderFloat(label, size, v, v_min, v_max, display_format, power);
}

CIMGUI_API bool				ig_VSliderInt(const char* label, const ImVec2 size, int* v, int v_min, int v_max, const char* display_format)
{
	return ImGui::VSliderInt(label, size, v, v_min, v_max, display_format);
}

// Widgets: Drags (tip: ctrl+click on a drag box to input text)
// ImGui 1.38+ work-in-progress, may change name or API.
CIMGUI_API bool				ig_DragFloat(const char* label, float* v, float v_step, float v_min, float v_max, const char* display_format)
{
	return ImGui::DragFloat(label, v, v_step, v_min, v_max, display_format);
}

CIMGUI_API bool				ig_DragInt(const char* label, int* v, int v_step, int v_min, int v_max, const char* display_format)
{
	return ImGui::DragInt(label, v, v_step, v_min, v_max, display_format);
}

// Widgets: Input
CIMGUI_API bool				ig_InputText(const char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags, ImGuiTextEditCallback callback, void* user_data)
{
	return ImGui::InputText(label, buf, buf_size, flags, callback, user_data);
}

CIMGUI_API bool				ig_InputFloat(const char* label, float* v, float step, float step_fast, int decimal_precision, ImGuiInputTextFlags extra_flags)
{
	return ImGui::InputFloat(label, v, step, step_fast, decimal_precision, extra_flags);
}

CIMGUI_API bool				ig_InputFloat2(const char* label, float v[2], int decimal_precision)
{
	return ImGui::InputFloat2(label, v, decimal_precision);
}

CIMGUI_API bool				ig_InputFloat3(const char* label, float v[3], int decimal_precision)
{
	return ImGui::InputFloat3(label, v, decimal_precision);
}

CIMGUI_API bool				ig_InputFloat4(const char* label, float v[4], int decimal_precision)
{
	return ImGui::InputFloat4(label, v, decimal_precision);
}

CIMGUI_API bool				ig_InputInt(const char* label, int* v, int step, int step_fast, ImGuiInputTextFlags extra_flags)
{
	return ImGui::InputInt(label, v, step, step_fast, extra_flags);
}

CIMGUI_API bool				ig_InputInt2(const char* label, int v[2])
{
	return ImGui::InputInt2(label, v);
}

CIMGUI_API bool				ig_InputInt3(const char* label, int v[3])
{
	return ImGui::InputInt3(label, v);
}

CIMGUI_API bool				ig_InputInt4(const char* label, int v[4])
{
	return ImGui::InputInt4(label, v);
}


// Widgets: Trees
CIMGUI_API bool				ig_TreeNode(const char* str_label_id)
{
	return ImGui::TreeNode(str_label_id);
}

CIMGUI_API bool				ig_TreeNodeStr(const char* str_id, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	bool res = ImGui::TreeNodeV(str_id, fmt, args);
	va_end(args);

	return res;
}

CIMGUI_API bool				ig_TreeNodePtr(const void* ptr_id, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	bool res = ImGui::TreeNodeV(ptr_id, fmt, args);
	va_end(args);

	return res;
}

CIMGUI_API bool				ig_TreeNodeStrV(const char* str_id, const char* fmt, va_list args)
{
	return ImGui::TreeNodeV(str_id,fmt,args);
}

CIMGUI_API bool				ig_TreeNodePtrV(const void* ptr_id, const char* fmt, va_list args)
{
	return ImGui::TreeNodeV(ptr_id, fmt, args);
}

CIMGUI_API void				ig_TreePushStr(const char* str_id)
{
	return ImGui::TreePush(str_id);
}

CIMGUI_API void				ig_TreePushPtr(const void* ptr_id)
{
	return ImGui::TreePush(ptr_id);
}

CIMGUI_API void				ig_TreePop()
{
	return ImGui::TreePop();
}

CIMGUI_API void				ig_SetNextTreeNodeOpened(bool opened, ImGuiSetCond cond)
{
	return ImGui::SetNextTreeNodeOpened(opened, cond);
}

// Widgets: Selectable / Lists
CIMGUI_API bool				ig_Selectable(const char* label, bool selected, const ImVec2 size)
{
	return ImGui::Selectable(label, selected, size);
}

CIMGUI_API bool				ig_SelectableEx(const char* label, bool* p_selected, const ImVec2 size)
{
	return ImGui::Selectable(label,p_selected,size);
}

CIMGUI_API bool				ig_ListBox(const char* label, int* current_item, const char** items, int items_count, int height_in_items)
{
	return ImGui::ListBox(label, current_item, items, items_count, height_in_items);
}

CIMGUI_API bool				ig_ListBox2(const char* label, int* current_item, bool(*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int height_in_items)
{
	return ImGui::ListBox(label, current_item, items_getter,data,items_count,height_in_items);
}

CIMGUI_API bool				ig_ListBoxHeader(const char* label, const ImVec2 size)
{
	return ImGui::ListBoxHeader(label, size);
}

CIMGUI_API bool				ig_ListBoxHeader2(const char* label, int items_count, int height_in_items)
{
	return ImGui::ListBoxHeader(label,items_count,height_in_items);
}

CIMGUI_API void				ig_ListBoxFooter()
{
	ImGui::ListBoxFooter();
}

// Widgets: Value() Helpers. Output single value in "name: value" format (tip: freely declare your own within the ImGui namespace!)
CIMGUI_API void				ig_ValueBool(const char* prefix, bool b)
{
	ImGui::Value(prefix, b);
}

CIMGUI_API void				ig_ValueInt(const char* prefix, int v)
{
	ImGui::Value(prefix, v);
}

CIMGUI_API void				ig_ValueUInt(const char* prefix, unsigned int v)
{
	ImGui::Value(prefix, v);
}

CIMGUI_API void				ig_ValueFloat(const char* prefix, float v, const char* float_format)
{
	ImGui::Value(prefix,v,float_format);
}

CIMGUI_API void				ig_Color(const char* prefix, const ImVec4 v)
{
	ImGui::Color(prefix,v);
}

CIMGUI_API void				ig_Color2(const char* prefix, unsigned int v)
{
	ImGui::Color(prefix,v);
}

// Logging: all text output from interface is redirected to tty/file/clipboard. Tree nodes are automatically opened.
CIMGUI_API void				ig_LogToTTY(int max_depth)
{
	ImGui::LogToTTY(max_depth);
}

CIMGUI_API void				ig_LogToFile(int max_depth, const char* filename)
{
	ImGui::LogToFile(max_depth,filename);
}

CIMGUI_API void				ig_LogToClipboard(int max_depth)
{
	ImGui::LogToClipboard(max_depth);
}

CIMGUI_API void				ig_LogFinish()
{
	ImGui::LogFinish();
}

CIMGUI_API void				ig_LogButtons()
{
	ImGui::LogButtons();
}

CIMGUI_API void				ig_LogText(const char* fmt, ...)
{
	char buffer[256];
	va_list args;
	va_start(args, fmt);
	snprintf(buffer, 256, fmt, args);
	va_end(args);

	ImGui::LogText("%s",buffer);
}

// Utilities
CIMGUI_API bool				ig_IsItemHovered()
{
	return ImGui::IsItemHovered();
}

CIMGUI_API bool				ig_IsItemHoveredRect()
{
	return ImGui::IsItemHoveredRect();
}

CIMGUI_API bool				ig_IsItemActive()
{
	return ImGui::IsItemActive();
}

CIMGUI_API bool				ig_IsAnyItemActive()
{
	return ImGui::IsAnyItemActive();
}

CIMGUI_API void ig_GetItemRectMin(ImVec2* pOut)
{
	*pOut = ImGui::GetItemRectMin();
}

CIMGUI_API void ig_GetItemRectMax(ImVec2* pOut)
{
	*pOut = ImGui::GetItemRectMax();
}

CIMGUI_API void	ig_GetItemRectSize(ImVec2* pOut)
{
	*pOut = ImGui::GetItemRectSize();
}

CIMGUI_API bool				ig_IsWindowFocused()
{
	return ImGui::IsWindowFocused();
}

CIMGUI_API bool				ig_IsRootWindowFocused()
{
	return ImGui::IsRootWindowFocused();
}

CIMGUI_API bool				ig_IsRootWindowOrAnyChildFocused()
{
	return ImGui::IsRootWindowOrAnyChildFocused();
}

CIMGUI_API bool				ig_IsClipped(const ImVec2 item_size)
{
	return ImGui::IsClipped(item_size);
}

CIMGUI_API bool				ig_IsKeyPressed(int key_index, bool repeat)
{
	return ImGui::IsKeyPressed(key_index,repeat);
}

CIMGUI_API bool				ig_IsMouseClicked(int button, bool repeat)
{
	return ImGui::IsMouseClicked(button, repeat);
}

CIMGUI_API bool				ig_IsMouseDoubleClicked(int button)
{
	return ImGui::IsMouseDoubleClicked(button);
}

CIMGUI_API bool				ig_IsMouseHoveringWindow()
{
	return ImGui::IsMouseHoveringWindow();
}

CIMGUI_API bool				ig_IsMouseHoveringAnyWindow()
{
	return ImGui::IsMouseHoveringAnyWindow();
}

CIMGUI_API bool				ig_IsMouseHoveringRect(const ImVec2 rect_min, const ImVec2 rect_max)
{
	return ImGui::IsMouseHoveringRect(rect_min,rect_max);
}

CIMGUI_API bool				ig_IsMouseDragging(int button, float lock_threshold)
{
	return ImGui::IsMouseDragging(button,lock_threshold);
}
CIMGUI_API bool				ig_IsPosHoveringAnyWindow(const ImVec2 pos)
{
	return ImGui::IsPosHoveringAnyWindow(pos);
}

CIMGUI_API void ig_GetMousePos(ImVec2* pOut)
{
	*pOut = ImGui::GetMousePos();
}

CIMGUI_API void ig_GetMouseDragDelta(ImVec2* pOut, int button, float lock_threshold)
{
	*pOut = ImGui::GetMouseDragDelta(button,lock_threshold);
}

CIMGUI_API ImGuiMouseCursor ig_GetMouseCursor()
{
	return ImGui::GetMouseCursor();
}

CIMGUI_API void				ig_SetMouseCursor(ImGuiMouseCursor type)
{
	ImGui::SetMouseCursor(type);
}

CIMGUI_API float			ig_GetTime()
{
	return ImGui::GetTime();
}

CIMGUI_API int				ig_GetFrameCount()
{
	return ImGui::GetFrameCount();
}

CIMGUI_API const char*		ig_GetStyleColName(ImGuiCol idx)
{
	return ImGui::GetStyleColName(idx);
}

CIMGUI_API void ig_CalcItemRectClosestPoint(ImVec2* pOut, const ImVec2 pos, bool on_edge, float outward)
{
	*pOut = ImGui::CalcItemRectClosestPoint(pos,on_edge,outward);
}

CIMGUI_API void ig_CalcTextSize(ImVec2* pOut, const char* text, const char* text_end, bool hide_text_after_double_hash, float wrap_width)
{
	*pOut = ImGui::CalcTextSize(text, text_end, hide_text_after_double_hash, wrap_width);
}

CIMGUI_API void				ig_CalcListClipping(int items_count, float items_height, int* out_items_display_start, int* out_items_display_end)
{
	ImGui::CalcListClipping(items_count,items_height,out_items_display_start,out_items_display_end);
}

CIMGUI_API void				ig_BeginChildFrame(ImGuiID id, const ImVec2 size)
{
	ImGui::BeginChildFrame(id, size);
}

CIMGUI_API void				ig_EndChildFrame()
{
	ImGui::EndChildFrame();
}

CIMGUI_API ImU32			ig_ColorConvertFloat4ToU32(const ImVec4 in)
{
	return ImGui::ColorConvertFloat4ToU32(in);
}

CIMGUI_API void				ig_ColorConvertRGBtoHSV(float r, float g, float b, float* out_h, float* out_s, float* out_v)
{
	ImGui::ColorConvertRGBtoHSV(r, g, b, *out_h, *out_s, *out_v);
}

CIMGUI_API void				ig_ColorConvertHSVtoRGB(float h, float s, float v, float* out_r, float* out_g, float* out_b)
{
	ImGui::ColorConvertHSVtoRGB(h,s,v,*out_r,*out_g,*out_b);
}

CIMGUI_API const char*		ig_GetVersion()
{
	return ImGui::GetVersion();
}

CIMGUI_API void*			ig_GetInternalState()
{
	return ImGui::GetInternalState();
}

CIMGUI_API size_t			ig_GetInternalStateSize()
{
	return ImGui::GetInternalStateSize();
}

CIMGUI_API void	ig_SetInternalState(void* state, bool construct)
{
	ImGui::SetInternalState(state,construct);
}

CIMGUI_API void ImGuiIO_AddInputCharacter(unsigned short c)
{
	ImGui::GetIO().AddInputCharacter(c);
}
