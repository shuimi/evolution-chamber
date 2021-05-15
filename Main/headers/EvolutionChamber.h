//
// Created by Vladimir on 15.05.2021.
//
#include <functional>

#include "../../Entities/headers/BinaryChromosome.h"
#include "../../Entities/headers/Population.h"

#ifndef GENETIC_ALGS_GENETICSTRAINER_H
#define GENETIC_ALGS_GENETICSTRAINER_H

//TODO:

class EvolutionChamber{
private:

    std::function<double(double)> fitnessFunction;

    Population* initialPopulation;

    Population* currentPopulation;

public:

    EvolutionChamber(const std::function<double(double)> &fitnessFunction) :
    fitnessFunction(fitnessFunction) {}

    EvolutionChamber() {}

    virtual ~EvolutionChamber() {}

    void setFitnessFunction(std::function<double(double)> fitnessFunction);

    const double executeFitnessFunction(double arg);

};


#endif //GENETIC_ALGS_GENETICSTRAINER_H
