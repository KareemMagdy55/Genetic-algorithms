#include "GeneticAlgorithm.h"

#include <algorithm>
#include<iostream>

#include "../Utilities/StaticData.h"
using namespace std;
static int seed = 0;

void GenericAlgorithm::run()
{
    int nGenerations = StaticData::get_max_generation();
    while (nGenerations--)
    {
        int mxIterationsPerGeneration = StaticData::get_mx_iteration_per_generation();
        vector<bool> currently_selected(population.size(), false);
        while (mxIterationsPerGeneration--)
        {
            // seed += 12 * M_1_PI;
            // select() => roulette wheel selection
            int firstIndv = select();
            while (currently_selected[firstIndv] == true)
            {
                // cout << firstIndv << endl;
                firstIndv = select();
            }
            int secondIndv = select();
            while (currently_selected[secondIndv] == true)
            {
                // cout << secondIndv << endl;
                // cout << "SECOND" << endl;
                secondIndv = select();
            }


            currently_selected[firstIndv] = true;
            currently_selected[secondIndv] = true;

            // crossover() => one point crossover
            Chromosome offspring1;
            Chromosome offspring2;

            crossover(population[firstIndv], population[secondIndv], offspring1, offspring2);


            // mutate => flip bit mutation
            mutate(offspring1);
            mutate(offspring2);

            // replace => Elitism replacement
            replace(firstIndv, offspring1);
            replace(secondIndv, offspring2);
        }
    }
}

void GenericAlgorithm::add_task(int task_exec_time)
{
    tasks_execution_time.push_back(task_exec_time);
}

void GenericAlgorithm::generate_population()
{
    for (int i = 0; i < StaticData::get_population_size(); i++)
    {
        Chromosome c;

        // If currenct chromosome c fitness is greater than max time limit replace the chromosome
        // So the population do not have infeasible solutions.
        while (c.calc_fitness(tasks_execution_time) > StaticData::get_max_time_limit())
        {
            const Chromosome tmp;
            c = tmp;
        }
        // cout << c.get_genes(0, StaticData::get_chromsome_size()) << endl;
        population.push_back(c);
    }
    individuals_fitness.resize(population.size());
}

int GenericAlgorithm::calc_fitness()
{
    int totalFitness = 0;


    for (int i = 0; i < population.size(); i++)
    {
        individuals_fitness[i] = population[i].calc_fitness(tasks_execution_time);
        totalFitness += individuals_fitness[i];
    }

    return totalFitness;
}

int GenericAlgorithm::select()
{
    // roulette wheel selection algorithm
    calc_fitness();
    vector<pair<double, int>> reversedFitness(individuals_fitness.size());

    for (int i = 0; i < individuals_fitness.size(); i++)
    {
        reversedFitness[i] = make_pair(1.0 / individuals_fitness[i], i);
    }
    sort(reversedFitness.begin(), reversedFitness.end());
    const double pick = RAND_FRAC(0, 1);

    double cumulative = 0.0;
    for (int i = 0; i < population.size(); ++i)
    {
        cumulative += reversedFitness[i].first;
        if (cumulative > pick)
        {
            // cout << "cumm : " << cumulative << endl;
            // cout << "pick : " << pick << endl;
            // cout << "i : " << reversedFitness[i].second;
            return reversedFitness[i].second;
        }
    }
    return static_cast<int>(reversedFitness.size()) - 1;
}


void GenericAlgorithm::crossover(Chromosome& parent1, Chromosome& parent2, Chromosome& offspring1,
                                 Chromosome& offspring2)
{
    // roulette wheel selection algorithm

    int crossover_point = RAND_INT(1, StaticData::get_chromsome_size() - 2);
    double r2 = RAND_FRAC(0.0f, 1.0f);

    if (r2 > StaticData::get_crossover_prop()) return;

    offspring1 = parent1;
    offspring2 = parent2;

    Chromosome tmp = offspring1;

    offspring1.replace_genes(crossover_point, offspring2);
    offspring2.replace_genes(crossover_point, tmp);
}

void GenericAlgorithm::replace(int parentIdx, Chromosome& offspring)
{
    Chromosome parent1 = population[parentIdx];

    int offspringFitness = offspring.calc_fitness(tasks_execution_time);

    if (offspringFitness < parent1.calc_fitness(tasks_execution_time) and offspringFitness <
        StaticData::get_max_time_limit())
    {
        population[parentIdx] = offspring;
        // cout << "parent1 : " << parent1.calc_fitness(tasks_execution_time) << endl;
        // cout << "offspring" << offspringFitness << endl;
    }
}

void GenericAlgorithm::mutate(Chromosome& chromosome)
{
    for (int i = 0; i < StaticData::get_chromsome_size(); i++)
    {
        srand(StaticData::get_chromsome_size() * i * population.size());
        double r = RAND_FRAC(0, 1);

        if (r <= StaticData::get_mutation_prop())
        {
            chromosome.mutate(i);
        }
    }
}

Chromosome GenericAlgorithm::get_the_fittest()
{
    calc_fitness();
    int mnFitnessIdx = min_element(individuals_fitness.begin(),
                                   individuals_fitness.end()) - individuals_fitness.begin();


    return population[mnFitnessIdx];
}

vector<int> GenericAlgorithm::get_tasks_execution_time()
{
    return tasks_execution_time;
}
