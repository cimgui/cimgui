
#if defined _WIN32 || defined __CYGWIN__
#define API __declspec(dllexport)
#define snprintf sprintf_s
#else
#define API
#endif

#define EXTERN extern "C"
#define CIMGUI_API EXTERN API

CIMGUI_API ImGuiIO*			ig_GetIO();
CIMGUI_API ImGuiStyle*		ig_GetStyle();
CIMGUI_API void				ig_NewFrame();
CIMGUI_API void				ig_Render();
CIMGUI_API void				ig_Shutdown();
CIMGUI_API void				ig_ShowUserGuide();
CIMGUI_API void				ig_ShowStyleEditor(ImGuiStyle* ref);
CIMGUI_API void				ig_ShowTestWindow(bool* opened = NULL);
CIMGUI_API void				ig_ShowMetricsWindow(bool* opened = NULL);

// Window
CIMGUI_API bool				ig_Begin(const char* name = "Debug", bool* p_opened = NULL, ImGuiWindowFlags flags = 0);
CIMGUI_API bool				ig_Begin2(const char* name, bool* p_opened, const ImVec2 size_on_first_use, float bg_alpha = -1.0f, ImGuiWindowFlags flags = 0);
CIMGUI_API void				ig_End();
CIMGUI_API bool				ig_BeginChild(const char* str_id, const ImVec2 size = ImVec2(0, 0), bool border = false, ImGuiWindowFlags extra_flags = 0);
CIMGUI_API bool				ig_BeginChild2(ImGuiID id, const ImVec2 size = ImVec2(0, 0), bool border = false, ImGuiWindowFlags extra_flags = 0);
CIMGUI_API void				ig_EndChild();
CIMGUI_API void				ig_GetContentRegionMax(ImVec2* out);
CIMGUI_API void				ig_GetWindowContentRegionMin(ImVec2* out);
CIMGUI_API void				ig_GetWindowContentRegionMax(ImVec2* out);
CIMGUI_API ImDrawList*		ig_GetWindowDrawList();
CIMGUI_API ImFont*			ig_GetWindowFont();
CIMGUI_API float			ig_GetWindowFontSize(); 
CIMGUI_API void				ig_SetWindowFontScale(float scale);
CIMGUI_API void				ig_GetWindowPos(ImVec2* out);
CIMGUI_API void				ig_GetWindowSize(ImVec2* out);
CIMGUI_API float			ig_GetWindowWidth();
CIMGUI_API bool				ig_GetWindowCollapsed();

CIMGUI_API void				ig_SetNextWindowPos(const ImVec2 pos, ImGuiSetCond cond = 0);
CIMGUI_API void				ig_SetNextWindowSize(const ImVec2 size, ImGuiSetCond cond = 0);
CIMGUI_API void				ig_SetNextWindowCollapsed(bool collapsed, ImGuiSetCond cond = 0);
CIMGUI_API void				ig_SetNextWindowFocus();
CIMGUI_API void				ig_SetWindowPos(const ImVec2 pos, ImGuiSetCond cond = 0);
CIMGUI_API void				ig_SetWindowSize(const ImVec2 size, ImGuiSetCond cond = 0);
CIMGUI_API void				ig_SetWindowCollapsed(bool collapsed, ImGuiSetCond cond = 0);
CIMGUI_API void				ig_SetWindowFocus();
CIMGUI_API void				ig_SetWindowPos2(const char* name, const ImVec2 pos, ImGuiSetCond cond = 0);
CIMGUI_API void				ig_SetWindowSize2(const char* name, const ImVec2 size, ImGuiSetCond cond = 0);
CIMGUI_API void				ig_SetWindowCollapsed2(const char* name, bool collapsed, ImGuiSetCond cond = 0);
CIMGUI_API void				ig_SetWindowFocus2(const char* name);

CIMGUI_API float			ig_GetScrollPosY();
CIMGUI_API float			ig_GetScrollMaxY();
CIMGUI_API void				ig_SetScrollPosHere();
CIMGUI_API void				ig_SetKeyboardFocusHere(int offset = 0);
CIMGUI_API void				ig_SetStateStorage(ImGuiStorage* tree);
CIMGUI_API ImGuiStorage*	ig_GetStateStorage();

