
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

CIMGUI_API ImGuiIO*         igGetIO();
CIMGUI_API ImGuiStyle*      igGetStyle();
CIMGUI_API ImDrawData*      igGetDrawData();
CIMGUI_API void             igNewFrame();
CIMGUI_API void             igRender();
CIMGUI_API void             igShutdown();
CIMGUI_API void             igShowUserGuide();
CIMGUI_API void             igShowStyleEditor(ImGuiStyle* ref);
CIMGUI_API void             igShowTestWindow(bool* opened);
CIMGUI_API void             igShowMetricsWindow(bool* opened);

// Window
CIMGUI_API bool             igBegin(CONST char* name, bool* p_opened, ImGuiWindowFlags flags);
CIMGUI_API bool             igBegin2(CONST char* name, bool* p_opened, CONST struct ImVec2 size_on_first_use, float bg_alpha, ImGuiWindowFlags flags);
CIMGUI_API void             igEnd();
CIMGUI_API bool             igBeginChild(CONST char* str_id, CONST struct ImVec2 size, bool border, ImGuiWindowFlags extra_flags);
CIMGUI_API bool             igBeginChildEx(ImGuiID id, CONST struct ImVec2 size, bool border, ImGuiWindowFlags extra_flags);
CIMGUI_API void             igEndChild();
CIMGUI_API void             igGetContentRegionMax(struct ImVec2* out);
CIMGUI_API void             igGetContentRegionAvail(struct ImVec2* out);
CIMGUI_API float            igGetContentRegionAvailWidth();
CIMGUI_API void             igGetWindowContentRegionMin(struct ImVec2* out);
CIMGUI_API void             igGetWindowContentRegionMax(struct ImVec2* out);
CIMGUI_API float            igGetWindowContentRegionWidth();
CIMGUI_API ImDrawList*      igGetWindowDrawList();
CIMGUI_API ImFont*          igGetWindowFont();
CIMGUI_API float            igGetWindowFontSize(); 
CIMGUI_API void             igSetWindowFontScale(float scale);
CIMGUI_API void             igGetWindowPos(struct ImVec2* out);
CIMGUI_API void             igGetWindowSize(struct ImVec2* out);
CIMGUI_API float            igGetWindowWidth();
CIMGUI_API float            igGetWindowHeight();
CIMGUI_API bool             igIsWindowCollapsed();

CIMGUI_API void             igSetNextWindowPos(CONST struct ImVec2 pos, ImGuiSetCond cond);
CIMGUI_API void             igSetNextWindowPosCenter(ImGuiSetCond cond);
CIMGUI_API void             igSetNextWindowSize(CONST struct ImVec2 size, ImGuiSetCond cond);
CIMGUI_API void             igSetNextWindowContentSize(CONST ImVec2 size);
CIMGUI_API void             igSetNextWindowContentWidth(float width);
CIMGUI_API void             igSetNextWindowCollapsed(bool collapsed, ImGuiSetCond cond);
CIMGUI_API void             igSetNextWindowFocus();
CIMGUI_API void             igSetWindowPos(CONST struct ImVec2 pos, ImGuiSetCond cond);
CIMGUI_API void             igSetWindowSize(CONST struct ImVec2 size, ImGuiSetCond cond);
CIMGUI_API void             igSetWindowCollapsed(bool collapsed, ImGuiSetCond cond);
CIMGUI_API void             igSetWindowFocus();
CIMGUI_API void             igSetWindowPosByName(CONST char* name, CONST struct ImVec2 pos, ImGuiSetCond cond);
CIMGUI_API void             igSetWindowSize2(CONST char* name, CONST struct ImVec2 size, ImGuiSetCond cond);
CIMGUI_API void             igSetWindowCollapsed2(CONST char* name, bool collapsed, ImGuiSetCond cond);
CIMGUI_API void             igSetWindowFocus2(CONST char* name);

CIMGUI_API float            igGetScrollX();
CIMGUI_API float            igGetScrollY();
CIMGUI_API float            igGetScrollMaxX();
CIMGUI_API float            igGetScrollMaxY();
CIMGUI_API void             igSetScrollX(float scroll_x);
CIMGUI_API void             igSetScrollY(float scroll_y);
CIMGUI_API void             igSetScrollHere(float center_y_ratio = 0.5f);
CIMGUI_API void             igSetScrollFromPosY(float pos_y, float center_y_ratio = 0.5f);
CIMGUI_API void             igSetKeyboardFocusHere(int offset);
CIMGUI_API void             igSetStateStorage(ImGuiStorage* tree);
CIMGUI_API ImGuiStorage*    igGetStateStorage();

