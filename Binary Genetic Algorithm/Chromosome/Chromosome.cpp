#include "Chromosome.h"

#include <algorithm>
#include <iostream>

#include "../Utilities/StaticData.h"
using namespace std ;

static int  count = 0 ;

string intToBinary(int n, int bits) {
    std::string binary_str = "";

    while (n > 0) {
        binary_str += (n % 2) ? '1' : '0';
        n /= 2;
    }

    std::reverse(binary_str.begin(), binary_str.end());

    while (binary_str.length() < bits) {
        binary_str = '0' + binary_str;
    }

    if (binary_str.length() > bits) {
        binary_str = binary_str.substr(binary_str.length() - bits);
    }

    return binary_str;
}
Chromosome::Chromosome()
{
    int randomNumber = RAND_INT(0, (1 << (StaticData::get_chromsome_size())) - 1);
    body = intToBinary(randomNumber, StaticData::get_chromsome_size());

}

int Chromosome::calc_fitness(vector<int>& tasks_execution_time)
{
    int core1ExecutionTime = 0;
    int core2ExecutionTime = 0;
    for (int i = 0; i < body.size(); i++)
    {
        if (body[i] == '1')
            core1ExecutionTime += tasks_execution_time[i];
        else
            core2ExecutionTime += tasks_execution_time[i];
    }
    return max(core1ExecutionTime, core2ExecutionTime);
}


string Chromosome::get_genes(int start, int end)
{
    int steps = (end - start);
    return body.substr(start, steps);
}

void Chromosome::mutate(int n_gene)
{
    // flipping
    body[n_gene] = body[n_gene] == '0' ? '1' : '0';
}

void Chromosome::replace_genes(int crossover_point, Chromosome& c)
{
    for (int i = crossover_point; i < body.size(); ++i)
    {
        body[i] = c.body[i];
    }
}
