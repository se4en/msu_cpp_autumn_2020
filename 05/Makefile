CC=g++
FLAGS=-std=c++17 -Wall -pedantic

all: clean test.o

test.o: 
	$(CC) $(FLAGS) test.cpp -o test

test: clean test.o
	./test

valgrind: clean test.o
	valgrind ./test

clean:
	rm -f *.o
	rm -f test
