#include <iostream>
#include "Main/EvolutionChamber.h"
#include "Breeding.h"

int main() {

    srand(time(NULL));

    double leftBound = 9;
    double rightBound = 14;

    int initialIndividualsAmount = 10;
    int generationsAmount = 50;

    double crossingProbability = 0.7;
    double mutationProbability = 0.3;

    auto fitnessFunction = [](double x){
        return x * x + 0.1 * x - 23;
    };

    auto constraints = new FunctionConstraints<int>(leftBound, rightBound);


//    EvolutionChamber* evolution = new EvolutionChamber(
//        fitnessFunction,
//        new FunctionConstraints<int>(leftBound, rightBound),
//        GenerationFactory::getUsingShotgun(
//            leftBound,
//            rightBound,
//            initialIndividualsAmount
//        )
//    );


//    BinaryChromosome* a = new BinaryChromosome(124256);
//    BinaryChromosome* b = new BinaryChromosome(842516);
//    a->printout();
//    b->printout();
//    Morphing::crossCX(a, b)->printout();

  
    Generation* generationA = GenerationFactory::getUsingShotgun(
            leftBound,
            rightBound,
            initialIndividualsAmount,
            0
    );
    Generation* generationB = GenerationFactory::getUsingShotgun(
            leftBound,
            rightBound,
            initialIndividualsAmount,
            1
    );

    generationA->printout();
    generationA->printout();


    Breeding::random(generationA)->printout();


    Breeding::inbreeding(
            generationA, generationB
    )->printout();


    Breeding::inbreeding(
            generationA, generationB,
            [=](double estimationValue) {
                return (estimationValue >= fitnessFunction(constraints->getMean()));
            },
            fitnessFunction
    )->printout();


    Breeding::scaleBased(
            generationA,
            [=](int decimal){
                return ((double)fitnessFunction(decimal) / (
                    fitnessFunction(
                        generationA->getWithMaxEstimation(
                                fitnessFunction
                            )->getDecimal()
                        )
                    )
                );
            },
            0.5
    )->printout();


    Generation* test = GenerationFactory::getUsingFocusing(10, 10, 15, 0);
    test->printout();
    FunctionConstraints<int>(0, 5).reduceGenerationToInterval(test)->printout();

}
