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

    //domyslne, generowane przez kompilator
    KnapsackProblem(const KnapsackProblem& other) = default;
    KnapsackProblem(KnapsackProblem&& other) = default;
    KnapsackProblem& operator=(const KnapsackProblem& other) = default;
    KnapsackProblem& operator=(KnapsackProblem&& other) = default;
    ~KnapsackProblem() = default;


    //Dziedziczone z BinaryOptimizationProblem
    virtual float evaluateGenotype(const std::vector<bool>& genotype) const override;
    virtual int getSolutionLength() const override;

private:
    int numItems; //liczba dostepnych przedmiotow
    int knapsackCapacity; //maksymalna pojemnosc plecaka
    std::vector<float> itemsValues; //wartosci pooszczegolnych przedmiotow
    std::vector<float> itemsWeights; //wagi poszczegolnych przedmiotowo

};


