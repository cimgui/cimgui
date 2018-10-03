
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


#ifdef _MSC_VER
typedef unsigned __int64 ImU64;
#else
//typedef unsigned long long ImU64;
#endif

//UDT stuff
typedef struct ImVec2_Simple { float x; float y; } ImVec2_Simple;
typedef struct ImVec4_Simple { float x; float y; float z; float w;} ImVec4_Simple;
typedef struct ImColor_Simple { ImVec4_Simple Value;} ImColor_Simple;


#ifdef CIMGUI_DEFINE_ENUMS_AND_STRUCTS
typedef unsigned short ImDrawIdx;
typedef void* ImTextureID;
// dear imgui, v1.65
typedef struct CustomRect CustomRect;
typedef struct GlyphRangesBuilder GlyphRangesBuilder;
typedef struct ImFontGlyph ImFontGlyph;
typedef struct Pair Pair;
typedef struct TextRange TextRange;
typedef struct ImVec4 ImVec4;
typedef struct ImVec2 ImVec2;
typedef struct ImGuiTextBuffer ImGuiTextBuffer;
typedef struct ImGuiTextFilter ImGuiTextFilter;
typedef struct ImGuiStyle ImGuiStyle;
typedef struct ImGuiStorage ImGuiStorage;
typedef struct ImGuiSizeCallbackData ImGuiSizeCallbackData;
typedef struct ImGuiPayload ImGuiPayload;
typedef struct ImGuiOnceUponAFrame ImGuiOnceUponAFrame;
typedef struct ImGuiListClipper ImGuiListClipper;
typedef struct ImGuiInputTextCallbackData ImGuiInputTextCallbackData;
typedef struct ImGuiIO ImGuiIO;
typedef struct ImGuiContext ImGuiContext;
typedef struct ImColor ImColor;
typedef struct ImFontConfig ImFontConfig;
typedef struct ImFontAtlas ImFontAtlas;
typedef struct ImFont ImFont;
typedef struct ImDrawVert ImDrawVert;
typedef struct ImDrawListSharedData ImDrawListSharedData;
typedef struct ImDrawList ImDrawList;
typedef struct ImDrawData ImDrawData;
typedef struct ImDrawCmd ImDrawCmd;
typedef struct ImDrawChannel ImDrawChannel;
// (headers)
// See imgui.cpp file for documentation.
// Call and read ImGui::ShowDemoWindow() in imgui_demo.cpp for demo code.
// Read 'Programmer guide' in imgui.cpp for notes on how to setup ImGui in your codebase.
// Get latest version at https://github.com/ocornut/imgui
// Configuration file (edit imconfig.h or define IMGUI_USER_CONFIG to set your own filename)
// Version
// (Integer encoded as XYYZZ for use in #if preprocessor conditionals. Work in progress versions typically starts at XYY00 then bounced up to XYY01 when release tagging happens)
// Define attributes of all API symbols declarations (e.g. for DLL under Windows)
//  is used for core imgui functions,  is used for the default bindings files (imgui_impl_xxx.h)
// Helpers
// Forward declarations
struct ImDrawChannel;               // Temporary storage for outputting drawing commands out of order, used by ImDrawList::ChannelsSplit()
struct ImDrawCmd;                   // A single draw command within a parent ImDrawList (generally maps to 1 GPU draw call)
struct ImDrawData;                  // All draw command lists required to render the frame
struct ImDrawList;                  // A single draw command list (generally one per window, conceptually you may see this as a dynamic "mesh" builder)
struct ImDrawListSharedData;        // Data shared among multiple draw lists (typically owned by parent ImGui context, but you may create one yourself)
struct ImDrawVert;                  // A single vertex (20 bytes by default, override layout with IMGUI_OVERRIDE_DRAWVERT_STRUCT_LAYOUT)
struct ImFont;                      // Runtime data for a single font within a parent ImFontAtlas
struct ImFontAtlas;                 // Runtime data for multiple fonts, bake multiple fonts into a single texture, TTF/OTF font loader
struct ImFontConfig;                // Configuration data when adding a font or merging fonts
struct ImColor;                     // Helper functions to create a color that can be converted to either u32 or float4 (*obsolete* please avoid using)
struct ImGuiContext;                // ImGui context (opaque)
struct ImGuiIO;                     // Main configuration and I/O between your application and ImGui
struct ImGuiInputTextCallbackData;  // Shared state of InputText() when using custom ImGuiInputTextCallback (rare/advanced use)
struct ImGuiListClipper;            // Helper to manually clip large list of items
struct ImGuiOnceUponAFrame;         // Helper for running a block of code not more than once a frame, used by IMGUI_ONCE_UPON_A_FRAME macro
struct ImGuiPayload;                // User data payload for drag and drop operations
struct ImGuiSizeCallbackData;       // Callback data when using SetNextWindowSizeConstraints() (rare/advanced use)
struct ImGuiStorage;                // Helper for key->value storage
struct ImGuiStyle;                  // Runtime data for styling/colors
struct ImGuiTextFilter;             // Helper to parse and apply text filters (e.g. "aaaaa[,bbbb][,ccccc]")
struct ImGuiTextBuffer;             // Helper to hold and append into a text buffer (~string builder)
// Typedefs and Enums/Flags (declared as int for compatibility with old C++, to allow using as flags and to not pollute the top of this file)
// Use your programming IDE "Go to definition" facility on the names of the center columns to find the actual flags/enum lists.
typedef unsigned int ImGuiID;       // Unique ID used by widgets (typically hashed from a stack of string)
typedef unsigned short ImWchar;     // Character for keyboard input/display
typedef int ImGuiCol;               // -> enum ImGuiCol_             // Enum: A color identifier for styling
typedef int ImGuiCond;              // -> enum ImGuiCond_            // Enum: A condition for Set*()
typedef int ImGuiDataType;          // -> enum ImGuiDataType_        // Enum: A primary data type
typedef int ImGuiDir;               // -> enum ImGuiDir_             // Enum: A cardinal direction
typedef int ImGuiKey;               // -> enum ImGuiKey_             // Enum: A key identifier (ImGui-side enum)
typedef int ImGuiNavInput;          // -> enum ImGuiNavInput_        // Enum: An input identifier for navigation
typedef int ImGuiMouseCursor;       // -> enum ImGuiMouseCursor_     // Enum: A mouse cursor identifier
typedef int ImGuiStyleVar;          // -> enum ImGuiStyleVar_        // Enum: A variable identifier for styling
typedef int ImDrawCornerFlags;      // -> enum ImDrawCornerFlags_    // Flags: for ImDrawList::AddRect*() etc.
typedef int ImDrawListFlags;        // -> enum ImDrawListFlags_      // Flags: for ImDrawList
typedef int ImFontAtlasFlags;       // -> enum ImFontAtlasFlags_     // Flags: for ImFontAtlas
typedef int ImGuiBackendFlags;      // -> enum ImGuiBackendFlags_    // Flags: for io.BackendFlags
typedef int ImGuiColorEditFlags;    // -> enum ImGuiColorEditFlags_  // Flags: for ColorEdit*(), ColorPicker*()
typedef int ImGuiColumnsFlags;      // -> enum ImGuiColumnsFlags_    // Flags: for Columns(), BeginColumns()
typedef int ImGuiConfigFlags;       // -> enum ImGuiConfigFlags_     // Flags: for io.ConfigFlags
typedef int ImGuiComboFlags;        // -> enum ImGuiComboFlags_      // Flags: for BeginCombo()
typedef int ImGuiDragDropFlags;     // -> enum ImGuiDragDropFlags_   // Flags: for *DragDrop*()
typedef int ImGuiFocusedFlags;      // -> enum ImGuiFocusedFlags_    // Flags: for IsWindowFocused()
typedef int ImGuiHoveredFlags;      // -> enum ImGuiHoveredFlags_    // Flags: for IsItemHovered(), IsWindowHovered() etc.
typedef int ImGuiInputTextFlags;    // -> enum ImGuiInputTextFlags_  // Flags: for InputText*()
typedef int ImGuiSelectableFlags;   // -> enum ImGuiSelectableFlags_ // Flags: for Selectable()
typedef int ImGuiTreeNodeFlags;     // -> enum ImGuiTreeNodeFlags_   // Flags: for TreeNode*(),CollapsingHeader()
typedef int ImGuiWindowFlags;       // -> enum ImGuiWindowFlags_     // Flags: for Begin*()
typedef int (*ImGuiInputTextCallback)(ImGuiInputTextCallbackData *data);
typedef void (*ImGuiSizeCallback)(ImGuiSizeCallbackData* data);
// Scalar data types
typedef signed int          ImS32;  // 32-bit signed integer == int
typedef unsigned int        ImU32;  // 32-bit unsigned integer (often used to store packed colors)
// 2D vector (often used to store positions, sizes, etc.)
struct ImVec2
{
    float     x, y;
};
// 4D vector (often used to store floating-point colors)
struct ImVec4
{
    float     x, y, z, w;
};
// Dear ImGui end-user API
// (In a namespace so you can add extra functions in your own separate file. Please don't modify imgui.cpp/.h!)
// Flags for ImGui::Begin()
enum ImGuiWindowFlags_
{
    ImGuiWindowFlags_None                   = 0,
    ImGuiWindowFlags_NoTitleBar             = 1 << 0,   // Disable title-bar
    ImGuiWindowFlags_NoResize               = 1 << 1,   // Disable user resizing with the lower-right grip
    ImGuiWindowFlags_NoMove                 = 1 << 2,   // Disable user moving the window
    ImGuiWindowFlags_NoScrollbar            = 1 << 3,   // Disable scrollbars (window can still scroll with mouse or programatically)
    ImGuiWindowFlags_NoScrollWithMouse      = 1 << 4,   // Disable user vertically scrolling with mouse wheel. On child window, mouse wheel will be forwarded to the parent unless NoScrollbar is also set.
    ImGuiWindowFlags_NoCollapse             = 1 << 5,   // Disable user collapsing window by double-clicking on it
    ImGuiWindowFlags_AlwaysAutoResize       = 1 << 6,   // Resize every window to its content every frame
    ImGuiWindowFlags_NoSavedSettings        = 1 << 8,   // Never load/save settings in .ini file
    ImGuiWindowFlags_NoInputs               = 1 << 9,   // Disable catching mouse or keyboard inputs, hovering test with pass through.
    ImGuiWindowFlags_MenuBar                = 1 << 10,  // Has a menu-bar
    ImGuiWindowFlags_HorizontalScrollbar    = 1 << 11,  // Allow horizontal scrollbar to appear (off by default). You may use SetNextWindowContentSize(ImVec2(width,0.0f)); prior to calling Begin() to specify width. Read code in imgui_demo in the "Horizontal Scrolling" section.
    ImGuiWindowFlags_NoFocusOnAppearing     = 1 << 12,  // Disable taking focus when transitioning from hidden to visible state
    ImGuiWindowFlags_NoBringToFrontOnFocus  = 1 << 13,  // Disable bringing window to front when taking focus (e.g. clicking on it or programatically giving it focus)
    ImGuiWindowFlags_AlwaysVerticalScrollbar= 1 << 14,  // Always show vertical scrollbar (even if ContentSize.y < Size.y)
    ImGuiWindowFlags_AlwaysHorizontalScrollbar=1<< 15,  // Always show horizontal scrollbar (even if ContentSize.x < Size.x)
    ImGuiWindowFlags_AlwaysUseWindowPadding = 1 << 16,  // Ensure child windows without border uses style.WindowPadding (ignored by default for non-bordered child windows, because more convenient)
    ImGuiWindowFlags_NoNavInputs            = 1 << 18,  // No gamepad/keyboard navigation within the window
    ImGuiWindowFlags_NoNavFocus             = 1 << 19,  // No focusing toward this window with gamepad/keyboard navigation (e.g. skipped by CTRL+TAB)
    ImGuiWindowFlags_NoNav                  = ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus,
    // [Internal]
    ImGuiWindowFlags_NavFlattened           = 1 << 23,  // [BETA] Allow gamepad/keyboard navigation to cross over parent border to this child (only use on child that have no scrolling!)
    ImGuiWindowFlags_ChildWindow            = 1 << 24,  // Don't use! For internal use by BeginChild()
    ImGuiWindowFlags_Tooltip                = 1 << 25,  // Don't use! For internal use by BeginTooltip()
    ImGuiWindowFlags_Popup                  = 1 << 26,  // Don't use! For internal use by BeginPopup()
    ImGuiWindowFlags_Modal                  = 1 << 27,  // Don't use! For internal use by BeginPopupModal()
    ImGuiWindowFlags_ChildMenu              = 1 << 28   // Don't use! For internal use by BeginMenu()
    // [Obsolete]
    //ImGuiWindowFlags_ShowBorders          = 1 << 7,   // --> Set style.FrameBorderSize=1.0f / style.WindowBorderSize=1.0f to enable borders around windows and items
    //ImGuiWindowFlags_ResizeFromAnySide    = 1 << 17,  // --> Set io.ConfigResizeWindowsFromEdges and make sure mouse cursors are supported by back-end (io.BackendFlags & ImGuiBackendFlags_HasMouseCursors)
};
// Flags for ImGui::InputText()
enum ImGuiInputTextFlags_
{
    ImGuiInputTextFlags_None                = 0,
    ImGuiInputTextFlags_CharsDecimal        = 1 << 0,   // Allow 0123456789.+-*/
    ImGuiInputTextFlags_CharsHexadecimal    = 1 << 1,   // Allow 0123456789ABCDEFabcdef
    ImGuiInputTextFlags_CharsUppercase      = 1 << 2,   // Turn a..z into A..Z
    ImGuiInputTextFlags_CharsNoBlank        = 1 << 3,   // Filter out spaces, tabs
    ImGuiInputTextFlags_AutoSelectAll       = 1 << 4,   // Select entire text when first taking mouse focus
    ImGuiInputTextFlags_EnterReturnsTrue    = 1 << 5,   // Return 'true' when Enter is pressed (as opposed to when the value was modified)
    ImGuiInputTextFlags_CallbackCompletion  = 1 << 6,   // Call user function on pressing TAB (for completion handling)
    ImGuiInputTextFlags_CallbackHistory     = 1 << 7,   // Call user function on pressing Up/Down arrows (for history handling)
    ImGuiInputTextFlags_CallbackAlways      = 1 << 8,   // Call user function every time. User code may query cursor position, modify text buffer.
    ImGuiInputTextFlags_CallbackCharFilter  = 1 << 9,   // Call user function to filter character. Modify data->EventChar to replace/filter input, or return 1 in callback to discard character.
    ImGuiInputTextFlags_AllowTabInput       = 1 << 10,  // Pressing TAB input a '\t' character into the text field
    ImGuiInputTextFlags_CtrlEnterForNewLine = 1 << 11,  // In multi-line mode, unfocus with Enter, add new line with Ctrl+Enter (default is opposite: unfocus with Ctrl+Enter, add line with Enter).
    ImGuiInputTextFlags_NoHorizontalScroll  = 1 << 12,  // Disable following the cursor horizontally
    ImGuiInputTextFlags_AlwaysInsertMode    = 1 << 13,  // Insert mode
    ImGuiInputTextFlags_ReadOnly            = 1 << 14,  // Read-only mode
    ImGuiInputTextFlags_Password            = 1 << 15,  // Password mode, display all characters as '*'
    ImGuiInputTextFlags_NoUndoRedo          = 1 << 16,  // Disable undo/redo. Note that input text owns the text data while active, if you want to provide your own undo/redo stack you need e.g. to call ClearActiveID().
    ImGuiInputTextFlags_CharsScientific     = 1 << 17,  // Allow 0123456789.+-*/eE (Scientific notation input)
    ImGuiInputTextFlags_CallbackResize      = 1 << 18,  // Allow buffer capacity resize + notify when the string wants to be resized (for string types which hold a cache of their Size) (see misc/stl/imgui_stl.h for an example of using this)
    // [Internal]
    ImGuiInputTextFlags_Multiline           = 1 << 20   // For internal use by InputTextMultiline()
};
// Flags for ImGui::TreeNodeEx(), ImGui::CollapsingHeader*()
enum ImGuiTreeNodeFlags_
{
    ImGuiTreeNodeFlags_None                 = 0,
    ImGuiTreeNodeFlags_Selected             = 1 << 0,   // Draw as selected
    ImGuiTreeNodeFlags_Framed               = 1 << 1,   // Full colored frame (e.g. for CollapsingHeader)
    ImGuiTreeNodeFlags_AllowItemOverlap     = 1 << 2,   // Hit testing to allow subsequent widgets to overlap this one
    ImGuiTreeNodeFlags_NoTreePushOnOpen     = 1 << 3,   // Don't do a TreePush() when open (e.g. for CollapsingHeader) = no extra indent nor pushing on ID stack
    ImGuiTreeNodeFlags_NoAutoOpenOnLog      = 1 << 4,   // Don't automatically and temporarily open node when Logging is active (by default logging will automatically open tree nodes)
    ImGuiTreeNodeFlags_DefaultOpen          = 1 << 5,   // Default node to be open
    ImGuiTreeNodeFlags_OpenOnDoubleClick    = 1 << 6,   // Need double-click to open node
    ImGuiTreeNodeFlags_OpenOnArrow          = 1 << 7,   // Only open when clicking on the arrow part. If ImGuiTreeNodeFlags_OpenOnDoubleClick is also set, single-click arrow or double-click all box to open.
    ImGuiTreeNodeFlags_Leaf                 = 1 << 8,   // No collapsing, no arrow (use as a convenience for leaf nodes).
    ImGuiTreeNodeFlags_Bullet               = 1 << 9,   // Display a bullet instead of arrow
    ImGuiTreeNodeFlags_FramePadding         = 1 << 10,  // Use FramePadding (even for an unframed text node) to vertically align text baseline to regular widget height. Equivalent to calling AlignTextToFramePadding().
    //ImGuITreeNodeFlags_SpanAllAvailWidth  = 1 << 11,  // FIXME: TODO: Extend hit box horizontally even if not framed
    //ImGuiTreeNodeFlags_NoScrollOnOpen     = 1 << 12,  // FIXME: TODO: Disable automatic scroll on TreePop() if node got just open and contents is not visible
    ImGuiTreeNodeFlags_NavLeftJumpsBackHere = 1 << 13,  // (WIP) Nav: left direction may move to this TreeNode() from any of its child (items submitted between TreeNode and TreePop)
    ImGuiTreeNodeFlags_CollapsingHeader     = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_NoAutoOpenOnLog
    // Obsolete names (will be removed)
};
// Flags for ImGui::Selectable()
enum ImGuiSelectableFlags_
{
    ImGuiSelectableFlags_None               = 0,
    ImGuiSelectableFlags_DontClosePopups    = 1 << 0,   // Clicking this don't close parent popup window
    ImGuiSelectableFlags_SpanAllColumns     = 1 << 1,   // Selectable frame can span all columns (text will still fit in current column)
    ImGuiSelectableFlags_AllowDoubleClick   = 1 << 2,   // Generate press events on double clicks too
    ImGuiSelectableFlags_Disabled           = 1 << 3    // Cannot be selected, display greyed out text
};
// Flags for ImGui::BeginCombo()
enum ImGuiComboFlags_
{
    ImGuiComboFlags_None                    = 0,
    ImGuiComboFlags_PopupAlignLeft          = 1 << 0,   // Align the popup toward the left by default
    ImGuiComboFlags_HeightSmall             = 1 << 1,   // Max ~4 items visible. Tip: If you want your combo popup to be a specific size you can use SetNextWindowSizeConstraints() prior to calling BeginCombo()
    ImGuiComboFlags_HeightRegular           = 1 << 2,   // Max ~8 items visible (default)
    ImGuiComboFlags_HeightLarge             = 1 << 3,   // Max ~20 items visible
    ImGuiComboFlags_HeightLargest           = 1 << 4,   // As many fitting items as possible
    ImGuiComboFlags_NoArrowButton           = 1 << 5,   // Display on the preview box without the square arrow button
    ImGuiComboFlags_NoPreview               = 1 << 6,   // Display only a square arrow button
    ImGuiComboFlags_HeightMask_             = ImGuiComboFlags_HeightSmall | ImGuiComboFlags_HeightRegular | ImGuiComboFlags_HeightLarge | ImGuiComboFlags_HeightLargest
};
// Flags for ImGui::IsWindowFocused()
enum ImGuiFocusedFlags_
{
    ImGuiFocusedFlags_None                          = 0,
    ImGuiFocusedFlags_ChildWindows                  = 1 << 0,   // IsWindowFocused(): Return true if any children of the window is focused
    ImGuiFocusedFlags_RootWindow                    = 1 << 1,   // IsWindowFocused(): Test from root window (top most parent of the current hierarchy)
    ImGuiFocusedFlags_AnyWindow                     = 1 << 2,   // IsWindowFocused(): Return true if any window is focused
    ImGuiFocusedFlags_RootAndChildWindows           = ImGuiFocusedFlags_RootWindow | ImGuiFocusedFlags_ChildWindows
};
// Flags for ImGui::IsItemHovered(), ImGui::IsWindowHovered()
// Note: if you are trying to check whether your mouse should be dispatched to imgui or to your app, you should use the 'io.WantCaptureMouse' boolean for that. Please read the FAQ!
// Note: windows with the ImGuiWindowFlags_NoInputs flag are ignored by IsWindowHovered() calls.
enum ImGuiHoveredFlags_
{
    ImGuiHoveredFlags_None                          = 0,        // Return true if directly over the item/window, not obstructed by another window, not obstructed by an active popup or modal blocking inputs under them.
    ImGuiHoveredFlags_ChildWindows                  = 1 << 0,   // IsWindowHovered() only: Return true if any children of the window is hovered
    ImGuiHoveredFlags_RootWindow                    = 1 << 1,   // IsWindowHovered() only: Test from root window (top most parent of the current hierarchy)
    ImGuiHoveredFlags_AnyWindow                     = 1 << 2,   // IsWindowHovered() only: Return true if any window is hovered
    ImGuiHoveredFlags_AllowWhenBlockedByPopup       = 1 << 3,   // Return true even if a popup window is normally blocking access to this item/window
    //ImGuiHoveredFlags_AllowWhenBlockedByModal     = 1 << 4,   // Return true even if a modal popup window is normally blocking access to this item/window. FIXME-TODO: Unavailable yet.
    ImGuiHoveredFlags_AllowWhenBlockedByActiveItem  = 1 << 5,   // Return true even if an active item is blocking access to this item/window. Useful for Drag and Drop patterns.
    ImGuiHoveredFlags_AllowWhenOverlapped           = 1 << 6,   // Return true even if the position is overlapped by another window
    ImGuiHoveredFlags_AllowWhenDisabled             = 1 << 7,   // Return true even if the item is disabled
    ImGuiHoveredFlags_RectOnly                      = ImGuiHoveredFlags_AllowWhenBlockedByPopup | ImGuiHoveredFlags_AllowWhenBlockedByActiveItem | ImGuiHoveredFlags_AllowWhenOverlapped,
    ImGuiHoveredFlags_RootAndChildWindows           = ImGuiHoveredFlags_RootWindow | ImGuiHoveredFlags_ChildWindows
};
// Flags for ImGui::BeginDragDropSource(), ImGui::AcceptDragDropPayload()
enum ImGuiDragDropFlags_
{
    ImGuiDragDropFlags_None                         = 0,
    // BeginDragDropSource() flags
    ImGuiDragDropFlags_SourceNoPreviewTooltip       = 1 << 0,   // By default, a successful call to BeginDragDropSource opens a tooltip so you can display a preview or description of the source contents. This flag disable this behavior.
    ImGuiDragDropFlags_SourceNoDisableHover         = 1 << 1,   // By default, when dragging we clear data so that IsItemHovered() will return false, to avoid subsequent user code submitting tooltips. This flag disable this behavior so you can still call IsItemHovered() on the source item.
    ImGuiDragDropFlags_SourceNoHoldToOpenOthers     = 1 << 2,   // Disable the behavior that allows to open tree nodes and collapsing header by holding over them while dragging a source item.
    ImGuiDragDropFlags_SourceAllowNullID            = 1 << 3,   // Allow items such as Text(), Image() that have no unique identifier to be used as drag source, by manufacturing a temporary identifier based on their window-relative position. This is extremely unusual within the dear imgui ecosystem and so we made it explicit.
    ImGuiDragDropFlags_SourceExtern                 = 1 << 4,   // External source (from outside of imgui), won't attempt to read current item/window info. Will always return true. Only one Extern source can be active simultaneously.
    ImGuiDragDropFlags_SourceAutoExpirePayload      = 1 << 5,   // Automatically expire the payload if the source cease to be submitted (otherwise payloads are persisting while being dragged)
    // AcceptDragDropPayload() flags
    ImGuiDragDropFlags_AcceptBeforeDelivery         = 1 << 10,  // AcceptDragDropPayload() will returns true even before the mouse button is released. You can then call IsDelivery() to test if the payload needs to be delivered.
    ImGuiDragDropFlags_AcceptNoDrawDefaultRect      = 1 << 11,  // Do not draw the default highlight rectangle when hovering over target.
    ImGuiDragDropFlags_AcceptNoPreviewTooltip       = 1 << 12,  // Request hiding the BeginDragDropSource tooltip from the BeginDragDropTarget site.
    ImGuiDragDropFlags_AcceptPeekOnly               = ImGuiDragDropFlags_AcceptBeforeDelivery | ImGuiDragDropFlags_AcceptNoDrawDefaultRect  // For peeking ahead and inspecting the payload before delivery.
};
// Standard Drag and Drop payload types. You can define you own payload types using short strings. Types starting with '_' are defined by Dear ImGui.
// A primary data type
enum ImGuiDataType_
{
    ImGuiDataType_S32,      // int
    ImGuiDataType_U32,      // unsigned int
    ImGuiDataType_S64,      // long long, __int64
    ImGuiDataType_U64,      // unsigned long long, unsigned __int64
    ImGuiDataType_Float,    // float
    ImGuiDataType_Double,   // double
    ImGuiDataType_COUNT
};
// A cardinal direction
enum ImGuiDir_
{
    ImGuiDir_None    = -1,
    ImGuiDir_Left    = 0,
    ImGuiDir_Right   = 1,
    ImGuiDir_Up      = 2,
    ImGuiDir_Down    = 3,
    ImGuiDir_COUNT
};
// User fill ImGuiIO.KeyMap[] array with indices into the ImGuiIO.KeysDown[512] array
enum ImGuiKey_
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
    ImGuiKey_Insert,
    ImGuiKey_Delete,
    ImGuiKey_Backspace,
    ImGuiKey_Space,
    ImGuiKey_Enter,
    ImGuiKey_Escape,
    ImGuiKey_A,         // for text edit CTRL+A: select all
    ImGuiKey_C,         // for text edit CTRL+C: copy
    ImGuiKey_V,         // for text edit CTRL+V: paste
    ImGuiKey_X,         // for text edit CTRL+X: cut
    ImGuiKey_Y,         // for text edit CTRL+Y: redo
    ImGuiKey_Z,         // for text edit CTRL+Z: undo
    ImGuiKey_COUNT
};
// Gamepad/Keyboard directional navigation
// Keyboard: Set io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard to enable. NewFrame() will automatically fill io.NavInputs[] based on your io.KeysDown[] + io.KeyMap[] arrays.
// Gamepad:  Set io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad to enable. Back-end: set ImGuiBackendFlags_HasGamepad and fill the io.NavInputs[] fields before calling NewFrame(). Note that io.NavInputs[] is cleared by EndFrame().
// Read instructions in imgui.cpp for more details. Download PNG/PSD at http://goo.gl/9LgVZW.
enum ImGuiNavInput_
{
    // Gamepad Mapping
    ImGuiNavInput_Activate,      // activate / open / toggle / tweak value       // e.g. Cross  (PS4), A (Xbox), A (Switch), Space (Keyboard)
    ImGuiNavInput_Cancel,        // cancel / close / exit                        // e.g. Circle (PS4), B (Xbox), B (Switch), Escape (Keyboard)
    ImGuiNavInput_Input,         // text input / on-screen keyboard              // e.g. Triang.(PS4), Y (Xbox), X (Switch), Return (Keyboard)
    ImGuiNavInput_Menu,          // tap: toggle menu / hold: focus, move, resize // e.g. Square (PS4), X (Xbox), Y (Switch), Alt (Keyboard)
    ImGuiNavInput_DpadLeft,      // move / tweak / resize window (w/ PadMenu)    // e.g. D-pad Left/Right/Up/Down (Gamepads), Arrow keys (Keyboard)
    ImGuiNavInput_DpadRight,     //
    ImGuiNavInput_DpadUp,        //
    ImGuiNavInput_DpadDown,      //
    ImGuiNavInput_LStickLeft,    // scroll / move window (w/ PadMenu)            // e.g. Left Analog Stick Left/Right/Up/Down
    ImGuiNavInput_LStickRight,   //
    ImGuiNavInput_LStickUp,      //
    ImGuiNavInput_LStickDown,    //
    ImGuiNavInput_FocusPrev,     // next window (w/ PadMenu)                     // e.g. L1 or L2 (PS4), LB or LT (Xbox), L or ZL (Switch)
    ImGuiNavInput_FocusNext,     // prev window (w/ PadMenu)                     // e.g. R1 or R2 (PS4), RB or RT (Xbox), R or ZL (Switch)
    ImGuiNavInput_TweakSlow,     // slower tweaks                                // e.g. L1 or L2 (PS4), LB or LT (Xbox), L or ZL (Switch)
    ImGuiNavInput_TweakFast,     // faster tweaks                                // e.g. R1 or R2 (PS4), RB or RT (Xbox), R or ZL (Switch)
    // [Internal] Don't use directly! This is used internally to differentiate keyboard from gamepad inputs for behaviors that require to differentiate them.
    // Keyboard behavior that have no corresponding gamepad mapping (e.g. CTRL+TAB) will be directly reading from io.KeysDown[] instead of io.NavInputs[].
    ImGuiNavInput_KeyMenu_,      // toggle menu                                  // = io.KeyAlt
    ImGuiNavInput_KeyLeft_,      // move left                                    // = Arrow keys
    ImGuiNavInput_KeyRight_,     // move right
    ImGuiNavInput_KeyUp_,        // move up
    ImGuiNavInput_KeyDown_,      // move down
    ImGuiNavInput_COUNT,
    ImGuiNavInput_InternalStart_ = ImGuiNavInput_KeyMenu_
};
// Configuration flags stored in io.ConfigFlags. Set by user/application.
enum ImGuiConfigFlags_
{
    ImGuiConfigFlags_NavEnableKeyboard      = 1 << 0,   // Master keyboard navigation enable flag. NewFrame() will automatically fill io.NavInputs[] based on io.KeysDown[].
    ImGuiConfigFlags_NavEnableGamepad       = 1 << 1,   // Master gamepad navigation enable flag. This is mostly to instruct your imgui back-end to fill io.NavInputs[]. Back-end also needs to set ImGuiBackendFlags_HasGamepad.
    ImGuiConfigFlags_NavEnableSetMousePos   = 1 << 2,   // Instruct navigation to move the mouse cursor. May be useful on TV/console systems where moving a virtual mouse is awkward. Will update io.MousePos and set io.WantSetMousePos=true. If enabled you MUST honor io.WantSetMousePos requests in your binding, otherwise ImGui will react as if the mouse is jumping around back and forth.
    ImGuiConfigFlags_NavNoCaptureKeyboard   = 1 << 3,   // Instruct navigation to not set the io.WantCaptureKeyboard flag when io.NavActive is set.
    ImGuiConfigFlags_NoMouse                = 1 << 4,   // Instruct imgui to clear mouse position/buttons in NewFrame(). This allows ignoring the mouse information set by the back-end.
    ImGuiConfigFlags_NoMouseCursorChange    = 1 << 5,   // Instruct back-end to not alter mouse cursor shape and visibility. Use if the back-end cursor changes are interfering with yours and you don't want to use SetMouseCursor() to change mouse cursor. You may want to honor requests from imgui by reading GetMouseCursor() yourself instead.
    // User storage (to allow your back-end/engine to communicate to code that may be shared between multiple projects. Those flags are not used by core ImGui)
    ImGuiConfigFlags_IsSRGB                 = 1 << 20,  // Application is SRGB-aware.
    ImGuiConfigFlags_IsTouchScreen          = 1 << 21   // Application is using a touch screen instead of a mouse.
};
// Back-end capabilities flags stored in io.BackendFlags. Set by imgui_impl_xxx or custom back-end.
enum ImGuiBackendFlags_
{
    ImGuiBackendFlags_HasGamepad            = 1 << 0,   // Back-end supports gamepad and currently has one connected.
    ImGuiBackendFlags_HasMouseCursors       = 1 << 1,   // Back-end supports honoring GetMouseCursor() value to change the OS cursor shape.
    ImGuiBackendFlags_HasSetMousePos        = 1 << 2    // Back-end supports io.WantSetMousePos requests to reposition the OS mouse position (only used if ImGuiConfigFlags_NavEnableSetMousePos is set).
};
// Enumeration for PushStyleColor() / PopStyleColor()
enum ImGuiCol_
{
    ImGuiCol_Text,
    ImGuiCol_TextDisabled,
    ImGuiCol_WindowBg,              // Background of normal windows
    ImGuiCol_ChildBg,               // Background of child windows
    ImGuiCol_PopupBg,               // Background of popups, menus, tooltips windows
    ImGuiCol_Border,
    ImGuiCol_BorderShadow,
    ImGuiCol_FrameBg,               // Background of checkbox, radio button, plot, slider, text input
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
    ImGuiCol_PlotLines,
    ImGuiCol_PlotLinesHovered,
    ImGuiCol_PlotHistogram,
    ImGuiCol_PlotHistogramHovered,
    ImGuiCol_TextSelectedBg,
    ImGuiCol_DragDropTarget,
    ImGuiCol_NavHighlight,          // Gamepad/keyboard: current highlighted item
    ImGuiCol_NavWindowingHighlight, // Highlight window when using CTRL+TAB
    ImGuiCol_NavWindowingDimBg,     // Darken/colorize entire screen behind the CTRL+TAB window list, when active
    ImGuiCol_ModalWindowDimBg,      // Darken/colorize entire screen behind a modal window, when one is active
    ImGuiCol_COUNT
    // Obsolete names (will be removed)
};
// Enumeration for PushStyleVar() / PopStyleVar() to temporarily modify the ImGuiStyle structure.
// NB: the enum only refers to fields of ImGuiStyle which makes sense to be pushed/popped inside UI code. During initialization, feel free to just poke into ImGuiStyle directly.
// NB: if changing this enum, you need to update the associated internal table GStyleVarInfo[] accordingly. This is where we link enum values to members offset/type.
enum ImGuiStyleVar_
{
    // Enum name ......................// Member in ImGuiStyle structure (see ImGuiStyle for descriptions)
    ImGuiStyleVar_Alpha,               // float     Alpha
    ImGuiStyleVar_WindowPadding,       // ImVec2    WindowPadding
    ImGuiStyleVar_WindowRounding,      // float     WindowRounding
    ImGuiStyleVar_WindowBorderSize,    // float     WindowBorderSize
    ImGuiStyleVar_WindowMinSize,       // ImVec2    WindowMinSize
    ImGuiStyleVar_WindowTitleAlign,    // ImVec2    WindowTitleAlign
    ImGuiStyleVar_ChildRounding,       // float     ChildRounding
    ImGuiStyleVar_ChildBorderSize,     // float     ChildBorderSize
    ImGuiStyleVar_PopupRounding,       // float     PopupRounding
    ImGuiStyleVar_PopupBorderSize,     // float     PopupBorderSize
    ImGuiStyleVar_FramePadding,        // ImVec2    FramePadding
    ImGuiStyleVar_FrameRounding,       // float     FrameRounding
    ImGuiStyleVar_FrameBorderSize,     // float     FrameBorderSize
    ImGuiStyleVar_ItemSpacing,         // ImVec2    ItemSpacing
    ImGuiStyleVar_ItemInnerSpacing,    // ImVec2    ItemInnerSpacing
    ImGuiStyleVar_IndentSpacing,       // float     IndentSpacing
    ImGuiStyleVar_ScrollbarSize,       // float     ScrollbarSize
    ImGuiStyleVar_ScrollbarRounding,   // float     ScrollbarRounding
    ImGuiStyleVar_GrabMinSize,         // float     GrabMinSize
    ImGuiStyleVar_GrabRounding,        // float     GrabRounding
    ImGuiStyleVar_ButtonTextAlign,     // ImVec2    ButtonTextAlign
    ImGuiStyleVar_COUNT
    // Obsolete names (will be removed)
};
// Enumeration for ColorEdit3() / ColorEdit4() / ColorPicker3() / ColorPicker4() / ColorButton()
enum ImGuiColorEditFlags_
{
    ImGuiColorEditFlags_None            = 0,
    ImGuiColorEditFlags_NoAlpha         = 1 << 1,   //              // ColorEdit, ColorPicker, ColorButton: ignore Alpha component (read 3 components from the input pointer).
    ImGuiColorEditFlags_NoPicker        = 1 << 2,   //              // ColorEdit: disable picker when clicking on colored square.
    ImGuiColorEditFlags_NoOptions       = 1 << 3,   //              // ColorEdit: disable toggling options menu when right-clicking on inputs/small preview.
    ImGuiColorEditFlags_NoSmallPreview  = 1 << 4,   //              // ColorEdit, ColorPicker: disable colored square preview next to the inputs. (e.g. to show only the inputs)
    ImGuiColorEditFlags_NoInputs        = 1 << 5,   //              // ColorEdit, ColorPicker: disable inputs sliders/text widgets (e.g. to show only the small preview colored square).
    ImGuiColorEditFlags_NoTooltip       = 1 << 6,   //              // ColorEdit, ColorPicker, ColorButton: disable tooltip when hovering the preview.
    ImGuiColorEditFlags_NoLabel         = 1 << 7,   //              // ColorEdit, ColorPicker: disable display of inline text label (the label is still forwarded to the tooltip and picker).
    ImGuiColorEditFlags_NoSidePreview   = 1 << 8,   //              // ColorPicker: disable bigger color preview on right side of the picker, use small colored square preview instead.
    ImGuiColorEditFlags_NoDragDrop      = 1 << 9,   //              // ColorEdit: disable drag and drop target. ColorButton: disable drag and drop source.
    // User Options (right-click on widget to change some of them). You can set application defaults using SetColorEditOptions(). The idea is that you probably don't want to override them in most of your calls, let the user choose and/or call SetColorEditOptions() during startup.
    ImGuiColorEditFlags_AlphaBar        = 1 << 16,  //              // ColorEdit, ColorPicker: show vertical alpha bar/gradient in picker.
    ImGuiColorEditFlags_AlphaPreview    = 1 << 17,  //              // ColorEdit, ColorPicker, ColorButton: display preview as a transparent color over a checkerboard, instead of opaque.
    ImGuiColorEditFlags_AlphaPreviewHalf= 1 << 18,  //              // ColorEdit, ColorPicker, ColorButton: display half opaque / half checkerboard, instead of opaque.
    ImGuiColorEditFlags_HDR             = 1 << 19,  //              // (WIP) ColorEdit: Currently only disable 0.0f..1.0f limits in RGBA edition (note: you probably want to use ImGuiColorEditFlags_Float flag as well).
    ImGuiColorEditFlags_RGB             = 1 << 20,  // [Inputs]     // ColorEdit: choose one among RGB/HSV/HEX. ColorPicker: choose any combination using RGB/HSV/HEX.
    ImGuiColorEditFlags_HSV             = 1 << 21,  // [Inputs]     // "
    ImGuiColorEditFlags_HEX             = 1 << 22,  // [Inputs]     // "
    ImGuiColorEditFlags_Uint8           = 1 << 23,  // [DataType]   // ColorEdit, ColorPicker, ColorButton: _display_ values formatted as 0..255.
    ImGuiColorEditFlags_Float           = 1 << 24,  // [DataType]   // ColorEdit, ColorPicker, ColorButton: _display_ values formatted as 0.0f..1.0f floats instead of 0..255 integers. No round-trip of value via integers.
    ImGuiColorEditFlags_PickerHueBar    = 1 << 25,  // [PickerMode] // ColorPicker: bar for Hue, rectangle for Sat/Value.
    ImGuiColorEditFlags_PickerHueWheel  = 1 << 26,  // [PickerMode] // ColorPicker: wheel for Hue, triangle for Sat/Value.
    // [Internal] Masks
    ImGuiColorEditFlags__InputsMask     = ImGuiColorEditFlags_RGB|ImGuiColorEditFlags_HSV|ImGuiColorEditFlags_HEX,
    ImGuiColorEditFlags__DataTypeMask   = ImGuiColorEditFlags_Uint8|ImGuiColorEditFlags_Float,
    ImGuiColorEditFlags__PickerMask     = ImGuiColorEditFlags_PickerHueWheel|ImGuiColorEditFlags_PickerHueBar,
    ImGuiColorEditFlags__OptionsDefault = ImGuiColorEditFlags_Uint8|ImGuiColorEditFlags_RGB|ImGuiColorEditFlags_PickerHueBar    // Change application default using SetColorEditOptions()
};
// Enumeration for GetMouseCursor()
// User code may request binding to display given cursor by calling SetMouseCursor(), which is why we have some cursors that are marked unused here
enum ImGuiMouseCursor_
{
    ImGuiMouseCursor_None = -1,
    ImGuiMouseCursor_Arrow = 0,
    ImGuiMouseCursor_TextInput,         // When hovering over InputText, etc.
    ImGuiMouseCursor_ResizeAll,         // (Unused by imgui functions)
    ImGuiMouseCursor_ResizeNS,          // When hovering over an horizontal border
    ImGuiMouseCursor_ResizeEW,          // When hovering over a vertical border or a column
    ImGuiMouseCursor_ResizeNESW,        // When hovering over the bottom-left corner of a window
    ImGuiMouseCursor_ResizeNWSE,        // When hovering over the bottom-right corner of a window
    ImGuiMouseCursor_Hand,              // (Unused by imgui functions. Use for e.g. hyperlinks)
    ImGuiMouseCursor_COUNT
    // Obsolete names (will be removed)
};
// Condition for ImGui::SetWindow***(), SetNextWindow***(), SetNextTreeNode***() functions
// Important: Treat as a regular enum! Do NOT combine multiple values using binary operators! All the functions above treat 0 as a shortcut to ImGuiCond_Always.
enum ImGuiCond_
{
    ImGuiCond_Always        = 1 << 0,   // Set the variable
    ImGuiCond_Once          = 1 << 1,   // Set the variable once per runtime session (only the first call with succeed)
    ImGuiCond_FirstUseEver  = 1 << 2,   // Set the variable if the object/window has no persistently saved data (no entry in .ini file)
    ImGuiCond_Appearing     = 1 << 3    // Set the variable if the object/window is appearing after being hidden/inactive (or the first time)
    // Obsolete names (will be removed)
};
// You may modify the ImGui::GetStyle() main instance during initialization and before NewFrame().
// During the frame, use ImGui::PushStyleVar(ImGuiStyleVar_XXXX)/PopStyleVar() to alter the main style values, and ImGui::PushStyleColor(ImGuiCol_XXX)/PopStyleColor() for colors.
struct ImGuiStyle
{
    float       Alpha;                      // Global alpha applies to everything in ImGui.
    ImVec2      WindowPadding;              // Padding within a window.
    float       WindowRounding;             // Radius of window corners rounding. Set to 0.0f to have rectangular windows.
    float       WindowBorderSize;           // Thickness of border around windows. Generally set to 0.0f or 1.0f. (Other values are not well tested and more CPU/GPU costly).
    ImVec2      WindowMinSize;              // Minimum window size. This is a global setting. If you want to constraint individual windows, use SetNextWindowSizeConstraints().
    ImVec2      WindowTitleAlign;           // Alignment for title bar text. Defaults to (0.0f,0.5f) for left-aligned,vertically centered.
    float       ChildRounding;              // Radius of child window corners rounding. Set to 0.0f to have rectangular windows.
    float       ChildBorderSize;            // Thickness of border around child windows. Generally set to 0.0f or 1.0f. (Other values are not well tested and more CPU/GPU costly).
    float       PopupRounding;              // Radius of popup window corners rounding. (Note that tooltip windows use WindowRounding)
    float       PopupBorderSize;            // Thickness of border around popup/tooltip windows. Generally set to 0.0f or 1.0f. (Other values are not well tested and more CPU/GPU costly).
    ImVec2      FramePadding;               // Padding within a framed rectangle (used by most widgets).
    float       FrameRounding;              // Radius of frame corners rounding. Set to 0.0f to have rectangular frame (used by most widgets).
    float       FrameBorderSize;            // Thickness of border around frames. Generally set to 0.0f or 1.0f. (Other values are not well tested and more CPU/GPU costly).
    ImVec2      ItemSpacing;                // Horizontal and vertical spacing between widgets/lines.
    ImVec2      ItemInnerSpacing;           // Horizontal and vertical spacing between within elements of a composed widget (e.g. a slider and its label).
    ImVec2      TouchExtraPadding;          // Expand reactive bounding box for touch-based system where touch position is not accurate enough. Unfortunately we don't sort widgets so priority on overlap will always be given to the first widget. So don't grow this too much!
    float       IndentSpacing;              // Horizontal indentation when e.g. entering a tree node. Generally == (FontSize + FramePadding.x*2).
    float       ColumnsMinSpacing;          // Minimum horizontal spacing between two columns.
    float       ScrollbarSize;              // Width of the vertical scrollbar, Height of the horizontal scrollbar.
    float       ScrollbarRounding;          // Radius of grab corners for scrollbar.
    float       GrabMinSize;                // Minimum width/height of a grab box for slider/scrollbar.
    float       GrabRounding;               // Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
    ImVec2      ButtonTextAlign;            // Alignment of button text when button is larger than text. Defaults to (0.5f,0.5f) for horizontally+vertically centered.
    ImVec2      DisplayWindowPadding;       // Window position are clamped to be visible within the display area by at least this amount. Only applies to regular windows.
    ImVec2      DisplaySafeAreaPadding;     // If you cannot see the edges of your screen (e.g. on a TV) increase the safe area padding. Apply to popups/tooltips as well regular windows. NB: Prefer configuring your TV sets correctly!
    float       MouseCursorScale;           // Scale software rendered mouse cursor (when io.MouseDrawCursor is enabled). May be removed later.
    bool        AntiAliasedLines;           // Enable anti-aliasing on lines/borders. Disable if you are really tight on CPU/GPU.
    bool        AntiAliasedFill;            // Enable anti-aliasing on filled shapes (rounded rectangles, circles, etc.)
    float       CurveTessellationTol;       // Tessellation tolerance when using PathBezierCurveTo() without a specific number of segments. Decrease for highly tessellated curves (higher quality, more polygons), increase to reduce quality.
    ImVec4      Colors[ImGuiCol_COUNT];
};
// This is where your app communicate with Dear ImGui. Access via ImGui::GetIO().
// Read 'Programmer guide' section in .cpp file for general usage.
struct ImGuiIO
{
    //------------------------------------------------------------------
    // Configuration (fill once)            // Default value:
    //------------------------------------------------------------------
    ImGuiConfigFlags   ConfigFlags;         // = 0                  // See ImGuiConfigFlags_ enum. Set by user/application. Gamepad/keyboard navigation options, etc.
    ImGuiBackendFlags  BackendFlags;        // = 0                  // Set ImGuiBackendFlags_ enum. Set by imgui_impl_xxx files or custom back-end to communicate features supported by the back-end.
    ImVec2        DisplaySize;              // <unset>              // Main display size, in pixels. For clamping windows positions.
    float         DeltaTime;                // = 1.0f/60.0f         // Time elapsed since last frame, in seconds.
    float         IniSavingRate;            // = 5.0f               // Minimum time between saving positions/sizes to .ini file, in seconds.
    const char*   IniFilename;              // = "imgui.ini"        // Path to .ini file. Set NULL to disable automatic .ini loading/saving, if e.g. you want to manually load/save from memory.
    const char*   LogFilename;              // = "imgui_log.txt"    // Path to .log file (default parameter to ImGui::LogToFile when no file is specified).
    float         MouseDoubleClickTime;     // = 0.30f              // Time for a double-click, in seconds.
    float         MouseDoubleClickMaxDist;  // = 6.0f               // Distance threshold to stay in to validate a double-click, in pixels.
    float         MouseDragThreshold;       // = 6.0f               // Distance threshold before considering we are dragging.
    int           KeyMap[ImGuiKey_COUNT];   // <unset>              // Map of indices into the KeysDown[512] entries array which represent your "native" keyboard state.
    float         KeyRepeatDelay;           // = 0.250f             // When holding a key/button, time before it starts repeating, in seconds (for buttons in Repeat mode, etc.).
    float         KeyRepeatRate;            // = 0.050f             // When holding a key/button, rate at which it repeats, in seconds.
    void*         UserData;                 // = NULL               // Store your own data for retrieval by callbacks.
    ImFontAtlas*  Fonts;                    // <auto>               // Load and assemble one or more fonts into a single tightly packed texture. Output to Fonts array.
    float         FontGlobalScale;          // = 1.0f               // Global scale all fonts
    bool          FontAllowUserScaling;     // = false              // Allow user scaling text of individual window with CTRL+Wheel.
    ImFont*       FontDefault;              // = NULL               // Font to use on NewFrame(). Use NULL to uses Fonts->Fonts[0].
    ImVec2        DisplayFramebufferScale;  // = (1.0f,1.0f)        // For retina display or other situations where window coordinates are different from framebuffer coordinates. User storage only, presently not used by ImGui.
    ImVec2        DisplayVisibleMin;        // <unset> (0.0f,0.0f)  // [obsolete] If you use DisplaySize as a virtual space larger than your screen, set DisplayVisibleMin/Max to the visible area.
    ImVec2        DisplayVisibleMax;        // <unset> (0.0f,0.0f)  // [obsolete: just use io.DisplaySize] If the values are the same, we defaults to Min=(0.0f) and Max=DisplaySize
    // Miscellaneous configuration options
    bool          MouseDrawCursor;              // = false          // Request ImGui to draw a mouse cursor for you (if you are on a platform without a mouse cursor). Cannot be easily renamed to 'io.ConfigXXX' because this is frequently used by back-end implementations.
    bool          ConfigMacOSXBehaviors;        // = defined(__APPLE__) // OS X style: Text editing cursor movement using Alt instead of Ctrl, Shortcuts using Cmd/Super instead of Ctrl, Line/Text Start and End using Cmd+Arrows instead of Home/End, Double click selects by word instead of selecting whole text, Multi-selection in lists uses Cmd/Super instead of Ctrl (was called io.OptMacOSXBehaviors prior to 1.63)
    bool          ConfigInputTextCursorBlink;   // = true           // Set to false to disable blinking cursor, for users who consider it distracting. (was called: io.OptCursorBlink prior to 1.63)
    bool          ConfigResizeWindowsFromEdges; // = false          // [BETA] Enable resizing of windows from their edges and from the lower-left corner. This requires (io.BackendFlags & ImGuiBackendFlags_HasMouseCursors) because it needs mouse cursor feedback. (This used to be the ImGuiWindowFlags_ResizeFromAnySide flag)
    //------------------------------------------------------------------
    // Settings (User Functions)
    //------------------------------------------------------------------
    // Optional: access OS clipboard
    // (default to use native Win32 clipboard on Windows, otherwise uses a private clipboard. Override to access OS clipboard on other architectures)
    const char* (*GetClipboardTextFn)(void* user_data);
    void        (*SetClipboardTextFn)(void* user_data, const char* text);
    void*       ClipboardUserData;
    // Optional: notify OS Input Method Editor of the screen position of your cursor for text input position (e.g. when using Japanese/Chinese IME in Windows)
    // (default to use native imm32 api on Windows)
    void        (*ImeSetInputScreenPosFn)(int x, int y);
    void*       ImeWindowHandle;            // (Windows) Set this to your HWND to get automatic IME cursor positioning.
    //------------------------------------------------------------------
    // Input - Fill before calling NewFrame()
    //------------------------------------------------------------------
    ImVec2      MousePos;                       // Mouse position, in pixels. Set to ImVec2(-FLT_MAX,-FLT_MAX) if mouse is unavailable (on another screen, etc.)
    bool        MouseDown[5];                   // Mouse buttons: 0=left, 1=right, 2=middle + extras. ImGui itself mostly only uses left button (BeginPopupContext** are using right button). Others buttons allows us to track if the mouse is being used by your application + available to user as a convenience via IsMouse** API.
    float       MouseWheel;                     // Mouse wheel Vertical: 1 unit scrolls about 5 lines text.
    float       MouseWheelH;                    // Mouse wheel Horizontal. Most users don't have a mouse with an horizontal wheel, may not be filled by all back-ends.
    bool        KeyCtrl;                        // Keyboard modifier pressed: Control
    bool        KeyShift;                       // Keyboard modifier pressed: Shift
    bool        KeyAlt;                         // Keyboard modifier pressed: Alt
    bool        KeySuper;                       // Keyboard modifier pressed: Cmd/Super/Windows
    bool        KeysDown[512];                  // Keyboard keys that are pressed (ideally left in the "native" order your engine has access to keyboard keys, so you can use your own defines/enums for keys).
    ImWchar     InputCharacters[16+1];          // List of characters input (translated by user from keypress+keyboard state). Fill using AddInputCharacter() helper.
    float       NavInputs[ImGuiNavInput_COUNT]; // Gamepad inputs (keyboard keys will be auto-mapped and be written here by ImGui::NewFrame, all values will be cleared back to zero in ImGui::EndFrame)
    // Functions
    //------------------------------------------------------------------
    // Output - Retrieve after calling NewFrame()
    //------------------------------------------------------------------
    bool        WantCaptureMouse;           // When io.WantCaptureMouse is true, imgui will use the mouse inputs, do not dispatch them to your main game/application (in both cases, always pass on mouse inputs to imgui). (e.g. unclicked mouse is hovering over an imgui window, widget is active, mouse was clicked over an imgui window, etc.).
    bool        WantCaptureKeyboard;        // When io.WantCaptureKeyboard is true, imgui will use the keyboard inputs, do not dispatch them to your main game/application (in both cases, always pass keyboard inputs to imgui). (e.g. InputText active, or an imgui window is focused and navigation is enabled, etc.).
    bool        WantTextInput;              // Mobile/console: when io.WantTextInput is true, you may display an on-screen keyboard. This is set by ImGui when it wants textual keyboard input to happen (e.g. when a InputText widget is active).
    bool        WantSetMousePos;            // MousePos has been altered, back-end should reposition mouse on next frame. Set only when ImGuiConfigFlags_NavEnableSetMousePos flag is enabled.
    bool        WantSaveIniSettings;        // When manual .ini load/save is active (io.IniFilename == NULL), this will be set to notify your application that you can call SaveIniSettingsToMemory() and save yourself. IMPORTANT: You need to clear io.WantSaveIniSettings yourself.
    bool        NavActive;                  // Directional navigation is currently allowed (will handle ImGuiKey_NavXXX events) = a window is focused and it doesn't use the ImGuiWindowFlags_NoNavInputs flag.
    bool        NavVisible;                 // Directional navigation is visible and allowed (will handle ImGuiKey_NavXXX events).
    float       Framerate;                  // Application framerate estimation, in frame per second. Solely for convenience. Rolling average estimation based on IO.DeltaTime over 120 frames
    int         MetricsRenderVertices;      // Vertices output during last call to Render()
    int         MetricsRenderIndices;       // Indices output during last call to Render() = number of triangles * 3
    int         MetricsRenderWindows;       // Number of visible windows
    int         MetricsActiveWindows;       // Number of active windows
    int         MetricsActiveAllocations;   // Number of active allocations, updated by MemAlloc/MemFree based on current context. May be off if you have multiple imgui contexts.
    ImVec2      MouseDelta;                 // Mouse delta. Note that this is zero if either current or previous position are invalid (-FLT_MAX,-FLT_MAX), so a disappearing/reappearing mouse won't have a huge delta.
    //------------------------------------------------------------------
    // [Internal] ImGui will maintain those fields. Forward compatibility not guaranteed!
    //------------------------------------------------------------------
    ImVec2      MousePosPrev;               // Previous mouse position temporary storage (nb: not for public use, set to MousePos in NewFrame())
    ImVec2      MouseClickedPos[5];         // Position at time of clicking
    double      MouseClickedTime[5];        // Time of last click (used to figure out double-click)
    bool        MouseClicked[5];            // Mouse button went from !Down to Down
    bool        MouseDoubleClicked[5];      // Has mouse button been double-clicked?
    bool        MouseReleased[5];           // Mouse button went from Down to !Down
    bool        MouseDownOwned[5];          // Track if button was clicked inside a window. We don't request mouse capture from the application if click started outside ImGui bounds.
    float       MouseDownDuration[5];       // Duration the mouse button has been down (0.0f == just clicked)
    float       MouseDownDurationPrev[5];   // Previous time the mouse button has been down
    ImVec2      MouseDragMaxDistanceAbs[5]; // Maximum distance, absolute, on each axis, of how much mouse has traveled from the clicking point
    float       MouseDragMaxDistanceSqr[5]; // Squared maximum distance of how much mouse has traveled from the clicking point
    float       KeysDownDuration[512];      // Duration the keyboard key has been down (0.0f == just pressed)
    float       KeysDownDurationPrev[512];  // Previous duration the key has been down
    float       NavInputsDownDuration[ImGuiNavInput_COUNT];
    float       NavInputsDownDurationPrev[ImGuiNavInput_COUNT];
};
//-----------------------------------------------------------------------------
// Obsolete functions (Will be removed! Read 'API BREAKING CHANGES' section in imgui.cpp for details)
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Helpers
//-----------------------------------------------------------------------------
// Helper: Lightweight std::vector<> like class to avoid dragging dependencies (also: Windows implementation of STL with debug enabled is absurdly slow, so let's bypass it so our code runs fast in debug).
// *Important* Our implementation does NOT call C++ constructors/destructors. This is intentional, we do not require it but you have to be mindful of that. Do _not_ use this class as a std::vector replacement in your code!
struct ImVector
{
    int Size;
    int Capacity;
    void* Data;
};
typedef struct ImVector ImVector;
// Helper: IM_NEW(), IM_PLACEMENT_NEW(), IM_DELETE() macros to call MemAlloc + Placement New, Placement Delete + MemFree
// We call C++ constructor on own allocated memory via the placement "new(ptr) Type()" syntax.
// Defining a custom placement new() with a dummy parameter allows us to bypass including <new> which on some platforms complains when user has disabled exceptions.
struct ImNewDummy {};
// Helper: Execute a block of code at maximum once a frame. Convenient if you want to quickly create an UI within deep-nested code that runs multiple times every frame.
// Usage: static ImGuiOnceUponAFrame oaf; if (oaf) ImGui::Text("This will be called only once per frame");
struct ImGuiOnceUponAFrame
{
     int RefFrame;
};
// Helper: Macro for ImGuiOnceUponAFrame. Attention: The macro expands into 2 statement so make sure you don't use it within e.g. an if() statement without curly braces.
// Helper: Parse and apply text filters. In format "aaaaa[,bbbb][,ccccc]"
struct ImGuiTextFilter
{
    // [Internal]
    char                InputBuf[256];
    ImVector/*<TextRange>*/ Filters;
    int                 CountGrep;
};
// Helper: Text buffer for logging/accumulating text
struct ImGuiTextBuffer
{
    ImVector/*<char>*/      Buf;
};
// Helper: key->value storage
// Typically you don't have to worry about this since a storage is held within each Window.
// We use it to e.g. store collapse state for a tree (Int 0/1)
// This is optimized for efficient lookup (dichotomy into a contiguous buffer) and rare insertion (typically tied to user interactions aka max once a frame)
// You can use it as custom user storage for temporary values. Declare your own storage if, for example:
// - You want to manipulate the open/close state of a particular sub-tree in your interface (tree node uses Int 0/1 to store their state).
// - You want to store custom debug data easily without adding or editing structures in your code (probably not efficient, but convenient)
// Types are NOT stored, so it is up to you to make sure your Key don't collide with different types.
struct ImGuiStorage
{
    ImVector/*<Pair>*/      Data;
    // - Get***() functions find pair, never add/allocate. Pairs are sorted so a query is O(log N)
    // - Set***() functions find pair, insertion on demand if missing.
    // - Sorted insertion is costly, paid once. A typical frame shouldn't need to insert any new pair.
    // - Get***Ref() functions finds pair, insert on demand if missing, return pointer. Useful if you intend to do Get+Set.
    // - References are only valid until a new value is added to the storage. Calling a Set***() function or a Get***Ref() function invalidates the pointer.
    // - A typical use case where this is convenient for quick hacking (e.g. add storage during a live Edit&Continue session if you can't modify existing struct)
    //      float* pvar = ImGui::GetFloatRef(key); ImGui::SliderFloat("var", pvar, 0, 100.0f); some_var += *pvar;
    // Use on your own storage if you know only integer are being stored (open/close all tree nodes)
    // For quicker full rebuild of a storage (instead of an incremental one), you may add all your contents and then sort once.
};
// Shared state of InputText(), passed as an argument to your callback when a ImGuiInputTextFlags_Callback* flag is used.
// The callback function should return 0 by default.
// Special processing:
// - ImGuiInputTextFlags_CallbackCharFilter:  return 1 if the character is not allowed. You may also set 'EventChar=0' as any character replacement are allowed.
// - ImGuiInputTextFlags_CallbackResize:      notified by InputText() when the string is resized. BufTextLen is set to the new desired string length so you can update the string size on your side of the fence. You can also replace Buf pointer if your underlying data is reallocated. No need to initialize new characters or zero-terminator as InputText will do it right after the resize callback.
struct ImGuiInputTextCallbackData
{
    ImGuiInputTextFlags EventFlag;      // One ImGuiInputTextFlags_Callback*    // Read-only
    ImGuiInputTextFlags Flags;          // What user passed to InputText()      // Read-only
    void*               UserData;       // What user passed to InputText()      // Read-only
    // Arguments for the different callback events
    // - To modify the text buffer in a callback, prefer using the InsertChars() / DeleteChars() function. InsertChars() will take care of calling the resize callback if necessary.
    // - If you know your edits are not going to resize the underlying buffer allocation, you may modify the contents of 'Buf[]' directly. You need to update 'BufTextLen' accordingly (0 <= BufTextLen < BufSize) and set 'BufDirty'' to true so InputText can update its internal state.
    ImWchar             EventChar;      // Character input                      // Read-write   // [CharFilter] Replace character or set to zero. return 1 is equivalent to setting EventChar=0;
    ImGuiKey            EventKey;       // Key pressed (Up/Down/TAB)            // Read-only    // [Completion,History]
    char*               Buf;            // Text buffer                          // Read-write   // [Resize] Can replace pointer / [Completion,History,Always] Only write to pointed data, don't replace the actual pointer!
    int                 BufTextLen;     // Text length in bytes                 // Read-write   // [Resize,Completion,History,Always] Exclude zero-terminator storage. In C land: == strlen(some_text), in C++ land: string.length()
    int                 BufSize;        // Buffer capacity in bytes             // Read-only    // [Resize,Completion,History,Always] Include zero-terminator storage. In C land == ARRAYSIZE(my_char_array), in C++ land: string.capacity()+1
    bool                BufDirty;       // Set if you modify Buf/BufTextLen!!   // Write        // [Completion,History,Always]
    int                 CursorPos;      //                                      // Read-write   // [Completion,History,Always]
    int                 SelectionStart; //                                      // Read-write   // [Completion,History,Always] == to SelectionEnd when no selection)
    int                 SelectionEnd;   //                                      // Read-write   // [Completion,History,Always]
    // Helper functions for text manipulation.
    // Use those function to benefit from the CallbackResize behaviors. Calling those function reset the selection.
};
// Resizing callback data to apply custom constraint. As enabled by SetNextWindowSizeConstraints(). Callback is called during the next Begin().
// NB: For basic min/max size constraint on each axis you don't need to use the callback! The SetNextWindowSizeConstraints() parameters are enough.
struct ImGuiSizeCallbackData
{
    void*   UserData;       // Read-only.   What user passed to SetNextWindowSizeConstraints()
    ImVec2  Pos;            // Read-only.   Window position, for reference.
    ImVec2  CurrentSize;    // Read-only.   Current window size.
    ImVec2  DesiredSize;    // Read-write.  Desired size, based on user's mouse position. Write to this field to restrain resizing.
};
// Data payload for Drag and Drop operations
struct ImGuiPayload
{
    // Members
    void*           Data;               // Data (copied and owned by dear imgui)
    int             DataSize;           // Data size
    // [Internal]
    ImGuiID         SourceId;           // Source item id
    ImGuiID         SourceParentId;     // Source parent id (if available)
    int             DataFrameCount;     // Data timestamp
    char            DataType[32+1];     // Data type tag (short user-supplied string, 32 characters max)
    bool            Preview;            // Set when AcceptDragDropPayload() was called and mouse has been hovering the target item (nb: handle overlapping drag targets)
    bool            Delivery;           // Set when AcceptDragDropPayload() was called and mouse button is released over the target item.
};
// Helpers macros to generate 32-bits encoded colors
// Helper: ImColor() implicity converts colors to either ImU32 (packed 4x1 byte) or ImVec4 (4x1 float)
// Prefer using IM_COL32() macros if you want a guaranteed compile-time ImU32 for usage with ImDrawList API.
// **Avoid storing ImColor! Store either u32 of ImVec4. This is not a full-featured color class. MAY OBSOLETE.
// **None of the ImGui API are using ImColor directly but you can use it as a convenience to pass colors in either ImU32 or ImVec4 formats. Explicitly cast to ImU32 or ImVec4 if needed.
struct ImColor
{
    ImVec4              Value;
    // FIXME-OBSOLETE: May need to obsolete/cleanup those helpers.
};
// Helper: Manually clip large list of items.
// If you are submitting lots of evenly spaced items and you have a random access to the list, you can perform coarse clipping based on visibility to save yourself from processing those items at all.
// The clipper calculates the range of visible items and advance the cursor to compensate for the non-visible items we have skipped.
// ImGui already clip items based on their bounds but it needs to measure text size to do so. Coarse clipping before submission makes this cost and your own data fetching/submission cost null.
// Usage:
//     ImGuiListClipper clipper(1000);  // we have 1000 elements, evenly spaced.
//     while (clipper.Step())
//         for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
//             ImGui::Text("line number d", i);
// - Step 0: the clipper let you process the first element, regardless of it being visible or not, so we can measure the element height (step skipped if we passed a known height as second arg to constructor).
// - Step 1: the clipper infer height from first element, calculate the actual range of elements to display, and position the cursor before the first element.
// - (Step 2: dummy step only required if an explicit items_height was passed to constructor or Begin() and user call Step(). Does nothing and switch to Step 3.)
// - Step 3: the clipper validate that we have reached the expected Y position (corresponding to element DisplayEnd), advance the cursor to the end of the list and then returns 'false' to end the loop.
struct ImGuiListClipper
{
    float   StartPosY;
    float   ItemsHeight;
    int     ItemsCount, StepNo, DisplayStart, DisplayEnd;
    // items_count:  Use -1 to ignore (you can call Begin later). Use INT_MAX if you don't know how many items you have (in which case the cursor won't be advanced in the final step).
    // items_height: Use -1.0f to be calculated automatically on first step. Otherwise pass in the distance between your items, typically GetTextLineHeightWithSpacing() or GetFrameHeightWithSpacing().
    // If you don't specify an items_height, you NEED to call Step(). If you specify items_height you may call the old Begin()/End() api directly, but prefer calling Step().
};
//-----------------------------------------------------------------------------
// Draw List
// Hold a series of drawing commands. The user provides a renderer for ImDrawData which essentially contains an array of ImDrawList.
//-----------------------------------------------------------------------------
// Draw callbacks for advanced uses.
// NB- You most likely do NOT need to use draw callbacks just to create your own widget or customized UI rendering (you can poke into the draw list for that)
// Draw callback may be useful for example, A) Change your GPU render state, B) render a complex 3D scene inside a UI element (without an intermediate texture/render target), etc.
// The expected behavior from your rendering function is 'if (cmd.UserCallback != NULL) cmd.UserCallback(parent_list, cmd); else RenderTriangles()'
typedef void (*ImDrawCallback)(const ImDrawList* parent_list, const ImDrawCmd* cmd);
// Typically, 1 command = 1 GPU draw call (unless command is a callback)
struct ImDrawCmd
{
    unsigned int    ElemCount;              // Number of indices (multiple of 3) to be rendered as triangles. Vertices are stored in the callee ImDrawList's vtx_buffer[] array, indices in idx_buffer[].
    ImVec4          ClipRect;               // Clipping rectangle (x1, y1, x2, y2). Subtract ImDrawData->DisplayPos to get clipping rectangle in "viewport" coordinates
    ImTextureID     TextureId;              // User-provided texture ID. Set by user in ImfontAtlas::SetTexID() for fonts or passed to Image*() functions. Ignore if never using images or multiple fonts atlas.
    ImDrawCallback  UserCallback;           // If != NULL, call the function instead of rendering the vertices. clip_rect and texture_id will be set normally.
    void*           UserCallbackData;       // The draw callback code can access this.
};
// Vertex index (override with '#define ImDrawIdx unsigned int' inside in imconfig.h)
// Vertex layout
// Draw channels are used by the Columns API to "split" the render list into different channels while building, so items of each column can be batched together.
// You can also use them to simulate drawing layers and submit primitives in a different order than how they will be rendered.
struct ImDrawChannel
{
    ImVector/*<ImDrawCmd>*/     CmdBuffer;
    ImVector/*<ImDrawIdx>*/     IdxBuffer;
};
enum ImDrawCornerFlags_
{
    ImDrawCornerFlags_TopLeft   = 1 << 0, // 0x1
    ImDrawCornerFlags_TopRight  = 1 << 1, // 0x2
    ImDrawCornerFlags_BotLeft   = 1 << 2, // 0x4
    ImDrawCornerFlags_BotRight  = 1 << 3, // 0x8
    ImDrawCornerFlags_Top       = ImDrawCornerFlags_TopLeft | ImDrawCornerFlags_TopRight,   // 0x3
    ImDrawCornerFlags_Bot       = ImDrawCornerFlags_BotLeft | ImDrawCornerFlags_BotRight,   // 0xC
    ImDrawCornerFlags_Left      = ImDrawCornerFlags_TopLeft | ImDrawCornerFlags_BotLeft,    // 0x5
    ImDrawCornerFlags_Right     = ImDrawCornerFlags_TopRight | ImDrawCornerFlags_BotRight,  // 0xA
    ImDrawCornerFlags_All       = 0xF     // In your function calls you may use ~0 (= all bits sets) instead of ImDrawCornerFlags_All, as a convenience
};
enum ImDrawListFlags_
{
    ImDrawListFlags_AntiAliasedLines = 1 << 0,
    ImDrawListFlags_AntiAliasedFill  = 1 << 1
};
// Draw command list
// This is the low-level list of polygons that ImGui functions are filling. At the end of the frame, all command lists are passed to your ImGuiIO::RenderDrawListFn function for rendering.
// Each ImGui window contains its own ImDrawList. You can use ImGui::GetWindowDrawList() to access the current window draw list and draw custom primitives.
// You can interleave normal ImGui:: calls and adding primitives to the current draw list.
// All positions are generally in pixel coordinates (top-left at (0,0), bottom-right at io.DisplaySize), but you are totally free to apply whatever transformation matrix to want to the data (if you apply such transformation you'll want to apply it to ClipRect as well)
// Important: Primitives are always added to the list and not culled (culling is done at higher-level by ImGui:: functions), if you use this API a lot consider coarse culling your drawn objects.
struct ImDrawList
{
    // This is what you have to render
    ImVector/*<ImDrawCmd>*/     CmdBuffer;          // Draw commands. Typically 1 command = 1 GPU draw call, unless the command is a callback.
    ImVector/*<ImDrawIdx>*/     IdxBuffer;          // Index buffer. Each command consume ImDrawCmd::ElemCount of those
    ImVector/*<ImDrawVert>*/    VtxBuffer;          // Vertex buffer.
    ImDrawListFlags         Flags;              // Flags, you may poke into these to adjust anti-aliasing settings per-primitive.
    // [Internal, used while building lists]
    const ImDrawListSharedData* _Data;          // Pointer to shared draw data (you can use ImGui::GetDrawListSharedData() to get the one from current ImGui context)
    const char*             _OwnerName;         // Pointer to owner window's name for debugging
    unsigned int            _VtxCurrentIdx;     // [Internal] == VtxBuffer.Size
    ImDrawVert*             _VtxWritePtr;       // [Internal] point within VtxBuffer.Data after each add command (to avoid using the ImVector<> operators too much)
    ImDrawIdx*              _IdxWritePtr;       // [Internal] point within IdxBuffer.Data after each add command (to avoid using the ImVector<> operators too much)
    ImVector/*<ImVec4>*/        _ClipRectStack;     // [Internal]
    ImVector/*<ImTextureID>*/   _TextureIdStack;    // [Internal]
    ImVector/*<ImVec2>*/        _Path;              // [Internal] current path building
    int                     _ChannelsCurrent;   // [Internal] current channel number (0)
    int                     _ChannelsCount;     // [Internal] number of active channels (1+)
    ImVector/*<ImDrawChannel>*/ _Channels;          // [Internal] draw channels for columns API (not resized down so _ChannelsCount may be smaller than _Channels.Size)
    // If you want to create ImDrawList instances, pass them ImGui::GetDrawListSharedData() or create and use your own ImDrawListSharedData (so you can use ImDrawList without ImGui)
    // Primitives
    // Stateful path API, add points then finish with PathFillConvex() or PathStroke()
    // Channels
    // - Use to simulate layers. By switching channels to can render out-of-order (e.g. submit foreground primitives before background primitives)
    // - Use to minimize draw calls (e.g. if going back-and-forth between multiple non-overlapping clipping rectangles, prefer to append into separate channels then merge at the end)
    // Advanced
    // Internal helpers
    // NB: all primitives needs to be reserved via PrimReserve() beforehand!
};
// All draw data to render an ImGui frame
// (NB: the style and the naming convention here is a little inconsistent but we preserve them for backward compatibility purpose)
struct ImDrawData
{
    bool            Valid;                  // Only valid after Render() is called and before the next NewFrame() is called.
    ImDrawList**    CmdLists;               // Array of ImDrawList* to render. The ImDrawList are owned by ImGuiContext and only pointed to from here.
    int             CmdListsCount;          // Number of ImDrawList* to render
    int             TotalIdxCount;          // For convenience, sum of all ImDrawList's IdxBuffer.Size
    int             TotalVtxCount;          // For convenience, sum of all ImDrawList's VtxBuffer.Size
    ImVec2          DisplayPos;             // Upper-left position of the viewport to render (== upper-left of the orthogonal projection matrix to use)
    ImVec2          DisplaySize;            // Size of the viewport to render (== io.DisplaySize for the main viewport) (DisplayPos + DisplaySize == lower-right of the orthogonal projection matrix to use)
    // Functions
};
struct ImFontConfig
{
    void*           FontData;               //          // TTF/OTF data
    int             FontDataSize;           //          // TTF/OTF data size
    bool            FontDataOwnedByAtlas;   // true     // TTF/OTF data ownership taken by the container ImFontAtlas (will delete memory itself).
    int             FontNo;                 // 0        // Index of font within TTF/OTF file
    float           SizePixels;             //          // Size in pixels for rasterizer (more or less maps to the resulting font height).
    int             OversampleH;            // 3        // Rasterize at higher quality for sub-pixel positioning. We don't use sub-pixel positions on the Y axis.
    int             OversampleV;            // 1        // Rasterize at higher quality for sub-pixel positioning. We don't use sub-pixel positions on the Y axis.
    bool            PixelSnapH;             // false    // Align every glyph to pixel boundary. Useful e.g. if you are merging a non-pixel aligned font with the default font. If enabled, you can set OversampleH/V to 1.
    ImVec2          GlyphExtraSpacing;      // 0, 0     // Extra spacing (in pixels) between glyphs. Only X axis is supported for now.
    ImVec2          GlyphOffset;            // 0, 0     // Offset all glyphs from this font input.
    const ImWchar*  GlyphRanges;            // NULL     // Pointer to a user-provided list of Unicode range (2 value per range, values are inclusive, zero-terminated list). THE ARRAY DATA NEEDS TO PERSIST AS LONG AS THE FONT IS ALIVE.
    float           GlyphMinAdvanceX;       // 0        // Minimum AdvanceX for glyphs, set Min to align font icons, set both Min/Max to enforce mono-space font
    float           GlyphMaxAdvanceX;       // FLT_MAX  // Maximum AdvanceX for glyphs
    bool            MergeMode;              // false    // Merge into previous ImFont, so you can combine multiple inputs font into one ImFont (e.g. ASCII font + icons + Japanese glyphs). You may want to use GlyphOffset.y when merge font of different heights.
    unsigned int    RasterizerFlags;        // 0x00     // Settings for custom font rasterizer (e.g. ImGuiFreeType). Leave as zero if you aren't using one.
    float           RasterizerMultiply;     // 1.0f     // Brighten (>1.0f) or darken (<1.0f) font output. Brightening small fonts may be a good workaround to make them more readable.
    // [Internal]
    char            Name[40];               // Name (strictly to ease debugging)
    ImFont*         DstFont;
};
struct ImFontGlyph
{
    ImWchar         Codepoint;          // 0x0000..0xFFFF
    float           AdvanceX;           // Distance to next character (= data from font + ImFontConfig::GlyphExtraSpacing.x baked in)
    float           X0, Y0, X1, Y1;     // Glyph corners
    float           U0, V0, U1, V1;     // Texture coordinates
};
enum ImFontAtlasFlags_
{
    ImFontAtlasFlags_None               = 0,
    ImFontAtlasFlags_NoPowerOfTwoHeight = 1 << 0,   // Don't round the height to next power of two
    ImFontAtlasFlags_NoMouseCursors     = 1 << 1    // Don't build software mouse cursors into the atlas
};
// Load and rasterize multiple TTF/OTF fonts into a same texture. The font atlas will build a single texture holding:
//  - One or more fonts.
//  - Custom graphics data needed to render the shapes needed by Dear ImGui.
//  - Mouse cursor shapes for software cursor rendering (unless setting 'Flags |= ImFontAtlasFlags_NoMouseCursors' in the font atlas).
// It is the user-code responsibility to setup/build the atlas, then upload the pixel data into a texture accessible by your graphics api.
//  - Optionally, call any of the AddFont*** functions. If you don't call any, the default font embedded in the code will be loaded for you.
//  - Call GetTexDataAsAlpha8() or GetTexDataAsRGBA32() to build and retrieve pixels data.
//  - Upload the pixels data into a texture within your graphics system (see imgui_impl_xxxx.cpp examples)
//  - Call SetTexID(my_tex_id); and pass the pointer/identifier to your texture in a format natural to your graphics API. 
//    This value will be passed back to you during rendering to identify the texture. Read FAQ entry about ImTextureID for more details.
// Common pitfalls:
// - If you pass a 'glyph_ranges' array to AddFont*** functions, you need to make sure that your array persist up until the 
//   atlas is build (when calling GetTexData*** or Build()). We only copy the pointer, not the data.
// - Important: By default, AddFontFromMemoryTTF() takes ownership of the data. Even though we are not writing to it, we will free the pointer on destruction.
//   You can set font_cfg->FontDataOwnedByAtlas=false to keep ownership of your data and it won't be freed, 
// - Even though many functions are suffixed with "TTF", OTF data is supported just as well.
// - This is an old API and it is currently awkward for those and and various other reasons! We will address them in the future!
struct ImFontAtlas
{
    // Build atlas, retrieve pixel data.
    // User is in charge of copying the pixels into graphics memory (e.g. create a texture with your engine). Then store your texture handle with SetTexID().
    // The pitch is always = Width * BytesPerPixels (1 or 4)
    // Building in RGBA32 format is provided for convenience and compatibility, but note that unless you manually manipulate or copy color data into 
    // the texture (e.g. when using the AddCustomRect*** api), then the RGB pixels emitted will always be white (~75 of memory/bandwidth waste.
    //-------------------------------------------
    // Glyph Ranges
    //-------------------------------------------
    // Helpers to retrieve list of common Unicode ranges (2 value per range, values are inclusive, zero-terminated list)
    // NB: Make sure that your string are UTF-8 and NOT in your local code page. In C++11, you can create UTF-8 string literal using the u8"Hello world" syntax. See FAQ for details.
    // NB: Consider using GlyphRangesBuilder to build glyph ranges from textual data.
    // Helpers to build glyph ranges from text data. Feed your application strings/characters to it then call BuildRanges().
    //-------------------------------------------
    // Custom Rectangles/Glyphs API
    //-------------------------------------------
    // You can request arbitrary rectangles to be packed into the atlas, for your own purposes. After calling Build(), you can query the rectangle position and render your pixels.
    // You can also request your rectangles to be mapped as font glyph (given a font + Unicode point), so you can render e.g. custom colorful icons and use them as regular glyphs.
    // [Internal]
    //-------------------------------------------
    // Members
    //-------------------------------------------
    bool                        Locked;             // Marked as Locked by ImGui::NewFrame() so attempt to modify the atlas will assert.
    ImFontAtlasFlags            Flags;              // Build flags (see ImFontAtlasFlags_)
    ImTextureID                 TexID;              // User data to refer to the texture once it has been uploaded to user's graphic systems. It is passed back to you during rendering via the ImDrawCmd structure.
    int                         TexDesiredWidth;    // Texture width desired by user before Build(). Must be a power-of-two. If have many glyphs your graphics API have texture size restrictions you may want to increase texture width to decrease height.
    int                         TexGlyphPadding;    // Padding between glyphs within texture in pixels. Defaults to 1.
    // [Internal]
    // NB: Access texture data via GetTexData*() calls! Which will setup a default font for you.
    unsigned char*              TexPixelsAlpha8;    // 1 component per pixel, each component is unsigned 8-bit. Total size = TexWidth * TexHeight
    unsigned int*               TexPixelsRGBA32;    // 4 component per pixel, each component is unsigned 8-bit. Total size = TexWidth * TexHeight * 4
    int                         TexWidth;           // Texture width calculated during Build().
    int                         TexHeight;          // Texture height calculated during Build().
    ImVec2                      TexUvScale;         // = (1.0f/TexWidth, 1.0f/TexHeight)
    ImVec2                      TexUvWhitePixel;    // Texture coordinates to a white pixel
    ImVector/*<ImFont*>*/           Fonts;              // Hold all the fonts returned by AddFont*. Fonts[0] is the default font upon calling ImGui::NewFrame(), use ImGui::PushFont()/PopFont() to change the current font.
    ImVector/*<CustomRect>*/        CustomRects;        // Rectangles for packing custom texture data into the atlas.
    ImVector/*<ImFontConfig>*/      ConfigData;         // Internal data
    int                         CustomRectIds[1];   // Identifiers of custom texture rectangle used by ImFontAtlas/ImDrawList
};
// Font runtime data and rendering
// ImFontAtlas automatically loads a default embedded font for you when you call GetTexDataAsAlpha8() or GetTexDataAsRGBA32().
struct ImFont
{
    // Members: Hot ~62/78 bytes
    float                       FontSize;           // <user set>   // Height of characters, set during loading (don't change after loading)
    float                       Scale;              // = 1.f        // Base font scale, multiplied by the per-window font scale which you can adjust with SetFontScale()
    ImVec2                      DisplayOffset;      // = (0.f,0.f)  // Offset font rendering by xx pixels
    ImVector/*<ImFontGlyph>*/       Glyphs;             //              // All glyphs.
    ImVector/*<float>*/             IndexAdvanceX;      //              // Sparse. Glyphs->AdvanceX in a directly indexable way (more cache-friendly, for CalcTextSize functions which are often bottleneck in large UI).
    ImVector/*<unsigned short>*/    IndexLookup;        //              // Sparse. Index glyphs by Unicode code-point.
    const ImFontGlyph*          FallbackGlyph;      // == FindGlyph(FontFallbackChar)
    float                       FallbackAdvanceX;   // == FallbackGlyph->AdvanceX
    ImWchar                     FallbackChar;       // = '?'        // Replacement glyph if one isn't found. Only set via SetFallbackChar()
    // Members: Cold ~18/26 bytes
    short                       ConfigDataCount;    // ~ 1          // Number of ImFontConfig involved in creating this font. Bigger than 1 when merging multiple font sources into one ImFont.
    ImFontConfig*               ConfigData;         //              // Pointer within ContainerAtlas->ConfigData
    ImFontAtlas*                ContainerAtlas;     //              // What we has been loaded into
    float                       Ascent, Descent;    //              // Ascent: distance from top to bottom of e.g. 'A' [0..FontSize]
    bool                        DirtyLookupTables;
    int                         MetricsTotalSurface;//              // Total surface in pixels to get an idea of the font rasterization/texture cost (not exact, we approximate the cost of padding between glyphs)
    // Methods
    // 'max_width' stops rendering after a certain width (could be turned into a 2d size). FLT_MAX to disable.
    // 'wrap_width' enable automatic word-wrapping across multiple lines to fit into given width. 0.0f to disable.
    // [Internal]
};
// Include imgui_user.h at the end of imgui.h (convenient for user to only explicitly include vanilla imgui.h)
    struct GlyphRangesBuilder
    {
        ImVector/*<unsigned char>*/ UsedChars;
    };
    struct CustomRect
    {
        unsigned int    ID;
        unsigned short  Width, Height;
        unsigned short  X, Y;
        float           GlyphAdvanceX;
        ImVec2          GlyphOffset;
        ImFont*         Font;
    };
    struct TextRange
    {
        const char* b;
        const char* e;
    };
    struct Pair
    {
        ImGuiID key;
        union { int val_i; float val_f; void* val_p; };
    };

