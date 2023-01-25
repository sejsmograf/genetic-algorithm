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


	//wypelnia wektor pierszej populacji dla danej instancji problemu, wypelniajac go losowymi osobnikami
	void createInitialPopulation(std::vector<Individual>& initialPopulation, const BinaryOptimizationProblem& problem, RandomNumberGenerator& rng);

	//wypelnia wektor nowej populacji, bazujac na poprzedniej,
	void createNextPopulation(const std::vector<Individual>& currentPopulation, std::vector<Individual>& nextPopulation, const SelectionMethod& selection, const BinaryOptimizationProblem& problem, RandomNumberGenerator& rng);

	//glowna metoda algorytmu, przeprowadza symulacje mechanizmu ewolucji, tworzac kolejne generacje populacji,
	void run(const BinaryOptimizationProblem& problem, int numIterations, const SelectionMethod& selection, bool printBestFromEveryPopulation = false);

	const Individual& getBestIndividualFromPopulation(const std::vector<Individual>& population) const;

	Individual getBestSolutionFromLastRun() const;

private:
	int populationSize; //rozmiar populacji
	float crossoverProbability; //szansa krzyzowania wybranych osobnikow
	float mutationProbability; //szansa mutacji kazdego genu kazdego osobnika
	Individual bestSolutionFromLastRun;
	RandomNumberGenerator rng; //instancja klasy enkapsulujacej generator liczb losowych, przekazywana jest dla innych klas, w celu unikniecia kopii
};

