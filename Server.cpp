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
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

/**
 * @brief A method which 
 * 
 * @param filePath path to the file of datasets
 * @param recv_buffer the buffer which contains the input of the client
 * @return string the type of the vector by its k closest neighbors.
 */
string calculateKNN(string filePath, char recv_buffer[]) {
    //Create instances of the different distances
    const char *dis;
    Distance *x;
    ManhattanDistance man = ManhattanDistance();
    EuclidianDistance auc = EuclidianDistance();
    CanberraDistance can = CanberraDistance();
    ChebyshevDistance che = ChebyshevDistance();
    MinkowskiDistance min = MinkowskiDistance();

    //splitting the line from the client into the vector, distance, and number k of neighbors.
    vector<string> allStr;
    char* ptr;
    //Converting the line seperated by spaces to a vector.
    ptr = strtok(recv_buffer, " ");
    while (ptr != NULL) {
        allStr.emplace_back(ptr);
        ptr = strtok (NULL, " ");
    }
    //The last string in the vector is the k.
    string temp;
    temp = allStr.back();
    int k;
    try {
        k = stoi(temp);
    }
    catch (exception e) {
        throw e;
    }
    if (k <= 0) {
        throw new exception;
    }
    //Then, the last string in the vector is the distance.
    allStr.pop_back();
    temp = allStr.back();
    dis = temp.c_str();
    allStr.pop_back();
    //Then allStr is left with just the vector.

    //Choosing the correct distance
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
        throw new exception();
    }

    vector<string> vecStr = allStr;
    vector<double> vec;
    string line;
    int i = 0;
    //Convert it to a vector of doubles. If failed, its an error.
    try {
        for (i = 0; i < vecStr.size(); i++) {
            double d = stod(vecStr[i]);
            vec.push_back(d);
        }
    } catch (exception e) {
        throw e;
    }

    //Get a map of the vectors to their type
    map<vector<double>, string> vecMap;
    vecMap = IfstreamToMap::ifstreamToMap(filePath, vec.size());
    //If there are no valid vectors to compare distance with, its an error.
    if (vecMap.size() == 0) {
        throw new exception;
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
 * @brief The main method that gets a file path of the datasets and a port to open the socket on.
 * It then recieves a line from the client which consists of a vector, distance and number k,
 * calculates its type based on the k closest neighbors. It then sends the type back to the client.
 * If the input was invalid, it sends "invalid input" to the client.
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
    if (argv != 3) {
        cout << "invalid input" << endl;
        exit(0);
    }
    //Get the arguments into variables.
    try {
        filePath = args[1];
        port = stoi(args[2]);
    } catch (...) {
        cout << "invalid input" << endl;
        exit(0);
    }

    if (port <= 1024 || port >= 65536) {
        cout << "invalid port value" << endl;
        exit(0);
    }
    //Creating a server socket
    const int server_port = port;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        cout << "error creating socket" << endl;
        exit(0);
    }
    //Binding the socket
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        cout << "error binding socket" << endl;
        close(sock);
        exit(0);
    }
    //Make the socket listen
    if (listen(sock, 5) < 0) {
        cout << "error listen for sockets" << endl;
        close(sock);
        exit(0);
    }
    //Variables for working with a specific client socket
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    char recv_buffer[4096];
    int expected_data_len = sizeof(recv_buffer);
    /* Endless loop which accepts a client and recieves messages from it. splits the message to a vector,
    distance and number k and returns its type based on the k closest vectors. */
    while(true) {
        //Accept a new client
        int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
        if (client_sock < 0) {
            cout << "error accepting client" << endl;
            exit(0);
        }

        //Read a line from the client, and calculate the k closest neighbors and return its type or an error.
        while(true){
            //Receive a message from the client
            memset(recv_buffer, '\0', sizeof(recv_buffer));
            int read_bytes = recv(client_sock, recv_buffer, expected_data_len, 0);
            //If 0 bytes were sent, the client closed the connection.
            if (read_bytes == 0) {
                close(client_sock);
                break;
            }
            if (read_bytes < 0) {
                cout << "error reading message" << endl;
                close(client_sock);
                exit(0);
            }
            //Find the type based on the k closest neighbors, if theres an exception it means the input was invalid.
            try{
                maxType = calculateKNN(filePath, recv_buffer);
            } catch (...) {
                string errormsg = "invalid input";
                int sent_bytes = send(client_sock, errormsg.c_str(), errormsg.length(), 0);
                if (sent_bytes < 0) {
                    cout << "error sending to client" << endl;
                    close(client_sock);
                    exit(0);
                }
                continue;
            }
            //If it was valid, send the type to the client.
            int sent_bytes = send(client_sock, maxType.c_str(), maxType.length(), 0);
            if (sent_bytes < 0) {
                cout << "error sending to client" << endl;
                close(client_sock);
                exit(0);
            }
        }

        //Close the current client socket
        close(client_sock);
    }

    //Close the server socket
    close(sock);
    return 0;
}