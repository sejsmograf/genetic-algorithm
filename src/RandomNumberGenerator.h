#pragma once
#include <random>

class RandomNumberGenerator
{
public:
	RandomNumberGenerator();

	int generateInt(int lowerBound, int upperBound);

	float generateFloat(float lowerBound, float upperBound);

private:
	std::mt19937 mt;
};
