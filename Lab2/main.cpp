#include <iostream>
#include "FileManager.h"
#include <Windows.h>
#include <sstream>
#include <string>


int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251); 
	SetConsoleOutputCP(1251);
	FileManager fm("InitialText.txt");
	fm.Encode();
	fm.Decode();
}