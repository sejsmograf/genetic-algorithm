#include "KnapsackProblem.h"
#include "RandomNumberGenerator.h"
#include "Individual.h"
#include <iostream>
#include <chrono>
#include "GeneticAlgorithm.h"
#include "TournamentSelection.h"




int main() {
	
	auto start = std::chrono::steady_clock::now();
	std::string shortFilePrefix = ".\\knapsack_test_cases\\low-dimensional";
	std::string longFilePrefix = ".\\knapsack_test_cases\\large_scale";
	std::string filename = "knapPI_1_500_1000_1";

	std::vector<float> values = { 44,46,90,72,91,40,75,35,8,54,78,40,77,15,61,17,75,29,75,63 };
	std::vector<float> weights = { 92,4,43,83,84,68,92,82,6,44,32,18,56,83,25,96,70,48,14,58 };

	try {
		GeneticAlgorithm ga(50, 0.6, 0.003);
		TournamentSelection selection(8);
		KnapsackProblem longFileCase(longFilePrefix + "\\" + filename);

		KnapsackProblem shortFileCase(shortFilePrefix + "\\2");
		KnapsackProblem shortVectorCase(weights, values, 878);
		
		
		ga.run(longFileCase, 1000, selection,true);
		
		
	}
	catch (const std::invalid_argument error) {
		std::cout << "Invalid argument error occured: " << error.what();
	}

	

	auto end = std::chrono::steady_clock::now();

	std::cout << "\n\n\n\nElapsed time in miliseconds: "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
		<< " ms" << std::endl;
}


