#pragma once

#include <memory>
#include <cstdint>

class Vgraphics_engine;
class Vgraphics_engine_graphics_engine;

class Simulator
{
public:
	Simulator();
	~Simulator();

	// Called by Application once per frame.
	// Advances the Verilated model by one full clock cycle.
	void Update();

	// Drive the model inputs (scan coordinates + video enable)
	void setPixel(uint16_t x, uint16_t y, bool videoOn);

	// 3-bit RGB output of the model for the current pixel
	uint8_t getRgb() const;

	inline const float* getScreen() const { return screen; }

	void writeImageToFramebuffer(const uint8_t* image_data, int width, int height, int channels);

private:
	// Verilated model; forward declared above, only included in Simulator.cpp
	std::unique_ptr<Vgraphics_engine> m_top;
	std::unique_ptr<Vgraphics_engine_graphics_engine> m_graphics_engine;

	// 640 * 480 with 3 color channels
	float screen[640 * 480 * 3];
};
