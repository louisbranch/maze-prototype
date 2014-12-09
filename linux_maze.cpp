#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "maze.h"

#define internal static

internal void PlatformReadMapFromFile(const char* fileName, map* maze);
internal void PlatformRenderMap(map* maze);

int main() {
  map maze;
  maze.rows = 6;
  maze.cols = 45;
  PlatformReadMapFromFile("map1.txt", &maze);
  PlatformRenderMap(&maze);
  return 0;
}

internal void PlatformReadMapFromFile(const char* fileName, map* maze) {
  FILE* fp;
  int i;
  int size = maze->rows * maze->cols;
  maze->tiles = (uint8_t*)calloc(size, sizeof(uint8_t));
  char c;
  fp = fopen(fileName, "r");
  for(;;) {
    c = fgetc(fp);
    if(i >= size || feof(fp)) {
      break;
    }
    if (c != '\n') {
      maze->tiles[i] = c;
      ++i;
    }
  }
  fclose(fp);
}

internal void PlatformRenderMap(map* maze) {
  int i;
  for (i = 0; i < maze->rows*maze->cols; i++) {
    if (i > 0 && i % maze->cols == 0) {
      printf("\n");
    }
    printf("%c", maze->tiles[i]);
  }
  printf("\n");
}
