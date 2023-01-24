#include "Individual.h"



Individual::Individual(int genotypeLength, RandomNumberGenerator& rng, bool isChild)
	:fitness()
{
	//zmienia rozmiar genotypu w celu szybszego zapelnienia, bez uzywania 'push_back'
	genotype.resize(genotypeLength);

	//jesli tworzony obiekt nie jest dzieckiem, wypelniamy genotyp losowymi boolami
	//w przeciwnym wypadku nie zmienia on wartosci
	if (!isChild)
	{
		for (int i = 0; i < genotypeLength; i++) {
			genotype[i] = rng.generateInt(0, 1);
		}
	}
}


float Individual::evaluateGenotype(const BinaryOptimizationProblem& problem)
{
	fitness = problem.evaluateGenotype(genotype);
	return fitness;
}



std::pair<Individual, Individual> Individual::crossover(const Individual& other, RandomNumberGenerator& rng) const
{
	//losowowo wybrany punkt krzyzowania
	int crossoverPoint = rng.generateInt(1, genotype.size() - 1);
	Individual child1(genotype.size(), rng, true);
	Individual child2(genotype.size(), rng, true);


	//wypelniamy genotypy dzieci az do punktu krzyzowania (dziecko pierwsze genotypem this, drugie other)
	for (int i = 0; i < crossoverPoint; i++) {
		child1.genotype[i] = genotype[i];
		child2.genotype[i] = other.genotype[i];
	}

	//dopelniamy pozostaly genotyp, tym razem zamieniajac rodzicow
	for (int i = crossoverPoint; i < genotype.size(); i++) {
		child1.genotype[i] = other.genotype[i];
		child2.genotype[i] = genotype[i];
	}

	return std::pair<Individual, Individual>(child1, child2);
}




float Individual::getFitness() const
{
	return fitness;
}

void Individual::mutate(float mutProb, RandomNumberGenerator& rng)
{
	for (int i = 0; i < genotype.size(); i++) {
		if (rng.generateFloat(0, 1) < mutProb) {
			genotype[i] = !(genotype[i]);
		}
	}
}

void Individual::print() const
{
	for (int i = 0; i < genotype.size(); i++) {
		std::cout << genotype[i];
	}
	std::cout << ",   FITNESS: " << fitness<<"\n";
}
