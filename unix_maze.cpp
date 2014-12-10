#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

void PlatformInit() {
  initscr();   // starts ncurses mode
  cbreak();    // disable line buffering
  noecho();    // disable echo on getch
  curs_set(0); // hide cursor
}

void PlatformShutdown() {
  endwin(); // end ncurses mode
}

internal void PlatformReadMapFromFile(const char* fileName, map* maze) {
  FILE* fp;
  int i = 0;
  int size = maze->rows * maze->cols;
  char c;
  maze->source = (uint8_t*)malloc(size * sizeof(uint8_t));
  maze->tiles = (uint8_t*)malloc(VISION_RADIUS * VISION_RADIUS * sizeof(uint8_t));
  fp = fopen(fileName, "r");
  if (fp != 0) {
    while(true) {
      c = fgetc(fp);
      if(i >= size || feof(fp)) {
        break;
      }
      if (c != '\n') {
        maze->source[i] = c;
        ++i;
      }
    }
    fclose(fp);
  } else {
    //TODO log error
  }
}

internal void PlatformRenderMap(map* maze) {
  clear();   // clear console
  int i;
  //maze->tiles[maze->cols * 2 + 1] = '@';
  for (i = 0; i < (int)(maze->rows * maze->cols); i++) {
    if (i > 0 && i % maze->cols == 0) {
      printw("\n");
    }
    printw("%c", maze->source[i]);
  }
  printw("\n");
  refresh(); // refresh console
}

internal enum input PlatformProcessInput() {
  char ch = getch();
  switch (ch) {
    case 'q':
      clear();
      printw("Are you sure? (y/[n])");
      refresh();
      ch = getch();
      if (ch == 'y') {
        return INPUT_QUIT;
      }
    case 'w': return INPUT_UP;
    case 'a': return INPUT_LEFT;
    case 's': return INPUT_DOWN;
    case 'd': return INPUT_RIGHT;
    default : return INPUT_INVALID;
  }
}
