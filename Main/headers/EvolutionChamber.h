//
// Created by Vladimir on 15.05.2021.
//
#include <functional>

#include "../../Morphers/headers/GenerationFactory.h"
#include "../../Entities/headers/Population.h"
#include "../../Morphers/service/MorphingFactor.h"
#include "../../Morphers/service/FitnessFunctionConstraints.h"

#ifndef GENETIC_ALGS_GENETICSTRAINER_H
#define GENETIC_ALGS_GENETICSTRAINER_H


class EvolutionChamber{
private:
    std::function<double(double)> fitnessFunction;
    Population* population = new Population();
    FitnessFunctionConstraints<int>* constraints;
    Generation* initialGeneration;
    MorphingFactor* morphingFactor;

public:

    EvolutionChamber(std::function<double(double)> fitnessFunction,
                     FitnessFunctionConstraints<int>* constraints,
                     Generation *initialGeneration,
                     MorphingFactor *morphingFactor);

    virtual ~EvolutionChamber();

    const double executeFitnessFunction(double arg);



    Generation* selection(Generation* population, std::function<bool(double)> selectionCondition);

    static Generation* selection(Generation* population,
                                 std::function<double(double)> fitnessFunction,
                                 std::function<bool(double)> selectionCondition);



    static std::tuple<BinaryChromosome*, BinaryChromosome*> selectRandomPair(Generation* population);



    const std::function<double(double)> &getFitnessFunction() const;
    void setFitnessFunction(std::function<double(double)> fitnessFunction);

    Population *getPopulation();
    void setPopulation(Population *population);

    Generation *getInitialGeneration();
    void setInitialGeneration(Generation *initialGeneration);

    MorphingFactor *getMorphingFactor();
    void setMorphingFactor(MorphingFactor *morphingFactor);

    FitnessFunctionConstraints<int> *getConstraints() const;
    void setConstraints(FitnessFunctionConstraints<int> *constraints);



    Generation* breedingRandom(Generation* generation);

    Generation* breedingInbreedingGenSimilarityDriven(Generation* parents, Generation* descendants);

    Generation* breedingInbreedingElite(Generation* parents, Generation* descendants);

    Generation* breedingWithEstimation(Generation* generation, double normalizedEstimationThreshold);

    Generation* executeBreeding(Generation* generation);



    Generation* getNextGeneration();

    Generation *selectionCustomEstimation(Generation *population, std::function<bool(double)> selectionCondition);
};


#endif //GENETIC_ALGS_GENETICSTRAINER_H
