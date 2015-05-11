#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "pid.h"
#include "step.h"
enum Direction {RIGTH, LEFT, STOP, FRONT, BACK};

class Robot {

  public:
    Robot( float via,
           double kp_r, double ki_r, double kd_r, double outMin_r, double outMax_r,
           double kp_l, double ki_l, double kd_l, double outMin_l, double outMax_l):
      _pid_r(kp_r, ki_r, kd_r, outMin_r, outMax_r),
      _pid_l(kp_l, ki_l, kd_l, outMin_l, outMax_l)
    {
      _via = via;
      _pid_l.Initialize();
      _pid_r.Initialize();
      _position.angle = 0.0f;
      _position.pos.x = 0.0f;
      _position.pos.y = 0.0f;
      _speed = 50;

    }

    void move_to(Position pos) {
      unsigned long start_time = millis();
      Vector2d relative_pos;
      relative_pos.x = pos.pos.x - _position.pos.x;
      relative_pos.y = pos.pos.y - _position.pos.y;

      while (!(pos.angle == _position.angle)) {
        if((pos.angle - _position.angle) > 0){;}
        if((pos.angle - _position.angle) < 0){;}
        unsigned long now = millis();
      }
      while (!(pos.pos.x == _position.pos.x & pos.pos.y == _position.pos.y)) {
        unsigned long now = millis();
      }
    }

  private:
    PID _pid_r, _pid_l;
    float _via;
    Position _position;
    float _speed;
};
