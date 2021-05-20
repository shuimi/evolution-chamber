//
// Created by Vladimir on 15.05.2021.
//

#ifndef GENETIC_ALGS_GENERATIONFACTORY_H
#define GENETIC_ALGS_GENERATIONFACTORY_H

#include "../Entities/Generation.h"
#include <random>

class GenerationFactory {
public:

    static Generation* getUsingCovering(
        int leftBound,
        int rightBound,
        int initIndex
    );

    static Generation* getUsingCovering(
        int leftBound,
        int rightBound
    );

    static Generation* getUsingShotgun(
        int leftBound,
        int rightBound,
        int individualsAmount
    );

    static Generation* getUsingFocusing(
        int focusPoint,
        int range,
        int individualsAmount
    );

    static Generation* getUsingShotgun(
        int leftBound,
        int rightBound,
        int individualsAmount,
        int initIndex
    );

    static Generation* getUsingFocusing(
        int focusPoint,
        int range,
        int individualsAmount,
        int initIndex
    );
};


#endif //GENETIC_ALGS_GENERATIONFACTORY_H
