#include "Simulator.h"

#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

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
	m_top->mode_select = 0;

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

void Simulator::setMode(bool spriteMode) {
	m_top->mode_select = spriteMode ? 1 : 0;
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

	// Floyd-Steinberg error diffusion to 3-bit direct RGB (8 colours)
	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			int i = (y * w + x) * 3;
			float r = buf[i + 0], g = buf[i + 1], b = buf[i + 2];

			// Quantize each channel independently to 1 bit (3-bit direct RGB, 8 colours)
			int r_bit = (r >= 0.5f) ? 1 : 0;
			int g_bit = (g >= 0.5f) ? 1 : 0;
			int b_bit = (b >= 0.5f) ? 1 : 0;

			float pr = (float)r_bit, pg = (float)g_bit, pb = (float)b_bit;
			float er = r - pr, eg = g - pg, eb = b - pb;

			// Pack into 3-bit direct RGB (R=bit2, G=bit1, B=bit0)
			uint8_t color_val = (uint8_t)((r_bit << 2) | (g_bit << 1) | b_bit);
			m_top->vga_controller->gfx_inst->framebuffer[y * 320 + x] = color_val;

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

static std::string joinPath(const std::string& dir, const char* name) {
	std::string d = dir;
	if (!d.empty() && d.back() != '\\' && d.back() != '/') d += '\\';
	return d + name;
}

template <typename T>
static bool readHexFile(const std::string& path, T* data, int count) {
	std::ifstream in(path);
	if (!in) return false;
	for (int i = 0; i < count; ++i) {
		std::string line;
		if (!std::getline(in, line)) return false;
		size_t comment = line.find("//");
		if (comment != std::string::npos) line = line.substr(0, comment);
		std::stringstream ss(line);
		unsigned int v;
		if (!(ss >> std::hex >> v)) return false;
		data[i] = (T)v;
	}
	return true;
}

uint8_t* Simulator::getNametable() {
	return &m_top->vga_controller->gfx_inst->nametable[0];
}

uint16_t* Simulator::getPatternTable() {
	return &m_top->vga_controller->gfx_inst->pattern_table[0];
}

uint8_t* Simulator::getPalette() {
	return &m_top->vga_controller->gfx_inst->palette_mem[0];
}

bool Simulator::loadHexFiles(const char* directory) {
	std::string dir = directory ? directory : "";
	if (!readHexFile(joinPath(dir, "nametable.hex"), getNametable(), 40 * 30)) return false;
	if (!readHexFile(joinPath(dir, "pattern_table.hex"), getPatternTable(), 128 * 8)) return false;

	std::ifstream in(joinPath(dir, "palette.hex"));
	if (!in) return false;
	uint8_t* pal = getPalette();
	for (int i = 0; i < 8; ++i) {
		std::string line;
		if (!std::getline(in, line)) return false;
		size_t comment = line.find("//");
		if (comment != std::string::npos) line = line.substr(0, comment);
		std::stringstream ss(line);
		unsigned int v;
		if (!(ss >> std::hex >> v)) return false;
		pal[i] = (uint8_t)v;
	}
	return true;
}
const uint8_t* Simulator::getFramebuffer() const {
	return &(m_top->vga_controller->gfx_inst->framebuffer[0]);
}
