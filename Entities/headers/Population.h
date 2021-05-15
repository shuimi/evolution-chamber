//
// Created by Vladimir on 15.05.2021.
//

#ifndef GENETIC_ALGS_POPULATION_H
#define GENETIC_ALGS_POPULATION_H

#include <vector>
#include <ostream>
#include "BinaryChromosome.h"

class Population {
private:
    int uniqueIndex;
    std::vector<BinaryChromosome*> individuals;

public:

    Population();

    Population(const std::vector<BinaryChromosome *> &individuals);

    virtual ~Population();

    const std::vector<BinaryChromosome *> &getIndividuals() const;

    void setIndividuals(const std::vector<BinaryChromosome *> &individuals);

    void addIndividual(BinaryChromosome* ind);

    friend std::ostream &operator<<(std::ostream &os, const Population &population);

    int getIndex() const;

    void setIndex(int index);

    bool operator==(const Population &rhs) const;

    bool operator!=(const Population &rhs) const;
};


#endif //GENETIC_ALGS_POPULATION_H
