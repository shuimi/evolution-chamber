//
// Created by Vladimir on 15.05.2021.
//

#include <iostream>
#include "headers/BinaryChromosome.h"

int BinaryChromosome::getDecimal() {
    int rank = 1, result = 0;
    for (bool gen : BinaryChromosome::genes) {
        if (gen) result += rank;
        rank *= 2;
    }
    return result;
};

void BinaryChromosome::setDecimal(int genSetDec) {
    std::vector<bool> genSetBin;
    while (genSetDec != 0) {
        genSetBin.push_back(genSetDec % 2);
        genSetDec /= 2;
    }
    BinaryChromosome::genes = genSetBin;
}

BinaryChromosome::BinaryChromosome(const std::vector<bool> &genesVector) : genes(genesVector) {
    BinaryChromosome::uniqueIdentifier = reinterpret_cast<int>(this);
};

BinaryChromosome::BinaryChromosome(int genesDec) {
    BinaryChromosome::setDecimal(genesDec);
    BinaryChromosome::uniqueIdentifier = reinterpret_cast<int>(this);
}

BinaryChromosome::BinaryChromosome() {
    BinaryChromosome::setDecimal(0);
    BinaryChromosome::uniqueIdentifier = reinterpret_cast<int>(this);
};

BinaryChromosome::~BinaryChromosome() {

}

std::string BinaryChromosome::getBinaryString() {
    std::string output;
    for (bool gen : BinaryChromosome::genes) {
        output += std::to_string(gen);
    }
    //std::reverse(output.begin(), output.end());
    return output;
}

int BinaryChromosome::getUniqueIdentifier() const {
    return uniqueIdentifier;
}

void BinaryChromosome::set(const std::vector<bool> &genSet) {
    BinaryChromosome::genes = genSet;
}

std::vector<bool> &BinaryChromosome::get() {
    return BinaryChromosome::genes;
}

void BinaryChromosome::invert() {
    for (int i = 0; i < BinaryChromosome::genes.size(); i++) {
        BinaryChromosome::genes.at(i) = !BinaryChromosome::genes.at(i);
    }
}

void BinaryChromosome::printout() {
    std::cout << "C_" << BinaryChromosome::getUniqueIdentifier() << ":{DEC:";
    std::cout << BinaryChromosome::getDecimal() << ",BIN:";
    std::cout << BinaryChromosome::getBinaryString() << "}\n";
}

int BinaryChromosome::getHammingDistance(BinaryChromosome *A, BinaryChromosome *B) {

    int maxSize, minSize, amountOfEqualPositions = 0;

    A->get().size() > B->get().size() ? maxSize = A->get().size() : maxSize = B->get().size();
    A->get().size() < B->get().size() ? minSize = A->get().size() : minSize = B->get().size();

    for (int i = 0; i < minSize; i++) {
        A->get().at(i) != B->get().at(i) ? amountOfEqualPositions++ : 0;
    }

    if (A->get().size() > B->get().size())
        for (int i = minSize; i < maxSize; i++) {
            A->get().at(i) != false ? amountOfEqualPositions++ : 0;
        }
    else
        for (int i = minSize; i < maxSize; i++) {
            B->get().at(i) != false ? amountOfEqualPositions++ : 0;
        }

    return amountOfEqualPositions;
}

double BinaryChromosome::getNormalizedHammingDistance(BinaryChromosome *A, BinaryChromosome *B) {

    int hammingDist = BinaryChromosome::getHammingDistance(A, B);
    int maxSize;

    A->get().size() > B->get().size() ? maxSize = A->get().size() : maxSize = B->get().size();

    return (double) hammingDist / (double) maxSize;
}

BinaryChromosome BinaryChromosome::addZeroes(BinaryChromosome *A, int n) {
    BinaryChromosome &T = *A;
    for (int i = 0; i < n; i++)
        T.get().push_back(0);
    return T;
}

