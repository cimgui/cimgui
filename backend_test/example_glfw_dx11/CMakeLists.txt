cmake_minimum_required(VERSION 3.11)
project(cimgui_glfwdx11 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)

include(FetchContent)

set(GLFW_VERSION 3.3.8)
FetchContent_Declare(
    glfw
    EXCLUDE_FROM_ALL
    URL https://github.com/glfw/glfw/archive/refs/tags/${GLFW_VERSION}.tar.gz
    GIT_PROGRESS true)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
if (NOT STATIC_BUILD)
	set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
endif()


FetchContent_MakeAvailable(glfw)
install(TARGETS glfw RUNTIME DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
					LIBRARY DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)

include(../cmake/GenerateCimguiBindings.cmake)

set(inclulist "")
GenerateCimguiBindings(cimgui_with_backend "glfw" dx11 inclulist)
target_link_libraries(cimgui_with_backend PRIVATE glfw d3dcompiler dwmapi)

add_executable(${PROJECT_NAME} 
	main.c
)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw cimgui_with_backend d3d11 d3dcompiler dwmapi)
target_compile_definitions(
	${PROJECT_NAME}
	PRIVATE 
	CIMGUI_DEFINE_ENUMS_AND_STRUCTS=1
	CIMGUI_USE_GLFW=1
	CIMGUI_USE_DX11=1
)
