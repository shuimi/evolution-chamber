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

std::tuple<BinaryChromosome*, BinaryChromosome*> EvolutionChamber::breedingRandom(Generation *generation) {
    BinaryChromosome *A, *B;
    A = generation->getRandomIndividual();
    B = generation->getRandomIndividual();
    while(A == B){
        B = generation->getRandomIndividual();
    }
    return std::make_tuple(A, B);
}

EvolutionChamber::EvolutionChamber(
    std::function<double(double)> fitnessFunction,
    Generation *initialGeneration,
    MorphingFactor *morphingFactor,
    int generationsAmount
) : fitnessFunction(std::move(fitnessFunction)),
initialGeneration(initialGeneration),
morphingFactor(morphingFactor),
generationsAmount(generationsAmount) {

}

EvolutionChamber::~EvolutionChamber() {

}
