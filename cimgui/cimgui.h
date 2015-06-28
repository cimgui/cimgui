
#include <stdio.h>

#if defined _WIN32 || defined __CYGWIN__
#define API __declspec(dllexport)
#define snprintf sprintf_s
#else
#define API
#endif

#if defined __cplusplus
#define EXTERN extern "C"
#else
#include <stdarg.h>
#include <stdbool.h>
#define EXTERN extern
#endif

#define CIMGUI_API EXTERN API
#define CONST const

typedef int ImGuiWindowFlags;
typedef int ImGuiSetCond;
typedef int ImGuiColorEditMode;

CIMGUI_API ImGuiIO*         ig_GetIO();
CIMGUI_API ImGuiStyle*      ig_GetStyle();
CIMGUI_API void             ig_NewFrame();
CIMGUI_API void             ig_Render();
CIMGUI_API void             ig_Shutdown();
CIMGUI_API void             ig_ShowUserGuide();
CIMGUI_API void             ig_ShowStyleEditor(ImGuiStyle* ref);
CIMGUI_API void             ig_ShowTestWindow(bool* opened);
CIMGUI_API void             ig_ShowMetricsWindow(bool* opened);

// Window
CIMGUI_API bool             ig_Begin(CONST char* name, bool* p_opened, ImGuiWindowFlags flags);
CIMGUI_API bool             ig_Begin2(CONST char* name, bool* p_opened, CONST struct ImVec2 size_on_first_use, float bg_alpha, ImGuiWindowFlags flags);
CIMGUI_API void             ig_End();
CIMGUI_API bool             ig_BeginChild(CONST char* str_id, CONST struct ImVec2 size, bool border, ImGuiWindowFlags extra_flags);
CIMGUI_API bool             ig_BeginChildEx(ImGuiID id, CONST struct ImVec2 size, bool border, ImGuiWindowFlags extra_flags);
CIMGUI_API void             ig_EndChild();
CIMGUI_API void             ig_GetContentRegionMax(struct ImVec2* out);
CIMGUI_API void             ig_GetWindowContentRegionMin(struct ImVec2* out);
CIMGUI_API void             ig_GetWindowContentRegionMax(struct ImVec2* out);
CIMGUI_API ImDrawList*      ig_GetWindowDrawList();
CIMGUI_API ImFont*          ig_GetWindowFont();
CIMGUI_API float            ig_GetWindowFontSize(); 
CIMGUI_API void             ig_SetWindowFontScale(float scale);
CIMGUI_API void             ig_GetWindowPos(struct ImVec2* out);
CIMGUI_API void             ig_GetWindowSize(struct ImVec2* out);
CIMGUI_API float            ig_GetWindowWidth();
CIMGUI_API bool             ig_IsWindowCollapsed();

CIMGUI_API void             ig_SetNextWindowPos(CONST struct ImVec2 pos, ImGuiSetCond cond);
CIMGUI_API void             ig_SetNextWindowPosCenter(ImGuiSetCond cond = 0);
CIMGUI_API void             ig_SetNextWindowSize(CONST struct ImVec2 size, ImGuiSetCond cond);
CIMGUI_API void             ig_SetNextWindowCollapsed(bool collapsed, ImGuiSetCond cond);
CIMGUI_API void             ig_SetNextWindowFocus();
CIMGUI_API void             ig_SetWindowPos(CONST struct ImVec2 pos, ImGuiSetCond cond);
CIMGUI_API void             ig_SetWindowSize(CONST struct ImVec2 size, ImGuiSetCond cond);
CIMGUI_API void             ig_SetWindowCollapsed(bool collapsed, ImGuiSetCond cond);
CIMGUI_API void             ig_SetWindowFocus();
CIMGUI_API void             ig_SetWindowPosByName(CONST char* name, CONST struct ImVec2 pos, ImGuiSetCond cond);
CIMGUI_API void             ig_SetWindowSize2(CONST char* name, CONST struct ImVec2 size, ImGuiSetCond cond);
CIMGUI_API void             ig_SetWindowCollapsed2(CONST char* name, bool collapsed, ImGuiSetCond cond);
CIMGUI_API void             ig_SetWindowFocus2(CONST char* name);

