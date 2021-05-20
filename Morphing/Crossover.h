//
// Created by Vladimir on 15.05.2021.
//

#ifndef GENETIC_ALGS_CROSSOVER_H
#define GENETIC_ALGS_CROSSOVER_H


#include "../Entities/Generation.h"

class Crossover {
private:

    static std::vector<int> getFibonacciVector(
        int numbersAmount
    );

    static std::vector<std::vector<bool>> makeBinaryNumbersTable(
        int n
    );

    static std::vector<BinaryChromosome *> makeParentParts(
        BinaryChromosome *parentA,
        int n
    );

    static int getGoldenRatioSeparationPoint(
        int l,
        int r,
        double error
    );

    static short indexOfValueInsideChromosome(
        int l,
        int r,
        std::vector<short> c,
        short valueToFind
    );

    static int insertAppropriateValueChildA(
        std::vector<short> parentA,
        std::vector<short> parentB,
        int indexParentB,
        int separationPoint
    );

    static int insertAppropriateValueChildB(
        std::vector<short> parentA,
        std::vector<short> parentB,
        int idxParentB,
        int separationPoint
    );

public:

    static Generation* doublePoint(
        BinaryChromosome* parentA,
        BinaryChromosome* parentB
    );

    static Generation* CX(
        BinaryChromosome* parentA,
        BinaryChromosome* parentB
    );

    static Generation* fibonacci(
        BinaryChromosome* parentA,
        BinaryChromosome* parentB
    );

    static Generation* PMX(
        BinaryChromosome* parentA,
        BinaryChromosome* parentB
    );

    static Generation* OX(
        BinaryChromosome* parentA,
        BinaryChromosome* parentB
    );

    static Generation *goldenRatio(
        BinaryChromosome* parentA,
        BinaryChromosome* parentB,
        double errorThreshold
    );

};

#endif //GENETIC_ALGS_CROSSOVER_H
