cmake_minimum_required(VERSION 3.19)
project(Genetic_Algs)

set(CMAKE_CXX_STANDARD 14)

add_executable(Genetic_Algs main.cpp Main/EvolutionChamber.h Main/EvolutionChamber.cpp Entities/BinaryChromosome.cpp Entities/BinaryChromosome.h Entities/Generation.cpp Entities/Generation.h Morphers/GenerationFactory.cpp Morphers/GenerationFactory.h Morphers/Morphing.cpp Morphers/Morphing.h Entities/Population.cpp Entities/Population.h Morphers/FunctionConstraints.h Breeding.cpp Breeding.h)