cmake_minimum_required(VERSION 3.28)
project(Floating_Point_GA)

set(CMAKE_CXX_STANDARD 17)

add_executable(Floating_Point_GA main.cpp)
add_executable(Helpers "Helper Functions/Helpers.cpp")
add_executable(MainAlgorithm "MainAlgorithm/MainAlgorithm.cpp")
add_executable(dataset "Dataset/Dataset.cpp")
