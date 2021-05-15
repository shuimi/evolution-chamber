cmake_minimum_required(VERSION 3.19)
project(Genetic_Algs)

set(CMAKE_CXX_STANDARD 14)

add_executable(Genetic_Algs main.cpp Main/headers/EvolutionChamber.h Main/EvolutionChamber.cpp Entities/BinaryChromosome.cpp Entities/headers/BinaryChromosome.h Entities/Population.cpp Entities/headers/Population.h Factories/ChromosomeMorpher.cpp Factories/headers/ChromosomeMorpher.h Factories/PopulationMorpher.cpp Factories/headers/PopulationMorpher.h Factories/service/MutationFactor.cpp Factories/service/MutationFactor.h)