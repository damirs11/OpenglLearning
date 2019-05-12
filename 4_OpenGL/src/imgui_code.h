#pragma once

#ifndef OVERLAY_IMGUI_H
#define OVERLAY_IMGUI_H

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

	
	int selectedItem = 0;
	bool enable_wireframe = false;

	ImVec4 color_clear;
	float alphaLevel;

private:
	const char* glsl_version = "#version 150";

	bool show_demo_window = false;

	
};

#endif // OVERLAY_IMGUI_H