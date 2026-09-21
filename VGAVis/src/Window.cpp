#include "Window.h"
#include "Simulator.h"

Window::Window(int width, int height) : WIDTH(width), HEIGHT(height), inputManager(){
	init();
}

Window::~Window() {

}

void Window::init() {
	if (!glfwInit()) {
		std::cerr << "glfw not initialized";
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor()); // Valid on GLFW 3.3+ only
	GLFWwindow* w = glfwCreateWindow(WIDTH, HEIGHT, "VGAVis", nullptr, nullptr);
	if (w == nullptr) {
		std::cout << "Failed to create window";

		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(w);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD";
		exit(EXIT_FAILURE);
	}

	std::cout << "GPU: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "GL Version: " << glGetString(GL_VERSION) << std::endl;

	glViewport(0, 0, WIDTH, HEIGHT);

	//glfwSetKeyCallback(w, Window::keyEventCallback);
	//setGLFWEventCallbacks(w);

	// Setup Dear ImGui context 
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Control
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

	ImGui::StyleColorsDark();                                 // Configure Style Color
	// Setup scaling
	ImGuiStyle& style = ImGui::GetStyle();
	style.ScaleAllSizes(main_scale);                          // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
	style.FontScaleDpi = main_scale;                          // Set initial font scale. (in docking branch: using io.ConfigDpiScaleFonts=true automatically overrides this for every window depending on the current monitor)
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
	io.ConfigDpiScaleFonts = true;                            // [Experimental] Automatically overwrite style.FontScaleDpi in Begin() when Monitor DPI changes. This will scale fonts but _NOT_ scale sizes/padding for now.
	io.ConfigDpiScaleViewports = true;                        // [Experimental] Scale Dear ImGui and Platform Windows when Monitor DPI changes.
#endif

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}
	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(w, true);                    // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init("#version 330");

	m_window = w;

	// triangle drawing test
	shader = std::make_unique<Shader>(vshader_src, fshader_src);

	float vertices[] = 
	{
		 0.5f, 1.0f, 1.0f,
		-1.0f, 0.0f, 1.0f,
		 1.0f, 0.0f, 1.0f
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

}

void Window::startFrame() {
	glfwPollEvents();

	// Start the Dear ImGui frame 
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Window::render(Simulator& sim) {
	//rendering
	// Create a dockspace that covers the entire viewport
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport()->ID, ImGui::GetMainViewport());

	renderControlWindow(sim);
	renderScreenWindow(sim);
	renderFramebufferWindow(sim);
	renderNametableWindow(sim);
	renderPatternTableWindow(sim);
	renderPatternPixelsWindow(sim);
	renderPatternTextureWindow(sim);
	renderNametableGridWindow(sim);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Window::endFrame() {
	ImGui::EndFrame();

	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}

	glfwSwapBuffers(m_window);
}

void Window::renderControlWindow(Simulator& sim) {
	ImGui::Begin("Control Window");
	ImGui::PushItemWidth(200.0f);
	ImGui::Text("Image File Path");
	ImGui::InputText("##imagefilepath", &image_path); 
	ImGui::PopItemWidth();
	ImGui::SameLine();
	if (ImGui::Button("Browse")) 
	{
		const char* filterPatters[] = {"*.png", "*.jpg", "*.jpeg"};
		const char* path = tinyfd_openFileDialog(
			"Choose image file",
			"",
			3,
			filterPatters,
			".png, .jpeg, .jpg",
			0
		);
		if (path)
			image_path = path;
	}
	
	if (ImGui::Button("Load image into framebuffer")) {
		int width, height, channels;
		uint8_t* image_data = stbi_load(image_path.c_str(), &width, &height, &channels, 4);

		if (!image_data) {
			printf("stbi_load failed: %s\n", stbi_failure_reason());
		}
		else{
			int out_w = 320, out_h = 240;
			unsigned char* resized_image_data = (unsigned char*)malloc(out_w * out_h * 4);

			if (!resized_image_data) {
				std::cout << "malloc failed when resizing image data" << '\n';
			}
			else {

				printf("Loaded image (%i, %i), channels = %i\n", width, height, channels);

				stbir_resize_uint8_linear(
					image_data, width, height, 0,            // src pixels, src w/h, src stride (0 = tightly packed)
					resized_image_data, out_w, out_h, 0,     // dst pixels, dst w/h, dst stride (0 = tightly packed)
					STBIR_RGBA
				);

				sim.writeImageToFramebuffer(resized_image_data, out_w, out_h, 4);
				frame_ready = true;
				stbi_image_free(image_data);
				free(resized_image_data);
			}
		}
	}

	ImGui::InputInt("Simulation Speed", &sim_speed);

	const char* modes[] = { "Image", "Tilemap" };
	ImGui::Combo("Render Mode", &render_mode, modes, 2);

	ImGui::End();
}

