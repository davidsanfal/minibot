struct Vector2d {
  Vector2d(int _x = 0, int _y = 0) : x(_x), y(_y) {}
  float x;
  float y;
};

struct Position {
  Position(int _x = 0, int _y = 0, float _angle = 0) : pos(_x, _y), angle(_angle) {}
  Vector2d pos;
  float angle;
};

struct Step {
  Step(float _dir = 0, float _module = 0) : dir(_dir), module(_module) {}
  float dir; //(0,2PI)
  float module; //(0, inf)
};
