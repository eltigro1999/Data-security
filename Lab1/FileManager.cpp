#include "FileManager.h"
#include <string>

FileManager::FileManager(const std::string& filename) {
	this->filename = filename;
	File.open(filename, std::ios::binary);
	File.unsetf(std::ios::skipws);
	if (File.is_open()) {
		File.seekg(0, std::ios::end);
		FileSize = File.tellg();
		File.seekg(0, std::ios::beg);
		//std::cout << "Size of the file in bytes is" << " " << FileSize << "." << std::endl;
	}
	Bytes.reserve(FileSize);
	Bytes.insert(Bytes.begin(),
		std::istream_iterator<char>(File),
		std::istream_iterator<char>());
	File.close();
}

long long FileManager::GetFileSize() {
	return FileSize;
}

std::vector<unsigned char> FileManager::GetFileBytes() {
	return Bytes;
}

std::map<unsigned char, double> FileManager::GetBytesRelativeFrequency() {
	for (int i = 0; i < FileSize; ++i) {
		RelativeFrequency[Bytes[i]]++;
	}
	for (auto& pair : RelativeFrequency) {
		pair.second=pair.second/RelativeFrequency.size();
	}
	return RelativeFrequency;
}
