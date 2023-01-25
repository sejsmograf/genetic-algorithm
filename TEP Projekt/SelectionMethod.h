#pragma once
#include <vector>

#include "Individual.h"
#include "RandomNumberGenerator.h"


//interfejs reprezentujacy metode selekcji osobnika z populacji
class SelectionMethod {
public:
	virtual int selectParent(const std::vector<Individual>& population,RandomNumberGenerator& rng) const = 0;
};