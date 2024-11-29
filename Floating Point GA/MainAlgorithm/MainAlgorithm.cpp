#include <algorithm>
#include <float.h>

#include "../MainLibrary.h"

const int MX_GENERATION = 100;
const int POPULATION_SIZE = 500;
const int K_BEST = 100;

std::vector<Chromosome> offsprings;
std::vector<Chromosome> parents;
Dataset dataset;


bool isValidDataset()
{
    if(dataset.num_chemicals != dataset.cost_coefficients.size()) return false;

    float sum = std::accumulate(dataset.upper_bounds.begin(), dataset.upper_bounds.end(), 0.0f) ;
    if (sum < dataset.total_proportion)
        return false;

    sum = std::accumulate(dataset.lower_bounds.begin(), dataset.lower_bounds.end(), 0.0f) ;
    if (sum > dataset.total_proportion) return false;

    return true;

}

// ----------- Eval Fitness -----------------
float evaluate_fitness(Chromosome& c)
{
    float fitness = 0.0;
    for (int i = 0; i < c.proportions.size(); i++)
        fitness += c.proportions[i] * dataset.cost_coefficients[i];
    return fitness;
}

// --------------------- Intial Generation -----------------------
void generate_intital_population()
{
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        Chromosome c;
        c.proportions.resize(dataset.num_chemicals);
        for (int j = 0; j < dataset.num_chemicals; ++j)
        {
            const auto& lb = dataset.lower_bounds[j];
            const auto& ub = dataset.upper_bounds[j];
            c.proportions[j] = generateRandomFloat(lb, ub);

            c.proportions[j] = std::round(c.proportions[j] * 100.0f) / 100.0f;
        }
        adjust_proportions(c.proportions, dataset);
        parents.push_back(c);
    }

    // for (auto& c : population)
    // {
    //     for (auto& p : c.proportions)
    //         std::cout << p << ' ';
    //     std::cout << std::endl;
    // }
}


// --------------------- Selection (Tournment Selection) -------------

void select()
{
    std::vector<Chromosome> mating_pool;
    if (parents.size() % 2 != 0)
    {
        mating_pool.push_back(parents.back());
        parents.pop_back();
    }
    int i = 0;
    while (i < parents.size())
    {
        auto& first = parents[i];
        auto& second = parents[i + 1];

        if (evaluate_fitness(first) < evaluate_fitness(second))
            mating_pool.push_back(first);
        else mating_pool.push_back(second);

        i += 2;
    }
    parents = mating_pool;
    offsprings = mating_pool;
}

// ------------------ crossover ( 2-point crossover) ----------------

void crossover()
{
    const int n = offsprings.size();
    int p1 = generateRandomInt(0, n - 1);
    int p2 = generateRandomInt(0, n - 1);
    if (p1 < p2) std::swap(p1, p2);

    int idx1 = generateRandomInt(0, n - 1);
    int idx2;
    do
    {
        idx2 = generateRandomInt(0, n - 1);
    }
    while (idx2 != idx1);


    Chromosome& parent1 = offsprings[idx1];
    Chromosome& parent2 = offsprings[idx2];


    while (p1 < p2)
    {
        std::swap(parent1.proportions[p1], parent2.proportions[p1]);
        p1++;
    }

    adjust_proportions(parent1.proportions, dataset);
    adjust_proportions(parent2.proportions, dataset);
}

// -------------------- Muatate ( non-uniform mutation)-----------------
void mutate(int current_generation)
{
    const int n = offsprings.size() - 1;
    int idx = generateRandomInt(0, n);

    Chromosome& c = offsprings[idx];
    int chromosomeLength = dataset.num_chemicals;
    float r = generateRandomFloat(0, 1);
    int b = generateRandomInt(1, 5);


    for (int i = 0; i < chromosomeLength; i++)
    {
        float delta_lb = c.proportions[i] - dataset.lower_bounds[i];
        float delta_ub = dataset.upper_bounds[i] - c.proportions[i];

        float r1 = generateRandomFloat(0, 1);
        float y = (r1 <= 0.5f) ? delta_lb : delta_ub;

        float pwr = powf((1 - current_generation / MX_GENERATION), b);
        float val = y * (1 - powf(r, pwr));


        c.proportions[i] += val;
    }
    adjust_proportions(c.proportions, dataset);
}

// ----------------- replace (elitist replacement) ------------------
void replace()
{
    std::vector<std::pair<int, int>> bestChromosomes;
    const int n = parents.size();
    for (int i = 0; i < n; i++)
    {
        bestChromosomes.emplace_back(evaluate_fitness(parents[i]), i);
    }

    sort(bestChromosomes.begin(), bestChromosomes.end());
    for (int i = 0; i < std::min(K_BEST, n); i++)
    {
        int idx = bestChromosomes[i].second;
        float parentFitness = evaluate_fitness(parents[idx]);
        float offspringFitness = evaluate_fitness(offsprings[idx]);

        // Minimize cost;
        if (parentFitness < offspringFitness)
            offsprings[idx] = parents[idx];
    }
}

Chromosome getTheBest()
{
    float fitness = FLT_MAX;
    Chromosome c;

    for (auto& indv : parents)
        if (evaluate_fitness(indv) < fitness)
            c = indv;

    return c;
}

void output(std::string& out)
{
    Chromosome c = getTheBest();
    out += ("Chemical Proportions: ");
    for (auto& prop : c.proportions)
        out += (std::to_string(prop) + " ");
    out += ("\nTotal Cost: ");
    out += (std::to_string(evaluate_fitness(c)));
    out += "\n======================================================\n";
}

void run(const Dataset& ds, std::string& out)
{
    dataset = ds;
    if (!isValidDataset())
    {
        out += "DATASET NOT VALID\n";
        return;
    }
    generate_intital_population();
    for (int g = 0; g < MX_GENERATION; g++)
    {
        select();
        crossover();
        mutate(g);
        replace();

        parents = offsprings;
        offsprings.clear();
    }
    output(out);
}
