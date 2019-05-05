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
	external/imgui/src/
	external/stb_lib
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
set(NAME 1_OpenGL)

file(GLOB_RECURSE SRC
    "${NAME}/src/*.h"
    "${NAME}/src/*.cpp"
)

set(ASSETS_DIR "${NAME}/Assets/")

file(GLOB Assets
	"${ASSETS_DIR}/Shaders/*.*"
    "${ASSETS_DIR}/Textures/*.*"
}
)


add_executable(${NAME} 
	${SRC}
	${Assets}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/${NAME}/Assets PREFIX "Assets" FILES ${Assets})

target_link_libraries(${NAME} 
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(${NAME}  PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${NAME} /")
create_target_launcher(${NAME}  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${NAME} /")

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

# 3_OpenGL
set(NAME 3_OpenGL)

file(GLOB_RECURSE SRC
    "${NAME}/src/*.h"
    "${NAME}/src/*.cpp"
)

set(ASSETS_DIR "${NAME}/Assets/")

file(GLOB Assets
	"${ASSETS_DIR}/Shaders/*.*"
    "${ASSETS_DIR}/Textures/*.*"
})

file(COPY ${Assets} DESTINATION Assets NO_SOURCE_PERMISSIONS)


add_executable(${NAME} 
	${SRC}
	${Assets}
	${STB}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/${NAME}/Assets PREFIX "Assets" FILES ${Assets})

target_link_libraries(${NAME} 
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(${NAME}  PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${NAME} /")
create_target_launcher(${NAME}  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${NAME} /")