#else
struct GLFWwindow;
struct SDL_Window;
typedef union SDL_Event SDL_Event;
inline ImVec2_Simple ImVec2ToSimple(ImVec2 vec)
{
	ImVec2_Simple result;
    result.x = vec.x;
    result.y = vec.y;
    return result;
}
inline ImVec4_Simple ImVec4ToSimple(ImVec4 vec)
{
	ImVec4_Simple result;
    result.x = vec.x;
    result.y = vec.y;
	result.z = vec.z;
    result.w = vec.w;
    return result;
}
inline ImColor_Simple ImColorToSimple(ImColor col)
{
	ImColor_Simple result;
    result.Value = ImVec4ToSimple(col.Value);
    return result;
}
#endif // CIMGUI_DEFINE_ENUMS_AND_STRUCTS

#ifndef CIMGUI_DEFINE_ENUMS_AND_STRUCTS
typedef ImFontAtlas::GlyphRangesBuilder GlyphRangesBuilder;
typedef ImFontAtlas::CustomRect CustomRect;
typedef ImGuiTextFilter::TextRange TextRange;
typedef ImGuiStorage::Pair Pair;
typedef ImVector<TextRange> ImVector_TextRange;
typedef ImVector<ImWchar> ImVector_ImWchar;
#else //CIMGUI_DEFINE_ENUMS_AND_STRUCTS
typedef ImVector ImVector_TextRange;
typedef ImVector ImVector_ImWchar;
#endif //CIMGUI_DEFINE_ENUMS_AND_STRUCTS
    // Context creation and access
    // Each context create its own ImFontAtlas by default. You may instance one yourself and pass it to CreateContext() to share a font atlas between imgui contexts.
    // All those functions are not reliant on the current context.
