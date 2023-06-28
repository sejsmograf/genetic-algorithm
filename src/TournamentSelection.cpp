#include "TournamentSelection.h"

TournamentSelection::TournamentSelection(int size)
{
	if (size <= 0)
	{
		throw std::invalid_argument("tournament size must be greater than zero");
	} // Tournament must have at least one candidate

	tournamentSize = size;
}

const Individual &TournamentSelection::selectParent(const std::vector<Individual> &population, RandomNumberGenerator &rng) const
{

	int indexOfBest = rng.generateInt(0, population.size() - 1);
	float fitnessOfBest = population[indexOfBest].getFitness();

	// Randomly pick and compare candidates
	for (int i = 1; i < tournamentSize; i++)
	{
		int randomIndex = rng.generateInt(0, population.size() - 1); // Random candidate index
		float fitnessOfCandidate = population[randomIndex].getFitness();

		if (fitnessOfCandidate > fitnessOfBest)
		{
			fitnessOfBest = fitnessOfCandidate;
			indexOfBest = randomIndex;
		}
	}

	return population[indexOfBest];
}
