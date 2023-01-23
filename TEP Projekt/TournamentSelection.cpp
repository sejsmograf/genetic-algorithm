#include "TournamentSelection.h"

TournamentSelection::TournamentSelection(int size)
{
	if (size <= 0) {
		throw std::invalid_argument("tournament size must be greater than zero");
	}
	tournamentSize = size;
}

int TournamentSelection::selectParent(const std::vector<Individual>& population, RandomNumberGenerator& rng) const
{


	int indexOfBest = rng.generateInt(0, population.size() - 1);
	float fitnessOfBest = population[indexOfBest].getFitness();

	//std::cout << "kandydat nr " << 1 << " :::  index ::: " << indexOfBest << "\t";
	//population[indexOfBest].print();

	//wybor losowego osobnika, porownanie jego fitnessu do najlepszego dotychczas
	for (int i = 1; i < tournamentSize; i++) {
		int randomIndex = rng.generateInt(0, population.size() - 1);
		float fitnessOfCandidate = population[randomIndex].getFitness();

		/*std::cout << "kandydat nr " << i + 1 << " ::: index ::: " << randomIndex << "\t";
		population[randomIndex].print();*/

		if (fitnessOfCandidate > fitnessOfBest) {
			fitnessOfBest = fitnessOfCandidate;
			indexOfBest = randomIndex;
		}
	}
	/*std::cout << "\n";*/
	return indexOfBest;
}
