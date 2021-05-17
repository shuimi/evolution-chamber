//
// Created by Vladimir on 15.05.2021.
//

#include "headers/EvolutionChamber.h"

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


Generation *EvolutionChamber::selectionElite(Generation *population, std::function<bool(double)> selectionCondition) {

    population->estimate(EvolutionChamber::getFitnessFunction());

    for(int i = 0; i < population->getIndividuals().size();){
        if(!selectionCondition(population->getIndividualsEstimation().at(i))) {
            population->eject(i);
        }
        else i++;
    }

    return population;
}

Generation *EvolutionChamber::selectionElite(Generation *population, std::function<double(double)> fitnessFunction,
                                             std::function<bool(double)> selectionCondition) {
    population->estimate(fitnessFunction);
    for(int i = 0; i < population->getIndividuals().size();){
        if(!selectionCondition(population->getIndividualsEstimation().at(i))) {
            population->eject(i);
        }
        else i++;
    }
    return population;
}

std::tuple<BinaryChromosome*, BinaryChromosome*> EvolutionChamber::selectRandomPair(Generation *population) {
    BinaryChromosome *A, *B;
    A = population->getRandomIndividual();
    B = population->getRandomIndividual();
    while(A == B){
        B = population->getRandomIndividual();
    }
    return std::make_tuple(A, B);
}

EvolutionChamber::EvolutionChamber(
    std::function<double(double)> fitnessFunction, Generation *initialGeneration, MorphingFactor *morphingFactor
) : fitnessFunction(std::move(fitnessFunction)), initialGeneration(initialGeneration), morphingFactor(morphingFactor) {

}

EvolutionChamber::~EvolutionChamber() {

}

Population *EvolutionChamber::getPopulation() const {
    return population;
}

void EvolutionChamber::setPopulation(Population *population) {
    EvolutionChamber::population = population;
}

Generation *EvolutionChamber::getInitialGeneration() const {
    return initialGeneration;
}

void EvolutionChamber::setInitialGeneration(Generation *initialGeneration) {
    EvolutionChamber::initialGeneration = initialGeneration;
}

MorphingFactor *EvolutionChamber::getMorphingFactor() const {
    return morphingFactor;
}

void EvolutionChamber::setMorphingFactor(MorphingFactor *morphingFactor) {
    EvolutionChamber::morphingFactor = morphingFactor;
}

Generation *EvolutionChamber::getNextGeneration() {
    return new Generation(0);
}