#define internal static

struct map {
  int rows;
  int cols;
  char** tiles;
};

struct vector {
  int x;
  int y;
};

struct hero {
  vector position;
};

enum game_stage {
  STAGE_MAIN_MENU,
  STAGE_PLAYING,
  STAGE_NEXT_LEVEL,
  STAGE_EXIT
};

enum input {
  INPUT_INVALID,
  INPUT_UP,
  INPUT_DOWN,
  INPUT_RIGHT,
  INPUT_LEFT,
  INPUT_QUIT
};

const vector EMPTY = {5, 5};

const int VISION_HEIGHT = 7;
const int VISION_WIDTH = 9;
const struct vector VISION_COORDS[VISION_HEIGHT][VISION_WIDTH] = {
  {EMPTY,EMPTY,EMPTY,{-3,-1},{-3,0},{-3,1},EMPTY,EMPTY,EMPTY},
  {EMPTY,EMPTY,{-2,-2},{-2,-1},{-2,0},{-2,1},{-2,2},EMPTY,EMPTY},
  {EMPTY,{-1,-3},{-1,-2},{-1,-1},{-1,0},{-1,1},{-1,2},{-1,3},EMPTY},
  {{0,-4},{0,-3},{0,-2},{0,-1},{0,0},{0,1},{0,2},{0,3},{0,4}},
  {EMPTY,{1,-3},{1,-2},{1,-1},{1,0},{1,1},{1,2},{1,3},EMPTY},
  {EMPTY,EMPTY,{2,-2},{2,-1},{2,0},{2,1},{2,2},EMPTY,EMPTY},
  {EMPTY,EMPTY,EMPTY,{3,-1},{3,0},{3,1},EMPTY,EMPTY,EMPTY}
};

bool InvalidVector(vector, map*);
