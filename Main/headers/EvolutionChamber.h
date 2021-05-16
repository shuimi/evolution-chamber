//
// Created by Vladimir on 15.05.2021.
//
#include <functional>

#include "../../Morphers/headers/GenerationFactory.h"
#include "../../Entities/headers/Population.h"
#include "../../Morphers/service/MorphingFactor.h"

#ifndef GENETIC_ALGS_GENETICSTRAINER_H
#define GENETIC_ALGS_GENETICSTRAINER_H


class EvolutionChamber{
private:
    std::function<double(double)> fitnessFunction;
    Population* population;
    Generation* initialGeneration;
    MorphingFactor* morphingFactor;
    int generationsAmount;

public:

    EvolutionChamber(std::function<double(double)> fitnessFunction,
                     Generation *initialGeneration,
                     MorphingFactor *morphingFactor,
                     int generationsAmount);

    virtual ~EvolutionChamber();

    const std::function<double(double)> &getFitnessFunction() const;
    void setFitnessFunction(std::function<double(double)> fitnessFunction);
    const double executeFitnessFunction(double arg);

    Generation*
    selectionElite(Generation* population,
                   std::function<bool(double)> selectionCondition);

    static Generation*
            selectionElite(Generation* population,
                           std::function<double(double)> fitnessFunction,
                           std::function<bool(double)> selectionCondition);

    static std::tuple<BinaryChromosome*, BinaryChromosome*>
            breedingRandom(Generation* population);

    static std::tuple<BinaryChromosome*, BinaryChromosome*>
            breedingInbreedingGenSimilarityDriven(Generation* generation);

    static Generation*
            breedingInbreedingElite(Generation* generation);

    Generation* getNextGeneration();

};


#endif //GENETIC_ALGS_GENETICSTRAINER_H
