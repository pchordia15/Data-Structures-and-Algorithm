CXX = g++
#CXXFLAGS = -g -std=c++11
CXXFLAGS = -g -std=c++11 -Wall -W -Werror -pedantic

sspapp: graph.o MinPriority.o sspapp.o
	$(CXX) -o sspapp sspapp.o graph.o MinPriority.o

sspapp.o: sspapp.cpp graph.h 

graph.o: graph.cpp graph.h MinPriority.h

MinPriority.o: MinPriority.cpp MinPriority.h

clean:
	rm -f *.o sspapp
