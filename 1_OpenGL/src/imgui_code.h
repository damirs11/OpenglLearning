#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


class IMGUI
{
public:

	IMGUI();

	void init_imgui(GLFWwindow* window);
	void forloop_imgui();
	void destroy_imgui();


public:
	bool init = false;
	ImVec4 color_clear;
	float xOffset;

private:
	const char* glsl_version = "#version 150";

	bool show_demo_window = false;
	bool enable_wireframe = false;

	
};