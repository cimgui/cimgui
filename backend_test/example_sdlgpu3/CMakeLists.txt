cmake_minimum_required(VERSION 3.30)
project(cimgui_sdlgpu3 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)

include(FetchContent)

FetchContent_Declare(
	sdl3
	URL https://github.com/libsdl-org/SDL/releases/download/release-3.2.8/SDL3-3.2.8.tar.gz
)

set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(sdl3)

include(../cmake/GenerateCimguiBindings.cmake)

set(inclulist ${sdl3_SOURCE_DIR}/include)
GenerateCimguiBindings(cimgui_with_backend sdl3 sdlgpu3 inclulist)
target_link_libraries(cimgui_with_backend PRIVATE SDL3::SDL3)

add_executable(${PROJECT_NAME} 
	main.c
)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 cimgui_with_backend)
target_compile_definitions(
	${PROJECT_NAME}
	PRIVATE 
	CIMGUI_DEFINE_ENUMS_AND_STRUCTS=1
	CIMGUI_USE_SDL3=1
	CIMGUI_USE_SDLGPU3=1
)
