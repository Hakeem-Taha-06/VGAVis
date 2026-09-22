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

	void setMode(bool spriteMode);

	inline const float* getScreen() const { return screen; }
	const uint8_t* getFramebuffer() const;

	uint8_t* getNametable();
	uint16_t* getPatternTable();
	uint8_t* getPalette();

	bool loadHexFiles(const char* directory);

	void writeImageToFramebuffer(const uint8_t* image_data, int width, int height, int channels);

private:
	// Verilated model; forward declared above, only included in Simulator.cpp
	std::unique_ptr<Vvga_controller> m_top;

	// 640 * 480 with 3 color channels
	float screen[640 * 480 * 3];

};
