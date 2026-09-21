#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_stdlib.h>

#include "tinyfiledialogs.h"

#include "stb/stb_image.h"
#include "stb/stb_image_resize2.h"

#include "InputManager.h"
#include "Shader.h"

#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <cstdint>

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
	int sim_speed = 3000;
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
	void renderFramebufferWindow(Simulator& sim);
	void renderNametableWindow(Simulator& sim);
	void renderPatternTableWindow(Simulator& sim);
	void renderPatternPixelsWindow(Simulator& sim);
	void renderPatternTextureWindow(Simulator& sim);
	void renderNametableGridWindow(Simulator& sim);

	struct MemoryViewState {
		uint16_t search_address = 0;
		float target_scroll = 0.0f;
		bool want_search = false;
	};
	void renderMemoryTable(const char* title, const char* table_id, uint16_t* data, int count, MemoryViewState& view);
	MemoryViewState nametable_view;

	std::string image_path;
	unsigned int screen_texture = 0;
	unsigned int framebuffer_texture = 0;
	unsigned int pattern_texture = 0;
	int screen_scale = 1;
	int render_mode = 1; // 0 = Image, 1 = Tilemap
	int pattern_tile_index = 0;

	// Helpers
	std::string readFile(std::string path);

};
