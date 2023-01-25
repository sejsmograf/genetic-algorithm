#pragma once
#include <vector>

//Interfejs reprezentujacy problem optymalizacyjny, ktorego rozwiazanie da sie zapisac jako binarny ciag
//gwarantuje metode oceniajaca jakosc rozwiazania(genotypu) oraz metode zwracajaca dlugosc wymaganego rozwiazania
class BinaryOptimizationProblem {

public:

	//ocenia jakosc genotypu i zwraca wynik
	virtual float evaluateGenotype(const std::vector<bool>& genotype) const = 0;

	//zwraca dlugosc wymaganego rozwiaazania
	virtual int getSolutionLength() const = 0;
};