#include "MainLibrary.h"
#include "MainAlgorithm/MainAlgorithm.cpp"
#include "Dataset/Dataset.cpp"

using namespace std;
int main()
{
    load_datasets_from_file();
    auto datasets = get_datasets();

    string output ;
    for(int i = 0 ; i < datasets.size() ; i ++)
    {
        auto& dataset = datasets[0];
        output += ("Dataset " + to_string(i + 1) + "\n");
        run(dataset, output);
    }
    writeToFile(output );

}
