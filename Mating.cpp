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
               const std::vector<crossFunction> &crossOperators,
               const std::vector<mutationFunction> &mutationOperators) : crossProbability(
        crossProbability), mutationProbability(mutationProbability), crossOperators(crossOperators), mutationOperators(
        mutationOperators) {}

void Mating::add(crossFunction crossOperator) {
    Mating::crossOperators.push_back(crossOperator);
}

void Mating::add(mutationFunction mutationOperator) {
    Mating::mutationOperators.push_back(mutationOperator);
}

Generation *Mating::executeForAll(Generation *generation) {

    int crossOperatorsAmount = Mating::crossOperators.size();
    int mutationOperatorsAmount = Mating::mutationOperators.size();

    Generation* result = new Generation(generation->getIndex());

    if(!Mating::crossOperators.empty())
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
        }
    }

    //random mutation
    if(!Mating::mutationOperators.empty())
    for(Chromosome* A : result->getIndividuals()){
        if(rand() % 1000 < Mating::mutationProbability * 1000){
            Mating::mutationOperators.at(rand() % mutationOperatorsAmount)(A);
        }
    }

    return result;
}

Generation *Mating::executeSingle(Generation *generation) {

    if(generation->size() < 2) throw "MATING CALLED FOR GENERATION WITH LESS THAN 2 INDIVIDUALS";

    int crossOperatorsAmount = Mating::crossOperators.size();
    int mutationOperatorsAmount = Mating::mutationOperators.size();

    std::tuple<Chromosome*, Chromosome*> pair = Breeding::selectRandomPair(generation);

    Generation* result = generation->copy();

    if(!Mating::crossOperators.empty()){
        if(rand() % 1000 < Mating::crossProbability * 1000){

            //random cross operator choice
            result->add(
                Mating::crossOperators.at(
                    rand() % crossOperatorsAmount
                )(std::get<0>(pair), std::get<1>(pair))
            );
        }
    }
    //random mutation
    if(!Mating::mutationOperators.empty())
        for(Chromosome* A : result->getIndividuals()){
            if(rand() % 1000 < Mating::mutationProbability * 1000){
                if(A->getDecimal() >= 2)
                    Mating::mutationOperators.at(rand() % mutationOperatorsAmount)(A);
            }
        }

    return result;
}


void Mating::add(std::vector<crossFunction> crossOperators) {
    for(std::function<Generation *(Chromosome *, Chromosome *)> function : crossOperators){
        Mating::add(function);
    }
}

void Mating::add(std::vector<mutationFunction> mutationOperators) {
    for(std::function<Chromosome *(Chromosome *)> function : mutationOperators){
        Mating::add(function);
    }
}

