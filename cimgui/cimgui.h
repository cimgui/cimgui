
#include <stdio.h>

#if defined _WIN32 || defined __CYGWIN__
#define API __declspec(dllexport)
#ifndef __GNUC__
#define snprintf sprintf_s
#endif
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

struct ImGuiIO;
struct ImGuiStyle;
struct ImDrawData;
struct ImVec2;
struct ImVec4;
struct ImGuiTextEditCallbackData;
struct ImGuiSizeConstraintCallbackData;
struct ImDrawList;
struct ImGuiStorage;
struct ImFont;
struct ImFontConfig;
struct ImFontAtlas;
struct ImDrawCmd;

typedef unsigned short ImDrawIdx;
typedef unsigned int ImU32;
typedef unsigned short ImWchar;     
typedef void* ImTextureID;       
typedef ImU32 ImGuiID;              
typedef int ImGuiCol;               
typedef int ImGuiStyleVar;          
typedef int ImGuiKey;               
typedef int ImGuiAlign;             
typedef int ImGuiColorEditMode;     
typedef int ImGuiMouseCursor;       
typedef int ImGuiWindowFlags;       
typedef int ImGuiSetCond;           
typedef int ImGuiInputTextFlags;    
typedef int ImGuiSelectableFlags;   
typedef int ImGuiTreeNodeFlags;     
typedef int (*ImGuiTextEditCallback)(struct ImGuiTextEditCallbackData *data);
typedef void (*ImGuiSizeConstraintCallback)(struct ImGuiSizeConstraintCallbackData* data);
typedef void (*ImDrawCallback)(CONST struct ImDrawList* parent_list, CONST struct ImDrawCmd* cmd);

#ifdef CIMGUI_DEFINE_ENUMS_AND_STRUCTS
struct ImVec2 {
    float x, y;
};

struct ImVec4 {
    float x, y, z, w;
};

enum {
    ImGuiWindowFlags_NoTitleBar             = 1 << 0,
    ImGuiWindowFlags_NoResize               = 1 << 1,
    ImGuiWindowFlags_NoMove                 = 1 << 2,
    ImGuiWindowFlags_NoScrollbar            = 1 << 3,
    ImGuiWindowFlags_NoScrollWithMouse      = 1 << 4,
    ImGuiWindowFlags_NoCollapse             = 1 << 5,
    ImGuiWindowFlags_AlwaysAutoResize       = 1 << 6,
    ImGuiWindowFlags_ShowBorders            = 1 << 7,
    ImGuiWindowFlags_NoSavedSettings        = 1 << 8,
    ImGuiWindowFlags_NoInputs               = 1 << 9,
    ImGuiWindowFlags_MenuBar                = 1 << 10,
    ImGuiWindowFlags_HorizontalScrollbar    = 1 << 11,
    ImGuiWindowFlags_NoFocusOnAppearing     = 1 << 12,
    ImGuiWindowFlags_NoBringToFrontOnFocus  = 1 << 13,
    ImGuiWindowFlags_AlwaysVerticalScrollbar = 1 << 14,
    ImGuiWindowFlags_AlwaysHorizontalScrollbar = 1 << 15,
    ImGuiWindowFlags_AlwaysUseWindowPadding = 1 << 16
};

enum {
    ImGuiInputTextFlags_CharsDecimal        = 1 << 0,
    ImGuiInputTextFlags_CharsHexadecimal    = 1 << 1,
    ImGuiInputTextFlags_CharsUppercase      = 1 << 2,
    ImGuiInputTextFlags_CharsNoBlank        = 1 << 3,
    ImGuiInputTextFlags_AutoSelectAll       = 1 << 4,
    ImGuiInputTextFlags_EnterReturnsTrue    = 1 << 5,
    ImGuiInputTextFlags_CallbackCompletion  = 1 << 6,
    ImGuiInputTextFlags_CallbackHistory     = 1 << 7,
    ImGuiInputTextFlags_CallbackAlways      = 1 << 8,
    ImGuiInputTextFlags_CallbackCharFilter  = 1 << 9,
    ImGuiInputTextFlags_AllowTabInput       = 1 << 10,
    ImGuiInputTextFlags_CtrlEnterForNewLine = 1 << 11,
    ImGuiInputTextFlags_NoHorizontalScroll  = 1 << 12,
    ImGuiInputTextFlags_AlwaysInsertMode    = 1 << 13,
    ImGuiInputTextFlags_ReadOnly            = 1 << 14,
    ImGuiInputTextFlags_Password            = 1 << 15
};

enum {
    ImGuiTreeNodeFlags_Selected             = 1 << 0,
    ImGuiTreeNodeFlags_Framed               = 1 << 1,
    ImGuiTreeNodeFlags_AllowOverlapMode     = 1 << 2,
    ImGuiTreeNodeFlags_NoTreePushOnOpen     = 1 << 3,
    ImGuiTreeNodeFlags_NoAutoOpenOnLog      = 1 << 4,
    ImGuiTreeNodeFlags_DefaultOpen          = 1 << 5,
    ImGuiTreeNodeFlags_OpenOnDoubleClick    = 1 << 6,
    ImGuiTreeNodeFlags_OpenOnArrow          = 1 << 7,
    ImGuiTreeNodeFlags_Leaf                 = 1 << 8,
    ImGuiTreeNodeFlags_Bullet               = 1 << 9,
    ImGuiTreeNodeFlags_CollapsingHeader     = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_NoAutoOpenOnLog
};

