#include <stdint.h>

#define internal static

const uint32_t VISION_RADIUS = 5;

struct map {
  uint32_t rows;
  uint32_t cols;
  uint8_t* source;
  uint8_t* tiles;
};

struct character {
  uint32_t position;
};

enum input {
  INPUT_INVALID,
  INPUT_UP,
  INPUT_DOWN,
  INPUT_RIGHT,
  INPUT_LEFT,
  INPUT_QUIT
};
