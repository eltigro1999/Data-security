#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "Coder.h"
#include "FileManager.h"

//std::string FilePath = "C:\\Users\\eltig\\OneDrive\\Рабочий стол\\Пришел, увидел, победил.docx";
std::string FileName = "Пришел, увидел, победил.docx";

int main() {
	FileManager fm(FileName);
	std::cout <<"File size is "<<fm.GetFileSize()<<std::endl;
	std::cout << "Relative frequency:" << std::endl;
	for (const auto& ByteFrequency : fm.GetBytesRelativeFrequency()) {
		std::cout << ByteFrequency.first << " - " << ByteFrequency.second<<std::endl;
	}
	Coder coder;
	std::string filename = "Пришел, увидел, победил.docx";
	coder.Encode(filename);
	coder.Decode(filename);
}