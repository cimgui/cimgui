
#if defined _WIN32 || defined __CYGWIN__
#define API __declspec(dllexport)
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
CIMGUI_API void				ig_GetContentRegionMax(ImVec2& out);
CIMGUI_API void				ig_GetWindowContentRegionMin(ImVec2& out);
CIMGUI_API void				ig_GetWindowContentRegionMax(ImVec2& out);
CIMGUI_API ImDrawList*		ig_GetWindowDrawList();
CIMGUI_API ImFont*			ig_GetWindowFont();
CIMGUI_API float			ig_GetWindowFontSize(); 
CIMGUI_API void				ig_SetWindowFontScale(float scale);
CIMGUI_API void				ig_GetWindowPos(ImVec2& out);
CIMGUI_API void				ig_GetWindowSize(ImVec2& out);
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