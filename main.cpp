#include <iostream>
#include "Main/headers/EvolutionChamber.h"

int main() {

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

    Generation* testPopulationFocus =
            GenerationFactory::getUsingFocusing(11, 3, 10);

    testPopulationFocus->printout();
    testPopulationFocus->statPrintout();
    testPopulationFocus->estimate(evolution->getFitnessFunction());
    testPopulationFocus->printoutEstimation();
    std::cout << evolution->executeFitnessFunction(10) << "\n\n";

    evolution->selectionElite(testPopulationFocus, [evolution](double estimationValue){
        return (estimationValue >= evolution->executeFitnessFunction(11));
    });

    testPopulationFocus->printout();
    testPopulationFocus->statPrintout();

    BinaryChromosome* a = new BinaryChromosome(17);
    BinaryChromosome* b = new BinaryChromosome(12);

    std::cout << BinaryChromosome::normalizedDistance(a, b);

}
