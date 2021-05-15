//
// Created by Vladimir on 15.05.2021.
//

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
    for(bool gen : BinaryChromosome::genes){
        gen = !gen;
    }
};
