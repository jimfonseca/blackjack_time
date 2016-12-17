
CC=g++
CFLAGS=-c -Wall -O2

all: bj


bj: bj.o

bj.o: bj.cpp
	$(CC) $(CFLAGS) bj.cpp

