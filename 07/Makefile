CC=g++
FLAGS=-std=c++17 -Wall -pedantic

all: clean allocator.o iterator.o vector.o tests.o

allocator.o: 
	$(CC) $(FLAGS) allocator.cpp -c

iterator.o: 
	$(CC) $(FLAGS) iterator.cpp -c

vector.o: 
	$(CC) $(FLAGS) vector.cpp -c

tests.o: allocator.o iterator.o vector.o
	$(CC) $(FLAGS) tests.cpp -c
	$(CC) $(FLAGS) allocator.o iterator.o vector.o tests.o -o test

test: clean tests.o
	./test

valgrind: clean tests.o
	valgrind ./test

clean:
	rm -f *.o
	rm -f test