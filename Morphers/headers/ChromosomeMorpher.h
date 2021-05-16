//
// Created by Vladimir on 15.05.2021.
//

#ifndef GENETIC_ALGS_CHROMOSOMEMORPHER_H
#define GENETIC_ALGS_CHROMOSOMEMORPHER_H

//TODO:

#include "../../Entities/headers/BinaryChromosome.h"
#include "../service/MorphingFactor.h"

class ChromosomeMorpher {
public:

    static std::tuple<BinaryChromosome*, BinaryChromosome*>
            crossoverTwoPoint(BinaryChromosome* parentA, BinaryChromosome* parentB);

    static BinaryChromosome*
            crossoverCycle(BinaryChromosome* parentA, BinaryChromosome* parentB);

    static BinaryChromosome*
            crossoverFibonacci(BinaryChromosome* parentA, BinaryChromosome* parentB);

    static BinaryChromosome*
            mutateSwapFibonacci(BinaryChromosome* parentA, MorphingFactor* factor);

    static BinaryChromosome*
            mutateInversion(BinaryChromosome* parentA, MorphingFactor* factor);

};


#endif //GENETIC_ALGS_CHROMOSOMEMORPHER_H
