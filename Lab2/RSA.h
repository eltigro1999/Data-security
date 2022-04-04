#pragma once
#include <map>
#include <string>


class RSA {
	std::map<char, int64_t> NumberToLetter;
	std::map<int64_t, char> LetterToNumber;
	int64_t primeP;
	int64_t primeQ;
	int64_t PrimeProduct;
	int64_t EulerFuncValue;
	int64_t PublicExp;
	int64_t ExponentModularInverse;
	std::pair<int64_t, int64_t> PublicKey;
	std::pair<int, int> PrivateKey;
	void CalculatePublicExponent();
	int64_t GCD(int a, int b);
	void CalculateExponentModularInverse();
	int64_t ModExp(const int64_t& Base, const int64_t& Power, const int64_t& Modulo);
public:
	RSA(const int64_t& primeP_, const int64_t& primeQ_);
	std::string Encode(std::string& Str);
	std::string Decode(std::string& Str);
};