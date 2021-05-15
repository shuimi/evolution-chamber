//
// Created by Vladimir on 15.05.2021.
//

#ifndef GENETIC_ALGS_POPULATIONMORPHER_H
#define GENETIC_ALGS_POPULATIONMORPHER_H

#include "../../Entities/headers/Population.h"

class PopulationMorpher {
public:
    //TODO: think about to rename class to PopulationFactory
    //TODO: or add all classes with responsibility to morph populations to PopulationMorpher as fields
    //TODO: and implement common scenarios

    static Population* getPopulationUsingShotgun();

    static Population* getPopulationUsingFocusing();

};


#endif //GENETIC_ALGS_POPULATIONMORPHER_H