// Parameters stacks (shared)
CIMGUI_API void             igPushFont(ImFont* font);
CIMGUI_API void             igPopFont();
CIMGUI_API void             igPushStyleColor(ImGuiCol idx, CONST struct ImVec4 col);
CIMGUI_API void             igPopStyleColor(int count);
CIMGUI_API void             igPushStyleVar(ImGuiStyleVar idx, float val);
CIMGUI_API void             igPushStyleVarVec(ImGuiStyleVar idx, CONST struct ImVec2 val);
CIMGUI_API void             igPopStyleVar(int count);
CIMGUI_API ImU32            igGetColorU32(ImGuiCol idx, float alpha_mul);
CIMGUI_API ImU32            igGetColorU32Vec(CONST ImVec4* col);


// Parameters stacks (current window)
CIMGUI_API void             igPushItemWidth(float item_width);
CIMGUI_API void             igPopItemWidth();
CIMGUI_API float            igCalcItemWidth();
CIMGUI_API void             igPushTextWrapPos(float wrap_pos_x);
CIMGUI_API void             igPopTextWrapPos();
CIMGUI_API void             igPushAllowKeyboardFocus(bool v);
CIMGUI_API void             igPopAllowKeyboardFocus();
CIMGUI_API void             igPushButtonRepeat(bool repeat);
CIMGUI_API void             igPopButtonRepeat();

// Layout
CIMGUI_API void             igBeginGroup();
CIMGUI_API void             igEndGroup();
CIMGUI_API void             igSeparator();
CIMGUI_API void             igSameLine(float local_pos_x, float spacing_w);
CIMGUI_API void             igSpacing();
CIMGUI_API void             igDummy(CONST ImVec2* size);
CIMGUI_API void             igIndent();
CIMGUI_API void             igUnindent();
CIMGUI_API void             igColumns(int count, CONST char* id, bool border);
CIMGUI_API void             igNextColumn();
CIMGUI_API int              igGetColumnIndex();
CIMGUI_API float            igGetColumnOffset(int column_index);
CIMGUI_API void             igSetColumnOffset(int column_index, float offset_x);
CIMGUI_API float            igGetColumnWidth(int column_index);
CIMGUI_API int              igGetColumnsCount();
CIMGUI_API void             igGetCursorPos(struct ImVec2* pOut);
CIMGUI_API float            igGetCursorPosX();
CIMGUI_API float            igGetCursorPosY();
CIMGUI_API void             igSetCursorPos(CONST struct ImVec2 local_pos);
CIMGUI_API void             igSetCursorPosX(float x);
CIMGUI_API void             igSetCursorPosY(float y);
CIMGUI_API void             igGetCursorStartPos(struct ImVec2* pOut);
CIMGUI_API void             igGetCursorScreenPos(struct ImVec2* pOut);
CIMGUI_API void             igSetCursorScreenPos(CONST struct ImVec2 pos);
CIMGUI_API void             igAlignFirstTextHeightToWidgets();
CIMGUI_API float            igGetTextLineHeight();
CIMGUI_API float            igGetTextLineHeightWithSpacing();
CIMGUI_API float            igGetItemsLineHeightWithSpacing();

// ID scopes
// If you are creating widgets in a loop you most likely want to push a unique identifier so ImGui can differentiate them
// You can also use "##extra" within your widget name to distinguish them from each others (see 'Programmer Guide')
CIMGUI_API void             igPushIdStr(CONST char* str_id);
CIMGUI_API void             igPushIdStrRange(CONST char* str_begin, CONST char* str_end);
CIMGUI_API void             igPushIdPtr(CONST void* ptr_id);
CIMGUI_API void             igPushIdInt(int int_id);
CIMGUI_API void             igPopId();
CIMGUI_API ImGuiID          igGetIdStr(CONST char* str_id);
CIMGUI_API ImGuiID          igGetIdStrRange(CONST char* str_begin,CONST char* str_end);
CIMGUI_API ImGuiID          igGetIdPtr(CONST void* ptr_id);