CIMGUI_API float            ig_GetScrollPosY();
CIMGUI_API float            ig_GetScrollMaxY();
CIMGUI_API void             ig_SetScrollPosHere();
CIMGUI_API void             ig_SetKeyboardFocusHere(int offset);
CIMGUI_API void             ig_SetStateStorage(ImGuiStorage* tree);
CIMGUI_API ImGuiStorage*    ig_GetStateStorage();

// Parameters stacks (shared)
CIMGUI_API void             ig_PushFont(ImFont* font);
CIMGUI_API void             ig_PopFont();
CIMGUI_API void             ig_PushStyleColor(ImGuiCol idx, CONST struct ImVec4 col);
CIMGUI_API void             ig_PopStyleColor(int count);
CIMGUI_API void             ig_PushStyleVar(ImGuiStyleVar idx, float val);
CIMGUI_API void             ig_PushStyleVarVec(ImGuiStyleVar idx, CONST struct ImVec2 val);
CIMGUI_API void             ig_PopStyleVar(int count);

// Parameters stacks (current window)
CIMGUI_API void             ig_PushItemWidth(float item_width);
CIMGUI_API void             ig_PopItemWidth();
CIMGUI_API float            ig_CalcItemWidth();
CIMGUI_API void             ig_PushAllowKeyboardFocus(bool v);
CIMGUI_API void             ig_PopAllowKeyboardFocus();
CIMGUI_API void             ig_PushTextWrapPos(float wrap_pos_x);
CIMGUI_API void             ig_PopTextWrapPos();
CIMGUI_API void             ig_PushButtonRepeat(bool repeat);
CIMGUI_API void             ig_PopButtonRepeat();


// Tooltip
CIMGUI_API void             ig_SetTooltip(CONST char* fmt, ...);
CIMGUI_API void             ig_SetTooltipV(CONST char* fmt, va_list args);
CIMGUI_API void             ig_BeginTooltip();
CIMGUI_API void             ig_EndTooltip();

// Popup
CIMGUI_API void             ig_OpenPopup(CONST char* str_id);
CIMGUI_API bool             ig_BeginPopup(CONST char* str_id);
CIMGUI_API bool             ig_BeginPopupModal(CONST char* name, bool* p_opened = NULL, ImGuiWindowFlags extra_flags = 0);
CIMGUI_API bool             ig_BeginPopupContextItem(CONST char* str_id, int mouse_button = 1);
CIMGUI_API bool             ig_BeginPopupContextWindow(bool also_over_items = true, CONST char* str_id = NULL, int mouse_button = 1);
CIMGUI_API bool             ig_BeginPopupContextVoid(CONST char* str_id = NULL, int mouse_button = 1);
CIMGUI_API void             ig_EndPopup();
CIMGUI_API void             ig_CloseCurrentPopup();

// Layout
CIMGUI_API void             ig_BeginGroup();
CIMGUI_API void             ig_EndGroup();
CIMGUI_API void             ig_Separator();
CIMGUI_API void             ig_SameLine(int column_x, int spacing_w);
CIMGUI_API void             ig_Spacing();
CIMGUI_API void             ig_Dummy(CONST ImVec2* size);
CIMGUI_API void             ig_Indent();
CIMGUI_API void             ig_Unindent();
CIMGUI_API void             ig_Columns(int count, CONST char* id, bool border);
CIMGUI_API void             ig_NextColumn();
CIMGUI_API int              ig_GetColumnIndex();
CIMGUI_API float            ig_GetColumnOffset(int column_index);
CIMGUI_API void             ig_SetColumnOffset(int column_index, float offset_x);
CIMGUI_API float            ig_GetColumnWidth(int column_index);
CIMGUI_API int              ig_GetColumnsCount();
CIMGUI_API void             ig_GetCursorPos(struct ImVec2* pOut);
CIMGUI_API float            ig_GetCursorPosX();
CIMGUI_API float            ig_GetCursorPosY();
CIMGUI_API void             ig_SetCursorPos(CONST struct ImVec2 pos);
CIMGUI_API void             ig_SetCursorPosX(float x);
CIMGUI_API void             ig_SetCursorPosY(float y);
CIMGUI_API void             ig_GetCursorScreenPos(struct ImVec2* pOut);
CIMGUI_API void             ig_SetCursorScreenPos(CONST struct ImVec2 pos);
CIMGUI_API void             ig_AlignFirstTextHeightToWidgets();
CIMGUI_API float            ig_GetTextLineHeight();
CIMGUI_API float            ig_GetTextLineHeightWithSpacing();
CIMGUI_API float            ig_GetItemsLineHeightWithSpacing();

