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

BinaryChromosome* Mutation::simple(BinaryChromosome* individual, int index) {
    individual->setGen(index, !individual->getGen(index));
    return individual;
}

BinaryChromosome* Mutation::simple(BinaryChromosome* individual) {
    return Mutation::simple(individual, std::rand() % individual->size());
}

BinaryChromosome* Mutation::inversion(BinaryChromosome* individual, int startIndex, int endIndex){
    individual->reverse(startIndex, endIndex);
    return individual;
}

BinaryChromosome* Mutation::transpose(BinaryChromosome* individual, int startIndex, int endIndex) {
    BinaryChromosome *erased = individual->erase(startIndex, endIndex);
    individual->insert(std::rand() % individual->size(), erased);
    return individual;
}

///RANDOM BASED FUNCTIONS

BinaryChromosome* Mutation::inversion(BinaryChromosome* individual) {
    std::pair<int, int> pos = getRandIndexCouple(individual->size());
    return Mutation::inversion(individual, pos.first, pos.second);
}

BinaryChromosome* Mutation::swap(BinaryChromosome* individual, int aGenIndex, int bGenIndex){
    individual->swap(aGenIndex, bGenIndex);
    return individual;
}

BinaryChromosome* Mutation::swapFibonacci(BinaryChromosome* individual) {
    int a = Maths::fibonacci(std::rand());
    int b = Maths::fibonacci(std::rand());
    while (b == a) b = Maths::fibonacci(std::rand());

    Mutation::swap(individual, a, b);
    return individual;
}

BinaryChromosome* Mutation::transpose(BinaryChromosome* individual) {
    std::pair<int, int> pos = getRandIndexCouple(individual->size());
    return transpose(individual, pos.first, pos.second);
}

