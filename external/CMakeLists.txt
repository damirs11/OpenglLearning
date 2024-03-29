if(MSVC AND NOT "${MSVC_VERSION}" LESS 1400)
	add_definitions( "/MP" )
endif()


add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-D_CRT_SECURE_NO_WARNINGS

)


### GLFW ###

add_subdirectory (glfw)

include_directories(
	glfw/include/
	glad/include/
	.
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(OPENGL_LIBRARY
	${OPENGL_LIBRARY}
	-lGL -lGLU -lXrandr -lXext -lX11 -lrt
	${CMAKE_DL_LIBS}
	${GLFW_LIBRARIES}
)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
set(OPENGL_LIBRARY
	${OPENGL_LIBRARY}
	${CMAKE_DL_LIBS}
	${GLFW_LIBRARIES}
)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

### GLAD ###

add_subdirectory (glad)

### IMGUI ###

add_subdirectory (imgui)

### stb_image ###

file(GLOB STB
	stb/*.cpp
	stb/*.h
)

### GLM ###



set_property(GLOBAL PROPERTY USE_FOLDERS ON)
add_subdirectory(glm)
