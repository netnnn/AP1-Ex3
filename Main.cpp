#include "CanberraDistance.h"
#include "ChebyshevDistance.h"
#include "MinkowskiDistance.h"
#include "EuclidianDistance.h"
#include "ManhattanDistance.h"
#include "StrToVector.h"
#include "IfstreamToMap.h"
#include "Distance.h"
#include "KNN.h"
#include <vector>
#include <iostream>
#include "string.h"
#include <map>
#include <list>

using namespace std;

/**
 * @brief The main method that gets a number of neighbors to find, a path to the file and the distance to calculate
 * by. It then recieves a vector and returns the type that appeared the most out of the k closest neighbors to it,
 * in an infinite loop.
 * 
 * @param argv number of command line arguments
 * @param args command line arguments
 * @return int 0 if ran successfully
 */
int main(int argv, char* args[]) {
    const char *dis;
    string filePath;
    int k = 0;
    //If number of arguments is different than 4 its invalid.
    if(argv != 4) {
        cout << "ERROR! Illegal arguments" << endl;
        exit(0);
    }
    //Get the arguments into variables.
    try {
        k = stoi(args[1]);
        filePath = args[2];
        dis = args[3];
    } catch (exception exception) {
        cout << "invalid arguments" << endl;
        exit(0);
    }

    //Choose which distance to cast into based on the user input
    Distance* x;
    ManhattanDistance man = ManhattanDistance();
    EuclidianDistance auc = EuclidianDistance();
    CanberraDistance can = CanberraDistance();
    ChebyshevDistance che = ChebyshevDistance();
    MinkowskiDistance min = MinkowskiDistance();

    if(strcmp("MAN", dis) == 0)
        x = &man;
    else if(strcmp("AUC", dis) == 0)
        x = &auc;
    else if(strcmp("CAN", dis) == 0)
        x = &can;
    else if(strcmp("CHB", dis) == 0)
        x = &che;
    else if(strcmp("MIN", dis) == 0)
        x = &min;
    //If no such distance, its invalid.
    else {
        cout << "ERROR! Invalid distance type" << endl;
        exit(0);
    }

    //Loop that runs infinitely: Get a vector and print the type that appeared the most out of the k closest neighbors.
    while (true) {
        vector<string> vecStr;
        vector<double> vec;
        string line;
        int i = 0;
        //Read a line from the user input
        getline(cin, line);
        //Convert it to a string of vectors
        vecStr = StrToVector::strToVector(line, ' ');
        //Convert it to a vector of doubles. If failed, continue to read another line.
        try {
            for (i = 0; i < vecStr.size(); i++) {
                double d = stod(vecStr[i]);
                vec.push_back(d);
            }
        } catch (exception e) {
            cout << "ERROR! illegal vector" << endl;
            continue;
        }

        //Get a map of the vectors to their type
        map<vector<double>, string> vecMap;
        vecMap = IfstreamToMap::ifstreamToMap(filePath, vec.size());
        //If there are no valid vectors to compare distance with, continue to read another line.
        if (vecMap.size() == 0){
            cout << "ERROR! no valid vectors to calculate distance with" << endl;
            continue;
        }
        //If the number of neighbors to find is larger than the size of the map, calculate by the entire map.
        if (vecMap.size() < k){
            k = vecMap.size();
        }

        //Get the list of the K closest neighbors
        list<vector<double>> KDistanceList;
        KDistanceList = KNN::knnList(vec, x, vecMap, k);

        // Print the k closest neighbors:
        // for (vector<double> v : KDistanceList) {
        //     for (auto x : v) {
        //         cout << x << " ";
        //     }
        //     cout << endl;
        // }

        //Get the type that appeared the most out of the k closest neighbors and print it.
        string maxType;
        maxType = KNN::findVectorType(KDistanceList, vecMap);

        cout << maxType << endl;
    }

    return 0;
}