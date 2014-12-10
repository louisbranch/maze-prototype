#include "maze.h"
#include "unix_maze.cpp"

void HandleInput(enum input key, map* maze);

int main() {
  PlatformInit();

  map maze;
  maze.rows = 6;
  maze.cols = 45;
  PlatformReadMapFromFile("map1.txt", &maze);
  PlatformRenderMap(&maze);

  while (true) {
    enum input key = PlatformProcessInput();
    if (key == INPUT_QUIT) {
      break;
    } else if (key != INPUT_INVALID) {
      HandleInput(key, &maze);
      PlatformRenderMap(&maze);
    }
  }
  PlatformShutdown();
  return 0;
}

void HandleInput(enum input i, map* maze) {
  printw("%i", i);
}
