//
// Created by Vladimir on 15.05.2021.
//

#include "headers/Population.h"

Population::Population(const std::vector<BinaryChromosome *> &individuals) : individuals(individuals) {
    Population::uniqueIndex = reinterpret_cast<int>(this);
}

Population::~Population() {

}

const std::vector<BinaryChromosome *> &Population::getIndividuals() const {
    return individuals;
}

void Population::setIndividuals(const std::vector<BinaryChromosome *> &individuals) {
    Population::individuals = individuals;
}

void Population::addIndividual(BinaryChromosome *ind) {
    Population::individuals.push_back(ind);
}

Population::Population() {
    Population::uniqueIndex = reinterpret_cast<int>(this);
}

std::ostream &operator<<(std::ostream &os, const Population &population) {

    std::string output = "[";
    for(BinaryChromosome* ind : population.individuals){
        output += ind->getDecimal() + " ";
    }
    output += "]";

    os << "individuals: " << output;
    return os;
}

int Population::getIndex() const {
    return uniqueIndex;
}

void Population::setIndex(int index) {
    Population::uniqueIndex = index;
}

bool Population::operator==(const Population &rhs) const {
    return uniqueIndex == rhs.uniqueIndex;
}

bool Population::operator!=(const Population &rhs) const {
    return !(rhs == *this);
}