CIMGUI_API ImGuiContext* igCreateContext(ImFontAtlas* shared_font_atlas);
CIMGUI_API void igDestroyContext(ImGuiContext* ctx);   // NULL = destroy current context
CIMGUI_API ImGuiContext* igGetCurrentContext(void);
CIMGUI_API void igSetCurrentContext(ImGuiContext* ctx);
CIMGUI_API bool igDebugCheckVersionAndDataLayout(const char* version_str,size_t sz_io,size_t sz_style,size_t sz_vec2,size_t sz_vec4,size_t sz_drawvert);
    // Main
CIMGUI_API ImGuiIO* igGetIO(void);                                    // access the IO structure (mouse/keyboard/gamepad inputs, time, various configuration options/flags)
CIMGUI_API ImGuiStyle* igGetStyle(void);                                 // access the Style structure (colors, sizes). Always use PushStyleCol(), PushStyleVar() to modify style mid-frame.
CIMGUI_API void igNewFrame(void);                                 // start a new ImGui frame, you can submit any command from this point until Render()/EndFrame().
CIMGUI_API void igEndFrame(void);                                 // ends the ImGui frame. automatically called by Render(), you likely don't need to call that yourself directly. If you don't need to render data (skipping rendering) you may call EndFrame() but you'll have wasted CPU already! If you don't need to render, better to not create any imgui windows and not call NewFrame() at all!
CIMGUI_API void igRender(void);                                   // ends the ImGui frame, finalize the draw data. (Obsolete: optionally call io.RenderDrawListsFn if set. Nowadays, prefer calling your render function yourself.)
CIMGUI_API ImDrawData* igGetDrawData(void);                              // valid after Render() and until the next call to NewFrame(). this is what you have to render. (Obsolete: this used to be passed to your io.RenderDrawListsFn() function.)
    // Demo, Debug, Information
