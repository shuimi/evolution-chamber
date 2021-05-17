cmake_minimum_required(VERSION 3.19)
project(Genetic_Algs)

set(CMAKE_CXX_STANDARD 14)

add_executable(Genetic_Algs main.cpp Main/headers/EvolutionChamber.h Main/EvolutionChamber.cpp Entities/BinaryChromosome.cpp Entities/headers/BinaryChromosome.h Entities/Generation.cpp Entities/headers/Generation.h Morphers/GenerationFactory.cpp Morphers/headers/GenerationFactory.h Morphers/service/MorphingFactor.cpp Morphers/service/MorphingFactor.h Entities/Population.cpp Entities/headers/Population.h Morphers/service/FitnessFunctionConstraints.h)