// Widgets
CIMGUI_API void             igText(CONST char* fmt, ...);
CIMGUI_API void             igTextV(CONST char* fmt, va_list args);
CIMGUI_API void             igTextColored(CONST struct ImVec4 col, CONST char* fmt, ...);
CIMGUI_API void             igTextColoredV(CONST struct ImVec4 col, CONST char* fmt, va_list args);
CIMGUI_API void             igTextDisabled(CONST char* fmt, ...);
CIMGUI_API void             igTextDisabledV(CONST char* fmt, va_list args);
CIMGUI_API void             igTextWrapped(CONST char* fmt, ...);
CIMGUI_API void             igTextWrappedV(CONST char* fmt, va_list args);
CIMGUI_API void             igTextUnformatted(CONST char* text, CONST char* text_end);
CIMGUI_API void             igLabelText(CONST char* label, CONST char* fmt, ...);
CIMGUI_API void             igLabelTextV(CONST char* label, CONST char* fmt, va_list args);
CIMGUI_API void             igBullet();
CIMGUI_API void             igBulletText(CONST char* fmt, ...);
CIMGUI_API void             igBulletTextV(CONST char* fmt, va_list args);
CIMGUI_API bool             igButton(CONST char* label, CONST struct ImVec2 size);
CIMGUI_API bool             igSmallButton(CONST char* label);
CIMGUI_API bool             igInvisibleButton(CONST char* str_id, CONST struct ImVec2 size);
CIMGUI_API void             igImage(ImTextureID user_texture_id, CONST struct ImVec2 size, CONST struct ImVec2 uv0, CONST struct ImVec2 uv1, CONST struct ImVec4 tint_col, CONST struct ImVec4 border_col);
CIMGUI_API bool             igImageButton(ImTextureID user_texture_id, CONST struct ImVec2 size, CONST struct ImVec2 uv0, CONST struct ImVec2 uv1, int frame_padding, CONST struct ImVec4 bg_col, CONST struct ImVec4 tint_col);
CIMGUI_API bool             igCollapsingHeader(CONST char* label, CONST char* str_id, bool display_frame, bool default_open);
CIMGUI_API bool             igCheckbox(CONST char* label, bool* v);
CIMGUI_API bool             igCheckboxFlags(CONST char* label, unsigned int* flags, unsigned int flags_value);
CIMGUI_API bool             igRadioButtonBool(CONST char* label, bool active);
CIMGUI_API bool             igRadioButton(CONST char* label, int* v, int v_button);
CIMGUI_API bool             igCombo(CONST char* label, int* current_item, CONST char** items, int items_count, int height_in_items);
CIMGUI_API bool             igCombo2(CONST char* label, int* current_item, CONST char* items_separated_by_zeros, int height_in_items);
CIMGUI_API bool             igCombo3(CONST char* label, int* current_item, bool(*items_getter)(void* data, int idx, CONST char** out_text), void* data, int items_count, int height_in_items);
CIMGUI_API bool             igColorButton(CONST struct ImVec4 col, bool small_height, bool outline_border);
CIMGUI_API bool             igColorEdit3(CONST char* label, float col[3]);
CIMGUI_API bool             igColorEdit4(CONST char* label, float col[4], bool show_alpha);
CIMGUI_API void             igColorEditMode(ImGuiColorEditMode mode);
CIMGUI_API void             igPlotLines(CONST char* label, CONST float* values, int values_count, int values_offset, CONST char* overlay_text, float scale_min, float scale_max, struct ImVec2 graph_size, int stride);
CIMGUI_API void             igPlotLines2(CONST char* label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset, CONST char* overlay_text, float scale_min, float scale_max, struct ImVec2 graph_size);
CIMGUI_API void             igPlotHistogram(CONST char* label, CONST float* values, int values_count, int values_offset, CONST char* overlay_text, float scale_min, float scale_max, struct ImVec2 graph_size, int stride);
CIMGUI_API void             igPlotHistogram2(CONST char* label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset, CONST char* overlay_text, float scale_min, float scale_max, struct ImVec2 graph_size);
CIMGUI_API void             igProgressBar(float fraction, CONST ImVec2* size_arg, const char* overlay);


// Widgets: Sliders (tip: ctrl+click on a slider to input text)
CIMGUI_API bool             igSliderFloat(CONST char* label, float* v, float v_min, float v_max, CONST char* display_format, float power);
CIMGUI_API bool             igSliderFloat2(CONST char* label, float v[2], float v_min, float v_max, CONST char* display_format, float power);
CIMGUI_API bool             igSliderFloat3(CONST char* label, float v[3], float v_min, float v_max, CONST char* display_format, float power);
CIMGUI_API bool             igSliderFloat4(CONST char* label, float v[4], float v_min, float v_max, CONST char* display_format, float power);
CIMGUI_API bool             igSliderAngle(CONST char* label, float* v_rad, float v_degrees_min, float v_degrees_max);
CIMGUI_API bool             igSliderInt(CONST char* label, int* v, int v_min, int v_max, CONST char* display_format);
CIMGUI_API bool             igSliderInt2(CONST char* label, int v[2], int v_min, int v_max, CONST char* display_format);
CIMGUI_API bool             igSliderInt3(CONST char* label, int v[3], int v_min, int v_max, CONST char* display_format);
CIMGUI_API bool             igSliderInt4(CONST char* label, int v[4], int v_min, int v_max, CONST char* display_format);
CIMGUI_API bool             igVSliderFloat(CONST char* label, CONST struct ImVec2 size, float* v, float v_min, float v_max, CONST char* display_format, float power);
CIMGUI_API bool             igVSliderInt(CONST char* label, CONST struct ImVec2 size, int* v, int v_min, int v_max, CONST char* display_format);

