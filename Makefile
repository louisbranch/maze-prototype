CFLAGS=-Wall -g
all:
	g++ linux_maze.cpp -o maze
clean:
	rm -f maze
