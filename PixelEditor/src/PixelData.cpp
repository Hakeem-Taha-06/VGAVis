#include "PixelData.h"

#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

PixelData::PixelData() {
	// Default palette: identity 3-bit RGB (palette[i] = i)
	for (int i = 0; i < 8; ++i) palette[i] = (uint8_t)i;
}

static std::string joinPath(const std::string& dir, const char* name) {
	std::string d = dir;
	if (!d.empty() && d.back() != '\\' && d.back() != '/') d += '\\';
	return d + name;
}

static bool writeHexFile(const std::string& path, const uint16_t* data, int count, int digits) {
	std::ofstream out(path);
	if (!out) return false;
	for (int i = 0; i < count; ++i) {
		out << std::uppercase << std::hex << std::setw(digits) << std::setfill('0') << data[i] << '\n';
	}
	return out.good();
}

static bool readHexFile(const std::string& path, uint16_t* data, int count) {
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
		data[i] = (uint16_t)v;
	}
	return true;
}

bool PixelData::exportHex(const char* directory) {
	std::string dir = directory ? directory : "";
	if (!writeHexFile(joinPath(dir, "nametable.hex"), nametable, 40 * 30, 3)) return false;
	if (!writeHexFile(joinPath(dir, "pattern.hex"), patternTable, 1200 * 8, 4)) return false;

	std::ofstream out(joinPath(dir, "palette.hex"));
	if (!out) return false;
	for (int i = 0; i < 8; ++i) {
		out << std::uppercase << std::hex << (int)palette[i] << '\n';
	}
	return out.good();
}

bool PixelData::importHex(const char* directory) {
	std::string dir = directory ? directory : "";
	if (!readHexFile(joinPath(dir, "nametable.hex"), nametable, 40 * 30)) return false;
	if (!readHexFile(joinPath(dir, "pattern.hex"), patternTable, 1200 * 8)) return false;

	std::ifstream in(joinPath(dir, "palette.hex"));
	if (!in) return false;
	for (int i = 0; i < 8; ++i) {
		std::string line;
		if (!std::getline(in, line)) return false;
		size_t comment = line.find("//");
		if (comment != std::string::npos) line = line.substr(0, comment);
		std::stringstream ss(line);
		unsigned int v;
		if (!(ss >> std::hex >> v)) return false;
		palette[i] = (uint8_t)v;
	}
	return true;
}
