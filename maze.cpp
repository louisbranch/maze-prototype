#include "maze.h"
#include "unix_maze.cpp"

void MapVision(map* maze, hero* player);
void HandleInput(enum input key, map* maze);
int SetHeroPosition(map* maze);
map CreateMap();

int main() {
  bool running = true;

  PlatformInit();

  map maze = CreateMap();

  hero player;
  player.position = SetHeroPosition(&maze);

  MapVision(&maze, &player);

  while (running) {
    enum input key = PlatformProcessInput();
    if (key == INPUT_QUIT) {
      running = false;
    } else if (key != INPUT_INVALID) {
      HandleInput(key, &maze);
      MapVision(&maze, &player);
    }
  }

  PlatformShutdown();
  return 0;
}

void MapVision(map* maze, hero* player) {
  int position = player->position;
  int size = maze->rows * maze->cols;
  int i;
  int j = 0;

  for(i = position - 3;
      i < position + 4;
      i++) {
    if (i >= 0 && i <= size) {
      maze->tiles[j] = maze->source[i];
      j++;
    }
  }
  PlatformRenderMap(maze);
}

void HandleInput(enum input i, map* maze) {
  printw("%i", i);
}

int SetHeroPosition(map* maze) {
  int i;
  for(i = 0;
      i < maze->rows * maze->cols;
      i++) {
    if (maze->source[i] == 'S') {
      maze->source[i] = '@';
      return i;
    }
  }
  //TODO assert position was set
  return 0;
}

map CreateMap() {
  map maze;
  maze.rows = 6;
  maze.cols = 45;
  PlatformReadMapFromFile("map1.txt", &maze);
  return maze;
}
