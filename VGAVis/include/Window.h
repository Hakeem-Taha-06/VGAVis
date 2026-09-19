#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_stdlib.h>

#include "tinyfiledialogs.h"

#include "stb/stb_image.h"

#include "InputManager.h"
#include "Shader.h"

#include <iostream>
#include <memory>
#include <string>
#include <fstream>

class Simulator;

class Window
{
public:
	Window(int width, int height);
	~Window();

	inline bool shouldExit() const { return glfwWindowShouldClose(m_window); }

	void startFrame();
	void render(Simulator& sim);
	void endFrame();

	bool frame_ready = true;
private:

	const char* vshader_src = "#version 330 core\n"
							  "layout (location = 0) in vec3 aPos;\n"
							  "void main()\n"
							  "{\n"
							  " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
							  "}\0";

	const char* fshader_src = "#version 330 core\n"
						      "out vec4 FragColor;\n"
						      "void main()\n"
						      "{\n"
						      "	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
						      "}\n";

	int WIDTH, HEIGHT;
	GLFWwindow* m_window;

	std::unique_ptr<Shader> shader;
	unsigned int VAO = 0;
	unsigned int VBO = 0;

	InputManager inputManager;

	void init();
	void renderControlWindow(Simulator& sim);
	void renderScreenWindow(Simulator& sim);

	std::string image_path;
	unsigned int screenTexture = 0;
	int screenScale = 1;

	// Helpers
	std::string readFile(std::string path);

};

