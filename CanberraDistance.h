#ifndef CANBERRADISTANCE_H
#define CANBERRADISTANCE_H

#include <vector>
#include "Distance.h"
using namespace std;

class CanberraDistance : public Distance{
    public:
    double getDistance(vector<double> vec1, vector<double> vec2, int vectorSizes);
};

#endif