cmake_minimum_required(VERSION 3.1)

project(cimgui VERSION 0.1.1)

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_tables.cpp)
	set(TABLES_SOURCE "imgui/imgui_tables.cpp")
else()
	set(TABLES_SOURCE "")
endif()

#general settings
file(GLOB IMGUI_SOURCES
    cimgui.cpp
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_widgets.cpp
	${TABLES_SOURCE}
)

option(IMGUI_STATIC "Build as a static library" OFF)
option(IMGUI_FREETYPE "Build with freetype library" OFF)
option(IMGUI_GLFW "Build with glfw3 backend" OFF)
option(IMGUI_OPENGL3 "Build with opengl3 backend" OFF)
option(IMGUI_GLEW "Build with glew backend" OFF)
set(IMGUI_LIBRARIES )
set(IMGUI_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
set(IMGUI_DEFINITIONS IMGUI_DISABLE_OBSOLETE_FUNCTIONS=1)

if(IMGUI_STATIC)
  set(IMGUI_BUILD STATIC)
else(IMGUI_STATIC)
  set(IMGUI_BUILD SHARED)
endif(IMGUI_STATIC)

if(IMGUI_FREETYPE)
	find_package(Freetype REQUIRED)
	list(APPEND IMGUI_INCLUDE_DIRS ${FREETYPE_INCLUDE_DIRS})
	list(APPEND IMGUI_LIBRARIES ${FREETYPE_LIBRARIES})
	list(APPEND IMGUI_SOURCES imgui/misc/freetype/imgui_freetype.cpp)
	add_definitions("-DCIMGUI_FREETYPE=1")
endif(IMGUI_FREETYPE)

if(IMGUI_GLFW)
	list(APPEND IMGUI_SOURCES
		imgui/backends/imgui_impl_glfw.cpp
	)
endif(IMGUI_GLFW)

if(IMGUI_OPENGL3)
	find_package(OpenGL 3 REQUIRED)
	list(APPEND IMGUI_INCLUDE_DIRS ${OPENGL_INCLUDE_DIR})
	list(APPEND IMGUI_LIBRARIES ${OPENGL_LIBRARIES})
	list(APPEND IMGUI_SOURCES
		imgui/backends/imgui_impl_opengl3.cpp
	)
endif(IMGUI_OPENGL3)

if(IMGUI_GLEW)
	find_package(GLEW REQUIRED)
	list(APPEND IMGUI_INCLUDE_DIRS ${GLEW_INCLUDE_DIRS})
	list(APPEND IMGUI_LIBRARIES ${GLEW_LIBRARIES})
	list(APPEND IMGUI_DEFINITIONS IMGUI_IMPL_OPENGL_LOADER_GLEW)
endif(IMGUI_GLEW)

if (WIN32)
	list(APPEND IMGUI_DEFINITIONS IMGUI_IMPL_API=extern\t\"C\"\t__declspec\(dllexport\))
else (WIN32)
	list(APPEND IMGUI_DEFINITIONS IMGUI_IMPL_API=extern\t\"C\"\t)
endif (WIN32)

include(GNUInstallDirs)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

#add library and link
add_library(${PROJECT_NAME} ${IMGUI_BUILD} ${IMGUI_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
                              VERSION ${PROJECT_VERSION}
                            SOVERSION ${PROJECT_VERSION_MAJOR})

target_compile_definitions(${PROJECT_NAME} PRIVATE ${IMGUI_DEFINITIONS})
target_include_directories(${PROJECT_NAME} PRIVATE ${IMGUI_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${IMGUI_LIBRARIES})

#install
install(TARGETS ${PROJECT_NAME}
        EXPORT  ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR})

#install(DIRECTORY include DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cimgui
#        PATTERN ".*" EXCLUDE)
install(
  FILES
    cimgui.h
    generator/output/cimgui_impl.h
  DESTINATION
    ${CMAKE_INSTALL_INCLUDEDIR}
  COMPONENT
    Devel
)

#test
set(CIMGUI_TEST "no" CACHE STRING "Enable compilation of a test unit based on imgui null")

if (CIMGUI_TEST)
  add_subdirectory(test)
endif ()

export(TARGETS ${PROJECT_NAME}
       NAMESPACE ${PROJECT_NAME}::
       FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
)

install(EXPORT      ${PROJECT_NAME}
        FILE        "${PROJECT_NAME}Config.cmake"
        NAMESPACE   ${PROJECT_NAME}::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
