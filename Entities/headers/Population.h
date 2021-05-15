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
    int uniqueIdentifier;
    int index;
    std::vector<BinaryChromosome*> individuals;

public:

    Population(Population* anotherPopulation);
    Population(int index);
    Population(const std::vector<BinaryChromosome *> &individuals);

    virtual ~Population();

    std::vector<BinaryChromosome *> &getIndividuals();
    void setIndividuals(const std::vector<BinaryChromosome *> &individuals);

    void addIndividual(BinaryChromosome* ind);

    int getUniqueIdentifier() const;

    int getIndex() const;
    void setIndex(int index);

    const std::string getIndividualsAsDecimalsString();
    const std::string getIndividualsAsBinariesString();

    void printout();

    BinaryChromosome* get(int index);
    void set(int index, BinaryChromosome* chromosome);

    bool operator==(const Population &rhs) const;
    bool operator!=(const Population &rhs) const;
};


#endif //GENETIC_ALGS_POPULATION_H