// ID scopes
// If you are creating widgets in a loop you most likely want to push a unique identifier so ImGui can differentiate them
// You can also use "##extra" within your widget name to distinguish them from each others (see 'Programmer Guide')
CIMGUI_API void             ig_PushIdStr(CONST char* str_id);
CIMGUI_API void             ig_PushIdStrRange(CONST char* str_begin, CONST char* str_end);
CIMGUI_API void             ig_PushIdPtr(CONST void* ptr_id);
CIMGUI_API void             ig_PushIdInt(CONST int int_id);
CIMGUI_API void             ig_PopId();
CIMGUI_API ImGuiID          ig_GetIdStr(CONST char* str_id);
CIMGUI_API ImGuiID          ig_GetIdStrRange(CONST char* str_begin,CONST char* str_end);
CIMGUI_API ImGuiID          ig_GetIdPtr(CONST void* ptr_id);

// Widgets
CIMGUI_API void             ig_Text(CONST char* fmt, ...);
CIMGUI_API void             ig_TextV(CONST char* fmt, va_list args);
CIMGUI_API void             ig_TextColored(CONST struct ImVec4 col, CONST char* fmt, ...);
CIMGUI_API void             ig_TextColoredV(CONST struct ImVec4 col, CONST char* fmt, va_list args);
CIMGUI_API void             ig_TextDisabled(CONST char* fmt, ...);
CIMGUI_API void             ig_TextDisabledV(CONST char* fmt, va_list args);
CIMGUI_API void             ig_TextWrapped(CONST char* fmt, ...);
CIMGUI_API void             ig_TextWrappedV(CONST char* fmt, va_list args);
CIMGUI_API void             ig_TextUnformatted(CONST char* text, CONST char* text_end);
CIMGUI_API void             ig_LabelText(CONST char* label, CONST char* fmt, ...);
CIMGUI_API void             ig_LabelTextV(CONST char* label, CONST char* fmt, va_list args);
CIMGUI_API void             ig_Bullet();
CIMGUI_API void             ig_BulletText(CONST char* fmt, ...);
CIMGUI_API void             ig_BulletTextV(CONST char* fmt, va_list args);
CIMGUI_API bool             ig_Button(CONST char* label, CONST struct ImVec2 size);
CIMGUI_API bool             ig_SmallButton(CONST char* label);
CIMGUI_API bool             ig_InvisibleButton(CONST char* str_id, CONST struct ImVec2 size);
CIMGUI_API void             ig_Image(ImTextureID user_texture_id, CONST struct ImVec2 size, CONST struct ImVec2 uv0, CONST struct ImVec2 uv1, CONST struct ImVec4 tint_col, CONST struct ImVec4 border_col);
CIMGUI_API bool             ig_ImageButton(ImTextureID user_texture_id, CONST struct ImVec2 size, CONST struct ImVec2 uv0, CONST struct ImVec2 uv1, int frame_padding, CONST struct ImVec4 bg_col, CONST struct ImVec4 tint_col);
CIMGUI_API bool             ig_CollapsingHeader(CONST char* label, CONST char* str_id, bool display_frame, bool default_open);
CIMGUI_API bool             ig_Checkbox(CONST char* label, bool* v);
CIMGUI_API bool             ig_CheckboxFlags(CONST char* label, unsigned int* flags, unsigned int flags_value);
CIMGUI_API bool             ig_RadioButtonBool(CONST char* label, bool active);
CIMGUI_API bool             ig_RadioButton(CONST char* label, int* v, int v_button);
CIMGUI_API bool             ig_Combo(CONST char* label, int* current_item, CONST char** items, int items_count, int height_in_items);
CIMGUI_API bool             ig_Combo2(CONST char* label, int* current_item, CONST char* items_separated_by_zeros, int height_in_items);
CIMGUI_API bool             ig_Combo3(CONST char* label, int* current_item, bool(*items_getter)(void* data, int idx, CONST char** out_text), void* data, int items_count, int height_in_items);
CIMGUI_API bool             ig_ColorButton(CONST struct ImVec4 col, bool small_height, bool outline_border);
CIMGUI_API bool             ig_ColorEdit3(CONST char* label, float col[3]);
CIMGUI_API bool             ig_ColorEdit4(CONST char* label, float col[4], bool show_alpha);
CIMGUI_API void             ig_ColorEditMode(ImGuiColorEditMode mode);
CIMGUI_API void             ig_PlotLines(CONST char* label, CONST float* values, int values_count, int values_offset, CONST char* overlay_text, float scale_min, float scale_max, struct ImVec2 graph_size, size_t stride);
CIMGUI_API void             ig_PlotLines2(CONST char* label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset, CONST char* overlay_text, float scale_min, float scale_max, struct ImVec2 graph_size);
CIMGUI_API void             ig_PlotHistogram(CONST char* label, CONST float* values, int values_count, int values_offset, CONST char* overlay_text, float scale_min, float scale_max, struct ImVec2 graph_size, size_t stride);
CIMGUI_API void             ig_PlotHistogram2(CONST char* label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset, CONST char* overlay_text, float scale_min, float scale_max, struct ImVec2 graph_size);

