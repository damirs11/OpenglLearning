#include "imgui_code.h"
#include "Shader.h"
#include "Image.h"
#include "Texture.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

IMGUI overlay_imgui;


int main()
{
	// glfw: initialize and configure
	// ------------------------------
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	overlay_imgui.init_imgui(window);
	
	
	// * GL_REPEAT: The default behavior for textures.Repeats the texture image.
	// * GL_MIRRORED_REPEAT : Same as GL_REPEAT but mirrors the image with each repeat.
	// * GL_CLAMP_TO_EDGE : Clamps the coordinates between 0 and 1. The result is that higher coordinates become clamped to the edge, resulting in a stretched edge pattern.
	// * GL_CLAMP_TO_BORDER : Coordinates outside the range are now given a user - specified border color.*/
	//----------------------------------------------------------------------------------------------------
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); // S = X
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT); // T = Y
	// * GL_CLAMP_TO_BORDER
	// float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// * GL_NEAREST_MIPMAP_NEAREST: takes the nearest mipmap to match the pixel sizeand uses nearest neighbor interpolation for texture sampling.
	// * GL_LINEAR_MIPMAP_NEAREST : takes the nearest mipmap leveland samples using linear interpolation.
	// * GL_NEAREST_MIPMAP_LINEAR : linearly interpolates between the two mipmaps that most closely match the size of a pixeland samples via nearest neighbor interpolation.
	// * GL_LINEAR_MIPMAP_LINEAR : linearly interpolates between the two closest mipmapsand samples the texture via linear interpolation.

	


	Shader shader("Assets/vertexShader.vert", "Assets/fragmentShader.frag");

	Image image_cont("Assets/container.jpg");
	Image image_face("Assets/awesomeface.png");

	Texture texture_1(image_cont, GL_RGB);
	Texture texture_2(image_face);

	texture_2.SetWrapping(GL_MIRRORED_REPEAT);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	float vertices[] = {
		// positions         // colors			// textures
		-0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f, // top left
		 0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, // bottom left

		 0.0f,  1.0f, 0.0f,  1.0f, 1.0f, 0.0f,  0.5f, 1.0f, // top
		-1.0f, -1.0f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // bottom left
		 1.0f, -1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f  // bottom right
	};
	int indices[] = {
		4, 5, 6
	};
	unsigned int VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// textures attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	


	shader.use();
	shader.setInt("texture1", 0);
	shader.setInt("texture2", 1);

	


	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// events handle
		glfwPollEvents();


		glClearColor(overlay_imgui.color_clear.x, overlay_imgui.color_clear.y, overlay_imgui.color_clear.z, overlay_imgui.color_clear.w);
		glClear(GL_COLOR_BUFFER_BIT);


		// input
		// -----
		processInput(window);
		
		// bind texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture_2);

		// GLM
		glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		// first container
		// ---------------
		shader.setMat4("transform", transform);
		shader.setFloat("alphaLevel", overlay_imgui.alphaLevel);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		// IMGUI
		overlay_imgui.forloop_imgui();

		if (overlay_imgui.enable_wireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);



		glfwMakeContextCurrent(window);
		glfwSwapBuffers(window);
	}

	

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	
	overlay_imgui.destroy_imgui();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}