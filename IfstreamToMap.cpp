#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "IfstreamToMap.h"
#include "StrToVector.h"

using namespace std;

/**
 * @brief A method that gets a file path to a .csv file where each line is a vector of doubles with its type
 * as the last term of the vector. It reads each line and converts it to a string vector. Then, if the
 * vector without the last term is a valid vector of doubles and it is the size requested, it adds it to
 * a map where the vector of doubles is the key and its type is the value.
 * @param filePath path to the file
 * @param vectorSize size of the vectors in the map.
 * @return map<vector<double>, string> a map of valid vectors of doubles the size requested and their type.
 */
map<vector<double>, string> IfstreamToMap::ifstreamToMap(string filePath, int vectorSize){
    ifstream file;
    map<vector<double>, string> map;

    //Try to open the file at the given path.
    file.open(filePath);
    if(!file) {
        cout << "ERROR! File not found" << endl;
        exit(0);
    }

    //Read a line from the file, if its a valid vector of doubles the size requested add it to the map.
    string line;
    while(getline(file,line)){

        //Turn the line into a vector of strings.
        vector<string> vecStr = StrToVector::strToVector(line, ',');
        //If its not the size requested, continue to the next line.
        if (vecStr.size()-1 != vectorSize) continue;

        //Turn the vector of strings to a vector of doubles.
        vector<double> vecDbl;
        int i;
        for(i = 0; i < vecStr.size()-1; i++){
            try {
                double d = stod(vecStr[i]);
                vecDbl.push_back(d);
            }
            //If it cant be converted to a vector of doubles, break
            catch(exception e) {
                break;
            }
        }
        //If i isnt equal to the size of the vector minus one, it means it didnt finish the loop so its invalid.
        if (i != vecStr.size()-1) continue;

        //Else, insert the vector to the map.
        map.insert({vecDbl, vecStr[i]});
    }
    //Close the file and return the map.
    file.close();
    return map;
    
}
