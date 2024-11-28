std::vector<Dataset> datasets;

std::vector<Dataset>& get_datasets() {
    return datasets;
}

bool load_datasets_from_file() {
    const std::string filename = INPUT_FILE_NAME;
    std::ifstream infile(filename);

    if (!infile) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return false;
    }

    int num_datasets;
    infile >> num_datasets;

    datasets.clear();

    for (int i = 0; i < num_datasets; ++i) {
        Dataset dataset;


        infile >> dataset.num_chemicals >> dataset.total_proportion;


        dataset.lower_bounds.resize(dataset.num_chemicals);
        dataset.upper_bounds.resize(dataset.num_chemicals);

        for (int j = 0; j < dataset.num_chemicals; ++j) {
            infile >> dataset.lower_bounds[j] >> dataset.upper_bounds[j];
        }


        dataset.cost_coefficients.resize(dataset.num_chemicals);
        for (int j = 0; j < dataset.num_chemicals; ++j) {
            infile >> dataset.cost_coefficients[j];
        }


        datasets.push_back(dataset);
    }

    infile.close();
    return true;
}
