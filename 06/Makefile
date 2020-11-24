CC=g++
FLAGS=-std=c++17 -Wall -pedantic

all: clean format.o test.o

format.o: 
	$(CC) $(FLAGS) format.cpp -c

test.o: format.o
	$(CC) $(FLAGS) test.cpp -c
	$(CC) $(FLAGS) format.o test.o -o test

test: clean test.o
	./test

clean:
	rm -f *.o
	rm -f test