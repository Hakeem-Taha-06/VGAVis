#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_stdlib.h>

#include "tinyfiledialogs.h"

#include "InputManager.h"
#include "Shader.h"

#include <iostream>
#include <memory>
#include <string>
#include <cstdint>

class PixelData;

class Window
{
public:
	Window(int width, int height);
	~Window();

	inline bool shouldExit() const { return glfwWindowShouldClose(m_window); }

	void startFrame();
	void render(PixelData& data);
	void endFrame();

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
	void renderFileWindow(PixelData& data);
	void renderNametableWindow(PixelData& data);
	void renderPatternTableWindow(PixelData& data);
	void renderPatternPixelsWindow(PixelData& data);
	void renderPaletteWindow(PixelData& data);
	void renderPatternTextureWindow(PixelData& data);
	void renderNametableTextureWindow(PixelData& data);

	struct MemoryViewState {
		uint16_t search_address = 0;
		float target_scroll = 0.0f;
		bool want_search = false;
	};
	void renderMemoryTable(const char* title, const char* table_id, uint8_t* data, int count, MemoryViewState& view);
	MemoryViewState nametable_view;

	unsigned int pattern_texture = 0;
	unsigned int nametable_texture = 0;
	int pattern_tile_index = 0;
};
