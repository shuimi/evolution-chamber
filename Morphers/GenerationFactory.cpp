//
// Created by Vladimir on 15.05.2021.
//

#include "headers/GenerationFactory.h"


Generation *GenerationFactory::getUsingShotgun(int leftBound, int rightBound, int individualsAmount) {
    return getUsingShotgun(leftBound, rightBound, individualsAmount, 0);
}


Generation *GenerationFactory::getUsingFocusing(int focusPoint, int range, int individualsAmount) {
    return getUsingFocusing(focusPoint, range, individualsAmount, 0);
}


Generation *GenerationFactory::getUsingShotgun(int leftBound, int rightBound,
                                               int individualsAmount, int initPopulationIndex) {
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());

    std::vector<int> i{ leftBound,  rightBound + 1};
    std::vector<double> w{  1,  0,  1};
    std::piecewise_constant_distribution<> constantDistribution(i.begin(), i.end(), w.begin());

    Generation* population = new Generation(initPopulationIndex);

    for(int i = 0; i < individualsAmount + 1; i++){
        population->addIndividual(
                new BinaryChromosome(
                        constantDistribution(generator)
                )
        );
    }

    return population;
}


Generation *GenerationFactory::getUsingFocusing(int focusPoint, int range,
                                                int individualsAmount, int initPopulationIndex) {
    std::random_device randomDevice{};
    std::mt19937 generator{randomDevice()};
    std::normal_distribution<> normalDistribution{(double)focusPoint, (double)range};

    Generation* population = new Generation(initPopulationIndex);

    for (int i = 0; i < individualsAmount; i++) {
        population->addIndividual(
                new BinaryChromosome(
                        normalDistribution(generator)
                )
        );
    }
    population->addIndividual(new BinaryChromosome(focusPoint));

    return population;
}
