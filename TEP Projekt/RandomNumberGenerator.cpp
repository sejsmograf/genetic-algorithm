#include "RandomNumberGenerator.h"

RandomNumberGenerator::RandomNumberGenerator()
	:mt(std::random_device{}())
{
}

int RandomNumberGenerator::generateInt(int lowerBound, int upperBound)
{
	std::uniform_int_distribution<> distr(lowerBound, upperBound);
	return distr(mt);
}

float RandomNumberGenerator::generateFloat(float lowerBound, float upperBound)
{
	std::uniform_real_distribution<float> distr(lowerBound, upperBound);
	return distr(mt);
}
