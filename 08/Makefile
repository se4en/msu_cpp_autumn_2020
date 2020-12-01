CC=g++
FLAGS=-std=c++17 -Wall -pedantic -pthread

all: clean test.o

test.o: 
	$(CC) $(FLAGS) test.cpp -o test

test: clean test.o
	./test

clean:
	rm -f *.o
	rm -f test