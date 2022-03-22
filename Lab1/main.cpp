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


//#include <iostream>
//#include <fstream>
//using namespace std;
//
//
//
//void KeyGenerate()
//{
//    ofstream out("test", ios::out | ios::binary);
//    if (!out) {
//        cout << "Cannot open file.\n";
//        return;
//    }
//    char line1[256];
//    char line2[256];
//    for (int i = -128; i <= 127; i++)
//    {
//        line1[i + 128] = i;
//    }
//    int j = 0;
//    for (int i = 127; i >= -128; i--)
//    {
//        line2[j] = i;
//        j++;
//    }
//    for (int i = -128; i <= 127; i++)
//    {
//        out.put(line1[i + 128]);
//    }
//    j = 0;
//    for (int i = 127; i >= -128; i--)
//    {
//        out.put(line2[j]);
//        j++;
//    }
//    out.close();
//
//}
//
//void Encryption()
//{
//    char line1[256];
//    char line2[256];
//    ifstream file("test", ios::in | ios::binary);
//    if (file.is_open())
//    {
//
//        file.read(line1, 256);
//        file.read(line2, 256);
//
//        file.close();
//    }
//
//    int sizeFile;
//    char* byte;
//    ifstream file2("task3", ios::in | ios::binary | ios::ate);
//    if (file2.is_open())
//    {
//        sizeFile = file2.tellg();
//        byte = new char[sizeFile];
//
//        file2.seekg(0, ios::beg);
//        file2.read(byte, sizeFile);
//        file2.close();
//
//        for (int i = 0; i < sizeFile; i++)
//        {
//            for (int j = 0; j < 256; j++)
//            {
//                if (line1[j] == byte[i])
//                {
//                    byte[i] = line2[j];
//                }
//            }
//        }
//
//        ofstream out("task3", ios::out | ios::binary);
//        for (int i = 0; i < sizeFile; i++)
//        {
//
//            out.put(byte[i]);
//        }
//        out.close();
//    }
//
//
//}
//
//void Decryption()
//{
//    char line1[256];
//    char line2[256];
//    ifstream file("test", ios::in | ios::binary);
//    if (file.is_open())
//    {
//
//        file.read(line1, 256);
//        file.read(line2, 256);
//        file.close();
//    }
//
//    int sizeFile;
//    char* byte = NULL;
//    ifstream file2("task3", ios::in | ios::binary | ios::ate);
//    if (file2.is_open())
//    {
//        sizeFile = file2.tellg();
//        byte = new char[sizeFile];
//
//        file2.seekg(0, ios::beg);
//        file2.read(byte, sizeFile);
//        file2.close();
//
//        for (int i = 0; i < sizeFile; i++)
//        {
//            for (int j = 0; j < 256; j++)
//            {
//                if (line2[j] == byte[i])
//                {
//                    byte[i] = line1[j];
//                }
//            }
//        }
//
//        ofstream out("task3", ios::out | ios::binary);
//        for (int i = 0; i < sizeFile; i++)
//        {
//            out.put(byte[i]);
//        }
//        out.close();
//    }
//
//
//}
//
//int main()
//{
//    KeyGenerate();
//    Encryption();
//    Decryption();
//}
