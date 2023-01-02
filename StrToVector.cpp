#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include "StrToVector.h"
using namespace std;

/**
 * @brief get a string and a delim and turn it into a vector of strings seperated by the delim.
 * 
 * @param str the string
 * @param delim the delim
 * @return vector<string> vector of strings.
 */
vector<string> StrToVector::strToVector(string str, char delim){
    //Initializing a vector of doubles.
    vector<string> vec;

    //Initializing a string and reading a line from the users input into it and constructing a stream from the string.
    stringstream lineStream(str);

    /* Splitting the line according to the delim character and storing each part in a string called word,
    then pushing it into the vector. */
    string word;
    while(getline(lineStream, word, delim)){
        vec.push_back(word);
    }

    //Returning the vector built from the line.
    return vec;
}