enum {
    ImGuiSelectableFlags_DontClosePopups    = 1 << 0,
    ImGuiSelectableFlags_SpanAllColumns     = 1 << 1,
    ImGuiSelectableFlags_AllowDoubleClick   = 1 << 2
};

enum {
    ImGuiKey_Tab,
    ImGuiKey_LeftArrow,
    ImGuiKey_RightArrow,
    ImGuiKey_UpArrow,
    ImGuiKey_DownArrow,
    ImGuiKey_PageUp,
    ImGuiKey_PageDown,
    ImGuiKey_Home,
    ImGuiKey_End,
    ImGuiKey_Delete,
    ImGuiKey_Backspace,
    ImGuiKey_Enter,
    ImGuiKey_Escape,
    ImGuiKey_A,
    ImGuiKey_C,
    ImGuiKey_V,
    ImGuiKey_X,
    ImGuiKey_Y,
    ImGuiKey_Z,
    ImGuiKey_COUNT
};

enum {
    ImGuiCol_Text,
    ImGuiCol_TextDisabled,
    ImGuiCol_WindowBg,
    ImGuiCol_ChildWindowBg,
    ImGuiCol_PopupBg,
    ImGuiCol_Border,
    ImGuiCol_BorderShadow,
    ImGuiCol_FrameBg,
    ImGuiCol_FrameBgHovered,
    ImGuiCol_FrameBgActive,
    ImGuiCol_TitleBg,
    ImGuiCol_TitleBgCollapsed,
    ImGuiCol_TitleBgActive,
    ImGuiCol_MenuBarBg,
    ImGuiCol_ScrollbarBg,
    ImGuiCol_ScrollbarGrab,
    ImGuiCol_ScrollbarGrabHovered,
    ImGuiCol_ScrollbarGrabActive,
    ImGuiCol_ComboBg,
    ImGuiCol_CheckMark,
    ImGuiCol_SliderGrab,
    ImGuiCol_SliderGrabActive,
    ImGuiCol_Button,
    ImGuiCol_ButtonHovered,
    ImGuiCol_ButtonActive,
    ImGuiCol_Header,
    ImGuiCol_HeaderHovered,
    ImGuiCol_HeaderActive,
    ImGuiCol_Column,
    ImGuiCol_ColumnHovered,
    ImGuiCol_ColumnActive,
    ImGuiCol_ResizeGrip,
    ImGuiCol_ResizeGripHovered,
    ImGuiCol_ResizeGripActive,
    ImGuiCol_CloseButton,
    ImGuiCol_CloseButtonHovered,
    ImGuiCol_CloseButtonActive,
    ImGuiCol_PlotLines,
    ImGuiCol_PlotLinesHovered,
    ImGuiCol_PlotHistogram,
    ImGuiCol_PlotHistogramHovered,
    ImGuiCol_TextSelectedBg,
    ImGuiCol_ModalWindowDarkening,
    ImGuiCol_COUNT
};

enum {
    ImGuiStyleVar_Alpha,
    ImGuiStyleVar_WindowPadding,
    ImGuiStyleVar_WindowRounding,
    ImGuiStyleVar_WindowMinSize,
    ImGuiStyleVar_ChildWindowRounding,
    ImGuiStyleVar_FramePadding,
    ImGuiStyleVar_FrameRounding,
    ImGuiStyleVar_ItemSpacing,
    ImGuiStyleVar_ItemInnerSpacing,
    ImGuiStyleVar_IndentSpacing,
    ImGuiStyleVar_GrabMinSize
};

enum {
    ImGuiAlign_Left     = 1 << 0,
    ImGuiAlign_Center   = 1 << 1,
    ImGuiAlign_Right    = 1 << 2,
    ImGuiAlign_Top      = 1 << 3,
    ImGuiAlign_VCenter  = 1 << 4,
    ImGuiAlign_Default  = ImGuiAlign_Left | ImGuiAlign_Top
};

enum {
    ImGuiColorEditMode_UserSelect = -2,
    ImGuiColorEditMode_UserSelectShowButton = -1,
    ImGuiColorEditMode_RGB = 0,
    ImGuiColorEditMode_HSV = 1,
    ImGuiColorEditMode_HEX = 2
};

enum {
    ImGuiMouseCursor_Arrow = 0,
    ImGuiMouseCursor_TextInput,
    ImGuiMouseCursor_Move,
    ImGuiMouseCursor_ResizeNS,
    ImGuiMouseCursor_ResizeEW,
    ImGuiMouseCursor_ResizeNESW,
    ImGuiMouseCursor_ResizeNWSE,
    ImGuiMouseCursor_Count_
};

enum {
    ImGuiSetCond_Always        = 1 << 0,
    ImGuiSetCond_Once          = 1 << 1,
    ImGuiSetCond_FirstUseEver  = 1 << 2,
    ImGuiSetCond_Appearing     = 1 << 3
};

