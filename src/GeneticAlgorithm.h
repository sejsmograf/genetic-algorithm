#pragma once
#include "RandomNumberGenerator.h"
#include "BinaryOptimizationProblem.h"
#include "SelectionMethod.h"

class GeneticAlgorithm
{
public:
	GeneticAlgorithm(int popSize, float crossProb, float mutProb);

	// Use the default for every Rule Of Five function
	GeneticAlgorithm(const GeneticAlgorithm &other) = default;
	GeneticAlgorithm(GeneticAlgorithm &&other) = default;
	GeneticAlgorithm &operator=(const GeneticAlgorithm &other) = default;
	GeneticAlgorithm &operator=(GeneticAlgorithm &&other) = default;
	~GeneticAlgorithm() = default;

	// Fills the initial population
	void createInitialPopulation(std::vector<Individual> &initialPopulation, const BinaryOptimizationProblem &problem, RandomNumberGenerator &rng);

	// Fills next population basing on the current one
	void createNextPopulation(const std::vector<Individual> &currentPopulation, std::vector<Individual> &nextPopulation, const SelectionMethod &selection, const BinaryOptimizationProblem &problem, RandomNumberGenerator &rng);

	// Main GA evolution method
	void run(const BinaryOptimizationProblem &problem, int numIterations, const SelectionMethod &selection, bool printBestFromEveryPopulation = false);

	const Individual &getBestIndividualFromPopulation(const std::vector<Individual> &population) const;

	Individual getBestSolutionFromLastRun() const;

private:
	int populationSize;
	float crossoverProbability;
	float mutationProbability;
	Individual bestSolutionFromLastRun;
	RandomNumberGenerator rng; // Random number generator instance used for various tasks
};
