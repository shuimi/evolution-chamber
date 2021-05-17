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

public:

    EvolutionChamber(std::function<double(double)> fitnessFunction,
                     Generation *initialGeneration,
                     MorphingFactor *morphingFactor);

    virtual ~EvolutionChamber();

    const std::function<double(double)> &getFitnessFunction() const;
    void setFitnessFunction(std::function<double(double)> fitnessFunction);

    const double executeFitnessFunction(double arg);

    Generation* selectionElite(Generation* population, std::function<bool(double)> selectionCondition);

    static Generation* selectionElite(Generation* population,
                           std::function<double(double)> fitnessFunction,
                           std::function<bool(double)> selectionCondition);

    static std::tuple<BinaryChromosome*, BinaryChromosome*>
            selectRandomPair(Generation* population);

    Population *getPopulation() const;
    void setPopulation(Population *population);

    Generation *getInitialGeneration() const;
    void setInitialGeneration(Generation *initialGeneration);

    MorphingFactor *getMorphingFactor() const;
    void setMorphingFactor(MorphingFactor *morphingFactor);

    static Generation* breedingRandom(Generation* generation);

    static Generation* breedingInbreedingGenSimilarityDriven(Generation* generation);

    static Generation* breedingInbreedingElite(Generation* generation);

    Generation* getNextGeneration();

};


#endif //GENETIC_ALGS_GENETICSTRAINER_H
