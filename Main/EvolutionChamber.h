//
// Created by Vladimir on 15.05.2021.
//
#include <functional>

#include "../Morphers/GenerationFactory.h"
#include "../Entities/Population.h"
#include "../Morphers/Morphing.h"
#include "../Morphers/FunctionConstraints.h"

#ifndef GENETIC_ALGS_GENETICSTRAINER_H
#define GENETIC_ALGS_GENETICSTRAINER_H


class EvolutionChamber{
private:

    std::function<double(double)> fitnessFunction;
    FunctionConstraints<int>* constraints;

    Population* population = new Population();
    Generation* initialGeneration;

    Morphing* morphingFactor;

public:

    EvolutionChamber(std::function<double(double)> fitnessFunction,
                     FunctionConstraints<int>* constraints,
                     Generation *initialGeneration,
                     Morphing *morphingFactor);

    virtual ~EvolutionChamber();

    const double executeFitnessFunction(double arg);

    ///getters, setters
    ///getters, setters
    ///getters, setters

    const std::function<double(double)> &getFitnessFunction() const;
    void setFitnessFunction(std::function<double(double)> fitnessFunction);

    Population *getPopulation();
    void setPopulation(Population *population);

    Generation *getInitialGeneration();
    void setInitialGeneration(Generation *initialGeneration);

    Morphing *getMorphingFactor();
    void setMorphingFactor(Morphing *morphingFactor);

    FunctionConstraints<int> *getConstraints() const;
    void setConstraints(FunctionConstraints<int> *constraints);

    ///main API

    Generation* executeBreeding(Generation* generation);

    Generation* getNextGeneration();

};


#endif //GENETIC_ALGS_GENETICSTRAINER_H
