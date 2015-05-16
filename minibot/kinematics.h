#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "data_structures.h"
#define PI 3.141592653589793

float radius_rotation(float wheelbase, float dist_l, float dist_r) {
  return abs((dist_r * wheelbase) * (dist_r - dist_l));
}


float angle_rotated(float wheelbase, float dist_l, float dist_r) {
  return (dist_r - dist_l) / wheelbase;
}

Position relative_movement(float wheelbase, float dist_l, float dist_r) {
  Position rel_pos;
  float angle = angle_rotated(wheelbase, dist_l, dist_r);
  float radius = radius_rotation(wheelbase, dist_l, dist_r);
  rel_pos.angle = angle;
  rel_pos.pos.x = radius * cos(angle);
  rel_pos.pos.y = radius * sin(angle);
  return rel_pos;
}