// Widgets: Drags (tip: ctrl+click on a drag box to input text)
CIMGUI_API bool             igDragFloat(CONST char* label, float* v, float v_speed, float v_min, float v_max, CONST char* display_format, float power);     // If v_max >= v_max we have no bound
CIMGUI_API bool             igDragFloat2(CONST char* label, float v[2], float v_speed, float v_min, float v_max, CONST char* display_format, float power);
CIMGUI_API bool             igDragFloat3(CONST char* label, float v[3], float v_speed, float v_min, float v_max, CONST char* display_format, float power);
CIMGUI_API bool             igDragFloat4(CONST char* label, float v[4], float v_speed, float v_min, float v_max, CONST char* display_format, float power);
CIMGUI_API bool             igDragFloatRange2(CONST char* label, float* v_current_min, float* v_current_max, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, CONST char* display_format = "%.3f", CONST char* display_format_max = NULL, float power = 1.0f);
CIMGUI_API bool             igDragInt(CONST char* label, int* v, float v_speed, int v_min, int v_max, CONST char* display_format);                                       // If v_max >= v_max we have no bound
CIMGUI_API bool             igDragInt2(CONST char* label, int v[2], float v_speed, int v_min, int v_max, CONST char* display_format);
CIMGUI_API bool             igDragInt3(CONST char* label, int v[3], float v_speed, int v_min, int v_max, CONST char* display_format);
CIMGUI_API bool             igDragInt4(CONST char* label, int v[4], float v_speed, int v_min, int v_max, CONST char* display_format);
CIMGUI_API bool             igDragIntRange2(CONST char* label, int* v_current_min, int* v_current_max, float v_speed = 1.0f, int v_min = 0, int v_max = 0, CONST char* display_format = "%.0f", CONST char* display_format_max = NULL);


// Widgets: Input
CIMGUI_API bool             igInputText(CONST char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags, ImGuiTextEditCallback callback, void* user_data);
CIMGUI_API bool             igInputTextMultiline(CONST char* label, char* buf, size_t buf_size, CONST ImVec2 size, ImGuiInputTextFlags flags, ImGuiTextEditCallback callback, void* user_data);
CIMGUI_API bool             igInputFloat(CONST char* label, float* v, float step, float step_fast, int decimal_precision, ImGuiInputTextFlags extra_flags);
CIMGUI_API bool             igInputFloat2(CONST char* label, float v[2], int decimal_precision, ImGuiInputTextFlags extra_flags);
CIMGUI_API bool             igInputFloat3(CONST char* label, float v[3], int decimal_precision, ImGuiInputTextFlags extra_flags);
CIMGUI_API bool             igInputFloat4(CONST char* label, float v[4], int decimal_precision, ImGuiInputTextFlags extra_flags);
CIMGUI_API bool             igInputInt(CONST char* label, int* v, int step, int step_fast, ImGuiInputTextFlags extra_flags);
CIMGUI_API bool             igInputInt2(CONST char* label, int v[2], ImGuiInputTextFlags extra_flags);
CIMGUI_API bool             igInputInt3(CONST char* label, int v[3], ImGuiInputTextFlags extra_flags);
CIMGUI_API bool             igInputInt4(CONST char* label, int v[4], ImGuiInputTextFlags extra_flags);

// Widgets: Trees
CIMGUI_API bool             igTreeNode(CONST char* str_label_id);
CIMGUI_API bool             igTreeNodeStr(CONST char* str_id, CONST char* fmt, ...);
CIMGUI_API bool             igTreeNodePtr(CONST void* ptr_id, CONST char* fmt, ...);
CIMGUI_API bool             igTreeNodeStrV(CONST char* str_id, CONST char* fmt, va_list args);
CIMGUI_API bool             igTreeNodePtrV(CONST void* ptr_id, CONST char* fmt, va_list args);
CIMGUI_API void             igTreePushStr(CONST char* str_id);
CIMGUI_API void             igTreePushPtr(CONST void* ptr_id);
CIMGUI_API void             igTreePop();
CIMGUI_API void             igSetNextTreeNodeOpened(bool opened, ImGuiSetCond cond);