CIMGUI_API void igShowDemoWindow(bool* p_open);        // create demo/test window (previously called ShowTestWindow). demonstrate most ImGui features. call this to learn about the library! try to make it always available in your application!
CIMGUI_API void igShowMetricsWindow(bool* p_open);     // create metrics window. display ImGui internals: draw commands (with individual draw calls and vertices), window list, basic internal state, etc.
CIMGUI_API void igShowStyleEditor(ImGuiStyle* ref);    // add style editor block (not a window). you can pass in a reference ImGuiStyle structure to compare to, revert to and save to (else it uses the default style)
CIMGUI_API bool igShowStyleSelector(const char* label);       // add style selector block (not a window), essentially a combo listing the default styles.
CIMGUI_API void igShowFontSelector(const char* label);        // add font selector block (not a window), essentially a combo listing the loaded fonts.
CIMGUI_API void igShowUserGuide(void);                            // add basic help/info block (not a window): how to manipulate ImGui as a end-user (mouse/keyboard controls).
CIMGUI_API const char* igGetVersion(void);                               // get the compiled version string e.g. "1.23"
    // Styles
CIMGUI_API void igStyleColorsDark(ImGuiStyle* dst);    // new, recommended style (default)
CIMGUI_API void igStyleColorsClassic(ImGuiStyle* dst); // classic imgui style
CIMGUI_API void igStyleColorsLight(ImGuiStyle* dst);   // best used with borders and a custom, thicker font
    // Windows
    // (Begin = push window to the stack and start appending to it. End = pop window from the stack. You may append multiple times to the same window during the same frame)
    // Begin()/BeginChild() return false to indicate the window being collapsed or fully clipped, so you may early out and omit submitting anything to the window.
    // You need to always call a matching End()/EndChild() for a Begin()/BeginChild() call, regardless of its return value (this is due to legacy reason and is inconsistent with BeginMenu/EndMenu, BeginPopup/EndPopup and other functions where the End call should only be called if the corresponding Begin function returned true.)
    // Passing 'bool* p_open != NULL' shows a close widget in the upper-right corner of the window, which when clicking will set the boolean to false.
    // Use child windows to introduce independent scrolling/clipping regions within a host window. Child windows can embed their own child.
