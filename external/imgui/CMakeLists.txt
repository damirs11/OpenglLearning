cmake_minimum_required(VERSION 3.2)
project(IMGUI)

add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_GLAD)

file(GLOB_RECURSE SOURCE_CPP RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp  )
file(GLOB_RECURSE SOURCE_HEADER RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.h  )

add_library(IMGUI ${SOURCE_HEADER} ${SOURCE_CPP})