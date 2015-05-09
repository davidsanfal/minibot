#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "pid.h"
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
    }
    
    void rotate_rigth(void){;}
    void rotate_left(void){;}

  private:
    PID _pid_r, _pid_l;
    float _via;
};
