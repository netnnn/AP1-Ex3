sever.out: Server.o client.out CanberraDistance.o ChebyshevDistance.o Distance.o EuclidianDistance.o IfstreamToMap.o KNN.o ManhattanDistance.o MinkowskiDistance.o StrToVector.o
	g++ -std=c++11 Server.o CanberraDistance.o ChebyshevDistance.o Distance.o EuclidianDistance.o IfstreamToMap.o KNN.o ManhattanDistance.o MinkowskiDistance.o StrToVector.o -o server.out

client.out: Client.o CanberraDistance.o ChebyshevDistance.o Distance.o EuclidianDistance.o IfstreamToMap.o KNN.o ManhattanDistance.o MinkowskiDistance.o StrToVector.o
	g++ -std=c++11 Client.o CanberraDistance.o ChebyshevDistance.o Distance.o EuclidianDistance.o IfstreamToMap.o KNN.o ManhattanDistance.o MinkowskiDistance.o StrToVector.o -o client.out


Client.o: Client.cpp
	g++ -std=c++11 -c Client.cpp
Server.o: Server.cpp
	g++ -std=c++11 -c Server.cpp
CanberraDistance.o: CanberraDistance.cpp CanberraDistance.h
	g++ -std=c++11 -c CanberraDistance.cpp
ChebyshevDistance.o: ChebyshevDistance.cpp ChebyshevDistance.h
	g++ -std=c++11 -c ChebyshevDistance.cpp
Distance.o: Distance.cpp Distance.h
	g++ -std=c++11 -c Distance.cpp
EuclidianDistance.o: EuclidianDistance.cpp EuclidianDistance.h
	g++ -std=c++11 -c EuclidianDistance.cpp
IfstreamToMap.o: IfstreamToMap.cpp IfstreamToMap.h
	g++ -std=c++11 -c IfstreamToMap.cpp
KNN.o: KNN.cpp KNN.h
	g++ -std=c++11 -c KNN.cpp
ManhattanDistance.o: ManhattanDistance.cpp ManhattanDistance.h
	g++ -std=c++11 -c ManhattanDistance.cpp
MinkowskiDistance.o: MinkowskiDistance.cpp MinkowskiDistance.h
	g++ -std=c++11 -c MinkowskiDistance.cpp
StrToVector.o: StrToVector.cpp StrToVector.h
	g++ -std=c++11 -c StrToVector.cpp