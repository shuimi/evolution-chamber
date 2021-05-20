//
// Created by Vladimir on 15.05.2021.
//

#include "EvolutionChamber.h"

#include <utility>

void EvolutionChamber::setFitnessFunction(std::function<double(double)> fitnessFunction) {
    EvolutionChamber::fitnessFunction = fitnessFunction;
}

const double EvolutionChamber::executeFitnessFunction(double arg){
    return fitnessFunction.operator()(arg);
}

const std::function<double(double)> &EvolutionChamber::getFitnessFunction() const {
    return fitnessFunction;
}

EvolutionChamber::EvolutionChamber(
        std::function<double(double)> fitnessFunction,
        FunctionConstraints<int>* constraints,
        Generation *initialGeneration,
        Morphing *morphingFactor
) : fitnessFunction(std::move(fitnessFunction)),
    constraints(constraints),
    initialGeneration(initialGeneration),
    morphingFactor(morphingFactor)
{
    EvolutionChamber::getInitialGeneration()->setIndex(0);
    EvolutionChamber::population->add(EvolutionChamber::getInitialGeneration());
}

EvolutionChamber::~EvolutionChamber() {

}

Population *EvolutionChamber::getPopulation() {
    return population;
}

void EvolutionChamber::setPopulation(Population *population) {
    EvolutionChamber::population = population;
}

Generation *EvolutionChamber::getInitialGeneration() {
    return initialGeneration;
}

void EvolutionChamber::setInitialGeneration(Generation *initialGeneration) {
    EvolutionChamber::initialGeneration = initialGeneration;
}

Morphing *EvolutionChamber::getMorphingFactor() {
    return morphingFactor;
}

void EvolutionChamber::setMorphingFactor(Morphing *morphingFactor) {
    EvolutionChamber::morphingFactor = morphingFactor;
}

Generation *EvolutionChamber::getNextGeneration() {
    return nullptr;
}

FunctionConstraints<int> *EvolutionChamber::getConstraints() const {
    return constraints;
}

void EvolutionChamber::setConstraints(FunctionConstraints<int> *constraints) {
    EvolutionChamber::constraints = constraints;
}

Generation *EvolutionChamber::executeBreeding(Generation *generation) {
    return nullptr;
}
