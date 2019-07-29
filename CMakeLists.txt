Project(cimgui)
cmake_minimum_required(VERSION 2.8)

#general settings
include_directories(imgui)
add_definitions("-DIMGUI_DISABLE_OBSOLETE_FUNCTIONS=1")

include_directories(.)
set(IMGUI_SOURCES ./cimgui.cpp ./imgui/imgui.cpp ./imgui/imgui_draw.cpp ./imgui/imgui_demo.cpp ./imgui/imgui_widgets.cpp)

set(IMGUI_LIBRARIES )

if (WIN32)
    add_definitions("-DIMGUI_IMPL_API=extern \"C\" __declspec\(dllexport\)")
else(WIN32)
    add_definitions("-DIMGUI_IMPL_API=extern \"C\" ")
endif(WIN32)

set(IMGUI_STATIC "no" CACHE STRING "Build as a static library")

#add library and link
if (IMGUI_STATIC)
    add_library(cimgui STATIC ${IMGUI_SOURCES})
else (IMGUI_STATIC)
    add_library(cimgui SHARED ${IMGUI_SOURCES})
endif (IMGUI_STATIC)

target_link_libraries(cimgui ${IMGUI_LIBRARIES})
set_target_properties(cimgui PROPERTIES PREFIX "")

#install
install(TARGETS cimgui
              RUNTIME DESTINATION  .
              LIBRARY DESTINATION  .
              ARCHIVE DESTINATION  .
              )
