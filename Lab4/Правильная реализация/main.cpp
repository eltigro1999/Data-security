#include <iostream>
#include <string>
#include "BlowFish.h"

int main() {
	std::string key = "Information security";
	std::string message = "I don't like to protect information";
	BlowFish blowfish(key);
	std::string bytes=blowfish.Encode(message);
	std::cout << bytes<<std::endl;
	std::string DecodedMessage = blowfish.Decode(bytes);
	std::cout << DecodedMessage<<std::endl;
}
//"This is a crypto blowfish 448 bits key and 64 bits text!"