//
// Created by Vladimir on 15.05.2021.
//

#ifndef GENETIC_ALGS_GENERATION_H
#define GENETIC_ALGS_GENERATION_H

#include <vector>
#include <map>
#include <ostream>
#include <functional>
#include "BinaryChromosome.h"

class Generation {
private:
    int uniqueIdentifier;
    int index;
    std::vector<BinaryChromosome*> individuals;
    std::vector<double> individualsEstimation;

public:

    Generation(Generation* anotherPopulation);
    Generation(int index);
    Generation(std::vector<BinaryChromosome *> &individuals);

    virtual ~Generation();

    std::vector<BinaryChromosome *> &getIndividuals();
    void setIndividuals(const std::vector<BinaryChromosome *> &individuals);

    void addIndividual(BinaryChromosome* ind);

    int getUniqueIdentifier() const;

    int getIndex() const;
    void setIndex(int index);

    std::string getIndividualsAsDecimalsString();
    std::string getIndividualsAsBinariesString();

    void printout();

    void add(Generation* generation);

    BinaryChromosome* get(int index);
    void set(int index, BinaryChromosome* chromosome);
    BinaryChromosome* eject(int index);
    void eject(BinaryChromosome* individual);

    bool operator==(const Generation &rhs) const;
    bool operator!=(const Generation &rhs) const;

    void statPrintout();

    void foreach(std::function<int(int)> decimalTransformation);
    void Generation::foreach(std::function<BinaryChromosome*(BinaryChromosome*)> transformation);
    void Generation::foreach(std::function<void(BinaryChromosome*)> transformation);

    void estimate(std::function<double(double)> fitnessFunction);

    void printoutEstimation();

    const std::vector<double> &getIndividualsEstimation() const;

    void setIndividualsEstimation(const std::vector<double> &individualsEstimation);

    BinaryChromosome* getRandomIndividual();

};


#endif //GENETIC_ALGS_GENERATION_H
