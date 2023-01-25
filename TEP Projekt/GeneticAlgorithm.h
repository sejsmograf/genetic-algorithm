#pragma once
#include "RandomNumberGenerator.h"
#include "BinaryOptimizationProblem.h"
#include "SelectionMethod.h"



//klasa reprezentujaca algorytm genetyczny rozwiazujacy problem optymalizacyjny
class GeneticAlgorithm
{
public:

	GeneticAlgorithm(int popSize, float crossProb, float mutProb);

	//domyslne, generowane przez kompilator 
	GeneticAlgorithm(const GeneticAlgorithm& other) = default;
	GeneticAlgorithm(GeneticAlgorithm&& other) = default;
	GeneticAlgorithm& operator=(const GeneticAlgorithm& other) = default;
	GeneticAlgorithm& operator=(GeneticAlgorithm&& other) = default;
	~GeneticAlgorithm() = default;


	void createInitialPopulation(std::vector<Individual>& initialPopulation, const BinaryOptimizationProblem& problem, RandomNumberGenerator& rng);

	void createNextPopulation(const std::vector<Individual>& currentPopulation, std::vector<Individual>& nextPopulation, const SelectionMethod& selection, const BinaryOptimizationProblem& problem, RandomNumberGenerator& rng);

	void run(const BinaryOptimizationProblem& problem, int numIterations, const SelectionMethod& selection, bool printBestFromEveryPopulation = false);

private:
	int populationSize;
	float crossoverProbability;
	float mutationProbability;
	RandomNumberGenerator rng;
};

