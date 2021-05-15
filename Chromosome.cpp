//
// Created by Vladimir on 15.05.2021.
//

#include "Chromosome.h"

int Chromosome::getDecimal(){
    int rank = 1, result = 0;
    for(bool gen : Chromosome::genes){
        if(gen) result += rank;
        rank *= 2;
    }
    return result;
};

void Chromosome::setDecimal(int genSetDec){
    std::vector<bool> genSetBin;
    while(genSetDec != 0){
        genSetBin.push_back(genSetDec % 2);
        genSetDec /= 2;
    }
    Chromosome::genes = genSetBin;
}

Chromosome::Chromosome(const std::vector<bool> &genSet) : genes(genSet) {};

Chromosome::Chromosome(int genSetDec){
    Chromosome::setDecimal(genSetDec);
}

Chromosome::Chromosome() {
    Chromosome::setDecimal(0);
};

Chromosome::~Chromosome() {

}

std::string Chromosome::getBinaryString() {
    std::string output;
    for(bool gen : Chromosome::genes){
        output += static_cast<char>(gen);
    }
    return output;
};
