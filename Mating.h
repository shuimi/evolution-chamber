//
// Created by Vladimir on 23.05.2021.
//

#ifndef GENETIC_ALGS_MATING_H
#define GENETIC_ALGS_MATING_H


#include "Containers/Generation.h"

class Mating {
private:
    double crossProbability;
    double mutationProbability;

    /// static Generation* XXX(Chromosome*, Chromosome*) is standard declaration
    /// which is required to use Mating

    /// static Chromosome* XXX(Chromosome*) is standard declaration
    /// which is required to use Mating

    std::vector<std::function<Generation*(Chromosome*, Chromosome*)>> crossOperators;
    std::vector<std::function<Chromosome*(Chromosome*)>> mutationOperators;

public:
    Mating(double crossProbability, double mutationProbability);

    Mating(double crossProbability, double mutationProbability,
           const std::vector<std::function<Generation *(Chromosome *, Chromosome *)>> &crossOperators,
           const std::vector<std::function<Chromosome *(Chromosome *)>> &mutationOperators);

    double getCrossProbability() const;

    void setCrossProbability(double crossProbability);

    double getMutationProbability() const;

    void setMutationProbability(double mutationProbability);

    void add(std::function<Generation*(Chromosome*, Chromosome*)> crossOperator);
    void add(std::function<Chromosome*(Chromosome*)> mutationOperator);

    Generation* execute(Generation* generation);

};


#endif //GENETIC_ALGS_MATING_H
