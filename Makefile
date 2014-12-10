FLAGS=-Wall -g
CC=g++
all:
	$(CC) ${FLAGS} maze.cpp -o bin/maze -lncurses
clean:
	rm -f bin/maze
