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
		std::string fileName = "2";

		
		RandomNumberGenerator rng;
		TournamentSelection selection;
		KnapsackProblem a(shortFilePrefix + "\\" + fileName);











		GeneticAlgorithm ga(50, 0.7, 0.05);
		ga.run(a, 100, selection);
		std::ifstream optimumInput(shortFilePrefix + "-optimum\\" + fileName);

		int opt;
		optimumInput >> opt;
		std::cout << "\n" << opt;
	}
	catch (const std::invalid_argument error) {
		std::cout << error.what();
	}


	auto end = std::chrono::steady_clock::now();

	std::cout << "\n\n\n\nElapsed time in nanoseconds: "
		<< std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
		<< " us" << std::endl;
}


