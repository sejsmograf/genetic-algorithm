#include "KnapsackProblem.h"
#include <stdexcept>
#include <iostream>


KnapsackProblem::KnapsackProblem(const std::vector<float>& weights, const std::vector<float>& values, int capacity)
{
	if (capacity < 0) {
		throw std::invalid_argument("knapsack capacity cannot be negative");
	}//ujemnma pojemnosc plecaka

	if (weights.size() != values.size()) {
		throw std::invalid_argument("weights and values are not the same size");
	}//rozne rozmiary wektorow


	for(int i = 0; i < weights.size(); i++){
		if (weights[i] < 0 || values[i] < 0) {
			throw std::invalid_argument("weights and values of items cannot be negative");
		}
	}//ujemna waga lub wartosc

	numItems = weights.size();
	knapsackCapacity = capacity;
	itemsWeights = weights;
	itemsValues = values;
}

float KnapsackProblem::evaluateGenotype(const std::vector<bool>& genotype) const
{
	//inicjujemy zmienne reprezentujace sume wag oraz wartossi wszystkich zabranych zmiennych
	float totalWeight = 0;
	float totalValue = 0;

	//iteracja po genotypie, jeesli true, to "zabieramy" przedmiot, czyli dodajemy jego parametry
	for (int i = 0; i < numItems; i++) {
		if (genotype[i]) {
			totalWeight += itemsWeights[i];
			totalValue += itemsValues[i];
		}
	}

	//jesli przekroczylismy rozmiar plecaka to jakosc rozwizania to 0 (plecak pekl)
	if (totalWeight > knapsackCapacity) { return 0; }

	return totalValue;
}

int KnapsackProblem::getSolutionLength() const
{
	return numItems;
}
