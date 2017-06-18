TARGET = Lab_5_checker
CC=g++
FLAGS = -std=c++11 -Wall -pedantic

OBJ = main.o SuffixTree.o

.PHONY: all clean

all: $(TARGET)

clean:
	rm -rf $(TARGET) *.o

SuffixTree.o: SuffixTree.cpp SuffixTree.h
	$(CC) $(FLAGS) -c $< -o $@
main.o: main.cpp SuffixTree.h
	$(CC) $(FLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $@