CIMGUI_API bool igBegin(const char* name,bool* p_open,ImGuiWindowFlags flags);
CIMGUI_API void igEnd(void);
CIMGUI_API bool igBeginChild(const char* str_id,const ImVec2 size,bool border,ImGuiWindowFlags flags); // Begin a scrolling region. size==0.0f: use remaining window size, size<0.0f: use remaining window size minus abs(size). size>0.0f: fixed size. each axis can use a different mode, e.g. ImVec2(0,400).
CIMGUI_API bool igBeginChildID(ImGuiID id,const ImVec2 size,bool border,ImGuiWindowFlags flags);
CIMGUI_API void igEndChild(void);
    // Windows Utilities
CIMGUI_API bool igIsWindowAppearing(void);
CIMGUI_API bool igIsWindowCollapsed(void);
CIMGUI_API bool igIsWindowFocused(ImGuiFocusedFlags flags); // is current window focused? or its root/child, depending on flags. see flags for options.
CIMGUI_API bool igIsWindowHovered(ImGuiHoveredFlags flags); // is current window hovered (and typically: not blocked by a popup/modal)? see flags for options. NB: If you are trying to check whether your mouse should be dispatched to imgui or to your app, you should use the 'io.WantCaptureMouse' boolean for that! Please read the FAQ!
CIMGUI_API ImDrawList* igGetWindowDrawList(void);                        // get draw list associated to the window, to append your own drawing primitives
CIMGUI_API ImVec2 igGetWindowPos(void);                             // get current window position in screen space (useful if you want to do your own drawing via the DrawList API)
CIMGUI_API ImVec2 igGetWindowSize(void);                            // get current window size
CIMGUI_API float igGetWindowWidth(void);                           // get current window width (shortcut for GetWindowSize().x)
CIMGUI_API float igGetWindowHeight(void);                          // get current window height (shortcut for GetWindowSize().y)
CIMGUI_API ImVec2 igGetContentRegionMax(void);                      // current content boundaries (typically window boundaries including scrolling, or current column boundaries), in windows coordinates
CIMGUI_API ImVec2 igGetContentRegionAvail(void);                    // == GetContentRegionMax() - GetCursorPos()
CIMGUI_API float igGetContentRegionAvailWidth(void);               //
CIMGUI_API ImVec2 igGetWindowContentRegionMin(void);                // content boundaries min (roughly (0,0)-Scroll), in window coordinates
CIMGUI_API ImVec2 igGetWindowContentRegionMax(void);                // content boundaries max (roughly (0,0)+Size-Scroll) where Size can be override with SetNextWindowContentSize(), in window coordinates
CIMGUI_API float igGetWindowContentRegionWidth(void);              //
CIMGUI_API void igSetNextWindowPos(const ImVec2 pos,ImGuiCond cond,const ImVec2 pivot); // set next window position. call before Begin(). use pivot=(0.5f,0.5f) to center on given point, etc.
CIMGUI_API void igSetNextWindowSize(const ImVec2 size,ImGuiCond cond);                  // set next window size. set axis to 0.0f to force an auto-fit on this axis. call before Begin()
CIMGUI_API void igSetNextWindowSizeConstraints(const ImVec2 size_min,const ImVec2 size_max,ImGuiSizeCallback custom_callback,void* custom_callback_data); // set next window size limits. use -1,-1 on either X/Y axis to preserve the current size. Use callback to apply non-trivial programmatic constraints.
CIMGUI_API void igSetNextWindowContentSize(const ImVec2 size);                               // set next window content size (~ enforce the range of scrollbars). not including window decorations (title bar, menu bar, etc.). set an axis to 0.0f to leave it automatic. call before Begin()
CIMGUI_API void igSetNextWindowCollapsed(bool collapsed,ImGuiCond cond);                 // set next window collapsed state. call before Begin()
CIMGUI_API void igSetNextWindowFocus(void);                                                       // set next window to be focused / front-most. call before Begin()
CIMGUI_API void igSetNextWindowBgAlpha(float alpha);                                          // set next window background color alpha. helper to easily modify ImGuiCol_WindowBg/ChildBg/PopupBg.
CIMGUI_API void igSetWindowPosVec2(const ImVec2 pos,ImGuiCond cond);                        // (not recommended) set current window position - call within Begin()/End(). prefer using SetNextWindowPos(), as this may incur tearing and side-effects.
CIMGUI_API void igSetWindowSizeVec2(const ImVec2 size,ImGuiCond cond);                      // (not recommended) set current window size - call within Begin()/End(). set to ImVec2(0,0) to force an auto-fit. prefer using SetNextWindowSize(), as this may incur tearing and minor side-effects.
CIMGUI_API void igSetWindowCollapsedBool(bool collapsed,ImGuiCond cond);                     // (not recommended) set current window collapsed state. prefer using SetNextWindowCollapsed().
CIMGUI_API void igSetWindowFocus(void);                                                           // (not recommended) set current window to be focused / front-most. prefer using SetNextWindowFocus().
CIMGUI_API void igSetWindowFontScale(float scale);                                            // set font scale. Adjust IO.FontGlobalScale if you want to scale all windows
CIMGUI_API void igSetWindowPosStr(const char* name,const ImVec2 pos,ImGuiCond cond);      // set named window position.
CIMGUI_API void igSetWindowSizeStr(const char* name,const ImVec2 size,ImGuiCond cond);    // set named window size. set axis to 0.0f to force an auto-fit on this axis.
CIMGUI_API void igSetWindowCollapsedStr(const char* name,bool collapsed,ImGuiCond cond);   // set named window collapsed state
CIMGUI_API void igSetWindowFocusStr(const char* name);                                           // set named window to be focused / front-most. use NULL to remove focus.
    // Windows Scrolling
CIMGUI_API float igGetScrollX(void);                                                   // get scrolling amount [0..GetScrollMaxX()]
CIMGUI_API float igGetScrollY(void);                                                   // get scrolling amount [0..GetScrollMaxY()]
CIMGUI_API float igGetScrollMaxX(void);                                                // get maximum scrolling amount ~~ ContentSize.X - WindowSize.X
CIMGUI_API float igGetScrollMaxY(void);                                                // get maximum scrolling amount ~~ ContentSize.Y - WindowSize.Y
CIMGUI_API void igSetScrollX(float scroll_x);                                     // set scrolling amount [0..GetScrollMaxX()]
CIMGUI_API void igSetScrollY(float scroll_y);                                     // set scrolling amount [0..GetScrollMaxY()]
CIMGUI_API void igSetScrollHere(float center_y_ratio);                     // adjust scrolling amount to make current cursor position visible. center_y_ratio=0.0: top, 0.5: center, 1.0: bottom. When using to make a "default/current item" visible, consider using SetItemDefaultFocus() instead.
CIMGUI_API void igSetScrollFromPosY(float pos_y,float center_y_ratio);    // adjust scrolling amount to make given position valid. use GetCursorPos() or GetCursorStartPos()+offset to get valid positions.
    // Parameters stacks (shared)
CIMGUI_API void igPushFont(ImFont* font);                                         // use NULL as a shortcut to push default font
CIMGUI_API void igPopFont(void);
CIMGUI_API void igPushStyleColorU32(ImGuiCol idx,ImU32 col);
CIMGUI_API void igPushStyleColor(ImGuiCol idx,const ImVec4 col);
CIMGUI_API void igPopStyleColor(int count);
CIMGUI_API void igPushStyleVarFloat(ImGuiStyleVar idx,float val);
CIMGUI_API void igPushStyleVarVec2(ImGuiStyleVar idx,const ImVec2 val);
CIMGUI_API void igPopStyleVar(int count);
CIMGUI_API const ImVec4* igGetStyleColorVec4(ImGuiCol idx);                                // retrieve style color as stored in ImGuiStyle structure. use to feed back into PushStyleColor(), otherwise use GetColorU32() to get style color with style alpha baked in.
CIMGUI_API ImFont* igGetFont(void);                                                      // get current font
CIMGUI_API float igGetFontSize(void);                                                  // get current font size (= height in pixels) of current font with current scale applied
CIMGUI_API ImVec2 igGetFontTexUvWhitePixel(void);                                       // get UV coordinate for a while pixel, useful to draw custom shapes via the ImDrawList API
CIMGUI_API ImU32 igGetColorU32(ImGuiCol idx,float alpha_mul);              // retrieve given style color with style alpha applied and optional extra alpha multiplier
CIMGUI_API ImU32 igGetColorU32Vec4(const ImVec4 col);                                 // retrieve given color with style alpha applied
CIMGUI_API ImU32 igGetColorU32U32(ImU32 col);                                         // retrieve given color with style alpha applied
    // Parameters stacks (current window)
CIMGUI_API void igPushItemWidth(float item_width);                                // width of items for the common item+label case, pixels. 0.0f = default to ~2/3 of windows width, >0.0f: width in pixels, <0.0f align xx pixels to the right of window (so -1.0f always align width to the right side)
CIMGUI_API void igPopItemWidth(void);
CIMGUI_API float igCalcItemWidth(void);                                                // width of item given pushed settings and current cursor position
CIMGUI_API void igPushTextWrapPos(float wrap_pos_x);                       // word-wrapping for Text*() commands. < 0.0f: no wrapping; 0.0f: wrap to end of window (or column); > 0.0f: wrap at 'wrap_pos_x' position in window local space
CIMGUI_API void igPopTextWrapPos(void);
CIMGUI_API void igPushAllowKeyboardFocus(bool allow_keyboard_focus);              // allow focusing using TAB/Shift-TAB, enabled by default but you can disable it for certain widgets
CIMGUI_API void igPopAllowKeyboardFocus(void);
CIMGUI_API void igPushButtonRepeat(bool repeat);                                  // in 'repeat' mode, Button*() functions return repeated true in a typematic manner (using io.KeyRepeatDelay/io.KeyRepeatRate setting). Note that you can call IsItemActive() after any Button() to tell if the button is held in the current frame.
CIMGUI_API void igPopButtonRepeat(void);
    // Cursor / Layout
CIMGUI_API void igSeparator(void);                                                    // separator, generally horizontal. inside a menu bar or in horizontal layout mode, this becomes a vertical separator.
CIMGUI_API void igSameLine(float pos_x,float spacing_w);          // call between widgets or groups to layout them horizontally
CIMGUI_API void igNewLine(void);                                                      // undo a SameLine()
CIMGUI_API void igSpacing(void);                                                      // add vertical spacing
CIMGUI_API void igDummy(const ImVec2 size);                                      // add a dummy item of given size
CIMGUI_API void igIndent(float indent_w);                                  // move content position toward the right, by style.IndentSpacing or indent_w if != 0
CIMGUI_API void igUnindent(float indent_w);                                // move content position back to the left, by style.IndentSpacing or indent_w if != 0
CIMGUI_API void igBeginGroup(void);                                                   // lock horizontal starting position + capture group bounding box into one "item" (so you can use IsItemHovered() or layout primitives such as SameLine() on whole group, etc.)
CIMGUI_API void igEndGroup(void);
CIMGUI_API ImVec2 igGetCursorPos(void);                                                 // cursor position is relative to window position
CIMGUI_API float igGetCursorPosX(void);                                                // "
CIMGUI_API float igGetCursorPosY(void);                                                // "
CIMGUI_API void igSetCursorPos(const ImVec2 local_pos);                          // "
CIMGUI_API void igSetCursorPosX(float x);                                         // "
CIMGUI_API void igSetCursorPosY(float y);                                         // "
CIMGUI_API ImVec2 igGetCursorStartPos(void);                                            // initial cursor position
CIMGUI_API ImVec2 igGetCursorScreenPos(void);                                           // cursor position in absolute screen coordinates [0..io.DisplaySize] (useful to work with ImDrawList API)
CIMGUI_API void igSetCursorScreenPos(const ImVec2 screen_pos);                   // cursor position in absolute screen coordinates [0..io.DisplaySize]
CIMGUI_API void igAlignTextToFramePadding(void);                                      // vertically align upcoming text baseline to FramePadding.y so that it will align properly to regularly framed items (call if you have text on a line before a framed item)
CIMGUI_API float igGetTextLineHeight(void);                                            // ~ FontSize
CIMGUI_API float igGetTextLineHeightWithSpacing(void);                                 // ~ FontSize + style.ItemSpacing.y (distance in pixels between 2 consecutive lines of text)
CIMGUI_API float igGetFrameHeight(void);                                               // ~ FontSize + style.FramePadding.y * 2
CIMGUI_API float igGetFrameHeightWithSpacing(void);                                    // ~ FontSize + style.FramePadding.y * 2 + style.ItemSpacing.y (distance in pixels between 2 consecutive lines of framed widgets)
    // ID stack/scopes
    // Read the FAQ for more details about how ID are handled in dear imgui. If you are creating widgets in a loop you most
    // likely want to push a unique identifier (e.g. object pointer, loop index) to uniquely differentiate them.
    // You can also use the "##foobar" syntax within widget label to distinguish them from each others.
    // In this header file we use the "label"/"name" terminology to denote a string that will be displayed and used as an ID,
    // whereas "str_id" denote a string that is only used as an ID and not aimed to be displayed.
CIMGUI_API void igPushIDStr(const char* str_id);                                     // push identifier into the ID stack. IDs are hash of the entire stack!
CIMGUI_API void igPushIDRange(const char* str_id_begin,const char* str_id_end);
CIMGUI_API void igPushIDPtr(const void* ptr_id);
CIMGUI_API void igPushIDInt(int int_id);
CIMGUI_API void igPopID(void);
CIMGUI_API ImGuiID igGetIDStr(const char* str_id);                                      // calculate unique ID (hash of whole ID stack + given parameter). e.g. if you want to query into ImGuiStorage yourself
CIMGUI_API ImGuiID igGetIDStrStr(const char* str_id_begin,const char* str_id_end);
CIMGUI_API ImGuiID igGetIDPtr(const void* ptr_id);
    // Widgets: Text
