//
// Created by Vladimir on 15.05.2021.
//

#ifndef GENETIC_ALGS_CROSSOVER_H
#define GENETIC_ALGS_CROSSOVER_H


#include "../Containers/Generation.h"

class Crossover {
private:

    constexpr static const double STANDARD_GOLDEN_RATIO_ERROR_THRESHOLD = 0.3;

    static std::vector<int> getFibonacciVector(
        int numbersAmount
    );

    static std::vector<std::vector<bool>> makeBinaryNumbersTable(
        int n
    );

    static std::vector<Chromosome *> makeParentParts(
        Chromosome *parentA,
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

    /// static Generation* XXX(Chromosome*, Chromosome*) is standard declaration
    /// which is required to use Mating

    static Generation* doublePoint(
        Chromosome* parentA,
        Chromosome* parentB
    );

    static Generation* CX(
        Chromosome* parentA,
        Chromosome* parentB
    );

    static Generation* fibonacci(
        Chromosome* parentA,
        Chromosome* parentB
    );

    static Generation* PMX(
        Chromosome* parentA,
        Chromosome* parentB
    );

    static Generation* OX(
        Chromosome* parentA,
        Chromosome* parentB
    );

    static Generation *goldenRatio(
        Chromosome* parentA,
        Chromosome* parentB,
        double errorThreshold
    );

    static Generation *goldenRatio(
            Chromosome* parentA,
            Chromosome* parentB
    );

};

#endif //GENETIC_ALGS_CROSSOVER_H
