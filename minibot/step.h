#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

struct Vector2d {
  float x;
  float y;
};

struct Position {
  Vector2d pos;
  float angle;
};
