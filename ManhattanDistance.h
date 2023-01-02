#ifndef MANHATTANDISTANCE_H
#define MANHATTANDISTANCE_H

#include <vector>
#include "Distance.h"
using namespace std;

class ManhattanDistance : public Distance{
    public:
    double getDistance(vector<double> vec1, vector<double> vec2, int vectorSizes);
};
#endif