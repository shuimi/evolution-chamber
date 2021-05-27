//
// Created by Vladimir on 20.05.2021.
//

#include "Mutation.h"
#include "../Service/Maths.h"

///SERVICE FUNCTIONS

std::pair<int, int> Mutation::getRandIndexCouple(int chromosomeSize) {
    if(chromosomeSize < 2) throw "UNABLE TO CHOOSE INDEX COUPLE IN SEQUENCE WITH LENGTH LESS THAN 2";
    int startIndex = std::rand() % (chromosomeSize - 1);
    int endIndex = std::rand() % chromosomeSize;
    while (startIndex >= endIndex) endIndex = std::rand() % chromosomeSize;
    return std::pair<int, int>(startIndex, endIndex);
}

///PURE FUNCTIONS

Chromosome* Mutation::simple_(Chromosome* individual, int index) {
    individual->setGen(index, !individual->getGen(index));
    return individual;
}

Chromosome* Mutation::inversion_(Chromosome* individual, int startIndex, int endIndex){
    individual->reverse(startIndex, endIndex);
    return individual;
}

Chromosome* Mutation::transpose_(Chromosome* individual, int startIndex, int endIndex) {
    Chromosome *erased = individual->erase(startIndex, endIndex);
    individual->insert(std::rand() % individual->size(), erased);
    return individual;
}

///RANDOM BASED FUNCTIONS

Chromosome* Mutation::simple(Chromosome* individual) {
    return Mutation::simple_(individual, std::rand() % individual->size());
}

Chromosome* Mutation::inversion(Chromosome* individual) {
    if(individual->size() < 2) throw "UNABLE TO INVERT CHROMOSOME WITH LENGTH LESS THAN 2";
    std::pair<int, int> pos = getRandIndexCouple(individual->size());
    return Mutation::inversion_(individual, pos.first, pos.second);
}

Chromosome* Mutation::swap(Chromosome* individual, int aGenIndex, int bGenIndex){
    individual->swap(aGenIndex, bGenIndex);
    return individual;
}

Chromosome* Mutation::swapFibonacci(Chromosome* individual) {

    int maxFibonacci = 0;
    for(int i = 0; i < individual->size() && Maths::fibonacci(i) < individual->size(); i++){
        maxFibonacci = i;
    }

    int a = Maths::fibonacci(std::rand() % (maxFibonacci - 1));
    int b = Maths::fibonacci(std::rand() % maxFibonacci);
    while (b == a) b = Maths::fibonacci(std::rand() % maxFibonacci);

    Mutation::swap(individual, a, b);
    return individual;
}

Chromosome* Mutation::transpose(Chromosome* individual) {
    if(individual->size() < 2) throw "UNABLE TO TRANSPOSE CHROMOSOME WITH LENGTH LESS THAN 2";
    std::pair<int, int> pos = getRandIndexCouple(individual->size());
    return transpose_(individual, pos.first, pos.second);
}

