#include <stdexcept>

#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(int popSize, float crossProb, float mutProb)
	:rng()
{
	if (popSize <= 0) {
		throw std::invalid_argument("population size must be greater than 0");
	}//niedodatni rozmiar populacji
	if (crossProb < 0 || crossProb > 1 || mutProb < 0 || mutProb > 1) {
		throw std::invalid_argument("probabilities must be between 0 and 1");
	}//prawdopodobienstwa nie nalezace do <0;1>

	populationSize = popSize;
	crossoverProbability = crossProb;
	mutationProbability = mutProb;
}

//tworzy pierwsza populacjie losowych osobnikow
void GeneticAlgorithm::createInitialPopulation(std::vector<Individual>& initialPopulation, const BinaryOptimizationProblem& problem, RandomNumberGenerator& rng)
{
	//czysci wektor populacji, nastepnie rezerwuje miejsce
	initialPopulation.clear();
	initialPopulation.reserve(populationSize);
	
	//dodaje osobniki do populacji
	for (int i = 0; i < populationSize; i++) {
		initialPopulation.push_back(Individual(problem.getSolutionLength(), rng)); // Individual traktowany jako rvalue (konstruktor przenoszacy)
		initialPopulation[i].evaluateGenotype(problem); //ewaluacja przystosowania wlasnie dodanego osobnika
	}
}


//tworzy nastepna generacje osobnikow, bazujac na dotychczasowej populacji
void GeneticAlgorithm::createNextPopulation(const std::vector<Individual>& population, std::vector<Individual>& nextPopulation, const SelectionMethod& selection, const BinaryOptimizationProblem& problem, RandomNumberGenerator& rng)
{
	//czysci wektor populacji, nastepnie rezerwuje miejsce
	nextPopulation.clear();
	nextPopulation.reserve(populationSize);


	if (populationSize % 2 == 1) {
		nextPopulation.push_back(population[selection.selectParent(population, rng)]);
	}//jesli rozmiar populacji jest nieparzysty, 


	while (nextPopulation.size() != populationSize) {
		const Individual& parent1 = population[selection.selectParent(population, rng)];
		const Individual& parent2 = population[selection.selectParent(population, rng)];

		if (rng.generateFloat(0, 1) < crossoverProbability) {
			//jesli krzyzowanie nastepuje to tworzymy dzieci, natepnie wstawiamy do nowej populacji
			std::pair<Individual, Individual> children = parent1.crossover(parent2, rng);

			nextPopulation.push_back(std::move(children.first));
			nextPopulation.push_back(std::move(children.second));
		}
		else {

			//w  przeciwnym wypadku do nowej populacji przechodza wybrani rodzice
			nextPopulation.push_back(parent1);
			nextPopulation.push_back(parent2);
		}
	}
	for (int i = 0; i < populationSize; i++) {
		nextPopulation[i].mutate(mutationProbability, rng);
		nextPopulation[i].evaluateGenotype(problem);
	}
}


void GeneticAlgorithm::run(const BinaryOptimizationProblem& problem, int numIterations,const SelectionMethod& selection, bool printBestFromEveryPopulation)
{
	if (numIterations < 0) {
		throw std::invalid_argument("number of iterations cannot be negative");
	}

	//utworzenie pierwszej populacji
	std::vector<Individual> population;
	createInitialPopulation(population, problem, rng);


	std::vector<Individual> nextPopulation;
	

	//glowna petla algorytmu, tworzy kolejne generacje populacji
	for (int i = 0; i < numIterations; i++) {

		//wypisz najlepszego osobnika z populacji
		if (printBestFromEveryPopulation) {
			std::cout << "POPULACJA NR: " << i + 1;

			int bestFitness = INT_MIN;
			int bestIndex = 0;
			for (int i = 0; i < populationSize; i++) {
				if (population[i].getFitness() > bestFitness) {
					bestFitness = population[i].getFitness();
					bestIndex = i;
				}
			}
			std::cout << ", Najlepszy:" << bestFitness << "\n";
		}

		createNextPopulation(population, nextPopulation, selection, problem, rng);

		std::swap(population, nextPopulation);
	}
}


