//
// Created by karee on 11/8/2024.
//

#ifndef GENERICALGORITHM_H
#define GENERICALGORITHM_H
#include <unordered_map>
#include <vector>
#include "../Chromosome/Chromosome.h"


class GenericAlgorithm {
    std::vector<int> tasks_execution_time;
    std::vector<Chromosome> population;
    vector<int> individuals_fitness;

public:
    void add_task(int task_exec_time);
    void generate_population();
    vector<int> get_tasks_execution_time();
    void run();
    void mutate(Chromosome& chromosome);
    int calc_fitness();
    void replace(int parentIdx, Chromosome& offspring);
    int select();
    Chromosome get_the_fittest();
    void crossover(Chromosome& parent1, Chromosome& parent2, Chromosome& offspring1, Chromosome& offspring2);

};



#endif //GENERICALGORITHM_H
