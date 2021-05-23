//
// Created by Vladimir on 16.05.2021.
//

#include "Population.h"

std::vector<Generation *> &Population::getGenerations() {
    return generations;
}

void Population::setGenerations(const std::vector<Generation *> &generations) {
    Population::generations = generations;
}

Population::Population(const std::vector<Generation *> &generations) : generations(generations) {}

Population::Population() {

}

Population::~Population() {

}

void Population::foreach(std::function<void (Generation *)> transformation) {
    for(Generation* generation : Population::generations){
        transformation(generation);
    }
}

void Population::printout() {
    Population::foreach([](Generation* g){
        g->printout();
    });
}

Generation *Population::get(int index) {
    return Population::getGenerations().at(index);
}

void Population::set(int index, Generation *generation) {
    Population::getGenerations().at(index) = generation;
}

void Population::add(Generation *generation) {
    Population::getGenerations().push_back(generation);
}

Generation *Population::eject(int index) {
    Generation* ret = Population::generations.at(index);
    Population::generations.erase(Population::generations.begin() + index);
    return ret;
}

void Population::eject(Generation *generation) {
    for(int i = 0; i < Population::generations.size(); i++){
        if(Population::generations.at(i)->getUniqueIdentifier() == generation->getUniqueIdentifier()){
            Population::generations.erase(Population::generations.begin() + i);
            break;
        }
    }
}

Generation *Population::getAsGeneration() {
    Generation* out = new Generation(0);
    Population::foreach([out](Generation* generation){
        out->add(generation);
    });
    return out;
}

Generation *Population::getLastGeneration() {
    return Population::get(Population::generations.size() - 1);
}

int Population::getSize() {
    return Population::generations.size();
}