struct ImGuiStyle {
    float          Alpha;
    struct ImVec2  WindowPadding;
    struct ImVec2  WindowMinSize;
    float          WindowRounding;
    ImGuiAlign     WindowTitleAlign;
    float          ChildWindowRounding;
    struct ImVec2  FramePadding;
    float          FrameRounding;
    struct ImVec2  ItemSpacing;
    struct ImVec2  ItemInnerSpacing;
    struct ImVec2  TouchExtraPadding;
    float          IndentSpacing;
    float          ColumnsMinSpacing;
    float          ScrollbarSize;
    float          ScrollbarRounding;
    float          GrabMinSize;
    float          GrabRounding;
    struct ImVec2  DisplayWindowPadding;
    struct ImVec2  DisplaySafeAreaPadding;
    bool           AntiAliasedLines;
    bool           AntiAliasedShapes;
    float          CurveTessellationTol;
    struct ImVec4  Colors[ImGuiCol_COUNT];
};

struct ImGuiIO {
    struct ImVec2        DisplaySize;
    float                DeltaTime;
    float                IniSavingRate;
    const char*          IniFilename;
    const char*          LogFilename;
    float                MouseDoubleClickTime;
    float                MouseDoubleClickMaxDist;
    float                MouseDragThreshold;
    int                  KeyMap[ImGuiKey_COUNT];
    float                KeyRepeatDelay;
    float                KeyRepeatRate;
    void*                UserData;
    struct ImFontAtlas*  Fonts;
    float                FontGlobalScale;
    bool                 FontAllowUserScaling;
    struct ImVec2        DisplayFramebufferScale;
    struct ImVec2        DisplayVisibleMin;
    struct ImVec2        DisplayVisibleMax;
    bool                 WordMovementUsesAltKey;
    bool                 ShortcutsUseSuperKey;
    bool                 DoubleClickSelectsWord;
    bool                 MultiSelectUsesSuperKey;
    void                 (*RenderDrawListsFn)(struct ImDrawData* data);
    const char*          (*GetClipboardTextFn)();
    void                 (*SetClipboardTextFn)(const char* text);
    void*                (*MemAllocFn)(size_t sz);
    void                 (*MemFreeFn)(void* ptr);
    void                 (*ImeSetInputScreenPosFn)(int x, int y);
    void*                ImeWindowHandle;
    struct ImVec2        MousePos;
    bool                 MouseDown[5];
    float                MouseWheel;
    bool                 MouseDrawCursor;
    bool                 KeyCtrl;
    bool                 KeyShift;
    bool                 KeyAlt;
    bool                 KeySuper;
    bool                 KeysDown[512];
    ImWchar              InputCharacters[16 + 1];
    bool                 WantCaptureMouse;
    bool                 WantCaptureKeyboard;
    bool                 WantTextInput;
    float                Framerate;
    int                  MetricsAllocs;
    int                  MetricsRenderVertices;
    int                  MetricsRenderIndices;
    int                  MetricsActiveWindows;
    struct ImVec2        MousePosPrev;
    struct ImVec2        MouseDelta;
    bool                 MouseClicked[5];
    struct ImVec2        MouseClickedPos[5];
    float                MouseClickedTime[5];
    bool                 MouseDoubleClicked[5];
    bool                 MouseReleased[5];
    bool                 MouseDownOwned[5];
    float                MouseDownDuration[5];
    float                MouseDownDurationPrev[5];
    float                MouseDragMaxDistanceSqr[5];
    float                KeysDownDuration[512];
    float                KeysDownDurationPrev[512];
};

struct ImGuiTextEditCallbackData {
    ImGuiInputTextFlags  EventFlag;
    ImGuiInputTextFlags  Flags;
    void*                UserData;
    bool                 ReadOnly;
    ImWchar              EventChar;
    ImGuiKey             EventKey;
    char*                Buf;
    int                  BufTextLen;
    int                  BufSize;
    bool                 BufDirty;
    int                  CursorPos;
    int                  SelectionStart;
    int                  SelectionEnd;
};

struct ImGuiSizeConstraintCallbackData {
    void*          UserData;
    struct ImVec2  Pos;
    struct ImVec2  CurrentSize;
    struct ImVec2  DesiredSize;
};

struct ImDrawCmd {
    unsigned int    ElemCount;
    struct ImVec4   ClipRect;
    ImTextureID     TextureId;
    ImDrawCallback  UserCallback;
    void*           UserCallbackData;
};

struct ImDrawData {
    bool                 Valid;
    struct ImDrawList**  CmdLists;
    int                  CmdListsCount;
    int                  TotalVtxCount;
    int                  TotalIdxCount;
};

struct ImFontConfig {
    void*           FontData;
    int             FontDataSize;
    bool            FontDataOwnedByAtlas;
    int             FontNo;
    float           SizePixels;
    int             OversampleH, OversampleV;
    bool            PixelSnapH;
    struct ImVec2   GlyphExtraSpacing;
    const ImWchar*  GlyphRanges;
    bool            MergeMode;
    bool            MergeGlyphCenterV;
    char            Name[32];
    struct ImFont*  DstFont;
};
#endif // CIMGUI_DEFINE_ENUMS_AND_STRUCTS

