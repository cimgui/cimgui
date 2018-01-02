
#include <stdio.h>

#if defined _WIN32 || defined __CYGWIN__
#ifdef CIMGUI_NO_EXPORT
#define API
#else
#define API __declspec(dllexport)
#endif
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
struct ImGuiListClipper;
struct ImGuiTextFilter;
struct ImGuiPayload;

#if defined __cplusplus
#define IMFONTGLYPH ImFontGlyph
#else
struct Glyph;
#define IMFONTGLYPH Glyph
#endif

typedef unsigned short ImDrawIdx;
typedef unsigned int ImU32;
typedef unsigned short ImWchar;
typedef void *ImTextureID;
typedef ImU32 ImGuiID;
typedef int ImGuiCol;
typedef int ImGuiStyleVar;
typedef int ImGuiKey;
typedef int ImGuiColorEditFlags;
typedef int ImGuiMouseCursor;
typedef int ImGuiWindowFlags;
typedef int ImGuiCond;
typedef int ImGuiColumnsFlags;
typedef int ImGuiInputTextFlags;
typedef int ImGuiSelectableFlags;
typedef int ImGuiTreeNodeFlags;
typedef int ImGuiHoveredFlags;
typedef int ImGuiComboFlags;
typedef int ImGuiDragDropFlags;
typedef int ImGuiFocusedFlags;
typedef int ImDrawCornerFlags;
typedef int ImDrawListFlags;
typedef int (*ImGuiTextEditCallback)(struct ImGuiTextEditCallbackData *data);
typedef void (*ImGuiSizeConstraintCallback)(struct ImGuiSizeConstraintCallbackData *data);
typedef void (*ImDrawCallback)(CONST struct ImDrawList *parent_list, CONST struct ImDrawCmd *cmd);
#ifdef _MSC_VER
typedef unsigned __int64 ImU64;
#else
typedef unsigned long long ImU64;
#endif

#ifdef CIMGUI_DEFINE_ENUMS_AND_STRUCTS
struct ImVec2
{
    float x, y;
};

struct ImVec4
{
    float x, y, z, w;
};

enum
{
    ImGuiWindowFlags_NoTitleBar = 1 << 0,
    ImGuiWindowFlags_NoResize = 1 << 1,
    ImGuiWindowFlags_NoMove = 1 << 2,
    ImGuiWindowFlags_NoScrollbar = 1 << 3,
    ImGuiWindowFlags_NoScrollWithMouse = 1 << 4,
    ImGuiWindowFlags_NoCollapse = 1 << 5,
    ImGuiWindowFlags_AlwaysAutoResize = 1 << 6,
    //ImGuiWindowFlags_ShowBorders = 1 << 7,
    ImGuiWindowFlags_NoSavedSettings = 1 << 8,
    ImGuiWindowFlags_NoInputs = 1 << 9,
    ImGuiWindowFlags_MenuBar = 1 << 10,
    ImGuiWindowFlags_HorizontalScrollbar = 1 << 11,
    ImGuiWindowFlags_NoFocusOnAppearing = 1 << 12,
    ImGuiWindowFlags_NoBringToFrontOnFocus = 1 << 13,
    ImGuiWindowFlags_AlwaysVerticalScrollbar = 1 << 14,
    ImGuiWindowFlags_AlwaysHorizontalScrollbar = 1 << 15,
    ImGuiWindowFlags_AlwaysUseWindowPadding = 1 << 16,
    ImGuiWindowFlags_ResizeFromAnySide = 1 << 17,
};

enum
{
    ImGuiInputTextFlags_CharsDecimal = 1 << 0,
    ImGuiInputTextFlags_CharsHexadecimal = 1 << 1,
    ImGuiInputTextFlags_CharsUppercase = 1 << 2,
    ImGuiInputTextFlags_CharsNoBlank = 1 << 3,
    ImGuiInputTextFlags_AutoSelectAll = 1 << 4,
    ImGuiInputTextFlags_EnterReturnsTrue = 1 << 5,
    ImGuiInputTextFlags_CallbackCompletion = 1 << 6,
    ImGuiInputTextFlags_CallbackHistory = 1 << 7,
    ImGuiInputTextFlags_CallbackAlways = 1 << 8,
    ImGuiInputTextFlags_CallbackCharFilter = 1 << 9,
    ImGuiInputTextFlags_AllowTabInput = 1 << 10,
    ImGuiInputTextFlags_CtrlEnterForNewLine = 1 << 11,
    ImGuiInputTextFlags_NoHorizontalScroll = 1 << 12,
    ImGuiInputTextFlags_AlwaysInsertMode = 1 << 13,
    ImGuiInputTextFlags_ReadOnly = 1 << 14,
    ImGuiInputTextFlags_Password = 1 << 15,
    ImGuiInputTextFlags_NoUndoRedo = 1 << 16,
};

enum
{
    ImGuiTreeNodeFlags_Selected = 1 << 0,
    ImGuiTreeNodeFlags_Framed = 1 << 1,
    ImGuiTreeNodeFlags_AllowItemOverlap = 1 << 2,
    ImGuiTreeNodeFlags_NoTreePushOnOpen = 1 << 3,
    ImGuiTreeNodeFlags_NoAutoOpenOnLog = 1 << 4,
    ImGuiTreeNodeFlags_DefaultOpen = 1 << 5,
    ImGuiTreeNodeFlags_OpenOnDoubleClick = 1 << 6,
    ImGuiTreeNodeFlags_OpenOnArrow = 1 << 7,
    ImGuiTreeNodeFlags_Leaf = 1 << 8,
    ImGuiTreeNodeFlags_Bullet = 1 << 9,
    ImGuiTreeNodeFlags_FramePadding = 1 << 10,
    ImGuiTreeNodeFlags_CollapsingHeader = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_NoAutoOpenOnLog
};

enum
{
    ImGuiSelectableFlags_DontClosePopups = 1 << 0,
    ImGuiSelectableFlags_SpanAllColumns = 1 << 1,
    ImGuiSelectableFlags_AllowDoubleClick = 1 << 2
};

enum ImGuiComboFlags_
{
    ImGuiComboFlags_PopupAlignLeft = 1 << 0,
    ImGuiComboFlags_HeightSmall = 1 << 1,
    ImGuiComboFlags_HeightRegular = 1 << 2,
    ImGuiComboFlags_HeightLarge = 1 << 3,
    ImGuiComboFlags_HeightLargest = 1 << 4,
    ImGuiComboFlags_HeightMask_ = ImGuiComboFlags_HeightSmall | ImGuiComboFlags_HeightRegular | ImGuiComboFlags_HeightLarge | ImGuiComboFlags_HeightLargest
};

enum ImGuiFocusedFlags_
{
    ImGuiFocusedFlags_ChildWindows = 1 << 0,
    ImGuiFocusedFlags_RootWindow = 1 << 1,
    ImGuiFocusedFlags_RootAndChildWindows = ImGuiFocusedFlags_RootWindow | ImGuiFocusedFlags_ChildWindows
};

enum ImGuiHoveredFlags_
{
    ImGuiHoveredFlags_ChildWindows = 1 << 0,
    ImGuiHoveredFlags_RootWindow = 1 << 1,
    ImGuiHoveredFlags_AllowWhenBlockedByPopup = 1 << 2,
    //ImGuiHoveredFlags_AllowWhenBlockedByModal     = 1 << 3,
    ImGuiHoveredFlags_AllowWhenBlockedByActiveItem = 1 << 4,
    ImGuiHoveredFlags_AllowWhenOverlapped = 1 << 5,
    ImGuiHoveredFlags_RectOnly = ImGuiHoveredFlags_AllowWhenBlockedByPopup | ImGuiHoveredFlags_AllowWhenBlockedByActiveItem | ImGuiHoveredFlags_AllowWhenOverlapped,
    ImGuiHoveredFlags_RootAndChildWindows = ImGuiHoveredFlags_RootWindow | ImGuiHoveredFlags_ChildWindows
};

enum ImGuiDragDropFlags_
{
    ImGuiDragDropFlags_SourceNoPreviewTooltip = 1 << 0,
    ImGuiDragDropFlags_SourceNoDisableHover = 1 << 1,
    ImGuiDragDropFlags_SourceNoHoldToOpenOthers = 1 << 2,
    ImGuiDragDropFlags_SourceAllowNullID = 1 << 3,
    ImGuiDragDropFlags_SourceExtern = 1 << 4,
    ImGuiDragDropFlags_AcceptBeforeDelivery = 1 << 10,
    ImGuiDragDropFlags_AcceptNoDrawDefaultRect = 1 << 11,
    ImGuiDragDropFlags_AcceptPeekOnly = ImGuiDragDropFlags_AcceptBeforeDelivery | ImGuiDragDropFlags_AcceptNoDrawDefaultRect
};

