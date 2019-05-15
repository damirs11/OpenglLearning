#include "imgui_code.h"
#include <iostream>

IMGUI::IMGUI()
{
	color_clear = ImVec4(0.45f, 0.55f, 0.60f, 1.00);
	alphaLevel = 0.2f;
	
}

void IMGUI::init_imgui(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

	//ImGui Style
	ImGui::StyleColorsDark();

	//ImGui Platform/Renderer binding
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);



	ImGuiWindowFlags_AlwaysAutoResize;
}

void IMGUI::forloop_imgui()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;
		static bool p_open = 1;

		ImGui::Begin("Hello, world!", &p_open, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysAutoResize);                          // Create a window called "Hello, world!" and append into it.

		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Enable Wireframe", &enable_wireframe);

		ImGui::SliderFloat("Alpha Level", &alphaLevel, -1.0f, 1.0f);
		ImGui::SliderFloat("Angle", &angle, -360.0f, 360.0f);

		static const char* items[] = { "GL_NEAREST", "GL_LINEAR" };
		if (ImGui::Combo("Combo", &selectedItem, items, IM_ARRAYSIZE(items)))
		{
			
		}

		ImGui::ColorEdit3("clear color", (float*)& color_clear); // Edit 3 floats representing a color

		ImGui::End();
	}

	ImGui::Render();

	// draw ImGui
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void IMGUI::destroy_imgui()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}