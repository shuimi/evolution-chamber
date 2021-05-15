#include <iostream>
#include "Main/headers/EvolutionChamber.h"

int main() {

    EvolutionChamber* evo = new EvolutionChamber();

    evo->setFitnessFunction([](double x){
        return x * x + 0.1 * x - 23;
    });
    std::cout << evo->executeFitnessFunction(5) << "\n";


    BinaryChromosome* chroma = new BinaryChromosome(6);
    std::cout << chroma->getDecimal() << "\n";
    std::cout << chroma->getBinaryString() << "\n";


    Population* testPopulation = new Population(1);
    testPopulation->addIndividual(new BinaryChromosome(501));
    for(int i = 0; i < 5; i++){testPopulation->addIndividual(new BinaryChromosome(501 + i));}
    testPopulation->addIndividual(new BinaryChromosome(13));
    testPopulation->printout();


}
