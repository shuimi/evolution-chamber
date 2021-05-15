//
// Created by Vladimir on 15.05.2021.
//

#include <iostream>
#include "headers/Population.h"

Population::Population(const std::vector<BinaryChromosome *> &individuals) : individuals(individuals) {
    Population::uniqueIdentifier = reinterpret_cast<int>(this);
}

Population::~Population() {

}

std::vector<BinaryChromosome *> &Population::getIndividuals() {
    return individuals;
}

void Population::setIndividuals(const std::vector<BinaryChromosome *> &individuals) {
    Population::individuals = individuals;
}

void Population::addIndividual(BinaryChromosome *ind) {
    Population::individuals.push_back(ind);
}

int Population::getUniqueIdentifier() const {
    return uniqueIdentifier;
}

bool Population::operator==(const Population &rhs) const {
    return uniqueIdentifier == rhs.uniqueIdentifier;
}

bool Population::operator!=(const Population &rhs) const {
    return !(rhs == *this);
}

std::string Population::getIndividualsAsDecimalsString() {
    std::string output = "[ ";
    for(BinaryChromosome* ind : Population::individuals){
        output.append(std::to_string(ind->getDecimal()));
        output.append(" ");
    }
    output.append("]");
    return output;
}

std::string Population::getIndividualsAsBinariesString() {
    std::string output = "[ ";
    for(BinaryChromosome* ind : Population::individuals){
        output.append(std::string(ind->getBinaryString()));
        output.append(" ");
    }
    output.append("]");
    return output;
}

void Population::printout() {
    std::cout
    << "----------------------------------------------------------" << "\n"
    << "Population #" << Population::getIndex() << "\n"
    << "Unique Identifier: " << Population::getUniqueIdentifier() << "\n"
    << "----------------------------------------------------------" << "\n"
    << "Decimals: " << Population::getIndividualsAsDecimalsString() << "\n"
    << "Binaries: " << Population::getIndividualsAsBinariesString() << "\n"
    << "----------------------------------------------------------" << "\n";
}

int Population::getIndex() const {
    return index;
}

void Population::setIndex(int index) {
    Population::index = index;
}

Population::Population(int index) {
    Population::setIndex(index);
    Population::uniqueIdentifier = reinterpret_cast<int>(this);
}

Population::Population(Population *anotherPopulation) {
    Population::uniqueIdentifier = anotherPopulation->getUniqueIdentifier();
    Population::individuals = anotherPopulation->getIndividuals();
    Population::index = anotherPopulation->getIndex();
}

BinaryChromosome *Population::get(int index) {
    return Population::getIndividuals().at(index);
}

void Population::set(int index, BinaryChromosome *chromosome) {
    Population::getIndividuals().at(index) = chromosome;
}
