#include "TournamentSelection.h"

//konstruktor przyjmuje rozmiar turnieju
TournamentSelection::TournamentSelection(int size)
{
	if (size <= 0) {
		throw std::invalid_argument("tournament size must be greater than zero");
	}//turniej musi miec co najmniej jednego kandydata
	tournamentSize = size;
}

const Individual& TournamentSelection::selectParent(const std::vector<Individual>& population, RandomNumberGenerator& rng) const
{

	int indexOfBest = rng.generateInt(0, population.size() - 1);
	float fitnessOfBest = population[indexOfBest].getFitness();

	//losowanie kandydatow do turnieju, zaczyna sie od 1, poniewaz pierwszy kandydat juz wybrany
	for (int i = 1; i < tournamentSize; i++) {
		int randomIndex = rng.generateInt(0, population.size() - 1); //indeks lsoowego kandydata
		float fitnessOfCandidate = population[randomIndex].getFitness();  //fitness kandydata

		if (fitnessOfCandidate > fitnessOfBest) {
			fitnessOfBest = fitnessOfCandidate;
			indexOfBest = randomIndex;
		}//jesli fitness jest wiekszy niz najlepszy dotychczas, to przypisujemy indeks
	}

	return population[indexOfBest];
}