void Window::renderScreenWindow(Simulator& sim) {
	ImGui::Begin("Screen");

	if (screen_texture == 0)
		glGenTextures(1, &screen_texture);

	glBindTexture(GL_TEXTURE_2D, screen_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 640, 480, 0, GL_RGB, GL_FLOAT, sim.getScreen());

	ImTextureID imTexture = (ImTextureID)(intptr_t)screen_texture;
	ImGui::GetWindowDrawList()->AddCallback(ImGui::GetPlatformIO().DrawCallback_SetSamplerNearest, nullptr);
	ImGui::Image(imTexture, ImVec2((float)(640 * screen_scale), (float)(480 * screen_scale)));
	ImGui::GetWindowDrawList()->AddCallback(ImGui::GetPlatformIO().DrawCallback_SetSamplerLinear, nullptr);

	glBindTexture(GL_TEXTURE_2D, 0);

	ImGui::End();
}

void Window::renderFramebufferWindow(Simulator& sim) {
	ImGui::Begin("Framebuffer");
	auto framebuffer = sim.getFramebuffer();

	// Framebuffer is 320x240, 3-bit RGB per pixel (R=bit2, G=bit1, B=bit0).
	// Allocate the conversion buffer on the heap (320*240*3 floats) and expand
	// each 3-bit colour to float RGB for OpenGL.
	auto framebuffer_screen = std::make_unique<float[]>(320 * 240 * 3);

	for (int y = 0; y < 240; y++) {
		for (int x = 0; x < 320; x++) {
			uint8_t color = framebuffer[y * 320 + x];
			int out_idx = (y * 320 + x) * 3;
			framebuffer_screen[out_idx + 0] = (color & 0b100) ? 1.0f : 0.0f; // Red
			framebuffer_screen[out_idx + 1] = (color & 0b010) ? 1.0f : 0.0f; // Green
			framebuffer_screen[out_idx + 2] = (color & 0b001) ? 1.0f : 0.0f; // Blue
		}
	}

	if (framebuffer_texture == 0)
		glGenTextures(1, &framebuffer_texture);

	glBindTexture(GL_TEXTURE_2D, framebuffer_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 320, 240, 0, GL_RGB, GL_FLOAT, framebuffer_screen.get());

	ImTextureID imTexture = (ImTextureID)(intptr_t)framebuffer_texture;
	ImGui::GetWindowDrawList()->AddCallback(ImGui::GetPlatformIO().DrawCallback_SetSamplerNearest, nullptr);
	ImGui::Image(imTexture, ImVec2((float)(320 * screen_scale), (float)(240 * screen_scale)));
	ImGui::GetWindowDrawList()->AddCallback(ImGui::GetPlatformIO().DrawCallback_SetSamplerLinear, nullptr);

	glBindTexture(GL_TEXTURE_2D, 0);

	ImGui::End();
}

