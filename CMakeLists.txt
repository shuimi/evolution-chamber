cmake_minimum_required(VERSION 3.19)
project(Genetic_Algs)

set(CMAKE_CXX_STANDARD 14)

add_executable(Genetic_Algs main.cpp GeneticsTrainer.h GeneticsTrainer.cpp Chromosome.cpp Chromosome.h)