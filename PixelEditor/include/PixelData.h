#pragma once

#include <cstdint>

class PixelData
{
public:
	PixelData();

	uint8_t* getNametable() { return nametable; }
	uint16_t* getPatternTable() { return patternTable; }
	uint8_t* getPalette() { return palette; }

	bool exportHex(const char* directory);
	bool importHex(const char* directory);

private:
	uint8_t nametable[40 * 30] = {};      // 1200 entries, 8-bit (7-bit tile id + 1-bit palette sel)
	uint16_t patternTable[128 * 8] = {};  // 128 tiles x 8 rows of 16-bit (2bpp x 8px)
	uint8_t palette[8] = {};              // 8 entries of 3-bit RGB
};
