#include "Simulator.h"

#include <iostream>
#include <memory>

#include "Vgraphics_engine.h"
#include "verilated.h"

// MSVC has no weak symbols, so Verilator's optional legacy time callback must
// be defined by the application. Without it, linking fails with
// LNK2019: unresolved external symbol "double __cdecl sc_time_stamp(void)".
double sc_time_stamp() {
	return 0;
}

Simulator::Simulator() {
	// Instantiate the Verilated module
	m_top = std::make_unique<Vgraphics_engine>();

	// Initialize inputs
	m_top->clk = 0;
	m_top->pixel_x = 0;
	m_top->pixel_y = 0;
	m_top->video_on = 1;

	// Settle the model once so outputs are valid before the first frame
	m_top->eval();

	std::cout << "SUCCESS: Verilated graphics_engine linked and evaluated cleanly!" << std::endl;
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
}

void Simulator::setPixel(unsigned short x, unsigned short y, bool videoOn) {
	m_top->pixel_x = x;
	m_top->pixel_y = y;
	m_top->video_on = videoOn ? 1 : 0;
}

unsigned char Simulator::getRgb() const {
	return m_top->rgb;
}
