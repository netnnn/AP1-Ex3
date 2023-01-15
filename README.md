<h1 align="center">AP1-EX3</h1>

<p align="center">The project contains a method that classifies a vector, given a chart of classified vectors. <br/>
At start, the server will execute as the following: "./server.out file port", file will be the file of vectors with their type, <br/>
and the port will be the port that the server listens from. <br/>
Similarly, the client will execute as the following: "./client.out ip port", ip is the ip of the serve and the port is the port that the server listens from. <br/>
The Client main method gets a number K which determines how many vectors to take for deciding what is the type of vector. <br/>
and a distance method that we will use in our calculations as well as the vector. while the Server main gets a path to scan the classified vector chart from, <br/>
Then the Client main method reads a line from the users input,which will be as the following "vector distance k" the main converts it to a vector and sends it and the K to the server.<br/> 
the server returns its type based on the type of the K-closest vectors to it, in an infinite loop. <br/>
So far, the distances taken into account are: Euclidean(AUC), Manhattan(MAN), Canberra(CAN), Chebyshev(CHB), and Minkowski(MIN).<br/>
The Server main uses methods StrToVector which reads gets a string and returns a string vector from that line. <br/>
And the method IfStreamToMap which gets a path to the .csv file and the size of our vector and returns a map of all the valid vectors to their type (valid means they have the same size as our vector so we can calculate their distance and are a valid vector of doubles). <br/>
Also The Server main uses the functions knnList which returns a list of the closest K vectors to a given vector by converting the Map from before into a list and sorting it, And the function findVectorType which returns the type that was the most common in the K closest vectors. <br/>
An ERROR! message will occur in the following cases and the program will terminate in the following cases: <br/> 
1. if there was a problem while binding. <br/>
2. if there was a problem connecting to the server. <br/>
3. if the number of arguments is wrong. <br/>
4. if the distance type does not exist. <br/>
5. if the file does not exist. <br/>
6. if sending or recieveing a message failed. <br/>
Whenever an illegal line is entered into the client, it will print an "invalid input" message and continue to scan the next line. <br/>
When -1 is recieved into the client, it closes the connection and the client program. The server always keeps running.<br/>
(Note: Minkowski uses a constant P for its calculation, we chose to calculate the distance with constant P=3). <br/>
The code is modular: each function is in its own cpp file. This help keep the code organised and efficient. </p>

## Links

- [Repo](https://github.com/netnnn/AP1-Ex3 "AP1-Ex3 Repo")

## How to run

In the project directory: <br/>
To compile: make <br/>
To execute: "./server.out file port" or "./client.out ip port" <br/>
To use Server: a file which is a path, and a port - a number between 1024 and 65536, For example: <br/>
./server.out /u/students/some-name/iris_classified.csv 5557 <br/>
To use Client: enter one line of numbers seperated by a single space (each line represents a vector), a distance method and a K num of K-closest vector For example: <br/>
1 2 3 4 AUC 10 <br/>

## Authors

**Netanel Teller**

- [Profile](https://github.com/netnnn)
- [Email](netanel7227@gmail.com)

**Evyatar Assor**

- [Profile](https://github.com/Eviassor789)
- [Email](eviassor@gmail.com)

