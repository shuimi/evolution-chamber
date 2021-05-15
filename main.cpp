#include <iostream>
#include "Main/headers/GeneticsTrainer.h"

int main() {

    GeneticsTrainer* geneticsTrainer = new GeneticsTrainer();

    geneticsTrainer->setFitnessFunction([](double x){
        return x * x + 0.1 * x - 23;
    });

//    std::cout << geneticsTrainer->executeFitnessFunction(5) << "\n";

    BinaryChromosome* testCh = new BinaryChromosome(6);
    std::cout << testCh->getDecimal() << "\n";
//    std::cout << testCh->getBinaryString() << "\n";

    Population* testPopulation = new Population();

    testPopulation->addIndividual(testCh);

    std::cout << *testPopulation;

}
