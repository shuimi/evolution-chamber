#include <iostream>
#include "Main/headers/EvolutionChamber.h"

int main() {

    double leftBound = 9;
    double rightBound = 14;

    int initialIndividualsAmount = 10;
    int generationsAmount = 50;

    double crossingProbability = 0.7;
    double mutationProbability = 0.3;

    EvolutionChamber* evolution = new EvolutionChamber([](double x){
            return x * x + 0.1 * x - 23;
        },
        GenerationFactory::getUsingShotgun(
            9,
            14,
            10
        ),
        new MorphingFactor(
            0.7,
            0.3
        ),
        50
    );

    evolution->getInitialGeneration()->printout();

    for(int i = 0; i < generationsAmount; i++){
        evolution->getNextGeneration()->printout();
    }


//    //TESTS: Generations factoring:
//
//    GenerationFactory::getUsingCovering(
//            leftBound,
//            rightBound
//    )->printout();
//
//    GenerationFactory::getUsingFocusing(
//            leftBound,
//            rightBound,
//            initialIndividualsAmount
//    )->printout();
//
//    GenerationFactory::getUsingShotgun(
//            leftBound,
//            rightBound,
//            initialIndividualsAmount
//    )->printout();


//    testPopulationFocus->printout();
//    testPopulationFocus->statPrintout();
//    testPopulationFocus->estimate(evolution->getFitnessFunction());
//    testPopulationFocus->printoutEstimation();
//    std::cout << evolution->executeFitnessFunction(10) << "\n\n";
//
//    evolution->selectionElite(testPopulationFocus, [evolution](double estimationValue){
//        return (estimationValue >= evolution->executeFitnessFunction(11));
//    });
//
//    testPopulationFocus->printout();
//    testPopulationFocus->statPrintout();
//
//    BinaryChromosome* a = new BinaryChromosome(17);
//    BinaryChromosome* b = new BinaryChromosome(12);
//
//    std::cout << BinaryChromosome::normalizedDistance(a, b);

}