// Widgets: Sliders (tip: ctrl+click on a slider to input text)
CIMGUI_API bool             ig_SliderFloat(CONST char* label, float* v, float v_min, float v_max, CONST char* display_format, float power);
CIMGUI_API bool             ig_SliderFloat2(CONST char* label, float v[2], float v_min, float v_max, CONST char* display_format, float power);
CIMGUI_API bool             ig_SliderFloat3(CONST char* label, float v[3], float v_min, float v_max, CONST char* display_format, float power);
CIMGUI_API bool             ig_SliderFloat4(CONST char* label, float v[4], float v_min, float v_max, CONST char* display_format, float power);
CIMGUI_API bool             ig_SliderAngle(CONST char* label, float* v_rad, float v_degrees_min, float v_degrees_max);
CIMGUI_API bool             ig_SliderInt(CONST char* label, int* v, int v_min, int v_max, CONST char* display_format);
CIMGUI_API bool             ig_SliderInt2(CONST char* label, int v[2], int v_min, int v_max, CONST char* display_format);
CIMGUI_API bool             ig_SliderInt3(CONST char* label, int v[3], int v_min, int v_max, CONST char* display_format);
CIMGUI_API bool             ig_SliderInt4(CONST char* label, int v[4], int v_min, int v_max, CONST char* display_format);
CIMGUI_API bool             ig_VSliderFloat(CONST char* label, CONST struct ImVec2 size, float* v, float v_min, float v_max, CONST char* display_format, float power);
CIMGUI_API bool             ig_VSliderInt(CONST char* label, CONST struct ImVec2 size, int* v, int v_min, int v_max, CONST char* display_format);

