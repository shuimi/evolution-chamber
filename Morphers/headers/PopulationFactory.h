//
// Created by Vladimir on 15.05.2021.
//

#ifndef GENETIC_ALGS_POPULATIONFACTORY_H
#define GENETIC_ALGS_POPULATIONFACTORY_H

#include "../../Entities/headers/Population.h"
#include <random>

class PopulationFactory {
public:
    //TODO: think about to rename class to PopulationFactory
    //TODO: or add all classes with responsibility to morph populations to PopulationFactory as fields
    //TODO: and implement common scenarios

    static Population* getPopulationUsingShotgun(int leftBound, int rightBound, int individualsAmount);

    static Population* getPopulationUsingFocusing(int focusPoint, int range, int individualsAmount);

    static Population* getPopulationUsingShotgun(int leftBound, int rightBound,
                                                 int individualsAmount, int initPopulationIndex);

    static Population* getPopulationUsingFocusing(int focusPoint, int range, int individualsAmount,
                                                  int initPopulationIndex);


};


#endif //GENETIC_ALGS_POPULATIONFACTORY_H
