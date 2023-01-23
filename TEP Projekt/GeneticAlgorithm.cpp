#include <stdexcept>

#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(int popSize, float crossProb, float mutProb)
	:rng()
{
	if (popSize <= 0) {
		throw std::invalid_argument("population size must be greater than 0");
	}
	if (crossProb < 0 || crossProb > 1 || mutProb < 0 || mutProb > 1) {
		throw std::invalid_argument("probabilities must be between 0 and 1");
	}

	populationSize = popSize;
	crossoverProb = crossProb;
	mutationProb = mutProb;
}

void GeneticAlgorithm::run(const BinaryOptimizationProblem& problem, int numIterations,const SelectionMethod& selection)
{
	if (numIterations < 0) {
		throw std::invalid_argument("number of iterations must be non negative");
	}

	//utworzenie pierwszej populacji
	std::vector<Individual> population;
	population.reserve(populationSize);

	//zapelnienie losowymi osobnikami oraz ocena przystowosania
	for (int i = 0; i < populationSize; i++) {
		population.push_back(Individual(problem.getSolutionLength(), rng));
		population[i].evaluateGenotype(problem);
	}

	std::vector<Individual> nextPopulation; //nastepna generacja populacji
	nextPopulation.reserve(populationSize);

	//glowna petla algorytmu, tworzy kolejne generacje populacji
	for (int i = 0; i < numIterations; i++) {
	
		std::cout << "POPULACJA NR: " << i + 1;

		int bestFitness = INT_MIN;
		int bestIndex = 0;
		for (int i = 0; i < populationSize; i++) {
			if (population[i].getFitness() > bestFitness) {
				bestFitness = population[i].getFitness();
				bestIndex = i;
			}
		}
		std::cout<<", Najlepszy:" << bestFitness<<"\n";
			
		while (nextPopulation.size() != populationSize) {



			//referencje na osobniki wybrane metoda selekcji z populacji
			const Individual& parent1 = population[selection.selectParent(population, rng)];
			const Individual& parent2 = population[selection.selectParent(population, rng)];
			
			
			//sprawdzenie czy nastepuje krzyzowanie
			if (rng.generateFloat(0, 1) < crossoverProb) {
				//jesli krzyzowanie nastepuje to tworzymy dzieci, natepnie wstawiamy do nowej populacji
				std::pair<Individual, Individual> children = parent1.crossover(parent2,rng);

				nextPopulation.push_back(std::move(children.first));
				nextPopulation.push_back(std::move(children.second));
			}
			else {

				//w  przeciwnym wypadku do nowej populacji przechodza wybrani rodzice
				nextPopulation.push_back(parent1);
				nextPopulation.push_back(parent2);
			}

		}
		//przeprowadzenie mutacji nowej populacji, oraz ewaluacja przystosowania osobnikow
		for (int i = 0; i < populationSize; i++) {
			nextPopulation[i].mutate(mutationProb, rng);
			nextPopulation[i].evaluateGenotype(problem);
			/*nextPopulation[i].print();*/
		}
		std::swap(population, nextPopulation);
		nextPopulation.clear();
		nextPopulation.reserve(populationSize);

	}

	
	
}
