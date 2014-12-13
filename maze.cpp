#include "maze.h"
#include "unix_maze.cpp"

void MapVision(map* maze, hero* player);
enum game_stage HandleInput(enum input key, hero* player, map* maze);
vector SetHeroPosition(map* maze);
map LoadMap(int number);

int main() {
  bool running = true;
  enum game_stage stage = STAGE_MAIN_MENU;
  map maze;
  hero player;

  PlatformInit();

  while (running) {
    switch (stage) {
      case STAGE_PLAYING: {
        enum input key = PlatformProcessInput();
        if (key == INPUT_QUIT) {
          stage = STAGE_EXIT;
        } else if (key != INPUT_INVALID) {
          stage = HandleInput(key, &player, &maze);
          MapVision(&maze, &player);
        }
      } break;
      case STAGE_NEXT_LEVEL: { //TODO add more maps!
        stage = STAGE_EXIT;
      } break;
      case STAGE_MAIN_MENU: { //TODO create intro menu
        maze = LoadMap(1);
        player.position = SetHeroPosition(&maze);
        MapVision(&maze, &player);
        stage = STAGE_PLAYING;
      } break;
      case STAGE_EXIT: {
        running = false;
      } break;
      default:
        // does nothing yet
        break;
    }
  }

  PlatformShutdown();
  return 0;
}

void MapVision(map* maze, hero* player) {
  PlatformRenderMap(maze);
}

enum game_stage HandleInput(enum input key, hero* player, map* maze) {
  enum game_stage stage = STAGE_PLAYING;
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
    return stage; // same position
  }
  if (next.x < 0 || next.x >= maze->rows) {
    return stage; // invalid x axis
  }
  if (next.y < 0 || next.y >= maze->cols) {
    return stage; // invalid y axis
  }
  if (maze->tiles[next.x][next.y] == '#') {
    return stage; // collision detection
  }
  if (maze->tiles[next.x][next.y] == 'E') {
    stage = STAGE_NEXT_LEVEL;
    return stage; // reached exit
  }
  maze->tiles[initial.x][initial.y] = ' ';
  maze->tiles[next.x][next.y] = '@';
  player->position = next;
  return stage;
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
