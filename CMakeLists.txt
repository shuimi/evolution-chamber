cmake_minimum_required(VERSION 3.19)
project(Genetic_Algs)

set(CMAKE_CXX_STANDARD 14)

add_executable(Genetic_Algs main.cpp Main/headers/GeneticsTrainer.h Main/GeneticsTrainer.cpp Entities/BinaryChromosome.cpp Entities/headers/BinaryChromosome.h Entities/Population.cpp Entities/headers/Population.h Factories/ChromosomeFactory.cpp Factories/headers/ChromosomeFactory.h Factories/PopulationFactory.cpp Factories/headers/PopulationFactory.h)