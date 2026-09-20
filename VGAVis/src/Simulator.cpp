#include "Simulator.h"

#include <iostream>
#include <memory>

#include "Vvga_controller.h"
#include "Vvga_controller_vga_controller.h"
#include "Vvga_controller_graphics_engine.h"
#include "verilated.h"

// MSVC has no weak symbols, so Verilator's optional legacy time callback must
// be defined by the application. Without it, linking fails with
// LNK2019: unresolved external symbol "double __cdecl sc_time_stamp(void)".
double sc_time_stamp() {
	return 0;
}

Simulator::Simulator() {
	// Instantiate the Verilated module
	m_top = std::make_unique<Vvga_controller>();

	// Initialize inputs
	m_top->clk = 0;
	m_top->rst = 0;

	// Settle the model once so outputs are valid before the first frame
	m_top->eval();

	std::cout << "SUCCESS: Verilated vga_controller linked and evaluated cleanly!" << std::endl;
	std::cout << "Initial RGB output: 0x" << std::hex << static_cast<int>(m_top->rgb) << std::dec << std::endl;
}

Simulator::~Simulator() {
	if (m_top) {
		m_top->final();
	}
}

void Simulator::Update() {
	// Run one clock cycle: Low -> High
	m_top->clk = 0;
	m_top->eval();

	m_top->clk = 1;
	m_top->eval();

	// Capture rendered pixel during active video
	if (m_top->vga_controller->video_on) {
		int out_idx = (m_top->vga_controller->pixel_y * 640 + m_top->vga_controller->pixel_x) * 3;
		// Expand 3-bit RGB (R=bit 2, G=bit 1, B=bit 0) to 8-bit channels
		screen[out_idx + 0] = (m_top->rgb & 0b100) ? 1.0f : 0.0f; // Red
		screen[out_idx + 1] = (m_top->rgb & 0b010) ? 1.0f : 0.0f; // Green
		screen[out_idx + 2] = (m_top->rgb & 0b001) ? 1.0f : 0.0f; // Blue
	}
}

uint8_t Simulator::getRgb() const {
	return m_top->rgb;
}

void Simulator::writeImageToFramebuffer(const uint8_t* image_data, int width, int height, int channels, int limit) {
	if (!image_data) return;

	// Crop to the 320x240 limit (or smaller if the image is tiny)
	int crop_width = std::min(width, 320);
	int crop_height = std::min(height, 240);

	for (int y = 0; y < crop_height; ++y) {
		for (int x = 0; x < crop_width; ++x) {

			// Calculate the starting byte index of the current pixel in your source image
			int src_index = (y * width + x) * channels;

			uint8_t r = image_data[src_index + 0];
			uint8_t g = image_data[src_index + 1];
			uint8_t b = image_data[src_index + 2];

			// Quantize each channel: 1 if >= 128, else 0
			uint8_t r_bit = (r >= limit) ? 1 : 0;
			uint8_t g_bit = (g >= limit) ? 1 : 0;
			uint8_t b_bit = (b >= limit) ? 1 : 0;

			// Pack into 3-bit color (R=bit 2, G=bit 1, B=bit 0)
			uint8_t color_val = (r_bit << 2) | (g_bit << 1) | b_bit;

			// Write directly into the Verilated module's public memory array
			int dest_index = y * 320 + x;
			m_top->vga_controller->gfx_inst->framebuffer[dest_index] = color_val;
		}
	}
}

const uint8_t* Simulator::getFramebuffer() const {
	return &(m_top->vga_controller->gfx_inst->framebuffer[0]);
}