enum
{
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

enum
{
    ImGuiCol_Text,
    ImGuiCol_TextDisabled,
    ImGuiCol_WindowBg,
    ImGuiCol_ChildBg,
    ImGuiCol_PopupBg,
    ImGuiCol_Border,
    ImGuiCol_BorderShadow,
    ImGuiCol_FrameBg,
    ImGuiCol_FrameBgHovered,
    ImGuiCol_FrameBgActive,
    ImGuiCol_TitleBg,
    ImGuiCol_TitleBgActive,
    ImGuiCol_TitleBgCollapsed,
    ImGuiCol_MenuBarBg,
    ImGuiCol_ScrollbarBg,
    ImGuiCol_ScrollbarGrab,
    ImGuiCol_ScrollbarGrabHovered,
    ImGuiCol_ScrollbarGrabActive,
    ImGuiCol_CheckMark,
    ImGuiCol_SliderGrab,
    ImGuiCol_SliderGrabActive,
    ImGuiCol_Button,
    ImGuiCol_ButtonHovered,
    ImGuiCol_ButtonActive,
    ImGuiCol_Header,
    ImGuiCol_HeaderHovered,
    ImGuiCol_HeaderActive,
    ImGuiCol_Separator,
    ImGuiCol_SeparatorHovered,
    ImGuiCol_SeparatorActive,
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
    ImGuiCol_DragDropTarget,
    ImGuiCol_COUNT
};

enum
{
    ImGuiStyleVar_Alpha,
    ImGuiStyleVar_WindowPadding,
    ImGuiStyleVar_WindowRounding,
    ImGuiStyleVar_WindowBorderSize,
    ImGuiStyleVar_WindowMinSize,
    ImGuiStyleVar_ChildRounding,
    ImGuiStyleVar_ChildBorderSize,
    ImGuiStyleVar_PopupRounding,
    ImGuiStyleVar_PopupBorderSize,
    ImGuiStyleVar_FramePadding,
    ImGuiStyleVar_FrameRounding,
    ImGuiStyleVar_FrameBorderSize,
    ImGuiStyleVar_ItemSpacing,
    ImGuiStyleVar_ItemInnerSpacing,
    ImGuiStyleVar_IndentSpacing,
    ImGuiStyleVar_GrabMinSize,
    ImGuiStyleVar_ButtonTextAlign,
    ImGuiStyleVar_Count_
};

enum
{
    ImGuiColorEditFlags_NoAlpha = 1 << 1,
    ImGuiColorEditFlags_NoPicker = 1 << 2,
    ImGuiColorEditFlags_NoOptions = 1 << 3,
    ImGuiColorEditFlags_NoSmallPreview = 1 << 4,
    ImGuiColorEditFlags_NoInputs = 1 << 5,
    ImGuiColorEditFlags_NoTooltip = 1 << 6,
    ImGuiColorEditFlags_NoLabel = 1 << 7,
    ImGuiColorEditFlags_NoSidePreview = 1 << 8,
    ImGuiColorEditFlags_AlphaBar = 1 << 9,
    ImGuiColorEditFlags_AlphaPreview = 1 << 10,
    ImGuiColorEditFlags_AlphaPreviewHalf = 1 << 11,
    ImGuiColorEditFlags_HDR = 1 << 12,
    ImGuiColorEditFlags_RGB = 1 << 13,
    ImGuiColorEditFlags_HSV = 1 << 14,
    ImGuiColorEditFlags_HEX = 1 << 15,
    ImGuiColorEditFlags_Uint8 = 1 << 16,
    ImGuiColorEditFlags_Float = 1 << 17,
    ImGuiColorEditFlags_PickerHueBar = 1 << 18,
    ImGuiColorEditFlags_PickerHueWheel = 1 << 19
};

enum
{
    ImGuiMouseCursor_None = -1,
    ImGuiMouseCursor_Arrow = 0,
    ImGuiMouseCursor_TextInput,
    ImGuiMouseCursor_Move,
    ImGuiMouseCursor_ResizeNS,
    ImGuiMouseCursor_ResizeEW,
    ImGuiMouseCursor_ResizeNESW,
    ImGuiMouseCursor_ResizeNWSE,
    ImGuiMouseCursor_Count_
};

enum
{
    ImGuiCond_Always = 1 << 0,
    ImGuiCond_Once = 1 << 1,
    ImGuiCond_FirstUseEver = 1 << 2,
    ImGuiCond_Appearing = 1 << 3
};

enum ImDrawCornerFlags_
{
    ImDrawCornerFlags_TopLeft = 1 << 0,
    ImDrawCornerFlags_TopRight = 1 << 1,
    ImDrawCornerFlags_BotLeft = 1 << 2,
    ImDrawCornerFlags_BotRight = 1 << 3,
    ImDrawCornerFlags_Top = ImDrawCornerFlags_TopLeft | ImDrawCornerFlags_TopRight,
    ImDrawCornerFlags_Bot = ImDrawCornerFlags_BotLeft | ImDrawCornerFlags_BotRight,
    ImDrawCornerFlags_Left = ImDrawCornerFlags_TopLeft | ImDrawCornerFlags_BotLeft,
    ImDrawCornerFlags_Right = ImDrawCornerFlags_TopRight | ImDrawCornerFlags_BotRight,
    ImDrawCornerFlags_All = 0xF
};

enum ImDrawListFlags_
{
    ImDrawListFlags_AntiAliasedLines = 1 << 0,
    ImDrawListFlags_AntiAliasedFill = 1 << 1
};

struct ImGuiStyle
{
    float Alpha;
    struct ImVec2 WindowPadding;
    float WindowRounding;
    float WindowBorderSize;
    ImVec2 WindowMinSize;
    struct ImVec2 WindowTitleAlign;
    float ChildRounding;
    float ChildBorderSize;
    float PopupRounding;
    float PopupBorderSize;
    struct ImVec2 FramePadding;
    float FrameRounding;
    float FrameBorderSize;
    struct ImVec2 ItemSpacing;
    struct ImVec2 ItemInnerSpacing;
    struct ImVec2 TouchExtraPadding;
    float IndentSpacing;
    float ColumnsMinSpacing;
    float ScrollbarSize;
    float ScrollbarRounding;
    float GrabMinSize;
    float GrabRounding;
    struct ImVec2 ButtonTextAlign;
    struct ImVec2 DisplayWindowPadding;
    struct ImVec2 DisplaySafeAreaPadding;
    bool AntiAliasedLines;
    bool AntiAliasedFill;
    float CurveTessellationTol;
    struct ImVec4 Colors[ImGuiCol_COUNT];
};

struct ImGuiIO
{
    struct ImVec2 DisplaySize;
    float DeltaTime;
    float IniSavingRate;
    CONST char *IniFilename;
    CONST char *LogFilename;
    float MouseDoubleClickTime;
    float MouseDoubleClickMaxDist;
    float MouseDragThreshold;
    int KeyMap[ImGuiKey_COUNT];
    float KeyRepeatDelay;
    float KeyRepeatRate;
    void *UserData;
    struct ImFontAtlas *Fonts;
    float FontGlobalScale;
    bool FontAllowUserScaling;
    struct ImFont *FontDefault;
    struct ImVec2 DisplayFramebufferScale;
    struct ImVec2 DisplayVisibleMin;
    struct ImVec2 DisplayVisibleMax;
    bool OptMacOSXBehaviors;
    bool OptCursorBlink;
    void (*RenderDrawListsFn)(struct ImDrawData *data);
    CONST char *(*GetClipboardTextFn)(void *user_data);
    void (*SetClipboardTextFn)(void *user_data, CONST char *text);
    void *ClipboardUserData;
    void *(*MemAllocFn)(size_t sz);
    void (*MemFreeFn)(void *ptr);
    void (*ImeSetInputScreenPosFn)(int x, int y);
    void *ImeWindowHandle;
    struct ImVec2 MousePos;
    bool MouseDown[5];
    float MouseWheel;
    bool MouseDrawCursor;
    bool KeyCtrl;
    bool KeyShift;
    bool KeyAlt;
    bool KeySuper;
    bool KeysDown[512];
    ImWchar InputCharacters[16 + 1];
    bool WantCaptureMouse;
    bool WantCaptureKeyboard;
    bool WantTextInput;
    float Framerate;
    int MetricsAllocs;
    int MetricsRenderVertices;
    int MetricsRenderIndices;
    int MetricsActiveWindows;
    struct ImVec2 MouseDelta;
    struct ImVec2 MousePosPrev;
    bool MouseClicked[5];
    struct ImVec2 MouseClickedPos[5];
    float MouseClickedTime[5];
    bool MouseDoubleClicked[5];
    bool MouseReleased[5];
    bool MouseDownOwned[5];
    float MouseDownDuration[5];
    float MouseDownDurationPrev[5];
    ImVec2 MouseDragMaxDistanceAbs[5];
    float MouseDragMaxDistanceSqr[5];
    float KeysDownDuration[512];
    float KeysDownDurationPrev[512];
};

struct ImGuiTextEditCallbackData
{
    ImGuiInputTextFlags EventFlag;
    ImGuiInputTextFlags Flags;
    void *UserData;
    bool ReadOnly;
    ImWchar EventChar;
    ImGuiKey EventKey;
    char *Buf;
    int BufTextLen;
    int BufSize;
    bool BufDirty;
    int CursorPos;
    int SelectionStart;
    int SelectionEnd;
};

struct ImGuiSizeConstraintCallbackData
{
    void *UserData;
    struct ImVec2 Pos;
    struct ImVec2 CurrentSize;
    struct ImVec2 DesiredSize;
};

struct ImDrawCmd
{
    unsigned int ElemCount;
    struct ImVec4 ClipRect;
    ImTextureID TextureId;
    ImDrawCallback UserCallback;
    void *UserCallbackData;
};

struct ImDrawData
{
    bool Valid;
    struct ImDrawList **CmdLists;
    int CmdListsCount;
    int TotalVtxCount;
    int TotalIdxCount;
};

struct ImDrawVert
{
    struct ImVec2 pos;
    struct ImVec2 uv;
    ImU32 col;
};

struct ImFontConfig
{
    void *FontData;
    int FontDataSize;
    bool FontDataOwnedByAtlas;
    int FontNo;
    float SizePixels;
    int OversampleH, OversampleV;
    bool PixelSnapH;
    struct ImVec2 GlyphExtraSpacing;
    struct ImVec2 GlyphOffset;
    CONST ImWchar *GlyphRanges;
    bool MergeMode;
    unsigned int RasterizerFlags;
    float RasterizerMultiply;
    char Name[32];
    struct ImFont *DstFont;
};

struct ImGuiListClipper
{
    float StartPosY;
    float ItemsHeight;
    int ItemsCount, StepNo, DisplayStart, DisplayEnd;
};

struct ImGuiPayload
{
    CONST void *Data;
    int DataSize;

