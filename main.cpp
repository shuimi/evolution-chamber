#include <iostream>
#include "Main/headers/EvolutionChamber.h"

int main() {

    double leftBound = 9;
    double rightBound = 14;

    int initialIndividualsAmount = 10;
    int generationsAmount = 50;

    double crossingProbability = 0.7;
    double mutationProbability = 0.3;

    GenerationFactory::getUsingCovering(
            leftBound,
            rightBound
    )->printout();

    EvolutionChamber* evolution = new EvolutionChamber([](double x){
            return x * x + 0.1 * x - 23;
        },
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

    evolution->getInitialGeneration()->printout();

    for(int i = 0; i < generationsAmount; i++){
        evolution->getNextGeneration()->printout();
    }


//    Generation* testPopulationFocus =
//            GenerationFactory::getUsingFocusing(11, 3, 10);
//
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
