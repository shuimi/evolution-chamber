//
// Created by Vladimir on 16.05.2021.
//

#ifndef GENETIC_ALGS_POPULATION_H
#define GENETIC_ALGS_POPULATION_H


#include "Generation.h"

class Population {
private:
    std::vector<Generation*> generations;
public:
    Population();
    Population(const std::vector<Generation *> &generations);

    virtual ~Population();

    std::vector<Generation *> &getGenerations();
    void setGenerations(const std::vector<Generation *> &generations);

    void foreach(std::function<void (Generation*)> decimalTransformation);

    void printout();

    Generation* get(int index);
    void set(int index, Generation* generation);
    void add(Generation* generation);
    Generation* eject(int index);
    void eject(Generation* generation);

    Generation* getAsGeneration();

};


#endif //GENETIC_ALGS_POPULATION_H
