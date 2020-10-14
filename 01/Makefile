CC=g++
FLAGS=-std=c++17 -Wall -pedantic

all: test

allocator.o: 
	$(CC) $(FLAGS) allocator.cpp -c

tests.o: allocator.o
	$(CC) $(FLAGS) tests.cpp -c
	$(CC) $(FLAGS) allocator.o tests.o -o test

test: tests.o
	./test

clean:
	rm -f *.o
	rm -f test