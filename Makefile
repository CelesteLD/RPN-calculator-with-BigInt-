CC=g++
CCXFLAGS=-g -std=c++14 -Wall

OBJS= src/main.o

all: ${OBJS}
	$(CC) $(CXXFLAGS) -o p1 ${OBJS}

.PHONY: clean

run: all
	./p1
	
clean: 
	rm -rf src/*.o p1 output.txt