CIMGUI_API struct ImGuiIO*         igGetIO();
CIMGUI_API struct ImGuiStyle*      igGetStyle();
CIMGUI_API struct ImDrawData*      igGetDrawData();
CIMGUI_API void                    igNewFrame();
CIMGUI_API void                    igRender();
CIMGUI_API void                    igShutdown();
CIMGUI_API void                    igShowUserGuide();
CIMGUI_API void                    igShowStyleEditor(struct ImGuiStyle* ref);
CIMGUI_API void                    igShowTestWindow(bool* opened);
CIMGUI_API void                    igShowMetricsWindow(bool* opened);

// Window
CIMGUI_API bool             igBegin(CONST char* name, bool* p_open, ImGuiWindowFlags flags);
CIMGUI_API bool             igBegin2(CONST char* name, bool* p_open, CONST struct ImVec2 size_on_first_use, float bg_alpha, ImGuiWindowFlags flags);
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
CIMGUI_API struct ImDrawList*      igGetWindowDrawList();
CIMGUI_API void             igGetWindowPos(struct ImVec2* out);
CIMGUI_API void             igGetWindowSize(struct ImVec2* out);
CIMGUI_API float            igGetWindowWidth();
CIMGUI_API float            igGetWindowHeight();
CIMGUI_API bool             igIsWindowCollapsed();
CIMGUI_API void             igSetWindowFontScale(float scale);

CIMGUI_API void             igSetNextWindowPos(CONST struct ImVec2 pos, ImGuiSetCond cond);
CIMGUI_API void             igSetNextWindowPosCenter(ImGuiSetCond cond);
CIMGUI_API void             igSetNextWindowSize(CONST struct ImVec2 size, ImGuiSetCond cond);
CIMGUI_API void             igSetNextWindowSizeConstraints(CONST struct ImVec2 size_min, CONST struct ImVec2 size_max, ImGuiSizeConstraintCallback custom_callback, void* custom_callback_data);
CIMGUI_API void             igSetNextWindowContentSize(CONST struct ImVec2 size);
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
CIMGUI_API void             igSetScrollHere(float center_y_ratio);
CIMGUI_API void             igSetScrollFromPosY(float pos_y, float center_y_ratio);
CIMGUI_API void             igSetKeyboardFocusHere(int offset);
CIMGUI_API void             igSetStateStorage(struct ImGuiStorage* tree);
CIMGUI_API struct ImGuiStorage*    igGetStateStorage();

// Parameters stacks (shared)
CIMGUI_API void             igPushFont(struct ImFont* font);
CIMGUI_API void             igPopFont();
CIMGUI_API void             igPushStyleColor(ImGuiCol idx, CONST struct ImVec4 col);
CIMGUI_API void             igPopStyleColor(int count);
CIMGUI_API void             igPushStyleVar(ImGuiStyleVar idx, float val);
CIMGUI_API void             igPushStyleVarVec(ImGuiStyleVar idx, CONST struct ImVec2 val);
CIMGUI_API void             igPopStyleVar(int count);
CIMGUI_API struct ImFont*          igGetFont();
CIMGUI_API float            igGetFontSize();
CIMGUI_API void             igGetFontTexUvWhitePixel(struct ImVec2* pOut);
CIMGUI_API ImU32            igGetColorU32(ImGuiCol idx, float alpha_mul);
CIMGUI_API ImU32            igGetColorU32Vec(CONST struct ImVec4* col);


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
CIMGUI_API void             igSeparator();
CIMGUI_API void             igSameLine(float pos_x, float spacing_w);
CIMGUI_API void             igNewLine();
CIMGUI_API void             igSpacing();
CIMGUI_API void             igDummy(CONST struct ImVec2* size);
CIMGUI_API void             igIndent(float indent_w);
CIMGUI_API void             igUnindent(float indent_w);
CIMGUI_API void             igBeginGroup();
CIMGUI_API void             igEndGroup();
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

//Columns
CIMGUI_API void             igColumns(int count, CONST char* id, bool border);
CIMGUI_API void             igNextColumn();
CIMGUI_API int              igGetColumnIndex();
CIMGUI_API float            igGetColumnOffset(int column_index);
CIMGUI_API void             igSetColumnOffset(int column_index, float offset_x);
CIMGUI_API float            igGetColumnWidth(int column_index);
CIMGUI_API int              igGetColumnsCount();

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
CIMGUI_API void             igProgressBar(float fraction, CONST struct ImVec2* size_arg, CONST char* overlay);


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
CIMGUI_API bool             igDragFloatRange2(CONST char* label, float* v_current_min, float* v_current_max, float v_speed, float v_min, float v_max, CONST char* display_format, CONST char* display_format_max, float power);
CIMGUI_API bool             igDragInt(CONST char* label, int* v, float v_speed, int v_min, int v_max, CONST char* display_format);                                       // If v_max >= v_max we have no bound
CIMGUI_API bool             igDragInt2(CONST char* label, int v[2], float v_speed, int v_min, int v_max, CONST char* display_format);
CIMGUI_API bool             igDragInt3(CONST char* label, int v[3], float v_speed, int v_min, int v_max, CONST char* display_format);
CIMGUI_API bool             igDragInt4(CONST char* label, int v[4], float v_speed, int v_min, int v_max, CONST char* display_format);
CIMGUI_API bool             igDragIntRange2(CONST char* label, int* v_current_min, int* v_current_max, float v_speed, int v_min, int v_max, CONST char* display_format, CONST char* display_format_max);


