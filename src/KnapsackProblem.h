#pragma once
#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>

#include "BinaryOptimizationProblem.h"

// This class represent a Binary Knapsack Problem
class KnapsackProblem : public BinaryOptimizationProblem
{

public:
    // Create an instance from vectors of values or pass the filename and load from it
    KnapsackProblem(const std::vector<float> &weights, const std::vector<float> &values, int capacity);
    KnapsackProblem(const std::string &filename);

    // Default Rule of Five
    KnapsackProblem(const KnapsackProblem &other) = default;
    KnapsackProblem(KnapsackProblem &&other) = default;
    KnapsackProblem &operator=(const KnapsackProblem &other) = default;
    KnapsackProblem &operator=(KnapsackProblem &&other) = default;
    ~KnapsackProblem() = default;

    // Override the inherited purely virtual methods
    virtual float evaluateGenotype(const std::vector<bool> &genotype) const override;
    virtual int getSolutionLength() const override;

private:
    int numItems;
    int knapsackCapacity;
    std::vector<float> itemsValues;
    std::vector<float> itemsWeights;
};
