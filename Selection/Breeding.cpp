//
// Created by Vladimir on 20.05.2021.
//

#include "Breeding.h"

///SELECT METHODS
///SELECT METHODS
///SELECT METHODS

Generation* Breeding::select(
    Generation* generation,
    std::function<bool(double)> fitnessRange,
    std::function<double(double)> fitnessFunction
) {

    if(generation->size() == 0)
        throw "[BREEDING ERROR] EMPTY GENERATION AT INPUT";

    generation->estimate(fitnessFunction);

    for(int i = 0; i < generation->size();){
        if(!fitnessRange(generation->getEstimation().at(i)))
            generation->eject(i);
        else i++;
    }

    return generation;
}

std::tuple<Chromosome*, Chromosome*> Breeding::selectRandomPair(Generation *generation) {

    if(generation->size() < 2)
        throw "[BREEDING ERROR] GENERATION SIZE IS LOWER THAN 2";

    Chromosome *A, *B;
    A = generation->getRandomIndividual();
    B = generation->getRandomIndividual();
    while(A == B){
        B = generation->getRandomIndividual();
    }
    return std::make_tuple(A, B);
}


///BREEDING OPERATORS
///BREEDING OPERATORS
///BREEDING OPERATORS


Generation *Breeding::random(
Generation *generation
) {
    return Breeding::random(generation, 0);
}

Generation *Breeding::inbreeding(
    Generation *parents, Generation *descendants,
    std::function<bool(double)> selectionCondition,
    std::function<double(double)> fitnessFunction
) {

    if(parents->size() == 0 || descendants->size() == 0)
        throw "[BREEDING ERROR] EMPTY GENERATION AT INPUT";

    Generation* parentsCopy = parents->copy();
    Generation* descendantsCopy = descendants->copy();
    Generation* newGeneration = new Generation(descendants->getIndex() + 1);

    auto add = [=](Generation* generationToAdd){
        newGeneration->add(
            select(
                generationToAdd,
                selectionCondition,
                fitnessFunction
            )
        );
    };
    add(parentsCopy);
    add(descendantsCopy);

    return newGeneration;
}

Generation *Breeding::inbreeding(
Generation* parents,
Generation* descendants
) {

    if(parents->size() == 0 || descendants->size() == 0)
        throw "[BREEDING ERROR] EMPTY GENERATION AT INPUT";

    Generation* parentsCopy = parents->copy();
    Generation* descendantsCopy = descendants->copy();

    Generation* newGeneration = new Generation(descendants->getIndex() + 1);

    Generation* temp = parentsCopy->copy();
    temp->add(descendantsCopy);

    double minNormalizedHammingDistance =
        Generation::getMinNormalizedHammingDistance(temp);
    double maxNormalizedHammingDistance =
        Generation::getMaxNormalizedHammingDistance(temp);

    //TODO: remove object
    double mean = (new FunctionConstraints<double>(
            minNormalizedHammingDistance,
            maxNormalizedHammingDistance
    ))->getMean();

    for (int i = 0; i < temp->size() - 1; i++){
        for (int j = i + 1; j < temp->size(); j++){
            if(temp->get(i) != temp->get(j)){
                if (Chromosome::getNormalizedHammingDistance(temp->get(i), temp->get(j)) < mean){
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

Generation *Breeding::scaleBased(
Generation *generation,
std::function<double(double)> estimationFunction,
double lowThreshold
) {

    if(generation->size() == 0)
        throw "[BREEDING ERROR] EMPTY GENERATION AT INPUT";

    Generation* generationCopy = generation->copy();
    Generation* newGeneration = new Generation(generation->getIndex() + 1);

    generationCopy->estimate(estimationFunction);
    generationCopy->reduce([lowThreshold](double estimationValue) {
        return (estimationValue > lowThreshold);
    });
    newGeneration->add(generationCopy);

    return newGeneration;
}

Generation *Breeding::random(Generation *generation, int amountFloor) {

    if(generation->size() == 0)
        throw "[BREEDING ERROR] EMPTY GENERATION AT INPUT";

    Generation* generationCopy = generation->copy();
    Generation* newGeneration = new Generation(generation->getIndex() + 1);
    int hybridizationCasesAmount = amountFloor + rand() % (generation->size() - amountFloor);

    while(hybridizationCasesAmount != 0){

        int currentIndex = rand() % generationCopy->size();
        newGeneration->add(generationCopy->get(currentIndex));
        generationCopy->eject(currentIndex);

        hybridizationCasesAmount--;
    }

    return newGeneration;
}
