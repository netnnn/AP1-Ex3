#ifndef KNN_H
#define KNN_H

#include <list>
#include <map>
#include <vector>
#include "Distance.h"
#include <string>

using namespace std;

class KNN {
public:
    static list<vector<double>> knnList(vector<double> vector1, Distance* distance, map<vector<double>, string> vecMap, int k);
    static string findVectorType(list<vector<double>> KDistanceList, map<vector<double>, string> vecMap);
};

#endif
