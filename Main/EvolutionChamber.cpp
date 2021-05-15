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

double getGenSetDecimal();

void setGenSetDecimal(double genSet);