// Widgets: Drags (tip: ctrl+click on a drag box to input text)
CIMGUI_API bool             ig_DragFloat(CONST char* label, float* v, float v_speed, float v_min, float v_max, CONST char* display_format, float power);     // If v_max >= v_max we have no bound
CIMGUI_API bool             ig_DragFloat2(CONST char* label, float v[2], float v_speed, float v_min, float v_max, CONST char* display_format, float power);
CIMGUI_API bool             ig_DragFloat3(CONST char* label, float v[3], float v_speed, float v_min, float v_max, CONST char* display_format, float power);
CIMGUI_API bool             ig_DragFloat4(CONST char* label, float v[4], float v_speed, float v_min, float v_max, CONST char* display_format, float power);
CIMGUI_API bool             ig_DragInt(CONST char* label, int* v, float v_speed, int v_min, int v_max, CONST char* display_format);                                       // If v_max >= v_max we have no bound
CIMGUI_API bool             ig_DragInt2(CONST char* label, int v[2], float v_speed, int v_min, int v_max, CONST char* display_format);
CIMGUI_API bool             ig_DragInt3(CONST char* label, int v[3], float v_speed, int v_min, int v_max, CONST char* display_format);
CIMGUI_API bool             ig_DragInt4(CONST char* label, int v[4], float v_speed, int v_min, int v_max, CONST char* display_format);


// Widgets: Input
CIMGUI_API bool             ig_InputText(CONST char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags, ImGuiTextEditCallback callback, void* user_data);
CIMGUI_API bool             ig_InputTextMultiline(CONST char* label, char* buf, size_t buf_size, CONST ImVec2& size = ImVec2(0,0), ImGuiInputTextFlags flags = 0, ImGuiTextEditCallback callback = NULL, void* user_data = NULL);
CIMGUI_API bool             ig_InputFloat(CONST char* label, float* v, float step, float step_fast, int decimal_precision, ImGuiInputTextFlags extra_flags);
CIMGUI_API bool             ig_InputFloat2(CONST char* label, float v[2], int decimal_precision, ImGuiInputTextFlags extra_flags);
CIMGUI_API bool             ig_InputFloat3(CONST char* label, float v[3], int decimal_precision, ImGuiInputTextFlags extra_flags);
CIMGUI_API bool             ig_InputFloat4(CONST char* label, float v[4], int decimal_precision, ImGuiInputTextFlags extra_flags);
CIMGUI_API bool             ig_InputInt(CONST char* label, int* v, int step, int step_fast, ImGuiInputTextFlags extra_flags);
CIMGUI_API bool             ig_InputInt2(CONST char* label, int v[2], ImGuiInputTextFlags extra_flags);
CIMGUI_API bool             ig_InputInt3(CONST char* label, int v[3], ImGuiInputTextFlags extra_flags);
CIMGUI_API bool             ig_InputInt4(CONST char* label, int v[4], ImGuiInputTextFlags extra_flags);

// Widgets: Trees
CIMGUI_API bool             ig_TreeNode(CONST char* str_label_id);
CIMGUI_API bool             ig_TreeNodeStr(CONST char* str_id, CONST char* fmt, ...);
CIMGUI_API bool             ig_TreeNodePtr(CONST void* ptr_id, CONST char* fmt, ...);
CIMGUI_API bool             ig_TreeNodeStrV(CONST char* str_id, CONST char* fmt, va_list args);
CIMGUI_API bool             ig_TreeNodePtrV(CONST void* ptr_id, CONST char* fmt, va_list args);
CIMGUI_API void             ig_TreePushStr(CONST char* str_id);
CIMGUI_API void             ig_TreePushPtr(CONST void* ptr_id);
CIMGUI_API void             ig_TreePop();
CIMGUI_API void             ig_SetNextTreeNodeOpened(bool opened, ImGuiSetCond cond);

