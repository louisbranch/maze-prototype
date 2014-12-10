FLAGS=-Wall -g
CC=g++
all:
	$(CC) ${FLAGS} unix_maze.cpp -o maze -lncurses
clean:
	rm -f maze
