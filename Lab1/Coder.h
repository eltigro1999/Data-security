#pragma once
#include <map>
#include <fstream>
#include <vector>
#include <string>

class Coder {
	std::map<unsigned char, unsigned char> encodingKey;
	std::map<unsigned char, unsigned char> decodingKey;
	bool KeyGenerated = false;
	void WriteNumbersIntoFile(const std::vector<int>&, std::ofstream&);
	void GenerateKey();
	void SubstituteBytes(const std::string& filename, const std::map<unsigned char, unsigned char>& Key);
	void ReadExistingKey(std::ifstream& KeyFile, std::vector<int>& Numbers);
public:
	Coder();
	void Encode(const std::string& filename);
	void Decode(const std::string& filename);


};