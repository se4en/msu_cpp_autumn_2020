CC=g++
FLAGS=-std=c++17 -Wall -pedantic

all: clean matrix.o test.o

matrix.o: 
	$(CC) $(FLAGS) matrix.cpp -c

test.o: matrix.o
	$(CC) $(FLAGS) test.cpp -c
	$(CC) $(FLAGS) matrix.o test.o -o test

test: clean test.o
	./test

clean:
	rm -f *.o
	rm -f test