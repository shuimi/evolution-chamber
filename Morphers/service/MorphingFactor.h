//
// Created by Vladimir on 15.05.2021.
//

#ifndef GENETIC_ALGS_MORPHINGFACTOR_H
#define GENETIC_ALGS_MORPHINGFACTOR_H


#include "../../Entities/headers/Generation.h"

class MorphingFactor {
private:
    double crossProbability;
    double mutationProbability;

public:

    MorphingFactor(double crossProbability, double mutationProbability);

    Generation* morph(Generation* generation);

    static std::function
            <Generation*(BinaryChromosome*, BinaryChromosome*)> crossoverTwoPoint;

    static std::function
            <Generation*(BinaryChromosome*, BinaryChromosome*)> crossoverCycle;

    static std::function
            <Generation*(BinaryChromosome*, BinaryChromosome*)> crossoverFibonacci;

    static std::function
            <BinaryChromosome*(BinaryChromosome* individual)> mutateSwapFibonacci;

    static std::function
            <BinaryChromosome*(BinaryChromosome* individual)> mutateInversion;

};


#endif //GENETIC_ALGS_MORPHINGFACTOR_H
