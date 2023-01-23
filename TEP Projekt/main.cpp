#include "KnapsackProblem.h"
#include "RandomNumberGenerator.h"
#include "Individual.h"
#include <iostream>
#include <chrono>
#include "GeneticAlgorithm.h"
#include "TournamentSelection.h"

int main() {

	


    auto start = std::chrono::steady_clock::now();
    RandomNumberGenerator rng;
    

    std::vector<float> weights = { 84, 83, 43, 4, 44, 6, 82, 92, 25, 83, 56, 18, 58, 14, 48, 70, 96, 32, 68, 92 };
    std::vector<float> values = { 91, 72, 90, 46, 55, 8, 35, 75, 61, 15, 77, 40, 63, 75, 29, 75, 17, 78, 40,44 };

    KnapsackProblem a(weights, values, 879);
    TournamentSelection selection(10);
    
    int popsize = 8;

    /*std::vector<Individual> population;
   


    for (int i = 0; i < popsize; i++) {
        population.push_back(Individual(6, rng));
        population[i].evaluateGenotype(a);
    }

    for (int j = 0; j < 1; j++) {
        std::cout << "POPULACJA: " << j<<"\n";
        for (int i = 0; i < popsize; i++) {
            population[i].print();
        }
           
        for (int i = 0; i < popsize / 2; i++) {
            auto children = population[selection.selectParent(population, rng)].crossover(population[selection.selectParent(population, rng)], rng);
            children.first.print();
            children.second.print();
            std::cout << "\n";
        }
        std::cout << "\n\n";
    }*/



    GeneticAlgorithm ga(20, 0.7, 0.1);
    ga.run(a, 10, selection);





    

    auto end = std::chrono::steady_clock::now();
        
    std::cout << "Elapsed time in nanoseconds: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
        << " us" << std::endl;
}


