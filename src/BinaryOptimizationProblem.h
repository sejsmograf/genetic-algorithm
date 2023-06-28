#pragma once
#include <vector>

// Interface representing an optimization problem whose solution can be represented as a binary sequence
// It guarantees a method for evaluating the quality of a solution (genotype) and a method for returning the required solution length
class BinaryOptimizationProblem
{

public:
	// Evaluates the quality of given solution
	virtual float evaluateGenotype(const std::vector<bool> &genotype) const = 0;

	// Returns the required solution sequence length
	virtual int getSolutionLength() const = 0;
};