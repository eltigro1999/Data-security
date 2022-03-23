#pragma once
#include <fstream>
#include <vector>
#include <map>

class FileManager {
	std::ifstream File;
	long long FileSize = 0;
	std::vector<unsigned char> Bytes;
	std::map<unsigned char, double> RelativeFrequency;
	std::string filename;
public:
	FileManager(const std::string& filename);
	long long GetFileSize();
	std::vector<unsigned char> GetFileBytes();
	std::map<unsigned char, double> GetBytesRelativeFrequency();
};