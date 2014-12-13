#include "maze.h"
#include "unix_maze.cpp"

void MapVision(map* maze, hero* player);
void HandleInput(enum input key, hero* player, map* maze);
vector SetHeroPosition(map* maze);
map LoadMap(int number);

int main() {
  bool running = true;
  bool playing = false;
  map maze;
  hero player;

  PlatformInit();

  while (running) {
    if (playing) {
      enum input key = PlatformProcessInput();
      if (key == INPUT_QUIT) {
        running = false;
      } else if (key != INPUT_INVALID) {
        HandleInput(key, &player, &maze);
        MapVision(&maze, &player);
      }
    } else {
      //TODO create initial menu
      maze = LoadMap(1);
      player.position = SetHeroPosition(&maze);
      MapVision(&maze, &player);
      playing = true;
    }
  }

  PlatformShutdown();
  return 0;
}

void MapVision(map* maze, hero* player) {
  PlatformRenderMap(maze);
}

void HandleInput(enum input key, hero* player, map* maze) {
  vector initial = player->position;
  vector next = initial;
  switch (key) {
    case INPUT_UP:
      next.x--;
      break;
    case INPUT_DOWN:
      next.x++;
      break;
    case INPUT_RIGHT:
      next.y++;
      break;
    case INPUT_LEFT:
      next.y--;
      break;
    default:
      break;
      //does nothing
  }
  if (initial.x == next.x && initial.y == next.y) {
    return; // same position
  }
  if (next.x < 0 || next.x >= maze->rows) {
    return; // invalid x axis
  }
  if (next.y < 0 || next.y >= maze->cols) {
    return; // invalid y axis
  }
  if (maze->tiles[next.x][next.y] == '#') {
    return; // collision detection
  }
  maze->tiles[initial.x][initial.y] = ' ';
  maze->tiles[next.x][next.y] = '@';
  player->position = next;
}

vector SetHeroPosition(map* maze) {
  vector position;
  int x, y;
  bool found = false;
  for (x = 0; x < maze->rows; x++) {
    for (y = 0; y < maze->cols; y++) {
      if (maze->tiles[x][y] == 'S') {
        found = true;
        maze->tiles[x][y] = '@';
        break;
      }
    }
    if (found) { break; }
  }
  position.x = x;
  position.y = y;
  return position;
}

map LoadMap(int number) {
  map maze;
  switch (number) {
    case 1:
      maze.rows = 6;
      maze.cols = 45;
      PlatformReadMapFromFile("map1.txt", &maze);
      break;
  }
  return maze;
}
