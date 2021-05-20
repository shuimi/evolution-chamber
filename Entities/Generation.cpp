//
// Created by Vladimir on 15.05.2021.
//

#include <iostream>
#include "Generation.h"

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

void Generation::add(BinaryChromosome *ind) {
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
    << "Size: " << Generation::size() << "\n"
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
    if(!estimations.empty())
        Generation::estimations.erase(Generation::estimations.begin() + index);
    return ret;
}

template<typename R>
void Generation::foreach(std::function<R(BinaryChromosome*)> transformation) {
    for(BinaryChromosome* individual : Generation::individuals){
        transformation(individual);
    }
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

void Generation::estimate(std::function<double(double)> estimationFunction) {
    Generation::estimations.clear();
    for(BinaryChromosome* individual : Generation::individuals){
        Generation::estimations.push_back(estimationFunction(std::round(individual->getDecimal())));
    }
}


void Generation::printoutEstimation() {
    std::cout << "Estimation:{\n";
    for(int i = 0; i < Generation::individuals.size(); i++){
        std::cout << "  f(" << Generation::getIndividuals().at(i)->getDecimal();
        std::cout << ") = " << Generation::estimations.at(i) << ",\n";
    }
    std::cout << "}\n\n";
}

const std::vector<double> &Generation::getEstimation() const {
    return estimations;
}

void Generation::setIndividualsEstimation(const std::vector<double> &individualsEstimation) {
    Generation::estimations = individualsEstimation;
}

void Generation::eject(BinaryChromosome *individual) {
    for(int i = 0; i < Generation::individuals.size(); i++){
        if(individual->getUniqueIdentifier() ==
        Generation::individuals.at(i)->getUniqueIdentifier()){
            Generation::individuals.erase(Generation::individuals.begin() + i);
            if(!Generation::estimations.empty())
                Generation::estimations.erase(Generation::estimations.begin() + i);
            break;
        }
    }
}

BinaryChromosome* Generation::getRandomIndividual() {
    return get(std::rand() % Generation::individuals.size());
}

void Generation::add(Generation* generation) {
    generation->foreach([this](BinaryChromosome* c){
        this->add(c);
    });
}

int Generation::size() {
    return Generation::individuals.size();
}

Generation *Generation::copy() {
    return new Generation(this);
}

double Generation::getMinNormalizedHammingDistance(Generation *generation) {

     double min = BinaryChromosome::getNormalizedHammingDistance(
             generation->first(),
             generation->last()
    );

    for(BinaryChromosome* a : generation->getIndividuals())
        for(BinaryChromosome* b : generation->getIndividuals()){
            if(a != b){
                double current = BinaryChromosome::getNormalizedHammingDistance(a, b);
                if (current < min) min = current;
            }
        }

    return min;
}

double Generation::getMaxNormalizedHammingDistance(Generation *generation) {

    double max = 0.0;

    for(BinaryChromosome* a : generation->getIndividuals())
        for(BinaryChromosome* b : generation->getIndividuals()){
            if(a != b){
                double current = BinaryChromosome::getNormalizedHammingDistance(a, b);
                if (current > max) max = current;
            }
        }

    return max;
}

BinaryChromosome *Generation::first() {
    return Generation::individuals.front();
}

BinaryChromosome *Generation::last() {
    return Generation::individuals.back();
}

bool Generation::contains(BinaryChromosome* chromosome) {
    for (BinaryChromosome* c : Generation::individuals){
        if (chromosome == c) return true;
    }
    return false;
}

BinaryChromosome *Generation::getWithMaxEstimation(std::function<double(double)> estimationFunction) {

    this->estimate(estimationFunction);

    double max = estimations.front();
    int maxIndex = 0;

    int index = 0;
    for(double estimation : Generation::estimations){
        if (estimation > max) {
            max = estimation;
            maxIndex = index;
        }
        index++;
    }

    return Generation::get(maxIndex);
}

void Generation::reduce(std::function<bool(BinaryChromosome *)> condition) {
    for (int i = 0; i < Generation::size(); ){
        if (condition(Generation::get(i))) Generation::eject(i);
        else i++;
    }
}

void Generation::reduce(std::function<bool(double)> condition) {
    for (int i = 0; i < Generation::size(); ){
        if (condition(Generation::getEstimation(i))) Generation::eject(i);
        else i++;
    }
}

double Generation::getEstimation(int index) {
    return Generation::estimations.at(index);
}