// Widgets: Selectable / Lists
CIMGUI_API bool             igSelectable(CONST char* label, bool selected, ImGuiSelectableFlags flags, CONST ImVec2 size);
CIMGUI_API bool             igSelectableEx(CONST char* label, bool* p_selected, ImGuiSelectableFlags flags, CONST ImVec2 size);
CIMGUI_API bool             igListBox(CONST char* label, int* current_item, CONST char** items, int items_count, int height_in_items);
CIMGUI_API bool             igListBox2(CONST char* label, int* current_item, bool(*items_getter)(void* data, int idx, CONST char** out_text), void* data, int items_count, int height_in_items);
CIMGUI_API bool             igListBoxHeader(CONST char* label, CONST struct ImVec2 size);
CIMGUI_API bool             igListBoxHeader2(CONST char* label, int items_count, int height_in_items);
CIMGUI_API void             igListBoxFooter();

// Widgets: Value() Helpers. Output single value in "name: value" format (tip: freely declare your own within the ImGui namespace!)
CIMGUI_API void             igValueBool(CONST char* prefix, bool b);
CIMGUI_API void             igValueInt(CONST char* prefix, int v);
CIMGUI_API void             igValueUInt(CONST char* prefix, unsigned int v);
CIMGUI_API void             igValueFloat(CONST char* prefix, float v, CONST char* float_format);
CIMGUI_API void             igValueColor(CONST char* prefix, CONST struct ImVec4 v);
CIMGUI_API void             igValueColor2(CONST char* prefix, unsigned int v);

// Tooltip
CIMGUI_API void             igSetTooltip(CONST char* fmt, ...);
CIMGUI_API void             igSetTooltipV(CONST char* fmt, va_list args);
CIMGUI_API void             igBeginTooltip();
CIMGUI_API void             igEndTooltip();

// Widgets: Menus
CIMGUI_API bool             igBeginMainMenuBar();
CIMGUI_API void             igEndMainMenuBar();
CIMGUI_API bool             igBeginMenuBar();
CIMGUI_API void             igEndMenuBar();
CIMGUI_API bool             igBeginMenu(CONST char* label, bool enabled);
CIMGUI_API void             igEndMenu();
CIMGUI_API bool             igMenuItem(CONST char* label, CONST char* shortcut, bool selected, bool enabled);
CIMGUI_API bool             igMenuItemPtr(CONST char* label, CONST char* shortcut, bool* p_selected, bool enabled);

// Popup
CIMGUI_API void             igOpenPopup(CONST char* str_id);
CIMGUI_API bool             igBeginPopup(CONST char* str_id);
CIMGUI_API bool             igBeginPopupModal(CONST char* name, bool* p_opened, ImGuiWindowFlags extra_flags);
CIMGUI_API bool             igBeginPopupContextItem(CONST char* str_id, int mouse_button);
CIMGUI_API bool             igBeginPopupContextWindow(bool also_over_items, CONST char* str_id, int mouse_button);
CIMGUI_API bool             igBeginPopupContextVoid(CONST char* str_id, int mouse_button);
CIMGUI_API void             igEndPopup();
CIMGUI_API void             igCloseCurrentPopup();

// Logging: all text output from interface is redirected to tty/file/clipboard. Tree nodes are automatically opened.
CIMGUI_API void             igLogToTTY(int max_depth);
CIMGUI_API void             igLogToFile(int max_depth, CONST char* filename);
CIMGUI_API void             igLogToClipboard(int max_depth);
CIMGUI_API void             igLogFinish();
CIMGUI_API void             igLogButtons();
CIMGUI_API void             igLogText(CONST char* fmt, ...);