// Widgets: Input
CIMGUI_API bool             igInputText(CONST char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags, ImGuiTextEditCallback callback, void* user_data);
CIMGUI_API bool             igInputTextMultiline(CONST char* label, char* buf, size_t buf_size, CONST struct ImVec2 size, ImGuiInputTextFlags flags, ImGuiTextEditCallback callback, void* user_data);
CIMGUI_API bool             igInputFloat(CONST char* label, float* v, float step, float step_fast, int decimal_precision, ImGuiInputTextFlags extra_flags);
CIMGUI_API bool             igInputFloat2(CONST char* label, float v[2], int decimal_precision, ImGuiInputTextFlags extra_flags);
CIMGUI_API bool             igInputFloat3(CONST char* label, float v[3], int decimal_precision, ImGuiInputTextFlags extra_flags);
CIMGUI_API bool             igInputFloat4(CONST char* label, float v[4], int decimal_precision, ImGuiInputTextFlags extra_flags);
CIMGUI_API bool             igInputInt(CONST char* label, int* v, int step, int step_fast, ImGuiInputTextFlags extra_flags);
CIMGUI_API bool             igInputInt2(CONST char* label, int v[2], ImGuiInputTextFlags extra_flags);
CIMGUI_API bool             igInputInt3(CONST char* label, int v[3], ImGuiInputTextFlags extra_flags);
CIMGUI_API bool             igInputInt4(CONST char* label, int v[4], ImGuiInputTextFlags extra_flags);

// Widgets: Trees
CIMGUI_API bool             igTreeNode(CONST char* label);
CIMGUI_API bool             igTreeNodeStr(CONST char* str_id, CONST char* fmt, ...);
CIMGUI_API bool             igTreeNodePtr(CONST void* ptr_id, CONST char* fmt, ...);
CIMGUI_API bool             igTreeNodeStrV(CONST char* str_id, CONST char* fmt, va_list args);
CIMGUI_API bool             igTreeNodePtrV(CONST void* ptr_id, CONST char* fmt, va_list args);
CIMGUI_API bool             igTreeNodeEx(CONST char* label, ImGuiTreeNodeFlags flags);
CIMGUI_API bool             igTreeNodeExStr(CONST char* str_id, ImGuiTreeNodeFlags flags, CONST char* fmt, ...);
CIMGUI_API bool             igTreeNodeExPtr(CONST void* ptr_id, ImGuiTreeNodeFlags flags, CONST char* fmt, ...);
CIMGUI_API bool             igTreeNodeExV(CONST char* str_id, ImGuiTreeNodeFlags flags, CONST char* fmt, va_list args);
CIMGUI_API bool             igTreeNodeExVPtr(CONST void* ptr_id, ImGuiTreeNodeFlags flags, CONST char* fmt, va_list args);
CIMGUI_API void             igTreePushStr(CONST char* str_id);
CIMGUI_API void             igTreePushPtr(CONST void* ptr_id);
CIMGUI_API void             igTreePop();
CIMGUI_API void             igTreeAdvanceToLabelPos();
CIMGUI_API float            igGetTreeNodeToLabelSpacing();
CIMGUI_API void             igSetNextTreeNodeOpen(bool opened, ImGuiSetCond cond);
CIMGUI_API bool             igCollapsingHeader(CONST char* label, ImGuiTreeNodeFlags flags);
CIMGUI_API bool             igCollapsingHeaderEx(CONST char* label, bool* p_open, ImGuiTreeNodeFlags flags);

// Widgets: Selectable / Lists
CIMGUI_API bool             igSelectable(CONST char* label, bool selected, ImGuiSelectableFlags flags, CONST struct ImVec2 size);
CIMGUI_API bool             igSelectableEx(CONST char* label, bool* p_selected, ImGuiSelectableFlags flags, CONST struct ImVec2 size);
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
CIMGUI_API bool             igBeginPopupModal(CONST char* name, bool* p_open, ImGuiWindowFlags extra_flags);
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

// Clipping
CIMGUI_API void             igPushClipRect(CONST struct ImVec2 clip_rect_min, CONST struct ImVec2 clip_rect_max, bool intersect_with_current_clip_rect);
CIMGUI_API void             igPopClipRect();

