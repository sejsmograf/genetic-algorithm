#include "KnapsackProblem.h"
#include "RandomNumberGenerator.h"
#include "Individual.h"
#include <iostream>
#include <chrono>
#include "GeneticAlgorithm.h"
#include "TournamentSelection.h"




int main() {
	
	auto start = std::chrono::steady_clock::now();
	try {
		std::string shortFilePrefix = ".\\knapsack_test_cases\\low-dimensional";
		std::string longFilePrefix = ".\\knapsack_test_cases\\large_scale";
		std::string fileName = "knapPI_1_500_1000_1";

		
		RandomNumberGenerator rng;
		TournamentSelection selection(6);
		KnapsackProblem a(longFilePrefix + "\\" + fileName);



		







		GeneticAlgorithm ga(200, 0.7, 0.003);
		ga.run(a, 2000, selection,true);
		std::ifstream optimumInput(longFilePrefix + "-optimum\\" + fileName);

		int opt;
		optimumInput >> opt;
		std::cout << "\n" << opt;
	}
	catch (const std::invalid_argument error) {
		std::cout << error.what();
	}

	

	auto end = std::chrono::steady_clock::now();

	std::cout << "\n\n\n\nElapsed time in miliseconds: "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
		<< " ms" << std::endl;
}


