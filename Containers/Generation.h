//
// Created by Vladimir on 15.05.2021.
//

#ifndef GENETIC_ALGS_GENERATION_H
#define GENETIC_ALGS_GENERATION_H

#include <vector>
#include <map>
#include <ostream>
#include <functional>
#include "Chromosome.h"

class Generation {
private:
    int uniqueIdentifier;
    int index;
    std::vector<Chromosome*> individuals;
    std::vector<double> estimations;

public:

    Generation(Generation* anotherPopulation);
    Generation(int index);
    Generation(std::vector<Chromosome *> &individuals);

    virtual ~Generation();

    std::vector<Chromosome *> &getIndividuals();
    void setIndividuals(const std::vector<Chromosome *> &individuals);

    void add(Chromosome* ind);

    int getUniqueIdentifier() const;

    int getIndex() const;
    void setIndex(int index);

    std::string getIndividualsAsDecimalsString();
    std::string getIndividualsAsBinariesString();

    void printout();

    void add(Generation* generation);

    Chromosome* get(int index);
    int size();
    void set(int index, Chromosome* chromosome);
    Chromosome* eject(int index);
    void eject(Chromosome* individual);

    bool operator==(const Generation &rhs) const;
    bool operator!=(const Generation &rhs) const;

    void statPrintout();

    template<typename R> void foreach(std::function<R(Chromosome*)> transformation);
    void foreach(std::function<int(int)> decimalTransformation);
    void Generation::foreach(std::function<Chromosome*(Chromosome*)> transformation);
    void Generation::foreach(std::function<void(Chromosome*)> transformation);


    void Generation::reduce(std::function<bool(Chromosome*)> condition);
    void Generation::reduce(std::function<bool(double)> condition);

    void estimate(std::function<double(double)> estimationFunction);

    void printoutEstimation();

    const std::vector<double> &getEstimation() const;
    double getEstimation(int index);

    void setIndividualsEstimation(const std::vector<double> &individualsEstimation);

    Chromosome* getRandomIndividual();

    Generation* copy();

    static double getMinNormalizedHammingDistance(Generation* generation);
    static double getMaxNormalizedHammingDistance(Generation* generation);

    Chromosome* first();
    Chromosome* last();
    Chromosome* getWithMaxEstimation(std::function<double(double)> estimationFunction);

    bool contains(Chromosome* chromosome);

    void reduceToUnique();

};


#endif //GENETIC_ALGS_GENERATION_H
