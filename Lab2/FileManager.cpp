#include "FileManager.h"
#include <iostream>

FileManager::FileManager(const std::string& Filename_) {
	Filename = Filename_;
}

std::string FileManager::Read() {
	File.open(Filename, std::ios::in);
	std::string Text;
	if (File.is_open()) {
		std::getline(File, Text);
		File.close();
	} else {
		std::cout << "File "<<Filename<<" has not been opened." << std::endl;
	}
	return Text;
}

void FileManager::Write(const std::string& Str) {
	File.open(Filename, std::ios::out);
	if (File.is_open()) {
		File << Str;
		File.close();
	}
	else {
		std::cout << "File " << Filename << " has not been opened." << std::endl;
	}
}

void FileManager::Encode() {
	std::ofstream EncodedFile("Encoded "+Filename);
	if (EncodedFile.is_open()) {
		std::string Text = Read();
		std::string EncodedText = rsa.Encode(Text);
		EncodedFile << EncodedText;
		EncodedFile.close();
	}
	else {
		std::cout << "Encoded file " << "Encoded "+Filename << " has not been opened." << std::endl;
	}
}

void FileManager::Decode() {
	std::ofstream DecodedFile("Decoded " + Filename);
	if (DecodedFile.is_open()) {
		FileManager fm("Encoded "+Filename);
		std::string Text = fm.Read();
		std::string DecodedText = rsa.Decode(Text);
		DecodedFile << DecodedText;
		DecodedFile.close();
	}
	else {
		std::cout << "Decoded file " << "Decoded " + Filename << " has not been opened." << std::endl;
	}
}