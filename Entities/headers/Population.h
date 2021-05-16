//
// Created by Vladimir on 15.05.2021.
//

#ifndef GENETIC_ALGS_POPULATION_H
#define GENETIC_ALGS_POPULATION_H

#include <vector>
#include <map>
#include <ostream>
#include <functional>
#include "BinaryChromosome.h"

class Population {
private:
    int uniqueIdentifier;
    int index;
    std::vector<BinaryChromosome*> individuals;
    std::vector<int> individualsEstimation;

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

    std::string getIndividualsAsDecimalsString();
    std::string getIndividualsAsBinariesString();

    void printout();

    BinaryChromosome* get(int index);
    void set(int index, BinaryChromosome* chromosome);
    BinaryChromosome* eject(int index);

    bool operator==(const Population &rhs) const;
    bool operator!=(const Population &rhs) const;

    void statPrintout();

    void foreach(std::function<int(int)> decimalTransformation);

    void estimate(std::function<double(double)> fitnessFunction);

    void printoutEstimation();

    const std::vector<int> &getIndividualsEstimation() const;

    void setIndividualsEstimation(const std::vector<int> &individualsEstimation);

};


#endif //GENETIC_ALGS_POPULATION_H
