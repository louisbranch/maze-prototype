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
  maze->tiles = (char**) malloc(maze->rows * sizeof(char*));
  int i;
  for (i = 0; i < maze->rows; i++) {
    maze->tiles[i] = (char*) malloc(maze->cols * sizeof(char));
  }

  FILE* fp;
  char c;
  int x, y;
  bool eof = false;

  fp = fopen(fileName, "r");
  if (fp != 0) {
    for (x = 0; x < maze->rows; x++) {
      if (eof) { break; }
      for (y = 0; y < maze->cols; y++) {
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
  int width = VISION_WIDTH / 2;
  int height = VISION_HEIGHT / 2;
  int x = -height;

  while (x < height) {
    int y = -width;
    while (y < width) {
      vector v;
      v.x = player->position.x + x;
      v.y = player->position.y + y;
      bool invalid = InvalidVector(v, maze);
      if (!invalid) {
        printw("%c", maze->tiles[v.x][v.y]);
      }
      y++;
    }
    printw("\n");
    x++;
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
