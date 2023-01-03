#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
using namespace std;

/**
 * @brief the main method of the client
 * 
 * @param argv number of command line arguments
 * @param args the command line arguments
 * @return int 0 if the program ran successfully
 */
int main(int argv, char* args[]) {
    //if more or less than 3 command line arguments, its invalid.
    if(argv != 3) {
        cout << "invalid input" << endl;
        exit(0);
    }
    //Initializing ip address and port no.
    char* ip_address = nullptr;
    int port_no = 0;
    //getting the ip and port no. of the server.
    try{
        ip_address = args[1];
        port_no = stoi(args[2]);
    } catch (exception exception) {
        cout << "invalid input" << endl;
        exit(0);
    }
    //Making them const
    const char* c_ip_address = ip_address;
    const int c_port_no = port_no;
    //Creating a tcp socket for the client
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        cout << "error creating socket" << endl;
        exit(0);
    }
    //Connecting the client to the server socket
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(c_ip_address);
    sin.sin_port = htons(c_port_no);
    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        cout << "error connecting to server" << endl;
        close(sock);
        exit(0);
    }

    //Reading a new line from the user
    string newLine;
    char recv_buffer[4096];
    /* Endless loop which reads a line from the user, until a -1 is given. it sends each line to the server
    and prints the type it returned based on the k closest neighbors if successful. else, it prints the 
    input was invalid. */
    while (true) {
        //Get a new line, if its -1, close the socket.
        getline(cin, newLine);
        if (newLine == "-1") {
            break;
        }
        //Send the message to the server
        const char* data_addr = newLine.c_str();
        int data_len = strlen(data_addr);
        int sent_bytes = send(sock, data_addr, data_len, 0);
        if (sent_bytes < 0) {
            cout << "error sending message" << endl;
            close(sock);
            exit(0);
        }
        //Receive the type from the server
        int expected_data_len = sizeof(recv_buffer);
        memset(recv_buffer, '\0', sizeof(recv_buffer));
        int read_bytes = recv(sock, recv_buffer, expected_data_len, 0);
        if (read_bytes == 0) {
            cout << "connection is closed" << endl;
            close(sock);
            continue;
        }
        if (read_bytes < 0) {
            cout << "error reading message" << endl;
            close(sock);
            exit(0);
        }
        //Print the type. If the server sent "invalid input" it prints it.
        string maxType(recv_buffer);
        cout << maxType << endl;
    
    }
    //Close the client socket.
    close(sock);
    return 0;
}