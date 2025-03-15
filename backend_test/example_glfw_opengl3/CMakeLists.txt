Project(cimgui_glfw)
cmake_minimum_required(VERSION 3.11)
if(WIN32) # to mingw work as all the others
	set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif(WIN32)

#run in build dir
set (CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR})

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
add_definitions("-DIMGUI_USER_CONFIG=\"../cimconfig.h\"")
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

set(IMGUI_LIBRARIES )


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

set(GLFW_VERSION 3.4)
include(FetchContent)
	FetchContent_Declare(
    glfw
    URL https://github.com/glfw/glfw/archive/refs/tags/${GLFW_VERSION}.tar.gz)
	#GIT_REPOSITORY https://github.com/glfw/glfw )

FetchContent_GetProperties(glfw)
if (NOT glfw_POPULATED)
	set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(glfw)
	set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
	set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
	if (NOT STATIC_BUILD)
	set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
	endif()
	add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

#if dynamic glfw then install
install(TARGETS glfw RUNTIME DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
					LIBRARY DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)
#FIND_PACKAGE(glfw3 PATHS "C:/LuaGL/gitsources/BUILDS/GLFW/install" REQUIRED)


if (NOT STATIC_BUILD)
  add_library(cimgui SHARED ${IMGUI_SOURCES})
else()
  add_library(cimgui STATIC ${IMGUI_SOURCES})
endif()

if (WIN32)
    target_compile_definitions(cimgui PUBLIC "-DIMGUI_IMPL_API=extern \"C\" __declspec\(dllexport\)")
else(WIN32)
    target_compile_definitions(cimgui PUBLIC "-DIMGUI_IMPL_API=extern \"C\" ")
endif(WIN32)

target_link_libraries(cimgui ${IMGUI_LIBRARIES} glfw)


# using library
add_executable(${PROJECT_NAME} main.c)
target_compile_definitions(${PROJECT_NAME} PUBLIC -DCIMGUI_USE_OPENGL3 -DCIMGUI_USE_GLFW)
target_link_libraries(${PROJECT_NAME} cimgui)


