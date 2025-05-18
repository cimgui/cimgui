cmake_minimum_required(VERSION 3.15)

# Project metadata
set(CIMGUI_LIBRARY_VERSION "1.91.9" CACHE STRING "Full version of the library")
set(CIMGUI_LIBRARY_SO_VERSION "1" CACHE STRING "Compatibility version of the library")

project(cimgui VERSION ${CIMGUI_LIBRARY_VERSION} LANGUAGES C CXX)

# Require C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Install directories
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Build options
option(CIMGUI_FREETYPE "Enable FreeType support" OFF)
option(CIMGUI_TEST "Enable ImGui test unit compilation" OFF)

# Backend options
option(CIMGUI_BACKEND_ALLEGRO5 "Allegro 5 backend" OFF)
option(CIMGUI_BACKEND_ANDROID "Android backend" OFF)
option(CIMGUI_BACKEND_DX9 "DirectX 9 backend" OFF)
option(CIMGUI_BACKEND_DX10 "DirectX 10 backend" OFF)
option(CIMGUI_BACKEND_DX11 "DirectX 11 backend" OFF)
option(CIMGUI_BACKEND_DX12 "DirectX 12 backend" OFF)
option(CIMGUI_BACKEND_GLFW "GLFW backend" OFF)
option(CIMGUI_BACKEND_GLUT "GLUT backend" OFF)
option(CIMGUI_BACKEND_METAL "Metal backend" OFF)
option(CIMGUI_BACKEND_OPENGL2 "OpenGL 2 backend" OFF)
option(CIMGUI_BACKEND_OPENGL3 "OpenGL 3 backend" OFF)
option(CIMGUI_BACKEND_OSX "macOS backend" OFF)
option(CIMGUI_BACKEND_SDL2 "SDL2 backend" OFF)
option(CIMGUI_BACKEND_SDL3 "SDL3 backend" OFF)
option(CIMGUI_BACKEND_SDLGPU3 "SDL3 GPU backend" OFF)
option(CIMGUI_BACKEND_SDLRENDERER2 "SDL2 Renderer backend" OFF)
option(CIMGUI_BACKEND_SDLRENDERER3 "SDL3 Renderer backend" OFF)
option(CIMGUI_BACKEND_VULKAN "Vulkan backend" OFF)
option(CIMGUI_BACKEND_WGPU "WebGPU backend" OFF)
option(CIMGUI_BACKEND_WIN32 "Win32 backend" OFF)

# Collect base source files
file(GLOB CIMGUI_SOURCE_FILES_LIST CONFIGURE_DEPENDS
  "*.cpp"
  "imgui/*.cpp"
)

# List to accumulate libraries to link
set(CIMGUI_LINK_LIBRARIES "")
# List of libraries for pkg-config
set(CIMGUI_PC_LIBRARIES "")
# Generate the script.
set(CIMGUI_CMAKE_PACKAGES "")

# Add optional FreeType support
if(CIMGUI_FREETYPE)
  find_package(Freetype REQUIRED)
  list(APPEND CIMGUI_SOURCE_FILES_LIST imgui/misc/freetype/imgui_freetype.cpp)
  list(APPEND CIMGUI_LINK_LIBRARIES Freetype::Freetype)
  list(APPEND CIMGUI_PC_LIBRARIES freetype2)
  set(CIMGUI_CMAKE_PACKAGES "${CIMGUI_CMAKE_PACKAGES}find_package(Freetype REQUIRED)\n")
endif()

# Backend implementations
if(CIMGUI_BACKEND_ALLEGRO5)
  list(APPEND CIMGUI_SOURCE_FILES_LIST imgui/backends/imgui_impl_allegro5.cpp)
  list(APPEND CIMGUI_LINK_LIBRARIES allegro allegro_font allegro_ttf)
  list(APPEND CIMGUI_PC_LIBRARIES allegro allegro_font allegro_ttf)
endif()