void BinaryChromosome::complementChromosome(BinaryChromosome *A, BinaryChromosome *B) {
    int n = A->get().size() - B->get().size();
    if (n > 0) addZeroes(B, n);
    else addZeroes(A, abs(n));
}

int BinaryChromosome::getSize() {
    return BinaryChromosome::genes.size();
}

void BinaryChromosome::setGen(int index, bool gen) {
    BinaryChromosome::genes.at(index) = gen;
}

bool BinaryChromosome::getGen(int index) {
    return BinaryChromosome::genes.at(index);
}

void BinaryChromosome::reverse(int startIndex, int endIndex) {
    std::reverse(BinaryChromosome::genes.begin() + startIndex, BinaryChromosome::genes.begin() + endIndex);
}

BinaryChromosome *BinaryChromosome::concatenate(BinaryChromosome *a, BinaryChromosome *b) {
    BinaryChromosome *out = a->getCopy();
    for (bool gen : b->get()) {
        out->addGen(gen);
    }
    return out;
}

BinaryChromosome *BinaryChromosome::getCopy() {
    BinaryChromosome *chromosome = new BinaryChromosome();
    chromosome->setDecimal(this->getDecimal());
    return chromosome;
}

void BinaryChromosome::addGen(bool gen) {
    BinaryChromosome::genes.push_back(gen);
}

void BinaryChromosome::swap(int aIndex, int bIndex) {
    bool savedGen = BinaryChromosome::getGen(aIndex);
    BinaryChromosome::setGen(aIndex, BinaryChromosome::getGen(bIndex));
    BinaryChromosome::setGen(bIndex, savedGen);
}

BinaryChromosome *BinaryChromosome::getSubsequence(int startIndex, int endIndex) {
    BinaryChromosome *chromosome = new BinaryChromosome();
    for (int i = startIndex; i <= endIndex; i++) {
        chromosome->addGen(BinaryChromosome::getGen(i));
    }
    return chromosome;
}

BinaryChromosome *BinaryChromosome::erase(int startIndex, int endIndex) {
    BinaryChromosome *ret = BinaryChromosome::getSubsequence(startIndex, endIndex);
    BinaryChromosome::genes.erase(
            BinaryChromosome::genes.begin() + startIndex,
            BinaryChromosome::genes.begin() + endIndex
    );
    return ret;
}

void BinaryChromosome::glue(BinaryChromosome *anotherChromosome) {
    for (bool gen : anotherChromosome->get()) {
        BinaryChromosome::addGen(gen);
    }
}

void BinaryChromosome::insert(int startIndex, BinaryChromosome *anotherChromosome) {
    for (bool gen : anotherChromosome->get()) {
        BinaryChromosome::get().insert(BinaryChromosome::get().begin() + startIndex, gen);
    }
}

void BinaryChromosome::reverse() {
    std::reverse(BinaryChromosome::genes.begin(), BinaryChromosome::genes.end());
}

std::vector<short> BinaryChromosome::getBitwiseDecimal() {

    std::vector<short> out;
    int decimal = BinaryChromosome::getDecimal();

    while(decimal != 0){
        out.push_back(decimal % 10);
        decimal /= 10;
    }

    std::reverse(out.begin(), out.end());

    return out;
}

void BinaryChromosome::complementChromosome(std::vector<short> &A, std::vector<short> &B) {
    int n = A.size() - B.size();
    if (n > 0) addZeroes(B, n);
    else addZeroes(A, abs(n));
}

std::vector<short> BinaryChromosome::addZeroes(std::vector<short> &A, int n) {
    std::vector<short> T;
    for (int i = 0; i < n; i++) T.push_back(0);
    for(short gen : A) T.push_back(gen);
    return T;
}

void BinaryChromosome::addGen(int gen) {
    BinaryChromosome::setDecimal(gen + BinaryChromosome::getDecimal());
}

void BinaryChromosome::addGenDecimalBitwise(int number) {
    BinaryChromosome::setDecimal(number + 10 * BinaryChromosome::getDecimal());
}
