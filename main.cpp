#include <iostream>
#include <cstdlib>
#include <ctime>
#include "GeneticAlgorithm/GeneticAlgorithm.h"
#include "Utilities/StaticData.h"

using namespace std;

void printCoreTasks(Chromosome& fittest, const vector<int>& tasks_execution_time, const string& corenum ,const string& core_id) {

    cout << "=========================== Core " << corenum << " tasks ============================" << endl;
    int totalExecTime = 0;

    string genes = fittest.get_genes(0, StaticData::get_chromsome_size());
    for (int i = 0; i < StaticData::get_chromsome_size(); ++i) {
        if (genes[i] == core_id[0]) {
            cout << "Task number : " << i << endl;
            cout << "Task execution time : " << tasks_execution_time[i] << endl;
            cout << "----------------------------------------\n";
            totalExecTime += tasks_execution_time[i];
        }
    }

    cout << "Total Execution : " << totalExecTime << endl << endl;
}

int main() {
    int nTestCases;
    cin >> nTestCases;

    for (int testcase = 0; testcase < nTestCases; ++testcase) {
        GenericAlgorithm generic_algorithm;

        int max_time_limit;
        int chromsome_size;
        cin >> max_time_limit >> chromsome_size;

        StaticData::set_max_time_limit(max_time_limit);
        StaticData::set_chromsome_size(chromsome_size);

        StaticData::set_mutation_prop(RAND_FRAC(0.001f, 0.1f));
        StaticData::set_crossover_prop(RAND_FRAC(0.4f, 0.7f));

        for (int i = 0; i < chromsome_size; ++i) {
            int task_execution_time;
            cin >> task_execution_time;
            generic_algorithm.add_task(task_execution_time);
        }

        generic_algorithm.generate_population();
        generic_algorithm.run();

        auto tasks_execution_time = generic_algorithm.get_tasks_execution_time();
        Chromosome the_fittest = generic_algorithm.get_the_fittest();

        cout << "||||| The Best Solution |||||" << endl << endl;
        cout << "Test case index : " << testcase << endl;
        cout << "Chromosome representation : " << the_fittest.get_genes(0, chromsome_size) << endl;
        cout << "Chromosome total fitness : " << the_fittest.calc_fitness(tasks_execution_time) << endl << endl;

        printCoreTasks(the_fittest, tasks_execution_time, "1", "1");
        printCoreTasks(the_fittest, tasks_execution_time, "2", "0");
    }

    return 0;
}
