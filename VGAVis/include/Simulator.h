#pragma once

#include <memory>

class Vgraphics_engine;

class Simulator
{
public:
	Simulator();
	~Simulator();

	// Called by Application once per frame.
	// Advances the Verilated model by one full clock cycle.
	void Update();

	// Drive the model inputs (scan coordinates + video enable)
	void setPixel(unsigned short x, unsigned short y, bool videoOn);

	// 3-bit RGB output of the model for the current pixel
	unsigned char getRgb() const;

private:
	// Verilated model; forward declared above, only included in Simulator.cpp
	std::unique_ptr<Vgraphics_engine> m_top;
};