// Widgets: Selectable / Lists
CIMGUI_API bool             ig_Selectable(CONST char* label, bool selected = false, ImGuiSelectableFlags flags = 0, CONST ImVec2& size = ImVec2(0,0));
CIMGUI_API bool             ig_SelectableEx(CONST char* label, bool* p_selected, ImGuiSelectableFlags flags = 0, CONST ImVec2& size = ImVec2(0,0));
CIMGUI_API bool             ig_ListBox(CONST char* label, int* current_item, CONST char** items, int items_count, int height_in_items);
CIMGUI_API bool             ig_ListBox2(CONST char* label, int* current_item, bool(*items_getter)(void* data, int idx, CONST char** out_text), void* data, int items_count, int height_in_items);
CIMGUI_API bool             ig_ListBoxHeader(CONST char* label, CONST struct ImVec2 size);
CIMGUI_API bool             ig_ListBoxHeader2(CONST char* label, int items_count, int height_in_items);
CIMGUI_API void             ig_ListBoxFooter();

// Widgets: Menus
CIMGUI_API bool             ig_BeginMainMenuBar();
CIMGUI_API void             ig_EndMainMenuBar();
CIMGUI_API bool             ig_BeginMenuBar();
CIMGUI_API void             ig_EndMenuBar();
CIMGUI_API bool             ig_BeginMenu(CONST char* label, bool enabled);
CIMGUI_API void             ig_EndMenu();
CIMGUI_API bool             ig_MenuItem(CONST char* label, CONST char* shortcut, bool selected, bool enabled);
CIMGUI_API bool             ig_MenuItemPtr(CONST char* label, CONST char* shortcut, bool* p_selected, bool enabled);


// Widgets: Value() Helpers. Output single value in "name: value" format (tip: freely declare your own within the ImGui namespace!)
CIMGUI_API void             ig_ValueBool(CONST char* prefix, bool b);
CIMGUI_API void             ig_ValueInt(CONST char* prefix, int v);
CIMGUI_API void             ig_ValueUInt(CONST char* prefix, unsigned int v);
CIMGUI_API void             ig_ValueFloat(CONST char* prefix, float v, CONST char* float_format);
CIMGUI_API void             ig_Color(CONST char* prefix, CONST struct ImVec4 v);
CIMGUI_API void             ig_Color2(CONST char* prefix, unsigned int v);

// Logging: all text output from interface is redirected to tty/file/clipboard. Tree nodes are automatically opened.
CIMGUI_API void             ig_LogToTTY(int max_depth);
CIMGUI_API void             ig_LogToFile(int max_depth, CONST char* filename);
CIMGUI_API void             ig_LogToClipboard(int max_depth);
CIMGUI_API void             ig_LogFinish();
CIMGUI_API void             ig_LogButtons();
CIMGUI_API void             ig_LogText(CONST char* fmt, ...);

