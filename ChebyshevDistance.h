#ifndef CHEBYSHEVDISTANCE_H
#define CHEBYSHEVDISTANCE_H

#include <vector>
#include "Distance.h"
using namespace std;

class ChebyshevDistance : public Distance{
    public:
    double getDistance(vector<double> vec1, vector<double> vec2, int vectorSizes);
};

#endif