// Utilities
CIMGUI_API bool             igIsItemHovered();
CIMGUI_API bool             igIsItemHoveredRect();
CIMGUI_API bool             igIsItemActive();
CIMGUI_API bool             igIsItemClicked(int mouse_button);
CIMGUI_API bool             igIsItemVisible();
CIMGUI_API bool             igIsAnyItemHovered();
CIMGUI_API bool             igIsAnyItemActive();
CIMGUI_API void             igGetItemRectMin(struct ImVec2* pOut);
CIMGUI_API void             igGetItemRectMax(struct ImVec2* pOut);
CIMGUI_API void             igGetItemRectSize(struct ImVec2* pOut);
CIMGUI_API void             igSetItemAllowOverlap();
CIMGUI_API bool             igIsWindowHovered();
CIMGUI_API bool             igIsWindowFocused();
CIMGUI_API bool             igIsRootWindowFocused();
CIMGUI_API bool             igIsRootWindowOrAnyChildFocused();
CIMGUI_API bool             igIsRootWindowOrAnyChildHovered();
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

CIMGUI_API void             igColorConvertU32ToFloat4(struct ImVec4* pOut, ImU32 in);
CIMGUI_API ImU32            igColorConvertFloat4ToU32(CONST struct ImVec4 in);
CIMGUI_API void             igColorConvertRGBtoHSV(float r, float g, float b, float* out_h, float* out_s, float* out_v);
CIMGUI_API void             igColorConvertHSVtoRGB(float h, float s, float v, float* out_r, float* out_g, float* out_b);

CIMGUI_API int              igGetKeyIndex(ImGuiKey key);
CIMGUI_API bool             igIsKeyDown(int key_index);
CIMGUI_API bool             igIsKeyPressed(int key_index, bool repeat);
CIMGUI_API bool             igIsKeyReleased(int key_index);
CIMGUI_API bool             igIsMouseDown(int button);
CIMGUI_API bool             igIsMouseClicked(int button, bool repeat);
CIMGUI_API bool             igIsMouseDoubleClicked(int button);
CIMGUI_API bool             igIsMouseReleased(int button);
CIMGUI_API bool             igIsMouseHoveringWindow();
CIMGUI_API bool             igIsMouseHoveringAnyWindow();
CIMGUI_API bool             igIsMouseHoveringRect(CONST struct ImVec2 r_min, CONST struct ImVec2 r_max, bool clip);
CIMGUI_API bool             igIsMouseDragging(int button, float lock_threshold);
CIMGUI_API void             igGetMousePos(struct ImVec2* pOut);
CIMGUI_API void             igGetMousePosOnOpeningCurrentPopup(struct ImVec2* pOut);
CIMGUI_API void             igGetMouseDragDelta(struct ImVec2* pOut, int button, float lock_threshold);
CIMGUI_API void             igResetMouseDragDelta(int button);
CIMGUI_API ImGuiMouseCursor igGetMouseCursor();
CIMGUI_API void             igSetMouseCursor(ImGuiMouseCursor type);
CIMGUI_API void             igCaptureKeyboardFromApp(bool capture);
CIMGUI_API void             igCaptureMouseFromApp(bool capture);

// Helpers functions to access functions pointers in ImGui::GetIO()
CIMGUI_API void*            igMemAlloc(size_t sz);
CIMGUI_API void             igMemFree(void* ptr);
CIMGUI_API CONST char*      igGetClipboardText();
CIMGUI_API void             igSetClipboardText(CONST char* text);

// Internal state access - if you want to share ImGui state between modules (e.g. DLL) or allocate it yourself
CIMGUI_API CONST char*             igGetVersion();
CIMGUI_API struct ImGuiContext*    igCreateContext(void* (*malloc_fn)(size_t), void (*free_fn)(void*));
CIMGUI_API void                    igDestroyContext(struct ImGuiContext* ctx);
CIMGUI_API struct ImGuiContext*    igGetCurrentContext();
CIMGUI_API void                    igSetCurrentContext(struct ImGuiContext* ctx);

CIMGUI_API void             ImFontConfig_DefaultConstructor(struct ImFontConfig* config);

CIMGUI_API void             ImFontAtlas_GetTexDataAsRGBA32(struct ImFontAtlas* atlas, unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel);
CIMGUI_API void             ImFontAtlas_GetTexDataAsAlpha8(struct ImFontAtlas* atlas, unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel);
CIMGUI_API void             ImFontAtlas_SetTexID(struct ImFontAtlas* atlas, void* tex);
CIMGUI_API struct ImFont*   ImFontAtlas_AddFont(struct ImFontAtlas* atlas, CONST struct ImFontConfig* font_cfg);
CIMGUI_API struct ImFont*   ImFontAtlas_AddFontDefault(struct ImFontAtlas* atlas, CONST struct ImFontConfig* font_cfg);
CIMGUI_API struct ImFont*   ImFontAtlas_AddFontFromFileTTF(struct ImFontAtlas* atlas, CONST char* filename, float size_pixels, CONST struct ImFontConfig* font_cfg, CONST ImWchar* glyph_ranges);
CIMGUI_API struct ImFont*   ImFontAtlas_AddFontFromMemoryTTF(struct ImFontAtlas* atlas, void* ttf_data, int ttf_size, float size_pixels, CONST struct ImFontConfig* font_cfg, CONST ImWchar* glyph_ranges);
CIMGUI_API struct ImFont*   ImFontAtlas_AddFontFromMemoryCompressedTTF(struct ImFontAtlas* atlas, CONST void* compressed_ttf_data, int compressed_ttf_size, float size_pixels, CONST struct ImFontConfig* font_cfg, CONST ImWchar* glyph_ranges);
CIMGUI_API struct ImFont*   ImFontAtlas_AddFontFromMemoryCompressedBase85TTF(struct ImFontAtlas* atlas, CONST char* compressed_ttf_data_base85, float size_pixels, CONST struct ImFontConfig* font_cfg, CONST ImWchar* glyph_ranges);
CIMGUI_API void             ImFontAtlas_ClearTexData(struct ImFontAtlas* atlas);
CIMGUI_API void             ImFontAtlas_Clear(struct ImFontAtlas* atlas);

