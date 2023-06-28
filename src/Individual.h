#pragma once
#include <iostream>

#include "RandomNumberGenerator.h"
#include "BinaryOptimizationProblem.h"

class Individual
{
public:
	Individual(int genotypeLength, RandomNumberGenerator &rng, bool isChild = false);

	// Default Rule of Five
	Individual(const Individual &other) = default;
	Individual(Individual &&other) = default;
	Individual &operator=(const Individual &other) = default;
	Individual &operator=(Individual &&other) = default;
	~Individual() = default;

	float getFitness() const;

	// Evaluate the genotype as a solution to given problem
	void evaluateGenotype(const BinaryOptimizationProblem &problem);

	// Performs a crossover, returns pair of children
	std::pair<Individual, Individual> crossover(const Individual &other, RandomNumberGenerator &rng) const;

	// Muatates each gene with given probability
	void mutate(float mutProb, RandomNumberGenerator &rng);

	// Prints the genotype and fitness
	void print() const;

private:
	std::vector<bool> genotype;
	float fitness;
};
