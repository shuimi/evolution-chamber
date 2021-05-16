#include <iostream>
#include "Main/headers/EvolutionChamber.h"
#include "Morphers/headers/PopulationMorpher.h"

int main() {

    EvolutionChamber* evo = new EvolutionChamber();


    evo->setFitnessFunction([](double x){
        return x * x + 0.1 * x - 23;
    });
    std::cout << evo->executeFitnessFunction(5) << "\n\n";


    BinaryChromosome* chroma = new BinaryChromosome(131);
    chroma->printout();
    chroma->invert();
    chroma->printout();


    Population* testPopulation = new Population(1);
    testPopulation->addIndividual(new BinaryChromosome(51));
    testPopulation->addIndividual(new BinaryChromosome(13));
    testPopulation->printout();

    Population* testPopulationShotgun =
            PopulationMorpher::getPopulationUsingShotgun(9, 14);
    Population* testPopulationFocus =
            PopulationMorpher::getPopulationUsingFocusing(11, 3);

    testPopulationShotgun->printout();
    testPopulationShotgun->statPrintout();
    testPopulationFocus->printout();
    testPopulationFocus->statPrintout();


}
