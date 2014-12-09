#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "maze.h"

#define internal static

internal void PlatformReadMapFromFile(const char* fileName, map* maze);
internal void PlatformRenderMap(map* maze);

int main() {
  map maze1;
  maze1.rows = 6;
  maze1.cols = 45;
  PlatformReadMapFromFile("map1.txt", &maze1);
  PlatformRenderMap(&maze1);

  map maze2;
  maze2.rows = 5;
  maze2.cols = 5;
  PlatformReadMapFromFile("map2.txt", &maze2);
  PlatformRenderMap(&maze2);

  return 0;
}

internal void PlatformReadMapFromFile(const char* fileName, map* maze) {
  FILE* fp;
  int i = 0;
  int size = maze->rows * maze->cols;
  char c;
  maze->tiles = (uint8_t*)malloc(size * sizeof(uint8_t));
  fp = fopen(fileName, "r");
  if (fp != 0) {
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
  } else {
    //TODO log error
  }
}

internal void PlatformRenderMap(map* maze) {
  int i;
  for (i = 0; i < (int)(maze->rows * maze->cols); i++) {
    if (i > 0 && i % maze->cols == 0) {
      printf("\n");
    }
    printf("%c", maze->tiles[i]);
  }
  printf("\n");
}
