CC=g++
FLAGS=-std=c++17 -Wall -pedantic

all: clean allocator.o tests.o

allocator.o: 
	$(CC) $(FLAGS) allocator.cpp -c

tests.o: allocator.o
	$(CC) $(FLAGS) tests.cpp -c
	$(CC) $(FLAGS) allocator.o tests.o -o test

test: clean tests.o
	./test

valgrind: clean tests.o
	valgrind ./test

clean:
	rm -f *.o
	rm -f test