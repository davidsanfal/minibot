#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "pid.h"
#include "data_structures.h"
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

    void move_to(Step stp) {
      unsigned long start_time = millis();
      Position pos;
      pos.angle = stp.dir + _position.angle;
      pos.pos.x = _position.pos.x + (stp.module * cos(stp.dir));
      pos.pos.y = _position.pos.x + (stp.module * sin(stp.dir));

      while (!(pos.angle == _position.angle)) {
        // rotate_to_angle();
      }
      while (!(pos.pos.x == _position.pos.x & pos.pos.y == _position.pos.y)) {
        // move_to_x();
        // move_to_y();
      }
    }

  private:
    PID _pid_r, _pid_l;
    float _via;
    Position _position;
    float _speed;
};
