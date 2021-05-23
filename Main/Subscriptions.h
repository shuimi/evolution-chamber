//
// Created by Vladimir on 23.05.2021.
//



#ifndef GENETIC_ALGS_SUBSCRIPTIONS_H
#define GENETIC_ALGS_SUBSCRIPTIONS_H

#include <functional>
#include "../Containers/Chromosome.h"
#include "../Containers/Generation.h"

typedef std::function<Chromosome * (Chromosome *)> mutationFunction;
typedef std::function<Generation*(Chromosome*, Chromosome*)> crossFunction;

#endif //GENETIC_ALGS_SUBSCRIPTIONS_H
