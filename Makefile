CC=g++
CFLAGS=-std=c++11
INCLUDE_REAL=-I include

all: main.cpp
	$(CC) $(CFLAGS) $(INCLUDE_REAL) main.cpp -o test


clean:
	rm -rf bin/* build/* *.o *~
