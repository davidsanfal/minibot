#include"robot.h"
#include"motor.h"

Position steps[256];
Robot robot(211,
            1.0, 0.0, 0.0, -100.0, 100,
            1.0, 0.0, 0.0, -100.0, 100);


void setup()
{
  Serial.begin (9600);
  setup_motors();
}

void loop()
{
  for (int i = 0; i < sizeof(steps); i++) {
    robot.move_to(steps[i]);
  }
}


