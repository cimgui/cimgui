# This downloads cimgui, configures it to generate the SDL3 and SDLGPU3 bindings, 
# and adds it as a cmake target for you to link to. Feel free to copy this file
# into your project, or refit it to your needs.

function(GenerateCimguiBindings target)
	include(FetchContent)

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

	# We're checking to see if the cimgui_impl.h file already has SDLGPU3 bindings,
	# since this will be executed on each "configure" (whenever you run cmake)
	string(FIND "${cimgui_impl}" "SDLGPU3" sdlgpu_position)
	# If we don't find it, sdlgpu_position will be -1
	if(sdlgpu_position EQUAL -1)
		# NOTE: This requires a luajit on your path. If your binary is named different, you will
		# need to modify this command
		cmake_path(GET CMAKE_C_COMPILER FILENAME C_COMP)
		cmake_path(REMOVE_EXTENSION C_COMP)
		execute_process(
		COMMAND luajit generator.lua ${C_COMP} internal sdl3 sdlgpu3 -I../imgui -I${sdl3_SOURCE_DIR}/include
		WORKING_DIRECTORY ${cimgui_SOURCE_DIR}/generator
		ERROR_VARIABLE error_command
		RESULT_VARIABLE build_command_result
		)
		if(NOT ${build_command_result} EQUAL 0)
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
		${cimgui_SOURCE_DIR}/imgui/backends/imgui_impl_sdl3.cpp
		${cimgui_SOURCE_DIR}/imgui/backends/imgui_impl_sdlgpu3.cpp
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
	target_link_libraries(${target} PRIVATE SDL3::SDL3)
endfunction()