if(CIMGUI_BACKEND_ANDROID)
  list(APPEND CIMGUI_SOURCE_FILES_LIST imgui/backends/imgui_impl_android.cpp)
  list(APPEND CIMGUI_LINK_LIBRARIES android log)
endif()

if(CIMGUI_BACKEND_DX9)
  list(APPEND CIMGUI_SOURCE_FILES_LIST imgui/backends/imgui_impl_dx9.cpp)
  list(APPEND CIMGUI_LINK_LIBRARIES d3d9)
endif()

if(CIMGUI_BACKEND_DX10)
  list(APPEND CIMGUI_SOURCE_FILES_LIST imgui/backends/imgui_impl_dx10.cpp)
  list(APPEND CIMGUI_LINK_LIBRARIES d3d10)
endif()

if(CIMGUI_BACKEND_DX11)
  list(APPEND CIMGUI_SOURCE_FILES_LIST imgui/backends/imgui_impl_dx11.cpp)
  list(APPEND CIMGUI_LINK_LIBRARIES d3d11)
endif()

if(CIMGUI_BACKEND_DX12)
  list(APPEND CIMGUI_SOURCE_FILES_LIST imgui/backends/imgui_impl_dx12.cpp)
  list(APPEND CIMGUI_LINK_LIBRARIES d3d12 dxgi dxguid)
endif()

if(CIMGUI_BACKEND_GLFW)
  find_package(glfw3 REQUIRED)
  list(APPEND CIMGUI_SOURCE_FILES_LIST imgui/backends/imgui_impl_glfw.cpp)
  list(APPEND CIMGUI_LINK_LIBRARIES glfw3)
  list(APPEND CIMGUI_PC_LIBRARIES glfw3)
  set(CIMGUI_CMAKE_PACKAGES "${CIMGUI_CMAKE_PACKAGES}find_package(glfw3 REQUIRED)\n")
endif()

if(CIMGUI_BACKEND_GLUT)
  find_package(GLUT REQUIRED)
  list(APPEND CIMGUI_SOURCE_FILES_LIST imgui/backends/imgui_impl_glut.cpp)
  list(APPEND CIMGUI_LINK_LIBRARIES GLUT::GLUT)
endif()

if(CIMGUI_BACKEND_METAL)
  list(APPEND CIMGUI_SOURCE_FILES_LIST imgui/backends/imgui_impl_metal.mm)
  find_library(METAL_LIB Metal REQUIRED)
  find_library(QUARTZCORE_LIB QuartzCore REQUIRED)
  list(APPEND CIMGUI_LINK_LIBRARIES ${METAL_LIB} ${QUARTZCORE_LIB})
  list(APPEND CIMGUI_PC_LIBRARIES ${METAL_LIB} ${QUARTZCORE_LIB})
endif()

if(CIMGUI_BACKEND_OPENGL2)
  find_package(OpenGL REQUIRED)
  list(APPEND CIMGUI_SOURCE_FILES_LIST imgui/backends/imgui_impl_opengl2.cpp)
  list(FIND CIMGUI_LINK_LIBRARIES OpenGL::GL IS_LINKED_TO_OPENGL)
  if(${IS_LINKED_TO_OPENGL} STREQUAL -1)
    list(APPEND CIMGUI_LINK_LIBRARIES OpenGL::GL)
    list(APPEND CIMGUI_PC_LIBRARIES ${OPENGL_LIBRARIES})
    set(CIMGUI_CMAKE_PACKAGES "${CIMGUI_CMAKE_PACKAGES}find_package(OpenGL REQUIRED)\n")
  endif()
endif()

