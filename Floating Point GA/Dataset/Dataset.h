#ifndef DATASET_H
#define DATASET_H

#include <vector>
#include <string>


struct Dataset {
    int num_chemicals;
    double total_proportion;
    std::vector<float> lower_bounds;
    std::vector<float> upper_bounds;
    std::vector<float> cost_coefficients;

};

std::vector<Dataset>& get_datasets();

bool load_datasets_from_file(const std::string& filename);

#endif
