
#include "KnapsackProblem.h"

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

KnapsackProblem::KnapsackProblem(const std::string& filename)
{
	std::ifstream inputFile(filename);
	
	if (!inputFile.is_open()) {
		throw std::invalid_argument("could open file: '" + filename + "'");
	}//nie udalo sie otworzyc pliku

	inputFile >> numItems >> knapsackCapacity;

	if (numItems < 0) {
		throw std::invalid_argument("number of items cannot be negative");
	}//ujemna liczba przedmiotow

	if (knapsackCapacity < 0) {
		throw std::invalid_argument("knapsack capacity cannot be negative");
	}//ujemna pojemnosc plecaka

	int itemCounter = 0; //licznik wczytanych przedmiotow
	float currentItemValue, currentItemWeight;

	while (inputFile >> currentItemValue >> currentItemWeight) {
		if (currentItemValue < 0 || currentItemWeight < 0) {
			throw std::invalid_argument("weight and value must be non negative");
		}//ujemna waga lub wartosc

		itemsValues.push_back(currentItemValue);
		itemsWeights.push_back(currentItemWeight);
		itemCounter++;
	}

	if (itemCounter != numItems) {
		throw std::invalid_argument("something went wrong (specified number of items doesnt match the real number / non numeric value encountered)");
	}//liczba przedmiotow ktore zostaly dodane rozni sie od liczby podanej jako pierwsza wartosc w pliku,
	//moze takze byc spowodowane wystapieniem wartosci ktora nie jest numeryczna


	inputFile.close();
}

float KnapsackProblem::evaluateGenotype(const std::vector<bool>& genotype) const
{
	//inicjujemy zmienne reprezentujace sume wag oraz wartossi wszystkich zabranych zmiennych
	float totalWeight = 0;
	float totalValue = 0;

	//iteracja po genotypie, jeesli true, to "zabieramy" przedmiot, czyli dodajemy jego wage oraz wartosc
	for (int i = 0; i < numItems; i++) {
		if (genotype[i]) {
			totalWeight += itemsWeights[i];
			totalValue += itemsValues[i];
		}
	}

	//jesli przekroczylismy rozmiar plecaka to jakosc rozwizania jest ujemna i wynosci calkowita wage o jaka przekroczono rozmiar
	if (totalWeight > knapsackCapacity) { return knapsackCapacity - totalWeight; }


	return totalValue;
}

//zwraca dlugosc wymaganego rozwiazania, czyli liczgbe przedmiotow mozliwych do zabrania
int KnapsackProblem::getSolutionLength() const
{
	return numItems;
}