if(CIMGUI_BACKEND_OPENGL3)
  find_package(OpenGL REQUIRED)
  list(APPEND CIMGUI_SOURCE_FILES_LIST imgui/backends/imgui_impl_opengl3.cpp)
  list(FIND CIMGUI_LINK_LIBRARIES OpenGL::GL IS_LINKED_TO_OPENGL)
  if(${IS_LINKED_TO_OPENGL} STREQUAL -1)
    list(APPEND CIMGUI_LINK_LIBRARIES OpenGL::GL)
    list(APPEND CIMGUI_PC_LIBRARIES ${OPENGL_LIBRARIES})
    set(CIMGUI_CMAKE_PACKAGES "${CIMGUI_CMAKE_PACKAGES}find_package(OpenGL REQUIRED)\n")
  endif()
endif()

if(CIMGUI_BACKEND_OSX)
  list(APPEND CIMGUI_SOURCE_FILES_LIST imgui/backends/imgui_impl_osx.mm)
  list(APPEND CIMGUI_LINK_LIBRARIES ${APPKIT_LIB})
  list(APPEND CIMGUI_PC_LIBRARIES ${APPKIT_LIB})
endif()

if(CIMGUI_BACKEND_SDL2)
  find_package(SDL2 REQUIRED)
  list(APPEND CIMGUI_SOURCE_FILES_LIST imgui/backends/imgui_impl_sdl2.cpp)
  list(FIND CIMGUI_LINK_LIBRARIES SDL2::SDL2 IS_LINKED_TO_SDL2)
  if(${IS_LINKED_TO_SDL2} STREQUAL -1)
    list(APPEND CIMGUI_LINK_LIBRARIES SDL2::SDL2)
    list(APPEND CIMGUI_PC_LIBRARIES sdl2)
    set(CIMGUI_CMAKE_PACKAGES "${CIMGUI_CMAKE_PACKAGES}find_package(SDL2 REQUIRED)\n")
  endif()
endif()

if(CIMGUI_BACKEND_SDL3)
  find_package(SDL3 REQUIRED)
  list(APPEND CIMGUI_SOURCE_FILES_LIST imgui/backends/imgui_impl_sdl3.cpp)
  list(FIND CIMGUI_LINK_LIBRARIES SDL3::SDL3 IS_LINKED_TO_SDL3)
  if(${IS_LINKED_TO_SDL3} STREQUAL -1)
    list(APPEND CIMGUI_LINK_LIBRARIES SDL3::SDL3)
    list(APPEND CIMGUI_PC_LIBRARIES sdl3)
    set(CIMGUI_CMAKE_PACKAGES "${CIMGUI_CMAKE_PACKAGES}find_package(SDL3 REQUIRED)\n")
  endif()
endif()

if(CIMGUI_BACKEND_SDLGPU3)
  list(APPEND CIMGUI_SOURCE_FILES_LIST imgui/backends/imgui_impl_sdlgpu3.cpp)
  list(FIND CIMGUI_LINK_LIBRARIES SDL3::SDL3 IS_LINKED_TO_SDL3)
  if(${IS_LINKED_TO_SDL3} STREQUAL -1)
    list(APPEND CIMGUI_LINK_LIBRARIES SDL3::SDL3)
    list(APPEND CIMGUI_PC_LIBRARIES sdl3)
    set(CIMGUI_CMAKE_PACKAGES "${CIMGUI_CMAKE_PACKAGES}find_package(SDL3 REQUIRED)\n")
  endif()
endif()

if(CIMGUI_BACKEND_SDLRENDERER2)
  find_package(SDL2 REQUIRED)
  list(APPEND CIMGUI_SOURCE_FILES_LIST imgui/backends/imgui_impl_sdlrenderer2.cpp)
  list(FIND CIMGUI_LINK_LIBRARIES SDL2::SDL2 IS_LINKED_TO_SDL2)
  if(${IS_LINKED_TO_SDL2} STREQUAL -1)
    list(APPEND CIMGUI_LINK_LIBRARIES SDL2::SDL2)
    list(APPEND CIMGUI_PC_LIBRARIES sdl2)
    set(CIMGUI_CMAKE_PACKAGES "${CIMGUI_CMAKE_PACKAGES}find_package(SDL2 REQUIRED)\n")
  endif()
endif()