    ImGuiID SourceId;
    ImGuiID SourceParentId;
    int DataFrameCount;
    char DataType[8 + 1];
    bool Preview;
    bool Delivery;
};
#endif // CIMGUI_DEFINE_ENUMS_AND_STRUCTS

// Main
CIMGUI_API struct ImGuiIO *igGetIO();
CIMGUI_API struct ImGuiStyle *igGetStyle();
CIMGUI_API struct ImDrawData *igGetDrawData();
CIMGUI_API void igNewFrame();
CIMGUI_API void igRender();
CIMGUI_API void igEndFrame();
CIMGUI_API void igShutdown();

// Demo/Debug/Info
CIMGUI_API void igShowDemoWindow(bool *opened);
CIMGUI_API void igShowMetricsWindow(bool *opened);
CIMGUI_API void igShowStyleEditor(struct ImGuiStyle *ref);
CIMGUI_API void igShowStyleSelector(CONST char *label);
CIMGUI_API void igShowFontSelector(CONST char *label);
CIMGUI_API void igShowUserGuide();

// Window
CIMGUI_API bool igBegin(CONST char *name, bool *p_open, ImGuiWindowFlags flags);
//Is going to be obsolete,
//CIMGUI_API bool             igBegin2(CONST char* name, bool* p_open, CONST struct ImVec2 size_on_first_use, float bg_alpha, ImGuiWindowFlags flags);
CIMGUI_API void igEnd();
CIMGUI_API bool igBeginChild(CONST char *str_id, CONST struct ImVec2 size, bool border, ImGuiWindowFlags extra_flags);
CIMGUI_API bool igBeginChildEx(ImGuiID id, CONST struct ImVec2 size, bool border, ImGuiWindowFlags extra_flags);
CIMGUI_API void igEndChild();
CIMGUI_API void igGetContentRegionMax(struct ImVec2 *out);
CIMGUI_API void igGetContentRegionAvail(struct ImVec2 *out);
CIMGUI_API float igGetContentRegionAvailWidth();
CIMGUI_API void igGetWindowContentRegionMin(struct ImVec2 *out);
CIMGUI_API void igGetWindowContentRegionMax(struct ImVec2 *out);
CIMGUI_API float igGetWindowContentRegionWidth();
CIMGUI_API struct ImDrawList *igGetWindowDrawList();
CIMGUI_API void igGetWindowPos(struct ImVec2 *out);
CIMGUI_API void igGetWindowSize(struct ImVec2 *out);
CIMGUI_API float igGetWindowWidth();
CIMGUI_API float igGetWindowHeight();
CIMGUI_API bool igIsWindowCollapsed();
CIMGUI_API bool igIsWindowAppearing();
CIMGUI_API void igSetWindowFontScale(float scale);

CIMGUI_API void igSetNextWindowPos(CONST struct ImVec2 pos, ImGuiCond cond, CONST struct ImVec2 pivot);
CIMGUI_API void igSetNextWindowSize(CONST struct ImVec2 size, ImGuiCond cond);
CIMGUI_API void igSetNextWindowSizeConstraints(CONST struct ImVec2 size_min, CONST struct ImVec2 size_max, ImGuiSizeConstraintCallback custom_callback, void *custom_callback_data);
CIMGUI_API void igSetNextWindowContentSize(CONST struct ImVec2 size);
CIMGUI_API void igSetNextWindowCollapsed(bool collapsed, ImGuiCond cond);
CIMGUI_API void igSetNextWindowFocus();
CIMGUI_API void igSetWindowPos(CONST struct ImVec2 pos, ImGuiCond cond);
CIMGUI_API void igSetWindowSize(CONST struct ImVec2 size, ImGuiCond cond);
CIMGUI_API void igSetWindowCollapsed(bool collapsed, ImGuiCond cond);
CIMGUI_API void igSetWindowFocus();
CIMGUI_API void igSetWindowPosByName(CONST char *name, CONST struct ImVec2 pos, ImGuiCond cond);
CIMGUI_API void igSetWindowSize2(CONST char *name, CONST struct ImVec2 size, ImGuiCond cond);
CIMGUI_API void igSetWindowCollapsed2(CONST char *name, bool collapsed, ImGuiCond cond);
CIMGUI_API void igSetWindowFocus2(CONST char *name);

CIMGUI_API float igGetScrollX();
CIMGUI_API float igGetScrollY();
CIMGUI_API float igGetScrollMaxX();
CIMGUI_API float igGetScrollMaxY();
CIMGUI_API void igSetScrollX(float scroll_x);
CIMGUI_API void igSetScrollY(float scroll_y);
CIMGUI_API void igSetScrollHere(float center_y_ratio);
CIMGUI_API void igSetScrollFromPosY(float pos_y, float center_y_ratio);
CIMGUI_API void igSetStateStorage(struct ImGuiStorage *tree);
CIMGUI_API struct ImGuiStorage *igGetStateStorage();

// Parameters stacks (shared)
CIMGUI_API void igPushFont(struct ImFont *font);
CIMGUI_API void igPopFont();
CIMGUI_API void igPushStyleColorU32(ImGuiCol idx, ImU32 col);
CIMGUI_API void igPushStyleColor(ImGuiCol idx, CONST struct ImVec4 col);
CIMGUI_API void igPopStyleColor(int count);
CIMGUI_API void igPushStyleVar(ImGuiStyleVar idx, float val);
CIMGUI_API void igPushStyleVarVec(ImGuiStyleVar idx, CONST struct ImVec2 val);
CIMGUI_API void igPopStyleVar(int count);
CIMGUI_API void igGetStyleColorVec4(struct ImVec4 *pOut, ImGuiCol idx);
CIMGUI_API struct ImFont *igGetFont();
CIMGUI_API float igGetFontSize();
CIMGUI_API void igGetFontTexUvWhitePixel(struct ImVec2 *pOut);
CIMGUI_API ImU32 igGetColorU32(ImGuiCol idx, float alpha_mul);
CIMGUI_API ImU32 igGetColorU32Vec(CONST struct ImVec4 *col);
CIMGUI_API ImU32 igGetColorU32U32(ImU32 col);

// Parameters stacks (current window)
CIMGUI_API void igPushItemWidth(float item_width);
CIMGUI_API void igPopItemWidth();
CIMGUI_API float igCalcItemWidth();
CIMGUI_API void igPushTextWrapPos(float wrap_pos_x);
CIMGUI_API void igPopTextWrapPos();
CIMGUI_API void igPushAllowKeyboardFocus(bool v);
CIMGUI_API void igPopAllowKeyboardFocus();
CIMGUI_API void igPushButtonRepeat(bool repeat);
CIMGUI_API void igPopButtonRepeat();

// Cursor / Layout
CIMGUI_API void igSeparator();
CIMGUI_API void igSameLine(float pos_x, float spacing_w);
CIMGUI_API void igNewLine();
CIMGUI_API void igSpacing();
CIMGUI_API void igDummy(CONST struct ImVec2 *size);
CIMGUI_API void igIndent(float indent_w);
CIMGUI_API void igUnindent(float indent_w);
CIMGUI_API void igBeginGroup();
CIMGUI_API void igEndGroup();
CIMGUI_API void igGetCursorPos(struct ImVec2 *pOut);
CIMGUI_API float igGetCursorPosX();
CIMGUI_API float igGetCursorPosY();
CIMGUI_API void igSetCursorPos(CONST struct ImVec2 local_pos);
CIMGUI_API void igSetCursorPosX(float x);
CIMGUI_API void igSetCursorPosY(float y);
CIMGUI_API void igGetCursorStartPos(struct ImVec2 *pOut);
CIMGUI_API void igGetCursorScreenPos(struct ImVec2 *pOut);
CIMGUI_API void igSetCursorScreenPos(CONST struct ImVec2 pos);
CIMGUI_API void igAlignTextToFramePadding();
CIMGUI_API float igGetTextLineHeight();
CIMGUI_API float igGetTextLineHeightWithSpacing();
CIMGUI_API float igGetFrameHeight();
CIMGUI_API float igGetFrameHeightWithSpacing();

//Columns
CIMGUI_API void igColumns(int count, CONST char *id, bool border);
CIMGUI_API void igNextColumn();
CIMGUI_API int igGetColumnIndex();
CIMGUI_API float igGetColumnWidth(int column_index); // get column width (in pixels). pass -1 to use current column
CIMGUI_API void igSetColumnWidth(int column_index, float width);
CIMGUI_API float igGetColumnOffset(int column_index);
CIMGUI_API void igSetColumnOffset(int column_index, float offset_x);
CIMGUI_API int igGetColumnsCount();

// ID scopes
// If you are creating widgets in a loop you most likely want to push a unique identifier so ImGui can differentiate them
// You can also use "##extra" within your widget name to distinguish them from each others (see 'Programmer Guide')
CIMGUI_API void igPushIDStr(CONST char *str_id);
CIMGUI_API void igPushIDStrRange(CONST char *str_begin, CONST char *str_end);
CIMGUI_API void igPushIDPtr(CONST void *ptr_id);
CIMGUI_API void igPushIDInt(int int_id);
CIMGUI_API void igPopID();
CIMGUI_API ImGuiID igGetIDStr(CONST char *str_id);
CIMGUI_API ImGuiID igGetIDStrRange(CONST char *str_begin, CONST char *str_end);
CIMGUI_API ImGuiID igGetIDPtr(CONST void *ptr_id);

// Widgets: Text
CIMGUI_API void igTextUnformatted(CONST char *text, CONST char *text_end);
CIMGUI_API void igText(CONST char *fmt, ...);
CIMGUI_API void igTextV(CONST char *fmt, va_list args);
CIMGUI_API void igTextColored(CONST struct ImVec4 col, CONST char *fmt, ...);
CIMGUI_API void igTextColoredV(CONST struct ImVec4 col, CONST char *fmt, va_list args);
CIMGUI_API void igTextDisabled(CONST char *fmt, ...);
CIMGUI_API void igTextDisabledV(CONST char *fmt, va_list args);
CIMGUI_API void igTextWrapped(CONST char *fmt, ...);
CIMGUI_API void igTextWrappedV(CONST char *fmt, va_list args);
CIMGUI_API void igLabelText(CONST char *label, CONST char *fmt, ...);
CIMGUI_API void igLabelTextV(CONST char *label, CONST char *fmt, va_list args);
CIMGUI_API void igBulletText(CONST char *fmt, ...);
CIMGUI_API void igBulletTextV(CONST char *fmt, va_list args);
CIMGUI_API void igBullet();

// Widgets: Main
CIMGUI_API bool igButton(CONST char *label, CONST struct ImVec2 size);
CIMGUI_API bool igSmallButton(CONST char *label);
CIMGUI_API bool igInvisibleButton(CONST char *str_id, CONST struct ImVec2 size);
CIMGUI_API void igImage(ImTextureID user_texture_id, CONST struct ImVec2 size, CONST struct ImVec2 uv0, CONST struct ImVec2 uv1, CONST struct ImVec4 tint_col, CONST struct ImVec4 border_col);
CIMGUI_API bool igImageButton(ImTextureID user_texture_id, CONST struct ImVec2 size, CONST struct ImVec2 uv0, CONST struct ImVec2 uv1, int frame_padding, CONST struct ImVec4 bg_col, CONST struct ImVec4 tint_col);
CIMGUI_API bool igCheckbox(CONST char *label, bool *v);
CIMGUI_API bool igCheckboxFlags(CONST char *label, unsigned int *flags, unsigned int flags_value);
CIMGUI_API bool igRadioButtonBool(CONST char *label, bool active);
CIMGUI_API bool igRadioButton(CONST char *label, int *v, int v_button);
CIMGUI_API void igPlotLines(CONST char *label, CONST float *values, int values_count, int values_offset, CONST char *overlay_text, float scale_min, float scale_max, struct ImVec2 graph_size, int stride);
CIMGUI_API void igPlotLines2(CONST char *label, float (*values_getter)(void *data, int idx), void *data, int values_count, int values_offset, CONST char *overlay_text, float scale_min, float scale_max, struct ImVec2 graph_size);
CIMGUI_API void igPlotHistogram(CONST char *label, CONST float *values, int values_count, int values_offset, CONST char *overlay_text, float scale_min, float scale_max, struct ImVec2 graph_size, int stride);
CIMGUI_API void igPlotHistogram2(CONST char *label, float (*values_getter)(void *data, int idx), void *data, int values_count, int values_offset, CONST char *overlay_text, float scale_min, float scale_max, struct ImVec2 graph_size);
CIMGUI_API void igProgressBar(float fraction, CONST struct ImVec2 *size_arg, CONST char *overlay);

CIMGUI_API bool igBeginCombo(CONST char *label, CONST char *preview_value, ImGuiComboFlags flags);
CIMGUI_API void igEndCombo();
CIMGUI_API bool igCombo(CONST char *label, int *current_item, CONST char *CONST *items, int items_count, int popup_max_height_in_items);
CIMGUI_API bool igCombo2(CONST char *label, int *current_item, CONST char *items_separated_by_zeros, int popup_max_height_in_items);
CIMGUI_API bool igCombo3(CONST char *label, int *current_item, bool (*items_getter)(void *data, int idx, CONST char **out_text), void *data, int items_count, int popup_max_height_in_items);

// Widgets: Drags (tip: ctrl+click on a drag box to input with keyboard. manually input values aren't clamped, can go off-bounds)
// For all the Float2/Float3/Float4/Int2/Int3/Int4 versions of every functions, note that a 'float v[X]' function argument is the same as 'float* v', the array syntax is just a way to document the number of elements that are expected to be accessible. You can pass address of your first element out of a contiguous set, e.g. &myvector.x
CIMGUI_API bool igDragFloat(CONST char *label, float *v, float v_speed, float v_min, float v_max, CONST char *display_format, float power); // If v_max >= v_max we have no bound
CIMGUI_API bool igDragFloat2(CONST char *label, float v[2], float v_speed, float v_min, float v_max, CONST char *display_format, float power);
CIMGUI_API bool igDragFloat3(CONST char *label, float v[3], float v_speed, float v_min, float v_max, CONST char *display_format, float power);
CIMGUI_API bool igDragFloat4(CONST char *label, float v[4], float v_speed, float v_min, float v_max, CONST char *display_format, float power);
CIMGUI_API bool igDragFloatRange2(CONST char *label, float *v_current_min, float *v_current_max, float v_speed, float v_min, float v_max, CONST char *display_format, CONST char *display_format_max, float power);
CIMGUI_API bool igDragInt(CONST char *label, int *v, float v_speed, int v_min, int v_max, CONST char *display_format); // If v_max >= v_max we have no bound
CIMGUI_API bool igDragInt2(CONST char *label, int v[2], float v_speed, int v_min, int v_max, CONST char *display_format);
CIMGUI_API bool igDragInt3(CONST char *label, int v[3], float v_speed, int v_min, int v_max, CONST char *display_format);
CIMGUI_API bool igDragInt4(CONST char *label, int v[4], float v_speed, int v_min, int v_max, CONST char *display_format);
CIMGUI_API bool igDragIntRange2(CONST char *label, int *v_current_min, int *v_current_max, float v_speed, int v_min, int v_max, CONST char *display_format, CONST char *display_format_max);

// Widgets: Input with Keyboard
CIMGUI_API bool igInputText(CONST char *label, char *buf, size_t buf_size, ImGuiInputTextFlags flags, ImGuiTextEditCallback callback, void *user_data);
CIMGUI_API bool igInputTextMultiline(CONST char *label, char *buf, size_t buf_size, CONST struct ImVec2 size, ImGuiInputTextFlags flags, ImGuiTextEditCallback callback, void *user_data);
CIMGUI_API bool igInputFloat(CONST char *label, float *v, float step, float step_fast, int decimal_precision, ImGuiInputTextFlags extra_flags);
CIMGUI_API bool igInputFloat2(CONST char *label, float v[2], int decimal_precision, ImGuiInputTextFlags extra_flags);
CIMGUI_API bool igInputFloat3(CONST char *label, float v[3], int decimal_precision, ImGuiInputTextFlags extra_flags);
CIMGUI_API bool igInputFloat4(CONST char *label, float v[4], int decimal_precision, ImGuiInputTextFlags extra_flags);
CIMGUI_API bool igInputInt(CONST char *label, int *v, int step, int step_fast, ImGuiInputTextFlags extra_flags);
CIMGUI_API bool igInputInt2(CONST char *label, int v[2], ImGuiInputTextFlags extra_flags);
CIMGUI_API bool igInputInt3(CONST char *label, int v[3], ImGuiInputTextFlags extra_flags);
CIMGUI_API bool igInputInt4(CONST char *label, int v[4], ImGuiInputTextFlags extra_flags);

// Widgets: Sliders (tip: ctrl+click on a slider to input with keyboard. manually input values aren't clamped, can go off-bounds)
CIMGUI_API bool igSliderFloat(CONST char *label, float *v, float v_min, float v_max, CONST char *display_format, float power);
CIMGUI_API bool igSliderFloat2(CONST char *label, float v[2], float v_min, float v_max, CONST char *display_format, float power);
CIMGUI_API bool igSliderFloat3(CONST char *label, float v[3], float v_min, float v_max, CONST char *display_format, float power);
CIMGUI_API bool igSliderFloat4(CONST char *label, float v[4], float v_min, float v_max, CONST char *display_format, float power);
CIMGUI_API bool igSliderAngle(CONST char *label, float *v_rad, float v_degrees_min, float v_degrees_max);
CIMGUI_API bool igSliderInt(CONST char *label, int *v, int v_min, int v_max, CONST char *display_format);
CIMGUI_API bool igSliderInt2(CONST char *label, int v[2], int v_min, int v_max, CONST char *display_format);
CIMGUI_API bool igSliderInt3(CONST char *label, int v[3], int v_min, int v_max, CONST char *display_format);
CIMGUI_API bool igSliderInt4(CONST char *label, int v[4], int v_min, int v_max, CONST char *display_format);
CIMGUI_API bool igVSliderFloat(CONST char *label, CONST struct ImVec2 size, float *v, float v_min, float v_max, CONST char *display_format, float power);
CIMGUI_API bool igVSliderInt(CONST char *label, CONST struct ImVec2 size, int *v, int v_min, int v_max, CONST char *display_format);

// Widgets: Color Editor/Picker (tip: the ColorEdit* functions have a little colored preview square that can be left-clicked to open a picker, and right-clicked to open an option menu.)
// Note that a 'float v[X]' function argument is the same as 'float* v', the array syntax is just a way to document the number of elements that are expected to be accessible. You can the pass the address of a first float element out of a contiguous structure, e.g. &myvector.x
CIMGUI_API bool igColorEdit3(CONST char *label, float col[3], ImGuiColorEditFlags flags);
CIMGUI_API bool igColorEdit4(CONST char *label, float col[4], ImGuiColorEditFlags flags);
CIMGUI_API bool igColorPicker3(CONST char *label, float col[3], ImGuiColorEditFlags flags);
CIMGUI_API bool igColorPicker4(CONST char *label, float col[4], ImGuiColorEditFlags flags, CONST float *ref_col);
CIMGUI_API bool igColorButton(CONST char *desc_id, CONST struct ImVec4 col, ImGuiColorEditFlags flags, CONST struct ImVec2 size);
CIMGUI_API void igSetColorEditOptions(ImGuiColorEditFlags flags);

// Widgets: Trees
CIMGUI_API bool igTreeNode(CONST char *label);
CIMGUI_API bool igTreeNodeStr(CONST char *str_id, CONST char *fmt, ...);
CIMGUI_API bool igTreeNodePtr(CONST void *ptr_id, CONST char *fmt, ...);
CIMGUI_API bool igTreeNodeStrV(CONST char *str_id, CONST char *fmt, va_list args);
CIMGUI_API bool igTreeNodePtrV(CONST void *ptr_id, CONST char *fmt, va_list args);
CIMGUI_API bool igTreeNodeEx(CONST char *label, ImGuiTreeNodeFlags flags);
CIMGUI_API bool igTreeNodeExStr(CONST char *str_id, ImGuiTreeNodeFlags flags, CONST char *fmt, ...);
CIMGUI_API bool igTreeNodeExPtr(CONST void *ptr_id, ImGuiTreeNodeFlags flags, CONST char *fmt, ...);
CIMGUI_API bool igTreeNodeExV(CONST char *str_id, ImGuiTreeNodeFlags flags, CONST char *fmt, va_list args);
CIMGUI_API bool igTreeNodeExVPtr(CONST void *ptr_id, ImGuiTreeNodeFlags flags, CONST char *fmt, va_list args);
CIMGUI_API void igTreePushStr(CONST char *str_id);
CIMGUI_API void igTreePushPtr(CONST void *ptr_id);
CIMGUI_API void igTreePop();
CIMGUI_API void igTreeAdvanceToLabelPos();
CIMGUI_API float igGetTreeNodeToLabelSpacing();
CIMGUI_API void igSetNextTreeNodeOpen(bool opened, ImGuiCond cond);
CIMGUI_API bool igCollapsingHeader(CONST char *label, ImGuiTreeNodeFlags flags);
CIMGUI_API bool igCollapsingHeaderEx(CONST char *label, bool *p_open, ImGuiTreeNodeFlags flags);

// Widgets: Selectable / Lists
CIMGUI_API bool igSelectable(CONST char *label, bool selected, ImGuiSelectableFlags flags, CONST struct ImVec2 size);
CIMGUI_API bool igSelectableEx(CONST char *label, bool *p_selected, ImGuiSelectableFlags flags, CONST struct ImVec2 size);
CIMGUI_API bool igListBox(CONST char *label, int *current_item, CONST char *CONST *items, int items_count, int height_in_items);
CIMGUI_API bool igListBox2(CONST char *label, int *current_item, bool (*items_getter)(void *data, int idx, CONST char **out_text), void *data, int items_count, int height_in_items);
CIMGUI_API bool igListBoxHeader(CONST char *label, CONST struct ImVec2 size);
CIMGUI_API bool igListBoxHeader2(CONST char *label, int items_count, int height_in_items);
CIMGUI_API void igListBoxFooter();

// Widgets: Value() Helpers. Output single value in "name: value" format (tip: freely declare your own within the ImGui namespace!)
CIMGUI_API void igValueBool(CONST char *prefix, bool b);
CIMGUI_API void igValueInt(CONST char *prefix, int v);
CIMGUI_API void igValueUInt(CONST char *prefix, unsigned int v);
CIMGUI_API void igValueFloat(CONST char *prefix, float v, CONST char *float_format);

// Tooltip
CIMGUI_API void igSetTooltip(CONST char *fmt, ...);
CIMGUI_API void igSetTooltipV(CONST char *fmt, va_list args);
CIMGUI_API void igBeginTooltip();
CIMGUI_API void igEndTooltip();

// Widgets: Menus
CIMGUI_API bool igBeginMainMenuBar();
CIMGUI_API void igEndMainMenuBar();
CIMGUI_API bool igBeginMenuBar();
CIMGUI_API void igEndMenuBar();
CIMGUI_API bool igBeginMenu(CONST char *label, bool enabled);
CIMGUI_API void igEndMenu();
CIMGUI_API bool igMenuItem(CONST char *label, CONST char *shortcut, bool selected, bool enabled);
CIMGUI_API bool igMenuItemPtr(CONST char *label, CONST char *shortcut, bool *p_selected, bool enabled);

// Popup
CIMGUI_API void igOpenPopup(CONST char *str_id);
CIMGUI_API bool igOpenPopupOnItemClick(CONST char *str_id, int mouse_button);
CIMGUI_API bool igBeginPopup(CONST char *str_id);
CIMGUI_API bool igBeginPopupModal(CONST char *name, bool *p_open, ImGuiWindowFlags extra_flags);
CIMGUI_API bool igBeginPopupContextItem(CONST char *str_id, int mouse_button);
CIMGUI_API bool igBeginPopupContextWindow(CONST char *str_id, int mouse_button, bool also_over_items);
CIMGUI_API bool igBeginPopupContextVoid(CONST char *str_id, int mouse_button);
CIMGUI_API void igEndPopup();
CIMGUI_API bool igIsPopupOpen(CONST char *str_id);
CIMGUI_API void igCloseCurrentPopup();

// Logging: all text output from interface is redirected to tty/file/clipboard. Tree nodes are automatically opened.
CIMGUI_API void igLogToTTY(int max_depth);
CIMGUI_API void igLogToFile(int max_depth, CONST char *filename);
CIMGUI_API void igLogToClipboard(int max_depth);
CIMGUI_API void igLogFinish();
CIMGUI_API void igLogButtons();
CIMGUI_API void igLogText(CONST char *fmt, ...);

CIMGUI_API bool igBeginDragDropSource(ImGuiDragDropFlags flags, int mouse_button);
CIMGUI_API bool igSetDragDropPayload(CONST char *type, CONST void *data, size_t size, ImGuiCond cond);
CIMGUI_API void igEndDragDropSource();
CIMGUI_API bool igBeginDragDropTarget();
CIMGUI_API CONST struct ImGuiPayload *igAcceptDragDropPayload(CONST char *type, ImGuiDragDropFlags flags);
CIMGUI_API void igEndDragDropTarget();

// Clipping
CIMGUI_API void igPushClipRect(CONST struct ImVec2 clip_rect_min, CONST struct ImVec2 clip_rect_max, bool intersect_with_current_clip_rect);
CIMGUI_API void igPopClipRect();

// Styles
CIMGUI_API void igStyleColorsClassic(struct ImGuiStyle *dst);
CIMGUI_API void igStyleColorsDark(struct ImGuiStyle *dst);
CIMGUI_API void igStyleColorsLight(struct ImGuiStyle *dst);

CIMGUI_API void igSetItemDefaultFocus();
CIMGUI_API void igSetKeyboardFocusHere(int offset);

// Utilities
CIMGUI_API bool igIsItemHovered(ImGuiHoveredFlags flags);
CIMGUI_API bool igIsItemActive();
CIMGUI_API bool igIsItemClicked(int mouse_button);
CIMGUI_API bool igIsItemVisible();
CIMGUI_API bool igIsAnyItemHovered();
CIMGUI_API bool igIsAnyItemActive();
CIMGUI_API void igGetItemRectMin(struct ImVec2 *pOut);
CIMGUI_API void igGetItemRectMax(struct ImVec2 *pOut);
CIMGUI_API void igGetItemRectSize(struct ImVec2 *pOut);
CIMGUI_API void igSetItemAllowOverlap();
CIMGUI_API bool igIsWindowFocused(ImGuiFocusedFlags flags);
CIMGUI_API bool igIsWindowHovered(ImGuiHoveredFlags falgs);
CIMGUI_API bool igIsAnyWindowFocused();
CIMGUI_API bool igIsAnyWindowHovered();
CIMGUI_API bool igIsRectVisible(CONST struct ImVec2 item_size);
CIMGUI_API bool igIsRectVisible2(CONST struct ImVec2 *rect_min, CONST struct ImVec2 *rect_max);
CIMGUI_API float igGetTime();
CIMGUI_API int igGetFrameCount();

CIMGUI_API struct ImDrawList *igGetOverlayDrawList();
CIMGUI_API struct ImDrawListSharedData *igGetDrawListSharedData();

CIMGUI_API CONST char *igGetStyleColorName(ImGuiCol idx);
CIMGUI_API void igCalcItemRectClosestPoint(struct ImVec2 *pOut, CONST struct ImVec2 pos, bool on_edge, float outward);
CIMGUI_API void igCalcTextSize(struct ImVec2 *pOut, CONST char *text, CONST char *text_end, bool hide_text_after_double_hash, float wrap_width);
CIMGUI_API void igCalcListClipping(int items_count, float items_height, int *out_items_display_start, int *out_items_display_end);

CIMGUI_API bool igBeginChildFrame(ImGuiID id, CONST struct ImVec2 size, ImGuiWindowFlags extra_flags);
CIMGUI_API void igEndChildFrame();

CIMGUI_API void igColorConvertU32ToFloat4(struct ImVec4 *pOut, ImU32 in);
CIMGUI_API ImU32 igColorConvertFloat4ToU32(CONST struct ImVec4 in);
CIMGUI_API void igColorConvertRGBtoHSV(float r, float g, float b, float *out_h, float *out_s, float *out_v);
CIMGUI_API void igColorConvertHSVtoRGB(float h, float s, float v, float *out_r, float *out_g, float *out_b);

// Inputs
CIMGUI_API int igGetKeyIndex(ImGuiKey imgui_key);
CIMGUI_API bool igIsKeyDown(int user_key_index);
CIMGUI_API bool igIsKeyPressed(int user_key_index, bool repeat);
CIMGUI_API bool igIsKeyReleased(int user_key_index);
CIMGUI_API int igGetKeyPressedAmount(int key_index, float repeat_delay, float rate);
CIMGUI_API bool igIsMouseDown(int button);
CIMGUI_API bool igIsMouseClicked(int button, bool repeat);
CIMGUI_API bool igIsMouseDoubleClicked(int button);
CIMGUI_API bool igIsMouseReleased(int button);
CIMGUI_API bool igIsMouseDragging(int button, float lock_threshold);
CIMGUI_API bool igIsMouseHoveringRect(CONST struct ImVec2 r_min, CONST struct ImVec2 r_max, bool clip);
CIMGUI_API bool igIsMousePosValid(CONST struct ImVec2 *mouse_pos);
;
CIMGUI_API void igGetMousePos(struct ImVec2 *pOut);
CIMGUI_API void igGetMousePosOnOpeningCurrentPopup(struct ImVec2 *pOut);
CIMGUI_API void igGetMouseDragDelta(struct ImVec2 *pOut, int button, float lock_threshold);
CIMGUI_API void igResetMouseDragDelta(int button);
CIMGUI_API ImGuiMouseCursor igGetMouseCursor();
CIMGUI_API void igSetMouseCursor(ImGuiMouseCursor type);
CIMGUI_API void igCaptureKeyboardFromApp(bool capture);
CIMGUI_API void igCaptureMouseFromApp(bool capture);

// Helpers functions to access functions pointers in ImGui::GetIO()
CIMGUI_API void *igMemAlloc(size_t sz);
CIMGUI_API void igMemFree(void *ptr);
CIMGUI_API CONST char *igGetClipboardText();
CIMGUI_API void igSetClipboardText(CONST char *text);

// Internal state access - if you want to share ImGui state between modules (e.g. DLL) or allocate it yourself
CIMGUI_API CONST char *igGetVersion();
CIMGUI_API struct ImGuiContext *igCreateContext(void *(*malloc_fn)(size_t), void (*free_fn)(void *));
CIMGUI_API void igDestroyContext(struct ImGuiContext *ctx);
CIMGUI_API struct ImGuiContext *igGetCurrentContext();
CIMGUI_API void igSetCurrentContext(struct ImGuiContext *ctx);

CIMGUI_API void ImFontConfig_DefaultConstructor(struct ImFontConfig *config);

// ImGuiIO
CIMGUI_API void ImGuiIO_AddInputCharacter(unsigned short c);
CIMGUI_API void ImGuiIO_AddInputCharactersUTF8(CONST char *utf8_chars);
CIMGUI_API void ImGuiIO_ClearInputCharacters();

// ImGuiTextFilter
CIMGUI_API struct ImGuiTextFilter *ImGuiTextFilter_Create(CONST char *default_filter);
CIMGUI_API void ImGuiTextFilter_Destroy(struct ImGuiTextFilter *filter);
CIMGUI_API void ImGuiTextFilter_Clear(struct ImGuiTextFilter *filter);
CIMGUI_API bool ImGuiTextFilter_Draw(struct ImGuiTextFilter *filter, CONST char *label, float width);
CIMGUI_API bool ImGuiTextFilter_PassFilter(CONST struct ImGuiTextFilter *filter, CONST char *text, CONST char *text_end);
CIMGUI_API bool ImGuiTextFilter_IsActive(CONST struct ImGuiTextFilter *filter);
CIMGUI_API void ImGuiTextFilter_Build(struct ImGuiTextFilter *filter);
CIMGUI_API CONST char *ImGuiTextFilter_GetInputBuf(struct ImGuiTextFilter *filter);

// ImGuiTextBuffer
CIMGUI_API struct ImGuiTextBuffer *ImGuiTextBuffer_Create();
CIMGUI_API void ImGuiTextBuffer_Destroy(struct ImGuiTextBuffer *buffer);
CIMGUI_API char ImGuiTextBuffer_index(struct ImGuiTextBuffer *buffer, int i);
CIMGUI_API CONST char *ImGuiTextBuffer_begin(CONST struct ImGuiTextBuffer *buffer);
CIMGUI_API CONST char *ImGuiTextBuffer_end(CONST struct ImGuiTextBuffer *buffer);
CIMGUI_API int ImGuiTextBuffer_size(CONST struct ImGuiTextBuffer *buffer);
CIMGUI_API bool ImGuiTextBuffer_empty(struct ImGuiTextBuffer *buffer);
CIMGUI_API void ImGuiTextBuffer_clear(struct ImGuiTextBuffer *buffer);
CIMGUI_API CONST char *ImGuiTextBuffer_c_str(CONST struct ImGuiTextBuffer *buffer);
CIMGUI_API void ImGuiTextBuffer_appendf(struct ImGuiTextBuffer *buffer, CONST char *fmt, ...);
CIMGUI_API void ImGuiTextBuffer_appendfv(struct ImGuiTextBuffer *buffer, CONST char *fmt, va_list args);

// ImGuiStorage
CIMGUI_API struct ImGuiStorage *ImGuiStorage_Create();
CIMGUI_API void ImGuiStorage_Destroy(struct ImGuiStorage *storage);
CIMGUI_API int ImGuiStorage_GetInt(struct ImGuiStorage *storage, ImGuiID key, int default_val);
CIMGUI_API void ImGuiStorage_SetInt(struct ImGuiStorage *storage, ImGuiID key, int val);
CIMGUI_API bool ImGuiStorage_GetBool(struct ImGuiStorage *storage, ImGuiID key, bool default_val);
CIMGUI_API void ImGuiStorage_SetBool(struct ImGuiStorage *storage, ImGuiID key, bool val);
CIMGUI_API float ImGuiStorage_GetFloat(struct ImGuiStorage *storage, ImGuiID key, float default_val);
CIMGUI_API void ImGuiStorage_SetFloat(struct ImGuiStorage *storage, ImGuiID key, float val);
CIMGUI_API void *ImGuiStorage_GetVoidPtr(struct ImGuiStorage *storage, ImGuiID key);
CIMGUI_API void ImGuiStorage_SetVoidPtr(struct ImGuiStorage *storage, ImGuiID key, void *val);
CIMGUI_API int *ImGuiStorage_GetIntRef(struct ImGuiStorage *storage, ImGuiID key, int default_val);
CIMGUI_API bool *ImGuiStorage_GetBoolRef(struct ImGuiStorage *storage, ImGuiID key, bool default_val);
CIMGUI_API float *ImGuiStorage_GetFloatRef(struct ImGuiStorage *storage, ImGuiID key, float default_val);
CIMGUI_API void **ImGuiStorage_GetVoidPtrRef(struct ImGuiStorage *storage, ImGuiID key, void *default_val);
CIMGUI_API void ImGuiStorage_SetAllInt(struct ImGuiStorage *storage, int val);

// ImGuiTextEditCallbackData
CIMGUI_API void ImGuiTextEditCallbackData_DeleteChars(struct ImGuiTextEditCallbackData *data, int pos, int bytes_count);
CIMGUI_API void ImGuiTextEditCallbackData_InsertChars(struct ImGuiTextEditCallbackData *data, int pos, CONST char *text, CONST char *text_end);
CIMGUI_API bool ImGuiTextEditCallbackData_HasSelection(struct ImGuiTextEditCallbackData *data);

// ImGuiListClipper
CIMGUI_API bool ImGuiListClipper_Step(struct ImGuiListClipper *clipper);
CIMGUI_API void ImGuiListClipper_Begin(struct ImGuiListClipper *clipper, int count, float items_height);
CIMGUI_API void ImGuiListClipper_End(struct ImGuiListClipper *clipper);
CIMGUI_API int ImGuiListClipper_GetDisplayStart(struct ImGuiListClipper *clipper);
CIMGUI_API int ImGuiListClipper_GetDisplayEnd(struct ImGuiListClipper *clipper);

//ImDrawList
CIMGUI_API int ImDrawList_GetVertexBufferSize(struct ImDrawList *list);
CIMGUI_API struct ImDrawVert *ImDrawList_GetVertexPtr(struct ImDrawList *list, int n);
CIMGUI_API int ImDrawList_GetIndexBufferSize(struct ImDrawList *list);
CIMGUI_API ImDrawIdx *ImDrawList_GetIndexPtr(struct ImDrawList *list, int n);
CIMGUI_API int ImDrawList_GetCmdSize(struct ImDrawList *list);
CIMGUI_API struct ImDrawCmd *ImDrawList_GetCmdPtr(struct ImDrawList *list, int n);

CIMGUI_API void ImDrawList_Clear(struct ImDrawList *list);
CIMGUI_API void ImDrawList_ClearFreeMemory(struct ImDrawList *list);
CIMGUI_API void ImDrawList_PushClipRect(struct ImDrawList *list, struct ImVec2 clip_rect_min, struct ImVec2 clip_rect_max, bool intersect_with_current_clip_rect);
CIMGUI_API void ImDrawList_PushClipRectFullScreen(struct ImDrawList *list);
CIMGUI_API void ImDrawList_PopClipRect(struct ImDrawList *list);
CIMGUI_API void ImDrawList_PushTextureID(struct ImDrawList *list, CONST ImTextureID texture_id);
CIMGUI_API void ImDrawList_PopTextureID(struct ImDrawList *list);
CIMGUI_API void ImDrawList_GetClipRectMin(struct ImVec2 *pOut, struct ImDrawList *list);
CIMGUI_API void ImDrawList_GetClipRectMax(struct ImVec2 *pOut, struct ImDrawList *list);

// Primitives
CIMGUI_API void ImDrawList_AddLine(struct ImDrawList *list, CONST struct ImVec2 a, CONST struct ImVec2 b, ImU32 col, float thickness);
CIMGUI_API void ImDrawList_AddRect(struct ImDrawList *list, CONST struct ImVec2 a, CONST struct ImVec2 b, ImU32 col, float rounding, int rounding_corners_flags, float thickness);
CIMGUI_API void ImDrawList_AddRectFilled(struct ImDrawList *list, CONST struct ImVec2 a, CONST struct ImVec2 b, ImU32 col, float rounding, int rounding_corners_flags);
CIMGUI_API void ImDrawList_AddRectFilledMultiColor(struct ImDrawList *list, CONST struct ImVec2 a, CONST struct ImVec2 b, ImU32 col_upr_left, ImU32 col_upr_right, ImU32 col_bot_right, ImU32 col_bot_left);
CIMGUI_API void ImDrawList_AddQuad(struct ImDrawList *list, CONST struct ImVec2 a, CONST struct ImVec2 b, CONST struct ImVec2 c, CONST struct ImVec2 d, ImU32 col, float thickness);
CIMGUI_API void ImDrawList_AddQuadFilled(struct ImDrawList *list, CONST struct ImVec2 a, CONST struct ImVec2 b, CONST struct ImVec2 c, CONST struct ImVec2 d, ImU32 col);
CIMGUI_API void ImDrawList_AddTriangle(struct ImDrawList *list, CONST struct ImVec2 a, CONST struct ImVec2 b, CONST struct ImVec2 c, ImU32 col, float thickness);
CIMGUI_API void ImDrawList_AddTriangleFilled(struct ImDrawList *list, CONST struct ImVec2 a, CONST struct ImVec2 b, CONST struct ImVec2 c, ImU32 col);
CIMGUI_API void ImDrawList_AddCircle(struct ImDrawList *list, CONST struct ImVec2 centre, float radius, ImU32 col, int num_segments, float thickness);
CIMGUI_API void ImDrawList_AddCircleFilled(struct ImDrawList *list, CONST struct ImVec2 centre, float radius, ImU32 col, int num_segments);
CIMGUI_API void ImDrawList_AddText(struct ImDrawList *list, CONST struct ImVec2 pos, ImU32 col, CONST char *text_begin, CONST char *text_end);
CIMGUI_API void ImDrawList_AddTextExt(struct ImDrawList *list, CONST struct ImFont *font, float font_size, CONST struct ImVec2 pos, ImU32 col, CONST char *text_begin, CONST char *text_end, float wrap_width, CONST struct ImVec4 *cpu_fine_clip_rect);
CIMGUI_API void ImDrawList_AddImage(struct ImDrawList *list, ImTextureID user_texture_id, CONST struct ImVec2 a, CONST struct ImVec2 b, CONST struct ImVec2 uv_a, CONST struct ImVec2 uv_b, ImU32 col);
CIMGUI_API void ImDrawList_AddImageQuad(struct ImDrawList *list, ImTextureID user_texture_id, CONST struct ImVec2 a, CONST struct ImVec2 b, CONST struct ImVec2 c, CONST struct ImVec2 d, CONST struct ImVec2 uv_a, CONST struct ImVec2 uv_b, CONST struct ImVec2 uv_c, CONST struct ImVec2 uv_d, ImU32 col);
CIMGUI_API void ImDrawList_AddImageRounded(struct ImDrawList *list, ImTextureID user_texture_id, CONST struct ImVec2 a, CONST struct ImVec2 b, CONST struct ImVec2 uv_a, CONST struct ImVec2 uv_b, ImU32 col, float rounding, int rounding_corners);
CIMGUI_API void ImDrawList_AddPolyline(struct ImDrawList *list, CONST struct ImVec2 *points, CONST int num_points, ImU32 col, bool closed, float thickness);
CIMGUI_API void ImDrawList_AddConvexPolyFilled(struct ImDrawList *list, CONST struct ImVec2 *points, CONST int num_points, ImU32 col);
CIMGUI_API void ImDrawList_AddBezierCurve(struct ImDrawList *list, CONST struct ImVec2 pos0, CONST struct ImVec2 cp0, CONST struct ImVec2 cp1, CONST struct ImVec2 pos1, ImU32 col, float thickness, int num_segments);

// Stateful path API, add points then finish with PathFill() or PathStroke()
CIMGUI_API void ImDrawList_PathClear(struct ImDrawList *list);
CIMGUI_API void ImDrawList_PathLineTo(struct ImDrawList *list, CONST struct ImVec2 pos);
CIMGUI_API void ImDrawList_PathLineToMergeDuplicate(struct ImDrawList *list, CONST struct ImVec2 pos);
CIMGUI_API void ImDrawList_PathFillConvex(struct ImDrawList *list, ImU32 col);
CIMGUI_API void ImDrawList_PathStroke(struct ImDrawList *list, ImU32 col, bool closed, float thickness);
CIMGUI_API void ImDrawList_PathArcTo(struct ImDrawList *list, CONST struct ImVec2 centre, float radius, float a_min, float a_max, int num_segments);
CIMGUI_API void ImDrawList_PathArcToFast(struct ImDrawList *list, CONST struct ImVec2 centre, float radius, int a_min_of_12, int a_max_of_12); // Use precomputed angles for a 12 steps circle
CIMGUI_API void ImDrawList_PathBezierCurveTo(struct ImDrawList *list, CONST struct ImVec2 p1, CONST struct ImVec2 p2, CONST struct ImVec2 p3, int num_segments);
CIMGUI_API void ImDrawList_PathRect(struct ImDrawList *list, CONST struct ImVec2 rect_min, CONST struct ImVec2 rect_max, float rounding, int rounding_corners_flags);

// Channels
CIMGUI_API void ImDrawList_ChannelsSplit(struct ImDrawList *list, int channels_count);
CIMGUI_API void ImDrawList_ChannelsMerge(struct ImDrawList *list);
CIMGUI_API void ImDrawList_ChannelsSetCurrent(struct ImDrawList *list, int channel_index);

// Advanced
CIMGUI_API void ImDrawList_AddCallback(struct ImDrawList *list, ImDrawCallback callback, void *callback_data); // Your rendering function must check for 'UserCallback' in ImDrawCmd and call the function instead of rendering triangles.
CIMGUI_API void ImDrawList_AddDrawCmd(struct ImDrawList *list);                                                // This is useful if you need to forcefully create a new draw call (to allow for dependent rendering / blending). Otherwise primitives are merged into the same draw-call as much as possible

// Internal helpers
CIMGUI_API void ImDrawList_PrimReserve(struct ImDrawList *list, int idx_count, int vtx_count);
CIMGUI_API void ImDrawList_PrimRect(struct ImDrawList *list, CONST struct ImVec2 a, CONST struct ImVec2 b, ImU32 col);
CIMGUI_API void ImDrawList_PrimRectUV(struct ImDrawList *list, CONST struct ImVec2 a, CONST struct ImVec2 b, CONST struct ImVec2 uv_a, CONST struct ImVec2 uv_b, ImU32 col);
CIMGUI_API void ImDrawList_PrimQuadUV(struct ImDrawList *list, CONST struct ImVec2 a, CONST struct ImVec2 b, CONST struct ImVec2 c, CONST struct ImVec2 d, CONST struct ImVec2 uv_a, CONST struct ImVec2 uv_b, CONST struct ImVec2 uv_c, CONST struct ImVec2 uv_d, ImU32 col);
CIMGUI_API void ImDrawList_PrimWriteVtx(struct ImDrawList *list, CONST struct ImVec2 pos, CONST struct ImVec2 uv, ImU32 col);
CIMGUI_API void ImDrawList_PrimWriteIdx(struct ImDrawList *list, ImDrawIdx idx);
CIMGUI_API void ImDrawList_PrimVtx(struct ImDrawList *list, CONST struct ImVec2 pos, CONST struct ImVec2 uv, ImU32 col);
CIMGUI_API void ImDrawList_UpdateClipRect(struct ImDrawList *list);
CIMGUI_API void ImDrawList_UpdateTextureID(struct ImDrawList *list);

// ImDrawData
CIMGUI_API void ImDrawData_DeIndexAllBuffers(struct ImDrawData *drawData);
CIMGUI_API void ImDrawData_ScaleClipRects(struct ImDrawData *drawData, CONST struct ImVec2 sc);

// ImFontAtlas
CIMGUI_API void ImFontAtlas_GetTexDataAsRGBA32(struct ImFontAtlas *atlas, unsigned char **out_pixels, int *out_width, int *out_height, int *out_bytes_per_pixel);
CIMGUI_API void ImFontAtlas_GetTexDataAsAlpha8(struct ImFontAtlas *atlas, unsigned char **out_pixels, int *out_width, int *out_height, int *out_bytes_per_pixel);
CIMGUI_API void ImFontAtlas_SetTexID(struct ImFontAtlas *atlas, ImTextureID id);
CIMGUI_API struct ImFont *ImFontAtlas_AddFont(struct ImFontAtlas *atlas, CONST struct ImFontConfig *font_cfg);
CIMGUI_API struct ImFont *ImFontAtlas_AddFontDefault(struct ImFontAtlas *atlas, CONST struct ImFontConfig *font_cfg);
CIMGUI_API struct ImFont *ImFontAtlas_AddFontFromFileTTF(struct ImFontAtlas *atlas, CONST char *filename, float size_pixels, CONST struct ImFontConfig *font_cfg, CONST ImWchar *glyph_ranges);
CIMGUI_API struct ImFont *ImFontAtlas_AddFontFromMemoryTTF(struct ImFontAtlas *atlas, void *font_data, int font_size, float size_pixels, CONST struct ImFontConfig *font_cfg, CONST ImWchar *glyph_ranges);
CIMGUI_API struct ImFont *ImFontAtlas_AddFontFromMemoryCompressedTTF(struct ImFontAtlas *atlas, CONST void *compressed_font_data, int compressed_font_size, float size_pixels, CONST struct ImFontConfig *font_cfg, CONST ImWchar *glyph_ranges);
CIMGUI_API struct ImFont *ImFontAtlas_AddFontFromMemoryCompressedBase85TTF(struct ImFontAtlas *atlas, CONST char *compressed_font_data_base85, float size_pixels, CONST struct ImFontConfig *font_cfg, CONST ImWchar *glyph_ranges);
CIMGUI_API void ImFontAtlas_ClearTexData(struct ImFontAtlas *atlas);
CIMGUI_API void ImFontAtlas_Clear(struct ImFontAtlas *atlas);
CIMGUI_API CONST ImWchar *ImFontAtlas_GetGlyphRangesDefault(struct ImFontAtlas *atlas);
CIMGUI_API CONST ImWchar *ImFontAtlas_GetGlyphRangesKorean(struct ImFontAtlas *atlas);
CIMGUI_API CONST ImWchar *ImFontAtlas_GetGlyphRangesJapanese(struct ImFontAtlas *atlas);
CIMGUI_API CONST ImWchar *ImFontAtlas_GetGlyphRangesChinese(struct ImFontAtlas *atlas);
CIMGUI_API CONST ImWchar *ImFontAtlas_GetGlyphRangesCyrillic(struct ImFontAtlas *atlas);
CIMGUI_API CONST ImWchar *ImFontAtlas_GetGlyphRangesThai(struct ImFontAtlas *atlas);

CIMGUI_API ImTextureID ImFontAtlas_GetTexID(struct ImFontAtlas *atlas);
CIMGUI_API unsigned char *ImFontAtlas_GetTexPixelsAlpha8(struct ImFontAtlas *atlas);
CIMGUI_API unsigned int *ImFontAtlas_GetTexPixelsRGBA32(struct ImFontAtlas *atlas);
CIMGUI_API int ImFontAtlas_GetTexWidth(struct ImFontAtlas *atlas);
CIMGUI_API int ImFontAtlas_GetTexHeight(struct ImFontAtlas *atlas);
CIMGUI_API int ImFontAtlas_GetTexDesiredWidth(struct ImFontAtlas *atlas);
CIMGUI_API void ImFontAtlas_SetTexDesiredWidth(struct ImFontAtlas *atlas, int TexDesiredWidth_);
CIMGUI_API int ImFontAtlas_GetTexGlyphPadding(struct ImFontAtlas *atlas);
CIMGUI_API void ImFontAtlas_SetTexGlyphPadding(struct ImFontAtlas *atlas, int TexGlyphPadding_);
CIMGUI_API void ImFontAtlas_GetTexUvWhitePixel(struct ImFontAtlas *atlas, struct ImVec2 *pOut);

// ImFontAtlas::Fonts;
CIMGUI_API int ImFontAtlas_Fonts_size(struct ImFontAtlas *atlas);
CIMGUI_API struct ImFont *ImFontAtlas_Fonts_index(struct ImFontAtlas *atlas, int index);

// ImFont
CIMGUI_API float ImFont_GetFontSize(CONST struct ImFont *font);
CIMGUI_API void ImFont_SetFontSize(struct ImFont *font, float FontSize_);
CIMGUI_API float ImFont_GetScale(CONST struct ImFont *font);
CIMGUI_API void ImFont_SetScale(struct ImFont *font, float Scale_);
CIMGUI_API void ImFont_GetDisplayOffset(CONST struct ImFont *font, struct ImVec2 *pOut);
CIMGUI_API CONST struct IMFONTGLYPH *ImFont_GetFallbackGlyph(CONST struct ImFont *font);
CIMGUI_API void ImFont_SetFallbackGlyph(struct ImFont *font, CONST struct IMFONTGLYPH *FallbackGlyph_);
CIMGUI_API float ImFont_GetFallbackAdvanceX(CONST struct ImFont *font);
CIMGUI_API ImWchar ImFont_GetFallbackChar(CONST struct ImFont *font);
CIMGUI_API short ImFont_GetConfigDataCount(CONST struct ImFont *font);
CIMGUI_API struct ImFontConfig *ImFont_GetConfigData(struct ImFont *font);
CIMGUI_API struct ImFontAtlas *ImFont_GetContainerAtlas(struct ImFont *font);
CIMGUI_API float ImFont_GetAscent(CONST struct ImFont *font);
CIMGUI_API float ImFont_GetDescent(CONST struct ImFont *font);
CIMGUI_API int ImFont_GetMetricsTotalSurface(CONST struct ImFont *font);
CIMGUI_API void ImFont_ClearOutputData(struct ImFont *font);
CIMGUI_API void ImFont_BuildLookupTable(struct ImFont *font);
CIMGUI_API CONST struct IMFONTGLYPH *ImFont_FindGlyph(CONST struct ImFont *font, ImWchar c);
CIMGUI_API void ImFont_SetFallbackChar(struct ImFont *font, ImWchar c);
CIMGUI_API float ImFont_GetCharAdvance(CONST struct ImFont *font, ImWchar c);
CIMGUI_API bool ImFont_IsLoaded(CONST struct ImFont *font);
CIMGUI_API CONST char *ImFont_GetDebugName(CONST struct ImFont *font);
CIMGUI_API void ImFont_CalcTextSizeA(CONST struct ImFont *font, struct ImVec2 *pOut, float size, float max_width, float wrap_width, CONST char *text_begin, CONST char *text_end, CONST char **remaining); // utf8
CIMGUI_API CONST char *ImFont_CalcWordWrapPositionA(CONST struct ImFont *font, float scale, CONST char *text, CONST char *text_end, float wrap_width);
CIMGUI_API void ImFont_RenderChar(CONST struct ImFont *font, struct ImDrawList *draw_list, float size, struct ImVec2 pos, ImU32 col, unsigned short c);
CIMGUI_API void ImFont_RenderText(CONST struct ImFont *font, struct ImDrawList *draw_list, float size, struct ImVec2 pos, ImU32 col, CONST struct ImVec4 *clip_rect, CONST char *text_begin, CONST char *text_end, float wrap_width, bool cpu_fine_clip);
// ImFont::Glyph
CIMGUI_API int ImFont_Glyphs_size(CONST struct ImFont *font);
CIMGUI_API struct IMFONTGLYPH *ImFont_Glyphs_index(struct ImFont *font, int index);
// ImFont::IndexXAdvance
CIMGUI_API int ImFont_IndexXAdvance_size(CONST struct ImFont *font);
CIMGUI_API float ImFont_IndexXAdvance_index(CONST struct ImFont *font, int index);
// ImFont::IndexLookup
CIMGUI_API int ImFont_IndexLookup_size(CONST struct ImFont *font);
CIMGUI_API unsigned short ImFont_IndexLookup_index(CONST struct ImFont *font, int index);
