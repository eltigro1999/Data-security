#pragma once
#include <string>
#include <fstream>
#include <map>
#include "RSA.h"

class FileManager {
	std::fstream File;
	std::string Filename;
	RSA rsa{7, 13};

public:
	FileManager(const std::string& Filename);
	std::string Read();
	void Write(const std::string& Str);
	void Encode();
	void Decode();
};