CIMGUI_API void igTextUnformatted(const char* text,const char* text_end);                // raw text without formatting. Roughly equivalent to Text("s", text) but: A) doesn't require null terminated string if 'text_end' is specified, B) it's faster, no memory copy is done, no buffer size limits, recommended for long chunks of text.
CIMGUI_API void igText(const char* fmt,...); // simple formatted text
CIMGUI_API void igTextV(const char* fmt,va_list args);
CIMGUI_API void igTextColored(const ImVec4 col,const char* fmt,...); // shortcut for PushStyleColor(ImGuiCol_Text, col); Text(fmt, ...); PopStyleColor();
CIMGUI_API void igTextColoredV(const ImVec4 col,const char* fmt,va_list args);
CIMGUI_API void igTextDisabled(const char* fmt,...); // shortcut for PushStyleColor(ImGuiCol_Text, style.Colors[ImGuiCol_TextDisabled]); Text(fmt, ...); PopStyleColor();
CIMGUI_API void igTextDisabledV(const char* fmt,va_list args);
CIMGUI_API void igTextWrapped(const char* fmt,...); // shortcut for PushTextWrapPos(0.0f); Text(fmt, ...); PopTextWrapPos();. Note that this won't work on an auto-resizing window if there's no other widgets to extend the window width, yoy may need to set a size using SetNextWindowSize().
CIMGUI_API void igTextWrappedV(const char* fmt,va_list args);
CIMGUI_API void igLabelText(const char* label,const char* fmt,...); // display text+label aligned the same way as value+label widgets
CIMGUI_API void igLabelTextV(const char* label,const char* fmt,va_list args);
CIMGUI_API void igBulletText(const char* fmt,...); // shortcut for Bullet()+Text()
CIMGUI_API void igBulletTextV(const char* fmt,va_list args);
    // Widgets: Main
    // Most widgets return true when the value has been changed or when pressed/selected
CIMGUI_API bool igButton(const char* label,const ImVec2 size);    // button
CIMGUI_API bool igSmallButton(const char* label);                                 // button with FramePadding=(0,0) to easily embed within text
CIMGUI_API bool igInvisibleButton(const char* str_id,const ImVec2 size);        // button behavior without the visuals, useful to build custom behaviors using the public api (along with IsItemActive, IsItemHovered, etc.)
CIMGUI_API bool igArrowButton(const char* str_id,ImGuiDir dir);                  // square button with an arrow shape
CIMGUI_API void igImage(ImTextureID user_texture_id,const ImVec2 size,const ImVec2 uv0,const ImVec2 uv1,const ImVec4 tint_col,const ImVec4 border_col);
CIMGUI_API bool igImageButton(ImTextureID user_texture_id,const ImVec2 size,const ImVec2 uv0,const ImVec2 uv1,int frame_padding,const ImVec4 bg_col,const ImVec4 tint_col);    // <0 frame_padding uses default frame padding settings. 0 for no padding
CIMGUI_API bool igCheckbox(const char* label,bool* v);
CIMGUI_API bool igCheckboxFlags(const char* label,unsigned int* flags,unsigned int flags_value);
CIMGUI_API bool igRadioButtonBool(const char* label,bool active);                    // use with e.g. if (RadioButton("one", my_value==1)) { my_value = 1; }
CIMGUI_API bool igRadioButtonIntPtr(const char* label,int* v,int v_button);           // shortcut to handle the above pattern when value is an integer
CIMGUI_API void igProgressBar(float fraction,const ImVec2 size_arg,const char* overlay);
CIMGUI_API void igBullet(void);                                                       // draw a small circle and keep the cursor on the same line. advance cursor x position by GetTreeNodeToLabelSpacing(), same distance that TreeNode() uses
    // Widgets: Combo Box
    // The new BeginCombo()/EndCombo() api allows you to manage your contents and selection state however you want it, by creating e.g. Selectable() items.
    // The old Combo() api are helpers over BeginCombo()/EndCombo() which are kept available for convenience purpose.
CIMGUI_API bool igBeginCombo(const char* label,const char* preview_value,ImGuiComboFlags flags);
CIMGUI_API void igEndCombo(void); // only call EndCombo() if BeginCombo() returns true!
CIMGUI_API bool igCombo(const char* label,int* current_item,const char* const items[],int items_count,int popup_max_height_in_items);
CIMGUI_API bool igComboStr(const char* label,int* current_item,const char* items_separated_by_zeros,int popup_max_height_in_items);      // Separate items with \0 within a string, end item-list with \0\0. e.g. "One\0Two\0Three\0"
CIMGUI_API bool igComboFnPtr(const char* label,int* current_item,bool(*items_getter)(void* data,int idx,const char** out_text),void* data,int items_count,int popup_max_height_in_items);
    // Widgets: Drags (tip: ctrl+click on a drag box to input with keyboard. manually input values aren't clamped, can go off-bounds)
    // For all the Float2/Float3/Float4/Int2/Int3/Int4 versions of every functions, note that a 'float v[X]' function argument is the same as 'float* v', the array syntax is just a way to document the number of elements that are expected to be accessible. You can pass address of your first element out of a contiguous set, e.g. &myvector.x
    // Adjust format string to decorate the value with a prefix, a suffix, or adapt the editing and display precision e.g. "%.3f" -> 1.234; "%5.2f secs" -> 01.23 secs; "Biscuit: %.0f" -> Biscuit: 1; etc.
    // Speed are per-pixel of mouse movement (v_speed=0.2f: mouse needs to move by 5 pixels to increase value by 1). For gamepad/keyboard navigation, minimum speed is Max(v_speed, minimum_step_at_given_precision).
CIMGUI_API bool igDragFloat(const char* label,float* v,float v_speed,float v_min,float v_max,const char* format,float power);     // If v_min >= v_max we have no bound
CIMGUI_API bool igDragFloat2(const char* label,float v[2],float v_speed,float v_min,float v_max,const char* format,float power);
CIMGUI_API bool igDragFloat3(const char* label,float v[3],float v_speed,float v_min,float v_max,const char* format,float power);
CIMGUI_API bool igDragFloat4(const char* label,float v[4],float v_speed,float v_min,float v_max,const char* format,float power);
CIMGUI_API bool igDragFloatRange2(const char* label,float* v_current_min,float* v_current_max,float v_speed,float v_min,float v_max,const char* format,const char* format_max,float power);
CIMGUI_API bool igDragInt(const char* label,int* v,float v_speed,int v_min,int v_max,const char* format);                                       // If v_min >= v_max we have no bound
CIMGUI_API bool igDragInt2(const char* label,int v[2],float v_speed,int v_min,int v_max,const char* format);
CIMGUI_API bool igDragInt3(const char* label,int v[3],float v_speed,int v_min,int v_max,const char* format);
CIMGUI_API bool igDragInt4(const char* label,int v[4],float v_speed,int v_min,int v_max,const char* format);
CIMGUI_API bool igDragIntRange2(const char* label,int* v_current_min,int* v_current_max,float v_speed,int v_min,int v_max,const char* format,const char* format_max);
CIMGUI_API bool igDragScalar(const char* label,ImGuiDataType data_type,void* v,float v_speed,const void* v_min,const void* v_max,const char* format,float power);
CIMGUI_API bool igDragScalarN(const char* label,ImGuiDataType data_type,void* v,int components,float v_speed,const void* v_min,const void* v_max,const char* format,float power);
    // Widgets: Sliders (tip: ctrl+click on a slider to input with keyboard. manually input values aren't clamped, can go off-bounds)
    // Adjust format string to decorate the value with a prefix, a suffix, or adapt the editing and display precision e.g. "%.3f" -> 1.234; "%5.2f secs" -> 01.23 secs; "Biscuit: %.0f" -> Biscuit: 1; etc.
CIMGUI_API bool igSliderFloat(const char* label,float* v,float v_min,float v_max,const char* format,float power);     // adjust format to decorate the value with a prefix or a suffix for in-slider labels or unit display. Use power!=1.0 for power curve sliders
CIMGUI_API bool igSliderFloat2(const char* label,float v[2],float v_min,float v_max,const char* format,float power);
CIMGUI_API bool igSliderFloat3(const char* label,float v[3],float v_min,float v_max,const char* format,float power);
CIMGUI_API bool igSliderFloat4(const char* label,float v[4],float v_min,float v_max,const char* format,float power);
CIMGUI_API bool igSliderAngle(const char* label,float* v_rad,float v_degrees_min,float v_degrees_max);
CIMGUI_API bool igSliderInt(const char* label,int* v,int v_min,int v_max,const char* format);
CIMGUI_API bool igSliderInt2(const char* label,int v[2],int v_min,int v_max,const char* format);
CIMGUI_API bool igSliderInt3(const char* label,int v[3],int v_min,int v_max,const char* format);
CIMGUI_API bool igSliderInt4(const char* label,int v[4],int v_min,int v_max,const char* format);
CIMGUI_API bool igSliderScalar(const char* label,ImGuiDataType data_type,void* v,const void* v_min,const void* v_max,const char* format,float power);
CIMGUI_API bool igSliderScalarN(const char* label,ImGuiDataType data_type,void* v,int components,const void* v_min,const void* v_max,const char* format,float power);
CIMGUI_API bool igVSliderFloat(const char* label,const ImVec2 size,float* v,float v_min,float v_max,const char* format,float power);
CIMGUI_API bool igVSliderInt(const char* label,const ImVec2 size,int* v,int v_min,int v_max,const char* format);
CIMGUI_API bool igVSliderScalar(const char* label,const ImVec2 size,ImGuiDataType data_type,void* v,const void* v_min,const void* v_max,const char* format,float power);
    // Widgets: Input with Keyboard
    // If you want to use InputText() with a dynamic string type such as std::string or your own, see misc/stl/imgui_stl.h
CIMGUI_API bool igInputText(const char* label,char* buf,size_t buf_size,ImGuiInputTextFlags flags,ImGuiInputTextCallback callback,void* user_data);
CIMGUI_API bool igInputTextMultiline(const char* label,char* buf,size_t buf_size,const ImVec2 size,ImGuiInputTextFlags flags,ImGuiInputTextCallback callback,void* user_data);
CIMGUI_API bool igInputFloat(const char* label,float* v,float step,float step_fast,const char* format,ImGuiInputTextFlags extra_flags);
CIMGUI_API bool igInputFloat2(const char* label,float v[2],const char* format,ImGuiInputTextFlags extra_flags);
CIMGUI_API bool igInputFloat3(const char* label,float v[3],const char* format,ImGuiInputTextFlags extra_flags);
CIMGUI_API bool igInputFloat4(const char* label,float v[4],const char* format,ImGuiInputTextFlags extra_flags);
CIMGUI_API bool igInputInt(const char* label,int* v,int step,int step_fast,ImGuiInputTextFlags extra_flags);
CIMGUI_API bool igInputInt2(const char* label,int v[2],ImGuiInputTextFlags extra_flags);
CIMGUI_API bool igInputInt3(const char* label,int v[3],ImGuiInputTextFlags extra_flags);
CIMGUI_API bool igInputInt4(const char* label,int v[4],ImGuiInputTextFlags extra_flags);
CIMGUI_API bool igInputDouble(const char* label,double* v,double step,double step_fast,const char* format,ImGuiInputTextFlags extra_flags);
CIMGUI_API bool igInputScalar(const char* label,ImGuiDataType data_type,void* v,const void* step,const void* step_fast,const char* format,ImGuiInputTextFlags extra_flags);
CIMGUI_API bool igInputScalarN(const char* label,ImGuiDataType data_type,void* v,int components,const void* step,const void* step_fast,const char* format,ImGuiInputTextFlags extra_flags);
    // Widgets: Color Editor/Picker (tip: the ColorEdit* functions have a little colored preview square that can be left-clicked to open a picker, and right-clicked to open an option menu.)
    // Note that a 'float v[X]' function argument is the same as 'float* v', the array syntax is just a way to document the number of elements that are expected to be accessible. You can the pass the address of a first float element out of a contiguous structure, e.g. &myvector.x
CIMGUI_API bool igColorEdit3(const char* label,float col[3],ImGuiColorEditFlags flags);
CIMGUI_API bool igColorEdit4(const char* label,float col[4],ImGuiColorEditFlags flags);
CIMGUI_API bool igColorPicker3(const char* label,float col[3],ImGuiColorEditFlags flags);
CIMGUI_API bool igColorPicker4(const char* label,float col[4],ImGuiColorEditFlags flags,const float* ref_col);
CIMGUI_API bool igColorButton(const char* desc_id,const ImVec4 col,ImGuiColorEditFlags flags,ImVec2 size);  // display a colored square/button, hover for details, return true when pressed.
CIMGUI_API void igSetColorEditOptions(ImGuiColorEditFlags flags);                     // initialize current options (generally on application startup) if you want to select a default format, picker type, etc. User will be able to change many settings, unless you pass the _NoOptions flag to your calls.
    // Widgets: Trees
    // TreeNode functions return true when the node is open, in which case you need to also call TreePop() when you are finished displaying the tree node contents.
CIMGUI_API bool igTreeNodeStr(const char* label);
CIMGUI_API bool igTreeNodeStrStr(const char* str_id,const char* fmt,...);   // helper variation to completely decorelate the id from the displayed string. Read the FAQ about why and how to use ID. to align arbitrary text at the same level as a TreeNode() you can use Bullet().
CIMGUI_API bool igTreeNodePtr(const void* ptr_id,const char* fmt,...);   // "
CIMGUI_API bool igTreeNodeVStr(const char* str_id,const char* fmt,va_list args);
CIMGUI_API bool igTreeNodeVPtr(const void* ptr_id,const char* fmt,va_list args);
CIMGUI_API bool igTreeNodeExStr(const char* label,ImGuiTreeNodeFlags flags);
CIMGUI_API bool igTreeNodeExStrStr(const char* str_id,ImGuiTreeNodeFlags flags,const char* fmt,...);
CIMGUI_API bool igTreeNodeExPtr(const void* ptr_id,ImGuiTreeNodeFlags flags,const char* fmt,...);
CIMGUI_API bool igTreeNodeExVStr(const char* str_id,ImGuiTreeNodeFlags flags,const char* fmt,va_list args);
CIMGUI_API bool igTreeNodeExVPtr(const void* ptr_id,ImGuiTreeNodeFlags flags,const char* fmt,va_list args);
CIMGUI_API void igTreePushStr(const char* str_id);                                       // ~ Indent()+PushId(). Already called by TreeNode() when returning true, but you can call TreePush/TreePop yourself if desired.
CIMGUI_API void igTreePushPtr(const void* ptr_id);                                // "
CIMGUI_API void igTreePop(void);                                                          // ~ Unindent()+PopId()
CIMGUI_API void igTreeAdvanceToLabelPos(void);                                            // advance cursor x position by GetTreeNodeToLabelSpacing()
CIMGUI_API float igGetTreeNodeToLabelSpacing(void);                                        // horizontal distance preceding label when using TreeNode*() or Bullet() == (g.FontSize + style.FramePadding.x*2) for a regular unframed TreeNode
CIMGUI_API void igSetNextTreeNodeOpen(bool is_open,ImGuiCond cond);              // set next TreeNode/CollapsingHeader open state.
CIMGUI_API bool igCollapsingHeader(const char* label,ImGuiTreeNodeFlags flags);  // if returning 'true' the header is open. doesn't indent nor push on ID stack. user doesn't have to call TreePop().
CIMGUI_API bool igCollapsingHeaderBoolPtr(const char* label,bool* p_open,ImGuiTreeNodeFlags flags); // when 'p_open' isn't NULL, display an additional small close button on upper right of the header
    // Widgets: Selectables
CIMGUI_API bool igSelectable(const char* label,bool selected,ImGuiSelectableFlags flags,const ImVec2 size);  // "bool selected" carry the selection state (read-only). Selectable() is clicked is returns true so you can modify your selection state. size.x==0.0: use remaining width, size.x>0.0: specify width. size.y==0.0: use label height, size.y>0.0: specify height
CIMGUI_API bool igSelectableBoolPtr(const char* label,bool* p_selected,ImGuiSelectableFlags flags,const ImVec2 size);       // "bool* p_selected" point to the selection state (read-write), as a convenient helper.
    // Widgets: List Boxes
CIMGUI_API bool igListBoxStr_arr(const char* label,int* current_item,const char* const items[],int items_count,int height_in_items);
CIMGUI_API bool igListBoxFnPtr(const char* label,int* current_item,bool(*items_getter)(void* data,int idx,const char** out_text),void* data,int items_count,int height_in_items);
CIMGUI_API bool igListBoxHeaderVec2(const char* label,const ImVec2 size); // use if you want to reimplement ListBox() will custom data or interactions. if the function return true, you can output elements then call ListBoxFooter() afterwards.
CIMGUI_API bool igListBoxHeaderInt(const char* label,int items_count,int height_in_items); // "
CIMGUI_API void igListBoxFooter(void);                                                    // terminate the scrolling region. only call ListBoxFooter() if ListBoxHeader() returned true!
    // Widgets: Data Plotting
CIMGUI_API void igPlotLines(const char* label,const float* values,int values_count,int values_offset,const char* overlay_text,float scale_min,float scale_max,ImVec2 graph_size,int stride);
CIMGUI_API void igPlotLinesFnPtr(const char* label,float(*values_getter)(void* data,int idx),void* data,int values_count,int values_offset,const char* overlay_text,float scale_min,float scale_max,ImVec2 graph_size);
CIMGUI_API void igPlotHistogramFloatPtr(const char* label,const float* values,int values_count,int values_offset,const char* overlay_text,float scale_min,float scale_max,ImVec2 graph_size,int stride);
CIMGUI_API void igPlotHistogramFnPtr(const char* label,float(*values_getter)(void* data,int idx),void* data,int values_count,int values_offset,const char* overlay_text,float scale_min,float scale_max,ImVec2 graph_size);
    // Widgets: Value() Helpers. Output single value in "name: value" format (tip: freely declare more in your code to handle your types. you can add functions to the ImGui namespace)
CIMGUI_API void igValueBool(const char* prefix,bool b);
CIMGUI_API void igValueInt(const char* prefix,int v);
CIMGUI_API void igValueUint(const char* prefix,unsigned int v);
CIMGUI_API void igValueFloat(const char* prefix,float v,const char* float_format);
    // Widgets: Menus
CIMGUI_API bool igBeginMainMenuBar(void);                                                 // create and append to a full screen menu-bar.
CIMGUI_API void igEndMainMenuBar(void);                                                   // only call EndMainMenuBar() if BeginMainMenuBar() returns true!
CIMGUI_API bool igBeginMenuBar(void);                                                     // append to menu-bar of current window (requires ImGuiWindowFlags_MenuBar flag set on parent window).
CIMGUI_API void igEndMenuBar(void);                                                       // only call EndMenuBar() if BeginMenuBar() returns true!
CIMGUI_API bool igBeginMenu(const char* label,bool enabled);                  // create a sub-menu entry. only call EndMenu() if this returns true!
CIMGUI_API void igEndMenu(void);                                                          // only call EndMenu() if BeginMenu() returns true!
CIMGUI_API bool igMenuItemBool(const char* label,const char* shortcut,bool selected,bool enabled);  // return true when activated. shortcuts are displayed for convenience but not processed by ImGui at the moment
CIMGUI_API bool igMenuItemBoolPtr(const char* label,const char* shortcut,bool* p_selected,bool enabled);              // return true when activated + toggle (*p_selected) if p_selected != NULL
    // Tooltips
CIMGUI_API void igBeginTooltip(void);                                                     // begin/append a tooltip window. to create full-featured tooltip (with any kind of items).
CIMGUI_API void igEndTooltip(void);
CIMGUI_API void igSetTooltip(const char* fmt,...);                     // set a text-only tooltip, typically use with ImGui::IsItemHovered(). overidde any previous call to SetTooltip().
CIMGUI_API void igSetTooltipV(const char* fmt,va_list args);
    // Popups
CIMGUI_API void igOpenPopup(const char* str_id);                                      // call to mark popup as open (don't call every frame!). popups are closed when user click outside, or if CloseCurrentPopup() is called within a BeginPopup()/EndPopup() block. By default, Selectable()/MenuItem() are calling CloseCurrentPopup(). Popup identifiers are relative to the current ID-stack (so OpenPopup and BeginPopup needs to be at the same level).
CIMGUI_API bool igBeginPopup(const char* str_id,ImGuiWindowFlags flags);                                             // return true if the popup is open, and you can start outputting to it. only call EndPopup() if BeginPopup() returns true!
CIMGUI_API bool igBeginPopupContextItem(const char* str_id,int mouse_button);                                 // helper to open and begin popup when clicked on last item. if you can pass a NULL str_id only if the previous item had an id. If you want to use that on a non-interactive item such as Text() you need to pass in an explicit ID here. read comments in .cpp!
CIMGUI_API bool igBeginPopupContextWindow(const char* str_id,int mouse_button,bool also_over_items);  // helper to open and begin popup when clicked on current window.
CIMGUI_API bool igBeginPopupContextVoid(const char* str_id,int mouse_button);                                 // helper to open and begin popup when clicked in void (where there are no imgui windows).
CIMGUI_API bool igBeginPopupModal(const char* name,bool* p_open,ImGuiWindowFlags flags);                     // modal dialog (regular window with title bar, block interactions behind the modal window, can't close the modal window by clicking outside)
CIMGUI_API void igEndPopup(void);                                                                                             // only call EndPopup() if BeginPopupXXX() returns true!
CIMGUI_API bool igOpenPopupOnItemClick(const char* str_id,int mouse_button);                                  // helper to open popup when clicked on last item. return true when just opened.
CIMGUI_API bool igIsPopupOpen(const char* str_id);                                    // return true if the popup is open
CIMGUI_API void igCloseCurrentPopup(void);                                                // close the popup we have begin-ed into. clicking on a MenuItem or Selectable automatically close the current popup.
    // Columns
    // You can also use SameLine(pos_x) for simplified columns. The columns API is still work-in-progress and rather lacking.
