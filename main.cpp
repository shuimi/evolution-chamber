#include <iostream>
#include "Main/headers/EvolutionChamber.h"

int main() {

    EvolutionChamber* evo = new EvolutionChamber();

    evo->setFitnessFunction([](double x){
        return x * x + 0.1 * x - 23;
    });

    Generation* testPopulationShotgun =
            GenerationFactory::getPopulationUsingShotgun(9, 14, 10);
    Generation* testPopulationFocus =
            GenerationFactory::getPopulationUsingFocusing(11, 3, 10);

    testPopulationFocus->printout();
    testPopulationFocus->statPrintout();
    testPopulationFocus->estimate(evo->getFitnessFunction());
    testPopulationFocus->printoutEstimation();
    std::cout << evo->executeFitnessFunction(10) << "\n\n";

    evo->selectionElite(testPopulationFocus, [evo](double estimationValue){
        return (estimationValue >= evo->executeFitnessFunction(11));
    });

    testPopulationFocus->printout();
    testPopulationFocus->statPrintout();

    BinaryChromosome* a = new BinaryChromosome(17);
    BinaryChromosome* b = new BinaryChromosome(12);

    std::cout << BinaryChromosome::normalizedDistance(a, b);
}
