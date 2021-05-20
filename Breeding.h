//
// Created by Vladimir on 20.05.2021.
//

#ifndef GENETIC_ALGS_BREEDING_H
#define GENETIC_ALGS_BREEDING_H


#include "Entities/Generation.h"
#include "Main/FunctionConstraints.h"

class Breeding {
public:

    /// [description] This is service method.
    /// All candidates are evaluated by the fitness function, after which those that meet the fitnessRange are selected.
    /// @return Generation that contains individuals selected randomly
    static Generation* select(
            Generation* generation,
            ///<[in] Source generation
            std::function<bool(double)> fitnessRange,
            ///<[in] Defines the range of fitness function values for which candidates will be selected
            std::function<double(double)> fitnessFunction
            ///<[in] Fitness function
    );

    /// [description] This selection operator is random-driven.
    /// It select individuals randomly.
    /// @return Generation that contains individuals selected randomly
    static Generation* random(
        Generation* generation ///<[in] Parents Generation
    );

    /// [description] This selection operator is gen-similarity-driven.
    /// It select individuals with genome that most similar to most popular.
    /// It is based on normalized Hamming distance.
    /// @return Generation that contains individuals satisfying selection conditions
    static Generation* inbreeding(
        Generation* parents,
        ///<[in] Parents Generation
        Generation* descendants
        ///<[in] Descendants Generation
    );

    /// [description] This selection operator is elite-selection-driven.
    /// It select individuals with genome that most satisfying to selection conditions.
    /// @return Generation that contains individuals satisfying selection conditions
    static Generation* inbreeding(
        Generation* parents,
        ///<[in] Parents Generation
        Generation* descendants,
        ///<[in] Descendants Generation
        std::function<bool(double)> selectionCondition,
        ///<[in] Defines how operator select individuals
        std::function<double(double)> fitnessFunction
        ///<[in] Fitness function
    );

    /// [description] This selection operator is estimation-driven.
    /// It assigns score to individuals according to the conditions.
    /// It assigns score to individuals according to the conditions.
    /// @return Generation that contains individuals satisfying selection conditions
    static Generation* scaleBased(
        Generation* generation,
        ///<[in] Parents Generation
        std::function<double(double)> estimationFunction,
        ///<[in] Defines how operator select individuals
        double lowThreshold
        ///<[in] Defines lowest acceptable estimation for individuals to be added to new Generation
    );

    /// [description] This is service method.
    /// @return tuple of random individuals
    static std::tuple<BinaryChromosome*, BinaryChromosome*> selectRandomPair(
        Generation* generation ///<[in] Source Generation
    );

};


#endif //GENETIC_ALGS_BREEDING_H
