FLAGS=-Wall -g
CC=g++
all:
	$(CC) ${FLAGS} linux_maze.cpp -o maze
clean:
	rm -f maze
