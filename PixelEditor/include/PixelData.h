#pragma once

#include <cstdint>

class PixelData
{
public:
	PixelData();

	uint16_t* getNametable() { return nametable; }
	uint16_t* getPatternTable() { return patternTable; }
	const uint8_t* getPalette() const { return palette; }

	bool exportHex(const char* directory);
	bool importHex(const char* directory);

private:
	uint16_t nametable[40 * 30] = {};      // 1200 entries, 12-bit (tile id + palette sel)
	uint16_t patternTable[1200 * 8] = {};  // 1200 tiles x 8 rows of 16-bit (2bpp x 8px)
	uint8_t palette[8] = {};               // 8 entries of 3-bit RGB
};