CIMGUI_API void igColumns(int count,const char* id,bool border);
CIMGUI_API void igNextColumn(void);                                                       // next column, defaults to current row or next row if the current row is finished
CIMGUI_API int igGetColumnIndex(void);                                                   // get current column index
CIMGUI_API float igGetColumnWidth(int column_index);                              // get column width (in pixels). pass -1 to use current column
CIMGUI_API void igSetColumnWidth(int column_index,float width);                      // set column width (in pixels). pass -1 to use current column
CIMGUI_API float igGetColumnOffset(int column_index);                             // get position of column line (in pixels, from the left side of the contents region). pass -1 to use current column, otherwise 0..GetColumnsCount() inclusive. column 0 is typically 0.0f
CIMGUI_API void igSetColumnOffset(int column_index,float offset_x);                  // set position of column line (in pixels, from the left side of the contents region). pass -1 to use current column
CIMGUI_API int igGetColumnsCount(void);
    // Logging/Capture: all text output from interface is captured to tty/file/clipboard. By default, tree nodes are automatically opened during logging.
CIMGUI_API void igLogToTTY(int max_depth);                                       // start logging to tty
CIMGUI_API void igLogToFile(int max_depth,const char* filename);         // start logging to file
CIMGUI_API void igLogToClipboard(int max_depth);                                 // start logging to OS clipboard
CIMGUI_API void igLogFinish(void);                                                        // stop logging (close file, etc.)
CIMGUI_API void igLogButtons(void);                                                       // helper to display buttons for logging to tty/file/clipboard
    // Drag and Drop
    // [BETA API] Missing Demo code. API may evolve.
CIMGUI_API bool igBeginDragDropSource(ImGuiDragDropFlags flags);                                      // call when the current item is active. If this return true, you can call SetDragDropPayload() + EndDragDropSource()
CIMGUI_API bool igSetDragDropPayload(const char* type,const void* data,size_t size,ImGuiCond cond);// type is a user defined string of maximum 32 characters. Strings starting with '_' are reserved for dear imgui internal types. Data is copied and held by imgui.
CIMGUI_API void igEndDragDropSource(void);                                                                    // only call EndDragDropSource() if BeginDragDropSource() returns true!
CIMGUI_API bool igBeginDragDropTarget(void);                                                                  // call after submitting an item that may receive an item. If this returns true, you can call AcceptDragDropPayload() + EndDragDropTarget()
CIMGUI_API const ImGuiPayload* igAcceptDragDropPayload(const char* type,ImGuiDragDropFlags flags);            // accept contents of a given type. If ImGuiDragDropFlags_AcceptBeforeDelivery is set you can peek into the payload before the mouse button is released.
CIMGUI_API void igEndDragDropTarget(void);                                                                    // only call EndDragDropTarget() if BeginDragDropTarget() returns true!
    // Clipping
CIMGUI_API void igPushClipRect(const ImVec2 clip_rect_min,const ImVec2 clip_rect_max,bool intersect_with_current_clip_rect);
CIMGUI_API void igPopClipRect(void);
    // Focus, Activation
    // (Prefer using "SetItemDefaultFocus()" over "if (IsWindowAppearing()) SetScrollHere()" when applicable, to make your code more forward compatible when navigation branch is merged)
CIMGUI_API void igSetItemDefaultFocus(void);                                              // make last item the default focused item of a window. Please use instead of "if (IsWindowAppearing()) SetScrollHere()" to signify "default item".
CIMGUI_API void igSetKeyboardFocusHere(int offset);                               // focus keyboard on the next widget. Use positive 'offset' to access sub components of a multiple component widget. Use -1 to access previous widget.
    // Utilities
    // See Demo Window under "Widgets->Querying Status" for an interactive visualization of many of those functions.
CIMGUI_API bool igIsItemHovered(ImGuiHoveredFlags flags);                         // is the last item hovered? (and usable, aka not blocked by a popup, etc.). See ImGuiHoveredFlags for more options.
CIMGUI_API bool igIsItemActive(void);                                                     // is the last item active? (e.g. button being held, text field being edited. This will continuously return true while holding mouse button on an item. Items that don't interact will always return false)
CIMGUI_API bool igIsItemFocused(void);                                                    // is the last item focused for keyboard/gamepad navigation?
CIMGUI_API bool igIsItemClicked(int mouse_button);                                // is the last item clicked? (e.g. button/node just clicked on) == IsMouseClicked(mouse_button) && IsItemHovered()
CIMGUI_API bool igIsItemVisible(void);                                                    // is the last item visible? (items may be out of sight because of clipping/scrolling)
CIMGUI_API bool igIsItemEdited(void);                                                     // did the last item modify its underlying value this frame? or was pressed? This is generally the same as the "bool" return value of many widgets.
CIMGUI_API bool igIsItemDeactivated(void);                                                // was the last item just made inactive (item was previously active). Useful for Undo/Redo patterns with widgets that requires continuous editing.
CIMGUI_API bool igIsItemDeactivatedAfterEdit(void);                                       // was the last item just made inactive and made a value change when it was active? (e.g. Slider/Drag moved). Useful for Undo/Redo patterns with widgets that requires continuous editing. Note that you may get false positives (some widgets such as Combo()/ListBox()/Selectable() will return true even when clicking an already selected item).
CIMGUI_API bool igIsAnyItemHovered(void);
CIMGUI_API bool igIsAnyItemActive(void);
CIMGUI_API bool igIsAnyItemFocused(void);
CIMGUI_API ImVec2 igGetItemRectMin(void);                                                   // get bounding rectangle of last item, in screen space
CIMGUI_API ImVec2 igGetItemRectMax(void);                                                   // "
CIMGUI_API ImVec2 igGetItemRectSize(void);                                                  // get size of last item, in screen space
CIMGUI_API void igSetItemAllowOverlap(void);                                              // allow last item to be overlapped by a subsequent item. sometimes useful with invisible buttons, selectables, etc. to catch unused area.
CIMGUI_API bool igIsRectVisible(const ImVec2 size);                                  // test if rectangle (of given size, starting from cursor position) is visible / not clipped.
CIMGUI_API bool igIsRectVisibleVec2(const ImVec2 rect_min,const ImVec2 rect_max);      // test if rectangle (in screen space) is visible / not clipped. to perform coarse clipping on user's side.
CIMGUI_API double igGetTime(void);
CIMGUI_API int igGetFrameCount(void);
CIMGUI_API ImDrawList* igGetOverlayDrawList(void);                                               // this draw list will be the last rendered one, useful to quickly draw overlays shapes/text
CIMGUI_API ImDrawListSharedData* igGetDrawListSharedData(void);                                    // you may use this when creating your own ImDrawList instances
CIMGUI_API const char* igGetStyleColorName(ImGuiCol idx);
CIMGUI_API void igSetStateStorage(ImGuiStorage* storage);                             // replace current window storage with our own (if you want to manipulate it yourself, typically clear subsection of it)
CIMGUI_API ImGuiStorage* igGetStateStorage(void);
CIMGUI_API ImVec2 igCalcTextSize(const char* text,const char* text_end,bool hide_text_after_double_hash,float wrap_width);
CIMGUI_API void igCalcListClipping(int items_count,float items_height,int* out_items_display_start,int* out_items_display_end);    // calculate coarse clipping for large list of evenly sized items. Prefer using the ImGuiListClipper higher-level helper if you can.
CIMGUI_API bool igBeginChildFrame(ImGuiID id,const ImVec2 size,ImGuiWindowFlags flags); // helper to create a child window / scrolling region that looks like a normal widget frame
CIMGUI_API void igEndChildFrame(void);                                                    // always call EndChildFrame() regardless of BeginChildFrame() return values (which indicates a collapsed/clipped window)
CIMGUI_API ImVec4 igColorConvertU32ToFloat4(ImU32 in);
CIMGUI_API ImU32 igColorConvertFloat4ToU32(const ImVec4 in);
CIMGUI_API void igColorConvertRGBtoHSV(float r,float g,float b,float out_h,float out_s,float out_v);
CIMGUI_API void igColorConvertHSVtoRGB(float h,float s,float v,float out_r,float out_g,float out_b);
    // Inputs
CIMGUI_API int igGetKeyIndex(ImGuiKey imgui_key);                                    // map ImGuiKey_* values into user's key index. == io.KeyMap[key]
CIMGUI_API bool igIsKeyDown(int user_key_index);                                      // is key being held. == io.KeysDown[user_key_index]. note that imgui doesn't know the semantic of each entry of io.KeysDown[]. Use your own indices/enums according to how your backend/engine stored them into io.KeysDown[]!
CIMGUI_API bool igIsKeyPressed(int user_key_index,bool repeat);               // was key pressed (went from !Down to Down). if repeat=true, uses io.KeyRepeatDelay / KeyRepeatRate
CIMGUI_API bool igIsKeyReleased(int user_key_index);                                  // was key released (went from Down to !Down)..
CIMGUI_API int igGetKeyPressedAmount(int key_index,float repeat_delay,float rate); // uses provided repeat rate/delay. return a count, most often 0 or 1 but might be >1 if RepeatRate is small enough that DeltaTime > RepeatRate
CIMGUI_API bool igIsMouseDown(int button);                                            // is mouse button held (0=left, 1=right, 2=middle)
CIMGUI_API bool igIsAnyMouseDown(void);                                                   // is any mouse button held
CIMGUI_API bool igIsMouseClicked(int button,bool repeat);                    // did mouse button clicked (went from !Down to Down) (0=left, 1=right, 2=middle)
CIMGUI_API bool igIsMouseDoubleClicked(int button);                                   // did mouse button double-clicked. a double-click returns false in IsMouseClicked(). uses io.MouseDoubleClickTime.
CIMGUI_API bool igIsMouseReleased(int button);                                        // did mouse button released (went from Down to !Down)
CIMGUI_API bool igIsMouseDragging(int button,float lock_threshold);      // is mouse dragging. if lock_threshold < -1.0f uses io.MouseDraggingThreshold
CIMGUI_API bool igIsMouseHoveringRect(const ImVec2 r_min,const ImVec2 r_max,bool clip);  // is mouse hovering given bounding rect (in screen space). clipped by current clipping settings, but  disregarding of other consideration of focus/window ordering/popup-block.
CIMGUI_API bool igIsMousePosValid(const ImVec2* mouse_pos);                    //
CIMGUI_API ImVec2 igGetMousePos(void);                                                      // shortcut to ImGui::GetIO().MousePos provided by user, to be consistent with other calls
CIMGUI_API ImVec2 igGetMousePosOnOpeningCurrentPopup(void);                                 // retrieve backup of mouse position at the time of opening popup we have BeginPopup() into
CIMGUI_API ImVec2 igGetMouseDragDelta(int button,float lock_threshold);    // dragging amount since clicking. if lock_threshold < -1.0f uses io.MouseDraggingThreshold
CIMGUI_API void igResetMouseDragDelta(int button);                                //
CIMGUI_API ImGuiMouseCursor igGetMouseCursor(void);                                                // get desired cursor type, reset in ImGui::NewFrame(), this is updated during the frame. valid before Render(). If you use software rendering by setting io.MouseDrawCursor ImGui will render those for you
CIMGUI_API void igSetMouseCursor(ImGuiMouseCursor type);                              // set desired cursor type
CIMGUI_API void igCaptureKeyboardFromApp(bool capture);                        // manually override io.WantCaptureKeyboard flag next frame (said flag is entirely left for your application to handle). e.g. force capture keyboard when your widget is being hovered.
CIMGUI_API void igCaptureMouseFromApp(bool capture);                           // manually override io.WantCaptureMouse flag next frame (said flag is entirely left for your application to handle).
    // Clipboard Utilities (also see the LogToClipboard() function to capture or output text data to the clipboard)
CIMGUI_API const char* igGetClipboardText(void);
CIMGUI_API void igSetClipboardText(const char* text);
    // Settings/.Ini Utilities
    // The disk functions are automatically called if io.IniFilename != NULL (default is "imgui.ini").
    // Set io.IniFilename to NULL to load/save manually. Read io.WantSaveIniSettings description about handling .ini saving manually.
CIMGUI_API void igLoadIniSettingsFromDisk(const char* ini_filename);                  // call after CreateContext() and before the first call to NewFrame(). NewFrame() automatically calls LoadIniSettingsFromDisk(io.IniFilename).
CIMGUI_API void igLoadIniSettingsFromMemory(const char* ini_data,size_t ini_size); // call after CreateContext() and before the first call to NewFrame() to provide .ini data from your own data source.
CIMGUI_API void igSaveIniSettingsToDisk(const char* ini_filename);
CIMGUI_API const char* igSaveIniSettingsToMemory(size_t* out_ini_size);               // return a zero-terminated string with the .ini data which you can save by your own mean. call when io.WantSaveIniSettings is set, then save data by your own mean and clear io.WantSaveIniSettings.
    // Memory Utilities
    // All those functions are not reliant on the current context.
    // If you reload the contents of imgui.cpp at runtime, you may need to call SetCurrentContext() + SetAllocatorFunctions() again.
CIMGUI_API void igSetAllocatorFunctions(void*(*alloc_func)(size_t sz,void* user_data),void(*free_func)(void* ptr,void* user_data),void* user_data);
CIMGUI_API void* igMemAlloc(size_t size);
CIMGUI_API void igMemFree(void* ptr);
CIMGUI_API void ImGuiStyle_ScaleAllSizes(ImGuiStyle* self,float scale_factor);
    //------------------------------------------------------------------
    // Configuration (fill once)            // Default value:
    //------------------------------------------------------------------
    // Miscellaneous configuration options
    //------------------------------------------------------------------
    // Settings (User Functions)
    //------------------------------------------------------------------
    // Optional: access OS clipboard
    // (default to use native Win32 clipboard on Windows, otherwise uses a private clipboard. Override to access OS clipboard on other architectures)
    // Optional: notify OS Input Method Editor of the screen position of your cursor for text input position (e.g. when using Japanese/Chinese IME in Windows)
    // (default to use native imm32 api on Windows)
    //------------------------------------------------------------------
    // Input - Fill before calling NewFrame()
    //------------------------------------------------------------------
    // Functions
CIMGUI_API void ImGuiIO_AddInputCharacter(ImGuiIO* self,ImWchar c);                        // Add new character into InputCharacters[]
CIMGUI_API void ImGuiIO_AddInputCharactersUTF8(ImGuiIO* self,const char* utf8_chars);      // Add new characters into InputCharacters[] from an UTF-8 string
CIMGUI_API void ImGuiIO_ClearInputCharacters(ImGuiIO* self);   // Clear the text input buffer manually
    //------------------------------------------------------------------
    // Output - Retrieve after calling NewFrame()
    //------------------------------------------------------------------
    //------------------------------------------------------------------
    // [Internal] ImGui will maintain those fields. Forward compatibility not guaranteed!
    //------------------------------------------------------------------
    // NB: It is forbidden to call push_back/push_front/insert with a reference pointing inside the ImVector data itself! e.g. v.push_back(v[10]) is forbidden.
CIMGUI_API bool ImGuiTextFilter_Draw(ImGuiTextFilter* self,const char* label,float width);    // Helper calling InputText+Build
CIMGUI_API bool ImGuiTextFilter_PassFilter(ImGuiTextFilter* self,const char* text,const char* text_end);
CIMGUI_API void ImGuiTextFilter_Build(ImGuiTextFilter* self);
CIMGUI_API void ImGuiTextFilter_Clear(ImGuiTextFilter* self);
CIMGUI_API bool ImGuiTextFilter_IsActive(ImGuiTextFilter* self);
    // [Internal]
CIMGUI_API const char* TextRange_begin(TextRange* self);
CIMGUI_API const char* TextRange_end(TextRange* self);
CIMGUI_API bool TextRange_empty(TextRange* self);
CIMGUI_API void TextRange_split(TextRange* self,char separator,ImVector_TextRange* out);
CIMGUI_API const char* ImGuiTextBuffer_begin(ImGuiTextBuffer* self);
CIMGUI_API const char* ImGuiTextBuffer_end(ImGuiTextBuffer* self);      // Buf is zero-terminated, so end() will point on the zero-terminator
CIMGUI_API int ImGuiTextBuffer_size(ImGuiTextBuffer* self);
CIMGUI_API bool ImGuiTextBuffer_empty(ImGuiTextBuffer* self);
CIMGUI_API void ImGuiTextBuffer_clear(ImGuiTextBuffer* self);
CIMGUI_API void ImGuiTextBuffer_reserve(ImGuiTextBuffer* self,int capacity);
CIMGUI_API const char* ImGuiTextBuffer_c_str(ImGuiTextBuffer* self);
CIMGUI_API void ImGuiTextBuffer_appendfv(ImGuiTextBuffer* self,const char* fmt,va_list args);
    // - Get***() functions find pair, never add/allocate. Pairs are sorted so a query is O(log N)
    // - Set***() functions find pair, insertion on demand if missing.
    // - Sorted insertion is costly, paid once. A typical frame shouldn't need to insert any new pair.
CIMGUI_API void ImGuiStorage_Clear(ImGuiStorage* self);
CIMGUI_API int ImGuiStorage_GetInt(ImGuiStorage* self,ImGuiID key,int default_val);
CIMGUI_API void ImGuiStorage_SetInt(ImGuiStorage* self,ImGuiID key,int val);
CIMGUI_API bool ImGuiStorage_GetBool(ImGuiStorage* self,ImGuiID key,bool default_val);
CIMGUI_API void ImGuiStorage_SetBool(ImGuiStorage* self,ImGuiID key,bool val);
CIMGUI_API float ImGuiStorage_GetFloat(ImGuiStorage* self,ImGuiID key,float default_val);
CIMGUI_API void ImGuiStorage_SetFloat(ImGuiStorage* self,ImGuiID key,float val);
CIMGUI_API void* ImGuiStorage_GetVoidPtr(ImGuiStorage* self,ImGuiID key); // default_val is NULL
CIMGUI_API void ImGuiStorage_SetVoidPtr(ImGuiStorage* self,ImGuiID key,void* val);
    // - Get***Ref() functions finds pair, insert on demand if missing, return pointer. Useful if you intend to do Get+Set.
    // - References are only valid until a new value is added to the storage. Calling a Set***() function or a Get***Ref() function invalidates the pointer.
    // - A typical use case where this is convenient for quick hacking (e.g. add storage during a live Edit&Continue session if you can't modify existing struct)
    //      float* pvar = ImGui::GetFloatRef(key); ImGui::SliderFloat("var", pvar, 0, 100.0f); some_var += *pvar;
CIMGUI_API int* ImGuiStorage_GetIntRef(ImGuiStorage* self,ImGuiID key,int default_val);
CIMGUI_API bool* ImGuiStorage_GetBoolRef(ImGuiStorage* self,ImGuiID key,bool default_val);
CIMGUI_API float* ImGuiStorage_GetFloatRef(ImGuiStorage* self,ImGuiID key,float default_val);
CIMGUI_API void** ImGuiStorage_GetVoidPtrRef(ImGuiStorage* self,ImGuiID key,void* default_val);
    // Use on your own storage if you know only integer are being stored (open/close all tree nodes)
CIMGUI_API void ImGuiStorage_SetAllInt(ImGuiStorage* self,int val);
    // For quicker full rebuild of a storage (instead of an incremental one), you may add all your contents and then sort once.
CIMGUI_API void ImGuiStorage_BuildSortByKey(ImGuiStorage* self);
    // Arguments for the different callback events
    // - To modify the text buffer in a callback, prefer using the InsertChars() / DeleteChars() function. InsertChars() will take care of calling the resize callback if necessary.
    // - If you know your edits are not going to resize the underlying buffer allocation, you may modify the contents of 'Buf[]' directly. You need to update 'BufTextLen' accordingly (0 <= BufTextLen < BufSize) and set 'BufDirty'' to true so InputText can update its internal state.
    // Helper functions for text manipulation.
    // Use those function to benefit from the CallbackResize behaviors. Calling those function reset the selection.
CIMGUI_API void ImGuiInputTextCallbackData_DeleteChars(ImGuiInputTextCallbackData* self,int pos,int bytes_count);
CIMGUI_API void ImGuiInputTextCallbackData_InsertChars(ImGuiInputTextCallbackData* self,int pos,const char* text,const char* text_end);
CIMGUI_API bool ImGuiInputTextCallbackData_HasSelection(ImGuiInputTextCallbackData* self);
    // Members
    // [Internal]
CIMGUI_API void ImGuiPayload_Clear(ImGuiPayload* self);
CIMGUI_API bool ImGuiPayload_IsDataType(ImGuiPayload* self,const char* type);
CIMGUI_API bool ImGuiPayload_IsPreview(ImGuiPayload* self);
CIMGUI_API bool ImGuiPayload_IsDelivery(ImGuiPayload* self);
    // FIXME-OBSOLETE: May need to obsolete/cleanup those helpers.
CIMGUI_API void ImColor_SetHSV(ImColor* self,float h,float s,float v,float a);
CIMGUI_API ImColor ImColor_HSV(ImColor* self,float h,float s,float v,float a);
    // items_count:  Use -1 to ignore (you can call Begin later). Use INT_MAX if you don't know how many items you have (in which case the cursor won't be advanced in the final step).
    // items_height: Use -1.0f to be calculated automatically on first step. Otherwise pass in the distance between your items, typically GetTextLineHeightWithSpacing() or GetFrameHeightWithSpacing().
    // If you don't specify an items_height, you NEED to call Step(). If you specify items_height you may call the old Begin()/End() api directly, but prefer calling Step().
