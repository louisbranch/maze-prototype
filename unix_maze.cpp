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
  maze->tiles = (char**) malloc(maze->cols * sizeof(char*));
  int i;
  for (i = 0; i < maze->cols; i++) {
    maze->tiles[i] = (char*) malloc(maze->rows * sizeof(char));
  }

  FILE* fp;
  char c;
  int x, y;
  bool eof = false;

  fp = fopen(fileName, "r");
  if (fp != 0) {
    for (y = 0; y < maze->rows; y++) {
      if (eof) { break; }
      for (x = 0; x < maze->cols; x++) {
        c = fgetc(fp);
        if (feof(fp)) {
          eof = true;
          break;
        }
        maze->tiles[x][y] = c;
      }
      fgetc(fp); // pop newline
    }
    fclose(fp);
  } else {
    //TODO log error
  }
}

internal void PlatformRenderMap(map* maze, hero* player) {
  clear();   // clear console

  int initial_x = - player->position.x;
  int initial_y = - player->position.y;

  int cols = VISION_COLS + initial_x;
  int rows = VISION_ROWS + initial_y;

  int x,y;

  for (y = initial_y; y < rows; y++) {
    for (x = initial_x; x < cols; x++) {
      vector v;
      v.x = player->position.x + x;
      v.y = player->position.y + y;
      if (!InvalidVector(v, maze)) {
        printw("%c", maze->tiles[v.x][v.y]);
      }
    }
    printw("\n");
  }
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
