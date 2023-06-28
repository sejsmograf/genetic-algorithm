#include "Individual.h"

Individual::Individual(int genotypeLength, RandomNumberGenerator &rng, bool isChild)
	: fitness()
{
	// Resize the genotype to avoid the cost of resizing
	genotype.resize(genotypeLength);

	// If individual is not a child we fill it's gentorype with random bits
	if (!isChild)
	{
		for (int i = 0; i < genotypeLength; i++)
		{
			genotype[i] = rng.generateInt(0, 1);
		}
	}
}

void Individual::evaluateGenotype(const BinaryOptimizationProblem &problem)
{
	fitness = problem.evaluateGenotype(genotype);
}

std::pair<Individual, Individual> Individual::crossover(const Individual &other, RandomNumberGenerator &rng) const
{
	// Randombly pick crossover point
	int crossoverPoint = rng.generateInt(1, genotype.size() - 1);

	// Create two children
	Individual child1(genotype.size(), rng, true);
	Individual child2(genotype.size(), rng, true);

	// Fill the genotypes copying parents, until the crossover point
	for (int i = 0; i < crossoverPoint; i++)
	{
		child1.genotype[i] = genotype[i];
		child2.genotype[i] = other.genotype[i];
	}

	// Swap the parents and fill the rest of genotypes
	for (int i = crossoverPoint; i < genotype.size(); i++)
	{
		child1.genotype[i] = other.genotype[i];
		child2.genotype[i] = genotype[i];
	}

	return std::pair<Individual, Individual>(child1, child2);
}

float Individual::getFitness() const
{
	return fitness;
}

void Individual::mutate(float mutProb, RandomNumberGenerator &rng)
{
	for (int i = 0; i < genotype.size(); i++)
	{
		if (rng.generateFloat(0, 1) < mutProb)
		{
			genotype[i] = !(genotype[i]);
		} // Mutate by flipping a bit if the mutation occurs
	}
}

void Individual::print() const
{
	for (int i = 0; i < genotype.size(); i++)
	{
		std::cout << genotype[i];
	}
	std::cout << ",   FITNESS: " << fitness << "\n";
}