CIMGUI_API bool ImGuiListClipper_Step(ImGuiListClipper* self);                                              // Call until it returns false. The DisplayStart/DisplayEnd fields will be set and you can process/draw those items.
CIMGUI_API void ImGuiListClipper_Begin(ImGuiListClipper* self,int items_count,float items_height);  // Automatically called by constructor if you passed 'items_count' or by Step() in Step 1.
CIMGUI_API void ImGuiListClipper_End(ImGuiListClipper* self);                                               // Automatically called on the last call of Step() that returns false.
    // This is what you have to render
    // [Internal, used while building lists]
    // If you want to create ImDrawList instances, pass them ImGui::GetDrawListSharedData() or create and use your own ImDrawListSharedData (so you can use ImDrawList without ImGui)
CIMGUI_API void ImDrawList_PushClipRect(ImDrawList* self,ImVec2 clip_rect_min,ImVec2 clip_rect_max,bool intersect_with_current_clip_rect);  // Render-level scissoring. This is passed down to your render function but not used for CPU-side coarse clipping. Prefer using higher-level ImGui::PushClipRect() to affect logic (hit-testing and widget culling)
CIMGUI_API void ImDrawList_PushClipRectFullScreen(ImDrawList* self);
CIMGUI_API void ImDrawList_PopClipRect(ImDrawList* self);
CIMGUI_API void ImDrawList_PushTextureID(ImDrawList* self,ImTextureID texture_id);
CIMGUI_API void ImDrawList_PopTextureID(ImDrawList* self);
CIMGUI_API ImVec2 ImDrawList_GetClipRectMin(ImDrawList* self);
CIMGUI_API ImVec2 ImDrawList_GetClipRectMax(ImDrawList* self);
    // Primitives
CIMGUI_API void ImDrawList_AddLine(ImDrawList* self,const ImVec2 a,const ImVec2 b,ImU32 col,float thickness);
CIMGUI_API void ImDrawList_AddRect(ImDrawList* self,const ImVec2 a,const ImVec2 b,ImU32 col,float rounding,int rounding_corners_flags,float thickness);   // a: upper-left, b: lower-right, rounding_corners_flags: 4-bits corresponding to which corner to round
CIMGUI_API void ImDrawList_AddRectFilled(ImDrawList* self,const ImVec2 a,const ImVec2 b,ImU32 col,float rounding,int rounding_corners_flags);                     // a: upper-left, b: lower-right
CIMGUI_API void ImDrawList_AddRectFilledMultiColor(ImDrawList* self,const ImVec2 a,const ImVec2 b,ImU32 col_upr_left,ImU32 col_upr_right,ImU32 col_bot_right,ImU32 col_bot_left);
CIMGUI_API void ImDrawList_AddQuad(ImDrawList* self,const ImVec2 a,const ImVec2 b,const ImVec2 c,const ImVec2 d,ImU32 col,float thickness);
CIMGUI_API void ImDrawList_AddQuadFilled(ImDrawList* self,const ImVec2 a,const ImVec2 b,const ImVec2 c,const ImVec2 d,ImU32 col);
CIMGUI_API void ImDrawList_AddTriangle(ImDrawList* self,const ImVec2 a,const ImVec2 b,const ImVec2 c,ImU32 col,float thickness);
CIMGUI_API void ImDrawList_AddTriangleFilled(ImDrawList* self,const ImVec2 a,const ImVec2 b,const ImVec2 c,ImU32 col);
CIMGUI_API void ImDrawList_AddCircle(ImDrawList* self,const ImVec2 centre,float radius,ImU32 col,int num_segments,float thickness);
CIMGUI_API void ImDrawList_AddCircleFilled(ImDrawList* self,const ImVec2 centre,float radius,ImU32 col,int num_segments);
CIMGUI_API void ImDrawList_AddText(ImDrawList* self,const ImVec2 pos,ImU32 col,const char* text_begin,const char* text_end);
CIMGUI_API void ImDrawList_AddTextFontPtr(ImDrawList* self,const ImFont* font,float font_size,const ImVec2 pos,ImU32 col,const char* text_begin,const char* text_end,float wrap_width,const ImVec4* cpu_fine_clip_rect);
CIMGUI_API void ImDrawList_AddImage(ImDrawList* self,ImTextureID user_texture_id,const ImVec2 a,const ImVec2 b,const ImVec2 uv_a,const ImVec2 uv_b,ImU32 col);
CIMGUI_API void ImDrawList_AddImageQuad(ImDrawList* self,ImTextureID user_texture_id,const ImVec2 a,const ImVec2 b,const ImVec2 c,const ImVec2 d,const ImVec2 uv_a,const ImVec2 uv_b,const ImVec2 uv_c,const ImVec2 uv_d,ImU32 col);
CIMGUI_API void ImDrawList_AddImageRounded(ImDrawList* self,ImTextureID user_texture_id,const ImVec2 a,const ImVec2 b,const ImVec2 uv_a,const ImVec2 uv_b,ImU32 col,float rounding,int rounding_corners);
CIMGUI_API void ImDrawList_AddPolyline(ImDrawList* self,const ImVec2* points,const int num_points,ImU32 col,bool closed,float thickness);
CIMGUI_API void ImDrawList_AddConvexPolyFilled(ImDrawList* self,const ImVec2* points,const int num_points,ImU32 col); // Note: Anti-aliased filling requires points to be in clockwise order.
CIMGUI_API void ImDrawList_AddBezierCurve(ImDrawList* self,const ImVec2 pos0,const ImVec2 cp0,const ImVec2 cp1,const ImVec2 pos1,ImU32 col,float thickness,int num_segments);
    // Stateful path API, add points then finish with PathFillConvex() or PathStroke()
CIMGUI_API void ImDrawList_PathClear(ImDrawList* self);
CIMGUI_API void ImDrawList_PathLineTo(ImDrawList* self,const ImVec2 pos);
CIMGUI_API void ImDrawList_PathLineToMergeDuplicate(ImDrawList* self,const ImVec2 pos);
CIMGUI_API void ImDrawList_PathFillConvex(ImDrawList* self,ImU32 col);  // Note: Anti-aliased filling requires points to be in clockwise order.
CIMGUI_API void ImDrawList_PathStroke(ImDrawList* self,ImU32 col,bool closed,float thickness);
CIMGUI_API void ImDrawList_PathArcTo(ImDrawList* self,const ImVec2 centre,float radius,float a_min,float a_max,int num_segments);
CIMGUI_API void ImDrawList_PathArcToFast(ImDrawList* self,const ImVec2 centre,float radius,int a_min_of_12,int a_max_of_12);                                            // Use precomputed angles for a 12 steps circle
CIMGUI_API void ImDrawList_PathBezierCurveTo(ImDrawList* self,const ImVec2 p1,const ImVec2 p2,const ImVec2 p3,int num_segments);
CIMGUI_API void ImDrawList_PathRect(ImDrawList* self,const ImVec2 rect_min,const ImVec2 rect_max,float rounding,int rounding_corners_flags);
    // Channels
    // - Use to simulate layers. By switching channels to can render out-of-order (e.g. submit foreground primitives before background primitives)
    // - Use to minimize draw calls (e.g. if going back-and-forth between multiple non-overlapping clipping rectangles, prefer to append into separate channels then merge at the end)
CIMGUI_API void ImDrawList_ChannelsSplit(ImDrawList* self,int channels_count);
CIMGUI_API void ImDrawList_ChannelsMerge(ImDrawList* self);
CIMGUI_API void ImDrawList_ChannelsSetCurrent(ImDrawList* self,int channel_index);
    // Advanced
CIMGUI_API void ImDrawList_AddCallback(ImDrawList* self,ImDrawCallback callback,void* callback_data);  // Your rendering function must check for 'UserCallback' in ImDrawCmd and call the function instead of rendering triangles.
CIMGUI_API void ImDrawList_AddDrawCmd(ImDrawList* self);                                               // This is useful if you need to forcefully create a new draw call (to allow for dependent rendering / blending). Otherwise primitives are merged into the same draw-call as much as possible
CIMGUI_API ImDrawList* ImDrawList_CloneOutput(ImDrawList* self);                                  // Create a clone of the CmdBuffer/IdxBuffer/VtxBuffer.
    // Internal helpers
    // NB: all primitives needs to be reserved via PrimReserve() beforehand!
CIMGUI_API void ImDrawList_Clear(ImDrawList* self);
CIMGUI_API void ImDrawList_ClearFreeMemory(ImDrawList* self);
CIMGUI_API void ImDrawList_PrimReserve(ImDrawList* self,int idx_count,int vtx_count);
CIMGUI_API void ImDrawList_PrimRect(ImDrawList* self,const ImVec2 a,const ImVec2 b,ImU32 col);      // Axis aligned rectangle (composed of two triangles)
CIMGUI_API void ImDrawList_PrimRectUV(ImDrawList* self,const ImVec2 a,const ImVec2 b,const ImVec2 uv_a,const ImVec2 uv_b,ImU32 col);
CIMGUI_API void ImDrawList_PrimQuadUV(ImDrawList* self,const ImVec2 a,const ImVec2 b,const ImVec2 c,const ImVec2 d,const ImVec2 uv_a,const ImVec2 uv_b,const ImVec2 uv_c,const ImVec2 uv_d,ImU32 col);
CIMGUI_API void ImDrawList_PrimWriteVtx(ImDrawList* self,const ImVec2 pos,const ImVec2 uv,ImU32 col);
CIMGUI_API void ImDrawList_PrimWriteIdx(ImDrawList* self,ImDrawIdx idx);
CIMGUI_API void ImDrawList_PrimVtx(ImDrawList* self,const ImVec2 pos,const ImVec2 uv,ImU32 col);
CIMGUI_API void ImDrawList_UpdateClipRect(ImDrawList* self);
CIMGUI_API void ImDrawList_UpdateTextureID(ImDrawList* self);
    // Functions
CIMGUI_API void ImDrawData_Clear(ImDrawData* self); // The ImDrawList are owned by ImGuiContext!
CIMGUI_API void ImDrawData_DeIndexAllBuffers(ImDrawData* self);                // Helper to convert all buffers from indexed to non-indexed, in case you cannot render indexed. Note: this is slow and most likely a waste of resources. Always prefer indexed rendering!
CIMGUI_API void ImDrawData_ScaleClipRects(ImDrawData* self,const ImVec2 sc);   // Helper to scale the ClipRect field of each ImDrawCmd. Use if your final output buffer is at a different scale than ImGui expects, or if there is a difference between your window resolution and framebuffer resolution.
    // [Internal]
CIMGUI_API ImFont* ImFontAtlas_AddFont(ImFontAtlas* self,const ImFontConfig* font_cfg);
CIMGUI_API ImFont* ImFontAtlas_AddFontDefault(ImFontAtlas* self,const ImFontConfig* font_cfg);
CIMGUI_API ImFont* ImFontAtlas_AddFontFromFileTTF(ImFontAtlas* self,const char* filename,float size_pixels,const ImFontConfig* font_cfg,const ImWchar* glyph_ranges);
CIMGUI_API ImFont* ImFontAtlas_AddFontFromMemoryTTF(ImFontAtlas* self,void* font_data,int font_size,float size_pixels,const ImFontConfig* font_cfg,const ImWchar* glyph_ranges); // Note: Transfer ownership of 'ttf_data' to ImFontAtlas! Will be deleted after destruction of the atlas. Set font_cfg->FontDataOwnedByAtlas=false to keep ownership of your data and it won't be freed.
CIMGUI_API ImFont* ImFontAtlas_AddFontFromMemoryCompressedTTF(ImFontAtlas* self,const void* compressed_font_data,int compressed_font_size,float size_pixels,const ImFontConfig* font_cfg,const ImWchar* glyph_ranges); // 'compressed_font_data' still owned by caller. Compress with binary_to_compressed_c.cpp.
CIMGUI_API ImFont* ImFontAtlas_AddFontFromMemoryCompressedBase85TTF(ImFontAtlas* self,const char* compressed_font_data_base85,float size_pixels,const ImFontConfig* font_cfg,const ImWchar* glyph_ranges);              // 'compressed_font_data_base85' still owned by caller. Compress with binary_to_compressed_c.cpp with -base85 parameter.
CIMGUI_API void ImFontAtlas_ClearInputData(ImFontAtlas* self);           // Clear input data (all ImFontConfig structures including sizes, TTF data, glyph ranges, etc.) = all the data used to build the texture and fonts.
CIMGUI_API void ImFontAtlas_ClearTexData(ImFontAtlas* self);             // Clear output texture data (CPU side). Saves RAM once the texture has been copied to graphics memory.
CIMGUI_API void ImFontAtlas_ClearFonts(ImFontAtlas* self);               // Clear output font data (glyphs storage, UV coordinates).
CIMGUI_API void ImFontAtlas_Clear(ImFontAtlas* self);                    // Clear all input and output.
    // Build atlas, retrieve pixel data.
    // User is in charge of copying the pixels into graphics memory (e.g. create a texture with your engine). Then store your texture handle with SetTexID().
    // The pitch is always = Width * BytesPerPixels (1 or 4)
    // Building in RGBA32 format is provided for convenience and compatibility, but note that unless you manually manipulate or copy color data into 
    // the texture (e.g. when using the AddCustomRect*** api), then the RGB pixels emitted will always be white (~75% of memory/bandwidth waste.
CIMGUI_API bool ImFontAtlas_Build(ImFontAtlas* self);                    // Build pixels data. This is called automatically for you by the GetTexData*** functions.
CIMGUI_API bool ImFontAtlas_IsBuilt(ImFontAtlas* self);
CIMGUI_API void ImFontAtlas_GetTexDataAsAlpha8(ImFontAtlas* self,unsigned char** out_pixels,int* out_width,int* out_height,int* out_bytes_per_pixel);  // 1 byte per-pixel
CIMGUI_API void ImFontAtlas_GetTexDataAsRGBA32(ImFontAtlas* self,unsigned char** out_pixels,int* out_width,int* out_height,int* out_bytes_per_pixel);  // 4 bytes-per-pixel
CIMGUI_API void ImFontAtlas_SetTexID(ImFontAtlas* self,ImTextureID id);
    //-------------------------------------------
    // Glyph Ranges
    //-------------------------------------------
    // Helpers to retrieve list of common Unicode ranges (2 value per range, values are inclusive, zero-terminated list)
    // NB: Make sure that your string are UTF-8 and NOT in your local code page. In C++11, you can create UTF-8 string literal using the u8"Hello world" syntax. See FAQ for details.
    // NB: Consider using GlyphRangesBuilder to build glyph ranges from textual data.
CIMGUI_API const ImWchar* ImFontAtlas_GetGlyphRangesDefault(ImFontAtlas* self);                // Basic Latin, Extended Latin
CIMGUI_API const ImWchar* ImFontAtlas_GetGlyphRangesKorean(ImFontAtlas* self);                 // Default + Korean characters
CIMGUI_API const ImWchar* ImFontAtlas_GetGlyphRangesJapanese(ImFontAtlas* self);               // Default + Hiragana, Katakana, Half-Width, Selection of 1946 Ideographs
CIMGUI_API const ImWchar* ImFontAtlas_GetGlyphRangesChineseFull(ImFontAtlas* self);            // Default + Half-Width + Japanese Hiragana/Katakana + full set of about 21000 CJK Unified Ideographs
CIMGUI_API const ImWchar* ImFontAtlas_GetGlyphRangesChineseSimplifiedCommon(ImFontAtlas* self);// Default + Half-Width + Japanese Hiragana/Katakana + set of 2500 CJK Unified Ideographs for common simplified Chinese
CIMGUI_API const ImWchar* ImFontAtlas_GetGlyphRangesCyrillic(ImFontAtlas* self);               // Default + about 400 Cyrillic characters
CIMGUI_API const ImWchar* ImFontAtlas_GetGlyphRangesThai(ImFontAtlas* self);                   // Default + Thai characters
    // Helpers to build glyph ranges from text data. Feed your application strings/characters to it then call BuildRanges().
CIMGUI_API bool GlyphRangesBuilder_GetBit(GlyphRangesBuilder* self,int n);
CIMGUI_API void GlyphRangesBuilder_SetBit(GlyphRangesBuilder* self,int n);  // Set bit 'c' in the array
CIMGUI_API void GlyphRangesBuilder_AddChar(GlyphRangesBuilder* self,ImWchar c);                          // Add character
CIMGUI_API void GlyphRangesBuilder_AddText(GlyphRangesBuilder* self,const char* text,const char* text_end);      // Add string (each character of the UTF-8 string are added)
CIMGUI_API void GlyphRangesBuilder_AddRanges(GlyphRangesBuilder* self,const ImWchar* ranges);                            // Add ranges, e.g. builder.AddRanges(ImFontAtlas::GetGlyphRangesDefault()) to force add all of ASCII/Latin+Ext
CIMGUI_API void GlyphRangesBuilder_BuildRanges(GlyphRangesBuilder* self,ImVector_ImWchar* out_ranges);                  // Output new ranges
    //-------------------------------------------
    // Custom Rectangles/Glyphs API
    //-------------------------------------------
    // You can request arbitrary rectangles to be packed into the atlas, for your own purposes. After calling Build(), you can query the rectangle position and render your pixels.
    // You can also request your rectangles to be mapped as font glyph (given a font + Unicode point), so you can render e.g. custom colorful icons and use them as regular glyphs.
CIMGUI_API bool CustomRect_IsPacked(CustomRect* self);
CIMGUI_API int ImFontAtlas_AddCustomRectRegular(ImFontAtlas* self,unsigned int id,int width,int height);                                                                   // Id needs to be >= 0x10000. Id >= 0x80000000 are reserved for ImGui and ImDrawList
CIMGUI_API int ImFontAtlas_AddCustomRectFontGlyph(ImFontAtlas* self,ImFont* font,ImWchar id,int width,int height,float advance_x,const ImVec2 offset);   // Id needs to be < 0x10000 to register a rectangle to map into a specific font.
CIMGUI_API const CustomRect* ImFontAtlas_GetCustomRectByIndex(ImFontAtlas* self,int index);
    // [Internal]
CIMGUI_API void ImFontAtlas_CalcCustomRectUV(ImFontAtlas* self,const CustomRect* rect,ImVec2* out_uv_min,ImVec2* out_uv_max);
CIMGUI_API bool ImFontAtlas_GetMouseCursorTexData(ImFontAtlas* self,ImGuiMouseCursor cursor,ImVec2* out_offset,ImVec2* out_size,ImVec2 out_uv_border[2],ImVec2 out_uv_fill[2]);
    //-------------------------------------------
    // Members
    //-------------------------------------------
    // [Internal]
    // NB: Access texture data via GetTexData*() calls! Which will setup a default font for you.
    // Members: Hot ~62/78 bytes
    // Members: Cold ~18/26 bytes
    // Methods
CIMGUI_API void ImFont_ClearOutputData(ImFont* self);
CIMGUI_API void ImFont_BuildLookupTable(ImFont* self);
CIMGUI_API const ImFontGlyph* ImFont_FindGlyph(ImFont* self,ImWchar c);
CIMGUI_API const ImFontGlyph* ImFont_FindGlyphNoFallback(ImFont* self,ImWchar c);
CIMGUI_API void ImFont_SetFallbackChar(ImFont* self,ImWchar c);
CIMGUI_API float ImFont_GetCharAdvance(ImFont* self,ImWchar c);
CIMGUI_API bool ImFont_IsLoaded(ImFont* self);
CIMGUI_API const char* ImFont_GetDebugName(ImFont* self);
    // 'max_width' stops rendering after a certain width (could be turned into a 2d size). FLT_MAX to disable.
    // 'wrap_width' enable automatic word-wrapping across multiple lines to fit into given width. 0.0f to disable.
CIMGUI_API ImVec2 ImFont_CalcTextSizeA(ImFont* self,float size,float max_width,float wrap_width,const char* text_begin,const char* text_end,const char** remaining); // utf8
CIMGUI_API const char* ImFont_CalcWordWrapPositionA(ImFont* self,float scale,const char* text,const char* text_end,float wrap_width);
CIMGUI_API void ImFont_RenderChar(ImFont* self,ImDrawList* draw_list,float size,ImVec2 pos,ImU32 col,unsigned short c);
CIMGUI_API void ImFont_RenderText(ImFont* self,ImDrawList* draw_list,float size,ImVec2 pos,ImU32 col,const ImVec4 clip_rect,const char* text_begin,const char* text_end,float wrap_width,bool cpu_fine_clip);
    // [Internal]
CIMGUI_API void ImFont_GrowIndex(ImFont* self,int new_size);
CIMGUI_API void ImFont_AddGlyph(ImFont* self,ImWchar c,float x0,float y0,float x1,float y1,float u0,float v0,float u1,float v1,float advance_x);
CIMGUI_API void ImFont_AddRemapChar(ImFont* self,ImWchar dst,ImWchar src,bool overwrite_dst); // Makes 'dst' character/glyph points to 'src' character/glyph. Currently needs to be called AFTER fonts have been built.


/////////////////////////hand written functions
//no LogTextV
CIMGUI_API void igLogText(CONST char *fmt, ...);
//no appendfV
CIMGUI_API void ImGuiTextBuffer_appendf(struct ImGuiTextBuffer *buffer, const char *fmt, ...);
CIMGUI_API void ImFontConfig_DefaultConstructor(ImFontConfig *config);
//for getting FLT_MAX in bindings
CIMGUI_API float igGET_FLT_MAX();


