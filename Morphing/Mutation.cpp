//
// Created by Vladimir on 20.05.2021.
//

#include "Mutation.h"
#include "../Service/Maths.h"

///SERVICE FUNCTIONS

std::pair<int, int> Mutation::getRandIndexCouple(int chromosomeSize) {
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
    std::pair<int, int> pos = getRandIndexCouple(individual->size());
    return Mutation::inversion_(individual, pos.first, pos.second);
}

Chromosome* Mutation::swap(Chromosome* individual, int aGenIndex, int bGenIndex){
    individual->swap(aGenIndex, bGenIndex);
    return individual;
}

Chromosome* Mutation::swapFibonacci(Chromosome* individual) {
    int a = Maths::fibonacci(std::rand());
    int b = Maths::fibonacci(std::rand());
    while (b == a) b = Maths::fibonacci(std::rand());

    Mutation::swap(individual, a, b);
    return individual;
}

Chromosome* Mutation::transpose(Chromosome* individual) {
    std::pair<int, int> pos = getRandIndexCouple(individual->size());
    return transpose_(individual, pos.first, pos.second);
}