// Parameters stacks (shared)
CIMGUI_API void				ig_PushFont(ImFont* font);
CIMGUI_API void				ig_PopFont();
CIMGUI_API void				ig_PushStyleColor(ImGuiCol idx, const ImVec4 col);
CIMGUI_API void				ig_PopStyleColor(int count = 1);
CIMGUI_API void				ig_PushStyleVar(ImGuiStyleVar idx, float val);
CIMGUI_API void				ig_PushStyleVarVec(ImGuiStyleVar idx, const ImVec2 val);
CIMGUI_API void				ig_PopStyleVar(int count = 1);

// Parameters stacks (current window)
CIMGUI_API void				ig_PushItemWidth(float item_width);
CIMGUI_API void				ig_PopItemWidth();
CIMGUI_API float			ig_CalcItemWidth();
CIMGUI_API void				ig_PushAllowKeyboardFocus(bool v);
CIMGUI_API void				ig_PopAllowKeyboardFocus();
CIMGUI_API void				ig_PushTextWrapPos(float wrap_pos_x = 0.0f);
CIMGUI_API void				ig_PopTextWrapPos();

// Tooltip
CIMGUI_API void				ig_SetTooltip(const char* fmt, ...);
CIMGUI_API void				ig_SetTooltipV(const char* fmt, va_list args);
CIMGUI_API void				ig_BeginTooltip();
CIMGUI_API void				ig_EndTooltip();

// Popup
CIMGUI_API void				ig_BeginPopup(bool* p_opened);
CIMGUI_API void				ig_EndPopup();

// Layout
CIMGUI_API void				ig_BeginGroup();
CIMGUI_API void				ig_EndGroup();
CIMGUI_API void				ig_Separator();
CIMGUI_API void				ig_SameLine(int column_x = 0, int spacing_w = -1);
CIMGUI_API void				ig_Spacing();
CIMGUI_API void				ig_Indent();
CIMGUI_API void				ig_Unindent();
CIMGUI_API void				ig_Columns(int count = 1, const char* id = NULL, bool border = true);
CIMGUI_API void				ig_NextColumn();
CIMGUI_API int				ig_GetColumnIndex();
CIMGUI_API float			ig_GetColumnOffset(int column_index = -1);
CIMGUI_API void				ig_SetColumnOffset(int column_index, float offset_x);
CIMGUI_API float			ig_GetColumnWidth(int column_index = -1);
CIMGUI_API int				ig_GetColumnsCount();
CIMGUI_API void				ig_GetCursorPos(ImVec2* pOut);
CIMGUI_API float			ig_GetCursorPosX();
CIMGUI_API float			ig_GetCursorPosY();
CIMGUI_API void				ig_SetCursorPos(const ImVec2 pos);
CIMGUI_API void				ig_SetCursorPosX(float x);
CIMGUI_API void				ig_SetCursorPosY(float y);
CIMGUI_API void				ig_GetCursorScreenPos(ImVec2* pOut);
CIMGUI_API void				ig_SetCursorScreenPos(const ImVec2 pos);
CIMGUI_API void				ig_AlignFirstTextHeightToWidgets();
CIMGUI_API float			ig_GetTextLineHeight();
CIMGUI_API float			ig_GetTextLineHeightWithSpacing();

// ID scopes
// If you are creating widgets in a loop you most likely want to push a unique identifier so ImGui can differentiate them
// You can also use "##extra" within your widget name to distinguish them from each others (see 'Programmer Guide')
CIMGUI_API void				ig_PushID(const char* str_id);
CIMGUI_API void				ig_PushID2(const void* ptr_id);
CIMGUI_API void				ig_PushID3(const int int_id);
CIMGUI_API void				ig_PopID();
CIMGUI_API ImGuiID			ig_GetID(const char* str_id);
CIMGUI_API ImGuiID			ig_GetID2(const void* ptr_id);

