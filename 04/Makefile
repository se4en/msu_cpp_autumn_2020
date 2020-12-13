CC=g++
FLAGS=-std=c++17 -Wall -pedantic

all: clean bigint.o test.o

bigint.o: 
	$(CC) $(FLAGS) bigint.cpp -c

test.o: bigint.o
	$(CC) $(FLAGS) test.cpp -c
	$(CC) $(FLAGS) bigint.o test.o -o test

test: clean test.o
	./test

valgrind: clean test.o
	valgrind ./test

clean:
	rm -f *.o
	rm -f test
