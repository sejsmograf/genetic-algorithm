
#include "KnapsackProblem.h"

KnapsackProblem::KnapsackProblem(const std::vector<float> &weights, const std::vector<float> &values, int capacity)
{
	if (capacity < 0)
	{
		throw std::invalid_argument("knapsack capacity cannot be negative");
	} // Negative capacity given

	if (weights.size() != values.size())
	{
		throw std::invalid_argument("weights and values are not the same size");
	} // Sizes and values do not match in size

	for (int i = 0; i < weights.size(); i++)
	{
		if (weights[i] < 0 || values[i] < 0)
		{
			throw std::invalid_argument("weights and values of items cannot be negative");
		}
	} // Negative size or value

	numItems = weights.size();
	knapsackCapacity = capacity;
	itemsWeights = weights;
	itemsValues = values;
}

KnapsackProblem::KnapsackProblem(const std::string &filename)
{
	std::ifstream inputFile(filename);

	if (!inputFile.is_open())
	{
		throw std::invalid_argument("could open file: '" + filename + "'");
	}

	inputFile >> numItems >> knapsackCapacity;

	if (numItems < 0)
	{
		throw std::invalid_argument("number of items cannot be negative");
	}

	if (knapsackCapacity < 0)
	{
		throw std::invalid_argument("knapsack capacity cannot be negative");
	}

	int itemCounter = 0; // Count the items loaded
	float currentItemValue, currentItemWeight;

	while (inputFile >> currentItemValue >> currentItemWeight)
	{
		if (currentItemValue < 0 || currentItemWeight < 0)
		{
			throw std::invalid_argument("weight and value must be non negative");
		}

		itemsValues.push_back(currentItemValue);
		itemsWeights.push_back(currentItemWeight);
		itemCounter++;
	}

	if (itemCounter != numItems)
	{
		throw std::invalid_argument("something went wrong (specified number of items doesnt match the real number / non numeric value encountered)");
	}

	inputFile.close();
}

float KnapsackProblem::evaluateGenotype(const std::vector<bool> &genotype) const
{
	float totalWeight = 0;
	float totalValue = 0;

	// Iterate over the genotype, if a gene is 1 take the item value and weight
	for (int i = 0; i < numItems; i++)
	{
		if (genotype[i])
		{
			totalWeight += itemsWeights[i];
			totalValue += itemsValues[i];
		}
	}

	// If exceeded the capacity the genotype's score is negative
	if (totalWeight > knapsackCapacity)
	{
		return knapsackCapacity - totalWeight;
	}

	// Return the value if weight within the capacity
	return totalValue;
}

// Returns the required length of the solution
int KnapsackProblem::getSolutionLength() const
{
	return numItems;
}
