#include <vector>
#include <cmath>
#include "ChebyshevDistance.h"
using namespace std;

/**
* @brief Get the Chebyshev Distance of two vectors of the same size

* @param vec1 the first vector
* @param vec2 the second vector
* @param vectorSizes the size of the two vectors
* @return the distance.
*/
double ChebyshevDistance::getDistance(vector<double> vec1, vector<double> vec2, int vectorSizes){
    //initializing the distance as the first distance between the vectors.
    double distance = abs(vec1[0] - vec2[0]);
    for (int i = 1; i < vectorSizes; i++) {
        if (distance < abs(vec1[i] - vec2[i]))
            distance = abs(vec1[i] - vec2[i]);
    }
    return distance;
}