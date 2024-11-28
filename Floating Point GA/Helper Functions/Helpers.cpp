#include <iomanip>
#include <vector>
#include <random>

#include "../MainLibrary.h"

#define LOWER_BOUND (0.0)
#define UPPER_BOUND (1e8)


void writeToFile(std::string str) {
    const std::string filename = OUTPUT_FILE_NAME;
    std::ofstream outputFile(filename);
    if (outputFile.is_open()) {
        outputFile << str;
        outputFile.close();
    } else {
        std::cerr << "Failed to open the file for writing." << std::endl;
    }
}
void _round(float& number)
{
    if (fmod(number, 1) >= 0.9999f)
        number = std::round(number);
}
int generateRandomInt(int lowerBound = LOWER_BOUND, int upperBound = UPPER_BOUND)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<int> dis(lowerBound, upperBound);
    return dis(gen);
}

float generateRandomFloat(float lowerBound = LOWER_BOUND, float upperBound = UPPER_BOUND)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_real_distribution<float> dis(lowerBound, upperBound);
    return std::round(dis(gen) * 100.0f) / 100.0f;
}

void _clamp(float& proportion, float lower_bound, float upper_bound)
{
    if (proportion < lower_bound)
        proportion = lower_bound;
    else if (proportion > upper_bound)
        proportion = upper_bound;
}
std::vector<float> adjust_proportions(std::vector<float>& proportions, const Dataset& dataset)
{
    std::setprecision(5);
    const int n = dataset.lower_bounds.size();
    float sum = 0.0f;
    for(int i = 0 ; i < proportions.size() ; i ++)
    {
        _clamp(proportions[i], dataset.lower_bounds[i], dataset.upper_bounds[i]);
        sum += proportions[i];
    }

    float diff = dataset.total_proportion - sum;
    // if (diff == 0) return proportions;


    if (diff > 0.001f)
    {
        // sum needs to be maxmized
        int i = 0 ;
        while(diff > 0.001f){

            float distToUpperBound = dataset.upper_bounds[i] - proportions[i];
            float increaseValue = generateRandomFloat(0, distToUpperBound);
            increaseValue = std::min(increaseValue, diff);


            proportions[i] += increaseValue;
            diff -= increaseValue;


            i  =(i + 1) % n;
        }

    }else if (diff < 0.001f)
    {
        // sum needs to be minimized
        int i = 0 ;
        while(diff < -0.001f){
            float distToLowerBound = proportions[i] - dataset.lower_bounds[i];
            float decreaseValue = generateRandomFloat(0, distToLowerBound);
            decreaseValue = std::min(decreaseValue, -diff);


            proportions[i] -= decreaseValue;
            diff += decreaseValue;


            i  =(i + 1) % n;
        }
    }
    for(auto& prop : proportions)
        _round(prop);


    return proportions;
}
