#pragma once

#include <memory>
#include <cstdint>

class Vvga_controller;

class Simulator
{
public:
	Simulator();
	~Simulator();

	// Called by Application once per frame.
	// Advances the Verilated model by one full clock cycle.
	void Update();

	// 3-bit RGB output of the model for the current pixel
	uint8_t getRgb() const;

	inline const float* getScreen() const { return screen; }
	const uint8_t* getFramebuffer() const;

	uint16_t* getNametable() { return nametable; }
	uint16_t* getPatternTable() { return patternTable; }
	const uint8_t* getPalette() const { return palette; }

	void writeImageToFramebuffer(const uint8_t* image_data, int width, int height, int channels);

private:
	// Verilated model; forward declared above, only included in Simulator.cpp
	std::unique_ptr<Vvga_controller> m_top;

	// 640 * 480 with 3 color channels
	float screen[640 * 480 * 3];

	// Tilemap golden-model memory (Section 2 layout)
	uint16_t nametable[40 * 30] = {};      // 1200 entries, 12-bit (tile id + palette sel)
	uint16_t patternTable[1200 * 8] = {};  // 1200 tiles x 8 rows of 16-bit (2bpp x 8px)
	uint8_t palette[8] = {};               // 8 entries of 3-bit RGB
};
