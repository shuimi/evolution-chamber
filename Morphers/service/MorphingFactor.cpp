//
// Created by Vladimir on 15.05.2021.
//

#include "MorphingFactor.h"


Generation *MorphingFactor::morph(Generation *generation) {
    return nullptr;
}

MorphingFactor::MorphingFactor(double crossProbability, double mutationProbability) :
        crossProbability(crossProbability), mutationProbability(mutationProbability) {}

Generation *MorphingFactor::crossoverTwoPoint(BinaryChromosome *parentA, BinaryChromosome *parentB) {
    BinaryChromosome::complementChromosome(parentA, parentB);
    int leftBarrier = rand() % parentA->get().size();
    int rightBarrier = rand() % parentA->get().size();

    while (rightBarrier <= leftBarrier)
        rightBarrier = rand() % parentA->get().size();

    std::vector<bool> childGen1, childGen2, childGen3, childGen4, childGen5, childGen6;
    for (int i = 0; i < leftBarrier; i++) {
        childGen1.push_back(parentA->get().at(i));
        childGen2.push_back(parentA->get().at(i));
        childGen3.push_back(parentA->get().at(i));
        childGen4.push_back(parentB->get().at(i));
        childGen5.push_back(parentB->get().at(i));
        childGen6.push_back(parentB->get().at(i));
    }
    for (int i = leftBarrier; i < rightBarrier; i++) {
        childGen1.push_back(parentA->get().at(i));
        childGen2.push_back(parentB->get().at(i));
        childGen3.push_back(parentB->get().at(i));
        childGen4.push_back(parentA->get().at(i));
        childGen5.push_back(parentA->get().at(i));
        childGen6.push_back(parentB->get().at(i));
    }
    for (int i = rightBarrier; i < parentA->get().size(); i++) {
        childGen1.push_back(parentB->get().at(i));
        childGen2.push_back(parentA->get().at(i));
        childGen3.push_back(parentB->get().at(i));
        childGen4.push_back(parentA->get().at(i));
        childGen5.push_back(parentB->get().at(i));
        childGen6.push_back(parentA->get().at(i));
    }
    BinaryChromosome *child1 = new BinaryChromosome(childGen1);
    BinaryChromosome *child2 = new BinaryChromosome(childGen2);
    BinaryChromosome *child3 = new BinaryChromosome(childGen3);
    BinaryChromosome *child4 = new BinaryChromosome(childGen4);
    BinaryChromosome *child5 = new BinaryChromosome(childGen5);
    BinaryChromosome *child6 = new BinaryChromosome(childGen6);

    std::vector<BinaryChromosome *> g;
    g.push_back(child1);
    g.push_back(child2);
    g.push_back(child3);
    g.push_back(child4);
    g.push_back(child5);
    g.push_back(child6);
    return new Generation(g);
}

Generation *MorphingFactor::crossoverFibonacci(BinaryChromosome *parentA, BinaryChromosome *parentB) {
    BinaryChromosome::complementChromosome(parentA, parentB);
    std::vector<int> fibNumbers = fibbonachi(parentA->get().size());
    std::vector<BinaryChromosome *> partsParentA = makeParentParts(parentA, fibNumbers.size());
    std::vector<BinaryChromosome *> partsParentB = makeParentParts(parentB, fibNumbers.size());

    //make confornity of parts and binary table without 0 and last rows
    std::vector<BinaryChromosome *> children;
    for (int i = 0; i < fibNumbers.size(); i++) {
        BinaryChromosome *child = new BinaryChromosome();
        for (int j = 0; j < parentA->get().size(); j++) {

        }
        children.push_back();
    }

}

std::vector<int> MorphingFactor::fibbonachi(int n) {
    int a1 = 1, a2 = 1;
    std::vector<int> fib;
    fib.push_back(a1);
    while (a2 < n) {
        int t = a2;
        a2 += a1;
        a1 = t;
        fib.push_back(a1);
        fib.push_back(a2);
    }
    return fib;
}

std::vector<std::vector<bool>> MorphingFactor::makeBinaryNumbersTable(int n) {
    int rowsAmount = pow(2, n);
    std::vector<std::vector<bool>> table;
    for (int i = 0; i < rowsAmount; i++) {
        std::vector<bool> row;
        int temp_i = i;
        for (int j = 0; j < n; j++) {
            row.push_back(temp_i % 2);
            temp_i / 2;
        }
        std::reverse(row.begin(), row.end());
        table.push_back(row);
    }
    return table;
}

std::vector<BinaryChromosome *> MorphingFactor::makeParentParts(BinaryChromosome *parent, int n) {
    std::vector<int> fibNumbers = fibbonachi(n);
    std::vector<BinaryChromosome *> parentParts;
    parentParts.push_back(new BinaryChromosome(std::vector<bool>(1, 1)));
    for (int i = 0; i < fibNumbers.size() - 1; i++) {
        std::vector<bool> tempGen;
        for (int j = fibNumbers.at(i); j < fibNumbers.at(i + 1); j++) {
            tempGen.push_back(parent->get().at(j));
        }
        parentParts.push_back(new BinaryChromosome(tempGen));
    }

    std::vector<bool> tempGen;
    for (int i = fibNumbers.at(fibNumbers.size()); i < parent->get().size(); i++) {
        tempGen.push_back(parent->get().at(i));
    }
    parentParts.push_back(new BinaryChromosome(tempGen));

    return parentParts;
}


