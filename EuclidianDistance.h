#ifndef EUCLIDIANDISTANCE_H
#define EUCLIDIANDISTANCE_H

#include <vector>
#include "Distance.h"
using namespace std;

class EuclidianDistance : public Distance{
    public:
    double getDistance(vector<double> vec1, vector<double> vec2, int vectorSizes);
};

#endif