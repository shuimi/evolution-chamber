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

    Generation *morph(Generation *generation);

    static Generation *crossoverTwoPoint(BinaryChromosome *, BinaryChromosome *);

    static Generation *crossoverCycle(BinaryChromosome *, BinaryChromosome *);

    static Generation *crossoverFibonacci(BinaryChromosome *, BinaryChromosome *);

    static Generation *crossoverPartlyOrdered(BinaryChromosome *, BinaryChromosome *);

    static Generation *crossoverOrdered(BinaryChromosome *, BinaryChromosome *);

    static Generation *GoldenRatio(BinaryChromosome *, BinaryChromosome *);

    static Generation *mutateSwapFibonacci(BinaryChromosome *);

    static Generation *mutateInversion(BinaryChromosome *);

    static Generation *mutateSimple(BinaryChromosome *);

    static Generation *mutateTransposition(BinaryChromosome *);

    static std::vector<int> fibbonachi(int n);
    static int getSingleFibonacci(int n);

    //has 0 and last rows
    static std::vector<std::vector<bool>> makeBinaryNumbersTable(int n);

    static std::vector<BinaryChromosome *> makeParentParts(BinaryChromosome *parentA, int n);
};


#endif //GENETIC_ALGS_MORPHINGFACTOR_H