if(CIMGUI_BACKEND_SDLRENDERER3)
  find_package(SDL3 REQUIRED)
  list(APPEND CIMGUI_SOURCE_FILES_LIST imgui/backends/imgui_impl_sdlrenderer3.cpp)
  list(FIND CIMGUI_LINK_LIBRARIES SDL3::SDL3 IS_LINKED_TO_SDL3)
  if(${IS_LINKED_TO_SDL3} STREQUAL -1)
    list(APPEND CIMGUI_LINK_LIBRARIES SDL3::SDL3)
    list(APPEND CIMGUI_PC_LIBRARIES sdl3)
    set(CIMGUI_CMAKE_PACKAGES "${CIMGUI_CMAKE_PACKAGES}find_package(SDL3 REQUIRED)\n")
  endif()
endif()

if(CIMGUI_BACKEND_VULKAN)
  find_package(Vulkan REQUIRED)
  list(APPEND CIMGUI_SOURCE_FILES_LIST imgui/backends/imgui_impl_vulkan.cpp)
  list(APPEND CIMGUI_LINK_LIBRARIES Vulkan::Vulkan)
  set(CIMGUI_CMAKE_PACKAGES "${CIMGUI_CMAKE_PACKAGES}find_package(Vulkan REQUIRED)\n")
endif()

if(CIMGUI_BACKEND_WGPU)
  list(APPEND CIMGUI_SOURCE_FILES_LIST imgui/backends/imgui_impl_wgpu.cpp)
  list(APPEND CIMGUI_LINK_LIBRARIES wgpu-native)
endif()

if(CIMGUI_BACKEND_WIN32)
  list(APPEND CIMGUI_SOURCE_FILES_LIST imgui/backends/imgui_impl_win32.cpp)
  list(APPEND CIMGUI_LINK_LIBRARIES user32 gdi32 shell32)
endif()

# Windows-specific linking
if(WIN32)
  list(APPEND CIMGUI_LINK_LIBRARIES imm32)
endif()

# Create the libraries
add_library(cimgui-Static STATIC ${CIMGUI_SOURCE_FILES_LIST})

# Library properties
set_target_properties(cimgui-Static PROPERTIES
  OUTPUT_NAME cimgui
  VERSION ${CIMGUI_LIBRARY_VERSION}
  SOVERSION ${CIMGUI_LIBRARY_SO_VERSION}
)