CIMGUI_API void             ImGuiIO_AddInputCharacter(unsigned short c);
CIMGUI_API void             ImGuiIO_AddInputCharactersUTF8(CONST char* utf8_chars);
CIMGUI_API void             ImGuiIO_ClearInputCharacters();

//ImDrawData
CIMGUI_API void                 ImDrawData_DeIndexAllBuffers(struct ImDrawData* drawData);

//ImDrawList
CIMGUI_API int                  ImDrawList_GetVertexBufferSize(struct ImDrawList* list);
CIMGUI_API struct ImDrawVert*   ImDrawList_GetVertexPtr(struct ImDrawList* list, int n);
CIMGUI_API int                  ImDrawList_GetIndexBufferSize(struct ImDrawList* list);
CIMGUI_API ImDrawIdx*           ImDrawList_GetIndexPtr(struct ImDrawList* list, int n);
CIMGUI_API int                  ImDrawList_GetCmdSize(struct ImDrawList* list);
CIMGUI_API struct ImDrawCmd*    ImDrawList_GetCmdPtr(struct ImDrawList* list, int n);

CIMGUI_API void             ImDrawList_Clear(struct ImDrawList* list);
CIMGUI_API void             ImDrawList_ClearFreeMemory(struct ImDrawList* list);
CIMGUI_API void             ImDrawList_PushClipRect(struct ImDrawList* list, struct ImVec2 clip_rect_min, struct ImVec2 clip_rect_max, bool intersect_with_current_clip_rect);
CIMGUI_API void             ImDrawList_PushClipRectFullScreen(struct ImDrawList* list);
CIMGUI_API void             ImDrawList_PopClipRect(struct ImDrawList* list);
CIMGUI_API void             ImDrawList_PushTextureID(struct ImDrawList* list, CONST ImTextureID texture_id);
CIMGUI_API void             ImDrawList_PopTextureID(struct ImDrawList* list);

// Primitives
CIMGUI_API void             ImDrawList_AddLine(struct ImDrawList* list, CONST struct ImVec2 a, CONST struct ImVec2 b, ImU32 col, float thickness);
CIMGUI_API void             ImDrawList_AddRect(struct ImDrawList* list, CONST struct ImVec2 a, CONST struct ImVec2 b, ImU32 col, float rounding, int rounding_corners, float thickness);
CIMGUI_API void             ImDrawList_AddRectFilled(struct ImDrawList* list, CONST struct ImVec2 a, CONST struct ImVec2 b, ImU32 col, float rounding, int rounding_corners);
CIMGUI_API void             ImDrawList_AddRectFilledMultiColor(struct ImDrawList* list, CONST struct ImVec2 a, CONST struct ImVec2 b, ImU32 col_upr_left, ImU32 col_upr_right, ImU32 col_bot_right, ImU32 col_bot_left);
CIMGUI_API void             ImDrawList_AddQuad(struct ImDrawList* list, CONST struct ImVec2 a, CONST struct ImVec2 b, CONST struct ImVec2 c, CONST struct ImVec2 d, ImU32 col, float thickness);
CIMGUI_API void             ImDrawList_AddQuadFilled(struct ImDrawList* list, CONST struct ImVec2 a, CONST struct ImVec2 b, CONST struct ImVec2 c, CONST struct ImVec2 d, ImU32 col);
CIMGUI_API void             ImDrawList_AddTriangle(struct ImDrawList* list, CONST struct ImVec2 a, CONST struct ImVec2 b, CONST struct ImVec2 c, ImU32 col, float thickness);
CIMGUI_API void             ImDrawList_AddTriangleFilled(struct ImDrawList* list, CONST struct ImVec2 a, CONST struct ImVec2 b, CONST struct ImVec2 c, ImU32 col);
CIMGUI_API void             ImDrawList_AddCircle(struct ImDrawList* list, CONST struct ImVec2 centre, float radius, ImU32 col, int num_segments, float thickness);
CIMGUI_API void             ImDrawList_AddCircleFilled(struct ImDrawList* list, CONST struct ImVec2 centre, float radius, ImU32 col, int num_segments);
CIMGUI_API void             ImDrawList_AddText(struct ImDrawList* list, CONST struct ImVec2 pos, ImU32 col, CONST char* text_begin, CONST char* text_end);
CIMGUI_API void             ImDrawList_AddTextExt(struct ImDrawList* list, CONST struct ImFont* font, float font_size, CONST struct ImVec2 pos, ImU32 col, CONST char* text_begin, CONST char* text_end, float wrap_width, CONST struct ImVec4* cpu_fine_clip_rect);
CIMGUI_API void             ImDrawList_AddImage(struct ImDrawList* list, ImTextureID user_texture_id, CONST struct ImVec2 a, CONST struct ImVec2 b, CONST struct ImVec2 uv0, CONST struct ImVec2 uv1, ImU32 col);
CIMGUI_API void             ImDrawList_AddPolyline(struct ImDrawList* list, CONST struct ImVec2* points, CONST int num_points, ImU32 col, bool closed, float thickness, bool anti_aliased);
CIMGUI_API void             ImDrawList_AddConvexPolyFilled(struct ImDrawList* list, CONST struct ImVec2* points, CONST int num_points, ImU32 col, bool anti_aliased);
CIMGUI_API void             ImDrawList_AddBezierCurve(struct ImDrawList* list, CONST struct ImVec2 pos0, CONST struct ImVec2 cp0, CONST struct ImVec2 cp1, CONST struct ImVec2 pos1, ImU32 col, float thickness, int num_segments);

