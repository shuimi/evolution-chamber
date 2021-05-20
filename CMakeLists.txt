cmake_minimum_required(VERSION 3.19)
project(Genetic_Algs)

set(CMAKE_CXX_STANDARD 14)

add_executable(Genetic_Algs main.cpp Entities/BinaryChromosome.cpp Entities/BinaryChromosome.h Entities/Generation.cpp Entities/Generation.h Morphing/GenerationFactory.cpp Morphing/GenerationFactory.h Morphing/Crossover.cpp Morphing/Crossover.h Entities/Population.cpp Entities/Population.h Main/FunctionConstraints.h Breeding.cpp Breeding.h Morphing/Mutation.cpp Morphing/Mutation.h Service/Maths.cpp Service/Maths.h Gen.cpp Gen.h)