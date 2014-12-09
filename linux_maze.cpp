#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "maze.h"

#define internal static

internal void PlatformReadMapFromFile(const char* fileName, map* maze);

int main() {
  map maze;
  maze.rows = 6;
  maze.cols = 15;
  PlatformReadMapFromFile("map1.txt", &maze);
  printf("%d\n", sizeof(maze.tiles));
  return 0;
}

internal void PlatformReadMapFromFile(const char* fileName, map* maze) {
  maze->tiles = (uint8_t*)calloc(maze->rows * maze->cols, sizeof(uint8_t));
}
