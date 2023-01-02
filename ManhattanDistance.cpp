#include <vector>
#include <cmath>
#include "ManhattanDistance.h"
using namespace std;

/**
* @brief Get the Euclidian Distance of two vectors of the same size
* 
* @param vec1 vector 1
* @param vec2 vector 2
* @param vectorSizes the size of the 2 vectors
* @return double the Euclidian distance between the two vectors.
*/
double ManhattanDistance::getDistance(vector<double> vec1, vector<double> vec2, int vectorSizes) {

    //initializing the distance as 0
    double distance = 0;

    //calculating by the euclidian distance formula.
    for (int i = 0; i < vectorSizes; i++) {
        distance += abs(vec1[i] - vec2[i]);
    }
    return distance;
}