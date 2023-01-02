<h1 align="center">AP1-EX2</h1>

<p align="center">The project contains a method that classifies a vector, given a chart of classified vectors. <br/>
The main method gets a number K which determines how many vectors to take for deciding what is the type of vector. <br/>
Also it gets a path to scan the classified vector chart from, and a distance method that we will use in our calculations. <br/>
Then the main method reads a line from the users input, converts it to a vector and returns its type based on the type of the k closest vectors to it, in an infinite loop. <br/>
So far, the distances taken into account are: Euclidean(AUC), Manhattan(MAN), Canberra(CAN), Chebyshev(CHB), and Minkowski(MIN).<br/>
The main uses methods StrToVector which reads gets a string and returns a string vector from that line. <br/>
And the method IfStreamToMap which gets a path to the .csv file and the size of our vector and returns a map of all the valid vectors to their type (valid means they have the same size as our vector so we can calculate their distance and are a valid vector of doubles). <br/>
Also The main uses the functions knnList which returns a list of the closest K vectors to a given vector by converting the Map from before into a list and sorting it, And the function findVectorType which returns the type that was the most common in the K closest vectors. <br/>
An ERROR! message will occur in the following cases and the program will terminate in the following cases: <br/> 
1. if the number of arguments is wrong. <br/>
2. if the distance type does not exist. <br/>
3. if the file does not exist. <br/>
4. if the vector is illegal (has a field that is not a double). <br/>
Also, if there are no valid vectors in the .csv file to compare distance with, an ERROR! message will pop but the program will continue to scan the next vector. <br/>
(Note: Minkowski uses a constant P for its calculation, we chose to calculate the distance with constant P=3). <br/>
The code is modular: each function is in its own cpp file. This help keep the code organised and efficient. </p>

## Links

- [Repo](https://github.com/netnnn/AP1-Ex2 "AP1-Ex2 Repo")

## How to run

In the project directory: <br/>
To compile: make <br/>
To execute: ./a.out k file distance  <br/>
To use: enter one line of numbers seperated by a single space (each line represents a vector). For example: <br/>
1 2 3 4 <br/>

## Authors

**Netanel Teller**

- [Profile](https://github.com/netnnn)
- [Email](netanel7227@gmail.com)

**Evyatar Assor**

- [Profile](https://github.com/Eviassor789)
- [Email](eviassor@gmail.com)

