#include "imgui.h"

#define CIMGUI_STRINGIZE_(x) #x
#define CIMGUI_STRINGIZE(x) CIMGUI_STRINGIZE_(x)
#define CIMGUI_DEFSTRING(x) "#define " #x " " CIMGUI_STRINGIZE(x)

#ifdef IMGUI_VERSION
#pragma message(CIMGUI_DEFSTRING(IMGUI_VERSION))
#endif

#ifdef IMGUI_HAS_DOCK
#pragma message(CIMGUI_DEFSTRING(IMGUI_HAS_DOCK))
#endif

#ifdef IMGUI_HAS_IMSTR
#pragma message(CIMGUI_DEFSTRING(IMGUI_HAS_IMSTR))
#endif

#ifdef FLT_MIN
#pragma message(CIMGUI_DEFSTRING(FLT_MIN))
#endif

#ifdef FLT_MAX
#pragma message(CIMGUI_DEFSTRING(FLT_MAX))
#endif
