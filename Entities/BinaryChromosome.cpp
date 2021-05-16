//
// Created by Vladimir on 15.05.2021.
//

#include <iostream>
#include "headers/BinaryChromosome.h"

int BinaryChromosome::getDecimal(){
    int rank = 1, result = 0;
    for(bool gen : BinaryChromosome::genes){
        if(gen) result += rank;
        rank *= 2;
    }
    return result;
};

void BinaryChromosome::setDecimal(int genSetDec){
    std::vector<bool> genSetBin;
    while(genSetDec != 0){
        genSetBin.push_back(genSetDec % 2);
        genSetDec /= 2;
    }
    BinaryChromosome::genes = genSetBin;
}

BinaryChromosome::BinaryChromosome(const std::vector<bool> &genesVector) : genes(genesVector) {
    BinaryChromosome::uniqueIdentifier = reinterpret_cast<int>(this);
};

BinaryChromosome::BinaryChromosome(int genesDec){
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
    for(bool gen : BinaryChromosome::genes){
        output += std::to_string(gen);
    }
    std::reverse(output.begin(), output.end());
    return output;
}

int BinaryChromosome::getUniqueIdentifier() const {
    return uniqueIdentifier;
}

void BinaryChromosome::set(const std::vector<bool> &genSet) {
    BinaryChromosome::genes = genSet;
}

const std::vector<bool> &BinaryChromosome::get() const {
    return BinaryChromosome::genes;
}

void BinaryChromosome::invert() {
    for(int i = 0; i < BinaryChromosome::genes.size(); i++){
        BinaryChromosome::genes.at(i) = !BinaryChromosome::genes.at(i);
    }
}

void BinaryChromosome::printout() {
    std::cout << "C_" << BinaryChromosome::getUniqueIdentifier() << ":{DEC:";
    std::cout << BinaryChromosome::getDecimal() << ",BIN:";
    std::cout << BinaryChromosome::getBinaryString() << "}";
}

int BinaryChromosome::getHammingDistance(BinaryChromosome *A, BinaryChromosome *B) {

    int maxSize, minSize, amountOfEqualPositions = 0;

    A->get().size() > B->get().size() ? maxSize = A->get().size() : maxSize = B->get().size();
    A->get().size() < B->get().size() ? minSize = A->get().size() : minSize = B->get().size();

    for(int i = 0; i < minSize; i++){
        A->get().at(i) != B->get().at(i) ? amountOfEqualPositions++ : 0;
    }

    if (A->get().size() > B->get().size())
        for(int i = minSize; i < maxSize; i++){
            A->get().at(i) != false ? amountOfEqualPositions++ : 0;
        }
    else
        for(int i = minSize; i < maxSize; i++){
            B->get().at(i) != false ? amountOfEqualPositions++ : 0;
        }

    return amountOfEqualPositions;
}

double BinaryChromosome::normalizedDistance(BinaryChromosome *A, BinaryChromosome *B) {

    int hammingDist = BinaryChromosome::getHammingDistance(A, B);
    int maxSize;

    A->get().size() > B->get().size() ? maxSize = A->get().size() : maxSize = B->get().size();

    return (double)hammingDist / (double)maxSize;
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
    BinaryChromosome* out = a->getCopy();
    for(bool gen : b->get()){
        out->addGen(gen);
    }
    return out;
}

BinaryChromosome *BinaryChromosome::getCopy() {
    BinaryChromosome* chromosome = new BinaryChromosome();
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

