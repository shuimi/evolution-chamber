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
    if(individuals.empty()) return "-1";

    std::string output = "[";
    for(int i = 0; i < Population::individuals.size() - 1; i++){
        output.append(std::to_string(Population::individuals.at(i)->getDecimal()));
        output.append(", ");
    }
    output.append(std::to_string(Population::individuals.at(Population::individuals.size() - 1)->getDecimal()));
    output.append("]");
    return output;
}

std::string Population::getIndividualsAsBinariesString() {
    if(individuals.empty()) return "-1";

    std::string output = "[";
    for(int i = 0; i < Population::individuals.size() - 1; i++){
        output.append(Population::individuals.at(i)->getBinaryString());
        output.append(", ");
    }
    output.append(Population::individuals.at(Population::individuals.size() - 1)->getBinaryString());
    output.append("]");
    return output;
}

void Population::printout() {
    std::cout
    << "Population #" << Population::getIndex() << "\n"
    << "Unique Identifier: " << Population::getUniqueIdentifier() << "\n"
    << "Decimals: " << Population::getIndividualsAsDecimalsString() << "\n"
    << "Binaries: " << Population::getIndividualsAsBinariesString() << "\n\n";
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

void Population::statPrintout() {
    std::map<int, int> stat{};
    for(BinaryChromosome* individual : Population::individuals){
        ++stat[individual->getDecimal()];
    }
    for(auto p : stat) {
        std::cout << std::setw(2) << p.first << ' ' << std::string(p.second, '*') << '\n';
    }
    std::cout << "\n";
}
