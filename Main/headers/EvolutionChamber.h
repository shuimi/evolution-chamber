//
// Created by Vladimir on 15.05.2021.
//
#include <functional>

#include "../../Morphers/headers/GenerationFactory.h"

#ifndef GENETIC_ALGS_GENETICSTRAINER_H
#define GENETIC_ALGS_GENETICSTRAINER_H


class EvolutionChamber{
private:

    std::function<double(double)> fitnessFunction;

    Generation* initialPopulation;

    Generation* currentPopulation;

    int populationSize;
    int generationsAmount;

public:

    EvolutionChamber(const std::function<double(double)> &fitnessFunction) :
    fitnessFunction(fitnessFunction) {}

    EvolutionChamber() {}

    virtual ~EvolutionChamber() {}

    const std::function<double(double)> &getFitnessFunction() const;

    void setFitnessFunction(std::function<double(double)> fitnessFunction);

    const double executeFitnessFunction(double arg);

    //TODO: microevolution

    //TODO: move selection operators to external Selection class
    //TODO: move breeding operators to external Breeding class

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
            breedingInbreedingGenSimilarityDriven(Generation* population);

    static Generation*
            breedingInbreedingElite(Generation* population);

};


#endif //GENETIC_ALGS_GENETICSTRAINER_H
