FLAGS=-Wall -g
CC=g++
all:
	$(CC) ${FLAGS} linux_maze.cpp -o maze -lncurses
clean:
	rm -f maze
