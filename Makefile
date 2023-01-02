a.out: Main.o CanberraDistance.o ChebyshevDistance.o Distance.o EuclidianDistance.o IfstreamToMap.o KNN.o ManhattanDistance.o MinkowskiDistance.o StrToVector.o
	g++ -std=c++11 Main.o CanberraDistance.o ChebyshevDistance.o Distance.o EuclidianDistance.o IfstreamToMap.o KNN.o ManhattanDistance.o MinkowskiDistance.o StrToVector.o -o a.out

Main.o: Main.cpp
	g++ -std=c++11 -c Main.cpp
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