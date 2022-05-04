#include "BlowFish.h"

BlowFish::BlowFish(const std::string& key_) {
	key = key_;
	ExtendKey();
}

void BlowFish::ExtendKey() {
	for (int PKeyNumber = 0; PKeyNumber < 18; PKeyNumber++) {
		int _32bits=bits32FromPos((PKeyNumber*4)%key.size(), key);
		PermutationBox[PKeyNumber] ^= _32bits;
	}
	uint64_t left = 0, right=0;
	for (int i = 0; i < 18; ++i) {
		FeistelCipherEncoding(left, right);
		PermutationBox[i] = left;
		PermutationBox[++i] = right;
	}
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 256; ++j) {
			FeistelCipherEncoding(left, right);
			SubstituteBox[i][j] = left;
			SubstituteBox[i][++j] = right;
		}
	}

}

std::string BlowFish::Encode(std::string message) {
	if (message.size() % 8 != 0) {
		int bytesToAdd=8 - message.size() % 8;
		for (int i = 0; i < bytesToAdd; ++i) {
			message += static_cast<char>(0);
		}
	}
	std::string encodedMessage;
	for (int i = 0; i < message.size(); i += 8) {
		uint64_t left = bits32FromPos(i, message);
		uint64_t right = bits32FromPos(i+4, message);
		FeistelCipherEncoding(left, right);
		Add32bitsIntoString(left, encodedMessage);
		Add32bitsIntoString(right, encodedMessage);
	}
	return encodedMessage;
}
std::string BlowFish::Decode(std::string bytes) {
	std::string decodedMessage;
	for (uint64_t i = 0; i < bytes.size(); i += 8) {
		uint64_t left = bits32FromPos(i, bytes);
		uint64_t right = bits32FromPos(i + 4, bytes);
		FeistelCipherDecoding(left, right);
		Add32bitsIntoString(left, decodedMessage);
		Add32bitsIntoString(right, decodedMessage);
	}
	return decodedMessage;
}

void BlowFish::FeistelCipherEncoding(uint64_t& left, uint64_t& right) {
	for (int round = 0; round < 16; ++round) {
		left ^= PermutationBox[round];
		right ^= F(left);
		if(round!=15) std::swap(left, right);
	}
	right ^= PermutationBox[16];
	left ^= PermutationBox[17];
}

void BlowFish::FeistelCipherDecoding(uint64_t& left, uint64_t& right) {
	for (int round = 17; round > 1; --round) {
		left ^= PermutationBox[round];
		right ^= F(left);
		if (round != 2) std::swap(left, right);
	}
	left ^= PermutationBox[0];
	right ^= PermutationBox[1];
}

uint64_t BlowFish::F(const uint64_t& subBlock) {
	uint64_t firstFragment = (subBlock & 0xFF000000)>>24;
	uint64_t secondFragment = (subBlock & 0x00FF0000)>>16;
	uint64_t thirdFragment = (subBlock & 0x0000FF00)>> 8;
	uint64_t fourthFragment = (subBlock & 0x000000FF);
	uint64_t result = ((((SubstituteBox[0][firstFragment] + SubstituteBox[1][secondFragment]) % 4294967296)
		^ SubstituteBox[2][thirdFragment]) + SubstituteBox[3][fourthFragment]) % 4294967296;
	return result;
}

uint64_t BlowFish::bits32FromPos(const uint64_t& Position, const std::string& str) {
	uint64_t _32bits = 0;
	for (int i = Position, counter=0; counter<4; i=(i+1)%str.size(), ++counter) {
		unsigned char c = (unsigned char)str[i];
		_32bits = _32bits << 8 | (unsigned char)str[i];
	}
	return _32bits;
}

void BlowFish::Add32bitsIntoString(const uint64_t& _4bytes, std::string& str) {
	uint64_t firstFragment = (_4bytes & 0xFF000000) >> 24;
	uint64_t secondFragment = (_4bytes & 0x00FF0000) >> 16;
	uint64_t thirdFragment = (_4bytes & 0x0000FF00) >> 8;
	uint64_t fourthFragment = _4bytes & 0x000000FF;
	str += firstFragment;
	str += secondFragment;
	str += thirdFragment;
	str += fourthFragment;

}