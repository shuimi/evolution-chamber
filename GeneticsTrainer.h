//
// Created by Vladimir on 15.05.2021.
//
#include <functional>

#ifndef GENETIC_ALGS_GENETICSTRAINER_H
#define GENETIC_ALGS_GENETICSTRAINER_H


class GeneticsTrainer{
private:
    std::function<double(double)> fitnessFunction;

public:

    GeneticsTrainer(const std::function<double(double)> &fitnessFunction) : fitnessFunction(fitnessFunction) {}

    GeneticsTrainer() {}

    virtual ~GeneticsTrainer() {}

    void setFitnessFunction(std::function<double(double)> fitnessFunction);

    const double executeFitnessFunction(double arg);

};




class Population{
private:

public:


};


#endif //GENETIC_ALGS_GENETICSTRAINER_H
