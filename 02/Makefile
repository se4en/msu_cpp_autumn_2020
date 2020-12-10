CC=g++
FLAGS=-std=c++17 -Wall -pedantic

all: clean parser.o test.o

parser.o: 
	$(CC) $(FLAGS) parser.cpp -c

test.o: parser.o
	$(CC) $(FLAGS) test.cpp -c
	$(CC) $(FLAGS) parser.o test.o -o test

test: clean test.o
	./test

clean:
	rm -f *.o
	rm -f test
