#include <vector>
#include <cmath>
#include "MinkowskiDistance.h"
using namespace std;

/**
* @brief Get the Minkowski Distance of two vectors of the same size and a given constant P.
* 
* @param vec1 vector 1
* @param vec2 vector 2
* @param vectorSizes the size of the 2 vectors
* @param p a constant for the Minkowski formula
* @return double the Minkowski distance with constant P between the two vectors.
*/
double MinkowskiDistance::getDistance(vector<double> vec1, vector<double> vec2, int vectorSizes) {

    //initializing the distance as 0
    double distance = 0;

    //calculating by the minkowski distance formula.
    for (int i = 0; i < vectorSizes; i++) {
        distance += pow(abs(vec1[i] - vec2[i]), P);
    }
    if (P >= 1) return pow(distance, (double) 1/P);
    else return distance;
}