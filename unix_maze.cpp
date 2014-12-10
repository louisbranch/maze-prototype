#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ncurses.h>

#include "maze.h"
#include "maze.cpp"

#define internal static

internal void UnixReadMapFromFile(const char* fileName, map* maze);
internal void UnixRenderMap(map* maze);

int main() {
  map maze1;
  maze1.rows = 6;
  maze1.cols = 45;
  UnixReadMapFromFile("map1.txt", &maze1);

  char ch;

  initscr(); // starts ncurses mode
  cbreak();  // disable line buffering
  noecho();  // disable echo on getch

  while (true) {
    ch = getch();
    if (ch == 'q') {
      clear();
      printw("Are you sure? (y/n)");
      refresh();
      ch = getch();
      if (ch == 'y') {
        break;
      }
    }
    clear();   // clear console

    enum input btn;

    switch (ch) {
      case 'w':
        btn = INPUT_UP;
        break;
      case 's':
        btn = INPUT_DOWN;
        break;
      case 'd':
        btn = INPUT_RIGHT;
        break;
      case 'a':
        btn = INPUT_LEFT;
        break;
    }

    if (btn) {
      HandleInput(btn);
      UnixRenderMap(&maze1);
      refresh(); // refresh console
    }
  }

  endwin(); // end ncurses mode
  return 0;
}

internal void UnixReadMapFromFile(const char* fileName, map* maze) {
  FILE* fp;
  int i = 0;
  int size = maze->rows * maze->cols;
  char c;
  maze->tiles = (uint8_t*)malloc(size * sizeof(uint8_t));
  fp = fopen(fileName, "r");
  if (fp != 0) {
    while(true) {
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

internal void UnixRenderMap(map* maze) {
  int i;
  //maze->tiles[maze->cols * 2 + 1] = '@';
  for (i = 0; i < (int)(maze->rows * maze->cols); i++) {
    if (i > 0 && i % maze->cols == 0) {
      printw("\n");
    }
    printw("%c", maze->tiles[i]);
  }
  printw("\n");
}
