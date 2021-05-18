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

    static int fibonacci(int number) {
        if (number == 0) return 0;
        if (number == 1) return 1;
        return fibonacci(number - 1) + fibonacci(number - 2);
    }

public:

    MorphingFactor(double crossProbability, double mutationProbability);


    Generation *morph(Generation *generation);

    static Generation *crossTwoPoint(BinaryChromosome *, BinaryChromosome *);

    //TODO: crossCX
    static Generation *crossCX(BinaryChromosome *, BinaryChromosome *);

    static Generation *crossFibonacci(BinaryChromosome *, BinaryChromosome *);

    //TODO: crossPMX
    static Generation *crossPMX(BinaryChromosome *, BinaryChromosome *);

    //TODO: crossOX
    static Generation *crossOX(BinaryChromosome *, BinaryChromosome *);

    //TODO: crossGoldenRatio
    static Generation *crossGoldenRatio(BinaryChromosome *, BinaryChromosome *);


    static BinaryChromosome *mutateSwapFibonacci(BinaryChromosome *individual);

    static BinaryChromosome *mutateInversion(BinaryChromosome *individual);

    static BinaryChromosome *mutateSimple(BinaryChromosome *individual);

    static BinaryChromosome *mutateTranspose(BinaryChromosome *individual);


    static std::vector<int> getFibonacciVector(int numbersAmount);

    //has 0 and last rows
    static std::vector<std::vector<bool>> makeBinaryNumbersTable(int n);

    static std::vector<BinaryChromosome *> makeParentParts(BinaryChromosome *parentA, int n);

    static int getGoldenRatioSeparationPoint(int l, int r, double error);

};
#endif //GENETIC_ALGS_MORPHINGFACTOR_H
