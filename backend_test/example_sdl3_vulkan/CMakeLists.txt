cmake_minimum_required(VERSION 2.8)
Project(cimgui_sdl3_vk)
if(WIN32) # to make mingw work as all the others
set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif(WIN32)
# general settings


if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../../imgui/backends)
	set(BACKENDS_FOLDER "../../imgui/backends/")
else()
	set(BACKENDS_FOLDER "../../imgui/examples/")
endif()

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../../imgui/imgui_tables.cpp)
	set(TABLES_SOURCE "../../imgui/imgui_tables.cpp")
else()
	set(TABLES_SOURCE "")
endif()

include_directories(../../imgui ../../imgui/backends)


include_directories(../../)
set(IMGUI_SOURCES ../../cimgui.cpp
../../cimgui_impl.cpp
../../imgui/imgui.cpp
../../imgui/imgui_draw.cpp
../../imgui/imgui_demo.cpp
../../imgui/imgui_widgets.cpp
${TABLES_SOURCE}
)

set(IMGUI_SOURCES_sdl)
set(IMGUI_LIBRARIES )


#optional adding freetype
option(IMGUI_FREETYPE "add Freetype2" OFF)

if(IMGUI_FREETYPE)
	FIND_PACKAGE(freetype REQUIRED PATHS ${FREETYPE_PATH})
	list(APPEND IMGUI_LIBRARIES freetype)
	list(APPEND IMGUI_SOURCES ../../imgui/misc/freetype/imgui_freetype.cpp)
	add_definitions("-DCIMGUI_FREETYPE=1")
endif(IMGUI_FREETYPE)

# vulkan
find_package(Vulkan REQUIRED FATAL_ERROR)
list(APPEND IMGUI_LIBRARIES Vulkan::Vulkan)
list(APPEND IMGUI_SOURCES ${BACKENDS_FOLDER}imgui_impl_vulkan.cpp)
include_directories(${Vulkan_INCLUDE_DIRS})

#sdl3
list(APPEND IMGUI_SOURCES ${BACKENDS_FOLDER}imgui_impl_sdl3.cpp)
include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.2.8
        #GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)
FetchContent_GetProperties(SDL3)
if (NOT sdl3_POPULATED)
	set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(SDL3)
	set(SDL_TEST OFF CACHE BOOL "" FORCE)
	set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
	add_subdirectory(${sdl3_SOURCE_DIR} ${sdl3_BINARY_DIR})
endif()
include_directories(${SDL3_SOURCE_DIR}/include)


#if dynamic SDL3 then install
# install(TARGETS SDL3 RUNTIME DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
					# LIBRARY DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
# )

add_library(cimgui_sdl STATIC ${IMGUI_SOURCES})
target_compile_definitions(cimgui_sdl PUBLIC "-DIMGUI_USER_CONFIG=\"../cimconfig.h\"")
target_compile_definitions(cimgui_sdl PUBLIC "-DIMGUI_DISABLE_OBSOLETE_FUNCTIONS=1")
target_compile_definitions(cimgui_sdl PUBLIC -DCIMGUI_USE_VULKAN -DCIMGUI_USE_SDL3)
if (WIN32)
    target_compile_definitions(cimgui_sdl PUBLIC "-DIMGUI_IMPL_API=extern \"C\" __declspec\(dllexport\)")
else(WIN32)
    target_compile_definitions(cimgui_sdl PUBLIC "-DIMGUI_IMPL_API=extern \"C\" ")
endif(WIN32)
#target_link_libraries(cimgui_sdl ${IMGUI_LIBRARIES} SDL3-static)

#using library
add_executable(test_sdl main.c)
target_compile_definitions(test_sdl PUBLIC -DCIMGUI_USE_VULKAN -DCIMGUI_USE_SDL3)
if (MINGW)
target_link_options(test_sdl PRIVATE "-mconsole")
endif()
target_link_libraries(test_sdl SDL3-static cimgui_sdl ${IMGUI_LIBRARIES})

