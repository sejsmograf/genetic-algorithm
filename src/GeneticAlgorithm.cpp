#include <stdexcept>

#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(int popSize, float crossProb, float mutProb)
	: rng(),
	  bestSolutionFromLastRun(0, rng, true)
{
	if (popSize <= 0)
	{
		throw std::invalid_argument("population size must be greater than 0");
	} // Non-positive population size
	if (crossProb < 0 || crossProb > 1 || mutProb < 0 || mutProb > 1)
	{
		throw std::invalid_argument("probabilities must be between 0 and 1");
	} // Out of bounds probability

	populationSize = popSize;
	crossoverProbability = crossProb;
	mutationProbability = mutProb;
}

// Generates the initial population of random individuals
void GeneticAlgorithm::createInitialPopulation(std::vector<Individual> &initialPopulation, const BinaryOptimizationProblem &problem, RandomNumberGenerator &rng)
{
	initialPopulation.reserve(populationSize);

	// Fill the population
	for (int i = 0; i < populationSize; i++)
	{
		initialPopulation.push_back(Individual(problem.getSolutionLength(), rng)); // Move constructor is used
		initialPopulation[i].evaluateGenotype(problem);							   // Evaluate individual's quality
	}
}

// Fills the next population basing on the current one
void GeneticAlgorithm::createNextPopulation(const std::vector<Individual> &population, std::vector<Individual> &nextPopulation, const SelectionMethod &selection, const BinaryOptimizationProblem &problem, RandomNumberGenerator &rng)
{
	nextPopulation.clear();
	nextPopulation.reserve(populationSize);

	if (populationSize % 2 == 1)
	{
		nextPopulation.push_back(selection.selectParent(population, rng));
	} // Handle odd population case (insert random individual)

	while (nextPopulation.size() != populationSize)
	{
		const Individual &parent1 = selection.selectParent(population, rng);
		const Individual &parent2 = selection.selectParent(population, rng);

		if (rng.generateFloat(0, 1) < crossoverProbability)
		{
			// Crossover and add to the new population
			std::pair<Individual, Individual> children = parent1.crossover(parent2, rng);

			nextPopulation.push_back(std::move(children.first));
			nextPopulation.push_back(std::move(children.second));
		}
		else
		{

			// Add parents to new population
			nextPopulation.push_back(parent1);
			nextPopulation.push_back(parent2);
		}
	}

	for (int i = 0; i < populationSize; i++)
	{
		nextPopulation[i].mutate(mutationProbability, rng);
		nextPopulation[i].evaluateGenotype(problem);
	} // Mutate the new population and evaluate every individual
}

void GeneticAlgorithm::run(const BinaryOptimizationProblem &problem, int numIterations, const SelectionMethod &selection, bool printBestFromEveryPopulation)
{
	if (numIterations < 0)
	{
		throw std::invalid_argument("number of iterations cannot be negative");
	} // Negative iteration number

	// Create initial population
	std::vector<Individual> population;
	createInitialPopulation(population, problem, rng);

	// Initialize next population
	std::vector<Individual> nextPopulation;

	// Find best individual from current population
	Individual bestSolution = getBestIndividualFromPopulation(population);

	// Main GA loop, creates and evaluates populations
	for (int i = 0; i < numIterations; i++)
	{

		createNextPopulation(population, nextPopulation, selection, problem, rng);

		std::swap(population, nextPopulation);

		const Individual &bestFromPopulation = getBestIndividualFromPopulation(population);
		if (bestFromPopulation.getFitness() > bestSolution.getFitness())
		{
			bestSolution = bestFromPopulation;
		}

		// Print currently best individual
		if (printBestFromEveryPopulation)
		{
			std::cout << "Best Individual from population <" << i + 1 << "> has a score of: " << bestFromPopulation.getFitness() << "\n";
		}
	}
	bestSolutionFromLastRun = bestSolution;
	std::cout << "\nBest found soultion has a score of: " << bestSolution.getFitness();
}

const Individual &GeneticAlgorithm::getBestIndividualFromPopulation(const std::vector<Individual> &population) const
{
	int bestIndex = 0;
	float bestFitness = population[0].getFitness();

	float currentFitness;
	for (int i = 0; i < populationSize; i++)
	{
		currentFitness = population[i].getFitness();

		if (currentFitness > bestFitness)
		{
			bestFitness = currentFitness;
			bestIndex = i;
		}
	}
	return population[bestIndex];
}

Individual GeneticAlgorithm::getBestSolutionFromLastRun() const
{
	return bestSolutionFromLastRun;
}
