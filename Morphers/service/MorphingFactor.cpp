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

    std::vector<int> fibNumbers = fibbonachi(parentA->getSize());
    std::vector<std::vector<bool>> binaryTable = makeBinaryNumbersTable(parentA->getSize()); //A->0, B->1

    std::vector<BinaryChromosome *> partsParentA = makeParentParts(parentA, fibNumbers.size());
    std::vector<BinaryChromosome *> partsParentB = makeParentParts(parentB, fibNumbers.size());

    std::vector<BinaryChromosome *> children;
    for (int i = 1; i < binaryTable.size() - 1; i++) {
        BinaryChromosome *child = new BinaryChromosome();

        //making a child from binary-table row: A->0, B->1
        for (int j = 0; j < parentA->getSize() - 1; j++) {

            if (binaryTable[i][j] == 0)
                child->glue(partsParentA.at(j));
            else child->glue(partsParentB.at(j));
        }
        if (children.empty())
            children.push_back(child);
        bool childAdded= 0;
        for (int k = 0; k < children.size(); k++) {
            for (int j = 0; j < child->getSize(); j++)
                if (children.at(k)->getGen(j) != child->getGen(j)) {
                    children.push_back(child);
                    childAdded = 1;
                    break;
                }
        if (childAdded) break;
        }
    }
    return new Generation(children);
}

std::vector<int> MorphingFactor::fibbonachi(int howMuchNumbers) {
    int a1 = 1, a2 = 1;
    std::vector<int> fib;
    fib.push_back(a1);
    while (fib.size() < howMuchNumbers) {
        int t = a2;
        a2 += a1;
        a1 = t;
        fib.push_back(a2);
    }
    return fib;
}

int MorphingFactor::getSingleFibonacci(int numberToCover) {
    int a1 = 1, a2 = 1;
    while (a2 < numberToCover) {
        int temp = a2;
        a2 += a1;
        a1 = temp;
    }
    return a2;
}

std::vector<std::vector<bool>> MorphingFactor::makeBinaryNumbersTable(int n) {
    int rowsAmount = pow(2, n);
    std::vector<std::vector<bool>> table;
    for (int i = 0; i < rowsAmount; i++) {
        std::vector<bool> row;
        int temp_i = i;
        do {
            row.push_back(temp_i % 2);
            temp_i /= 2;
        } while (temp_i > 0);

        while (row.size() < n)
            row.push_back(0);

        std::reverse(row.begin(), row.end());
        table.push_back(row);
    }
    return table;
}

std::vector<BinaryChromosome *> MorphingFactor::makeParentParts(BinaryChromosome *parent, int n) {
    int t = 1;
    while (n > getSingleFibonacci(t)) { t++; }
    std::vector<int> fibNumbers = fibbonachi(t);
    std::vector<BinaryChromosome *> parentParts;

    //separately push first(left) part
    parentParts.push_back(new BinaryChromosome(std::vector<bool>(1, parent->get().at(0))));

    for (int i = 0; i < fibNumbers.size() - 1; i++) {
        BinaryChromosome *tempChromosome = parent->getSubsequence(fibNumbers.at(i), fibNumbers.at(i + 1) - 1);
        parentParts.push_back(tempChromosome);
    }

    //separately push last(right) part
    BinaryChromosome *tempChromosome = parent->getSubsequence(fibNumbers.back(), parent->get().size() - 1);
    if (!tempChromosome->get().empty()) parentParts.push_back(tempChromosome);

    return parentParts;
}



