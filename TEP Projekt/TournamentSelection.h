#pragma once
#include <stdexcept>
#include "SelectionMethod.h"


class TournamentSelection :
	public SelectionMethod
{
public:
	//konstruktor przyjmuje rozmiar turnieju, domyslnie jest to 2
	TournamentSelection(int size = 2);


	virtual int selectParent(const std::vector<Individual>& population, RandomNumberGenerator& rng) const override;


private:
	int tournamentSize;

};

