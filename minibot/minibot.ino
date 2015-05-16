#include"robot.h"
#include"motor.h"

const int encoder_steps = 1600;
const float wheel_diameter = 80;
const float wheelbase = 211;

Step steps[256];
Robot robot(wheelbase, wheel_diameter, encoder_steps,
            1.0, 0.0, 0.0, -100.0, 100,
            1.0, 0.0, 0.0, -100.0, 100);

int preR = -1;
int preL = -1;
int num_steps = 0;
float length_step = 80;
void setup()
{
  Serial.begin (9600);
  setup_motors();
  Serial.println("Inint ...");
}

void loop()
{
  //logger();
  for (int i = 0; i < sizeof(steps); i++) {
    robot.move_to(steps[i]);
  }
}

void logger() {
  if (preR != encoderRPos | preL != encoderLPos)
  {
    Serial.print(encoderLPos);
    Serial.print(" ; ");
    Serial.println(encoderRPos);
    preR = encoderRPos;
    preL = encoderLPos;
  }
}

void add_step(float angle) {
  Step _step(angle, length_step);
  steps[num_steps] = _step;
  num_steps++;
}


