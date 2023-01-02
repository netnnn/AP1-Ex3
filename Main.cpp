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
#include <stdio.h>
#include <list>
#include <map>
#include <cstring>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
#include <unistd.h>
#include <winsock.h>
#include "winsock2.h"

using namespace std;

void createServer(int port) {
    const int server_port = port;
    int sock = socket(AF_INET, SOCK_STREAM,0);
    if (sock < 0) {
        perror("error creating socket");
    }

    struct sockaddr_in sin;
    memset(&sin,0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);
    if (bind(sock,(struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
    }
    if (listen(sock,1) < 0) {
        perror("error listening to a socket");
    }
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(sock, (struct sockaddr *) &client_sin,reinterpret_cast<int *>(&addr_len));
    if (client_sock < 0) {
        perror("error accepting client");
    }
    char buffer[4096];
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(client_sock, buffer, expected_data_len,0);
    if (read_bytes == 0) {
// connection is closed
    }
    else if (read_bytes < 0) {
// error
    } else{
        cout << buffer;
    }
    int sent_bytes = send(client_sock, buffer, read_bytes,0);
    if (sent_bytes < 0){
        perror("error sending to client");
    }
    close(sock);

}

string calculateKNN(string filePath, char buffer[]) {
    const char *dis;
    Distance *x;
    ManhattanDistance man = ManhattanDistance();
    EuclidianDistance auc = EuclidianDistance();
    CanberraDistance can = CanberraDistance();
    ChebyshevDistance che = ChebyshevDistance();
    MinkowskiDistance min = MinkowskiDistance();

    vector<string> allStr;
    char* ptr;
    ptr = strtok(buffer, " ");
    while (ptr != NULL) {
        allStr.emplace_back(ptr);
        ptr = strtok (NULL, " ");
    }
    string temp;
    temp = allStr.back();
    int k = stoi(temp);
    allStr.pop_back();
    temp = allStr.back();
    dis = temp.c_str();
    allStr.pop_back();


    if (strcmp("MAN", dis) == 0)
        x = &man;
    else if (strcmp("AUC", dis) == 0)
        x = &auc;
    else if (strcmp("CAN", dis) == 0)
        x = &can;
    else if (strcmp("CHB", dis) == 0)
        x = &che;
    else if (strcmp("MIN", dis) == 0)
        x = &min;
        //If no such distance, its invalid.
    else {
        cout << "ERROR! Invalid distance type" << endl;
        exit(0);
    }

    //Loop that runs infinitely: Get a vector and print the type that appeared the most out of the k closest neighbors.

    vector<string> vecStr = allStr;
    vector<double> vec;
    string line;
    int i = 0;
    //Convert it to a vector of doubles. If failed, continue to read another line.
    try {
        for (i = 0; i < vecStr.size(); i++) {
            double d = stod(vecStr[i]);
            vec.push_back(d);
        }
    } catch (exception e) {
        return "ERROR! illegal vector";
    }

    //Get a map of the vectors to their type
    map<vector<double>, string> vecMap;
    vecMap = IfstreamToMap::ifstreamToMap(filePath, vec.size());
    //If there are no valid vectors to compare distance with, continue to read another line.
    if (vecMap.size() == 0) {
        return "ERROR! no valid vectors to calculate distance with";
    }
    //If the number of neighbors to find is larger than the size of the map, calculate by the entire map.
    if (vecMap.size() < k) {
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

    return maxType;

}

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
    string maxType;
    string filePath;
    int port;
    //If number of arguments is different from 3 its invalid.
    if(argv != 3) {
        cout << "ERROR! Illegal arguments" << endl;
        exit(0);
    }
    //Get the arguments into variables.
    try {
        filePath = args[1];
        port = stoi(args[2]);
    } catch (exception exception) {
        cout << "invalid arguments" << endl;
        exit(0);
    }
    ///createServer(port);

    const int server_port = port;
    int sock = socket(AF_INET, SOCK_STREAM,0);
    if (sock < 0) {
        perror("error creating socket");
    }

    struct sockaddr_in sin;
    memset(&sin,0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);
    if (bind(sock,(struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
    }
    if (listen(sock,1) < 0) {
        perror("error listening to a socket");
    }
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(sock, (struct sockaddr *) &client_sin,reinterpret_cast<int *>(&addr_len));
    if (client_sock < 0) {
        perror("error accepting client");
    }
    char buffer[4096];
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(client_sock, buffer, expected_data_len,0);
    if (read_bytes == 0) {
// connection is closed
    }
    else if (read_bytes < 0) {
// error
    } else{
        maxType = calculateKNN(filePath, buffer);
        cout << maxType;
    }
    int sent_bytes = send(client_sock, maxType.c_str(), read_bytes,0);
    if (sent_bytes < 0){
        perror("error sending to client");
    }
    close(sock);



    return 0;
}