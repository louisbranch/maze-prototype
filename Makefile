FLAGS=-Wall -g
CC=g++
all:
	$(CC) ${FLAGS} unix_maze.cpp -o bin/maze -lncurses
clean:
	rm -f bin/maze
