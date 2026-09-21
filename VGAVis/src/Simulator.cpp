#include "Simulator.h"

#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>

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

	// Default palette: identity 3-bit RGB (palette[i] = i)
	for (int i = 0; i < 8; ++i) palette[i] = (uint8_t)i;
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

void Simulator::writeImageToFramebuffer(const uint8_t* image_data, int width, int height, int channels) {
	if (!image_data) return;

	int w = std::min(width, 320);
	int h = std::min(height, 240);

	// Working float buffer for error diffusion
	std::vector<float> buf((size_t)w * h * 3);

	// Copy source to float [0,1]
	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			int si = (y * width + x) * channels;
			int di = (y * w + x) * 3;
			buf[di + 0] = image_data[si + 0] / 255.0f;
			buf[di + 1] = image_data[si + 1] / 255.0f;
			buf[di + 2] = image_data[si + 2] / 255.0f;
		}
	}

	// Floyd-Steinberg error diffusion against palette[0..3] (4 colours, 2 bpp)
	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			int i = (y * w + x) * 3;
			float r = buf[i + 0], g = buf[i + 1], b = buf[i + 2];

			// Nearest palette colour
			int best = 0;
			float bestDist = 1e30f;
			for (int c = 0; c < 4; ++c) {
				float pr = (palette[c] & 0b100) ? 1.0f : 0.0f;
				float pg = (palette[c] & 0b010) ? 1.0f : 0.0f;
				float pb = (palette[c] & 0b001) ? 1.0f : 0.0f;
				float dr = r - pr, dg = g - pg, db = b - pb;
				float d = dr * dr + dg * dg + db * db;
				if (d < bestDist) { bestDist = d; best = c; }
			}

			float pr = (palette[best] & 0b100) ? 1.0f : 0.0f;
			float pg = (palette[best] & 0b010) ? 1.0f : 0.0f;
			float pb = (palette[best] & 0b001) ? 1.0f : 0.0f;
			float er = r - pr, eg = g - pg, eb = b - pb;

			// Store 2-bit colour index into the indexed framebuffer
			m_top->vga_controller->gfx_inst->framebuffer[y * 320 + x] = (uint8_t)best;

			auto diffuse = [&](int nx, int ny, float wgt) {
				if (nx < 0 || nx >= w || ny < 0 || ny >= h) return;
				int ni = (ny * w + nx) * 3;
				buf[ni + 0] += er * wgt;
				buf[ni + 1] += eg * wgt;
				buf[ni + 2] += eb * wgt;
			};
			diffuse(x + 1, y,     7.0f / 16.0f);
			diffuse(x - 1, y + 1, 3.0f / 16.0f);
			diffuse(x,     y + 1, 5.0f / 16.0f);
			diffuse(x + 1, y + 1, 1.0f / 16.0f);
		}
	}
}

const uint8_t* Simulator::getFramebuffer() const {
	return &(m_top->vga_controller->gfx_inst->framebuffer[0]);
}
