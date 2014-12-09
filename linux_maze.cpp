#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ncurses.h>

#include "maze.h"

#define internal static

internal void PlatformReadMapFromFile(const char* fileName, map* maze);
internal void PlatformRenderMap(map* maze);

int main() {
  map maze1;
  maze1.rows = 6;
  maze1.cols = 45;
  PlatformReadMapFromFile("map1.txt", &maze1);

  char ch;

  initscr(); // starts ncurse mode
  cbreak();  // disable line buffering
  noecho();  // disable echo on getch

  do {
    ch = getch();
    clear();   // clear console
    PlatformRenderMap(&maze1);
    refresh();
  } while (ch != 'q');

  endwin();

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
      printw("\n");
    }
    printw("%c", maze->tiles[i]);
  }
  printw("\n");
}
