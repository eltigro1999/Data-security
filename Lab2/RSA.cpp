#include "RSA.h"
#include <cmath>
#include <sstream>

RSA::RSA(const int64_t& primeP_, const int64_t& primeQ_) {
	primeP = primeP_;
	primeQ = primeQ_;
	PrimeProduct = primeP * primeQ;
	EulerFuncValue = (primeP-1)*(primeQ-1);
	CalculatePublicExponent();
	PublicKey = std::make_pair(PublicExp, PrimeProduct);
	CalculateExponentModularInverse();
	PrivateKey= std::make_pair(ExponentModularInverse, PrimeProduct);
	int64_t number = 1;
	for (char letter = 'À', number=1; letter != 'ß' + 1; ++letter, ++number) {
		LetterToNumber[letter]=number;
		NumberToLetter[number] = letter;
	}
	LetterToNumber['¨'] = 33;
	NumberToLetter[33] = '¨';
	LetterToNumber[' '] = 34;
	NumberToLetter[34] = ' ';
	for (char letter = '0', number = 35; letter != '9' + 1; ++letter, ++number) {
		LetterToNumber[letter] = number;
		NumberToLetter[number] = letter;
	}
}

std::string RSA::Encode(std::string& Str) {
	std::string encoded_string;
	for (int i=0; i<Str.size(); ++i){
		encoded_string+=std::to_string(ModExp(LetterToNumber[Str[i]], PublicExp, PrimeProduct));
		if (i != Str.size() - 1) {
			encoded_string += " ";
		}
	}
	return encoded_string;
}

std::string RSA::Decode(std::string& Str) {
	std::string decoded_string;
	std::stringstream stream(Str);
	int Number = 0;
	while (!stream.eof()) {
		stream >> Number;
		decoded_string+=NumberToLetter[ModExp(Number, PrivateKey.first, PrivateKey.second)];
	}
	return decoded_string;
}

void RSA::CalculatePublicExponent() {
	for (int64_t i = static_cast<int>(sqrt(EulerFuncValue)); i > 0; --i) {
		if (GCD(i, EulerFuncValue) == 1) {
			PublicExp = i;
			return;
		}
	}
}

int64_t RSA::GCD(int a, int b) {
	if (b > a) std::swap(a,b);
	if (a % b != 0) GCD(b, a%b);
	return b;
}

void RSA::CalculateExponentModularInverse() {
	int64_t k = 1;
	do {
		ExponentModularInverse = k * EulerFuncValue + 1;
		++k;
	} while (ExponentModularInverse%PublicExp!=0);
	ExponentModularInverse /= PublicExp;
}


int64_t RSA::ModExp(const int64_t& Base, const int64_t& Power, const int64_t& Modulo)
{
	if (Power == 0) return 1;
	int Temp = ModExp(Base, Power / 2, Modulo);
	if (Power % 2 == 0)
		return (Temp * Temp) % Modulo;
	else
		return (Base * Temp * Temp) % Modulo;
}