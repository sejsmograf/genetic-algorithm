#pragma once
#include "RandomNumberGenerator.h"
#include "BinaryOptimizationProblem.h"
#include "SelectionMethod.h"



//klasa reprezentujaca algorytm genetyczny rozwiazujacy problem optymalizacyjny
class GeneticAlgorithm
{
public:
	GeneticAlgorithm(int popSize, float crossProb, float mutProb);


	void run(const BinaryOptimizationProblem& problem, int numIterations, const SelectionMethod& selection);




private:
	int populationSize;
	float crossoverProb;
	float mutationProb;
	RandomNumberGenerator rng;
};

