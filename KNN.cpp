#include "KNN.h"
#include <vector>
#include <iostream>
#include "Distance.h"
#include <list>
#include <map>
#include <string>
using namespace std;

/**
 * @brief A comparator class to compare vectors based on their distance from a vector.
 * Both the vector and the distance function are given.
 */
class vectorCmp {
public:
    vector<double> vec;
    Distance* distance;
    vectorCmp(vector<double> vector1, Distance* distance1){
        distance = distance1;
        vec = vector1;
    }
    bool operator()(const vector<double>& vec1,const vector<double>& vec2) {
        if (distance->getDistance(vec, vec1, vec.size())
            < distance->getDistance(vec, vec2, vec.size())) {
            return true;
        }
        return false;
    }
};

/**
 * @brief A method to return a list of the k closest neighbors to a given vector using a given distance method.
 * 
 * @param vector1 the vector to calculate distance from
 * @param distance the distance method
 * @param vecMap map of vectors to type
 * @param k number of neighbors to returns
 * @return list<vector<double>> list of k closesnt neighbors to the given vectors using the given distance method.
 */
list<vector<double>> KNN::knnList(vector<double> vector1, Distance* distance, map<vector<double>, string> vecMap, int k) {
    vectorCmp vc(vector1, distance);
    list<vector<double>> vecList;
    //Push all the vectors from the map into the list
    for (auto v : vecMap) {
        vecList.push_back(v.first);
    }
    //Sort the list
    vecList.sort(vc);
    list<vector<double>> KList;
    list<vector<double>>::iterator it;
    int i = 0;
    //Return the K closest neighbors.
    for (i = 0; i < k; i++) {
        it = vecList.begin();
        KList.splice(KList.end(), vecList, it);
    }
    return KList;
}

/**
 * @brief A method to return the type that appeared the most out of the k closest neighbors.
 * 
 * @param KDistanceList A list of the K closesnt neighbors
 * @param vecMap A map of the vectors to their type.
 * @return string the type that appeared the most out of the k closest neighbors.
 */
string KNN::findVectorType(list<vector<double>> KDistanceList, map<vector<double>, string> vecMap){
    //A map of how many times each type appeared.
    map<string, int> vecType;
    map<string, int>::iterator typeIter;

    //Initialize all the values in the map to 0.
    for (vector<double> v : KDistanceList) {
        vecType[vecMap[v]] = 0;
    }

    //Update the number of times the type appeared for each vector in the list.
    for (vector<double> v : KDistanceList) {
        vecType[vecMap[v]] += 1;
    }

    //Find the maximum of and return it.
    string maxType = vecType.begin()->first;
    for (typeIter = vecType.begin(); typeIter != vecType.end() ; typeIter++) {
        if (vecType[maxType] < typeIter->second){
            maxType = typeIter->first;
        }
    }
    return maxType;
}