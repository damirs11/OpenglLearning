# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (Tutorials)

find_package(OpenGL REQUIRED)


if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()



# Compile external dependencies 
add_subdirectory (external)

# On Visual 2005 and above, this module can set the debug working directory
cmake_policy(SET CMP0026 OLD)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/external/cmake-modules")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP


include_directories(
	external/glfw/include/
	external/glad/include/
	external/imgui/src
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	glad
	IMGUI
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-D_CRT_SECURE_NO_WARNINGS
)


# 1_OpenGL
file(COPY 1_OpenGL/Shaders DESTINATION ${CMAKE_BINARY_DIR})

file(GLOB_RECURSE SRC
    "1_OpenGL/*.h"
    "1_OpenGL/*.cpp"
)

add_executable(1_OpenGL 
	${SRC}
)
target_link_libraries(1_OpenGL 
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(1_OpenGL  PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/1_OpenGL /")
create_target_launcher(1_OpenGL  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/1_OpenGL /")

# 2_OpenGL
add_executable(2_OpenGL 
	2_OpenGL/Main.cpp
	2_OpenGL/imgui_code.cpp
	2_OpenGL/imgui_code.h
)
target_link_libraries(2_OpenGL 
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(2_OpenGL  PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/2_OpenGL /")
create_target_launcher(2_OpenGL  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/2_OpenGL /")
