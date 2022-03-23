#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "Coder.h"

std::string FilePath = "C:\\Users\\eltig\\OneDrive\\Рабочий стол\\Пришел, увидел, победил.docx";
long long task1(std::vector<char>& Bytes);
long long task2(std::vector<char>& Bytes, const int& FileSize);
void task3();

int main() {
	std::vector<char> Bytes;
	long long FileSize = task1(Bytes);
	long long RelativeFrequency=task2(Bytes, FileSize);
	task3();
}

long long task1(std::vector<char>& Bytes) {
	std::ifstream File(FilePath, std::ios::binary);
	File.unsetf(std::ios::skipws);
	long long FileSize=0;
	if (File.is_open()) {
		File.seekg(0, std::ios::end);
		FileSize = File.tellg();
		File.seekg(0, std::ios::beg);
		std::cout << "Size of the file in bytes is" << " " << FileSize << "."<<std::endl;
	}
	Bytes.reserve(FileSize);
	Bytes.insert(Bytes.begin(),
		std::istream_iterator<char>(File),
		std::istream_iterator<char>());
	File.close();
	return FileSize;
}

long long task2(std::vector<char>& Bytes, const int& FileSize) {
	std::map<char, long long> RelativeFrequency;
	for (int i = 0; i < FileSize; ++i) {
		RelativeFrequency[Bytes[i]]++;
	}
	std::cout << " Rlative Frequency of byte:" << std::endl;
	for (auto& pair : RelativeFrequency) {
		std::cout <<pair.first << " - " <<
			static_cast<double>(pair.second) / 
			static_cast<double>(RelativeFrequency.size())<<std::endl;
	}
	return 1;
}

void task3() {
	Coder coder;
	std::string filename = "Пришел, увидел, победил.docx";
	coder.Encode(filename);
	coder.Decode(filename);

	
}