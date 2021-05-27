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

    int leftBound = 9;
    int rightBound = 14;

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
    Generation* preparedToMating = new Generation(-1);

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

        if (currentGeneration->size() < 2) break;
        previousGeneration = currentGeneration->copy();

//BREEDING SECTION

        while(preparedToMating->size() < 2){

            if(generationIndex == 0){
                preparedToMating = Breeding::random(currentGeneration, previousGeneration->size() / 2);
                std::cout << "Breeding::random\n";
            }
            else{

                dice = rand() % 3;

                if(dice == 0){
                    preparedToMating = Breeding::random(currentGeneration, previousGeneration->size() / 2);
                    std::cout << "Breeding::random\n";
                }
                else if(dice == 1){
                    preparedToMating = Breeding::inbreeding(
                            initialGeneration,
                            previousGeneration
                    );
                    std::cout << "Breeding::inbreeding (gen-similarity)\n";
                }
                else{
                    preparedToMating = Breeding::inbreeding(
                            initialGeneration,
                            previousGeneration,
                            [=](double estimation){
                                return estimation > fitnessFunction(constraints->getMean());
                            },
                            fitnessFunction
                    );
                    std::cout << "Breeding::inbreeding (elite)\n";
                }

            }

        }

        std::cout << "BREEDING RESULT:\n";
        currentGeneration->printout();
        preparedToMating->printout();

//MATING SECTION

        preparedToMating = mating->executeSingle(preparedToMating);
        currentGeneration->add(preparedToMating);
        currentGeneration->setIndex(currentGeneration->getIndex() + 1);

        std::cout << "MATING RESULT:\n";
        currentGeneration->printout();

//SELECTION SECTION

        currentGeneration = Breeding::select(
            currentGeneration,
            [=](double estimation){
                return estimation > fitnessFunction(constraints->getMean());
            },
            fitnessFunction
        );
        currentGeneration = constraints->reduceGenerationToInterval(currentGeneration);

//        if(currentGeneration->size() != 0)
//        currentGeneration->reduceToUnique();

        std::cout << "SELECTION RESULT:\n";
        currentGeneration->printout();

    }

//    Breeding::scaleBased(initialGeneration,customEstimation,0.5);

}
