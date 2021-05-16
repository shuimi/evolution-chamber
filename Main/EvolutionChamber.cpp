//
// Created by Vladimir on 15.05.2021.
//

#include "headers/EvolutionChamber.h"

void EvolutionChamber::setFitnessFunction(std::function<double(double)> fitnessFunction) {
    EvolutionChamber::fitnessFunction = fitnessFunction;
}

const double EvolutionChamber::executeFitnessFunction(double arg){
    return fitnessFunction.operator()(arg);
}

const std::function<double(double)> &EvolutionChamber::getFitnessFunction() const {
    return fitnessFunction;
}


Population *EvolutionChamber::selectionElite(Population *population, std::function<bool(int)> selectionCondition) {
    population->estimate(EvolutionChamber::getFitnessFunction());
    for(int i = 0; i < population->getIndividuals().size(); i++){
        if(!selectionCondition(population->getIndividualsEstimation().at(i))) {
            population->eject(i);
            i--;
        }
    }
    return population;
}

Population *EvolutionChamber::selectionElite(Population *population, std::function<double(double)> fitnessFunction,
                                             std::function<bool(int)> selectionCondition) {
    population->estimate(fitnessFunction);
    for(int i = 0; i < population->getIndividuals().size(); i++){
        if(!selectionCondition(population->getIndividualsEstimation().at(i))) {
            population->eject(i);
            i--;
        }
    }
    return population;
}
