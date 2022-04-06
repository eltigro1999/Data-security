#include <iostream>
#include <Windows.h>
#include "Image.h"

int main() {
	Image image("9.bmp");
	image.Encode();
	image.Decode();
}