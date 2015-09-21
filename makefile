
CC=g++

CFLAGS = -c -g -Wall -O4 -std=c++11 

all: prog

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

prog: main.o
	$(CC) -o prog main.o 
