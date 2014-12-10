struct map {
  uint32_t rows;
  uint32_t cols;
  uint8_t* tiles;
};

enum input {
  INPUT_UP    = 1<<0,
  INPUT_DOWN  = 1<<1,
  INPUT_RIGHT = 1<<2,
  INPUT_LEFT  = 1<<3
};