// Utilities
CIMGUI_API bool             igIsItemHovered();
CIMGUI_API bool             igIsItemHoveredRect();
CIMGUI_API bool             igIsItemActive();
CIMGUI_API bool             igIsItemVisible();
CIMGUI_API bool             igIsAnyItemHovered();
CIMGUI_API bool             igIsAnyItemActive();
CIMGUI_API void             igGetItemRectMin(struct ImVec2* pOut);
CIMGUI_API void             igGetItemRectMax(struct ImVec2* pOut);
CIMGUI_API void             igGetItemRectSize(struct ImVec2* pOut);
CIMGUI_API bool             igIsWindowHovered();
CIMGUI_API bool             igIsWindowFocused();
CIMGUI_API bool             igIsRootWindowFocused();
CIMGUI_API bool             igIsRootWindowOrAnyChildFocused();
CIMGUI_API bool             igIsRectVisible(CONST struct ImVec2 item_size);
CIMGUI_API bool             igIsPosHoveringAnyWindow(CONST struct ImVec2 pos);
CIMGUI_API float            igGetTime();
CIMGUI_API int              igGetFrameCount();
CIMGUI_API CONST char*      igGetStyleColName(ImGuiCol idx);
CIMGUI_API void             igCalcItemRectClosestPoint(struct ImVec2* pOut, CONST struct ImVec2 pos, bool on_edge, float outward);
CIMGUI_API void             igCalcTextSize(struct ImVec2* pOut, CONST char* text, CONST char* text_end, bool hide_text_after_double_hash, float wrap_width);
CIMGUI_API void             igCalcListClipping(int items_count, float items_height, int* out_items_display_start, int* out_items_display_end);

CIMGUI_API bool             igBeginChildFrame(ImGuiID id, CONST struct ImVec2 size, ImGuiWindowFlags extra_flags);
CIMGUI_API void             igEndChildFrame();

CIMGUI_API void             igColorConvertU32ToFloat4(ImVec4* pOut, ImU32 in);
CIMGUI_API ImU32            igColorConvertFloat4ToU32(CONST struct ImVec4 in);
CIMGUI_API void             igColorConvertRGBtoHSV(float r, float g, float b, float* out_h, float* out_s, float* out_v);
CIMGUI_API void             igColorConvertHSVtoRGB(float h, float s, float v, float* out_r, float* out_g, float* out_b);

CIMGUI_API bool             igIsKeyDown(int key_index);
CIMGUI_API bool             igIsKeyPressed(int key_index, bool repeat);
CIMGUI_API bool             igIsKeyReleased(int key_index);
CIMGUI_API bool             igIsMouseDown(int button);
CIMGUI_API bool             igIsMouseClicked(int button, bool repeat);
CIMGUI_API bool             igIsMouseDoubleClicked(int button);
CIMGUI_API bool             igIsMouseReleased(int button);
CIMGUI_API bool             igIsMouseHoveringWindow();
CIMGUI_API bool             igIsMouseHoveringAnyWindow();
CIMGUI_API bool             igIsMouseHoveringRect(CONST struct ImVec2 pos_min, CONST struct ImVec2 pos_max, bool clip);
CIMGUI_API bool             igIsMouseDragging(int button, float lock_threshold);
CIMGUI_API void             igGetMousePos(struct ImVec2* pOut);
CIMGUI_API void             igGetMousePosOnOpeningCurrentPopup(ImVec2* pOut);
CIMGUI_API void             igGetMouseDragDelta(struct ImVec2* pOut, int button, float lock_threshold);
CIMGUI_API void             igResetMouseDragDelta(int button);
CIMGUI_API ImGuiMouseCursor igGetMouseCursor();
CIMGUI_API void             igSetMouseCursor(ImGuiMouseCursor type);
CIMGUI_API void             igCaptureKeyboardFromApp();
CIMGUI_API void             igCaptureMouseFromApp();

// Helpers functions to access functions pointers in ImGui::GetIO()
CIMGUI_API void*            igMemAlloc(size_t sz);
CIMGUI_API void             igMemFree(void* ptr);
CIMGUI_API CONST char*      igGetClipboardText();
CIMGUI_API void             igSetClipboardText(CONST char* text);

// Internal state access - if you want to share ImGui state between modules (e.g. DLL) or allocate it yourself
CIMGUI_API CONST char*      igGetVersion();
CIMGUI_API void*            igGetInternalState();
CIMGUI_API size_t           igGetInternalStateSize();
CIMGUI_API void             igSetInternalState(void* state, bool construct);

