const uint32_t VISION_RADIUS = 5;

struct map {
  uint32_t rows;
  uint32_t cols;
  uint8_t* source;
  uint8_t* tiles;
};

enum input {
  INPUT_INVALID = 0<<0,
  INPUT_UP      = 1<<0,
  INPUT_DOWN    = 1<<1,
  INPUT_RIGHT   = 1<<2,
  INPUT_LEFT    = 1<<3,
  INPUT_QUIT    = 1<<4
};
