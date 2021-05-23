//
// Created by Vladimir on 15.05.2021.
//

#include <iostream>
#include "Chromosome.h"

int Chromosome::getDecimal() {
    int rank = 1, result = 0;
    for (bool gen : Chromosome::genes) {
        if (gen) result += rank;
        rank *= 2;
    }
    return result;
};

void Chromosome::setDecimal(int genSetDec) {
    std::vector<bool> genSetBin;
    while (genSetDec != 0) {
        genSetBin.push_back(genSetDec % 2);
        genSetDec /= 2;
    }
    Chromosome::genes = genSetBin;
}

Chromosome::Chromosome(const std::vector<bool> &genesVector) : genes(genesVector) {
    Chromosome::uniqueIdentifier = reinterpret_cast<int>(this);
};

Chromosome::Chromosome(int genesDec) {
    Chromosome::setDecimal(genesDec);
    Chromosome::uniqueIdentifier = reinterpret_cast<int>(this);
}

Chromosome::Chromosome() {
    Chromosome::setDecimal(0);
    Chromosome::uniqueIdentifier = reinterpret_cast<int>(this);
};

Chromosome::~Chromosome() {

}

std::string Chromosome::getBinaryString() {
    if (Chromosome::genes.empty()) return "0";
    std::string output;
    for (bool gen : Chromosome::genes) {
        output += std::to_string(gen);
    }
    std::reverse(output.begin(), output.end());
    return output;
}

int Chromosome::getUniqueIdentifier() const {
    return uniqueIdentifier;
}

void Chromosome::set(const std::vector<bool> &genSet) {
    Chromosome::genes = genSet;
}

std::vector<bool> &Chromosome::get() {
    return Chromosome::genes;
}

void Chromosome::invert() {
    for (int i = 0; i < Chromosome::genes.size(); i++) {
        Chromosome::genes.at(i) = !Chromosome::genes.at(i);
    }
}

void Chromosome::printout() {
    std::cout << "C_" << Chromosome::getUniqueIdentifier() << ":{DEC:";
    std::cout << Chromosome::getDecimal() << ",BIN:";
    std::cout << Chromosome::getBinaryString() << "}\n";
}

int Chromosome::getHammingDistance(Chromosome *A, Chromosome *B) {

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

double Chromosome::getNormalizedHammingDistance(Chromosome *A, Chromosome *B) {

    int hammingDist = Chromosome::getHammingDistance(A, B);
    int maxSize;

    A->get().size() > B->get().size() ? maxSize = A->get().size() : maxSize = B->get().size();

    return (double) hammingDist / (double) maxSize;
}

void Chromosome::addZeroes(Chromosome *A, int n) {
    for (int i = 0; i < n; i++)
        A->get().push_back(0);
}

void Chromosome::complementChromosome(Chromosome *A, Chromosome *B) {
    int n = A->get().size() - B->get().size();
    if (n > 0) addZeroes(B, n);
    else addZeroes(A, abs(n));
}

int Chromosome::size() {
    return Chromosome::genes.size();
}

void Chromosome::setGen(int index, bool gen) {
    Chromosome::genes.at(index) = gen;
}

bool Chromosome::getGen(int index) {
    return Chromosome::genes.at(index);
}

void Chromosome::reverse(int startIndex, int endIndex) {
    std::reverse(Chromosome::genes.begin() + startIndex, Chromosome::genes.begin() + endIndex);
}

Chromosome *Chromosome::concatenate(Chromosome *a, Chromosome *b) {
    Chromosome *out = a->getCopy();
    for (bool gen : b->get()) {
        out->addGen(gen);
    }
    return out;
}

Chromosome *Chromosome::getCopy() {
    Chromosome *chromosome = new Chromosome();
    chromosome->setDecimal(this->getDecimal());
    return chromosome;
}

void Chromosome::addGen(bool gen) {
    Chromosome::genes.push_back(gen);
}

void Chromosome::swap(int aIndex, int bIndex) {
    bool savedGen = Chromosome::getGen(aIndex);
    Chromosome::setGen(aIndex, Chromosome::getGen(bIndex));
    Chromosome::setGen(bIndex, savedGen);
}

Chromosome *Chromosome::getSubsequence(int startIndex, int endIndex) {
    Chromosome *chromosome = new Chromosome();
    for (int i = startIndex; i <= endIndex; i++) {
        chromosome->addGen(Chromosome::getGen(i));
    }
    return chromosome;
}

Chromosome *Chromosome::erase(int startIndex, int endIndex) {
    Chromosome *ret = Chromosome::getSubsequence(startIndex, endIndex);
    Chromosome::genes.erase(
            Chromosome::genes.begin() + startIndex,
            Chromosome::genes.begin() + endIndex
    );
    return ret;
}

void Chromosome::glue(Chromosome *anotherChromosome) {
    for (bool gen : anotherChromosome->get()) {
        Chromosome::addGen(gen);
    }
}

void Chromosome::insert(int startIndex, Chromosome *anotherChromosome) {
    for (bool gen : anotherChromosome->get()) {
        Chromosome::get().insert(Chromosome::get().begin() + startIndex, gen);
    }
}

void Chromosome::reverse() {
    std::reverse(Chromosome::genes.begin(), Chromosome::genes.end());
}

std::vector<short> Chromosome::getBitwiseDecimal() {

    std::vector<short> out;
    int decimal = Chromosome::getDecimal();

    while(decimal != 0){
        out.push_back(decimal % 10);
        decimal /= 10;
    }

    std::reverse(out.begin(), out.end());

    return out;
}

void Chromosome::complementChromosome(std::vector<short> &A, std::vector<short> &B) {
    int n = A.size() - B.size();
    if (n > 0) addZeroes(B, n);
    else addZeroes(A, abs(n));
}

std::vector<short> Chromosome::addZeroes(std::vector<short> &A, int n) {
    std::vector<short> T;
    for (int i = 0; i < n; i++) T.push_back(0);
    for(short gen : A) T.push_back(gen);
    return T;
}

void Chromosome::addGen(int gen) {
    Chromosome::setDecimal(gen + Chromosome::getDecimal());
}

void Chromosome::addGenDecimalBitwise(int number) {
    Chromosome::setDecimal(number + 10 * Chromosome::getDecimal());
}

