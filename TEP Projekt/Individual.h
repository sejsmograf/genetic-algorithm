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

	//domyslne, wygenerowane przez kompilator
	Individual(const Individual& other) = default;
	Individual(Individual&& other) = default;
	Individual& operator=(const Individual& other) = default;
	Individual& operator=(Individual&& other) = default;
	~Individual() = default;

	//zwraca przystosowanie osobnika
	float getFitness() const;

	//ocenia przystosowanie osobnika dla danego problemu optymalizacyjnego
	void evaluateGenotype(const BinaryOptimizationProblem& problem);

	//przeprowadza krzyzowanie osobnika z drugim osobnikiem i zwraca pare dzieci
	std::pair<Individual, Individual> crossover(const Individual& other,RandomNumberGenerator& rng) const;

	//przeprowadza mutacje kazdego genu z szansa mutProb
	void mutate(float mutProb, RandomNumberGenerator& rng);

	//wyswietla genotyp oraz przysotowanie osobnika
	void print() const;
	
private:
	std::vector<bool> genotype; //genotyp reprezentujacy rozwiazanie problemu
	float fitness; //przystosowanie
};


