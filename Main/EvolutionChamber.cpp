//
// Created by Vladimir on 15.05.2021.
//

#include "headers/EvolutionChamber.h"

#include <utility>

void EvolutionChamber::setFitnessFunction(std::function<double(double)> fitnessFunction) {
    EvolutionChamber::fitnessFunction = fitnessFunction;
}

const double EvolutionChamber::executeFitnessFunction(double arg){
    return fitnessFunction.operator()(arg);
}

const std::function<double(double)> &EvolutionChamber::getFitnessFunction() const {
    return fitnessFunction;
}


Generation *EvolutionChamber::selectionElite(Generation *population, std::function<bool(double)> selectionCondition) {

    population->estimate(EvolutionChamber::getFitnessFunction());

    for(int i = 0; i < population->getIndividuals().size();){
        if(!selectionCondition(population->getIndividualsEstimation().at(i))) {
            population->eject(i);
        }
        else i++;
    }

    return population;
}

Generation *EvolutionChamber::selectionElite(Generation *population, std::function<double(double)> fitnessFunction,
                                             std::function<bool(double)> selectionCondition) {
    population->estimate(fitnessFunction);
    for(int i = 0; i < population->getIndividuals().size();){
        if(!selectionCondition(population->getIndividualsEstimation().at(i))) {
            population->eject(i);
        }
        else i++;
    }
    return population;
}

template<typename T>
Generation *EvolutionChamber::selection(Generation *population, std::function<bool(T)> selectionCondition) {

    population->estimate(EvolutionChamber::getFitnessFunction());

    for(int i = 0; i < population->getIndividuals().size();){
        if(!selectionCondition(population->getIndividuals().at(i))) {
            population->eject(i);
        }
        else i++;
    }

    return population;
}

std::tuple<BinaryChromosome*, BinaryChromosome*> EvolutionChamber::selectRandomPair(Generation *population) {
    BinaryChromosome *A, *B;
    A = population->getRandomIndividual();
    B = population->getRandomIndividual();
    while(A == B){
        B = population->getRandomIndividual();
    }
    return std::make_tuple(A, B);
}

EvolutionChamber::EvolutionChamber(
        std::function<double(double)> fitnessFunction,
        FitnessFunctionConstraints<int>* constraints,
        Generation *initialGeneration,
        MorphingFactor *morphingFactor
) : fitnessFunction(std::move(fitnessFunction)),
    constraints(constraints),
    initialGeneration(initialGeneration),
    morphingFactor(morphingFactor)
{
    EvolutionChamber::getInitialGeneration()->setIndex(0);
    EvolutionChamber::population->add(EvolutionChamber::getInitialGeneration());
}

EvolutionChamber::~EvolutionChamber() {

}

Population *EvolutionChamber::getPopulation() {
    return population;
}

void EvolutionChamber::setPopulation(Population *population) {
    EvolutionChamber::population = population;
}

Generation *EvolutionChamber::getInitialGeneration() {
    return initialGeneration;
}

void EvolutionChamber::setInitialGeneration(Generation *initialGeneration) {
    EvolutionChamber::initialGeneration = initialGeneration;
}

MorphingFactor *EvolutionChamber::getMorphingFactor() {
    return morphingFactor;
}

void EvolutionChamber::setMorphingFactor(MorphingFactor *morphingFactor) {
    EvolutionChamber::morphingFactor = morphingFactor;
}

Generation *EvolutionChamber::getNextGeneration() {
    return new Generation(0);
}

Generation *EvolutionChamber::breedingRandom(Generation *generation) {

    Generation* generationCopy = generation->getCopy();
    Generation* newGeneration = new Generation(generation->getIndex() + 1);
    int hybridizationCasesAmount = rand() % generation->getSize();

    while(hybridizationCasesAmount != 0){

        int currentIndex = rand() % generationCopy->getSize();
        newGeneration->add(generationCopy->get(currentIndex));
        generationCopy->eject(currentIndex);

        hybridizationCasesAmount--;
    }

    return newGeneration;
}

Generation *EvolutionChamber::breedingInbreedingElite(Generation *parents, Generation *descendants) {

    Generation* parentsCopy = parents->getCopy();
    Generation* descendantsCopy = descendants->getCopy();

    Generation* newGeneration = new Generation(descendants->getIndex() + 1);

    newGeneration->add(selectionElite(parentsCopy, [this](double estimationValue){
        return (estimationValue >= EvolutionChamber::executeFitnessFunction(
                EvolutionChamber::getConstraints()->getMean())
        );
    }));
    newGeneration->add(selectionElite(descendantsCopy, [this](double estimationValue){
        return (estimationValue >= EvolutionChamber::executeFitnessFunction(
                EvolutionChamber::getConstraints()->getMean())
        );
    }));

    return newGeneration;
}

Generation *EvolutionChamber::breedingInbreedingGenSimilarityDriven(Generation *parents, Generation *descendants) {

    Generation* parentsCopy = parents->getCopy();
    Generation* descendantsCopy = descendants->getCopy();

    Generation* newGeneration = new Generation(descendants->getIndex() + 1);

    Generation* temp = parentsCopy->getCopy();
    temp->add(descendantsCopy);

    double minNormalizedHammingDistance = Generation::getMinNormalizedHammingDistance(temp);
    double maxNormalizedHammingDistance = Generation::getMaxNormalizedHammingDistance(temp);

    FitnessFunctionConstraints<double>* estimation
            = new FitnessFunctionConstraints<double>(minNormalizedHammingDistance,maxNormalizedHammingDistance);

    double mean = estimation->getMean();

    for (int i = 0; i < temp->getSize() - 1; i++){
        for (int j = i + 1; j < temp->getSize(); j++){
            if(temp->get(i) != temp->get(j)){
                if (BinaryChromosome::getNormalizedHammingDistance(temp->get(i), temp->get(j)) < mean){
                    if (!newGeneration->contains(temp->get(i)))
                        newGeneration->add(temp->get(i));
                    if (!newGeneration->contains(temp->get(j)))
                        newGeneration->add(temp->get(j));
                }
            }
        }
    }

    return newGeneration;
}

FitnessFunctionConstraints<int> *EvolutionChamber::getConstraints() const {
    return constraints;
}

void EvolutionChamber::setConstraints(FitnessFunctionConstraints<int> *constraints) {
    EvolutionChamber::constraints = constraints;
}

Generation *EvolutionChamber::executeHybridization(Generation *generation) {
    return nullptr;
}
