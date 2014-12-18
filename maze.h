#define internal static

const int VISION_WIDTH = 20;
const int VISION_HEIGHT = 5;

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

bool InvalidVector(vector, map*);