# Compiler definitions
target_compile_definitions(cimgui-Static PRIVATE -DIMGUI_USER_CONFIG=\"../cimconfig.h\")
target_compile_definitions(cimgui-Static PRIVATE CIMGUI_DISABLE_OBSOLETE_FUNCTIONS=1)

# Platform-specific definitions
if(WIN32)
  target_compile_definitions(cimgui-Static PRIVATE "IMGUI_IMPL_API=extern \"C\" __declspec(dllexport)")
else()
  target_compile_definitions(cimgui-Static PRIVATE "IMGUI_IMPL_API=extern \"C\"")
endif()

# Include directories
target_include_directories(cimgui-Static PRIVATE ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/imgui)

# FreeType include directories
if(CIMGUI_FREETYPE)
  target_include_directories(cimgui-Static PRIVATE ${FREETYPE_INCLUDE_DIRS})
endif()

# Link the collected libraries
target_link_libraries(cimgui-Static PUBLIC ${CIMGUI_LINK_LIBRARIES})

# Right substitution for pkg-config.
string(REPLACE ";" " " CIMGUI_PC_LIBRARIES "${CIMGUI_PC_LIBRARIES}")

# Add the shared library if not compiling with emscripten.
if(NOT CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
  # Create the libraries
  add_library(cimgui-Shared SHARED ${CIMGUI_SOURCE_FILES_LIST})
  # Library properties
  set_target_properties(cimgui-Shared PROPERTIES
    OUTPUT_NAME cimgui
    VERSION ${CIMGUI_LIBRARY_VERSION}
    SOVERSION ${CIMGUI_LIBRARY_SO_VERSION}
    PUBLIC_HEADER "cimgui.h;cimgui_impl.h"
  )

  # Compiler definitions
  target_compile_definitions(cimgui-Shared PRIVATE -DIMGUI_USER_CONFIG=\"../cimconfig.h\")
  target_compile_definitions(cimgui-Shared PRIVATE CIMGUI_DISABLE_OBSOLETE_FUNCTIONS=1)
  target_compile_definitions(cimgui-Shared PRIVATE "IMGUI_IMPL_API=extern \"C\"")

  # Include directories
  target_include_directories(cimgui-Shared PRIVATE ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/imgui)

  # FreeType include directories
  if(CIMGUI_FREETYPE)
    target_include_directories(cimgui-Shared PRIVATE ${FREETYPE_INCLUDE_DIRS})
  endif()

  # Link the collected libraries
  target_link_libraries(cimgui-Shared PUBLIC ${CIMGUI_LINK_LIBRARIES})
endif()

# Installation rules
if(NOT CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
  # CMake version configuration file
  write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/cimguiConfigVersion.cmake"
    VERSION ${CIMGUI_LIBRARY_VERSION}
    COMPATIBILITY SameMajorVersion
  )

  # Export cmake config file
  configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cimguiConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cimguiConfig.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_DATADIR}/cimguiConfig/cmake"
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )

  install(TARGETS cimgui-Shared cimgui-Static
    EXPORT cimguiConfig
    RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )

  install(EXPORT cimguiConfig
    NAMESPACE cimgui::
    DESTINATION ${CMAKE_INSTALL_DATADIR}/cimguiConfig/cmake
    FILE cimguiTargets.cmake
  )

  file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/cimguiDependencies.cmake
    "${CIMGUI_CMAKE_PACKAGES}"
  )

  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/cimguiConfig.cmake
      ${CMAKE_CURRENT_BINARY_DIR}/cimguiConfigVersion.cmake
      ${CMAKE_CURRENT_BINARY_DIR}/cimguiDependencies.cmake
    DESTINATION ${CMAKE_INSTALL_DATADIR}/cimguiConfig/cmake
  )

  configure_file(
    "${CMAKE_CURRENT_LIST_DIR}/cmake/cimgui.pc.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cimgui.pc"
    @ONLY
  )

  install(FILES "${CMAKE_CURRENT_BINARY_DIR}/cimgui.pc"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig"
  )
else()
  # CMake version configuration file
  write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/cimguiConfigVersion.cmake"
    VERSION ${CIMGUI_LIBRARY_VERSION}
    COMPATIBILITY SameMajorVersion
  )

  # Export cmake config file
  configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cimguiConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cimguiConfig.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_DATADIR}/cimguiConfig/cmake"
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )

  install(TARGETS cimgui-Static
    EXPORT cimguiConfig
    RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )

  install(EXPORT cimguiConfig
    NAMESPACE cimgui::
    DESTINATION ${CMAKE_INSTALL_DATADIR}/cimguiConfig/cmake
    FILE cimguiTargets.cmake
  )

  file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/cimguiDependencies.cmake
    "${CIMGUI_CMAKE_PACKAGES}"
  )

  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/cimguiConfig.cmake
      ${CMAKE_CURRENT_BINARY_DIR}/cimguiConfigVersion.cmake
      ${CMAKE_CURRENT_BINARY_DIR}/cimguiDependencies.cmake
    DESTINATION ${CMAKE_INSTALL_DATADIR}/cimguiConfig/cmake
  )

  configure_file(
    "${CMAKE_CURRENT_LIST_DIR}/cmake/cimgui.pc.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cimgui.pc"
    @ONLY
  )

  install(FILES "${CMAKE_CURRENT_BINARY_DIR}/cimgui.pc"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig"
  )
endif()

# Enable test project if requested
if(CIMGUI_TEST)
  add_subdirectory(test)
endif()
