//
// Created by Vladimir on 23.05.2021.
//

#include "Mating.h"

Mating::Mating(double crossProbability, double mutationProbability) : crossProbability(crossProbability),
                                                                      mutationProbability(mutationProbability) {}

double Mating::getCrossProbability() const {
    return crossProbability;
}

void Mating::setCrossProbability(double crossProbability) {
    Mating::crossProbability = crossProbability;
}

double Mating::getMutationProbability() const {
    return mutationProbability;
}

void Mating::setMutationProbability(double mutationProbability) {
    Mating::mutationProbability = mutationProbability;
}

Mating::Mating(double crossProbability, double mutationProbability,
               const std::vector<std::function<Generation *(Chromosome *, Chromosome *)>> &crossOperators,
               const std::vector<std::function<Chromosome *(Chromosome *)>> &mutationOperators) : crossProbability(
        crossProbability), mutationProbability(mutationProbability), crossOperators(crossOperators), mutationOperators(
        mutationOperators) {}

void Mating::add(std::function<Generation *(Chromosome *, Chromosome *)> crossOperator) {
    Mating::crossOperators.push_back(crossOperator);
}

void Mating::add(std::function<Chromosome *(Chromosome *)> mutationOperator) {
    Mating::mutationOperators.push_back(mutationOperator);
}

Generation *Mating::execute(Generation *generation) {

    int crossOperatorsAmount = Mating::crossOperators.size();
    int mutationOperatorsAmount = Mating::mutationOperators.size();

    Generation* result = new Generation(generation->getIndex());

    for(int i = 0; i < generation->size(); i++){
        Chromosome* A = generation->get(i);
        for(int j = i + 1; j < generation->size(); j++){
            Chromosome* B = generation->get(j);
            //pairing any couples from source set, by chance
            if(A != B){

                //random pairing
                if(rand() % 1000 < Mating::crossProbability * 1000){

                    //random cross operator choice
                    result->add(
                        Mating::crossOperators.at(
                            rand() % crossOperatorsAmount
                        )(A, B)
                    );

                }

            }
            result->printout();
        }
    }

    //random mutation
    for(Chromosome* A : result->getIndividuals()){
        if(rand() % 1000 < Mating::mutationProbability * 1000){
            Mating::mutationOperators.at(rand() % mutationOperatorsAmount)(A);
        }
    }

    return result;
}
