cmake_minimum_required(VERSION 3.28)
project(Genetic_algorithms)

set(CMAKE_CXX_STANDARD 17)

add_executable(Genetic_algorithms main.cpp
        Chromosome/Chromosome.h
        Chromosome/Chromosome.cpp
        "Utilities/StaticData.h"
        GeneticAlgorithm/GeneticAlgorithm.h
        GeneticAlgorithm/GeneticAlgorithm.cpp
        GeneticAlgorithm/GeneticAlgorithm.cpp
        Utilities/StaticData.cpp)
