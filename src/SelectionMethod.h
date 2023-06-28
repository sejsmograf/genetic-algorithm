#pragma once
#include <vector>

#include "Individual.h"
#include "RandomNumberGenerator.h"

// This interface represents a method of selecting an individual from the population
class SelectionMethod
{
public:
	// Returns const reference to selected parent
	virtual const Individual &selectParent(const std::vector<Individual> &population, RandomNumberGenerator &rng) const = 0;
};