// Utilities
CIMGUI_API bool             ig_IsItemHovered();
CIMGUI_API bool             ig_IsItemHoveredRect();
CIMGUI_API bool             ig_IsItemActive();
CIMGUI_API bool             ig_IsItemVisible();
CIMGUI_API bool             ig_IsAnyItemHovered();
CIMGUI_API bool             ig_IsAnyItemActive();
CIMGUI_API void             ig_GetItemRectMin(struct ImVec2* pOut);
CIMGUI_API void             ig_GetItemRectMax(struct ImVec2* pOut);
CIMGUI_API void             ig_GetItemRectSize(struct ImVec2* pOut);
CIMGUI_API bool             ig_IsWindowHovered();
CIMGUI_API bool             ig_IsWindowFocused();
CIMGUI_API bool             ig_IsRootWindowFocused();
CIMGUI_API bool             ig_IsRootWindowOrAnyChildFocused();
CIMGUI_API bool             ig_IsRectVisible(CONST struct ImVec2 item_size);
CIMGUI_API bool             ig_IsKeyDown(int key_index);
CIMGUI_API bool             ig_IsKeyPressed(int key_index, bool repeat);
CIMGUI_API bool             ig_IsKeyReleased(int key_index);
CIMGUI_API bool             ig_IsMouseDown(int button);
CIMGUI_API bool             ig_IsMouseClicked(int button, bool repeat);
CIMGUI_API bool             ig_IsMouseDoubleClicked(int button);
CIMGUI_API bool             ig_IsMouseReleased(int button);
CIMGUI_API bool             ig_IsMouseHoveringWindow();
CIMGUI_API bool             ig_IsMouseHoveringAnyWindow();
CIMGUI_API bool             ig_IsMouseHoveringRect(CONST struct ImVec2 rect_min, CONST struct ImVec2 rect_max);
CIMGUI_API bool             ig_IsMouseDragging(int button, float lock_threshold);
CIMGUI_API bool             ig_IsPosHoveringAnyWindow(CONST struct ImVec2 pos);
CIMGUI_API void             ig_GetMousePos(struct ImVec2* pOut);
CIMGUI_API void             ig_GetMouseDragDelta(struct ImVec2* pOut, int button, float lock_threshold);
CIMGUI_API void             ig_ResetMouseDragDelta(int button);
CIMGUI_API ImGuiMouseCursor ig_GetMouseCursor();
CIMGUI_API void             ig_SetMouseCursor(ImGuiMouseCursor type);
CIMGUI_API float            ig_GetTime();
CIMGUI_API int              ig_GetFrameCount();
CIMGUI_API CONST char*      ig_GetStyleColName(ImGuiCol idx);
CIMGUI_API void             ig_CalcItemRectClosestPoint(struct ImVec2* pOut, CONST struct ImVec2 pos, bool on_edge, float outward);
CIMGUI_API void             ig_CalcTextSize(struct ImVec2* pOut, CONST char* text, CONST char* text_end, bool hide_text_after_double_hash, float wrap_width);
CIMGUI_API void             ig_CalcListClipping(int items_count, float items_height, int* out_items_display_start, int* out_items_display_end);

CIMGUI_API bool             ig_BeginChildFrame(ImGuiID id, CONST struct ImVec2 size);
CIMGUI_API void             ig_EndChildFrame();

CIMGUI_API ImU32            ig_ColorConvertFloat4ToU32(CONST struct ImVec4 in);
CIMGUI_API void             ig_ColorConvertRGBtoHSV(float r, float g, float b, float* out_h, float* out_s, float* out_v);
CIMGUI_API void             ig_ColorConvertHSVtoRGB(float h, float s, float v, float* out_r, float* out_g, float* out_b);

// Internal state access - if you want to share ImGui state between modules (e.g. DLL) or allocate it yourself
CIMGUI_API CONST char*      ig_GetVersion();
CIMGUI_API void*            ig_GetInternalState();
CIMGUI_API size_t           ig_GetInternalStateSize();
CIMGUI_API void             ig_SetInternalState(void* state, bool construct);

CIMGUI_API void             ImFontAtlas_GetTexDataAsRGBA32(ImFontAtlas* atlas, unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel);
CIMGUI_API void             ImFontAtlas_GetTexDataAsAlpha8(ImFontAtlas* atlas, unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel);
CIMGUI_API void             ImFontAtlas_SetTexID(ImFontAtlas* atlas, void* tex);
CIMGUI_API ImFont*          ImFontAtlas_AddFontDefault(ImFontAtlas* atlas);
CIMGUI_API ImFont*          ImFontAtlas_AddFontFromFileTTF(ImFontAtlas* atlas, CONST char* filename, float size_pixels, CONST ImWchar* glyph_ranges, int font_no);
CIMGUI_API ImFont*          ImFontAtlas_AddFontFromMemoryTTF(ImFontAtlas* atlas, void* ttf_data, int ttf_size, float size_pixels, CONST ImWchar* glyph_ranges, int font_no);
CIMGUI_API ImFont*          ImFontAtlas_AddFontFromMemoryCompressedTTF(ImFontAtlas* atlas, CONST void* compressed_ttf_data, int compressed_ttf_size, float size_pixels, CONST ImWchar* glyph_ranges, int font_no);
CIMGUI_API void             ImFontAtlas_ClearTexData(ImFontAtlas* atlas);
CIMGUI_API void             ImFontAtlas_Clear(ImFontAtlas* atlas);