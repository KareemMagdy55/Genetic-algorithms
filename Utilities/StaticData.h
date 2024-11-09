//
// Created by karee on 11/8/2024.
//

#pragma  once
#include <random>

#define MAKE_SEED   (srand(static_cast<unsigned int>(time(0))));
static std::mt19937 gen1(std::random_device{}());

#define RAND_INT(st, end) (std::uniform_int_distribution<int>(st, end)(gen1))

static std::mt19937 gen2(std::random_device{}());

#define RAND_FRAC(st, end) (std::uniform_real_distribution<float>(st, end)(gen2))
#include <vector>


class StaticData {
private:
    static const int MX_GENERATION = 50;
    static const int POPULATION_SIZE = 150;
    static const int MX_ITERATIONS_PER_GENERATION = 10;
    static int max_time_limit;
    static int chromsome_size;
    static double crossover_prop;
    static double mutation_prop;
public:
    static void set_chromsome_size(int _chromsome_size);
    static void set_max_time_limit(int _max_time_limit);
    static void set_crossover_prop(double pc);
    static void set_mutation_prop(double pm);

    static int get_chromsome_size();
    static int get_max_time_limit();
    static int get_max_generation();
    static int get_population_size();
    static int get_mx_iteration_per_generation();

    static double get_crossover_prop();
    static double get_mutation_prop();
};



