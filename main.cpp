#include <iostream>

#include "Main/Subscriptions.h"
#include "Selection/Breeding.h"
#include "Factoring/GenerationFactory.h"
#include "Morphing/Crossover.h"
#include "Morphing/Mutation.h"
#include "Mating.h"

int main() {


    //INITIALIZATION

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

    auto condition = [=](double estimationValue) {
        return (estimationValue >= fitnessFunction(constraints->getMean()));
    };

    Generation* initialGeneration;

    std::cout << "INITIAL GENERATION::";

    int dice = rand() % 2;

    if(dice == 0){
        std::cout << "SHOTGUN::\n";
        initialGeneration = GenerationFactory::getUsingShotgun(
            leftBound,
            rightBound,
            initialIndividualsAmount,
            0
        );
    }
    else{
        std::cout << "FOCUSING::\n";
        initialGeneration = GenerationFactory::getUsingFocusing(
            leftBound,
            rightBound,
            initialIndividualsAmount,
            0
        );
    }

    initialGeneration->printout();

    Generation* currentGeneration = initialGeneration->copy();
    Generation* previousGeneration = initialGeneration->copy();

    auto customEstimation = [=](int decimal){
        return ((double)fitnessFunction(decimal) / (
                fitnessFunction(
                        currentGeneration->getWithMaxEstimation(fitnessFunction)->getDecimal()
                )
            )
        );
    };

    //SETTING UP MATING CONFIG

    Mating* mating = new Mating(0.7, 0.3);

    std::vector<crossFunction> myCrossOperatorsSet = {
            Crossover::doublePoint,
            Crossover::CX,
            Crossover::fibonacci
    };
    std::vector<mutationFunction> myMutationOperatorsSet = {
//            Mutation::swapFibonacci,
            Mutation::inversion
    };

//    std::vector<crossFunction> maxCrossOperatorsSet = {
//            Crossover::PMX,
//            Crossover::OX,
//            Crossover::goldenRatio
//    };
//    std::vector<mutationFunction> maxMutationOperatorsSet = {
//            Mutation::transpose,
//            Mutation::simple
//    };

    mating->add(myCrossOperatorsSet);
    mating->add(myMutationOperatorsSet);

    //EVOLUTION

    for(int generationIndex = 0; generationIndex < generationsAmount; generationIndex++){

        previousGeneration = currentGeneration->copy();

        dice = rand() % 3;

        //BREEDING SECTION

        if(dice == 0)
        currentGeneration = Breeding::random(currentGeneration);
        else if(dice == 1)
        currentGeneration = Breeding::inbreeding(
                initialGeneration,
                previousGeneration
        );
        else if(dice == 2)
        currentGeneration = Breeding::inbreeding(
                initialGeneration,
                previousGeneration,
                condition,
                fitnessFunction
        );

        //MATING SECTION

        currentGeneration = mating->execute(currentGeneration);
        currentGeneration = constraints->reduceGenerationToInterval(currentGeneration);

        //SELECTION SECTION

        currentGeneration->reduceToUnique();
        currentGeneration = Breeding::select(
            currentGeneration,
            customEstimation,
            fitnessFunction
        );

        //PRINTOUTS

        currentGeneration->printout();
    }

//    for(int generationIndex = 0; generationIndex < 5000; generationIndex++){
//        currentGeneration = GenerationFactory::getUsingShotgun(
//                leftBound,
//                rightBound,
//                initialIndividualsAmount,
//                0
//        );
//        currentGeneration = mating->execute(currentGeneration);
//        currentGeneration = constraints->reduceGenerationToInterval(currentGeneration);
//        currentGeneration->reduceToUnique();
//        currentGeneration->printout();
//    }

//    Breeding::scaleBased(initialGeneration,customEstimation,0.5);

}
