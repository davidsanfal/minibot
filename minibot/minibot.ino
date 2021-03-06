#include"robot.h"
#include"motor.h"

const int encoder_steps = 1600;
const float wheel_diameter = 80;
const float wheelbase = 211;

Step steps[256];
Robot robot(wheelbase, wheel_diameter, encoder_steps,
            1.0, 0.0, 0.0, -100.0, 100,
            1.0, 0.0, 0.0, -100.0, 100);

int preR = 0;
int preL = 0;
int num_steps = 0;
float length_step = 80;
int speedL = 150, speedR = 150;
int dirA = LOW, dirB = HIGH;
bool dirG = true;
void setup()
{
  Serial.begin (9600);
  setup_motors();
  Serial.println("Inint ...");
}

void loop()
{
  int distL, distR;
  speedL = 150;
  speedR = 150;
  digitalWrite(dirLPinB, dirB);
  digitalWrite(dirLPinA, dirA);
  digitalWrite(dirRPinB, dirB);
  digitalWrite(dirRPinA, dirA);
  if (dirG) {
    if (encoderLPos < encoderRPos) {
      speedL += abs(encoderRPos - encoderLPos);
      speedR -= abs(encoderRPos - encoderLPos);
    }
    if (encoderLPos > encoderRPos) {
      speedR += abs(encoderLPos - encoderRPos);
      speedL -= abs(encoderRPos - encoderLPos);
    }
  }
  else {
    if (encoderLPos > encoderRPos) {
      speedL += abs(encoderRPos - encoderLPos);
      speedR -= abs(encoderRPos - encoderLPos);
    }
    if (encoderLPos < encoderRPos) {
      speedR += abs(encoderLPos - encoderRPos);
      speedL -= abs(encoderRPos - encoderLPos);
    }
  }
  if (speedR > 255) speedR = 255;
  if (speedL > 255) speedL = 255;
  if (speedR < 0) speedR = 0;
  if (speedL < 0) speedL = 0;
  analogWrite(speedLPin, speedR);
  analogWrite(speedRPin, speedL);
  if (preR != encoderRPos | preL != encoderLPos)
  {
    Serial.print((encoderLPos / encoder_steps)*wheel_diameter * PI);
    Serial.print(" (");
    Serial.print(speedL);
    Serial.print(")");
    Serial.print(" ; ");
    Serial.print((encoderRPos / encoder_steps)*wheel_diameter * PI);
    Serial.print(" (");
    Serial.print(speedR);
    Serial.println(")");
    preR = encoderRPos;
    preL = encoderLPos;
  }
  if ((((encoderLPos / encoder_steps)*wheel_diameter * PI) > 2000) & dirG) {
    dirG = false;
    dirA = HIGH;
    dirB = LOW;
  }
  if ((((encoderLPos / encoder_steps)*wheel_diameter * PI) < 0) & !dirG)  {
    dirG = true;
    dirA = LOW;
    dirB = HIGH;
  }
  if (speedL > 255) speedL = 255;
  //  for (int i = 0; i < sizeof(steps); i++) {
  //    robot.move_to(steps[i]);
  //  }
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