CIMGUI_API void             ImFontAtlas_GetTexDataAsRGBA32(ImFontAtlas* atlas, unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel);
CIMGUI_API void             ImFontAtlas_GetTexDataAsAlpha8(ImFontAtlas* atlas, unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel);
CIMGUI_API void             ImFontAtlas_SetTexID(ImFontAtlas* atlas, void* tex);
CIMGUI_API ImFont*          ImFontAtlas_AddFont(ImFontAtlas* atlas, CONST ImFontConfig* font_cfg);
CIMGUI_API ImFont*          ImFontAtlas_AddFontDefault(ImFontAtlas* atlas, CONST ImFontConfig* font_cfg);
CIMGUI_API ImFont*          ImFontAtlas_AddFontFromFileTTF(ImFontAtlas* atlas, CONST char* filename, float size_pixels, CONST ImFontConfig* font_cfg, CONST ImWchar* glyph_ranges);
CIMGUI_API ImFont*          ImFontAtlas_AddFontFromMemoryTTF(ImFontAtlas* atlas, void* ttf_data, int ttf_size, float size_pixels, CONST ImFontConfig* font_cfg, CONST ImWchar* glyph_ranges);
CIMGUI_API ImFont*          ImFontAtlas_AddFontFromMemoryCompressedTTF(ImFontAtlas* atlas, CONST void* compressed_ttf_data, int compressed_ttf_size, float size_pixels, CONST ImFontConfig* font_cfg, CONST ImWchar* glyph_ranges);
CIMGUI_API ImFont*          ImFontAtlas_AddFontFromMemoryCompressedBase85TTF(ImFontAtlas* atlas, CONST char* compressed_ttf_data_base85, float size_pixels, CONST ImFontConfig* font_cfg, CONST ImWchar* glyph_ranges);
CIMGUI_API void             ImFontAtlas_ClearTexData(ImFontAtlas* atlas);
CIMGUI_API void             ImFontAtlas_Clear(ImFontAtlas* atlas);

CIMGUI_API void             ImGuiIO_AddInputCharacter(unsigned short c);
CIMGUI_API void             ImGuiIO_AddInputCharactersUTF8(CONST char* utf8_chars);
CIMGUI_API void             ImGuiIO_ClearInputCharacters();

//ImDrawData
CIMGUI_API void             ImDrawData_DeIndexAllBuffers(ImDrawData* drawData);

//ImDrawList
CIMGUI_API int              ImDrawList_GetVertexBufferSize(ImDrawList* list);
CIMGUI_API ImDrawVert*      ImDrawList_GetVertexPtr(ImDrawList* list, int n);
CIMGUI_API int              ImDrawList_GetIndexBufferSize(ImDrawList* list);
CIMGUI_API ImDrawIdx*       ImDrawList_GetIndexPtr(ImDrawList* list, int n);
CIMGUI_API int              ImDrawList_GetCmdSize(ImDrawList* list);
CIMGUI_API ImDrawCmd*       ImDrawList_GetCmdPtr(ImDrawList* list, int n);

CIMGUI_API void             ImDrawList_Clear(ImDrawList* list);
CIMGUI_API void             ImDrawList_ClearFreeMemory(ImDrawList* list);
CIMGUI_API void             ImDrawList_PushClipRect(ImDrawList* list, CONST struct ImVec4 clip_rect); // Scissoring. The values are x1, y1, x2, y2.
CIMGUI_API void             ImDrawList_PushClipRectFullScreen(ImDrawList* list);
CIMGUI_API void             ImDrawList_PopClipRect(ImDrawList* list);
CIMGUI_API void             ImDrawList_PushTextureID(ImDrawList* list, CONST ImTextureID texture_id);
CIMGUI_API void             ImDrawList_PopTextureID(ImDrawList* list);

// Primitives
CIMGUI_API void             ImDrawList_AddLine(ImDrawList* list, CONST struct ImVec2 a, CONST struct ImVec2 b, ImU32 col, float thickness);
CIMGUI_API void             ImDrawList_AddRect(ImDrawList* list, CONST struct ImVec2 a, CONST struct ImVec2 b, ImU32 col, float rounding, int rounding_corners);
CIMGUI_API void             ImDrawList_AddRectFilled(ImDrawList* list, CONST struct ImVec2 a, CONST struct ImVec2 b, ImU32 col, float rounding, int rounding_corners);
CIMGUI_API void             ImDrawList_AddRectFilledMultiColor(ImDrawList* list, CONST struct ImVec2 a, CONST struct ImVec2 b, ImU32 col_upr_left, ImU32 col_upr_right, ImU32 col_bot_right, ImU32 col_bot_left);
CIMGUI_API void             ImDrawList_AddTriangleFilled(ImDrawList* list, CONST struct ImVec2 a, CONST struct ImVec2 b, CONST struct ImVec2 c, ImU32 col);
CIMGUI_API void             ImDrawList_AddCircle(ImDrawList* list, CONST struct ImVec2 centre, float radius, ImU32 col, int num_segments);
CIMGUI_API void             ImDrawList_AddCircleFilled(ImDrawList* list, CONST struct ImVec2 centre, float radius, ImU32 col, int num_segments);
CIMGUI_API void             ImDrawList_AddText(ImDrawList* list, CONST struct ImVec2 pos, ImU32 col, CONST char* text_begin, CONST char* text_end);
CIMGUI_API void             ImDrawList_AddTextExt(ImDrawList* list, CONST ImFont* font, float font_size, CONST struct ImVec2 pos, ImU32 col, CONST char* text_begin, CONST char* text_end, float wrap_width, CONST ImVec4* cpu_fine_clip_rect);
CIMGUI_API void             ImDrawList_AddImage(ImDrawList* list, ImTextureID user_texture_id, CONST struct ImVec2 a, CONST struct ImVec2 b, CONST struct ImVec2 uv0, CONST struct ImVec2 uv1, ImU32 col);
CIMGUI_API void             ImDrawList_AddPolyline(ImDrawList* list, CONST ImVec2* points, CONST int num_points, ImU32 col, bool closed, float thickness, bool anti_aliased);
CIMGUI_API void             ImDrawList_AddConvexPolyFilled(ImDrawList* list, CONST ImVec2* points, CONST int num_points, ImU32 col, bool anti_aliased);
CIMGUI_API void             ImDrawList_AddBezierCurve(ImDrawList* list, CONST struct ImVec2 pos0, CONST struct ImVec2 cp0, CONST struct ImVec2 cp1, CONST struct ImVec2 pos1, ImU32 col, float thickness, int num_segments);

