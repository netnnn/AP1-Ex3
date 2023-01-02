#ifndef DISTANCE_H
#define DISTANCE_H

#include <vector>
using namespace std;

class Distance{
    public:
    virtual double getDistance(vector<double> vec1, vector<double> vec2, int vectorSizes);
};

#endif