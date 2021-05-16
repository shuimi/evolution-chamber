//
// Created by Vladimir on 15.05.2021.
//

#include "MorphingFactor.h"


Generation *MorphingFactor::morph(Generation *generation) {
    return nullptr;
}

MorphingFactor::MorphingFactor(double crossProbability, double mutationProbability) :
crossProbability(crossProbability), mutationProbability(mutationProbability) {}

BinaryChromosome *MorphingFactor::mutateSimple(BinaryChromosome *individual) {
    int index = std::rand() % individual->getSize();
    individual->setGen(index, !individual->getGen(index));
    return individual;
}

BinaryChromosome *MorphingFactor::mutateInversion(BinaryChromosome *individual) {
    int startIndex = std::rand() % individual->getSize();
    int endIndex = std::rand() % individual->getSize();
    individual->reverse(startIndex, endIndex);
    return individual;
}

BinaryChromosome *MorphingFactor::mutateSwapFibonacci(BinaryChromosome *individual) {
    int a = MorphingFactor::fibonacci(std::rand());
    int b = MorphingFactor::fibonacci(std::rand());
    while (b == a) b = MorphingFactor::fibonacci(std::rand());
    individual->swap(a, b);
    return individual;
}
