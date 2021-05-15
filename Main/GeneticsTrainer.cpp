//
// Created by Vladimir on 15.05.2021.
//

#include "headers/GeneticsTrainer.h"

void GeneticsTrainer::setFitnessFunction(std::function<double(double)> fitnessFunction) {
    GeneticsTrainer::fitnessFunction = fitnessFunction;
}

const double GeneticsTrainer::executeFitnessFunction(double arg){
    return fitnessFunction.operator()(arg);
}

double getGenSetDecimal();

void setGenSetDecimal(double genSet);
