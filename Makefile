CC = g++
CFLAGS = -O3 -std=c++11

build: main.cpp unionfind.hpp percolation.hpp
	$(CC) -o run main.cpp $(CFLAGS)

clean:
	rm run