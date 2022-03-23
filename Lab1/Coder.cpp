#include "Coder.h"
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>
#include <iostream>


Coder::Coder() {
	std::ifstream KeyFile;
	KeyFile.open("key.txt");
	if (!KeyFile) {
		GenerateKey();
	}
	else {
		std::vector<int> EncodingNumbers;
		std::vector<int> DecodingNumbers;
		ReadExistingKey(KeyFile, EncodingNumbers);
		ReadExistingKey(KeyFile, DecodingNumbers);
		for (int i = 0; i < EncodingNumbers.size(); ++i) {
			encodingKey[EncodingNumbers[i]] = DecodingNumbers[i];
			decodingKey[DecodingNumbers[i]] = EncodingNumbers[i];
		}
	}
	KeyFile.close();
}

void Coder::GenerateKey() {
	if (!KeyGenerated) {
		std::ofstream KeyFile("key.txt");
		std::vector<int> Numbers(256);
		std::iota(std::begin(Numbers), std::end(Numbers), 0);
		auto Randomizer = std::default_random_engine{};
		std::vector<int> ShuffledNumbers(Numbers);
		std::shuffle(ShuffledNumbers.begin(), ShuffledNumbers.end(), Randomizer);
		if (KeyFile.is_open()) {
			WriteNumbersIntoFile(Numbers, KeyFile);
			KeyFile << "\n";
			WriteNumbersIntoFile(ShuffledNumbers, KeyFile);
		}
		for (size_t i = 0; i < Numbers.size(); ++i) {
			encodingKey[Numbers[i]] = ShuffledNumbers[i];
			decodingKey[ShuffledNumbers[i]] = Numbers[i];
		}
		KeyFile.close();
		KeyGenerated = true;
	}
	else {
		std::cout << "File not found" << std::endl;
	}
}

void Coder::WriteNumbersIntoFile(const std::vector<int>& Numbers, std::ofstream& File) {
	for (size_t i = 0; i < Numbers.size(); ++i) {
		File << Numbers[i];
		if (i != Numbers.size() - 1)
			File << " ";
	};
}

void Coder::Encode(const std::string& filename) {
	SubstituteBytes(filename, encodingKey);
}
void Coder::Decode(const std::string& filename) {
	SubstituteBytes(filename, decodingKey);
}

void Coder::SubstituteBytes(const std::string& filename, const std::map<unsigned char, unsigned char>& Key) {
	std::ifstream OriginalFile;
	OriginalFile.open(filename, std::ios::binary);
	if (OriginalFile) {
		OriginalFile.unsetf(std::ios::skipws);
		std::string CipheredfileName = std::string("Ciphered ") + filename;
		std::ofstream CipheredFile(CipheredfileName, std::ios::binary);
		OriginalFile.seekg(0, std::ios::end);
		long long OriginalFileSize = OriginalFile.tellg();
		OriginalFile.seekg(0, std::ios::beg);
		unsigned char c;
		for (long long i = 0; i < OriginalFileSize; ++i) {
			OriginalFile >> c;
			CipheredFile << Key.at(c);
		}
		OriginalFile.close();
		CipheredFile.close();
		bool deleted;
		deleted=std::remove(filename.c_str());
		if (deleted) {
			std::cout<<"Deleted"<<std::endl;
		}
		std::rename(CipheredfileName.c_str(), filename.c_str());
	}
}

void Coder::ReadExistingKey(std::ifstream& KeyFile, std::vector<int>& Numbers) {
	std::string strNumbers;
	std::getline(KeyFile, strNumbers);
	std::stringstream stream(strNumbers);
	Numbers.assign(std::istream_iterator<int>(stream), std::istream_iterator<int>());
}