void Window::renderMemoryTable(const char* title, const char* table_id, uint16_t* data, int count, MemoryViewState& view) {
	ImGui::Begin(title);

	int numCols = 16;
	int numRows = count / numCols;
	ImGuiTableFlags flags = ImGuiTableFlags_BordersOuter | ImGuiTableFlags_ScrollY | ImGuiTableFlags_RowBg;

	// Memory address search
	bool wantSearch = false;
	ImGui::Text("Search Address");
	ImGui::InputScalar("##address", ImGuiDataType_U16, &view.search_address, nullptr, nullptr, "%04X", ImGuiInputTextFlags_CharsHexadecimal);
	ImGui::SameLine();
	if (ImGui::Button("GOTO") && !wantSearch) {
		wantSearch = true;
		int searchRow = view.search_address / numCols;
		ImGuiStyle& style = ImGui::GetStyle();
		float rowHeight = ImGui::GetTextLineHeight() + style.CellPadding.y * 2.0f;
		view.target_scroll = searchRow * rowHeight;
	}

	if (ImGui::BeginTable(table_id, numCols + 1, flags)) {

		// set fixed width for columns
		ImGui::TableSetupColumn("Offset", ImGuiTableColumnFlags_WidthFixed, 60.0f);
		for (int i = 0; i < numCols; i++) {
			ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 48.0f);
		}

		if (wantSearch) {
			ImGui::SetScrollY(view.target_scroll);
			wantSearch = false;
		}

		ImGuiListClipper clipper;
		clipper.Begin(numRows);

		while (clipper.Step()) {
			for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; ++row) {
				ImGui::TableNextRow();

				ImGui::TableSetColumnIndex(0);
				ImGui::Text("%04X", row * numCols);

				for (int col = 0; col < numCols; ++col) {
					ImGui::TableSetColumnIndex(col + 1);

					int byteIdx = row * numCols + col;
					ImGui::PushID(byteIdx);
					ImGui::PushItemWidth(-FLT_MIN);

					ImGui::InputScalar("##cell", ImGuiDataType_U16, &data[byteIdx], nullptr, nullptr, "%04X", ImGuiInputTextFlags_CharsHexadecimal);

					ImGui::PopItemWidth();
					ImGui::PopID();
				}
			}
		}

		ImGui::EndTable();
	}
	ImGui::End();
}

void Window::renderNametableWindow(Simulator& sim) {
	renderMemoryTable("Nametable", "nametable_tbl", sim.getNametable(), 40 * 30, nametable_view);
}

void Window::renderPatternTableWindow(Simulator& sim) {
	ImGui::Begin("Pattern Table");
	uint16_t* patterns = sim.getPatternTable();

	const int numCols = 8;         // 8 tiles side by side
	const int rowsPerTile = 8;     // 8 scanlines per tile
	const int numMajorRows = 1200 / numCols; // 150 groups of 8 tiles

	ImGuiTableFlags flags = ImGuiTableFlags_BordersOuter | ImGuiTableFlags_RowBg;

	ImGuiListClipper clipper;
	clipper.Begin(numMajorRows);
	while (clipper.Step()) {
		for (int major = clipper.DisplayStart; major < clipper.DisplayEnd; ++major) {
			int baseTile = major * numCols;

			ImGui::Text("Tiles %04d - %04d", baseTile, baseTile + numCols - 1);

			if (ImGui::BeginTable("pt_rows", numCols + 1, flags)) {
				ImGui::TableSetupColumn("Row", ImGuiTableColumnFlags_WidthFixed, 40.0f);
				for (int c = 0; c < numCols; c++) {
					ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 52.0f);
				}

				for (int row = 0; row < rowsPerTile; ++row) {
					ImGui::TableNextRow();

					ImGui::TableSetColumnIndex(0);
					ImGui::Text("%d", row);

					for (int c = 0; c < numCols; ++c) {
						ImGui::TableSetColumnIndex(c + 1);

						int idx = (baseTile + c) * rowsPerTile + row;
						ImGui::PushID(idx);
						ImGui::PushItemWidth(-FLT_MIN);
						ImGui::InputScalar("##cell", ImGuiDataType_U16, &patterns[idx], nullptr, nullptr, "%04X", ImGuiInputTextFlags_CharsHexadecimal);
						ImGui::PopItemWidth();
						ImGui::PopID();
					}
				}
				ImGui::EndTable();
			}

			ImGui::Separator();
		}
	}

	ImGui::End();
}

