#ifndef IFSTREAMTOMAP_H
#define IFSTREAMTOMAP_H

#include <map>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class IfstreamToMap{
    public:
    static map<vector<double>, string> ifstreamToMap(string filePath, int vectorSize);
};

#endif