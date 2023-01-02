#include <vector>
#include <cmath>
#include "EuclidianDistance.h"
using namespace std;

/**
* @brief Get the Euclidian Distance of two vectors of the same size
* 
* @param vec1 vector 1
* @param vec2 vector 2
* @param vectorSizes the size of the 2 vectors
* @return double the Euclidian distance between the two vectors.
*/
double EuclidianDistance::getDistance(vector<double> vec1, vector<double> vec2, int vectorSizes) {
    //initializing the distance as 0
    double distance = 0;

    //calculating by the minkowski distance formula.
    for (int i = 0; i < vectorSizes; i++)
        distance += pow(abs(vec1[i] - vec2[i]), 2);
    return pow(distance, 0.5);
}