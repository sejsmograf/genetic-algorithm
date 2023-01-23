#pragma once
#include <random>

//Klasa enkapsulujace generator liczb losowych
class RandomNumberGenerator
{
public:
	RandomNumberGenerator();

	//zwraca losowa liczbe calkowita z przedzialu
	int generateInt(int lowerBound, int upperBound);

	//zwraca losowa liczbe zmiennoprzecinkowa z przedzialu
	float generateFloat(float lowerBound, float upperBound);

private:
	std::mt19937 mt;
		
};