// Widgets
CIMGUI_API void				ig_Text(const char* fmt, ...);
CIMGUI_API void				ig_TextV(const char* fmt, va_list args);
CIMGUI_API void				ig_TextColored(const ImVec4 col, const char* fmt, ...);
CIMGUI_API void				ig_TextColoredV(const ImVec4 col, const char* fmt, va_list args);
CIMGUI_API void				ig_TextWrapped(const char* fmt, ...);
CIMGUI_API void				ig_TextWrappedV(const char* fmt, va_list args);
CIMGUI_API void				ig_TextUnformatted(const char* text, const char* text_end = NULL);
CIMGUI_API void				ig_LabelText(const char* label, const char* fmt, ...);
CIMGUI_API void				ig_LabelTextV(const char* label, const char* fmt, va_list args);
CIMGUI_API void				ig_Bullet();
CIMGUI_API void				ig_BulletText(const char* fmt, ...);
CIMGUI_API void				ig_BulletTextV(const char* fmt, va_list args);
CIMGUI_API bool				ig_Button(const char* label, const ImVec2 size = ImVec2(0, 0), bool repeat_when_held = false);
CIMGUI_API bool				ig_SmallButton(const char* label);
CIMGUI_API bool				ig_InvisibleButton(const char* str_id, const ImVec2 size);
CIMGUI_API void				ig_Image(ImTextureID user_texture_id, const ImVec2 size, const ImVec2 uv0 = ImVec2(0, 0), const ImVec2 uv1 = ImVec2(1, 1), const ImVec4 tint_col = ImVec4(1, 1, 1, 1), const ImVec4 border_col = ImVec4(0, 0, 0, 0));
CIMGUI_API bool				ig_ImageButton(ImTextureID user_texture_id, const ImVec2 size, const ImVec2 uv0 = ImVec2(0, 0), const ImVec2 uv1 = ImVec2(1, 1), int frame_padding = -1, const ImVec4 bg_col = ImVec4(0, 0, 0, 1), const ImVec4 tint_col = ImVec4(1, 1, 1, 1));
CIMGUI_API bool				ig_CollapsingHeader(const char* label, const char* str_id = NULL, bool display_frame = true, bool default_open = false);
CIMGUI_API bool				ig_Checkbox(const char* label, bool* v);
CIMGUI_API bool				ig_CheckboxFlags(const char* label, unsigned int* flags, unsigned int flags_value);
CIMGUI_API bool				ig_RadioButton(const char* label, bool active);
CIMGUI_API bool				ig_RadioButton2(const char* label, int* v, int v_button);
CIMGUI_API bool				ig_Combo(const char* label, int* current_item, const char** items, int items_count, int height_in_items = -1);
CIMGUI_API bool				ig_Combo2(const char* label, int* current_item, const char* items_separated_by_zeros, int height_in_items = -1);
CIMGUI_API bool				ig_Combo3(const char* label, int* current_item, bool(*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int height_in_items = -1);
CIMGUI_API bool				ig_ColorButton(const ImVec4 col, bool small_height = false, bool outline_border = true);
CIMGUI_API bool				ig_ColorEdit3(const char* label, float col[3]);
CIMGUI_API bool				ig_ColorEdit4(const char* label, float col[4], bool show_alpha = true);
CIMGUI_API void				ig_ColorEditMode(ImGuiColorEditMode mode);
CIMGUI_API void				ig_PlotLines(const char* label, const float* values, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0), size_t stride = sizeof(float));
CIMGUI_API void				ig_PlotLines2(const char* label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0));
CIMGUI_API void				ig_PlotHistogram(const char* label, const float* values, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0), size_t stride = sizeof(float));
CIMGUI_API void				ig_PlotHistogram2(const char* label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0));

// Widgets: Sliders (tip: ctrl+click on a slider to input text)
CIMGUI_API bool				ig_SliderFloat(const char* label, float* v, float v_min, float v_max, const char* display_format = "%.3f", float power = 1.0f);
CIMGUI_API bool				ig_SliderFloat2(const char* label, float v[2], float v_min, float v_max, const char* display_format = "%.3f", float power = 1.0f);
CIMGUI_API bool				ig_SliderFloat3(const char* label, float v[3], float v_min, float v_max, const char* display_format = "%.3f", float power = 1.0f);
CIMGUI_API bool				ig_SliderFloat4(const char* label, float v[4], float v_min, float v_max, const char* display_format = "%.3f", float power = 1.0f);
CIMGUI_API bool				ig_SliderAngle(const char* label, float* v_rad, float v_degrees_min = -360.0f, float v_degrees_max = +360.0f);
CIMGUI_API bool				ig_SliderInt(const char* label, int* v, int v_min, int v_max, const char* display_format = "%.0f");
CIMGUI_API bool				ig_SliderInt2(const char* label, int v[2], int v_min, int v_max, const char* display_format = "%.0f");
CIMGUI_API bool				ig_SliderInt3(const char* label, int v[3], int v_min, int v_max, const char* display_format = "%.0f");
CIMGUI_API bool				ig_SliderInt4(const char* label, int v[4], int v_min, int v_max, const char* display_format = "%.0f");
CIMGUI_API bool				ig_VSliderFloat(const char* label, const ImVec2 size, float* v, float v_min, float v_max, const char* display_format = "%.3f", float power = 1.0f);
CIMGUI_API bool				ig_VSliderInt(const char* label, const ImVec2 size, int* v, int v_min, int v_max, const char* display_format = "%.0f");

