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

				printf("Loaded image (%i, %i), channels = %i", width, height, channels);

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

std::string Window::readFile(std::string path) {
	std::ifstream file(path);

	if (!file)
		throw std::runtime_error("File not open");

	return std::string{ std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
}