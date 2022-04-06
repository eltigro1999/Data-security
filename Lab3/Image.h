#pragma once
#include <string>
#include <Windows.h>
#include <vector>
#include <fstream>

class Image {
	std::string FileName;
	BITMAPINFOHEADER HeaderInfo;
	BITMAPFILEHEADER Header;
	RGBQUAD pixel;
	void hide_byte_into_pixel(RGBQUAD& pixel, uint8_t hide_byte);
	uint8_t convert_pixel_to_a_text_byte(const RGBQUAD& pixel);
	template<typename T>
	void Read(std::ifstream& File, T& object) {
		File.read(reinterpret_cast<char*>(&object), sizeof(object));
	}
	template<typename T>
	void Write(std::ofstream& File, T& object) {
		File.write(reinterpret_cast<char*>(&object), sizeof(object));
	}

public:
	Image(const std::string& FileName_);
	void Decode();
	void Encode();

};