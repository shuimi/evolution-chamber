#include <iostream>
#include "GeneticsTrainer.h"
#include "Chromosome.h"

int main() {

    GeneticsTrainer* geneticsTrainer = new GeneticsTrainer();

    geneticsTrainer->setFitnessFunction([](double x){
        return x * x + 0.1 * x - 23;
    });

    std::cout << geneticsTrainer->executeFitnessFunction(5) << "\n";

    Chromosome* testCh = new Chromosome(432);
    std::cout << testCh->getDecimal() << "\n";
    std::cout << testCh->getBinaryString() << "\n";

}
