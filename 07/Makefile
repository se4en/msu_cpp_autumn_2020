CC=g++
FLAGS=-std=c++17 -Wall -pedantic

all: clean tests.o

tests.o: 
	$(CC) $(FLAGS) tests.cpp -o test

test: clean tests.o
	./test

valgrind: clean tests.o
	valgrind ./test

clean:
	rm -f *.o
	rm -f test