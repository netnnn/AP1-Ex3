#ifndef MINKOWSKIDISTANCE_H
#define MINKOWSKIDISTANCE_H

#include <vector>
#include "Distance.h"
#define P 3 //CONSTANT P FOR MINKOWSKI
using namespace std;

class MinkowskiDistance : public Distance{
    public:
    double getDistance(vector<double> vec1, vector<double> vec2, int vectorSizes);
};

#endif