// Stateful path API, add points then finish with PathFill() or PathStroke()
CIMGUI_API void             ImDrawList_PathClear(ImDrawList* list);
CIMGUI_API void             ImDrawList_PathLineTo(ImDrawList* list, CONST struct ImVec2 pos);
CIMGUI_API void             ImDrawList_PathLineToMergeDuplicate(ImDrawList* list, CONST struct ImVec2 pos);
CIMGUI_API void             ImDrawList_PathFill(ImDrawList* list, ImU32 col);
CIMGUI_API void             ImDrawList_PathStroke(ImDrawList* list, ImU32 col, bool closed, float thickness);
CIMGUI_API void             ImDrawList_PathArcTo(ImDrawList* list, CONST struct ImVec2 centre, float radius, float a_min, float a_max, int num_segments);
CIMGUI_API void             ImDrawList_PathArcToFast(ImDrawList* list, CONST struct ImVec2 centre, float radius, int a_min_of_12, int a_max_of_12); // Use precomputed angles for a 12 steps circle
CIMGUI_API void             ImDrawList_PathBezierCurveTo(ImDrawList* list, CONST struct ImVec2 p1, CONST struct ImVec2 p2, CONST struct ImVec2 p3, int num_segments);
CIMGUI_API void             ImDrawList_PathRect(ImDrawList* list, CONST struct ImVec2 rect_min, CONST struct ImVec2 rect_max, float rounding, int rounding_corners);

// Channels
CIMGUI_API void             ImDrawList_ChannelsSplit(ImDrawList* list, int channels_count);
CIMGUI_API void             ImDrawList_ChannelsMerge(ImDrawList* list);
CIMGUI_API void             ImDrawList_ChannelsSetCurrent(ImDrawList* list, int channel_index);

// Advanced
CIMGUI_API void             ImDrawList_AddCallback(ImDrawList* list, ImDrawCallback callback, void* callback_data); // Your rendering function must check for 'UserCallback' in ImDrawCmd and call the function instead of rendering triangles.
CIMGUI_API void             ImDrawList_AddDrawCmd(ImDrawList* list); // This is useful if you need to forcefully create a new draw call (to allow for dependent rendering / blending). Otherwise primitives are merged into the same draw-call as much as possible

// Internal helpers
CIMGUI_API void             ImDrawList_PrimReserve(ImDrawList* list, int idx_count, int vtx_count);
CIMGUI_API void             ImDrawList_PrimRect(ImDrawList* list, CONST struct ImVec2 a, CONST struct ImVec2 b, ImU32 col);
CIMGUI_API void             ImDrawList_PrimRectUV(ImDrawList* list, CONST struct ImVec2 a, CONST struct ImVec2 b, CONST struct ImVec2 uv_a, CONST struct ImVec2 uv_b, ImU32 col);
CIMGUI_API void             ImDrawList_PrimVtx(ImDrawList* list, CONST struct ImVec2 pos, CONST struct ImVec2 uv, ImU32 col);
CIMGUI_API void             ImDrawList_PrimWriteVtx(ImDrawList* list, CONST struct ImVec2 pos, CONST struct ImVec2 uv, ImU32 col);
CIMGUI_API void             ImDrawList_PrimWriteIdx(ImDrawList* list, ImDrawIdx idx);
CIMGUI_API void             ImDrawList_UpdateClipRect(ImDrawList* list);
CIMGUI_API void             ImDrawList_UpdateTextureID(ImDrawList* list);