#include <string>
#include <iostream>
#include <fstream>
#include <map>

std::string FilePath = "C:\\Users\\eltig\\OneDrive\\Рабочий стол\\Пришел, увидел, победил.docx";
long long task1(char*& Bytes);
long long task2(char*& Bytes, const int& FileSize);


int main() {
	char* Bytes=nullptr;
	long long FileSize=task1(Bytes);
	int RelativeFrequency=task2(Bytes, FileSize);
	delete[] Bytes;
}

long long task1(char*& Bytes) {
	std::ifstream File(FilePath);
	long long FileSize=0;
	if (File.is_open()) {
		File.seekg(0, std::ios::end);
		FileSize = File.tellg();
		File.seekg(0, std::ios::beg);
		std::cout << "Size of the file in bytes is" << " " << FileSize << "."<<std::endl;
	}
	Bytes = new char[FileSize];
	File.read(Bytes, FileSize);
	return FileSize;
}

long long task2(char*& Bytes, const int& FileSize) {
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