// Widgets: Drags (tip: ctrl+click on a drag box to input text)
// ImGui 1.38+ work-in-progress, may change name or API.
CIMGUI_API bool				ig_DragFloat(const char* label, float* v, float v_step = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f");
CIMGUI_API bool				ig_DragInt(const char* label, int* v, int v_step = 1, int v_min = 0.0f, int v_max = 0.0f, const char* display_format = "%.0f");

// Widgets: Input
CIMGUI_API bool				ig_InputText(const char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiTextEditCallback callback = NULL, void* user_data = NULL);
CIMGUI_API bool				ig_InputFloat(const char* label, float* v, float step = 0.0f, float step_fast = 0.0f, int decimal_precision = -1, ImGuiInputTextFlags extra_flags = 0);
CIMGUI_API bool				ig_InputFloat2(const char* label, float v[2], int decimal_precision = -1);
CIMGUI_API bool				ig_InputFloat3(const char* label, float v[3], int decimal_precision = -1);
CIMGUI_API bool				ig_InputFloat4(const char* label, float v[4], int decimal_precision = -1);
CIMGUI_API bool				ig_InputInt(const char* label, int* v, int step = 1, int step_fast = 100, ImGuiInputTextFlags extra_flags = 0);
CIMGUI_API bool				ig_InputInt2(const char* label, int v[2]);
CIMGUI_API bool				ig_InputInt3(const char* label, int v[3]);
CIMGUI_API bool				ig_InputInt4(const char* label, int v[4]);

// Widgets: Trees
CIMGUI_API bool				ig_TreeNode(const char* str_label_id);
CIMGUI_API bool				ig_TreeNode2(const char* str_id, const char* fmt, ...);
CIMGUI_API bool				ig_TreeNode3(const void* ptr_id, const char* fmt, ...);
CIMGUI_API bool				ig_TreeNodeV(const char* str_id, const char* fmt, va_list args);
CIMGUI_API bool				ig_TreeNodeV2(const void* ptr_id, const char* fmt, va_list args);
CIMGUI_API void				ig_TreePush(const char* str_id = NULL);
CIMGUI_API void				ig_TreePush2(const void* ptr_id = NULL);
CIMGUI_API void				ig_TreePop();
CIMGUI_API void				ig_SetNextTreeNodeOpened(bool opened, ImGuiSetCond cond = 0);

// Widgets: Selectable / Lists
CIMGUI_API bool				ig_Selectable(const char* label, bool selected = false, const ImVec2 size = ImVec2(0, 0));
CIMGUI_API bool				ig_Selectable2(const char* label, bool* p_selected, const ImVec2 size = ImVec2(0, 0));
CIMGUI_API bool				ig_ListBox(const char* label, int* current_item, const char** items, int items_count, int height_in_items = -1);
CIMGUI_API bool				ig_ListBox2(const char* label, int* current_item, bool(*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int height_in_items = -1);
CIMGUI_API bool				ig_ListBoxHeader(const char* label, const ImVec2 size = ImVec2(0, 0));
CIMGUI_API bool				ig_ListBoxHeader2(const char* label, int items_count, int height_in_items = -1);
CIMGUI_API void				ig_ListBoxFooter();

// Widgets: Value() Helpers. Output single value in "name: value" format (tip: freely declare your own within the ImGui namespace!)
CIMGUI_API void				ig_Value(const char* prefix, bool b);
CIMGUI_API void				ig_Value2(const char* prefix, int v);
CIMGUI_API void				ig_Value3(const char* prefix, unsigned int v);
CIMGUI_API void				ig_Value4(const char* prefix, float v, const char* float_format = NULL);
CIMGUI_API void				ig_Color(const char* prefix, const ImVec4 v);
CIMGUI_API void				ig_Color2(const char* prefix, unsigned int v);

// Logging: all text output from interface is redirected to tty/file/clipboard. Tree nodes are automatically opened.
CIMGUI_API void				ig_LogToTTY(int max_depth = -1);
CIMGUI_API void				ig_LogToFile(int max_depth = -1, const char* filename = NULL);
CIMGUI_API void				ig_LogToClipboard(int max_depth = -1);
CIMGUI_API void				ig_LogFinish();
CIMGUI_API void				ig_LogButtons();
CIMGUI_API void				ig_LogText(const char* fmt, ...);

// Utilities
CIMGUI_API bool				ig_IsItemHovered();
CIMGUI_API bool				ig_IsItemHoveredRect();
CIMGUI_API bool				ig_IsItemActive();
CIMGUI_API bool				ig_IsAnyItemActive();
CIMGUI_API void				ig_GetItemRectMin(ImVec2* pOut);
CIMGUI_API void				ig_GetItemRectMax(ImVec2* pOut);
CIMGUI_API void				ig_GetItemRectSize(ImVec2* pOut);
CIMGUI_API bool				ig_IsWindowFocused();
CIMGUI_API bool				ig_IsRootWindowFocused();
CIMGUI_API bool				ig_IsRootWindowOrAnyChildFocused();
CIMGUI_API bool				ig_IsClipped(const ImVec2 item_size);
CIMGUI_API bool				ig_IsKeyPressed(int key_index, bool repeat = true);
CIMGUI_API bool				ig_IsMouseClicked(int button, bool repeat = false);
CIMGUI_API bool				ig_IsMouseDoubleClicked(int button);
CIMGUI_API bool				ig_IsMouseHoveringWindow();
CIMGUI_API bool				ig_IsMouseHoveringAnyWindow();
CIMGUI_API bool				ig_IsMouseHoveringRect(const ImVec2 rect_min, const ImVec2 rect_max);
CIMGUI_API bool				ig_IsMouseDragging(int button = 0, float lock_threshold = -1.0f);
CIMGUI_API bool				ig_IsPosHoveringAnyWindow(const ImVec2 pos);
CIMGUI_API void				ig_GetMousePos(ImVec2* pOut);
CIMGUI_API void				ig_GetMouseDragDelta(ImVec2* pOut, int button = 0, float lock_threshold = -1.0f);
CIMGUI_API ImGuiMouseCursor ig_GetMouseCursor();
CIMGUI_API void				ig_SetMouseCursor(ImGuiMouseCursor type);
CIMGUI_API float			ig_GetTime();
CIMGUI_API int				ig_GetFrameCount();
CIMGUI_API const char*		ig_GetStyleColName(ImGuiCol idx);
CIMGUI_API void				ig_CalcItemRectClosestPoint(ImVec2* pOut, const ImVec2 pos, bool on_edge = false, float outward = +0.0f);
CIMGUI_API void				ig_CalcTextSize(ImVec2* pOut, const char* text, const char* text_end = NULL, bool hide_text_after_double_hash = false, float wrap_width = -1.0f);
CIMGUI_API void				ig_CalcListClipping(int items_count, float items_height, int* out_items_display_start, int* out_items_display_end);

CIMGUI_API void				ig_BeginChildFrame(ImGuiID id, const ImVec2 size);
CIMGUI_API void				ig_EndChildFrame();

CIMGUI_API ImU32			ig_ColorConvertFloat4ToU32(const ImVec4 in);
CIMGUI_API void				ig_ColorConvertRGBtoHSV(float r, float g, float b, float* out_h, float* out_s, float* out_v);
CIMGUI_API void				ig_ColorConvertHSVtoRGB(float h, float s, float v, float* out_r, float* out_g, float* out_b);

// Internal state access - if you want to share ImGui state between modules (e.g. DLL) or allocate it yourself
CIMGUI_API const char*		ig_GetVersion();
CIMGUI_API void*			ig_GetInternalState();
CIMGUI_API size_t			ig_GetInternalStateSize();
CIMGUI_API void				ig_SetInternalState(void* state, bool construct = false);