// Stateful path API, add points then finish with PathFill() or PathStroke()
CIMGUI_API void             ImDrawList_PathClear(struct ImDrawList* list);
CIMGUI_API void             ImDrawList_PathLineTo(struct ImDrawList* list, CONST struct ImVec2 pos);
CIMGUI_API void             ImDrawList_PathLineToMergeDuplicate(struct ImDrawList* list, CONST struct ImVec2 pos);
CIMGUI_API void             ImDrawList_PathFill(struct ImDrawList* list, ImU32 col);
CIMGUI_API void             ImDrawList_PathStroke(struct ImDrawList* list, ImU32 col, bool closed, float thickness);
CIMGUI_API void             ImDrawList_PathArcTo(struct ImDrawList* list, CONST struct ImVec2 centre, float radius, float a_min, float a_max, int num_segments);
CIMGUI_API void             ImDrawList_PathArcToFast(struct ImDrawList* list, CONST struct ImVec2 centre, float radius, int a_min_of_12, int a_max_of_12); // Use precomputed angles for a 12 steps circle
CIMGUI_API void             ImDrawList_PathBezierCurveTo(struct ImDrawList* list, CONST struct ImVec2 p1, CONST struct ImVec2 p2, CONST struct ImVec2 p3, int num_segments);
CIMGUI_API void             ImDrawList_PathRect(struct ImDrawList* list, CONST struct ImVec2 rect_min, CONST struct ImVec2 rect_max, float rounding, int rounding_corners);

// Channels
CIMGUI_API void             ImDrawList_ChannelsSplit(struct ImDrawList* list, int channels_count);
CIMGUI_API void             ImDrawList_ChannelsMerge(struct ImDrawList* list);
CIMGUI_API void             ImDrawList_ChannelsSetCurrent(struct ImDrawList* list, int channel_index);

// Advanced
CIMGUI_API void             ImDrawList_AddCallback(struct ImDrawList* list, ImDrawCallback callback, void* callback_data); // Your rendering function must check for 'UserCallback' in ImDrawCmd and call the function instead of rendering triangles.
CIMGUI_API void             ImDrawList_AddDrawCmd(struct ImDrawList* list); // This is useful if you need to forcefully create a new draw call (to allow for dependent rendering / blending). Otherwise primitives are merged into the same draw-call as much as possible

// Internal helpers
CIMGUI_API void             ImDrawList_PrimReserve(struct ImDrawList* list, int idx_count, int vtx_count);
CIMGUI_API void             ImDrawList_PrimRect(struct ImDrawList* list, CONST struct ImVec2 a, CONST struct ImVec2 b, ImU32 col);
CIMGUI_API void             ImDrawList_PrimRectUV(struct ImDrawList* list, CONST struct ImVec2 a, CONST struct ImVec2 b, CONST struct ImVec2 uv_a, CONST struct ImVec2 uv_b, ImU32 col);
CIMGUI_API void             ImDrawList_PrimQuadUV(struct ImDrawList* list,CONST struct ImVec2 a, CONST struct ImVec2 b, CONST struct ImVec2 c, CONST struct ImVec2 d, CONST struct ImVec2 uv_a, CONST struct ImVec2 uv_b, CONST struct ImVec2 uv_c, CONST struct ImVec2 uv_d, ImU32 col);
CIMGUI_API void             ImDrawList_PrimWriteVtx(struct ImDrawList* list, CONST struct ImVec2 pos, CONST struct ImVec2 uv, ImU32 col);
CIMGUI_API void             ImDrawList_PrimWriteIdx(struct ImDrawList* list, ImDrawIdx idx);
CIMGUI_API void             ImDrawList_PrimVtx(struct ImDrawList* list, CONST struct ImVec2 pos, CONST struct ImVec2 uv, ImU32 col);
CIMGUI_API void             ImDrawList_UpdateClipRect(struct ImDrawList* list);
CIMGUI_API void             ImDrawList_UpdateTextureID(struct ImDrawList* list);
