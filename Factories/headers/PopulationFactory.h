//
// Created by Vladimir on 15.05.2021.
//

#ifndef GENETIC_ALGS_POPULATIONFACTORY_H
#define GENETIC_ALGS_POPULATIONFACTORY_H

#include "../../Entities/headers/Population.h"

class PopulationFactory {
public:
    static Population* getPopulationUsingShotgun();

    static Population* getPopulationUsingFocusing();
};


#endif //GENETIC_ALGS_POPULATIONFACTORY_H
