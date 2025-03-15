Project(cimgui_sdl)
cmake_minimum_required(VERSION 2.8)
if(WIN32) #to mingw work as all the others
set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif(WIN32)

set (CMAKE_CXX_STANDARD 11)

#general settings


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



add_compile_definitions("IMGUI_IMPL_OPENGL_LOADER_GL3W")

#optional adding freetype
option(IMGUI_FREETYPE "add Freetype2" OFF)

if(IMGUI_FREETYPE)
	FIND_PACKAGE(freetype REQUIRED PATHS ${FREETYPE_PATH})
	list(APPEND IMGUI_LIBRARIES freetype)
	list(APPEND IMGUI_SOURCES ../../imgui/misc/freetype/imgui_freetype.cpp)
	add_definitions("-DCIMGUI_FREETYPE=1")
endif(IMGUI_FREETYPE)

#opengl3
list(APPEND IMGUI_SOURCES ${BAKENDS_FOLDER}imgui_impl_opengl3.cpp)
include_directories(../../imgui/examples/libs/gl3w)
if(WIN32)
       list(APPEND IMGUI_LIBRARIES opengl32)
else(WIN32)#Unix
       list(APPEND IMGUI_LIBRARIES GL)
endif(WIN32)


list(APPEND IMGUI_SOURCES ${BAKENDS_FOLDER}imgui_impl_sdl2.cpp)
include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.30.12
        #GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)
#FetchContent_MakeAvailable(SDL2)
FetchContent_GetProperties(SDL2)
if (NOT sdl2_POPULATED)
	set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(SDL2)
	set(SDL_TEST OFF CACHE BOOL "" FORCE)
	set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
	add_subdirectory(${sdl2_SOURCE_DIR} ${sdl2_BINARY_DIR})
endif()
include_directories(${SDL2_SOURCE_DIR}/include})

#if dynamic SDL2 then install
install(TARGETS SDL2 RUNTIME DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
					LIBRARY DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)

add_library(cimgui_sdl SHARED ${IMGUI_SOURCES})
target_compile_definitions(cimgui_sdl PUBLIC "-DIMGUI_DISABLE_OBSOLETE_FUNCTIONS=1")
if (WIN32)
    target_compile_definitions(cimgui_sdl PUBLIC "-DIMGUI_IMPL_API=extern \"C\" __declspec\(dllexport\)")
else(WIN32)
    target_compile_definitions(cimgui_sdl PUBLIC "-DIMGUI_IMPL_API=extern \"C\" ")
endif(WIN32)
target_link_libraries(cimgui_sdl ${IMGUI_LIBRARIES} SDL2)

#using library
add_executable(test_sdl main.c)
target_compile_definitions(test_sdl PUBLIC -DCIMGUI_USE_OPENGL3 -DCIMGUI_USE_SDL2)
if (MINGW)
target_link_options(test_sdl PRIVATE "-mconsole")
endif()
target_link_libraries(test_sdl SDL2 cimgui_sdl)
