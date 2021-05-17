//
// Created by Vladimir on 15.05.2021.
//

#include <iostream>
#include "headers/Generation.h"

Generation::Generation(std::vector<BinaryChromosome *> &individuals) : individuals(individuals) {
    Generation::uniqueIdentifier = reinterpret_cast<int>(this);
}

Generation::~Generation() {

}

std::vector<BinaryChromosome *> &Generation::getIndividuals() {
    return individuals;
}

void Generation::setIndividuals(const std::vector<BinaryChromosome *> &individuals) {
    Generation::individuals = individuals;
}

void Generation::addIndividual(BinaryChromosome *ind) {
    Generation::individuals.push_back(ind);
}

int Generation::getUniqueIdentifier() const {
    return uniqueIdentifier;
}

bool Generation::operator==(const Generation &rhs) const {
    return uniqueIdentifier == rhs.uniqueIdentifier;
}

bool Generation::operator!=(const Generation &rhs) const {
    return !(rhs == *this);
}

std::string Generation::getIndividualsAsDecimalsString() {
    if(individuals.empty()) return "-1";

    std::string output = "[";
    for(int i = 0; i < Generation::individuals.size() - 1; i++){
        output.append(std::to_string(Generation::individuals.at(i)->getDecimal()));
        output.append(", ");
    }
    output.append(std::to_string(Generation::individuals.at(Generation::individuals.size() - 1)->getDecimal()));
    output.append("]");
    return output;
}

std::string Generation::getIndividualsAsBinariesString() {
    if(individuals.empty()) return "-1";

    std::string output = "[";
    for(int i = 0; i < Generation::individuals.size() - 1; i++){
        output.append(Generation::individuals.at(i)->getBinaryString());
        output.append(", ");
    }
    output.append(Generation::individuals.at(Generation::individuals.size() - 1)->getBinaryString());
    output.append("]");
    return output;
}

void Generation::printout() {
    std::cout
    << "Generation #" << Generation::getIndex() << "\n"
    << "Unique Identifier: " << Generation::getUniqueIdentifier() << "\n"
    << "Decimals: " << Generation::getIndividualsAsDecimalsString() << "\n"
    << "Binaries: " << Generation::getIndividualsAsBinariesString() << "\n\n";
}

int Generation::getIndex() const {
    return index;
}

void Generation::setIndex(int index) {
    Generation::index = index;
}

Generation::Generation(int index) {
    Generation::setIndex(index);
    Generation::uniqueIdentifier = reinterpret_cast<int>(this);
}

Generation::Generation(Generation *anotherPopulation) {
    Generation::uniqueIdentifier = anotherPopulation->getUniqueIdentifier();
    Generation::individuals = anotherPopulation->getIndividuals();
    Generation::index = anotherPopulation->getIndex();
}

BinaryChromosome *Generation::get(int index) {
    return Generation::getIndividuals().at(index);
}

void Generation::set(int index, BinaryChromosome *chromosome) {
    Generation::getIndividuals().at(index) = chromosome;
}

void Generation::statPrintout() {
    std::map<int, int> stat{};
    for(BinaryChromosome* individual : Generation::individuals){
        ++stat[individual->getDecimal()];
    }
    for(auto p : stat) {
        std::cout << std::setw(2) << p.first << ' ' << std::string(p.second, '*') << '\n';
    }
    std::cout << "\n";
}

BinaryChromosome *Generation::eject(int index) {
    BinaryChromosome* ret = Generation::individuals.at(index);
    Generation::individuals.erase(Generation::individuals.begin() + index);
    Generation::individualsEstimation.erase(Generation::individualsEstimation.begin() + index);
    return ret;
}

void Generation::foreach(std::function<int(int)> decimalTransformation) {
    for(BinaryChromosome* individual : Generation::individuals){
        individual->setDecimal(decimalTransformation(individual->getDecimal()));
    }
}

void Generation::foreach(std::function<BinaryChromosome*(BinaryChromosome*)> transformation) {
    for(BinaryChromosome* individual : Generation::individuals){
        individual = transformation(individual);
    }
}

void Generation::foreach(std::function<void(BinaryChromosome *)> transformation) {
    for(BinaryChromosome* individual : Generation::individuals){
        transformation(individual);
    }
}

void Generation::estimate(std::function<double(double)> fitnessFunction) {
    Generation::individualsEstimation.clear();
    for(BinaryChromosome* individual : Generation::individuals){
        Generation::individualsEstimation.push_back(fitnessFunction(std::round(individual->getDecimal())));
    }
}

void Generation::printoutEstimation() {
    std::cout << "Estimation:{\n";
    for(int i = 0; i < Generation::individuals.size(); i++){
        std::cout << "  f(" << Generation::getIndividuals().at(i)->getDecimal();
        std::cout << ") = " << Generation::individualsEstimation.at(i) << ",\n";
    }
    std::cout << "}\n\n";
}

const std::vector<double> &Generation::getIndividualsEstimation() const {
    return individualsEstimation;
}

void Generation::setIndividualsEstimation(const std::vector<double> &individualsEstimation) {
    Generation::individualsEstimation = individualsEstimation;
}

void Generation::eject(BinaryChromosome *individual) {
    for(int i = 0; i < Generation::individuals.size(); i++){
        if(individual->getUniqueIdentifier() ==
        Generation::individuals.at(i)->getUniqueIdentifier()){
            Generation::individuals.erase(Generation::individuals.begin() + i);
            Generation::individualsEstimation.erase(Generation::individualsEstimation.begin() + i);
            break;
        }
    }
}

BinaryChromosome* Generation::getRandomIndividual() {
    return get(std::rand() % Generation::individuals.size());
}

void Generation::add(Generation* generation) {
    generation->foreach([this](BinaryChromosome* c){
        this->addIndividual(c);
    });
}

int Generation::getSize() {
    return Generation::individuals.size();
}



