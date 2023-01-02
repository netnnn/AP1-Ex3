#include <vector>
#include <cmath>
#include "CanberraDistance.h"
using namespace std;

/**
* @brief Get the Canberra Distance between two vectors.
* 
* @param vec1 vector 1
* @param vec2 vector 2
* @param vectorSizes the size of the two vectors
* @return double the canberra distance between the two vectors
*/
double CanberraDistance::getDistance(vector<double> vec1, vector<double> vec2, int vectorSizes){
    //initializing the distance as 0
    double distance = 0;
    //calculating by the manhattan distance formula.
    for (int i = 0; i < vectorSizes; i++) {
        if(vec1[i] != 0 || vec2[i] != 0)
            distance += abs(vec1[i] - vec2[i])/(abs(vec1[i]) + abs(vec2[i]));
    }
    //returning the distance
    return distance;
}