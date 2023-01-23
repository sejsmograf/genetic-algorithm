#pragma once
#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>

#include "BinaryOptimizationProblem.h"

//Klasa reprezentujaca binarny problem plecakowy
class KnapsackProblem :
    public BinaryOptimizationProblem
{

public:

    KnapsackProblem(const std::vector<float>& weights, const std::vector<float>& values, int capacity);
    KnapsackProblem(const std::string& filename);

    //Dziedziczone z BinaryOptimizationProblem
    virtual float evaluateGenotype(const std::vector<bool>& genotype) const override;
    virtual int getSolutionLength() const override;

private:
    int numItems;
    int knapsackCapacity;
    std::vector<float> itemsValues;
    std::vector<float> itemsWeights;

};


