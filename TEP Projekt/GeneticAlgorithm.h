#pragma once
#include "RandomNumberGenerator.h"
#include "BinaryOptimizationProblem.h"
#include "SelectionMethod.h"



//klasa reprezentujaca algorytm genetyczny rozwiazujacy problem optymalizacyjny
class GeneticAlgorithm
{
public:
	GeneticAlgorithm(int popSize, float crossProb, float mutProb);

	void createInitialPopulation(std::vector<Individual>& initialPopulation, const BinaryOptimizationProblem& problem, RandomNumberGenerator& rng);

	void createNextPopulation(const std::vector<Individual>& currentPopulation, std::vector<Individual>& nextPopulation, const SelectionMethod& selection, const BinaryOptimizationProblem& problem, RandomNumberGenerator& rng);

	void run(const BinaryOptimizationProblem& problem, int numIterations, const SelectionMethod& selection, bool printBestFromEveryPopulation = false);

private:
	int populationSize;
	float crossoverProb;
	float mutationProb;
	RandomNumberGenerator rng;
};

