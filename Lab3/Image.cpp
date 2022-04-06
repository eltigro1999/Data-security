#include "Image.h"
#include <fstream>
#include <iostream>

Image::Image(const std::string& FileName_) {
	FileName = FileName_;
}

void Image::Decode() {
	std::ifstream bmpFile;
	bmpFile.open("Encoded "+FileName, std::ios::in | std::ios::binary);
	std::ofstream decodedFile;
	decodedFile.open("Decoded.txt", std::ios::out | std::ios::binary);
	if (bmpFile.is_open() && decodedFile.is_open()) {
		Read(bmpFile, Header);
		Read(bmpFile, HeaderInfo);
		while (!bmpFile.eof()) {
			Read(bmpFile, pixel);
			uint8_t byte=convert_pixel_to_a_text_byte(pixel);
			if (byte == 0xDB) break;
			Write(decodedFile, byte);
		}
		bmpFile.close();
		decodedFile.close();
	}
}

void Image::Encode() {
	std::ifstream bmpFile(FileName, std::ios::in | std::ios::binary);
	std::ifstream FileToEncode("Text to encode.txt", std::ios::in | std::ios::binary);
	std::ofstream EncodedBmpFile("Encoded " + FileName, std::ios::out | std::ios::binary);
	if (bmpFile.is_open() && FileToEncode.is_open()) {
		Read(bmpFile, Header);
		Write(EncodedBmpFile, Header);
		Read(bmpFile, HeaderInfo);
		Write(EncodedBmpFile, HeaderInfo);
		uint8_t byte;
		while (!bmpFile.eof()) {
			Read(bmpFile, pixel);
			Read(FileToEncode, byte);
			if (FileToEncode.eof()) {
				byte = 0xDB;
			}
			hide_byte_into_pixel(pixel, byte);
			Write(EncodedBmpFile, pixel);
		}
		EncodedBmpFile.close();
		bmpFile.close();
		FileToEncode.close();
	}
}

uint8_t Image::convert_pixel_to_a_text_byte(const RGBQUAD& pixel) {
	uint8_t byte=0;
	byte |= (pixel.rgbBlue&0x3);
	byte <<= 2;
	byte |= (pixel.rgbGreen & 0x3);
	byte <<= 2;
	byte |= (pixel.rgbRed & 0x3);
	byte <<= 2;
	byte |= (pixel.rgbReserved & 0x3);
	return byte;
}


void Image::hide_byte_into_pixel(RGBQUAD& pixel, uint8_t hide_byte) {
	pixel.rgbBlue &= (0xFC);
	pixel.rgbBlue |= (hide_byte >> 6) & 0x3;
	pixel.rgbGreen &= (0xFC);
	pixel.rgbGreen |= (hide_byte >> 4) & 0x3;
	pixel.rgbRed &= (0xFC);
	pixel.rgbRed |= (hide_byte >> 2) & 0x3;
	pixel.rgbReserved &= (0xFC);
	pixel.rgbReserved |= (hide_byte) & 0x3;
}