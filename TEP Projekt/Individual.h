#pragma once
#include <iostream>

#include "RandomNumberGenerator.h"
#include "BinaryOptimizationProblem.h"

class Individual
{
public:
	//konstruktor przyjmuje dlugosc wymaganego genotypu, instacje generatora losowego
	//oraz informacje czy tworzone jest dziecko
	Individual(int genotypeLength, RandomNumberGenerator& rng, bool isChild = false);

	Individual(const Individual& other) = default;

	Individual(Individual&& other) = default;
	
	Individual& operator=(const Individual& other) = default;

	Individual& operator=(Individual&& other) = default;

	~Individual() = default;

	//ocenia przystosowanie osobnika dla danego problemu optymalizacyjnego i zwraca wynik
	float evaluateGenotype(const BinaryOptimizationProblem& problem);

	//przeprowadza krzyzowanie osobnika z drugim rodzicem i zwraca pare dzieci
	std::pair<Individual, Individual> crossover(const Individual& other,RandomNumberGenerator& rng) const;

	
	
	float getFitness() const;

	void mutate(float mutProb, RandomNumberGenerator& rng);

	void print() const;
	
private:
	std::vector<bool> genotype;
	float fitness;
};


