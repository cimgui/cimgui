Project(cimgui_glfw)
cmake_minimum_required(VERSION 3.11)
if(WIN32) # to mingw work as all the others
	set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif(WIN32)

set (CMAKE_CXX_STANDARD 11)

# general settings
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../../imgui/backends)
	set(BAKENDS_FOLDER "../../imgui/backends/")
else()
	set(BAKENDS_FOLDER "../../imgui/examples/")
endif()

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../../imgui/imgui_tables.cpp)
	set(TABLES_SOURCE "../../imgui/imgui_tables.cpp")
else()
	set(TABLES_SOURCE "")
endif()

include_directories(../../imgui)
add_definitions("-DIMGUI_DISABLE_OBSOLETE_FUNCTIONS=1")

include_directories(../../)
set(IMGUI_SOURCES 
../../cimgui.cpp 
../../imgui/imgui.cpp 
../../imgui/imgui_draw.cpp 
../../imgui/imgui_demo.cpp 
../../imgui/imgui_widgets.cpp
${TABLES_SOURCE} 
)

set(IMGUI_SOURCES_sdl)
set(IMGUI_LIBRARIES )

if (WIN32)
    add_definitions("-DIMGUI_IMPL_API=extern \"C\" __declspec\(dllexport\)")
else(WIN32)
    add_definitions("-DIMGUI_IMPL_API=extern \"C\" ")
endif(WIN32)

add_compile_definitions("IMGUI_IMPL_OPENGL_LOADER_GL3W")

# optional adding freetype
option(IMGUI_FREETYPE "add Freetype2" OFF)

if(IMGUI_FREETYPE)
	FIND_PACKAGE(freetype REQUIRED PATHS ${FREETYPE_PATH})
	list(APPEND IMGUI_LIBRARIES freetype)
	list(APPEND IMGUI_SOURCES ../../imgui/misc/freetype/imgui_freetype.cpp)
	add_definitions("-DCIMGUI_FREETYPE=1")
endif(IMGUI_FREETYPE)

# opengl3
list(APPEND IMGUI_SOURCES ${BAKENDS_FOLDER}imgui_impl_opengl3.cpp)
include_directories(../../imgui/examples/libs/gl3w)
if(WIN32)
       list(APPEND IMGUI_LIBRARIES opengl32)
else(WIN32) # Unix
       list(APPEND IMGUI_LIBRARIES GL)
endif(WIN32)

# GLFW
list(APPEND IMGUI_SOURCES ${BAKENDS_FOLDER}imgui_impl_glfw.cpp)

set(GLFW_VERSION 3.3.8)
include(FetchContent)
	FetchContent_Declare(
    glfw
    URL https://github.com/glfw/glfw/archive/refs/tags/${GLFW_VERSION}.tar.gz)

FetchContent_GetProperties(glfw)
if (NOT glfw_POPULATED)
	set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(glfw)
	set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
	add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()


# glfw/imgui gets confused if it is not statically built.
IF (WIN32)
  add_library(cimgui STATIC ${IMGUI_SOURCES})
ELSE()
  add_library(cimgui SHARED ${IMGUI_SOURCES})
ENDIF()

target_link_libraries(cimgui ${IMGUI_LIBRARIES} glfw)


# using library
include_directories(../../generator/output/)
add_executable(${PROJECT_NAME} main.c)
target_compile_definitions(${PROJECT_NAME} PUBLIC -DCIMGUI_USE_OPENGL3 -DCIMGUI_USE_GLFW)
if (MINGW)
	target_link_options(${PROJECT_NAME} PRIVATE "-mconsole")
endif()
target_link_libraries(${PROJECT_NAME} ${IMGUI_SDL_LIBRARY} cimgui)


