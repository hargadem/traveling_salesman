all: main

clean:
	rm main.o tsp.o

main: main.o tsp.o
	g++ -g -o main main.o tsp.o

main.o: main.cpp tsp.hpp
	g++ -g -c main.cpp

tsp.o: tsp.cpp tsp.hpp
	g++ -g -c tsp.cpp
