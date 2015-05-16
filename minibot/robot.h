#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


#include "pid.h"
#include "kinematics.h"
enum Direction {RIGTH, LEFT, STOP, FRONT, BACK};

class Robot {

  public:
    Robot( float wheelbase, float wheel_diameter, int encoder_steps,
           double kp_r, double ki_r, double kd_r, double outMin_r, double outMax_r,
           double kp_l, double ki_l, double kd_l, double outMin_l, double outMax_l):
      _pid_r(kp_r, ki_r, kd_r, outMin_r, outMax_r),
      _pid_l(kp_l, ki_l, kd_l, outMin_l, outMax_l)
    {
      _wheelbase = wheelbase;
      _wheel_diameter = wheel_diameter;
      _pid_l.Initialize();
      _pid_r.Initialize();
      _position.angle = 0.0f;
      _position.pos.x = 0.0f;
      _position.pos.y = 0.0f;
      _speed = 0;
      _encoder_steps = encoder_steps;
      _wheel_step = _wheel_diameter * PI / encoder_steps;
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

    void set_speed(float spd) {
      _speed = spd;
    }

  private:

    PID _pid_r, _pid_l;
    float _wheelbase, _wheel_diameter, _speed, _wheel_step;
    Position _position;
    int _encoder_steps;
};
