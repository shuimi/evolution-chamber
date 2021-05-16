//
// Created by Vladimir on 15.05.2021.
//

#ifndef GENETIC_ALGS_GENERATIONFACTORY_H
#define GENETIC_ALGS_GENERATIONFACTORY_H

#include "../../Entities/headers/Generation.h"
#include <random>

class GenerationFactory {
public:
    //TODO: think about to rename class to GenerationFactory
    //TODO: or add all classes with responsibility to morph populations to GenerationFactory as fields
    //TODO: and implement common scenarios

    static Generation* getPopulationUsingShotgun(int leftBound, int rightBound, int individualsAmount);

    static Generation* getPopulationUsingFocusing(int focusPoint, int range, int individualsAmount);

    static Generation* getPopulationUsingShotgun(int leftBound, int rightBound,
                                                 int individualsAmount, int initPopulationIndex);

    static Generation* getPopulationUsingFocusing(int focusPoint, int range, int individualsAmount,
                                                  int initPopulationIndex);


};


#endif //GENETIC_ALGS_GENERATIONFACTORY_H
