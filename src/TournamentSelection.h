#pragma once
#include <stdexcept>
#include "SelectionMethod.h"

// Method of tournament selection, implements SelectionMethod
class TournamentSelection : public SelectionMethod
{
public:
	// Contructor takes the size of the tournament
	TournamentSelection(int size = 2);

	// Default rule of five
	TournamentSelection(const TournamentSelection &other) = default;
	TournamentSelection(TournamentSelection &&other) = default;
	TournamentSelection &operator=(const TournamentSelection &other) = default;
	TournamentSelection &operator=(TournamentSelection &&other) = default;
	~TournamentSelection() = default;

	// Implement the inherited virtual method
	virtual const Individual &selectParent(const std::vector<Individual> &population, RandomNumberGenerator &rng) const override;

private:
	int tournamentSize; // Tournament size is the number of compared individiuals
};
