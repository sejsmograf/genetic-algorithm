#pragma once
#include <stdexcept>
#include "SelectionMethod.h"

//metoda selekcji poprzez turniej n zawodnikow (przechodzi najlepszy z n losowo wybranych) , implementuje interfejs selection method
class TournamentSelection :
	public SelectionMethod
{
public:
	//konstruktor przyjmuje rozmiar turnieju, domyslnie jest to 2
	TournamentSelection(int size = 2);

	//override metody wybierajacej rodzica z danej populacji
	virtual int selectParent(const std::vector<Individual>& population, RandomNumberGenerator& rng) const override;


private:
	int tournamentSize; //liczba zawodnikow przy kazdym turnieju

};

