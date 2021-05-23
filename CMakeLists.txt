cmake_minimum_required(VERSION 3.19)
project(Genetic_Algs)

set(CMAKE_CXX_STANDARD 14)

add_executable(Genetic_Algs main.cpp Containers/Chromosome.cpp Containers/Chromosome.h Containers/Generation.cpp Containers/Generation.h Factoring/GenerationFactory.cpp Factoring/GenerationFactory.h Morphing/Crossover.cpp Morphing/Crossover.h Containers/Population.cpp Containers/Population.h Service/FunctionConstraints.h Selection/Breeding.cpp Selection/Breeding.h Morphing/Mutation.cpp Morphing/Mutation.h Service/Maths.cpp Service/Maths.h Misc/Gen.cpp Misc/Gen.h Mating.cpp Mating.h Main/Subscriptions.h)