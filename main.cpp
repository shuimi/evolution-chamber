#include <iostream>
#include "Main/headers/EvolutionChamber.h"

int main() {

    srand(time(NULL));

    double leftBound = 9;
    double rightBound = 14;

    int initialIndividualsAmount = 10;
    int generationsAmount = 50;

    double crossingProbability = 0.7;
    double mutationProbability = 0.3;

    EvolutionChamber* evolution = new EvolutionChamber([](double x){
            return x * x + 0.1 * x - 23;
        },
        new FitnessFunctionConstraints<int>(leftBound, rightBound),
        GenerationFactory::getUsingShotgun(
            leftBound,
            rightBound,
            initialIndividualsAmount
        ),
        new MorphingFactor(
            crossingProbability,
            mutationProbability
        )
    );


//    BinaryChromosome* a = new BinaryChromosome(124256);
//    BinaryChromosome* b = new BinaryChromosome(842516);
//    a->printout();
//    b->printout();
//    MorphingFactor::crossCX(a, b)->printout();

  
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


    evolution->breedingRandom(generationA)->printout();

    evolution->breedingInbreedingGenSimilarityDriven(generationA, generationB)->printout();

    evolution->breedingInbreedingElite(generationA, generationB,[evolution](double estimationValue) {
        return (estimationValue >= evolution->executeFitnessFunction(
                evolution->getConstraints()->getMean())
        );
    })->printout();

    evolution->breedingWithEstimation(
            generationA,
            [evolution, generationA](int decimal){
                return ((double)evolution->executeFitnessFunction(decimal) / (
                    evolution->executeFitnessFunction(
                        generationA->getWithMaxEstimation(
                            evolution->getFitnessFunction())->getDecimal()
                        )
                    )
                );
            },
            0.5
    )->printout();


    Generation* test = GenerationFactory::getUsingFocusing(10, 10, 15, 0);
    test->printout();
    FitnessFunctionConstraints<int>(0, 5).reduceGenerationToInterval(test)->printout();

}
