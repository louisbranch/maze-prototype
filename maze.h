#define internal static

const int VISION_RADIUS = 7;

struct map {
  int rows;
  int cols;
  char* source;
  char* tiles;
};

struct hero {
  int position;
};

enum input {
  INPUT_INVALID,
  INPUT_UP,
  INPUT_DOWN,
  INPUT_RIGHT,
  INPUT_LEFT,
  INPUT_QUIT
};
