#include"StaticData.h"

#include <iostream>

int StaticData::max_time_limit = 0;
int StaticData::chromsome_size = 0;

double StaticData::mutation_prop = RAND_FRAC(0.001f, 0.1f);
double StaticData::crossover_prop = RAND_FRAC(0.4f, 0.7f);

void StaticData::set_chromsome_size(int _chromsome_size)
{
    chromsome_size = _chromsome_size;
}

void StaticData::set_max_time_limit(int _max_time_limit)
{
    max_time_limit = _max_time_limit;
}

int StaticData::get_max_generation()
{
    return MX_GENERATION;
}

int StaticData::get_population_size()
{
    return POPULATION_SIZE;
}

int StaticData::get_chromsome_size()
{
    return chromsome_size;
}

int StaticData::get_max_time_limit()
{
    return max_time_limit;
}

double StaticData::get_crossover_prop()
{
    return crossover_prop;
}
double StaticData::get_mutation_prop()
{
    return mutation_prop;
}
void StaticData::set_crossover_prop(double pc)
{
    crossover_prop = pc;
}
void StaticData::set_mutation_prop(double pm)
{
    mutation_prop = pm;
}
int StaticData::get_mx_iteration_per_generation()
{
    return MX_ITERATIONS_PER_GENERATION;
}