void Window::renderPatternPixelsWindow(Simulator& sim) {
	ImGui::Begin("Pattern Pixels");
	uint16_t* patterns = sim.getPatternTable();

	ImGui::PushItemWidth(120.0f);
	ImGui::InputInt("Tile Index", &pattern_tile_index);
	ImGui::PopItemWidth();
	if (pattern_tile_index < 0) pattern_tile_index = 0;
	if (pattern_tile_index > 1199) pattern_tile_index = 1199;

	ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_SizingFixedFit;
	if (ImGui::BeginTable("pixgrid", 8, flags)) {
		for (int py = 0; py < 8; ++py) {
			ImGui::TableNextRow();

			uint16_t word = patterns[pattern_tile_index * 8 + py];
			for (int px = 0; px < 8; ++px) {
				ImGui::TableSetColumnIndex(px);

				int shift = px * 2;
				int val = (word >> shift) & 0x3;
				ImGui::PushID(py * 8 + px);
				ImGui::PushItemWidth(30);

				int tmp = val;
				if (ImGui::InputInt("##px", &tmp, 1, 1)) {
					if (tmp < 0) tmp = 0;
					if (tmp > 3) tmp = 3;
					word = (word & ~(0x3 << shift)) | ((uint16_t)tmp << shift);
					patterns[pattern_tile_index * 8 + py] = word;
				}

				ImGui::PopItemWidth();
				ImGui::PopID();
			}
		}
		ImGui::EndTable();
	}

	ImGui::End();
}

void Window::renderPatternTextureWindow(Simulator& sim) {
	ImGui::Begin("Pattern Texture");

	if (render_mode == 0) {
		// Image mode: pattern table unused, show nothing but keep texture contents
		ImGui::End();
		return;
	}

	if (pattern_texture == 0)
		glGenTextures(1, &pattern_texture);

	uint16_t* patterns = sim.getPatternTable();
	const uint8_t* palette = sim.getPalette();

	// 1200 tiles in a 40x30 grid, each 8x8 px -> 320x240 texture
	auto tex = std::make_unique<float[]>(320 * 240 * 3);

	for (int ty = 0; ty < 30; ++ty) {
		for (int tx = 0; tx < 40; ++tx) {
			int tile = ty * 40 + tx;
			for (int py = 0; py < 8; ++py) {
				uint16_t word = patterns[tile * 8 + py];
				for (int px = 0; px < 8; ++px) {
					int idx = (word >> (px * 2)) & 0x3;
					uint8_t color = palette[idx];
					int oi = ((ty * 8 + py) * 320 + (tx * 8 + px)) * 3;
					tex[oi + 0] = (color & 0b100) ? 1.0f : 0.0f; // Red
					tex[oi + 1] = (color & 0b010) ? 1.0f : 0.0f; // Green
					tex[oi + 2] = (color & 0b001) ? 1.0f : 0.0f; // Blue
				}
			}
		}
	}

	glBindTexture(GL_TEXTURE_2D, pattern_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 320, 240, 0, GL_RGB, GL_FLOAT, tex.get());

	ImTextureID imTexture = (ImTextureID)(intptr_t)pattern_texture;
	ImGui::GetWindowDrawList()->AddCallback(ImGui::GetPlatformIO().DrawCallback_SetSamplerNearest, nullptr);
	ImGui::Image(imTexture, ImVec2((float)(320 * screen_scale), (float)(240 * screen_scale)));
	ImGui::GetWindowDrawList()->AddCallback(ImGui::GetPlatformIO().DrawCallback_SetSamplerLinear, nullptr);

	glBindTexture(GL_TEXTURE_2D, 0);

	ImGui::End();
}

void Window::renderNametableGridWindow(Simulator& sim) {
	ImGui::Begin("Nametable Grid");
	uint16_t* nt = sim.getNametable();

	if (ImGui::BeginTable("ntgrid", 40, ImGuiTableFlags_Borders | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_ScrollY)) {
		for (int y = 0; y < 30; ++y) {
			ImGui::TableNextRow();
			for (int x = 0; x < 40; ++x) {
				ImGui::TableSetColumnIndex(x);
				ImGui::Text("%03X", nt[y * 40 + x]);
			}
		}
		ImGui::EndTable();
	}

	ImGui::End();
}

std::string Window::readFile(std::string path) {
	std::ifstream file(path);

	if (!file)
		throw std::runtime_error("File not open");

	return std::string{ std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
}
