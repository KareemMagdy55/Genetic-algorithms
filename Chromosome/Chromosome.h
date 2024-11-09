#ifndef CHROMOSOME_H
#define CHROMOSOME_H
#include <string>
#include <vector>
using namespace std ;


class Chromosome {
private:
    std::string body ;
public:
    Chromosome();
    int calc_fitness(vector<int>& tasks_execution_time);
    void mutate(int n_gene);
    string get_genes(int start, int end);
    void replace_genes(int crossover_point, Chromosome& c);
};



#endif //CHROMOSOME_H
