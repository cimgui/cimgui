# This downloads cimgui, configures it to generate the SDL3 and SDLGPU3 bindings, 
# and adds it as a cmake target for you to link to. Feel free to copy this file
# into your project, or refit it to your needs.

#include(CMakePrintHelpers)

function(IncludesStr comp includes)
	#cmake_print_variables(includes)
	if("${comp}" STREQUAL "cl")
		set(Ist "/I")
	else()
		set(Ist "-I")
	endif()
	set(incstr "")
	foreach(inc ${${includes}})
		set(incstr ${incstr} ${Ist}${inc})
	endforeach()
	set(incstr ${incstr} PARENT_SCOPE)
endfunction()



function(GenerateCimguiBindings target platbk rendbk _inclist)
	include(FetchContent)
	set(FETCHCONTENT_QUIET OFF)
	#cmake_print_variables(_inclist)
	set(__inclist ${${_inclist}})
	#cmake_print_variables(__inclist)
	# NOTE: In your own project, you may want to pin this project to a particular commit
	FetchContent_Declare(
		cimgui
		EXCLUDE_FROM_ALL
		GIT_REPOSITORY https://github.com/cimgui/cimgui.git 
		GIT_TAG docking_inter
		GIT_SUBMODULES_RECURSE true
		GIT_PROGRESS true
		GIT_SHALLOW true
	)

	FetchContent_MakeAvailable(cimgui)

	file(READ ${cimgui_SOURCE_DIR}/cimgui_impl.h cimgui_impl)

	# We're checking to see if the cimgui_impl.h file already has required bindings,
	# since this will be executed on each "configure" (whenever you run cmake)
	string(TOUPPER ${platbk} PLATBK)
	string(TOUPPER ${rendbk} RENDBK)
	string(FIND "${cimgui_impl}" CIMGUI_USE_${RENDBK} rendbk_position)
	string(FIND "${cimgui_impl}" CIMGUI_USE_${PLATBK} platbk_position)
	# If we don't find it, rendbk_position will be -1
	if(rendbk_position EQUAL -1 OR platbk_position EQUAL -1)
		#get compiler name
		cmake_path(GET CMAKE_C_COMPILER FILENAME C_COMP)
		cmake_path(REMOVE_EXTENSION C_COMP)
		#get includes string
		IncludesStr(${C_COMP} __inclist)
		message(STATUS "incstr is ${incstr}")
		execute_process(
		COMMAND luajit generator.lua ${C_COMP} "internal noimstrv" ${platbk} ${rendbk} ${incstr}
		WORKING_DIRECTORY ${cimgui_SOURCE_DIR}/generator
		ERROR_VARIABLE error_command
		RESULT_VARIABLE build_command_result
		)
		if(NOT ${build_command_result} EQUAL 0)
			message(STATUS "cimgui generation failed: Do you have LuaJIT?")
			message(STATUS "cimgui generation failed: ${build_command_result}")
			message(FATAL_ERROR "error_command: ${error_command}")
		endif()
	endif()

	add_library(${target} SHARED 
		${cimgui_SOURCE_DIR}/cimgui.cpp
		${cimgui_SOURCE_DIR}/cimgui_impl.cpp
		${cimgui_SOURCE_DIR}/imgui/imgui.cpp
		${cimgui_SOURCE_DIR}/imgui/imgui_draw.cpp
		${cimgui_SOURCE_DIR}/imgui/imgui_demo.cpp
		${cimgui_SOURCE_DIR}/imgui/imgui_widgets.cpp
		${cimgui_SOURCE_DIR}/imgui/imgui_tables.cpp
		${cimgui_SOURCE_DIR}/imgui/backends/imgui_impl_${platbk}.cpp
		${cimgui_SOURCE_DIR}/imgui/backends/imgui_impl_${rendbk}.cpp
	)

	target_include_directories(${target} PUBLIC ${cimgui_SOURCE_DIR} ${cimgui_SOURCE_DIR}/generator/output)
	target_include_directories(${target} PRIVATE ${cimgui_SOURCE_DIR}/imgui ${cimgui_SOURCE_DIR}/imgui/backends)
	#for ASSERT working on Release mode
	target_compile_definitions(${target} PUBLIC "-DIMGUI_USER_CONFIG=\"../cimconfig.h\"")
	target_compile_definitions(${target} PUBLIC "-DIMGUI_DISABLE_OBSOLETE_FUNCTIONS=1")
	if (WIN32)
		target_compile_definitions(${target} PUBLIC "-DIMGUI_IMPL_API=extern \"C\" __declspec\(dllexport\)")
	else(WIN32)
		target_compile_definitions(${target} PUBLIC "-DIMGUI_IMPL_API=extern \"C\" ")
	endif(WIN32)
	target_compile_features(${target} PRIVATE cxx_std_11)
endfunction()
