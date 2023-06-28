#include <iostream>
#include <chrono>
#include "KnapsackProblem.h"
#include "RandomNumberGenerator.h"
#include "Individual.h"
#include "GeneticAlgorithm.h"
#include "TournamentSelection.h"

#ifdef _WIN32
const std::string pathSeparator = "\\";
#else
const std::string pathSeparator = "/";
#endif

int main()
{

	auto start = std::chrono::steady_clock::now();
	std::string shortFilePrefix = "." + pathSeparator + "knapsack_test_cases" + pathSeparator + "low-dimensional";
	std::string longFilePrefix = "." + pathSeparator + "knapsack_test_cases" + pathSeparator + "large_scale";
	std::string filename = "knapPI_1_500_1000_1";

	std::vector<float> values = {44, 46, 90, 72, 91, 40, 75, 35, 8, 54, 78, 40, 77, 15, 61, 17, 75, 29, 75, 63};
	std::vector<float> weights = {92, 4, 43, 83, 84, 68, 92, 82, 6, 44, 32, 18, 56, 83, 25, 96, 70, 48, 14, 58};

	try
	{
		GeneticAlgorithm ga(50, 0.6, 0.003);
		TournamentSelection selection(8);
		KnapsackProblem longFileCase(longFilePrefix + pathSeparator + filename);

		KnapsackProblem shortFileCase(shortFilePrefix + pathSeparator + "2");
		KnapsackProblem shortVectorCase(weights, values, 878);

		ga.run(longFileCase, 1000, selection, true);
	}
	catch (const std::invalid_argument error)
	{
		std::cout << "Invalid argument error occured: " << error.what();
	}

	auto end = std::chrono::steady_clock::now();

	std::cout << "\n\n\n\nElapsed time in miliseconds: "
			  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
			  << " ms" << std::endl;
}
