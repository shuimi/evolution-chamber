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
    BinaryChromosome::uniqueIndex = reinterpret_cast<int>(this);
};

BinaryChromosome::BinaryChromosome(int genesDec){
    BinaryChromosome::setDecimal(genesDec);
    BinaryChromosome::uniqueIndex = reinterpret_cast<int>(this);
}

BinaryChromosome::BinaryChromosome() {
    BinaryChromosome::setDecimal(0);
    BinaryChromosome::uniqueIndex = reinterpret_cast<int>(this);
};

BinaryChromosome::~BinaryChromosome() {

}

std::string BinaryChromosome::getBinaryString() {
    std::string output;
    for(bool gen : BinaryChromosome::genes){
        output += static_cast<char>(gen);
    }
    std::reverse(output.begin(), output.end());
    return output;
}

std::ostream &operator<<(std::ostream &os, const BinaryChromosome &chromosome) {
    os << "genes: " << chromosome.genes;
    return os;
}

int BinaryChromosome::getUniqueIndex() const {
    return uniqueIndex;
}

void BinaryChromosome::setUniqueIndex(int uniqueIndex) {
    BinaryChromosome::uniqueIndex = uniqueIndex;
};
